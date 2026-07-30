/*
 * lcd.c
 *
 *  Created on: Jul 30, 2026
 *      Author: PC
 */

#include "lcd.h"
#define MAX_LCD 1
#define LCD_CH0

enum lcd_instruction{
	Clear_Display = 0x01,
	Return_Home = 0x02,
	Display_onoff = 0x10,
	Set_CGRAM_Address = 0x40,
	Set_DDRAM_Address = 0x80,
};

typedef struct{
	GPIO_TypeDef* port;
	uint16_t pin_num;
}Lcd_ConnTypeDef;

typedef struct{
	Lcd_ConnTypeDef rs;
	Lcd_ConnTypeDef en;
	Lcd_ConnTypeDef db[4];
}Lcd_PinTypeDef;

typedef struct{
Lcd_PinTypeDef lcd_pin;
uint8_t row;
uint8_t col;
bool lcd_onoff;
}Lcd_HandleTypeDef;

static Lcd_HandleTypeDef lcd_tbl[MAX_LCD];

static void lcd_bit_reset(uint8_t ch){
	#ifdef LCD_CH0
	if(ch == 0){
		HAL_GPIO_WritePin(lcd_tbl[0].lcd_pin.rs.port,lcd_tbl[0].lcd_pin.rs.pin_num, GPIO_PIN_RESET);
		for(int i;i <4; i++){
			HAL_GPIO_WritePin(lcd_tbl[0].lcd_pin.db[i].port,lcd_tbl[0].lcd_pin.db[i].pin_num, GPIO_PIN_RESET);
		}
	}
	#endif
}
void lcd_command(void);


static void lcd_init(uint8_t ch){

	#ifdef LCD_CH0
	if(ch == 0){
	// GPIO 핀 매핑
	lcd_tbl[ch].lcd_pin.rs.port = GPIOA;
	lcd_tbl[ch].lcd_pin.rs.pin_num = GPIO_PIN_6;

	lcd_tbl[ch].lcd_pin.en.port = GPIOA;
	lcd_tbl[ch].lcd_pin.en.pin_num = GPIO_PIN_6;

	lcd_tbl[ch].lcd_pin.db[0].port = GPIOA;
	lcd_tbl[ch].lcd_pin.db[0].pin_num = GPIO_PIN_6;

	lcd_tbl[ch].lcd_pin.db[1].port = GPIOA;
	lcd_tbl[ch].lcd_pin.db[1].pin_num = GPIO_PIN_6;

	lcd_tbl[ch].lcd_pin.db[2].port = GPIOA;
	lcd_tbl[ch].lcd_pin.db[2].pin_num = GPIO_PIN_6;

	lcd_tbl[ch].lcd_pin.db[3].port = GPIOA;
	lcd_tbl[ch].lcd_pin.db[3].pin_num = GPIO_PIN_6;
	}

	HAL_GPIO_WritePin(lcd_tbl[0].lcd_pin.en.port,lcd_tbl[0].lcd_pin.en.pin_num, GPIO_PIN_SET);
	lcd_bit_reset(ch);

	lcd_tbl[0].row = 0;
	lcd_tbl[0].col = 0;
	lcd_tbl[0].lcd_onoff = false;

	#endif
}



bool lcd_begin(uint8_t ch)
{
	if (ch >= MAX_LCD)return false;
	lcd_init(ch);




	return true;
}

bool lcd_set_cursor(uint8_t ch,uint8_t row,uint8_t col){
	if (ch >= MAX_LCD)return false;

	return true;
} // DDRAM address 설정


bool lcd_write_str(uint8_t ch,const char* str){
	if (ch >= MAX_LCD || str == NULL)return false;

	return true;
} // DDRAM data 작성


bool lcd_clear(uint8_t ch){
	if (ch >= MAX_LCD)return false;

	return true;
} //clear


