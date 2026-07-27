/*
 * cds.c
 *
 *  Created on: Jul 23, 2026
 *      Author: PC
 */



#include "hw_adc.h"
#include "cds.h"

#define CDS1_ADCID 0
#define CDS_TIMEOUT_MS 1
#define CDS_MAX 1

#define CDS_VAL_DARK 3000
#define CDS_VAL_MIDDLE 1500

#define ADC_READ_TIMES 5

typedef struct{
	uint8_t cds_adc_id;
}Cds_HandleTypeDef;

static Cds_HandleTypeDef cds_tbl[CDS_MAX] = {
		{CDS1_ADCID}
};

/**
 * @brief    수신받은 cds 센서 값을 토대로 현재 상태를 수정한다.
 * @param[in,out]  cds_state 	현재 cds센서의 상태.
 * @param[in]      ch        	사용할 cds 인스턴스 번호.
 * @retval true    cds 센서의 상태가 수정 되었음.
 * @retval false   전달 받은 포인터가 유효하지 않음, adc측정 실패, 상태가 수정되지 않음,수신 받은 센서 값이 현재의 상태와 동일함.
 * @todo       	현재는 상태가 수정되지 않았을 때의 반환 값을 false로 전부 처리하는 구조,로그와 디버깅에 좋지 않은 구조이다.
 * 				enum으로 실패 원인을 세부화 하여 반환 하도록 해서 로그와 디버깅에 유리한 구조로 만들 것.
 */


bool cds_process(CdsState_TypeDef* cds_state,uint8_t ch){
	uint32_t cds_value = 0;
	uint32_t cds_sum_value = 0;
	uint32_t cds_avg_value = 0;


	if(cds_state == NULL || ch >= CDS_MAX)return false;
	for(int i = 0; i < ADC_READ_TIMES; i++){
		if(adc_read_polling(cds_tbl[ch].cds_adc_id,CDS_TIMEOUT_MS,&(cds_value)) == false){
			return false;
		}
		cds_sum_value += cds_value;
	}
	cds_avg_value = cds_sum_value / ADC_READ_TIMES;

	if(cds_avg_value >= CDS_VAL_DARK){
		 if(*cds_state == CDS_DARK)return false;
		*cds_state = CDS_DARK;
		return true;
	}
	else if(cds_avg_value >= CDS_VAL_MIDDLE){
		if(*cds_state == CDS_MIDDLE_LIGHT)return false;
		*cds_state = CDS_MIDDLE_LIGHT;
		return true;
	}
	else if(*cds_state != CDS_LIGHT) {
		*cds_state = CDS_LIGHT;
		return true;
	}
	return false;
}
