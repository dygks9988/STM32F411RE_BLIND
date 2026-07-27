/*
 * Uart_Cmd_task.c
 *
 *  Created on: Jun 30, 2026
 *      Author: PC
 */
#include "rtos_task.h"
#include "uart_cmd.h"

/**
 * @brief   UART의 ISR로부터 데이터를 수신하면, uart_cmd_process를 호출하고,명령이 생성되었으면 지정된 타깃으로 명령을 송신한다.
 * @details   루프가 명령을 수신받을 때까지 Blocking 된다.
 * @return NONE
 */

void uart_cmd_task(){
	Uart_Cmd_type huart_cmd;
	uint8_t uart_rx_data;
	Servo_Cmd_PacketTypeDef pservo;



	for (;;){
		if(xQueueReceive(UartRxQueueHandle, &uart_rx_data, portMAX_DELAY)==pdPASS)
		{
			if(uart_cmd_process(uart_rx_data, &huart_cmd))
			{
				switch(huart_cmd.target_ch)
					{
					case NONE_CMD_CH:
						break;
					case SW_CMD_CH:
						xQueueSend(SW_Cmd_QueueHandle,&huart_cmd.cmd,(TickType_t )10);
						huart_cmd.target_ch = NONE_CMD_CH;
						break;
					case SERVO_CMD_CH:
						pservo.servo_cmd = huart_cmd.cmd;
						pservo.servo_cmd_angle = huart_cmd.value;
						xQueueSend(Servo_Cmd_QueueHandle,&pservo,(TickType_t )10);
						huart_cmd.target_ch = NONE_CMD_CH;
						break;
					case BLIND_CMD_CH:
						xQueueSend(SmartBlind_Cmd_QueueHandle,&huart_cmd.cmd,(TickType_t )10);
						huart_cmd.target_ch = NONE_CMD_CH;
					}
			}
		}
	}
}
