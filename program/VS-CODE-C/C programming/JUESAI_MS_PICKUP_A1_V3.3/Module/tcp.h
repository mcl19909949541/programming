#ifndef __TCP_H
#define __TCP_H

#include "main.h"
#include "usart.h"
#include "gpio.h"
#include "tim.h"
#include "module_arm.h"

typedef enum
{
	TCP_START,
	TCP_HEADR1,
	TCP_HEADR2,
	TCP_ID,
	TCP_LEN,
	TCP_DATAS,
	TCP_SUM,
}TCP_REV_STA;

extern uint8_t tcp_send_datas_sensorState[6];
extern uint8_t tcp_rev_buf[1];
extern uint8_t tcp_rev_datas[10];

void tcp_init(void);
void tcp_datas_handler(void);
void tcp_send_setting(void);
uint8_t TCPRevDataHandler(uint8_t rdata);
void TCPRevDatasHandler(uint8_t *rdatas);


#endif
