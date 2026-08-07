/*
 * display_task.c
 *
 *  Created on: Aug 5, 2026
 *      Author: PC
 */
#include "ap_lcd.h"
#include "rtos_task.h"


void display_task(void){
	lcd_begin(0);

	LcdMessage_TypeDef lcd_msg;
	memset(&lcd_msg,0,sizeof(lcd_msg));


	for(;;){
		if(xQueueReceive(LcdMsg_QueueHandle, &lcd_msg, portMAX_DELAY)){
			lcd_unpacking_msg(0, &lcd_msg);
			lcd_update(0);
		}
	}
}


