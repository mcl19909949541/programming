#include "protocal.h"
#include "usart.h"
#include "can.h"
/**
激光数据接收状态机
**/

RECEIVE_STATE  receive_state = {
   RECEIVE_HEADER1,  //接收数据帧头1
	 0,                //接收数据设备参数数量为0
	0,                //接收数据帧子数据设备ID号已计算的校验和为0
};

/**
  
  */
DATA_PACK   data_pack = {
	INVALID,          //数据设备指令有效性默认为无效
	0X55,             //数据设备ID号默认为0x55
	AX16_ORDER_NONE,  //数据设备指令默认为无操作指令
	0,                //数据包长度默认为0
	{0},              //数据设备参数默认为无
};

/*******************************************************************************
检查接收数据设备指令函数
data：需要接受检查的数据设备指令
返回：合法->输入的数据设备指令，非法->0x55
*******************************************************************************/
AX16_INSTRUCTION  Check_AX16_Instructions(uint8_t data)
{
   if(   data == AX16_ORDER_PING
      || data == AX16_ORDER_READ
      || data == AX16_ORDER_WRITE
      || data == AX16_ORDER_REG_WRITE
      || data == AX16_ORDER_ACTION
      || data == AX16_ORDER_RESET
      || data == AX16_ORDER_SYNC_WRITE)
   {
      return   (AX16_INSTRUCTION)data;
   }
   else
   {
      return   (AX16_INSTRUCTION)0X55;
   }
}

uint8_t check_address(uint8_t data)
{
	if(data == 0x00 
		|| data == 0x01 
		|| data == 0x02
		|| data == 0x03
		|| data == 0x04
		|| data == 0x05
		|| data == 0x06
		|| data == 0x07
		|| data == 0x08
		|| data == 0x09
		|| data == 0x10
		|| data == 0x11
		)return 1;
	else 
	{
		return 0;
	}
}



/*******************************************************************************
状态机CAN接收数据判断函数
data：通过CAN接收到的数据
返回：接收数据帧分析错误的PACK_ANALIZE_RETURN_VALUE类型
*******************************************************************************/
void  Pack_Analize(uint8_t data)
{
   switch(receive_state.type)                                        //选择接收数据 帧在通讯协议中的类型进行判断
   {
		 case  RECEIVE_HEADER1:                                         //如果为接收数据帧头1则执行以下操作：
      {
         if(data == PACK_HEADER1)                                    //如果接收到的数据等于通讯协议数据帧头1
         {
            receive_state.count_param = 0;                           //接收数据设备参数数量清零
            receive_state.type = RECEIVE_HEADER2;                    //接收数据帧在通讯协议中的类型跳置下一个，接收数据帧头2
         }
         else
         {
         }
         break;                                                      //跳出状态机结束此帧数据判断
      }
      
		 case  RECEIVE_HEADER2:                                         //如果为接收数据帧头2则执行以下操作
      {
         if(data == PACK_HEADER2)                                    //如果接收数据等于通讯协议数据帧头2
         {
            receive_state.type = RECEIVE_ID;                         //接收数据帧在通讯协议中的类型跳至下一个，接收数据ID号
            receive_state.check = 0;                                 //接收数据帧自数据设备ID号已计算的校验和清零
         }
         else
         {
            receive_state.type = RECEIVE_HEADER1;                       //否则接收数据帧在通讯协议中的类型返回接收数据帧头1，重新接收数据
         }
				 break;                                                      //跳出状态机结束此帧数据判断
      }
      
		 case  RECEIVE_ID:                                              //如果为接收数据设备ID号则执行以下操作
      {
				if(check_address(data))                                      //如果接收数据设备ID号等于电机控制板的软件设定串口总线地址
         {
            data_pack.id = data;                                     //将接受的数据存入数据设备ID号
            receive_state.check += data;                             //计算校验和
            receive_state.type = RECEIVE_LENGTH;                     //接收数据帧在通讯协议中的类型跳至下一个，接收数据包长度
         }
         else
         {
            receive_state.type = RECEIVE_HEADER1;                    //否则接收数据帧在通讯协议中的类型返回接收数据帧头1，重新接收数据
         }
         break;                                                      //跳出状态机结束此帧数据判断
      }
      
		 case  RECEIVE_LENGTH:                                          //如果为接收数据包长度则执行以下操作
      {
         if(data >= MIN_DATA_LENGTH)                                 //如果接收数据包长度大于或等于最小数据包长度
         {
            data_pack.length = data;                                 //将接受的数据存入数据包长度
            receive_state.check += data;                             //计算校验和
            receive_state.type = RECEIVE_INSTRUCTION;                //接收数据帧在通讯协议中的类型跳至下一个，接收数据设备指令
         }
         else
         {
            receive_state.type = RECEIVE_HEADER1;                    //否则接收数据帧在通讯协议中的类型返回接收数据帧头1，重新接收数据
         }
         break;                                                      //跳出状态机结束此帧数据判断
      }
      
		 case  RECEIVE_INSTRUCTION:                                       //如果为接收数据设备指令则执行以下操作：
      {                                                               //读还是写
         if(Check_AX16_Instructions(data) != 0X55)                   
         {
            data_pack.instruction = Check_AX16_Instructions(data);   
            receive_state.check += data; 					                    //计算校验和
            if((data_pack.length -3) != 0)                                
            {
               receive_state.type = RECEIVE_PARAM;                   //接收数据帧在通讯协议中的类型跳至下一个，接收数据设备参数
            }
            else
            {
               receive_state.type = RECEIVE_CHECKSUM;                //主控向灰度或激光发送数据时没有参数
            }                                                        //只需要读命令不需要参数包
         }
         else
         {
            receive_state.type = RECEIVE_HEADER1;                    //否则接收数据帧在通讯协议中的类型返回接收数据帧头1，重新接收数据
         }
         break;                                                      //跳出状态机结束此帧数据判断
      }
      
		 case  RECEIVE_PARAM:                                           //如果为接收数据设备参数则执行以下操作：
      {
         data_pack.param[receive_state.count_param] = data;          //
         receive_state.check += data;  				                       //计算校验和
         receive_state.count_param++;				
         if(receive_state.count_param == data_pack.length - 3)       
         {
            receive_state.type = RECEIVE_CHECKSUM;                   //接收数据帧在通讯协议中的类型跳至下一个，接收数据校验和
         }
         break;                                                      //跳出状态机结束此帧数据判断
      }
      
		 case  RECEIVE_CHECKSUM:                                        //如果为接收数据校验和则执行以下操作：
      {  
				 /**与report_pack中的协议对应**/
         receive_state.check = ((receive_state.check) & 0XFF);      //
				 if(receive_state.check == data)                             //如果计算出的校验和等于接收数据校验和
         {
						Receive_Value();
            receive_state.type = RECEIVE_HEADER1;                    //接收数据帧在通讯协议中的类型返回接收数据帧头1，重新接收数据
         }
         else
         {
            receive_state.type = RECEIVE_HEADER1;                    //接收数据帧在通讯协议中的类型返回接收数据帧头1，重新接收数据
         }
         break;                                                      //跳出状态机结束此帧数据判断
      }
      
		 default:                                                       //如过为其他情况
      {
				break;                                                      //跳出状态机结束此帧数据判断
      }
   }
}


void Receive_Value(void)
{
		int16_t temp=0;
	 /**此处进行过修改，主要是数组数据对应**/
		temp = temp | data_pack.param[0];//高八位
		LASER.laser_value[data_pack.id] = ( temp << 8) | data_pack.param[1];//低八位
}

