/*
 * servo_motor_task.c
 *
 *  Created on: Jul 9, 2026
 *      Author: PC
 */
#include "rtos_task.h"
#include "servo_motor.h"

/**
 * @brief   서보 모터의 인스터스를 생성,명령을 수신하면 서보모터 애플리케이션 모듈을 호출한다.
 * @details   루프가 서보 모터 명령을 수신받을 때까지 Blocking 되며, 태스크가 실행 되면 서보모터가 동작 상태로 시작한다.
 * @return NONE
 */

void servo_motor_task(void){
	Servo_Cmd_PacketTypeDef pservo_cmd;
	Servo_HandleTypeDef hservo1;

	servo_motor_init(&hservo1,SERVO_MOTOR_TIM_CH);

	pservo_cmd.servo_cmd = SERVO_CMD_START;
	pservo_cmd.servo_cmd_angle = 0;
	set_servo_motor_cmd(&hservo1, &pservo_cmd);
	servo_motor_process(&hservo1);

	for(;;){
		if(xQueueReceive(Servo_Cmd_QueueHandle, &pservo_cmd, portMAX_DELAY)==pdPASS){
			set_servo_motor_cmd(&hservo1,&pservo_cmd);
			servo_motor_process(&hservo1);
		}
	}
}
