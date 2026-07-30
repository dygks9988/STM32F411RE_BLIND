/*
 * smart_blind_task.c
 *
 *  Created on: Jul 16, 2026
 *      Author: PC
 */

#include "rtos_task.h"
#include "smart_blind.h"

/**
 * @brief   블라인드 상태를 저장할 변수 생성,명령을 수신하면 블라인드 애플리케이션 모듈을 호출하고, 서보 모터로 명령을 송신한다
 * @details   루프가 명령을 수신받을 때까지 Blocking 된다.
 * @return NONE
 */

void smart_blind_task(void){
	Blind_StateTypeDef blind_state;
	Blind_CmdTypeDef blind_cmd;
	Servo_Cmd_PacketTypeDef pservo_cmd;

	blind_init(&blind_state);

	for(;;){
		if(xQueueReceive(SmartBlind_Cmd_QueueHandle, &blind_cmd, portMAX_DELAY)==pdPASS){
			if(blind_process(&blind_state,blind_cmd,&pservo_cmd) == true){
				xQueueSend(Servo_Cmd_QueueHandle,&pservo_cmd,pdMS_TO_TICKS(10));
			};
		}
	}
}
