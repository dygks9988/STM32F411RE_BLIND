/*
 * lcd.c
 *
 *  Created on: Jul 30, 2026
 *      Author: PC
 */

#include "lcd.h"
#include "FreeRTOS.h"
#include "task.h"



#define MAX_LCD 1
#define MY_RTOS


enum lcd_instruction{
	Display_clear = 0x01,
	Return_Home = 0x02,
	Entry_mode_set = 0x06,
	Display_off = 0x08,
	Display_on = 0x0c,
	Function_set = 0x20,
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


static void Delay_us(uint32_t microseconds)
{
	uint32_t start_cycle = DWT->CYCCNT;
	uint32_t cycles_per_us = HAL_RCC_GetHCLKFreq() / 1000000; // 1us occur cycles

	while ((DWT->CYCCNT - start_cycle)
	       < microseconds * cycles_per_us) {
	};
}




static void lcd_bit_reset(uint8_t ch){

	HAL_GPIO_WritePin(lcd_tbl[ch].lcd_pin.rs.port,lcd_tbl[ch].lcd_pin.rs.pin_num, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(lcd_tbl[ch].lcd_pin.en.port,lcd_tbl[ch].lcd_pin.en.pin_num, GPIO_PIN_RESET);
	for(int i=0;i <4; i++){
		HAL_GPIO_WritePin(lcd_tbl[ch].lcd_pin.db[i].port,lcd_tbl[ch].lcd_pin.db[i].pin_num, GPIO_PIN_RESET);
	}

}

static void enable_pulse(uint8_t ch){
	HAL_GPIO_WritePin(
		lcd_tbl[ch].lcd_pin.en.port,
		lcd_tbl[ch].lcd_pin.en.pin_num,
		GPIO_PIN_RESET);

	HAL_GPIO_WritePin(
		lcd_tbl[ch].lcd_pin.en.port,
		lcd_tbl[ch].lcd_pin.en.pin_num,
		GPIO_PIN_SET);

	HAL_GPIO_WritePin(
		lcd_tbl[ch].lcd_pin.en.port,
		lcd_tbl[ch].lcd_pin.en.pin_num,
		GPIO_PIN_RESET);
}

/*
 * When the power is turned on,
 * 8-bit operation is automatically selected and
 * the first write is performed as an 8-bit operation.
 * so, it must be init for 4-bit operation
 * 4-bit operation init sequence function
*/
static void write_upper_nibble(uint8_t ch, uint8_t instruction){
	uint8_t upper_nibble = instruction >> 4;

	for(int i=0; i<4; i++){
		HAL_GPIO_WritePin(
			lcd_tbl[ch].lcd_pin.db[i].port,
			lcd_tbl[ch].lcd_pin.db[i].pin_num,
			(upper_nibble>>i) & 0x01);
		}
	enable_pulse(ch);
}

static void lcd_instruction(uint8_t ch, uint8_t instruction){
	uint8_t upper_nibble = instruction >> 4;
	uint8_t lower_nibble = instruction & ~(0xF0);

	for(int i=0; i<4; i++){
		HAL_GPIO_WritePin(
				lcd_tbl[ch].lcd_pin.db[i].port,
			lcd_tbl[ch].lcd_pin.db[i].pin_num,
			(upper_nibble>>i) & 0x01);
	}

	enable_pulse(ch);

	for(int i=0; i<4; i++){
		HAL_GPIO_WritePin(
			lcd_tbl[ch].lcd_pin.db[i].port,
			lcd_tbl[ch].lcd_pin.db[i].pin_num,
			(lower_nibble>>i) & 0x01);
	}

	enable_pulse(ch);
}

// GPIO PIN Mapping
static void lcd_init(uint8_t ch){

	// db[0]~[4] = DB4~DB7

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

	lcd_bit_reset(ch);

	lcd_tbl[ch].row = 0;
	lcd_tbl[ch].col = 0;
	lcd_tbl[ch].lcd_onoff = false;

}



bool lcd_begin(uint8_t ch)
{
	if (ch >= MAX_LCD)return false;
	lcd_init(ch);
	// 4-bit operation initializations
#ifdef MY_RTOS
	// wait for more than 15ms after Vcc rises to 4.5V
	vTaskDelay(pdMS_TO_TICKS(20));

	write_upper_nibble(ch,Function_set + 0x10);
	//Wait for more than 4.1 ms
	vTaskDelay(pdMS_TO_TICKS(10));

	write_upper_nibble(ch,Function_set + 0x10);
	//Wait for more than 100 µs
	vTaskDelay(pdMS_TO_TICKS(1));

	write_upper_nibble(ch,Function_set + 0x10);
	Delay_us(50);

	write_upper_nibble(ch,Function_set);
	Delay_us(50);

	lcd_instruction(ch,Function_set + 0x08); // 2line_display
	Delay_us(50);

	lcd_instruction(ch,Display_off);
	Delay_us(50);

	lcd_instruction(ch,Display_clear);
	vTaskDelay(pdMS_TO_TICKS(3));

	lcd_instruction(ch,Entry_mode_set);
	Delay_us(50);

	lcd_instruction(ch,Display_on);
	Delay_us(50);

	return true;
#endif //MY_RTOS

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


