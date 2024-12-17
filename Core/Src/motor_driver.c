/*
 * motor_driver.c
 *
 *  Created on: Dec 14, 2024
 *      Author: ngocrc
 */
#include "motor_driver.h"

static void motor_move_forward(motor_t* motor);
static void motor_move_backward(motor_t* motor);
static void motor_stop(motor_t* motor);

void motor_init(motor_t* motor, TIM_HandleTypeDef* htim, volatile uint32_t* p_CCR_A, volatile uint32_t* p_CCR_B, uint32_t channel_a, uint32_t channel_b) {
	motor->timer_instance = htim->Instance;
	motor->p_CCR_A = p_CCR_A;
	motor->p_CCR_B = p_CCR_B;

	motor_move_operate(motor, 0); // stop the motor if it is operating

	HAL_TIM_PWM_Start(htim, channel_a);
	HAL_TIM_PWM_Start(htim, channel_b);
}

extern void motor_move_operate(motor_t* motor, int speed) {
	motor->speed = speed;

	if(speed > 0)
		motor_move_forward(motor);
	else if(speed < 0)
		motor_move_backward(motor);
	else
		motor_stop(motor);
}

void motor_move_forward(motor_t* motor) {
	*motor->p_CCR_A = motor->speed;
	*motor->p_CCR_B = 0;
}

void motor_move_backward(motor_t* motor) {
	*motor->p_CCR_A = 0;
	*motor->p_CCR_B = -motor->speed;
}

void motor_stop(motor_t* motor) {
	*motor->p_CCR_A = 0;
	*motor->p_CCR_B = 0;
}
