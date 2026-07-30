/*
 * hw_motor.c
 *
 *  Created on: Jul 8, 2026
 *      Author: PC
 */

#include "hw_motor.h"
#define MAX_ANGLE 180
#define SERVO_MIN_CCR 600



void hw_motor_init(uint8_t ch){
	hw_motor_set_angle(ch,0);
	hw_motor_stop(ch);
}

void hw_motor_start(uint8_t ch){
	hw_TIM_pwm_start(ch);
}

void hw_motor_stop(uint8_t ch){
	hw_TIM_pwm_stop(ch);
}

static uint16_t angle_to_ccr(uint8_t angle){
	if(angle > MAX_ANGLE)angle = MAX_ANGLE;

	return ((uint16_t)angle*10) + SERVO_MIN_CCR; // 각도 1당 CCR값 * 각도 + SERVO_MIN_CCR
}

void hw_motor_set_angle(uint8_t ch,uint8_t angle){

	hw_TIM_pwm_set_ccr(ch,angle_to_ccr(angle));
}
