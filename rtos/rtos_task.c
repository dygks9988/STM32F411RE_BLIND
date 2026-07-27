/*
 * rtos_task.c
 *
 *  Created on: Jun 30, 2026
 *      Author: PC
 */

#include "rtos_task.h"
#include "main.h"
#include "servo_motor.h"

#define UART_RX_QUEUE_LENGTH  30
#define SW_CMD_QUEUE_LENGTH 30
#define SERVO_CMD_QUEUE_LENGTH 30
#define SMART_BLIND_CMD_QUEUE_LENGTH 30

QueueHandle_t UartRxQueueHandle;
QueueHandle_t SW_Cmd_QueueHandle;
QueueHandle_t Servo_Cmd_QueueHandle;
QueueHandle_t SmartBlind_Cmd_QueueHandle;

void rtos_init(void)
{
	UartRxQueueHandle = xQueueCreate(UART_RX_QUEUE_LENGTH,sizeof(uint8_t));
	if(UartRxQueueHandle == NULL){
		Error_Handler();
	}
	SW_Cmd_QueueHandle = xQueueCreate(SW_CMD_QUEUE_LENGTH,sizeof(uint8_t));
	if(SW_Cmd_QueueHandle == NULL){
		Error_Handler();
	}

	Servo_Cmd_QueueHandle = xQueueCreate(SERVO_CMD_QUEUE_LENGTH,sizeof(struct Servo_Cmd_PacketTypeDef *));
	if(SW_Cmd_QueueHandle == NULL){
		Error_Handler();
	}
	SmartBlind_Cmd_QueueHandle = xQueueCreate(SMART_BLIND_CMD_QUEUE_LENGTH,sizeof(uint8_t));
	if(SmartBlind_Cmd_QueueHandle == NULL){
		Error_Handler();
	}
}
