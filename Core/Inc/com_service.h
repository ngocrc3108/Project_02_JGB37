/*
 * com_service.h
 *
 *  Created on: Dec 17, 2024
 *      Author: ngocrc
 */

#ifndef INC_COM_SERVICE_H_
#define INC_COM_SERVICE_H_

#include "stdint.h"

typedef enum {
	COM_SERVICE_READ_ENCODER = 0x04,
	COM_SERVICE_VELOCITY_WRITE = 0x05,
	COM_SERVICE_NEGATIVE_RESPONE = 0x7F,
} ComService_t;

typedef enum {
	COM_STATUS_OK = 0,
	COM_STATUS_ERR,
} ComStatus_t;

ComStatus_t com_handler(uint8_t* data, uint32_t len);
ComStatus_t com_read_encoder_service();
ComStatus_t com_write_velocity_service(uint8_t* data);
ComStatus_t com_out_of_service();

#endif /* INC_COM_SERVICE_H_ */
