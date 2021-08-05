#include "laser.h"
#include "callback.h"

/*声明结构体与变量*/
DEF_LASER_STATE LASER;

/*激光采集函数*/
void  LASER_INSTRUCTION_TX(CAN_HandleTypeDef *hcan,uint8_t id)
{
    static CAN_TxHeaderTypeDef LASER_HDR =
    {
        //A型主控给激光发送的ID号
        0x101,
        0,
        CAN_ID_STD,
        CAN_RTR_DATA,
        8,
        DISABLE
    };	
		//header1
		CAN2_TXMSG.txdata[0]=0x55;
    //header2
    CAN2_TXMSG.txdata[1] = 0x55;
    //所要采集的激光ID号
		CAN2_TXMSG.txdata[2] = id;
    //采集指令
    CAN2_TXMSG.txdata[3] = 0x02;
    //校验和
    CAN2_TXMSG.txdata[4] = (CAN2_TXMSG.txdata[2]+0x02)&0xff;
    CAN2_TXMSG.txdata[5] = 0;
    CAN2_TXMSG.txdata[6] = 0;
    CAN2_TXMSG.txdata[7] = 0;
	HAL_CAN_AddTxMessage(hcan, &LASER_HDR, CAN2_TXMSG.txdata, &CAN2_TXMSG.txmailbox);
}
/*
激光数据更新
*/
void LASER_TX_UPDATE(void)
{
    static uint8_t num = 0;
	  uint8_t buf[6] = { 0 };
		LASER_TX[0] = num;
    LASER_TX[1] = 0x03;
	  LASER_TX[2] = 0x00; 
    LASER_TX[3] = 0x34;
    LASER_TX[4] = 0x00;
    LASER_TX[5] = 0x01;
	  for(uint8_t i = 0; i<6; i++)
		{
			buf[i] = LASER_TX[i];
		}
    LASER_TX[6] = CRC_TEST(buf)&0x00FF;   //CRC校验低8位
    LASER_TX[7] = (CRC_TEST(buf)&0xFF00) >> 8;   //CRC校验高8位
	  HAL_UART_Transmit(&huart7, LASER_TX,8,0XFF);
	  num = num + 1;
	  if(num >= 4)
		{
			num = 0;
		}
}
/*
CRC-16/MODBUS效验算法
*/
unsigned short CRC_TEST(uint8_t buff[])
{
  unsigned short tmp = 0xffff;
  for (int n = 0; n < 6; n++) 
	{/*此处的6 -- 要校验的位数为6个*/
    tmp = buff[n] ^ tmp;
    for (int i = 0; i < 8; i++) 
		{  /*此处的8 -- 指每一个char类型有8bit，每bit都要处理*/
      if (tmp & 0x01)
		  {
        tmp = tmp >> 1;
        tmp = tmp ^ 0xa001;
      }
      else 
			{
        tmp = tmp >> 1;
      }
    }
   }
	 return tmp;
}

void LASER_BARRIER_UPDATE(void)
{
/****************
激光未接，后续恢复
*****************/
//    uint8_t i=0;
//    /*多方位障碍物判断*/
//    //X+
//    if(LASER.laser_value[0]<Barrier_Distance_XY||LASER.laser_value[1]<Barrier_Distance_XY)
//    {
//        //X+方向上有障碍物
//        LASER.barrier_state.barrier_xyq[0]=1;
//    }
//    else
//    {
//        LASER.barrier_state.barrier_xyq[0]=0;
//    }
//    if(LASER.laser_value[2]<Barrier_Distance_XY||LASER.laser_value[3]<Barrier_Distance_XY)
//    {
//        //Y-方向上有障碍物
//        LASER.barrier_state.barrier_xyq[1]=1;
//    }
//    else
//    {
//        LASER.barrier_state.barrier_xyq[1]=0;
//    }
//    if(LASER.laser_value[4]<Barrier_Distance_XY||LASER.laser_value[5]<Barrier_Distance_XY)
//    {
//        //X-方向上有障碍物
//        LASER.barrier_state.barrier_xyq[2]=1;
//    }
//    else
//    {
//        LASER.barrier_state.barrier_xyq[2]=0;
//    }
//    if(LASER.laser_value[6]<Barrier_Distance_XY||LASER.laser_value[7]<Barrier_Distance_XY)
//    {
//        //Y+方向上有障碍物
//        LASER.barrier_state.barrier_xyq[3]=1;
//    }
//    else
//    {
//        LASER.barrier_state.barrier_xyq[3]=0;
//    }
//    //第一象限有障碍
//    if(LASER.laser_value[11]<Barrier_Distance_Q)
//    {
//        LASER.barrier_state.barrier_xyq[4]=1;
//        LASER.barrier_state.laser_bar_quard=LASER_QUADRANT1_BARRIER;
//				//Q1
//        LASER.barrier_state.barrier_dis[4]=LASER.laser_value[11];
//    }
//    else
//    {
//        LASER.barrier_state.barrier_xyq[4]=0;
//    }
//    //第二象限上有障碍物
//    if(LASER.laser_value[9]<Barrier_Distance_Q)
//    {
//        LASER.barrier_state.barrier_xyq[5]=1;
//        LASER.barrier_state.laser_bar_quard=LASER_QUADRANT2_BARRIER;
//			  //Q2
//				LASER.barrier_state.barrier_dis[5]=LASER.laser_value[9];
//    }
//    else
//    {
//        LASER.barrier_state.barrier_xyq[5]=0;
//    }
//    //第三象限有障碍
//    if(LASER.laser_value[8]<Barrier_Distance_Q)
//    {
//        LASER.barrier_state.barrier_xyq[6]=1;
//        LASER.barrier_state.laser_bar_quard=LASER_QUADRANT3_BARRIER;
//			  //Q3
//				LASER.barrier_state.barrier_dis[6]=LASER.laser_value[8];
//    }
//    else
//    {
//        LASER.barrier_state.barrier_xyq[6]=0;
//    }
//    //第四象限有障碍
//    if(LASER.laser_value[10]<Barrier_Distance_Q)
//    {
//        LASER.barrier_state.barrier_xyq[7]=1;
//        LASER.barrier_state.laser_bar_quard=LASER_QUADRANT4_BARRIER;
//				//Q4
//				LASER.barrier_state.barrier_dis[7]=LASER.laser_value[10];
//    }
//    else
//    {
//        LASER.barrier_state.barrier_xyq[7]=0;
//    }
//    if(LASER.barrier_state.barrier_xyq[4]!=1&&LASER.barrier_state.barrier_xyq[5]!=1&&LASER.barrier_state.barrier_xyq[6]!=1&&LASER.barrier_state.barrier_xyq[7]!=1)
//    {
//        LASER.barrier_state.laser_bar_quard=NO_QBARRIER;
//    }
//    //如果不是工作在无障碍模式下
//    if(LASER.barrier_state.laser_mode==BARRIER_MODE)
//    {
//        /*在避障模式下，根据当前行动方向判断避障模式*/
//        switch(TRACK.FINAL_DIR)
//        {
//            case NO_DIR:
//            {

//            }
//            break;
//            case Xplus_DIR:
//            {
//                //前方50cm有障碍物
//                if(LASER.barrier_state.barrier_xyq[0]==1)
//                {
//                    LASER.barrier_state.laser_bar_xy=LASER_Xplus_BARRIER;
//										if(LASER.laser_value[0]<LASER.laser_value[1])
//										{
//											LASER.barrier_state.barrier_dis[0]=LASER.laser_value[0];
//										}
//										else 
//										{
//											LASER.barrier_state.barrier_dis[0]=LASER.laser_value[1];
//										}
//                }
//                else
//                {
//                    LASER.barrier_state.laser_bar_xy=NO_XYBARRIER;
//                }
//                
//            }
//            break;
//            case Yplus_DIR:
//            {
//                //前方50cm有障碍物
//                if(LASER.barrier_state.barrier_xyq[3]==1)
//                {
//                    LASER.barrier_state.laser_bar_xy=LASER_Yplus_BARRIER;
//										//Y+
//										if(LASER.laser_value[6]<LASER.laser_value[7])
//										{
//											LASER.barrier_state.barrier_dis[1]=LASER.laser_value[6];
//										}
//										else 
//										{
//											LASER.barrier_state.barrier_dis[1]=LASER.laser_value[7];
//										}
//                }
//                else
//                {
//                    LASER.barrier_state.laser_bar_xy=NO_XYBARRIER;
//                }
//            }
//            break;
//            case Xminus_DIR:
//            {
//                //前方50cm有障碍物
//                if(LASER.barrier_state.barrier_xyq[2]==1)
//                {
//                    LASER.barrier_state.laser_bar_xy=LASER_Xminus_BARRIER;
//										if(LASER.laser_value[4]<LASER.laser_value[5])
//										{
//											LASER.barrier_state.barrier_dis[2]=LASER.laser_value[4];
//										}
//										else 
//										{
//											LASER.barrier_state.barrier_dis[2]=LASER.laser_value[5];
//										}
//                }
//                else
//                {
//                    LASER.barrier_state.laser_bar_xy=NO_XYBARRIER;
//                }
//            }
//            break;
//            case Yminus_DIR:
//            {
//                //前方50cm有障碍物
//                if(LASER.barrier_state.barrier_xyq[1]==1)
//                {
//                    LASER.barrier_state.laser_bar_xy=LASER_Yminus_BARRIER;
//										if(LASER.laser_value[2]<LASER.laser_value[3])
//										{
//											LASER.barrier_state.barrier_dis[3]=LASER.laser_value[2];
//										}
//										else 
//										{
//											LASER.barrier_state.barrier_dis[3]=LASER.laser_value[3];
//										}
//										
//                }
//                else
//                {
//                    LASER.barrier_state.laser_bar_xy=NO_XYBARRIER;
//                }
//            }
//            break;
//        }
				
				
				
				
				
				
/***************下面本来就没用的***************/					
				
				
				
				
				
				
				
	
    //     /*判断XY方向上的障碍*/
    //     //x+方向有障碍
    //     if(LASER.laser_value[0]<Barrier_Distance_XY||LASER.laser_value[1]<Barrier_Distance_XY)
    //     {
    //         LASER.barrier_state.laser_bar_xy=LASER_Xplus_BARRIER;
    //     }
    //     //Y-方向有障碍
    //     else if(LASER.laser_value[2]<Barrier_Distance_XY||LASER.laser_value[3]<Barrier_Distance_XY)
    //     {
    //         LASER.barrier_state.laser_bar_xy=LASER_Yminus_BARRIER;
    //     }
    //     //X-方向有障碍
    //     else if(LASER.laser_value[4]<Barrier_Distance_XY||LASER.laser_value[5]<Barrier_Distance_XY)
    //     {
    //         LASER.barrier_state.laser_bar_xy=LASER_Xminus_BARRIER;
    //     }
    //     //Y+方向有障碍
    //     else if(LASER.laser_value[6]<Barrier_Distance_XY||LASER.laser_value[7]<Barrier_Distance_XY)
    //     {
    //         LASER.barrier_state.laser_bar_xy=LASER_Yplus_BARRIER;
    //     }
		
	// 	//如果即将要碰到障碍物
	// 	  else if(LASER.laser_value[0]<Barrier_Distance||LASER.laser_value[1]<Barrier_Distance)
    //     {
    //         LASER.barrier_state.laser_bar_xy=PRE_Xplus_BARRIER;
    //     }
    //     //Y-方向有障碍
    //     else if(LASER.laser_value[2]<Barrier_Distance||LASER.laser_value[3]<Barrier_Distance)
    //     {
    //         LASER.barrier_state.laser_bar_xy=PRE_Yplus_BARRIER;
    //     }
    //     //X-方向有障碍
    //     else if(LASER.laser_value[4]<Barrier_Distance||LASER.laser_value[5]<Barrier_Distance)
    //     {
    //         LASER.barrier_state.laser_bar_xy=PRE_Xminus_BARRIER;
    //     }
    //     //Y+方向有障碍
    //     else if(LASER.laser_value[6]<Barrier_Distance||LASER.laser_value[7]<Barrier_Distance)
    //     {
    //         LASER.barrier_state.laser_bar_xy=PRE_Yminus_BARRIER;
    //     }
    //     else
    //     {
    //         LASER.barrier_state.laser_bar_xy=NO_XYBARRIER;
    //     } 
    //     /*判断斜角方向上的障碍*/
    //     //第一象限有障碍
    //     if(LASER.laser_value[8]<Barrier_Distance_Q)
    //     {
    //         LASER.barrier_state.laser_bar_quard=LASER_QUADRANT3_BARRIER;
    //     }
    //     //第四象限有障碍
    //     else if(LASER.laser_value[9]<Barrier_Distance_Q)
    //     {
    //         LASER.barrier_state.laser_bar_quard=LASER_QUADRANT2_BARRIER;
    //     }
    //     //第三象限有障碍
    //     else if(LASER.laser_value[10]<Barrier_Distance_Q)
    //     {
    //         LASER.barrier_state.laser_bar_quard=LASER_QUADRANT4_BARRIER;
    //     }
    //     //第二象限有障碍
    //     else if(LASER.laser_value[11]<Barrier_Distance_Q)
    //     {
    //         LASER.barrier_state.laser_bar_quard=LASER_QUADRANT1_BARRIER;
    //     }
    //     else
    //     {
    //         LASER.barrier_state.laser_bar_quard=NO_QBARRIER;
    //     } 
    // }
    // //如果工作在无障碍模式下
    // else 
    // {
    //     LASER.barrier_state.laser_bar_xy=NO_XYBARRIER;
    //     LASER.barrier_state.laser_bar_quard=NO_QBARRIER;
    // }
	//}
}

