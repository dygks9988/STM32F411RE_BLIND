/*
 * stopwatch.c
 *
 *  Created on: Jun 16, 2026
 *      Author: PC
 */

#include "stopwatch.h"

#define SEC_PER_TEN_MS 100
#define MIN_PER_SEC 60
#define HOUR_PER_MIN 60


typedef struct{
	SW_STATE state;
	uint8_t ten_ms_cnt;
	uint8_t sec_cnt;
	uint8_t min_cnt;
	uint8_t hour_cnt;
}stop_status;

stop_status sw;
static Sw_Cmd_Type_t sw_cmd;

void stopwatch_init(void){
	sw_cmd = SW_NONE;
	ten_ms_flag = 0;
	sw.state = IDLE;
	sw.ten_ms_cnt = 0;
	sw.sec_cnt = 0;
	sw.min_cnt = 0;
	sw.hour_cnt = 0;
}
void stopwatch_start(void){
	hw_TIM_start(SW_TIM_CH);
	sw.state = RUNNING;
}
void stopwatch_pause(void){
	hw_TIM_stop(SW_TIM_CH);
	sw.state = PAUSE;
}
void stopwatch_stop(void){
	hw_TIM_stop(SW_TIM_CH);
	stopwatch_init();
	sw.state = IDLE;
}
void stopwatch_set_cmd(Sw_Cmd_Type_t cmd){
	sw_cmd = cmd;
}


void stopwatch_update(void){
	sw.ten_ms_cnt++;
	if(sw.ten_ms_cnt >= SEC_PER_TEN_MS){
		sw.ten_ms_cnt = 0;
		sw.sec_cnt++;
		led_toggle(LED_CH_0);
		if(sw.sec_cnt >= MIN_PER_SEC){
			sw.sec_cnt = 0;
			sw.min_cnt++;
			if(sw.min_cnt >= HOUR_PER_MIN){
				sw.min_cnt = 0;
				sw.hour_cnt++;
			}
		}
	}

}
/**
 * @brief   스톱워치 명령을 처리하고 명령에 따라 상태를 수정한다.
 * @details   루프에서 주기적으로 호출 되어야 하며, TIM_ISR에서 세운 ten_ms_flag의 상태가 변화 되었다면 stopwatch_update를 호출한다.
 * @note   TIM의 ISR 호출 주기가 10ms 이므로 루프의 함수 호출 주기를 10ms이내로 설정해야 한다.
 */

void stopwatch_process(void){
		switch(sw.state){
		case IDLE:
			if(sw_cmd == SW_START){
				stopwatch_start();
				sw_cmd = SW_NONE;
			}
			break;
		case RUNNING:
			if(sw_cmd == SW_PAUSE){
				stopwatch_pause();
				sw_cmd = SW_NONE;
			}
			if(ten_ms_flag != 0){
				stopwatch_update();
				ten_ms_flag = 0;
			}
			break;
		case PAUSE:
			if(sw_cmd == SW_STOP){
				stopwatch_stop();
				sw_cmd = SW_NONE;
			}
			if(sw_cmd == SW_START){
				stopwatch_start();
				sw_cmd = SW_NONE;
			}
			break;
	}
	//if(sw_cmd == SW_GET_TIME)

}


