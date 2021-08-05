#ifndef _DEVICE_STEER_H
#define _DEVICE_STEER_H

#include "stm32f4xx_hal.h"

#define online 1
#define offline 2
#define ArmUart huart7   //串口宏定义，方便移植

#define MotorMode 1
#define ServoMode 2

typedef struct
{
	int16_t speed_last;
	uint8_t speed_measure_enable;
	uint8_t speed_measure_cnt_20ms;
}DEF_SERVO_SPEED_MEASURE;

typedef struct
{
	uint8_t ID;//舵机ID
	uint8_t mode;
    int16_t TagAngle;//舵机目标角度
	int16_t Speed;//舵机转动目标速度
	uint16_t TagAngleDelayTime;//舵机转动到目标角度所用的时间
	int16_t ActAngle;//舵机实时角度
	int16_t LastActAngle;//舵机上次实际角度
	int16_t InitActAngle;//初始角度，即舵机的初始化角度，机械臂体上的舵机初始角度为中位角度
	uint8_t is_reach;//舵机是否到达目标点的标志，如果舵机目前回传的角度与目标角度相差幅度比较小，则认为舵机已到达目标角度
	DEF_SERVO_SPEED_MEASURE speed_measure;
}SERVO_HandleTypeDef;//舵机句柄

extern uint8_t ArmRxDatas[10];

void SERVO_MOVE_TIME_WRITE(SERVO_HandleTypeDef *Arm_Write);
void SERVO_MOVE_TIME_READ(SERVO_HandleTypeDef *ServoWrite);
void SERVO_ANGLE_OFFSET_ADJUST(SERVO_HandleTypeDef *ServoWrite);
void SERVO_POS_READ(SERVO_HandleTypeDef *Servo);
void SERVO_OR_MOTOR_MODE_WRITE(SERVO_HandleTypeDef *Servo);
void ServoDriver(SERVO_HandleTypeDef *Servo);
void MotorRemoteTest(SERVO_HandleTypeDef *Servo,int16_t ch);

#endif
