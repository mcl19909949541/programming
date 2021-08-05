/**
  ******************************************************************************
  * File Name          : CAN.c
  * Description        : This file provides code for the configuration
  *                      of the CAN instances.
  ******************************************************************************
  ** This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * COPYRIGHT(c) 2019 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "can.h"

/* USER CODE BEGIN 0 */
//CAN1过滤器初始化
CAN_FilterTypeDef  hcan1_FilerConf;
//CAN2过滤器初始化
CAN_FilterTypeDef  hcan2_FilerConf;
//CAN1发送数据结构体
CAN_TX CAN1_TXMSG;
//CAN1接收数据结构体
CAN_RX CAN1_RXMSG;
//CAN2发送数据结构体
CAN_TX CAN2_TXMSG;
//CAN2接收数据结构体
CAN_RX CAN2_RXMSG;
//CAN测试数组
char can_tx[8];
char can_rx[8];
/* USER CODE END 0 */

CAN_HandleTypeDef hcan1;
CAN_HandleTypeDef hcan2;

/* CAN1 init function */
void MX_CAN1_Init(void)
{

  hcan1.Instance = CAN1;
  hcan1.Init.Prescaler = 3;
  hcan1.Init.Mode = CAN_MODE_NORMAL;
  hcan1.Init.SyncJumpWidth = CAN_SJW_1TQ;//4
  hcan1.Init.TimeSeg1 = CAN_BS1_10TQ;//7
  hcan1.Init.TimeSeg2 = CAN_BS2_3TQ;//6
  hcan1.Init.TimeTriggeredMode = DISABLE;
  hcan1.Init.AutoBusOff = DISABLE;
  hcan1.Init.AutoWakeUp = DISABLE;
  hcan1.Init.AutoRetransmission = DISABLE;
  hcan1.Init.ReceiveFifoLocked = DISABLE;
  hcan1.Init.TransmitFifoPriority = DISABLE;
  if (HAL_CAN_Init(&hcan1) != HAL_OK)
  {
    Error_Handler();
  }
  //CAN1过滤器配置
  hcan1_FilerConf.FilterIdHigh=0x0000;
  hcan1_FilerConf.FilterIdLow=0x0000;
  hcan1_FilerConf.FilterMaskIdHigh=0x0000;
  hcan1_FilerConf.FilterMaskIdLow=0x0000;
  //过滤器0关联到FIFO0
  hcan1_FilerConf.FilterFIFOAssignment=CAN_FILTER_FIFO0;
  hcan1_FilerConf.FilterBank=0;
  //设置为32位模式
  hcan1_FilerConf.FilterScale=CAN_FILTERSCALE_32BIT;
  //标识符屏蔽模式
  hcan1_FilerConf.FilterMode=CAN_FILTERMODE_IDMASK;
  hcan1_FilerConf.FilterActivation=ENABLE;
  hcan1_FilerConf.SlaveStartFilterBank=14;
  //初始化过滤器
	if(HAL_CAN_ConfigFilter(&hcan1,&hcan1_FilerConf)!=HAL_OK) 
	{
    Error_Handler();
  }
  //打开CAN1
  if(HAL_CAN_Start(&hcan1)!=HAL_OK) 
	{
    Error_Handler();
  }
  //打开CAN1接收中断
  if(HAL_CAN_ActivateNotification(&hcan1,CAN_IT_RX_FIFO0_MSG_PENDING|CAN_IT_RX_FIFO1_MSG_PENDING)!=HAL_OK) 
	{
    Error_Handler();
  }
}
/* CAN2 init function */
void MX_CAN2_Init(void)
{

  hcan2.Instance = CAN2;
  hcan2.Init.Prescaler = 3;
  hcan2.Init.Mode = CAN_MODE_NORMAL;
  hcan2.Init.SyncJumpWidth = CAN_SJW_1TQ;
  hcan2.Init.TimeSeg1 = CAN_BS1_10TQ;
  hcan2.Init.TimeSeg2 = CAN_BS2_3TQ;
  hcan2.Init.TimeTriggeredMode = DISABLE;
  hcan2.Init.AutoBusOff = DISABLE;
  hcan2.Init.AutoWakeUp = DISABLE;
  hcan2.Init.AutoRetransmission = DISABLE;
  hcan2.Init.ReceiveFifoLocked = DISABLE;
  hcan2.Init.TransmitFifoPriority = DISABLE;
  if (HAL_CAN_Init(&hcan2) != HAL_OK)
  {
    Error_Handler();
  }
  //CAN2过滤器配置
  hcan2_FilerConf.FilterIdHigh=0x0000;
  hcan2_FilerConf.FilterIdLow=0x0000;
  hcan2_FilerConf.FilterMaskIdHigh=0x0000;
  hcan2_FilerConf.FilterMaskIdLow=0x0000;
  //过滤器0关联到FIFO0
  hcan2_FilerConf.FilterFIFOAssignment=CAN_FILTER_FIFO0;
  //过滤器号与CAN1设置的slavestartbank对应
  hcan2_FilerConf.FilterBank=14;
  //设置为32位模式
  hcan2_FilerConf.FilterScale=CAN_FILTERSCALE_32BIT;
  //标识符屏蔽模式
  hcan2_FilerConf.FilterMode=CAN_FILTERMODE_IDMASK;
  //激活过滤器
  hcan2_FilerConf.FilterActivation=ENABLE;
  hcan2_FilerConf.SlaveStartFilterBank=14;
  //初始化CAN2过滤器
	if(HAL_CAN_ConfigFilter(&hcan2,&hcan2_FilerConf)!=HAL_OK) 
	{
    Error_Handler();
  }
  //打开CAN2
  if(HAL_CAN_Start(&hcan2)!=HAL_OK) 
	{
    Error_Handler();
  }
  //打开CAN2接收中断
  if(HAL_CAN_ActivateNotification(&hcan2,CAN_IT_RX_FIFO0_MSG_PENDING|CAN_IT_RX_FIFO1_MSG_PENDING)!=HAL_OK) 
	{
    Error_Handler();
  }
}

static uint32_t HAL_RCC_CAN1_CLK_ENABLED=0;

void HAL_CAN_MspInit(CAN_HandleTypeDef* canHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(canHandle->Instance==CAN1)
  {
  /* USER CODE BEGIN CAN1_MspInit 0 */

  /* USER CODE END CAN1_MspInit 0 */
    /* CAN1 clock enable */
    HAL_RCC_CAN1_CLK_ENABLED++;
    if(HAL_RCC_CAN1_CLK_ENABLED==1){
      __HAL_RCC_CAN1_CLK_ENABLE();
    }
  
    __HAL_RCC_GPIOD_CLK_ENABLE();
    /**CAN1 GPIO Configuration    
    PD0     ------> CAN1_RX
    PD1     ------> CAN1_TX 
    */
    GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF9_CAN1;
    HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

    /* CAN1 interrupt Init */
    HAL_NVIC_SetPriority(CAN1_RX0_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(CAN1_RX0_IRQn);
    HAL_NVIC_SetPriority(CAN1_RX1_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(CAN1_RX1_IRQn);
  /* USER CODE BEGIN CAN1_MspInit 1 */

  /* USER CODE END CAN1_MspInit 1 */
  }
  else if(canHandle->Instance==CAN2)
  {
  /* USER CODE BEGIN CAN2_MspInit 0 */

  /* USER CODE END CAN2_MspInit 0 */
    /* CAN2 clock enable */
    __HAL_RCC_CAN2_CLK_ENABLE();
    HAL_RCC_CAN1_CLK_ENABLED++;
    if(HAL_RCC_CAN1_CLK_ENABLED==1){
      __HAL_RCC_CAN1_CLK_ENABLE();
    }
  
    __HAL_RCC_GPIOB_CLK_ENABLE();
    /**CAN2 GPIO Configuration    
    PB12     ------> CAN2_RX
    PB13     ------> CAN2_TX 
    */
    GPIO_InitStruct.Pin = GPIO_PIN_12|GPIO_PIN_13;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF9_CAN2;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    /* CAN2 interrupt Init */
    HAL_NVIC_SetPriority(CAN2_RX0_IRQn, 1, 0);
    HAL_NVIC_EnableIRQ(CAN2_RX0_IRQn);
    HAL_NVIC_SetPriority(CAN2_RX1_IRQn, 1, 0);
    HAL_NVIC_EnableIRQ(CAN2_RX1_IRQn);
  /* USER CODE BEGIN CAN2_MspInit 1 */

  /* USER CODE END CAN2_MspInit 1 */
  }
}

void HAL_CAN_MspDeInit(CAN_HandleTypeDef* canHandle)
{

  if(canHandle->Instance==CAN1)
  {
  /* USER CODE BEGIN CAN1_MspDeInit 0 */

  /* USER CODE END CAN1_MspDeInit 0 */
    /* Peripheral clock disable */
    HAL_RCC_CAN1_CLK_ENABLED--;
    if(HAL_RCC_CAN1_CLK_ENABLED==0){
      __HAL_RCC_CAN1_CLK_DISABLE();
    }
  
    /**CAN1 GPIO Configuration    
    PD0     ------> CAN1_RX
    PD1     ------> CAN1_TX 
    */
    HAL_GPIO_DeInit(GPIOD, GPIO_PIN_0|GPIO_PIN_1);

    /* CAN1 interrupt Deinit */
    HAL_NVIC_DisableIRQ(CAN1_RX0_IRQn);
    HAL_NVIC_DisableIRQ(CAN1_RX1_IRQn);
  /* USER CODE BEGIN CAN1_MspDeInit 1 */

  /* USER CODE END CAN1_MspDeInit 1 */
  }
  else if(canHandle->Instance==CAN2)
  {
  /* USER CODE BEGIN CAN2_MspDeInit 0 */

  /* USER CODE END CAN2_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_CAN2_CLK_DISABLE();
    HAL_RCC_CAN1_CLK_ENABLED--;
    if(HAL_RCC_CAN1_CLK_ENABLED==0){
      __HAL_RCC_CAN1_CLK_DISABLE();
    }
  
    /**CAN2 GPIO Configuration    
    PB12     ------> CAN2_RX
    PB13     ------> CAN2_TX 
    */
    HAL_GPIO_DeInit(GPIOB, GPIO_PIN_12|GPIO_PIN_13);

    /* CAN2 interrupt Deinit */
    HAL_NVIC_DisableIRQ(CAN2_RX0_IRQn);
    HAL_NVIC_DisableIRQ(CAN2_RX1_IRQn);
  /* USER CODE BEGIN CAN2_MspDeInit 1 */

  /* USER CODE END CAN2_MspDeInit 1 */
  }
} 

/* USER CODE BEGIN 1 */
//CAN发送函数
//传入参数：CAN初始化结构体，基本id，扩展id，数据长度，数据数组
//返回值：
void CAN_Send_Msg(CAN_HandleTypeDef* canHandle,unsigned int stid,unsigned int extid,unsigned int num,unsigned char *data)
{
	unsigned int i=0;
	CAN_TX can_txmsg={0};
  //将传入参数数据给can发�?�结构体
	can_txmsg.txheader.StdId=stid;
	can_txmsg.txheader.ExtId=extid;
	can_txmsg.txheader.IDE=CAN_ID_STD;
	can_txmsg.txheader.RTR=CAN_RTR_DATA;
	can_txmsg.txheader.DLC=num;
	can_txmsg.txheader.TransmitGlobalTime=DISABLE;
	//将数据存进发送数组里
	for(i=0;i<num;i++)
	{
		can_txmsg.txdata[i]=*(data+i);
	}
  //tx_mailbox
	can_txmsg.txmailbox=0;
	//调用CAN发�?�函�?
  HAL_CAN_AddTxMessage(canHandle,&can_txmsg.txheader,can_txmsg.txdata,&can_txmsg.txmailbox);
  //用于存储测试CAN发�?�数�?
	for(i=0;i<8;i++)
	{
		can_tx[i]=can_txmsg.txdata[i];
	}
}
/* USER CODE END 1 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
