#include "openmv.h"
#include "tcp.h"

uint8_t openmv_rev_buf[1];
uint8_t openmv_rev_datas[6];
uint8_t openmv_send_buf[4]={0xef,0xef,0x00,0x00};

OPENMV_REV_STA openmv_rev_sta=OPENMV_START;

void OpenmvInit(void)
{
	MX_USART6_UART_Init();
	HAL_UART_Receive_IT(&huart6,openmv_rev_buf,1);
}

void OpenmvThresholdMeasure(uint8_t color_select)
{
	openmv_send_buf[2]=3;
  openmv_send_buf[3]=color_select;//1:测定红色，2：测定蓝色，3：测定黄色
	HAL_UART_Transmit(&huart6,openmv_send_buf,4,0x01);
}

void OpenmvScanBallStartStop(uint8_t _switch)//开始追踪小球 ,_switch=1,则开始拨小球，_switch=0，停止拨球
{
	openmv_send_buf[2]=1;
	openmv_send_buf[3]=_switch;
	HAL_UART_Transmit(&huart6,openmv_send_buf,4,0x01);
}

uint8_t OpenmvRevDataHandler(uint8_t rdata)
{
	static uint8_t temp=0,sum=0,temp_bit=0;
	switch(openmv_rev_sta)
	{
		case OPENMV_START:
	    if(rdata==0x56)
			{
		    openmv_rev_datas[temp_bit]=rdata;
			  openmv_rev_sta++;
				temp_bit++;
			}
			else
			{
				openmv_rev_sta=OPENMV_START;
				temp_bit=0;
			}
			break;
		case OPENMV_HEADR1:
			if(rdata==0x56)
			{
		    openmv_rev_datas[temp_bit]=rdata;
			  openmv_rev_sta++;
				temp_bit++;
			}
			else
			{
				openmv_rev_sta=OPENMV_START;
				temp_bit=0;
			}
			break;
		case OPENMV_HEADR2:
		  openmv_rev_datas[temp_bit]=rdata;
			openmv_rev_sta++;
		  temp_bit++;
			break;
    case OPENMV_ID:
			if(rdata>2)
			{
				openmv_rev_sta=OPENMV_START;
			  temp_bit=0;
			}
			else
			{
				openmv_rev_datas[temp_bit]=rdata;
				openmv_rev_sta++;
				temp_bit++;
				temp=0;
			}
			break;
    case OPENMV_LEN:
      openmv_rev_datas[temp_bit]=rdata;
		  temp++;
		  temp_bit++;
		  if(temp==openmv_rev_datas[3])
		  {
		    openmv_rev_sta++;
		    sum=0;
			}
			break;
    case OPENMV_DATAS:
			sum+=openmv_rev_datas[3]+openmv_rev_datas[2];
      for(temp=0;temp<openmv_rev_datas[3];temp++)
        sum+=openmv_rev_datas[4+temp];
		  openmv_rev_sta=OPENMV_START;
      if(sum==rdata)
			{
				openmv_rev_datas[temp_bit]=rdata;
				temp_bit=0;
				return 0;
			}       
      break;
		default:
      break;				
	}
	return 1;
}

void OpenmvRevDatasHandler(uint8_t *rdatas)
{
	switch(rdatas[2])
	{
		case 0x08:
			arm.openmv.is_threshold_got=rdatas[4];
		  break;
		case 0x07:
			arm.openmv.ball_color_got=rdatas[4];
		  break;
		default:
			break;
	}
}

