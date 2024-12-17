/*
 * motor_controller.h
 *
 *  Created on: Dec 15, 2024
 *      Author: ngocrc
 */

#ifndef INC_MOTOR_CONTROLLER_H_
#define INC_MOTOR_CONTROLLER_H_

#include "encoder.h"
#include "motor_driver.h"
#include "pid.h"

#define MAX_COUNT_PER_PID_CONTROL_LOOP	32
#define PID_PARAMETER_P					3.3
#define PID_PARAMETER_I					1.7
#define PID_PARAMETER_D					0.01

typedef struct {
	double speed;
	double pid_speed;
	double target_speed;
	PID_TypeDef pid;
	encoder_t encoder;
	motor_t motor;
} PIDLoop_Typedef;

extern PIDLoop_Typedef pid_loop_right;

extern void pid_loop_init(PIDLoop_Typedef* loop_inst);
extern void pid_loop_handler(PIDLoop_Typedef* loop_inst);
extern void pid_loop_set_speed(PIDLoop_Typedef* loop_inst, double speed);

#endif /* INC_MOTOR_CONTROLLER_H_ */
