/*
 * stopwatch.h
 *
 *  Created on: Jun 16, 2026
 *      Author: PC
 */

#ifndef STOPWATCH_H_
#define STOPWATCH_H_

#include "hw.h"


typedef enum{
	SW_START = 0,
	SW_PAUSE,
	SW_STOP,
	SW_GET_TIME,
	SW_NONE
}Sw_Cmd_Type_t;


typedef enum{
	IDLE = 0,
	RUNNING,
	PAUSE
}SW_STATE;

void stopwatch_init(void);
void stopwatch_start(void);
void stopwatch_stop(void);
void stopwatch_pause(void);
void stopwatch_process(void);
void stopwatch_set_cmd(uint8_t cmd);
void get_stopwatch_snapshot(uint8_t* pstate,uint32_t* ptime);

#endif /* STOPWATCH_H_ */
