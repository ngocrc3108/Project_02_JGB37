/*
 * com_service.c
 *
 *  Created on: Dec 18, 2024
 *      Author: ngocrc
 */

#include "com_service.h"
#include "motor_controller.h"
#include "usbd_cdc_if.h"

ComStatus_t com_handler(uint8_t* data, uint32_t len)
{
	ComStatus_t status = COM_STATUS_OK;

	if(len == 1 && data[0] == COM_SERVICE_READ_ENCODER)
		status = com_read_encoder_service();
	else if(len == 3 && data[0] == COM_SERVICE_VELOCITY_WRITE)
		status = com_write_velocity_service(data);
	else
		status = com_out_of_service(); // send back negative code

	return status;
}

ComStatus_t com_read_encoder_service()
{
  /* Important function */
  uint32_t prim;

  /* Do some stuff here which can be interrupted */
	int8_t data[3];

	data[0] = COM_SERVICE_READ_ENCODER;

  /* Read PRIMASK register, check interrupt status before you disable them */
  /* Returns 0 if they are enabled, or non-zero if disabled */
  prim = __get_PRIMASK();

  /* Disable interrupts */
  __disable_irq();

  /* Do some stuff here which can not be interrupted */
	data[1] = pid_loop_left.encoder.delta_count;
	data[2] = pid_loop_right.encoder.delta_count;

  /* Enable interrupts back */
  if (!prim) {
      __enable_irq();
  }

  /* Do some stuff here which can be interrupted */
	uint8_t result = CDC_Transmit_FS((uint8_t*)&data, sizeof(data));

	if(result == USBD_OK)
		return COM_STATUS_OK;

	return COM_STATUS_ERR;
}

ComStatus_t com_write_velocity_service(uint8_t* data)
{
	pid_loop_left.target_speed = (double)((int8_t)data[1]);
	pid_loop_right.target_speed = (double)((int8_t)data[2]);

	uint8_t response[1] = {COM_SERVICE_VELOCITY_WRITE};
	uint8_t result = CDC_Transmit_FS(response, sizeof(response));

	if(result == USBD_OK)
		return COM_STATUS_OK;

	return COM_STATUS_ERR;
}

ComStatus_t com_out_of_service()
{
	uint8_t data[1] = {COM_SERVICE_NEGATIVE_RESPONE};

	uint8_t result = CDC_Transmit_FS(data, sizeof(data));

	if(result == USBD_OK)
		return COM_STATUS_OK;

	return COM_STATUS_ERR;
}
