/*
 * ap_lcd.c
 *
 *  Created on: Aug 4, 2026
 *      Author: PC
 */


#include "ap_lcd.h"
#include "smart_blind.h"

static char blind_buf[MAX_LCD][20] = {{""}};
static char stopwatch_buf[MAX_LCD][20] = {{""}};

bool lcd_unpacking_msg(uint8_t ch,const LcdMessage_TypeDef* msg){
	if(msg == NULL)return false;
	if(ch >= MAX_LCD)return false;

	switch (msg->target) {
		case TARGET_NONE:
			return false;
			break;
// lcd msg가 stopwatch에 의존하지 않게 하기 위해 time value를 송신측에서 병렬화 한 후 수신받는다.
		case TARGET_STOPWATCH:
			sprintf(stopwatch_buf[ch],
					"%lu:%lu:%lu",
					(msg->value >> 16) & (0xFF),
					(msg->value >> 8) & (0xFF),
					msg->value & (0xFF));

			break;
		case TARGET_SMARTBLIND:
			switch(msg->state){
				case BLIND_NONE:
					sprintf(blind_buf[ch],"BLIND NONE");
					break;
				case BLIND_OPEN:
					sprintf(blind_buf[ch],"BLIND OPEN");
					break;
				case BLIND_HALF:
					sprintf(blind_buf[ch],"BLIND HALF");
					break;
				case BLIND_CLOSE:
					sprintf(blind_buf[ch],"BLIND CLOSE");
					break;
			}
			break;
		default:
			return false;
			break;
	}
	return true;
}

bool lcd_update(uint8_t ch){
	if(ch >= MAX_LCD)return false;

	lcd_set_cursor(ch, 0, 0);
	lcd_write_str(ch, blind_buf[ch]);
	lcd_write_str(ch, "              ");

	lcd_set_cursor(ch, 1, 0);
	lcd_write_str(ch, stopwatch_buf[ch]);
	lcd_write_str(ch, "              ");

	return true;

}


