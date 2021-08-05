#include "callback.h"

/*回调函数结构体与变量*/
UART_GRAY uart_gray;
TIM2_DELAY T2_delay;
TIM3_MODULE_UPDATE T3_module_update;
TIM4_SENSOR_UPDATE T4_sensor_update;
_tBLECOM_QUEUE Ble_RxQuene; //接收队列
_tBLECOM_QUEUE Ble_TxQuene; //发送队列

uint16_t TaskCnt_20ms;
uint16_t TaskCnt_1s;
uint8_t HeartBeat=6;//心跳计数变量，每1s记一次数
uint8_t IsConnectedFlag;//表示tcp连接是否正常的标志位，1表示正常，2表示断开
uint8_t armflag1=0;
uint8_t LASER_RX[1];
uint8_t LASER_TX[8];
uint8_t LASER_RX_TRUE[7];


uint16_t  ArmPidCnt;
uint16_t  PWMcount1=0;//PWM计数数据过大，需要2位
uint16_t  PWMcount2=0;
uint16_t  armflag2;
uint16_t  adjustflag;
/*定时器回调函数*/
//基本定时器的更新中断回调函数
/*三个定时器周期都为10ms。
其中TIM2用于延时，
TIM3用于底盘任务调度（每50ms更新一次速度信息）
TIM4专门用于各种传感器进行信息更新
*/
/*********************************************************************************
*函数功能：队列指针初始化
*输入参数：*q队列结构体指针参数，*Buf：指向的缓存区首地址，BufSize：缓存允许最大值
*输出参数：无
*返    回：无
*********************************************************************************/
void Ble_init_quene(_tBLECOM_QUEUE *q,void *Buf,uint16_t BufSize)
{
	q->qFull = 0;
	q->qIN = 0;
	q->qOUT = 0;
	q->qBuf = Buf;
	q->MaxNum = BufSize;
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if (htim->Instance == htim2.Instance)
    {
		  T2_delay.led_delay++;
			T2_delay.oled_delay++;
			armflag1++;
			
		if(armflag1>=50)
		{
			armflag1=0;
			armflag2++;
			adjustflag++;
		}
		//A型主控正常运行指示灯：红绿灯轮流闪烁
		if(T2_delay.led_delay>=50)
		{
			T2_delay.led_delay=0;
			ledflag=1-ledflag;
			LED(0,ledflag);
			LED(1,1-ledflag);
		}
		if(T2_delay.oled_delay>=10)
		{
			T2_delay.oled_delay=0;
			OLED_TRACK_CAR();
    }
	}
    if (htim->Instance == htim3.Instance)
    {
		T3_module_update.chassic++;
		T3_module_update.barrier++;
		if(T3_module_update.barrier>=15)
		{
			T3_module_update.barrier=0;
//			LASER_BARRIER_UPDATE();
		}
		//底盘运动信息更新
		if(T3_module_update.chassic>=2)
		{
			T3_module_update.angle++;
			T3_module_update.step++;
			T3_module_update.chassic=0;
//			//更新位置调整量的信息
//			TRACK_POS_ADJUST();
			//发送速度信息给B型主控
			TRACK_INSTRUCTION_TX(&hcan1);
		}
		//以下是机械臂部分的任务调度更新
		TaskCnt_20ms++;
		if(arm.target.touch_touching_cnt<250)
		  arm.target.touch_touching_cnt++;
		if(arm.target.touch_reseting_cnt<250)
		  arm.target.touch_reseting_cnt++;
//		if(TaskCnt_1s%2==1)
//		{
//			if(arm.arm_base_ctrl_enable)//如果使能了左右动态扫描
//				ArmBaseCtrl(350);
//		}
//		else if(TaskCnt_1s%2==0)
//		{
//			if(arm.arm_base_ctrl_enable)//如果使能了左右动态扫描
//				ArmBaseCtrl(600);
//		}
		if(TaskCnt_20ms%50==0)
		{
			TaskCnt_1s++;
			if(arm.target.touch_enable==1)
		    arm.target.touch_wait_time++;
			HeartBeat++ ;
		}
		if(task_delay.delay_start==1)
			task_delay.task_delay_cnt++;
		if(task_delay.task_delay_cnt==task_delay.delay_time)
		{
			task_delay.delay_start=0;
		}
    }
    if(htim->Instance == htim4.Instance)
    {
		T4_sensor_update.pos++;
		T4_sensor_update.laser++;
		//每隔10ms给一个激光发送更新指令
		if(T4_sensor_update.laser>=1)
		{
			T4_sensor_update.laser=0;
			LASER_TX_UPDATE();
		}
		//每40ms更新一次位置调整信息
		if(T4_sensor_update.pos>=5)
		{
			T4_sensor_update.pos=0;
			GRAY_FUNC_DIR_UPDATE();
		}
    }
}
//OC中断回调函数
void HAL_TIM_OC_DelayElapsedCallback(TIM_HandleTypeDef *htim)
{
	if (htim->Instance == htim8.Instance)
	{
	}
}
//PWM中断回调函数
void HAL_TIM_PWM_PulseFinishedCallback(TIM_HandleTypeDef *htim)
{
	if (htim->Instance == htim8.Instance)//每10^(-4)秒来一个脉冲
	{
			PWMcount1++;
		if(PWMcount1>1000)
		{
			PWMcount2++;		//每0.1秒+1，10khz/200/8=6.25转/s
			if(PWMcount2>86)//6.25x10=62.5转
		  {
			  HAL_TIM_PWM_Stop(&htim8, TIM_CHANNEL_1);
			  PWMcount2=0;
		  }
		  PWMcount1=0;
		}
	}
}

//CAN中断回调函数
void HAL_CAN_RxFifo0MsgPendingCallback (CAN_HandleTypeDef *hcan)
{
	uint8_t i;
	uint16_t temp;
	//接收can1发来的数据
	if(hcan->Instance == CAN1)
	{
		temp=0;
		HAL_CAN_GetRxMessage(&hcan1, CAN_RX_FIFO0, &CAN1_RXMSG.rxheader, CAN1_RXMSG.rxdata);
		switch(CAN1_RXMSG.rxheader.StdId)
		{
			case 0x401:
			{
	      temp=temp|CAN1_RXMSG.rxdata[0];//高八位
			  CAR.CUR_V.VX=(temp << 8) | CAN2_RXMSG.rxdata[1];//低八位
			  temp=0;
			  temp=temp|CAN1_RXMSG.rxdata[2];//高八位
			  CAR.CUR_V.VY=(temp << 8) | CAN2_RXMSG.rxdata[3];//低八位
			  temp=0;
			}
			break;
		}
	}
	//接收can2发来的数据
	if(hcan->Instance == CAN2)
	{
		temp=0;
		HAL_CAN_GetRxMessage(&hcan2, CAN_RX_FIFO0, &CAN2_RXMSG.rxheader, CAN2_RXMSG.rxdata);
		if(CAN2_RXMSG.rxheader.StdId == 0x1311)
		{
		  temp = temp | CAN2_RXMSG.rxdata[3];//高八位
			LASER.pwm_laser = (temp << 8) | CAN2_RXMSG.rxdata[4];//低八位
			temp=0;	
		}	
		switch(CAN2_RXMSG.rxheader.StdId)
		{
			//激光发来的数据    //主循环一直执行坐标函数（8.8），收到激光数据，判断有障碍物，再次执行坐标函数时会使其避障，
													//赋值给电机速度 -0.3*5000 = -1500，电机来不及反应 此时灰度接收中断，进行位置更新,判断速度方向为负，坐标减少！
//			case 0x0000:
//				{
//				if(CAN2_RXMSG.rxdata[2]!=12)
//				{
//				temp = temp | CAN2_RXMSG.rxdata[3];//高八位
//				LASER.laser_value[CAN2_RXMSG.rxdata[2]] = (temp << 8) | CAN2_RXMSG.rxdata[4];//低八位
//				temp=0;
//				}
//				
//				else 
//				{
//				temp = temp | CAN2_RXMSG.rxdata[3];//高八位
//				LASER.pwm_laser = (temp << 8) | CAN2_RXMSG.rxdata[4];//低八位
//				temp=0;
//				}
//				}
//				break;
			/*A2主控发来的灰度数据*/
			case 0x102:
			{
				//更新速度矢量信息和方向信息
				TRACK_DIR_UPDATE(); //进灰度中断就开始判断运动方向，如果有障碍物，电机反应不及时，赋值速度为-1500，车往前走，速度向后，y坐标减少				
				for(i=0;i<4;i++)
				{
					temp = temp | CAN2_RXMSG.rxdata[i*2];//高八位
					temp = (temp << 8) | CAN2_RXMSG.rxdata[i*2+1];//低八位
					DIGITAL_GRAY_ANALYSIS(temp,i+1);
					temp=0;
					/*一轮灰度信息赋值完后进行位置信息更新*/
					if(i==3)
					{
						//更新位置调整量的信息
						TRACK_POS_ADJUST();
						//更新速度矢量信息和方向信息
			      		TRACK_DIR_UPDATE();
						
						LASER_BARRIER_UPDATE();

						TRACK_POS_UPDATE();
						TRACK_COR_UPDATE();
					}
				}
			}
			break;
/*********************************************2020年版架构A2无激光，故屏蔽********************************************************************/
			/*A2主控发来的第一组四个激光数据*/
//			case 0x103:
//			{
//				for(i=0;i<4;i++)
//				{
//					temp = temp | CAN2_RXMSG.rxdata[i*2];//高八位
//					temp = (temp << 8) | CAN2_RXMSG.rxdata[i*2+1];//低八位
//					LASER.last_last_laser_value[i]=LASER.last_laser_value[i];
//					LASER.last_laser_value[i]=LASER.cur_laser_value[i];
//					LASER.cur_laser_value[i]=temp;
//					LASER.laser_value[i]=(LASER.last_last_laser_value[i]+LASER.last_laser_value[i]+LASER.cur_laser_value[i])/3;
//					temp=0;
//				}
//			}
//			break;
			/*A2主控发来的第二组四个激光数据*/
//			case 0x104:
//			{
//				for(i=0;i<4;i++)
//				{
//					temp = temp | CAN2_RXMSG.rxdata[i*2];//高八位
//					temp = (temp << 8) | CAN2_RXMSG.rxdata[i*2+1];//低八位
//					LASER.last_last_laser_value[i+4]=LASER.last_laser_value[i+4];
//					LASER.last_laser_value[i+4]=LASER.cur_laser_value[i+4];
//					LASER.cur_laser_value[i+4]=temp;
//					LASER.laser_value[i+4]=(LASER.last_last_laser_value[i+4]+LASER.last_laser_value[i+4]+LASER.cur_laser_value[i+4])/3;
//					LASER.laser_value[i+4]=temp;
//					temp=0;
//				}
//			}
//			break;
		}
	}
}


//串口回调函数
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)//串口中断处理函数
{
	int16_t temp=0;
	uint8_t i = 0;
	
	if(huart==&huart7)
	{
	  HAL_UART_Receive_IT(&huart7,LASER_RX,1);
		static uint8_t sum = 0;
		LASER_RX_TRUE[sum] = LASER_RX[0];
		sum++;
		if(sum >= 3)
		{
		  if(LASER_RX_TRUE[1] != 0x03 || LASER_RX_TRUE[2] != 0x02)sum=0;
			
			else if(sum >= 7)
		  {
		    temp = temp | LASER_RX_TRUE[3];
		    LASER.laser_value[LASER_RX_TRUE[0]] = (temp << 8)|LASER_RX_TRUE[4];
		    temp = 0;
		    sum = 0;
		  }
		}
	}
	if(huart==&huart8)
	{
		if(TCPRevDataHandler(tcp_rev_buf[0])==0)
		  TCPRevDatasHandler(tcp_rev_datas);
	  HAL_UART_Receive_IT(&huart8,tcp_rev_buf,1);
	}
	if(huart==&huart6)
	{
		if(OpenmvRevDataHandler(openmv_rev_buf[0])==0)
			OpenmvRevDatasHandler(openmv_rev_datas);
		HAL_UART_Receive_IT(&huart6,openmv_rev_buf,1);
	}
}

//串口错误回调函数
void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart)
{
  if(huart->Instance == USART2)
	{
		__HAL_UART_CLEAR_OREFLAG(&huart2);
//		if(HAL_UART_Receive_IT(&huart2,LASER_RX,1) != HAL_OK)
//		{
//		}
	}
	if(huart->Instance == USART6)
	{
		__HAL_UART_CLEAR_OREFLAG(&huart6);
		if(HAL_UART_Receive_IT(&huart6,openmv_rev_buf,1) != HAL_OK)
		{
		}
	}
	if(huart->Instance == UART7)
	{
		__HAL_UART_CLEAR_OREFLAG(&huart7);
		if(HAL_UART_Receive_IT(&huart7,LASER_RX,1) != HAL_OK)
	  {
	  }
  }
	if(huart->Instance == UART8)
	{
		__HAL_UART_CLEAR_OREFLAG(&huart8);
		if(HAL_UART_Receive_IT(&huart8,tcp_rev_buf,1) != HAL_OK)
		{
		}
	}
}


