/*
 * cds.h
 *
 *  Created on: Jul 23, 2026
 *      Author: PC
 */

#ifndef MODULE_CDS_H_
#define MODULE_CDS_H_

#include "hw_adc.h"

typedef enum{
	CDS_NONE =0,
	CDS_DARK,
	CDS_MIDDLE_LIGHT,
	CDS_LIGHT
}CdsState_TypeDef;

bool cds_process(CdsState_TypeDef* cds_state,uint8_t ch);

#endif /* MODULE_CDS_H_ */
