/*
 * display_task.c
 *
 *  Created on: Aug 4, 2026
 *      Author: PC
 */
#include "FreeRTOS.h"
#include "task.h"
#include "ap_lcd.h"


void display_task(void){
	lcd_begin(0);
	lcd_set_cursor(0, 0, 0);
	lcd_write_str(0, "AAAAAAAAAAAAAAAA");
	lcd_write_str(0, "1234567890123456");
	lcd_set_cursor(0, 1, 0);
	lcd_write_str(0, "HELLO WORLD");
}
