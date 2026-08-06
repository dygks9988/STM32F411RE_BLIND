/*
 * sensor_task.c
 *
 *  Created on: Jul 27, 2026
 *      Author: PC
 */

#include "cds.h"
#include "smart_blind.h"
#include "rtos_task.h"

/**
 * @brief  	cds_process호출,센서의 상태가 수정 되면 상태 확인 후 blind_cmd 생성 및 전송
 * @details	루프의 로직의 실행 시간 + 100ms loop blocking.
 * @return NONE
 */
void sensor_task(void){
	static CdsState_TypeDef cds_state = CDS_NONE;

	for(;;){
		if(cds_process(&cds_state,0)){
			Blind_CmdTypeDef blind_cmd = BLIND_CMD_NONE;
			switch(cds_state){
			case CDS_NONE:
				break;
			case CDS_DARK:
				blind_cmd = BLIND_CMD_OPEN;
				break;
			case CDS_MIDDLE_LIGHT:
				blind_cmd = BLIND_CMD_HALF;
				break;
			case CDS_LIGHT:
				blind_cmd = BLIND_CMD_CLOSE;
				break;
			default:
				break;
			}
			xQueueSend(SmartBlind_Cmd_QueueHandle,&blind_cmd,pdMS_TO_TICKS(5));
		}
		vTaskDelay((TickType_t)100);
	}

}
