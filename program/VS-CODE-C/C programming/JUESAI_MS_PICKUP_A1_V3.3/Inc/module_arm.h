#ifndef __MOUDLE_ARM_H
#define __MOUDLE_ARM_H

#include "device_steer.h"
#include "math.h"
#include "tim.h"
#include "openmv.h"
#include "pid.h"
#include "callback.h"


#define ArmL1 21.6
#define ArmL2 25
#define pi 3.14

#define TOUCH_TEST 0
#define TEST_MOUDLE 0//测试赛模式打开

#define PAW_TOUCH_POS 120
#define PAW_RESET_POS 300
//#define S1_MAXANGLE 950
//#define S1_MINANGLE 450
//#define S2_MAXANGLE 900
//#define S2_MINANGLE 750


//#define LeftSide 0  
//#define RightSide 1  
//#define Center  2 
//#define UpSide 3 
//#define DownSide 4 
//#define QR 1 
//#define Block 2
//#define TAGLOCATION 100


typedef struct
{
	uint8_t x,y;
}OBJ_LOCATION;

typedef struct
{
	uint8_t is_threshold_got;//0:空闲 1:红色阈值测量完毕 2:蓝色阈值测定完毕 3:黄色阈值测定完毕
	uint8_t ball_color_got;//openmv采集到的小球颜色，1：红色 2：蓝色 3：黄色 0:未采集到
	uint8_t openmv_scan_switch;//openmv扫描小球的开关
}DEF_OPENMV;

typedef enum
{
	ACTION_START,
	ACTION_1,
	ACTION_2,
	WAIT_COLLECT_BALL,
	ACTION_COLLECT_BALL,
	ACTION_3,
	ACTION_4,
	ACTION_5,
	ACTION_STOP,
	ACTION_READ_THRESHOLD,
	READY
}DEF_ARM_STA;

typedef struct
{
	int16_t up_angle;//货舱收起时的角度
	int16_t down_angle;//货舱放下时的角度
	int16_t collect_angle;//货舱水平时的角度
	int16_t cmd;//0：放平 1：升起 2：放下
}DEF_HOLD;

typedef struct
{
	int16_t pos_x_last,pos_y_last;
	uint8_t speed_measure_enable;
	uint8_t speed_measure_cnt_20ms;
}DEF_ARM_SPEED_MEASURE;

typedef enum
{
	TOUCH_READY,
	TOUCHING,
	TOUCH_RESET
}DEF_TOUCH_STA;//改状态机表现的是爪子拨球的流程

typedef struct
{
	uint8_t touch_target_switch;
	uint8_t target_color;//目标。1：红色，2：蓝色，3：黄色
	uint8_t is_arm_got_target;
	uint8_t collected_ball_cnt[3];
	uint8_t touch_enable;
	DEF_TOUCH_STA touch_state;
	uint8_t touch_wait_time;//拨球的超时时间，如果一定时间内目标不出现，则进行下一步
	uint8_t touch_touching_cnt,touch_reseting_cnt;
	uint8_t target_cnt[3];
}DEF_TARGET;

typedef struct
{
	//4个机械臂体上的舵机， 1个底盘 一个爪子，一个货仓
	SERVO_HandleTypeDef servo1,servo2,servo3,servo4,servo5,servo6,servo7;
	DEF_OPENMV openmv;
	DEF_HOLD hold;
	DEF_ARM_SPEED_MEASURE speed_measure;
	double targetPos_x,targetPos_y;
	DEF_ARM_STA state;
	DEF_TARGET target;
	uint8_t times_cnt;
	uint8_t arm_base_ctrl_enable;
	uint8_t is_test_ball_got;//测试模式是否得到一个球
}DEF_ARM;

extern DEF_ARM arm;
extern	uint8_t openmv_revi[1];
void Duoji_Init();
void waiting_fetch_ball();
void waiting_fetch_cube();
void waiting_fetch_qr();
void Duoji_angle(uint8_t ID,uint16_t angle, int speed);
void tcp_feedback(DEF_ARM* arm);
void SERVOTEST (int16_t SetSpeed);
void ArmInit(DEF_ARM *arm);
void Arm(void);
void ServoFeedBack(uint8_t *RxDatas);
void Platform_Init(void);
void PlatformControl(uint8_t mode, uint16_t pwmcount1, uint16_t pwmcount2);
void TouchMonitor(DEF_ARM *arm);
void TouchTest(uint8_t cmd);
void finish_fetch(uint8_t color);
uint8_t ServoSpeedMeasure(SERVO_HandleTypeDef* servo);
uint8_t adjustlaser(uint8_t color);
void ArmDriver(DEF_ARM *arm);
void ArmBaseCtrl(int16_t angle);



#endif
