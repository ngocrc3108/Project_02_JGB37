/*
 * encoder.c
 *
 *  Created on: Dec 14, 2024
 *      Author: ngocrc
 */
#include "encoder.h"

void encoder_init(encoder_t* encoder, TIM_HandleTypeDef* htim) {
	encoder->timer_instance = htim->Instance;
	encoder->value = 0;
	encoder->last_value = 0;
	encoder->delta_count = 0;

	HAL_TIM_Encoder_Start(htim, TIM_CHANNEL_ALL);
}

void encoder_interrupt_handler(encoder_t* encoder) {
	encoder->value = encoder->timer_instance->CNT;

	// uint8_t direction = (encoder->timer_instance->CR1 >> 4) & 0x1;

	// un-sign numbers' magic :)
	encoder->delta_count = (int8_t)(encoder->value - encoder->last_value); // do not reduce the equation!
	// encoder->delta_count = direction == COUNT_DIR_BIT_UP ? encoder->delta_count : -encoder->delta_count;

	encoder->last_value = encoder->value;
}
