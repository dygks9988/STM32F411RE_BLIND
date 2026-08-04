/*
 * lcd.h
 *
 *  Created on: Jul 30, 2026
 *      Author: PC
 */

#ifndef DRIVER_LCD_H_
#define DRIVER_LCD_H_

#include "gpio.h"


#define MAX_LCD 1


bool lcd_begin(uint8_t ch);
bool lcd_set_cursor(uint8_t ch,uint8_t row,uint8_t col);
bool lcd_write_str(uint8_t ch,const char* str);
bool lcd_clear(uint8_t ch);



#endif /* DRIVER_LCD_H_ */
