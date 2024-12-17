/*
 * motor_driver.h
 *
 *  Created on: Dec 14, 2024
 *      Author: ngocrc
 */

#ifndef INC_MOTOR_DRIVER_H_
#define INC_MOTOR_DRIVER_H_

#include "stm32f1xx_hal.h"

typedef struct {
	int speed; // count per pid loop
	volatile uint32_t* p_CCR_A;
	volatile uint32_t* p_CCR_B;
	TIM_TypeDef* timer_instance;
} motor_t;

extern void motor_init(motor_t* motor, TIM_HandleTypeDef* htim, volatile uint32_t* p_CCR_A, volatile uint32_t* p_CCR_B, uint32_t channel_a, uint32_t channel_b);
extern void motor_move_operate(motor_t* motor, int speed);

#endif /* INC_MOTOR_DRIVER_H_ */
