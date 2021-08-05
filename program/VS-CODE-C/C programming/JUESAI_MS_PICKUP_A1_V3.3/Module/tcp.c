#include "tcp.h"
#include "string.h"
#include "module_arm.h"

uint8_t tcp_rev_datas[10];
uint8_t tcp_rev_buf[1];

TCP_REV_STA tcp_rev_sta=TCP_START;

uint8_t ESP8266_SEND_SETTING[]={'A','T','+','C','I','P','S','E','N','D','=','0',',','1','7',0X0D,0X0A};
uint8_t ESP8266_RST[]={'A','T','+','R','S','T',0x0D,0x0A};          //复位
uint8_t ESP8266_CIPMUX_SELECT[]={'A','T','+','C','I','P','M','U','X','=','1',0X0D,0X0A}; //开启多连接
uint8_t ESP8266_SERVER_START[]={'A','T','+','C','I','P','S','E','R','V','E','R','=','1',',','8','0','0','0',0X0D,0X0A};//开启服务器

void tcp_send_setting(void)
{
	if(IsConnectedFlag)//如果连接正常
	  HAL_UART_Transmit(&huart8,ESP8266_SEND_SETTING,sizeof(ESP8266_SEND_SETTING),0x01);
}

void tcp_init(void)
{
  HAL_UART_Transmit(&huart8,ESP8266_RST,sizeof(ESP8266_RST),0X01);//复位esp8266
  HAL_Delay(1000);
	HAL_UART_Transmit(&huart8,ESP8266_CIPMUX_SELECT,sizeof(ESP8266_CIPMUX_SELECT),0X10); //开启多连接
  HAL_Delay(1000);
	HAL_UART_Transmit(&huart8,ESP8266_SERVER_START,sizeof(ESP8266_SERVER_START),0X01);//开启服务器
  HAL_Delay(2000);
	LED_R_ON();
	HAL_Delay(500);
	LED_R_OFF();
	HAL_Delay(500);
	LED_R_ON();
	HAL_Delay(500);
	LED_R_OFF();
	HAL_Delay(500);
	HAL_UART_Receive_IT(&huart8,tcp_rev_buf,1);
	//tcp_feedback(5);
	
}

uint8_t TCPRevDataHandler(uint8_t rdata)
{
	static uint8_t temp=0,sum=0,temp_bit=0;
	switch(tcp_rev_sta)
	{
		case TCP_START:
	    if(rdata==0x55)
			{
		    tcp_rev_datas[temp_bit]=rdata;
			  tcp_rev_sta++;
				temp_bit++;
			}
			else
			{
				tcp_rev_sta=TCP_START;
				temp_bit=0;
			}
			break;
		case TCP_HEADR1:
			if(rdata==0x55)
			{
		    tcp_rev_datas[temp_bit]=rdata;
			  tcp_rev_sta++;
				temp_bit++;
			}
			else
			{
				tcp_rev_sta=TCP_START;
				temp_bit=0;
			}
			break;
		case TCP_HEADR2:
		  tcp_rev_datas[temp_bit]=rdata;
			tcp_rev_sta++;
		  temp_bit++;
			break;
    case TCP_ID:
			if(rdata>2)
			{
				tcp_rev_sta=TCP_START;
			  temp_bit=0;
			}
			else
			{
				tcp_rev_datas[temp_bit]=rdata;
				tcp_rev_sta++;
				temp_bit++;
				temp=0;
			}
			break;
    case TCP_LEN:
      tcp_rev_datas[temp_bit]=rdata;
		  temp++;
		  temp_bit++;
		  if(temp==tcp_rev_datas[3])
		  {
		    tcp_rev_sta++;
		    sum=0;
			}
			break;
    case TCP_DATAS:
			sum+=tcp_rev_datas[3]+tcp_rev_datas[2];
      for(temp=0;temp<tcp_rev_datas[3];temp++)
        sum+=tcp_rev_datas[4+temp];
		  tcp_rev_sta=TCP_START;
      if(sum==rdata)
			{
				tcp_rev_datas[temp_bit]=rdata;
				temp_bit=0;
				return 0;
			}       
      break;
		default:
      break;				
	}
	return 1;
}

void TCPRevDatasHandler(uint8_t *rdatas)
{
	switch(rdatas[2])
	{
		case 0x02://接收心跳包
			HeartBeat=0;
		  break;
		case 0x00:
			if(rdatas[4]==0x01)
			  LED_G_ON();
			else
				LED_G_OFF();
		  break;
		case 0x01:
			arm.targetPos_x=rdatas[4];
		  arm.targetPos_y=rdatas[5];
		  break;
		case 0x03:
			arm.target.touch_target_switch=1;
			break;
		case 0x04:
			OpenmvThresholdMeasure(rdatas[4]);
	    arm.state=ACTION_READ_THRESHOLD;
		  break;
		case 0x05:
			OpenmvScanBallStartStop(rdatas[4]);
		  break;
		default:
			break;
	}
}
