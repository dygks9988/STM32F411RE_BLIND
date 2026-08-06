/*
 * stopwatch_task.c
 *
 *  Created on: Jun 24, 2026
 *      Author: PC
 */



#include "rtos_task.h"
#include "stopwatch.h"
#include "ap_lcd.h"


const TickType_t Sw_Task_Delay_Tick = 10;

/**
 * @brief   stopwatch_process를 10ms주기로 호출하고,명령을 수신 받으면 stopwatch_set_cmd를 호출하여 동작 정책을 수정.
 * @return NONE
 */
void stopwatch_task(){
	Sw_Cmd_Type_t Cmd = SW_NONE;

	LcdMessage_TypeDef lcd_stopwatch_msg = {TARGET_STOPWATCH,0,SW_NONE};

	uint8_t sw_state;
	uint32_t display_value = 0;
	uint32_t previous_display_value = 0;

	TickType_t xLastWakeTime = xTaskGetTickCount();

	stopwatch_init();

	for(;;){
		if(xQueueReceive(SW_Cmd_QueueHandle,&Cmd,0)== pdPASS){
			stopwatch_set_cmd(Cmd);
		}
		stopwatch_process();
		get_stopwatch_snapshot(&sw_state, &display_value);
		lcd_stopwatch_msg.state = sw_state;
		lcd_stopwatch_msg.value = display_value;

		if(display_value - previous_display_value >= 1){ // 1초가 지났을 때
		xQueueSend(LcdMsg_QueueHandle,&lcd_stopwatch_msg,pdMS_TO_TICKS(5));
		previous_display_value = display_value;
		}
		vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(10));
	}
}

