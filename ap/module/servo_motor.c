/*
 * servo_motor.c
 *
 *  Created on: Jul 9, 2026
 *      Author: PC
 */
#include "servo_motor.h"

void servo_motor_init(Servo_HandleTypeDef* hservo,uint8_t tim_ch){
	if(hservo == NULL)return;

	hservo->servo_angle = 0;
	hservo->servo_state = SERVO_STOP;
	hservo->servo_tim_ch = tim_ch;
}


void set_servo_motor_cmd(Servo_HandleTypeDef* hservo,Servo_Cmd_PacketTypeDef* pservo_cmd){
	if(hservo == NULL || pservo_cmd == NULL)return;

	hservo->hservo_cmd.servo_cmd = pservo_cmd->servo_cmd;
	hservo->hservo_cmd.servo_cmd_angle = pservo_cmd->servo_cmd_angle;
}

/**
 * @brief    서보모터 명령을 처리하고 명령에 따라 상태를 수정한다.
 * @param[in,out]   hservo   현재 서보의 상태, 수행 할 명령을 담는 인스턴스
 * @return NONE
 * @warning   1회성으로 실행 되는 프로세스이기에 명령을 소비하지 않는 구조, 주기성 실행이 필요하다면 리팩토링 필요하다.
 */
void servo_motor_process(Servo_HandleTypeDef* hservo){
	if(hservo == NULL)return;

	switch(hservo->servo_state){
		case SERVO_STOP:
			if(hservo->hservo_cmd.servo_cmd == SERVO_CMD_START){
				hw_motor_start(hservo->servo_tim_ch);
				hservo->servo_state = SERVO_HOLDING;
				hw_motor_set_angle(hservo->servo_tim_ch,hservo->hservo_cmd.servo_cmd_angle);
				hservo->servo_angle = hservo->hservo_cmd.servo_cmd_angle;
			}
			break;
		case SERVO_HOLDING:
			if(hservo->hservo_cmd.servo_cmd == SERVO_CMD_STOP){
				hw_motor_stop(hservo->servo_tim_ch);
				hservo->servo_state = SERVO_STOP;
			}
			break;
	}
	if (hservo->hservo_cmd.servo_cmd == SERVO_CMD_SET_ANGLE){
		hw_motor_set_angle(hservo->servo_tim_ch,hservo->hservo_cmd.servo_cmd_angle);
		hservo->servo_angle = hservo->hservo_cmd.servo_cmd_angle;
	}
}
