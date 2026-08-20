/*
 * smart_blind.h
 *
 *  Created on: Jul 16, 2026
 *      Author: PC
 */

/*
 * servo_motor.h
 *
 *  Created on: Jul 10, 2026
 *      Author: PC
 */

#ifndef SMART_BLIND_H_
#define SMART_BLIND_H_
#include "servo_motor.h"



typedef enum{
	BLIND_NONE = 0,
	BLIND_OPEN,
	BLIND_HALF,
	BLIND_CLOSE
}Blind_StateTypeDef;

typedef enum{
	BLIND_CMD_NONE =0,
	BLIND_CMD_OPEN,
	BLIND_CMD_HALF,
	BLIND_CMD_CLOSE,
}Blind_CmdTypeDef;

void blind_init(Blind_StateTypeDef* blind_state);

bool blind_process(
Blind_StateTypeDef* blind_state,
Blind_CmdTypeDef blind_cmd,
Servo_Cmd_PacketTypeDef* pservo_cmd
);



#endif /* SMART_BLIND_H_ */
