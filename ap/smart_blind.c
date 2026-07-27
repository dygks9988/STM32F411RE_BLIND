/*
 * smart_blind.c
 *
 *  Created on: Jul 16, 2026
 *      Author: PC
 */

#include "smart_blind.h"

#define BLIND_OPEN_ANGLE  0
#define BLIND_HALF_ANGLE  45
#define BLIND_CLOSE_ANGLE 90



void blind_init(Blind_StateTypeDef* blind_state){
	if(blind_state == NULL)return;
	*blind_state = BLIND_NONE;
}

/**
 * @brief    블라인드 명령을 처리하고 명령에 따라 상태를 수정한다.
 * @param[in,out]   blind_state      현재 블라인드의 상태.
 * @param[in]      blind_cmd      처리 할 블라인드 명령.
 * @param[out]      pservo_cmd        서보모터로 전송할 통신 패킷.
 * @retval true    상태가 수정되어 서보모터로 송신할 명령 생성됨.
 * @retval false   수신한 명령이 유효하지 않거나 현재 상태와 동일한 명령이 수신 되어 상태가 수정되지 않음
 */

bool blind_process(
Blind_StateTypeDef* blind_state,
Blind_CmdTypeDef blind_cmd,
Servo_Cmd_PacketTypeDef* pservo_cmd
){
	if(blind_state == NULL || pservo_cmd == NULL)return false;

	switch (blind_cmd) {
		case BLIND_CMD_NONE:
			return false;
	    case BLIND_CMD_OPEN:
	        if (*blind_state == BLIND_OPEN)return false;

	        pservo_cmd->servo_cmd = SERVO_CMD_SET_ANGLE;
	        pservo_cmd->servo_cmd_angle = BLIND_OPEN_ANGLE;
	        *blind_state = BLIND_OPEN;
	        return true;

	    case BLIND_CMD_HALF:
	        if (*blind_state == BLIND_HALF)return false;

	        pservo_cmd->servo_cmd = SERVO_CMD_SET_ANGLE;
	        pservo_cmd->servo_cmd_angle = BLIND_HALF_ANGLE;
	        *blind_state = BLIND_HALF;
	        return true;

	    case BLIND_CMD_CLOSE:
	        if (*blind_state == BLIND_CLOSE)return false;

	        pservo_cmd->servo_cmd = SERVO_CMD_SET_ANGLE;
	        pservo_cmd->servo_cmd_angle = BLIND_CLOSE_ANGLE;
	        *blind_state = BLIND_CLOSE;
	        return true;

	    default:
	        return false;
	    }
}

