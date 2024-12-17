/*
 * motor_controller.c
 *
 *  Created on: Dec 15, 2024
 *      Author: ngocrc
 */

#include "motor_controller.h"

void pid_loop_handler(PIDLoop_Typedef* loop_inst)
{
	loop_inst->speed = (double)loop_inst->encoder.delta_count;

	PID_Compute(&loop_inst->pid);

	motor_move_operate(&loop_inst->motor, (int)(loop_inst->pid_speed / MAX_COUNT_PER_PID_CONTROL_LOOP * MOTOR_MAX_SPEED));
}

void pid_loop_init(PIDLoop_Typedef* loop_inst)
{
  PID(&loop_inst->pid, &loop_inst->speed, &loop_inst->pid_speed, &loop_inst->target_speed,
  		PID_PARAMETER_P, PID_PARAMETER_I, PID_PARAMETER_D, _PID_P_ON_E, _PID_CD_DIRECT);
  PID_SetMode(&loop_inst->pid, _PID_MODE_AUTOMATIC);
  PID_SetSampleTime(&loop_inst->pid, 1000.0 / INTERVAL_FREQUENCY);
  PID_SetOutputLimits(&loop_inst->pid, -MAX_COUNT_PER_PID_CONTROL_LOOP, MAX_COUNT_PER_PID_CONTROL_LOOP);
}

void pid_loop_set_speed(PIDLoop_Typedef* loop_inst, double speed)
{
	loop_inst->target_speed = speed;
}
