#include "module_arm.h"
#include "callback.h"
#include "track.h"
#include "tcp.h"
#include "oled.h"

DEF_ARM arm;//定义一个机械臂
uint8_t openmv_revi[1];
double test_x=0,test_y=0;

uint8_t Servotx[10]={0x55,0x55,0x01,0x07,0x01,0x00,0x00,0x00,0x00,0x00};
uint8_t Servorx[10];
uint8_t openmv_send_data[]="12345678";
uint8_t openmv_rev[3];
uint8_t adjustlaser(uint8_t color)
{
   while(!TRACK_GO_STEP(-500,0,5));
	return 1;
}	
void  Duoji_angle(uint8_t ID,uint16_t angle, int speed)    //乐幻索尔舵机的舵机模式
{
	 uint8_t count; 
	 uint16_t check=0;
	
   Servotx[0] = 0X55;  
   Servotx[1] = 0X55;
   Servotx[2] = ID;
   Servotx[3] = 0x07;
	 Servotx[4] = 0x01;
	 Servotx[5] = angle&0xff;
	 Servotx[6] = angle>>8;
	 Servotx[7] = speed&0xff;                  //到达指定角度的时间，即舵机转速
	 Servotx[8] = speed>>8;
	
	 for(count=0;count<7;count++){
			check+=Servotx[count+2];
	 }
	 check%=256;
	 check=~check;
	 Servotx[9]=(uint8_t)check;
	
	 HAL_UART_Transmit(&huart8,Servotx, 10, 0xffff);
}

void Duoji_Init()
{
  Duoji_angle(0x01, 3, 900);
  Duoji_angle(0x02, 265, 900);
  Duoji_angle(0x03, 527, 900);
  Duoji_angle(0x04, 439, 900);
  Duoji_angle(0x05, 542, 900);
  Duoji_angle(0x06, 760, 900);
  Duoji_angle(0x07, 180, 900);
	HAL_Delay(1500);
}
	
void waiting_fetch_ball()
{
	Duoji_angle(0x06, 732, 900);
	HAL_Delay(500);
	Duoji_angle(0x07, 280, 900);
	HAL_Delay(500);
  Duoji_angle(0x03, 850, 900);
  Duoji_angle(0x02, 211, 900);
  HAL_Delay(500);
  Duoji_angle(0x01, 270, 900);
  HAL_Delay(500);
  Duoji_angle(0x04, 245, 900);
  Duoji_angle(0x05, 327, 900);
  HAL_Delay(500);
	Duoji_angle(0x03, 795, 900);
  HAL_Delay(500);
}

void waiting_fetch_cube()
{
	Duoji_angle(0x01, 60, 900);
  HAL_Delay(500);
	Duoji_angle(0x07, 225, 900);
	HAL_Delay(500);
  Duoji_angle(0x03, 850, 900);
  HAL_Delay(500);
  Duoji_angle(0x02, 211, 900);
  HAL_Delay(500);
  Duoji_angle(0x01, 300, 900);
  HAL_Delay(500);
	Duoji_angle(0x03, 790, 900);
  HAL_Delay(500);
	Duoji_angle(0x06, 732, 900);
	HAL_Delay(500);
  Duoji_angle(0x04, 245, 900);
  Duoji_angle(0x05, 327, 900);
  
	
}

void waiting_fetch_qr()
{
	Duoji_angle(0x01, 60, 900);
  HAL_Delay(500);
	Duoji_angle(0x07, 235, 900);
	HAL_Delay(700);
  Duoji_angle(0x03, 850, 900);
  HAL_Delay(500);
  Duoji_angle(0x02, 213, 900);
  HAL_Delay(500);
  Duoji_angle(0x01, 280, 900);
  HAL_Delay(500);
	Duoji_angle(0x03, 794, 900);
  HAL_Delay(500);
	Duoji_angle(0x06, 732, 900);
	HAL_Delay(500);
  Duoji_angle(0x04, 188, 900);
  Duoji_angle(0x05, 293, 900);
  
	
}

void finish_fetch(uint8_t color)
{	
	uint8_t openmv_send_ball_r[]={0x55, 0x56, 0x01, 0x01, 0x88, 0x88};
	uint8_t openmv_send_ball_b[]={0x55, 0x56, 0x02, 0x02, 0x88, 0x88};
	uint8_t openmv_send_ball_y[]={0x55, 0x56, 0x03, 0x03, 0x88, 0x88};
	uint8_t openmv_send_cube_r[]={0x55, 0x56, 0x04, 0x04, 0x88, 0x88};
	uint8_t openmv_send_cube_b[]={0x55, 0x56, 0x05, 0x05, 0x88, 0x88};
	uint8_t openmv_send_cube_y[]={0x55, 0x56, 0x06, 0x06, 0x88, 0x88};
	uint8_t openmv_send_qr_r[]={0x55, 0x56, 0x07, 0x07, 0x88, 0x88};
	uint8_t openmv_send_qr_b[]={0x55, 0x56, 0x07, 0x08, 0x88, 0x88};
	uint8_t openmv_send_qr_y[]={0x55, 0x56, 0x07, 0x09, 0x88, 0x88};
	uint8_t openmv_send_data[] = {NULL, *openmv_send_ball_r, *openmv_send_ball_b, *openmv_send_ball_y,
																*openmv_send_cube_r, *openmv_send_cube_b, *openmv_send_cube_y,
																*openmv_send_qr_r, *openmv_send_qr_b, *openmv_send_qr_y};
	int num=0, i=0;
	armflag2=0;
	HAL_UART_Receive_IT(&huart6,openmv_revi,4);
	HAL_Delay(1500);
	if(color>=4&&color<=6)
		TRACK_CAR_CTOL(0,0,0,800,0,0);
	else if(color>=7)
		TRACK_CAR_CTOL(0,0,0,600,0,0);
		while(1){
			HAL_UART_Receive_IT(&huart6,openmv_revi,4);
			switch(color){
				case 1: {
					HAL_UART_Transmit(&huart6, openmv_send_ball_r,6,0X01);
					break;
				}	
				case 2: {
					HAL_UART_Transmit(&huart6, openmv_send_ball_b,6,0X01);
					break;
				}	
				case 3: {
					HAL_UART_Transmit(&huart6, openmv_send_ball_y,6,0X01);
					break;
				}	
				case 4: {
					HAL_UART_Transmit(&huart6, openmv_send_cube_r,6,0X01);
					break;
				}
				case 5: {
					HAL_UART_Transmit(&huart6, openmv_send_cube_b,6,0X01);
					break;
				}	
				case 6: {
					HAL_UART_Transmit(&huart6, openmv_send_cube_y,6,0X01);
					break;
				}	
				case 7: {
					HAL_UART_Transmit(&huart6, openmv_send_qr_r,6,0X01);
					break;
				}
				case 8: {
					HAL_UART_Transmit(&huart6, openmv_send_qr_b,6,0X01);
					break;
				}	
				case 9: {
					HAL_UART_Transmit(&huart6, openmv_send_qr_y,6,0X01);
					break;
				}	
			}
			if(openmv_revi[0]==0x59){
					if(color>=4)
						HAL_Delay(750);
					else if(color <= 3)
						HAL_Delay(400);
					openmv_revi[0] = 0;
					TRACK_CAR_CTOL(0,0,0,0,0,0);
					if(color>=4){
						Duoji_angle(0x01, 5, 5);
						HAL_Delay(300);
						Duoji_angle(0x01, 300, 5);
					}
					else{
						Duoji_angle(0x01, 100, 5);
						HAL_Delay(250);
						Duoji_angle(0x01, 270, 5);
					}
					num ++;
					if(color>=4&&color<=6)
						TRACK_CAR_CTOL(0,0,0,800,0,0);
					else if(color>=7&&color<=9)
						TRACK_CAR_CTOL(0,0,0,600,0,0);
			}
			
			else if(armflag2>=30&&color!=3)
			{
				armflag2=0;
				break;
			}
			else if(armflag2>=20&&color==3)
			{
				armflag2=0;
				break;
			}
			else if(num==3&&color>=4&&color<6) break;
			else if(num==7&&color>=1&&color<=3) break;
			else if(num==2&&color>=7&&color<=9) break;
			else if(num==3&&color==6) break;
			else if(LASER.laser_value[1]>=200&&color>3) break;
		}
		TRACK_CAR_CTOL(0,0,0,0,0,0);
		Duoji_angle(0x01, 380, 900);
		HAL_Delay(500);
		Duoji_angle(0x03, 766, 900);
		HAL_Delay(500);
		
		Duoji_angle(0x04, 439, 900);
		Duoji_angle(0x05, 542, 900);
		
		HAL_Delay(500);
		Duoji_angle(0x01, 3, 900);
		HAL_Delay(500);
		Duoji_angle(0x03, 527, 900);
		HAL_Delay(500);
		HAL_Delay(500);
}


//PID_HANDLE Servo6PidAngle = {0};
//PID_HANDLE Servo5PidAngle_up = {0};
//PID_HANDLE Servo4PidAngle_up = {0};
//PID_HANDLE Servo3PidAngle_up = {0};
//PID_HANDLE Servo2PidAngle_up = {0};
//PID_HANDLE Servo1PidAngle = {0};

//PID_HANDLE Servo5PidAngle_down = {0};
//PID_HANDLE Servo4PidAngle_down = {0};
//PID_HANDLE Servo3PidAngle_down = {0};
//PID_HANDLE Servo2PidAngle_down = {0};
//PID_HANDLE Servo1PidAngle_down = {0};

void ServoGetPos(void)				 		//读取7个舵机信息
{
  SERVO_POS_READ(&arm.servo1);
	SERVO_POS_READ(&arm.servo2);
  SERVO_POS_READ(&arm.servo3);
	SERVO_POS_READ(&arm.servo4);
	SERVO_POS_READ(&arm.servo5);
	SERVO_POS_READ(&arm.servo6);
	SERVO_POS_READ(&arm.servo7);
}

void ArmGetPos(DEF_ARM* arm)
{
}


uint8_t ServoEndJudging(SERVO_HandleTypeDef *Servo,uint8_t error)
{
	if(Servo->ActAngle-Servo->TagAngle>-error&&Servo->ActAngle-Servo->TagAngle<error)
		return 1;
	else
		return 0;
}

void ServosCtrl(DEF_ARM *arm)
{
  ServoDriver(&(arm->servo2));
  ServoDriver(&(arm->servo3));
	ServoDriver(&(arm->servo4));
  ServoDriver(&(arm->servo5));
}

//货舱控制函数 cmd:1:收起货舱 2:放下货舱 0:展开货舱，收集小球时的指令
void ArmHoldCtrl(DEF_ARM* arm)
{
	switch(arm->hold.cmd)
	{
		case 1:
			arm->servo7.TagAngle=arm->hold.up_angle;
		  break;
		case 2:
			arm->servo7.TagAngle=arm->hold.down_angle;
		  break;
		case 0:
			arm->servo7.TagAngle=arm->hold.collect_angle;
		  break;		
		default:
			break;
	}
	arm->servo7.TagAngleDelayTime=1000;
	ServoDriver(&(arm->servo7));
}

//void Pid_Init(void)
//{
//	//PID使能
//	Servo1PidAngle.enable            = 1;
//	//PID使能积分限幅
//	Servo1PidAngle.enable_lim_sum_error  = 1;
//	//PID使能输出限幅
//	Servo1PidAngle.enable_lim_ouput      = 1;
//	//PID比例参数
//	Servo1PidAngle.kp                    = 8;
//	//PID积分参数
//	Servo1PidAngle.ki                    = 0.1;
//	//PID微分参数
//	Servo1PidAngle.kd                    = 5;
//	//PID积分限幅
//	Servo1PidAngle.lim_sum_error         = 1500;
//	//PID输出限幅
//	Servo1PidAngle.lim_output            = 1000;
//	//均值滤波器
//	Servo1PidAngle.hfilter1.a            = 0;
//}

void ArmInit(DEF_ARM *arm)
{
  arm->servo1.ID=0x01;
	arm->servo1.mode=ServoMode;
	arm->servo1.TagAngle=PAW_RESET_POS;
	arm->servo2.ID=0x02;
	arm->servo2.mode=ServoMode;
	arm->servo2.InitActAngle=592;
	arm->servo3.ID=0x03;
	arm->servo3.mode=ServoMode;
	arm->servo3.InitActAngle=635;
	arm->servo4.ID=0x04;
	arm->servo4.mode=ServoMode;
	arm->servo4.InitActAngle=555;
	arm->servo5.ID=0x05;
	arm->servo5.mode=ServoMode;
	arm->servo5.InitActAngle=683;
	arm->servo6.ID=0x06;
	arm->servo6.mode=ServoMode;
	arm->servo6.InitActAngle=500;
	arm->servo7.ID=0x07;
	arm->servo7.mode=ServoMode;
	ArmGetPos(arm);
	arm->servo1.LastActAngle=arm->servo1.ActAngle;
	arm->servo2.LastActAngle=arm->servo2.ActAngle;
	arm->servo3.LastActAngle=arm->servo3.ActAngle;
	arm->servo4.LastActAngle=arm->servo4.ActAngle;
	arm->servo5.LastActAngle=arm->servo5.ActAngle;
	arm->servo6.LastActAngle=arm->servo6.ActAngle;
	arm->servo7.LastActAngle=arm->servo7.ActAngle;
	arm->hold.up_angle=0;
	arm->hold.collect_angle=200;
	arm->hold.down_angle=450;
	arm->state=ACTION_START;
	arm->target.touch_enable=0;
	arm->target.touch_state=TOUCH_READY;
//	Pid_Init();
	arm->targetPos_x=2;
	arm->targetPos_y=20;
  ArmDriver(arm);//更新机械臂坐标值以及驱动机械臂
	arm->hold.cmd=0;//放平货舱
	arm->servo1.TagAngle=PAW_RESET_POS;
	ServoDriver(&(arm->servo1));
	ServosCtrl(arm);
	ArmHoldCtrl(arm);
	arm->times_cnt=1;
	#if TEST_MOUDLE==1
	ArmBaseCtrl(475);
	#else
	ArmBaseCtrl(475);
	#endif
	
}

void TouchMonitor(DEF_ARM *arm)//如果监测到目标颜色，则控制机械抓触碰目标
{
	if(arm->target.touch_enable)//如果使能拨球
	{
		#if TEST_MOUDLE==1
		if(arm->openmv.ball_color_got!=0)
		#else
		if(arm->openmv.ball_color_got==arm->target.target_color)
		#endif
		{
			arm->target.touch_target_switch=1;
//			arm->is_arm_got_target=1;
//			if(arm->times_cnt==3||arm->times_cnt==4)
			arm->target.touch_wait_time=0;
		}
		else
		{
			arm->target.touch_target_switch=0;
		}
	}
	arm->openmv.ball_color_got=0;
		
}

//击打球的最佳位置为x:32  y:24 
void TouchAargetDriver(DEF_ARM *arm)
{
	switch(arm->target.touch_state)
	{
		case TOUCH_READY:
			if(arm->target.touch_target_switch==1&&arm->target.touch_reseting_cnt>25)//如果发现目标
			{
				arm->target.touch_state=TOUCHING;
			}
			break;
		case TOUCHING:
			arm->servo1.TagAngle=PAW_TOUCH_POS;
		  ServoDriver(&(arm->servo1));
			arm->target.touch_state=TOUCH_RESET;
		  arm->target.touch_touching_cnt=0;
			break;
		case TOUCH_RESET:
			if(arm->target.touch_touching_cnt>10)
			{
				arm->servo1.TagAngle=PAW_RESET_POS;
				arm->target.touch_target_switch=0;
				arm->target.touch_state=TOUCH_READY;
				ServoDriver(&(arm->servo1));
				#if TEST_MOUDLE==1
				arm->is_test_ball_got=1;
				#else
				arm->target.collected_ball_cnt[arm->target.target_color-1]++;
				#endif
				arm->target.touch_reseting_cnt=0;
				arm->target.touch_target_switch=0;
			}
			break;                 
	}
}

uint8_t ServoSpeedMeasure(SERVO_HandleTypeDef* servo)
{
	double temp_move;
	if(servo->speed_measure.speed_measure_enable==0)
	{
		servo->speed_measure.speed_measure_enable=1;
		servo->speed_measure.speed_last=servo->ActAngle;
	}
	if(servo->speed_measure.speed_measure_cnt_20ms>50)//1s之后
	{
	  servo->speed_measure.speed_measure_enable=0;
		servo->speed_measure.speed_measure_cnt_20ms=0;
		temp_move=servo->ActAngle-servo->speed_measure.speed_last;
		if(temp_move*temp_move<2500)//如果动的幅度不大，就说明机械臂没有动
		{
			return 1;
		}
		else
			return 2;
	}
	return 0;
}

int16_t AngVal6;//全局变量，测试用

void ArmDriver(DEF_ARM *arm)
{
	double d,theta3,theta2,err_x,err_y;
	int16_t AngVal2,AngVal3,AngVal4,AngVal5;
	d=sqrt(arm->targetPos_x*arm->targetPos_x+arm->targetPos_y*arm->targetPos_y);//计算目标点到原点的距离
	if(d>(ArmL1-ArmL2)&&d>(ArmL2-ArmL1)&&d<(ArmL1+ArmL2))//如果可以到达目标点
	{
		theta3=pi/2-(acos((ArmL1*ArmL1+d*d-ArmL2*ArmL2)/(2*ArmL1*d))+atan(arm->targetPos_y/arm->targetPos_x));//舵机1偏离的角度
    theta2=pi-acos((ArmL1*ArmL1+ArmL2*ArmL2-d*d)/(2*ArmL1*ArmL2));//舵机2的角度
		//计算误差
		err_x=arm->targetPos_x-(ArmL1*sin(theta3)+ArmL2*cos(theta2+theta3-pi/2));
		err_y=arm->targetPos_y-(ArmL1*cos(theta3)-ArmL2*sin(theta2+theta3-pi/2));
		if(err_x*err_x+err_y*err_y<=50)//如果根据解算的舵机角度算出来的目标坐标与目标点的坐标相吻合
		{
			AngVal4=arm->servo4.InitActAngle+theta3*180/pi/0.24;//转换量纲
			AngVal5=arm->servo5.InitActAngle+theta3*180/pi/0.24;
			AngVal3=arm->servo3.InitActAngle-theta2*180/pi/0.24;
			AngVal2=arm->servo2.InitActAngle-80/0.24;
			arm->servo2.TagAngle=AngVal2;
			arm->servo3.TagAngle=AngVal3;//给舵机赋值
			arm->servo4.TagAngle=AngVal4;
			arm->servo5.TagAngle=AngVal5;//舵机4、5要保持一致
			arm->servo2.TagAngleDelayTime=1000;
			arm->servo3.TagAngleDelayTime=1000;
			arm->servo4.TagAngleDelayTime=1000;
			arm->servo5.TagAngleDelayTime=1000;
//			temp_deltax=arm->actualPos_x-arm->targetPos_x;
//			temp_deltay=arm->actualPos_y-arm->targetPos_y;	
////      if(ArmSpeedMeasure(arm)==1&&temp_deltax*temp_deltax+temp_deltay*temp_deltay>40)//如果机械臂没有动
////			{
////				ServosCtrl(arm);
////			}		
////      if(temp_deltax*temp_deltax+temp_deltay*temp_deltay<40)//如果到达目标点
////        arm->is_arm_reach=1;
////      else
////        arm->is_arm_reach=0;				
		}
	}
}

uint8_t tcp_send_setting_flag;//tcp发送配置标志位，当值为0时，配置服务器发送参数，当值为1时，发送消息
void Arm(void)
{
	if(TaskCnt_20ms%2==0)//每40ms执行一次
	{
		//ArmGetPos(&arm);//读取机械臂现在的状态
	  TouchMonitor(&arm);
//	  TouchAargetDriver(&arm);
		switch(arm.state)
		{
			case READY:
				//闲置
				break;
			case ACTION_START:
			  #if TOUCH_TEST==0//如果没有打开测阈值模式
				if(TRACK.STATE==TRACK_WAIT_FETCH||TRACK.STATE==TRACK_WAIT_FETCH_2||TRACK.STATE==TRACK_WAIT_FETCH_3||TRACK.STATE==TRACK_WAIT_FETCH_4)
				#endif
				{
					arm.state=ACTION_1;
					arm.targetPos_x=16;
				  arm.targetPos_y=40;
					ArmDriver(&arm);//更新机械臂坐标值以及驱动机械臂
					ServosCtrl(&arm);
          TaskDelayStart(&task_delay,100);//延时2s
          #if TEST_MOUDLE==1					
          ArmBaseCtrl(600);	
          #endif					
				}
				break;
			case ACTION_1:
				if(task_delay.delay_start==0)
				{
					arm.state=WAIT_COLLECT_BALL;
          arm.targetPos_x=28;
				  arm.targetPos_y=28;
					ArmDriver(&arm);//更新机械臂坐标值以及驱动机械臂
          ServosCtrl(&arm);
          TaskDelayStart(&task_delay,100);//延时2s					
				}
				break;
			case ACTION_2:
				if(task_delay.delay_start==0)
				{
					TaskDelayStart(&task_delay,100);//延时2s
					arm.state=WAIT_COLLECT_BALL;
				}
				break;
			case WAIT_COLLECT_BALL:
				#if TOUCH_TEST==1
					arm.target.target_color=2;
				#else
				  arm.target.target_color=TRACK.color;
			    arm.target.collected_ball_cnt[arm.target.target_color-1]=0;
			  #endif
				if(task_delay.delay_start==0)//延时时间到
				{
					if(arm.times_cnt==1||arm.times_cnt==3)
						arm.target.target_cnt[arm.target.target_color-1]=10;
					else if(arm.times_cnt==2)
						arm.target.target_cnt[arm.target.target_color-1]=11;
					arm.target.collected_ball_cnt[arm.target.target_color-1]=0;
					arm.target.touch_wait_time=0;
					arm.target.touch_enable=1;
					arm.state=ACTION_COLLECT_BALL;
					#if TEST_MOUDLE==1//如果测试模式打开
						 ArmBaseCtrl(300);
					   arm.is_test_ball_got=0;
          #endif					
				}
				break;
			case ACTION_COLLECT_BALL:
          TouchAargetDriver(&arm);					
          #if TOUCH_TEST==0			
					if(arm.is_test_ball_got==1||((arm.target.touch_wait_time>15||arm.target.collected_ball_cnt[arm.target.target_color-1]>=arm.target.target_cnt[arm.target.target_color-1])&&arm.target.touch_state==TOUCH_READY))//如果收集够球
					{
						arm.target.touch_enable=0;
						arm.state=ACTION_3;
						TaskDelayStart(&task_delay,100);//延时2s
						arm.targetPos_x=16;
				    arm.targetPos_y=40;
						ArmDriver(&arm);//更新机械臂坐标值以及驱动机械臂
						ServosCtrl(&arm);
						arm.arm_base_ctrl_enable=0;
					}
			    #endif
				break;
			case ACTION_3:
				if(task_delay.delay_start==0)
				{
					arm.state=ACTION_4;
					arm.targetPos_x=2;
				  arm.targetPos_y=20;
					ArmDriver(&arm);//更新机械臂坐标值以及驱动机械臂
          ServosCtrl(&arm);
          TaskDelayStart(&task_delay,100);//延时2s
				}
				break;
			case ACTION_4:
			  if(task_delay.delay_start==0)
				{
					arm.state=ACTION_5;
					arm.hold.cmd=1;//收起货舱 
					ArmHoldCtrl(&arm);
				}
				break;
			case ACTION_5:
				if(TRACK.STATE==WAIT_PUT_OVER||TRACK.STATE==WAIT_PUT_OVER_2||TRACK.STATE==WAIT_PUT_OVER_3||TRACK.STATE==WAIT_PUT_OVER_4)
				{
					arm.state=ACTION_STOP;
					arm.hold.cmd=2;//放下货舱，倒小球
					TaskDelayStart(&task_delay,150);//延时3s
					ArmHoldCtrl(&arm);
				}
				break;
			case ACTION_STOP:
				if(task_delay.delay_start==0)//如果上一个延时时间到
				{
					arm.state=ACTION_START;
					arm.hold.cmd=0;//放平货舱
					ArmHoldCtrl(&arm);
					arm.times_cnt++;
				}
				break;
			default:
				break;
		}
	}
}

void ArmBaseCtrl(int16_t angle)
{
	arm.servo6.TagAngle=angle;
	arm.servo6.TagAngleDelayTime=2000;
	ServoDriver(&(arm.servo6));
}

/* 平台初始化函数   */
void Platform_Init()
{ 
//  LASER_INSTRUCTION_TX(&hcan2,0x0C);  //发送指令更新激光数据
//	HAL_Delay(30);				 //10ms更新
  while(LASER.laser_value[2] > 70)     //激光数据会比实际大
	{
		PlatformControl(2,0,0);    //平台下降
		HAL_Delay(30);				 //30ms更新
	}
		HAL_TIM_PWM_Stop(&htim8, TIM_CHANNEL_1); //平台停止，停止pwm
}


/* 平台控制函数   mode=1上升 mode=2下降 mode=3上升一半 mode=4下降一半 pwmcount1 pwmcount2PWM计数变量*/
void PlatformControl(uint8_t mode, uint16_t  pwmcount1, uint16_t  pwmcount2)  
{
	switch (mode)
	{
		case 1:
		{	
				HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, GPIO_PIN_SET);
	      HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, GPIO_PIN_RESET);
		    PWMcount1=pwmcount1;
        PWMcount2=pwmcount2;
      	pwm_setvalue(60);//包含了打开PWM通道的步骤	
		}
		break;
		
		case 2:
		{
			  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, GPIO_PIN_RESET);
	      HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, GPIO_PIN_RESET);
		    PWMcount1=pwmcount1;
        PWMcount2=pwmcount2;
      	pwm_setvalue(60);
		}			
		break;
		
//		case 3:
//		{	
//				HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, GPIO_PIN_SET);
//	      HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, GPIO_PIN_RESET);
//		    PWMcount1=pwmcount1;
//        PWMcount2=pwmcount2;//75
//      	pwm_setvalue(60);	
//		}
//		break;
//		
//		case 4:
//		{
//			  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, GPIO_PIN_RESET);
//	      HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, GPIO_PIN_RESET);
//		    PWMcount1=pwmcount1;
//        PWMcount2=pwmcount2;//75
//      	pwm_setvalue(60);
//		}			
//		break;
	}
}

