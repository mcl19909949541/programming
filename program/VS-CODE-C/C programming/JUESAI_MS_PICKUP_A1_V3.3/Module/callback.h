#ifndef _CALLBACK_H
#define _CALLBACK_H
//包含所需要的板载资源头文件
#include "main.h"
#include "can.h"
#include "tim.h"
#include "usart.h"
#include "digital_gray16.h"
#include "laser.h"
#include "track.h"
#include "led.h"
#include "oled.h"
#include "openmv.h"
#include "tcp.h"

//回调函数统一在这里，方便查看和修改

/*灰度值接收结构体*/
typedef struct 
{
    uint8_t usart2_gray1[2] ;
    uint8_t usart6_gray2[2] ;
    uint8_t uart7_gray3[2] ;
    uint8_t uart8_gray4[2] ;
}UART_GRAY;

/*TIM2延时单位结构体*/
typedef struct 
{
    uint16_t led_delay;
		uint8_t oled_delay;
}TIM2_DELAY;
/*TIM3底盘任务调度单位结构体*/
typedef struct 
{
    //避障信息更新
    uint8_t barrier;
    //速度信息更新
    uint8_t chassic;
    //转动角度时间
    uint16_t angle;
    //前进里程步数
    uint16_t step;
}TIM3_MODULE_UPDATE;
/*TIM4传感器任务调度单位结构体*/
typedef struct 
{
    uint8_t gray;
    uint8_t pos;
    uint8_t laser;
}TIM4_SENSOR_UPDATE;

typedef struct
{
	int16_t qIN;
	int16_t qOUT;
  uint16_t MaxNum;
	uint16_t CurNum;
	uint8_t *qBuf;
	uint8_t *End;
	unsigned char qFull;
}_tBLECOM_QUEUE;

extern UART_GRAY uart_gray;
extern TIM2_DELAY T2_delay;
extern TIM3_MODULE_UPDATE T3_module_update;
extern TIM4_SENSOR_UPDATE T4_sensor_update;
extern uint16_t ArmPidCnt;
extern uint16_t PWMcount1;
extern uint16_t PWMcount2;
extern uint16_t armflag2;
extern uint16_t adjustflag;
extern uint8_t LASER_RX[1];
extern uint8_t LASER_TX[8];
extern uint8_t LASER_RX_TRUE[7];

extern uint16_t TaskCnt_20ms;
extern uint16_t TaskCnt_1s;
extern uint8_t HeartBeat;//心跳计数变量，每1s记一次数
extern uint8_t IsConnectedFlag;//表示tcp连接是否正常的标志位，1表示正常，2表示断开

void Ble_init_quene(_tBLECOM_QUEUE *q,void *Buf,uint16_t BufSize);
	
#endif


