#ifndef __TRACK_H
#define __TRACK_H
#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "can.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "digital_gray16.h"
#include "module_arm.h"
	 
	 
	 
/*定义车坐标模式*/
typedef enum CAR_COR_MODE
{
    //无坐标模式
	NO_COR_MODE,
	//有坐标模式
	COR_UPDATE_MODE,
}CAR_COR_MODE;

/*定义车位置调整模式*/
typedef enum CAR_DIR_MODE
{
    //无调整模式
	NO_DIR_MODE,
	//行进中调整模式
	DIR_RUN_MODE,
	//静止中调整模式
	DIR_SILENCE_MODE,
}CAR_DIR_MODE;

/*定义车当前相对于线的位置*/
typedef enum CAR_POS
{
    //不在任何线和点上
    OUT,
    //在中心点上
    CENTER,
    //在沿X方向的线上
    ON_X,
    //在沿Y轴的线上
    ON_Y,
    //在X+边沿的中心上
    Xplus_CENTER,
    //在X+边沿的中心上
    Xminus_CENTER,
    //在X+边沿的中心上
    Yplus_CENTER,
    //在X+边沿的中心上
    Yminus_CENTER,
    //在左上角
    Q1_CENTER,
	  //在右上角
    Q2_CENTER,
    //左下角
    Q3_CENTER,
    //右下角
    Q4_CENTER,
}CAR_POS;

/*定义车速*/
typedef struct CAR_V
{
    //X方向上的速度
    int16_t VX;
    //Y方向上的速度
    int16_t VY;
    //W方向上的速度（顺时针为正）
    int8_t VW;
    //合速度大小
    uint16_t Vmagnitude;
    //和速度方向（合速度与X正轴方向夹角）
    float angle;
    //调整完成标志位
    uint8_t ok;
    //精密调整完成标志位
    uint8_t p_ok;
}CAR_V;


/*定义车的方向*/
typedef enum CAR_DIR
{
    //静止无方向
    NO_DIR,
    //X+方向
    Xplus_DIR,
    //Y+方向
    Yplus_DIR,
    //X-方向
    Xminus_DIR,
    //Y-方向
    Yminus_DIR,
    // //第一象限方向
    // Q1_DIR,
    // //第一象限方向
    // Q2_DIR,
    // //第一象限方向
    // Q3_DIR,
    // //第一象限方向
    // Q4_DIR,
}CAR_DIR;

/*定义车坐标*/
typedef struct CAR_COR
{
    int8_t X_COR;
    int8_t Y_COR;
}CAR_COR;

/*定义是否抵达坐标点*/
typedef enum CAR_ARRIVE
{
	NO_ARRIVE,
	ARRIVED,
}CAR_ARRIVE;

/*循迹总结构体*/
typedef struct DEF_CAR
{
    //循迹所处的模式
    CAR_COR_MODE COR_MODE;
    CAR_DIR_MODE DIR_MODE;
    //循迹指定速度
    CAR_V V;
    //循迹自动调整速度
    CAR_V V_ADJUST; 
	  //电机反馈的车实际速度
	  CAR_V CUR_V;
    //循迹当前方向
    CAR_DIR DIR;
	  //循迹上一个方向
	  CAR_DIR LAST_DIR;
    //循迹当前所处的位置
    CAR_POS CUR_POS;
    //循迹上一次所处的位置
    CAR_POS LAST_POS;
    //循迹当前坐标
    CAR_COR CUR_COR;
    //循迹上一次坐标点
    CAR_COR LAST_COR;
}DEF_CAR;

/*坐标更新所需计数值存储结构体*/
typedef struct COR_GRAY
{
    /*当前计数值*/
    uint8_t pos_xplus;
    uint8_t pos_xminus;
    uint8_t pos_yplus;
    uint8_t pos_yminus;
    /*上次计数值*/
    uint8_t last_pos_xplus;
    uint8_t last_pos_xminus;
    uint8_t last_pos_yplus;
    uint8_t last_pos_yminus;
}COR_GRAY;

/*循迹控制结构体*/
/*循迹状态结构体*/
typedef enum DEF_TRACK_STATE
{
    START,
	
    TRACK_GO_FETCH,
		TRACK_GO_FETCH_2,
		TRACK_GO_FETCH_2_1,
    TRACK_GO_FETCH_2_2,
    TRACK_GO_FETCH_3,
	  TRACK_GO_FETCH_3_2,
		TRACK_GO_FETCH_3_1,
	 TRACK_GO_FETCH_4,
	   TRACK_GO_FETCH_4_1,
    TRACK_GO_FETCH_4_2,
	TRACK_GO_FETCH_BALL,
	WAITING_FUCK_BRIKE,
	WAITING_FUCK_BRIKE_2,
	WAITING_FUCK_BRIKE_3,
	WAITING_FUCK_BALL_RED,
	WAITING_FUCK_BALL_BLUE,
	WAITING_FUCK_BALL_YELLOW,
	WAITING_FUCK_BRIKE_QR,
	TRACK_GO_FETCH_BALL_2,
	TRACK_GO_FETCH_BALL_1,
	TRACK_GO_FETCH_BRICK,
	TRACK_GO_FETCH_BRICK_2,
	TRACK_GO_FETCH_BRICK_3,
	TRACK_GO_FETCH_BRICK_4,
	TRACK_GO_FETCH_BRICK_5,
	TRACK_GO_FETCH_BRICK_6,
	TRACK_GO_FETCH_BRICK_7,
	TRACK_GO_FETCH_BRICK_YELLOWBALL,
	TRACK_GO_FETCH_BRICK_YELLOWBALL_2,
	TRACK_GO_FETCH_BRICK_YELLOWBALL_3,
	TRACK_GO_FETCH_BRICK_YELLOWBALL_4,
	TRACK_GO_FETCH_BALL_RED,
	TRACK_GO_FETCH_BALL_RED_2,
	TRACK_GO_FETCH_BALL_RED_3,
	TRACK_GO_FETCH_BALL_BLUE,
	TRACK_GO_FETCH_BALL_BLUE_2,
	TRACK_GO_FETCH_BALL_BLUE_3,
	TRACK_GO_FETCH_BALL_YELLOW,
	TRACK_GO_FETCH_BALL_YELLOW_2,
	TRACK_GO_FETCH_BALL_YELLOW_3,
	TRACK_GO_FETCH_BRICK_QR,
	TRACK_GO_FETCH_BRICK_QR_2,
	TRACK_GO_FETCH_BRICK_QR_3,
	TRACK_GO_FETCH_BRICK_QR_4,
	
		TURE_TO_FETCH,     //蓝色方180度旋转后抓取
	TURE_TO_FETCH_2,
	  TURE_TO_FETCH_3,
	  TURE_TO_FETCH_4,
		
	  TRACK_FETCH_BALL_RED,
		TRACK_FETCH_BALL_BLUE,
		TRACK_FETCH_BALL_YELLOW,
	  TRACK_FETCH,
    TRACK_FETCH_BALL,
		TRACK_FETCH_BRICK,
		TRACK_FETCH_BRICK_2,
		TRACK_FETCH_BRICK_3,
		TRACK_FETCH_BRICK_QR,
	TRACK_FETCH_2,
		TRACK_FETCH_3,
	TRACK_FETCH_4,
	

    TRACK_WAIT_FETCH,
		TRACK_WAIT_FETCH_2,
	  TRACK_WAIT_FETCH_3,
		TRACK_WAIT_FETCH_4,
    
		FETCH_BRICK_OVER_BACK_ONLINE,
		FETCH_BRICK_OVER_BACK_ONLINE_2,
		FETCH_BRICK_OVER_BACK_ONLINE_3,
		FETCH_BRICK_OVER,
		FETCH_QR_OVER_BACK_ONLINE,
		FETCH_BALL_OVER,
		FETCH_BALL_OVER_RED,
		FETCH_BALL_OVER_BLUE,
		FETCH_BALL_OVER_BLUE_2,
		FETCH_BALL_OVER_YELLOW,
    FETCH_OVER,
		FETCH_OVER_1,
		FETCH_OVER_2,
	FETCH_OVER_3,
	FETCH_OVER_4,
	
		TURE_TO_PUT,			//蓝色方180 度转回
		TURE_TO_PUT_2,
		TURE_TO_PUT_3,
			TURE_TO_PUT_4,
	
	  BEFORE_THROUGH,
		BEFORE_THROUGH_2,
		BEFORE_THROUGH_3,
		BEFORE_THROUGH_4,
		
		THROUGH,
		THROUGH_2,
		THROUGH_3,
		THROUGH_4,
		
		
    GO_PUT,
		GO_PUT_2,
		GO_PUT_3,
		GO_PUT_4,
		
	  TURE_TO_THE_BUSCKET,
		TURE_TO_THE_BUSCKET_2,
		TURE_TO_THE_BUSCKET_3,
		TURE_TO_THE_BUSCKET_4,
		
    PUT,
		PUT_2,
		PUT_3,
		PUT_4,

    PUT_BARRIER,
		
		STORE,
		STORE_1,
		STORE_2,
		STORE_RED,
		STORE_BLUE,
		STORE_YELLOW,
		STORE_BRIKE,
		STORE_QR,
		STORE_BRIKE_YELLOWBALL,
		GO_STORE,
		GO_STORE_1,
		GO_STORE_2,
		GO_STORE_RED,
		GO_STORE_BLUE,
		GO_STORE_YELLOW,
		GO_STORE_YELLOW_2,
		GO_STORE_BRIKE,
		GO_STORE_QR,
		GO_STORE_BRIKE_YELLOWBALL,
		GO_STORE_BRIKE_YELLOWBALL_2,
		STORE_OVER_BACK_ONLINE,
		STORE_OVER_BACK_ONLINE_2,
		STORE_OVER_BACK_ONLINE_3,
		STORE_OVER_BACK_ONLINE_4,

		Bizhang,
		Bizhang_1,
		Bizhang_2,
		Bizhang_3,
		Bizhang_4,
		Bizhang_5,
		
    WAIT_PUT_OVER,
		WAIT_PUT_OVER_2,
		WAIT_PUT_OVER_3,
		WAIT_PUT_OVER_4,
		
	  AWAY,
		AWAY_2,
		AWAY_3,
		AWAY_4,
		
	  TURE_BACK,
		TURE_BACK_2,
		TURE_BACK_3,
    TURE_BACK_4,
		

		READY_FOR_BACK,
    BACK,
    BACK_1,
    BACK_2,
		TO_START_POINT,
		FINISH,
		FINISH_2,
}DEF_TRACK_STATE;

/*循迹总结构体*/
typedef struct DEF_TRACK
{
    //循迹ID【0：自由循迹（0，0）1：红方（5，0）2：蓝方（3，0）】
    uint8_t id;
    //抓取颜色【1：红 2：蓝 3：黄】
    uint8_t color;
    //循迹放货模式【0：无模式（等待）1：左边直行放货 2：作业区放货】
    uint8_t put;
    //循迹状态
    DEF_TRACK_STATE STATE;
    //目标方向
    CAR_DIR FINAL_DIR;
    CAR_DIR LAST_FINAL_DIR;
	  //目标速度
	  CAR_V FINAL_V;
    //记录预选方向
    uint8_t maybe_dir[5];
    //方向优先级:第一位表示XY与+-之间的优先级，第二位表示X（0）与Y之间的优先级，第三位表示+（0）与-之间的优先级
    uint8_t prior_dir[5];
    //是否处理完成上一个障碍物的绕道
    uint8_t barrier_ok[4];
	  //遇到障碍物时的方向
  	CAR_DIR BARRIER_DIR;
    //与障碍物坐标
    CAR_COR BARRIER_COR;
    //目标坐标
    CAR_COR FINAL_COR;
    //是否抵达目的地
    CAR_ARRIVE ARRIVE;
		//抓取次数
		uint8_t flag;
}DEF_TRACK;


extern DEF_CAR CAR; 
extern DEF_TRACK TRACK;
extern COR_GRAY POS_GRAY_COUNT;


/*循迹信息更新函数*/
/*运动信息发送函数_CAN1发送ID：0x100*/
void  TRACK_INSTRUCTION_TX(CAN_HandleTypeDef *hcan);
/*运动方向信息更新*/
void TRACK_DIR_UPDATE(void);
/*位置更新函数*/
void TRACK_POS_UPDATE(void);
/*坐标信息更新函数*/
void TRACK_COR_UPDATE(void);
/*位置调整函数*/
void TRACK_POS_ADJUST(void);

/*运动控制模块*/
/*计算最优方向*/
void TRACK_DIR_GO(void);
/*方向转换调整*/
uint8_t TRACK_POS_GO(void);
/*到达目标坐标*/
uint8_t TRACK_COR_GO(uint8_t x,uint8_t y,uint16_t vx,uint16_t vy);
/*转动一定角度*/
uint8_t TRACK_TURN_ANGLE(int16_t vw,int16_t angle);

uint8_t PRECISE_ADJUST_OK(void);
uint8_t SILENCE_ADJUST_OK(void);
uint8_t adjust(void);
void TRACK_BARRIER_COR_GO(void);
void P_ADJUST(void);
void S_ADJUST(void);

/*循迹总模块*/
/*循迹模块初始化*/
void TRACK_INIT(void);
/*循迹总结构体*/
void TRACK_MODULE(void);
/*循迹走两次的模块*/
void	TRACK_MODULE_RED_RY(void);
void	TRACK_MODULE_BLUE_BY(void);
void	TRACK_MODULE_RED_YR(void);
void	TRACK_MODULE_BLUE_YB(void);
/*循迹走三次的模块*/
void	TRACK_MODULE_RED_RYR(void);
void	TRACK_MODULE_BLUE_BYB(void);
/*循迹走四次的模块*/
void	TRACK_MODULE_RED_RYRY(void);
void	TRACK_MODULE_BLUE_BYBY(void);
void	TRACK_MODULE_RED_YRYR(void);
void	TRACK_MODULE_BLUE_YBYB(void);
/*循迹状态赋值:
cor_mode:
0-NO_COR_MODE
1-COR_UPDATE_MODE
dir_mode:
0-NO_DIR_MODE
1-DIR_RUN_MODE
2-DIR_SILENCE_MODE
*/
void TRACK_CAR_CTOL(uint8_t cor_mode,uint8_t dir_mode,int16_t vx,int16_t vy,int8_t vw,uint16_t ms);
void TRACK_LASER_CTOL(void);
/*前进一段里程*/
/*

*/
uint8_t TRACK_GO_STEP(int16_t vx,int16_t vy,int16_t step);


/////////////////////////////////////////////



#ifdef __cplusplus
}
#endif
#endif 

