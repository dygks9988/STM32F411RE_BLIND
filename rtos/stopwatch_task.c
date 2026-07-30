/*
 * stopwatch_task.c
 *
 *  Created on: Jun 24, 2026
 *      Author: PC
 */



#include "rtos_task.h"
#include "stopwatch.h"

const TickType_t Sw_Task_Delay_Tick = 10;

/**
 * @brief   stopwatch_process를 10ms주기로 호출하고,명령을 수신 받으면 stopwatch_set_cmd를 호출하여 동작 정책을 수정.
 * @return NONE
 */


void stopwatch_task(){
	stopwatch_init();
	Sw_Cmd_Type_t Cmd = SW_NONE;
	TickType_t xLastWakeTime = xTaskGetTickCount();

	for(;;){
		if(xQueueReceive(SW_Cmd_QueueHandle,&Cmd,0)== pdPASS){
			stopwatch_set_cmd(Cmd);
		}
		stopwatch_process();
		vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(10));
	}
}

