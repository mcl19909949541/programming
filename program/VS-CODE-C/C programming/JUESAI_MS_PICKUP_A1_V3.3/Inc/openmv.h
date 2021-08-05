#ifndef __OPENMV_H
#define __OPENMV_H

#include "stm32f4xx_hal.h"
#include "usart.h"



typedef enum
{
	OPENMV_START,
	OPENMV_HEADR1,
	OPENMV_HEADR2,
	OPENMV_ID,
	OPENMV_LEN,
	OPENMV_DATAS,
	OPENMV_SUM
}OPENMV_REV_STA;



extern uint8_t openmv_rev_buf[1];
extern uint8_t openmv_rev_datas[6];

void OpenmvInit(void);
void OpenmvScanBallStartStop(uint8_t _switch);
void OpenmvThresholdMeasure(uint8_t color_select);
void OpenmvRevDatasHandler(uint8_t *rdatas);
uint8_t OpenmvRevDataHandler(uint8_t rdata);	


#endif
