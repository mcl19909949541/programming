/*该文件用于储存机械臂相关参数*/
#include "stm32f4xx_hal.h"
//机械臂初始化位置信息
#define Init_x              10
#define Init_y 	            5

//机械臂扫码扫颜色准备
#define OpenmvPre_x					5
#define OpenmvPre_y					5

//机械臂扫码位置信息
#define QR_x                25
#define QR_y   							-1

//机械臂扫颜色位置信息
#define Color_x             15
#define Color_y 						-2

//机械臂第一次抓取位置信息
#define PutUpLeft1_x 			  25
#define PutUpCent1_x        21
#define PutUpRight1_x     	25
#define PutUp1_y            1

//机械臂第二次抓取位置信息
#define PutUpLeft2_x        28
#define	PutUpCent2_x 			  21
#define PutUpRight2_x       28
#define PutUp2_y            -3

//机械臂第一次放位置信息
#define PutDownLeft1_x      29
#define PutDownCent1_x      23
#define PutDownRight1_x     29
#define PutDown1_y          -5

//机械臂第二次放位置信息
#define PutDownLeft2_x      29
#define PutDownCent2_x      20
#define PutDownRight2_x     29
#define PutDown2_y          -5

//机械臂旋转速度信息
#define FastSpeed           1000
#define MiddleSpeed         600
#define QRSpeed             200
#define ColorSpeed          250

//机械臂底座z轴角度参数
#define PUT_UP_CENT_1 70 //第一次抓取的中位（中间物块）
#define PUT_UP_LEFT_1 PUT_UP_CENT_1-110
#define PUT_UP_RIGH_1 PUT_UP_CENT_1+110

#define BASE_INIT_ANGLE PUT_UP_CENT_1+380//出车时底座的角度

#define BASE_GET_QR PUT_UP_LEFT_1//扫码时底座的角度

#define PUT_DOWN_CENT_1 PUT_UP_CENT_1+760 //第一次放的中位
#define PUT_DOWN_LEFT_1 PUT_DOWN_CENT_1+210 
#define PUT_DOWN_RIGH_1 PUT_DOWN_CENT_1-210 

#define PUT_UP_CENT_2 PUT_DOWN_CENT_1 //第二次抓取的中位（中间物块）
#define PUT_UP_LEFT_2 PUT_DOWN_LEFT_1
#define PUT_UP_RIGH_2 PUT_DOWN_RIGH_1

#define PUT_DOWN_CENT_2 PUT_UP_CENT_1+385 //第二次放的中位
#define PUT_DOWN_LEFT_2 PUT_DOWN_CENT_2+220 
#define PUT_DOWN_RIGH_2 PUT_DOWN_CENT_2-220 
//机械臂体的两个舵机的初始角度参数
#define SERVO1_INIT_ANGLE 827
#define SERVO2_INIT_ANGLE 877
//机械爪角度参数
#define PAW_ANGLE_SMALL 4//小角度
#define PAW_ANGLE_MIDDLE 6//中等角度
#define PAW_ANGLE_BIG 10//大角度
