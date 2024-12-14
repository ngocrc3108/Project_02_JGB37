/*
 * encoder.h
 *
 *  Created on: Dec 14, 2024
 *      Author: ngocrc
 */

#ifndef INC_ENCODER_H_
#define INC_ENCODER_H_

#include "stm32f1xx_hal.h"

#define COUNT_PER_CYCLE 11
#define COUNT_DIR_BIT_UP 0
#define COUNT_DIR_BIT_DOWN 1
#define INTERVAL_FREQUENCY 30

typedef struct {
	int8_t delta_count; // the count between 2 interrupt
	uint16_t value; // the current value of timer
	uint16_t last_value; // the value of timer in last interrupt
	TIM_TypeDef* timer_instance;
} encoder_t;

extern void encoder_init(encoder_t* encoder, TIM_HandleTypeDef* htim);
extern void encoder_interrupt_handler(encoder_t* encoder);

#endif /* INC_ENCODER_H_ */
