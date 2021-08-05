#ifndef __laser_H
#define __laser_H
#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "can.h"
#include "track.h"

//宏定义检测到障碍物的极限数值
#define Barrier_Distance_XY 600
#define Barrier_Distance_Q 350
#define Barrier_Distance 800

typedef enum LASER_BARRIER_QUADRANT
{
    NO_QBARRIER,
    LASER_QUADRANT1_BARRIER,
    LASER_QUADRANT2_BARRIER,
    LASER_QUADRANT3_BARRIER,
    LASER_QUADRANT4_BARRIER,
}LASER_BARRIER_QUADRANT;

typedef enum LASER_BARRIER_XY
{
    NO_XYBARRIER = 1,
    LASER_Xplus_BARRIER,
    LASER_Xminus_BARRIER,
    LASER_Yplus_BARRIER,
    LASER_Yminus_BARRIER,
	PRE_Xplus_BARRIER,
	PRE_Xminus_BARRIER,
	PRE_Yplus_BARRIER,
	PRE_Yminus_BARRIER,
}LASER_BARRIER_XY;

typedef enum LASER_WORK_TYPE
{
    BARRIER_MODE,
    NO_BARRIER_MODE,
}LASER_WORK_TYPE;

typedef struct LASER_SOL_TYPE
{
    //单方位障碍物判断（当前前进方向上障碍物）
    LASER_BARRIER_QUADRANT laser_bar_quard;
    LASER_BARRIER_XY laser_bar_xy;
    //是否处于避障模式
    LASER_WORK_TYPE laser_mode;
    //多方位障碍物数组
    uint8_t barrier_xyq[8];
    //各个方向激光具体数值:X+Y+X-Y-Q1Q2Q3Q4
    uint16_t barrier_dis[8];
}LASER_SOL_TYPE;

typedef struct 
{
    LASER_SOL_TYPE barrier_state;
    uint16_t cur_laser_value[12];
    uint16_t last_laser_value[12];
    uint16_t last_last_laser_value[12];
    uint16_t laser_value[12];
	  uint16_t pwm_laser;
}DEF_LASER_STATE;

/*激光模块结构体*/
extern DEF_LASER_STATE LASER;
/*激光采集函数*/
void  LASER_INSTRUCTION_TX(CAN_HandleTypeDef *hcan,uint8_t id);
/*激光数据采集指令*/
void LASER_TX_UPDATE(void);
/*激光检测到障碍状态更新*/
void LASER_BARRIER_UPDATE(void);

unsigned short CRC_TEST(unsigned char buff[]);
#ifdef __cplusplus
}
#endif
#endif 



