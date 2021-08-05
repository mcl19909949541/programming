#ifndef  _PROTOCAL_H
#define  _PROTOCAL_H

#include "stm32f4xx_hal.h"

#define  PACK_HEADER1         0X55  //宏定义通讯协议数据帧头1为0X55
#define  PACK_HEADER2         0X55  //宏定义通讯协议数据帧头20X55

#define  MIN_DATA_LENGTH     3     //宏定义最小数据长度3

/**
  *定义枚举类型TAG_PACK_VALIDITY,显示接收数据设备指令的有效性-------------------
  *定义TAG_PACK_VALIDITY类型的别名PACK_VALIDITY---------------------------------
  */
typedef  enum  TAG_PACK_VALIDITY
{
   VALID,         //接收设备数据指令
   INVALID,       //接收数据设备指令无效
}PACK_VALIDITY;   //TAG_PACK_VALIDITY梗靡PACK_VALIDITY

/**
*定义枚举类型TAG_PACK_RECEIVE_TYPE,显示接收数据帧在通讯协议的类型 -----------
  *隅砱TAG_PACK_RECEIVE_TYPE濬倰腔梗靡PACK_RECEIVE_TYPE-------------------------
  */
typedef  enum  TAG_PACK_RECEIVE_TYPE
{
   RECEIVE_HEADER1,        //接收数据帧头1:0X55
   RECEIVE_HEADER2,        //接收数据帧头2:0X55
   RECEIVE_ID,             //接收数据设备ID号
   RECEIVE_LENGTH,         //接收数据包长度
   RECEIVE_INSTRUCTION,    //接收数据设备指令
   RECEIVE_PARAM,          //接收数据设备参数
   RECEIVE_CHECKSUM,       //接收数据校验和
}PACK_RECEIVE_TYPE;        //TAG_PACK_RECEIVE_TYPE别名PACK_RECEIVE_TYPE

/**
  *定义结构体TAG_RECEIVE_STATE,显示接收数据帧的状态-----------------------------
  *定义TAG_RECEIVE_STATE结构体的别名RECEIVE_STATE-------------------------------
  */
typedef  struct   TAG_RECEIVE_STATE
{
   PACK_RECEIVE_TYPE type;     //接收数据帧在通讯协议中的类型
   uint8_t   count_param;      //接收数据帧数据设备参数的数量
   uint32_t   check;           //接收数据帧自数据设备ID号已计算的校验和
}RECEIVE_STATE;                //TAG_RECEIVE_STATE别名RECEIVE_STATE

/**
  *定义枚举类型TAG_AX16_INSTRUCTION,指定通讯协议接收数据设备指令----------------
  *定义TAG_AX16_INSTRUCTION类型的别名fAX16_INSTRUCTION---------------------------
  */
typedef  enum  TAG_AX16_INSTRUCTION
{
    AX16_ORDER_PING            = 0x01,     //
	AX16_ORDER_READ              = 0x02,     //
	AX16_ORDER_WRITE             = 0x03,     //
	AX16_ORDER_REG_WRITE         = 0x04,     //
	AX16_ORDER_ACTION            = 0x05,     //
	AX16_ORDER_RESET             = 0x06,     //
	AX16_ORDER_DIGITAL_RESET     = 0x07,     // 
	AX16_ORDER_SYNC_WRITE        = 0x83,     // 
	AX16_ORDER_NONE     	       = 0xff,     //

}AX16_INSTRUCTION;                        //TAG_AX16_INSTRUCTION梗靡AX16_INSTRUCTION

/**
  *定义结构体TAG_DATA_PACK与指向TAG_DATA_PACK类型的指针P_DATA_PACK----------
  *显示当前已接受数据的属性-----------------------------------------------------
  *定义TAG_DATA_PACK结构体的别名DATA_PACK---------------------------------------
  */
typedef  struct   TAG_DATA_PACK
{
   PACK_VALIDITY  pack_validity;       //数据设备指令的有效性
   uint8_t id;                         //数据设备ID号
   AX16_INSTRUCTION  instruction;      //数据设备指令
   uint8_t length;                     //数据包长度
   uint8_t param[156];                 //数据设备参数
}DATA_PACK, *P_DATA_PACK;              //TAG_DATA_PACK别名DATA_PACK

/**
  *定义枚举类型TAG_PACK_ANALIZE_RETURN,显示接收数据帧分析错误时的错误类型-------
  *定义TAG_PACK_ANALIZE_RETURN类型的别名PACK_ANALIZE_VALUE----------------------
  */
typedef  enum  TAG_PACK_ANALIZE_RETURN
{
   ANALIZE_OK,                //接收数据无误
   ANALIZE_HEADER1_ERROR,     //接收数据帧头1错误
   ANALIZE_HEADER2_ERROR,     //接收数据帧头2错误
   ANALIZE_INVALID_ID,        //接收数据设备ID号无效
   ANALIZE_LENGHT_ERROR,      //接收数据包长度错误
   ANALIZE_INSTRUCTION_ERROR, //接收数据包设备指令错误
   ANALIZE_CHECK_ERROR,       //接收数据校验和错误
   ANALIZE_UNKNOW_ERROR,      //接收数据未知错误
}PACK_ANALIZE_RETURN_VALUE;   //TAG_PACK_ANALIZE_RETURN别名PACK_ANALIZE_VALUE

AX16_INSTRUCTION           Check_AX16_Instructions(uint8_t data);   //检查接收数据设备指令函数
void  Pack_Analize(uint8_t data);              //状态机串口接收数据判断函数

void  Receive_Value(void);

#endif

