/*
 * ap_lcd.h
 *
 *  Created on: Aug 4, 2026
 *      Author: PC
 */

#ifndef MODULE_AP_LCD_H_
#define MODULE_AP_LCD_H_

#include "lcd.h"

typedef enum{
	TARGET_NONE = 0,
	TARGET_STOPWATCH,
	TARGET_SMARTBLIND
}LcdTarget_TypeDef;

typedef struct {
	LcdTarget_TypeDef target;
	uint32_t value;
	uint8_t state;
}LcdMessage_TypeDef;

bool ap_lcd_process();



#endif /* MODULE_AP_LCD_H_ */
