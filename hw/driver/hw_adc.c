/*
 * hw_adc.c
 *
 *  Created on: Jul 22, 2026
 *      Author: PC
 */

#define ADC_MAX 1
#include "adc.h"




static ADC_HandleTypeDef* adcs[ADC_MAX] = {
	&hadc1
};


/*
 * adc_read_polling
 * adc의 다중 채널을 제대로 사용하지 못하는 로직.
 * 조도 센서 하나만을 읽기위해 제작.
 * 다중채널로 할당을 받을 경우는 DMA나 인터럽트 방식을 이용하여 다시 정리한다.
 * 반환 상태를 enum으로 정리하면 디버깅과 예외처리를 할 때 강점이 있을 것.
 */


bool adc_read_polling(uint8_t adc_id,uint32_t timeout_ms,uint32_t* adc_value){
	if(adc_id >= ADC_MAX || adc_value == NULL)return false;

	if(HAL_ADC_Start(adcs[adc_id])!= HAL_OK)return false;

	if(HAL_ADC_PollForConversion(adcs[adc_id], timeout_ms) == HAL_OK){
		*adc_value = HAL_ADC_GetValue(adcs[adc_id]);
	}
	else return false;

	if(HAL_ADC_Stop(adcs[adc_id])!= HAL_OK)return false;

	return true;
}
