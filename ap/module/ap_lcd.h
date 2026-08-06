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


/* lcd msg instance
 * lcd task에 queue를 send할 때 사용 되며 송신 측에서 값을 대입한 뒤 송신 되어야 한다.
 */
typedef struct {
	LcdTarget_TypeDef target;
	uint32_t value;
	uint8_t state;
}LcdMessage_TypeDef;


bool lcd_unpacking_msg(uint8_t ch,const LcdMessage_TypeDef* msg);
bool lcd_update(uint8_t ch);



#endif /* MODULE_AP_LCD_H_ */
