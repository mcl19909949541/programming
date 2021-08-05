#ifndef __DIGITAL_GRAY16_H
#define __DIGITAL_GRAY16_H
#ifdef __cplusplus
 extern "C" {
#endif

#include "main.h"
#include "usart.h"
#include <stdio.h>
#include<stdlib.h>
#include <math.h>	

//得到灰度的命令
#define GET_GRAY_COMAND 0x57

//16路灰度设备特征结构体
typedef struct
{
	union 
	{
		//16路灰度的串口值
		uint16_t value;
		struct
		{
			//传感器向下，且传感器突出部分向前，此时从右向左数据位递增 序号依次为1 2 3...8
			uint8_t L1 : 1;
			
			uint8_t L2 : 1;
			
			uint8_t L3 : 1;
	
			uint8_t L4 : 1;
			
			uint8_t L5 : 1;
			
			uint8_t L6 : 1;
			
			uint8_t L7 : 1;
			
			uint8_t L8 : 1;
						
			uint8_t L9 : 1;
			
			uint8_t L10 : 1;
			
			uint8_t L11 : 1;
			
			uint8_t L12 : 1;
			
			uint8_t L13 : 1;
			
			uint8_t L14 : 1;
			
			uint8_t L15 : 1;
			
			uint8_t L16 : 1;
		}STATE;
	}digital16_gray_state;
	//上一次的灰度值
	union 
	{
		//16路灰度的上一次
		uint16_t last_value;
		struct
		{
			//传感器向下，且传感器突出部分向前，此时从右向左数据位递增 序号依次为1 2 3...8
			uint8_t L1 : 1;
			
			uint8_t L2 : 1;
			
			uint8_t L3 : 1;

			uint8_t L4 : 1;
			
			uint8_t L5 : 1;
			
			uint8_t L6 : 1;
			
			uint8_t L7 : 1;
			
			uint8_t L8 : 1;
						
			uint8_t L9 : 1;
			
			uint8_t L10 : 1;
			
			uint8_t L11 : 1;
			
			uint8_t L12 : 1;
			
			uint8_t L13 : 1;
			
			uint8_t L14 : 1;
			
			uint8_t L15 : 1;
			
			uint8_t L16 : 1;
		}LAST_STATE;
	}digital16_gray_laststate;
	uint8_t sum_gray[16];
	//设备ID
	uint8_t id;
}DEF_16DIGITAL_GRAY;


//16路灰度位置偏离信息结构体类型
typedef struct DEF_GRAY_DIR
{
	//中心垂直于前进直线的距离（有符号）
	//X方向上的
	float X_DIR_DISTANCE;
	//Y方向上的
	float Y_DIR_DISTANCE;
	//当前方向偏离坐标轴角度（有符号）
	//X轴上
	float X_DIR_ANGLE;
	//Y轴上
	float Y_DIR_ANGLE;
}DEF_GRAY_DIR;


extern DEF_16DIGITAL_GRAY DIGITAL16_GRAY_1;
extern DEF_16DIGITAL_GRAY DIGITAL16_GRAY_2;
extern DEF_16DIGITAL_GRAY DIGITAL16_GRAY_3;
extern DEF_16DIGITAL_GRAY DIGITAL16_GRAY_4;
extern DEF_GRAY_DIR GRAY_DIR;


//16路灰度数据初始化
void  DIGITAL16_Init(void);
/*灰度状态和计数操作函数*/
uint8_t GRAY_UPDATE_state(void);
void Reset_Gray_Cnt(void);
void DIGITAL_GRAY_ANALYSIS(uint16_t data,uint8_t id);
/*灰度功能函数*/
uint8_t GRAYx_FUNC_Linecount(DEF_16DIGITAL_GRAY Gray_BUFF);
float GRAYx_FUNC_POS(DEF_16DIGITAL_GRAY Gray_BUFF);
/*灰度位置调整值更新*/
void GRAY_FUNC_DIR_UPDATE(void);
	 
#ifdef __cplusplus
}
#endif
#endif 


