#include "digital_gray16.h"

//顺时针方向
//灰度ID 1——X+方向：USART2
DEF_16DIGITAL_GRAY DIGITAL16_GRAY_1;
//灰度ID 2——Y-方向：USART6
DEF_16DIGITAL_GRAY DIGITAL16_GRAY_2;
//灰度ID3——X-方向：UART7
DEF_16DIGITAL_GRAY DIGITAL16_GRAY_3;
//灰度ID3——Y+方向：UART8
DEF_16DIGITAL_GRAY DIGITAL16_GRAY_4;
//阵列灰度位置偏差值
DEF_GRAY_DIR GRAY_DIR;

//16路灰度初始化
void  DIGITAL16_Init(void)
{
    //赋值ID1——X+
	DIGITAL16_GRAY_1.id = 1;
	//赋值ID2——Y-
	DIGITAL16_GRAY_2.id = 2;
    //赋值ID3——X-
	DIGITAL16_GRAY_3.id = 3;
	//赋值ID2——Y+
	DIGITAL16_GRAY_4.id = 4;
}

/*灰度读值更新*/
uint8_t GRAY_UPDATE_state(void)
{
    //判断是否是第一次进入更新函数
    static uint8_t i=0;
    //1:成功；0：失败
    uint8_t ok;
    uint8_t uart_data=GET_GRAY_COMAND;
    //如果是第一次进入更新函数，进行发送操作
	switch(i)
	{
		case 0:
		{
				HAL_UART_Transmit(&huart2,&uart_data,1,0xffff);
		}
		break;
		case 1:
		{
				HAL_UART_Transmit(&huart6,&uart_data,1,0xffff);
		}
		break;
		case 2:
		{
				HAL_UART_Transmit(&huart7,&uart_data,1,0xffff);
		}
		break;
		case 3:
		{
				HAL_UART_Transmit(&huart8,&uart_data,1,0xffff);
		}
		break;
	}
	i=i+1;
	if(i>=4)
	{
		i=0;
	}
	return ok;
}

/*16路灰度状态和计数函数*/
void DIGITAL_GRAY_ANALYSIS(uint16_t data,uint8_t id)
{
    switch (id)
    {
    case 0x01:
    {
		//保存上一次的值
		DIGITAL16_GRAY_1.digital16_gray_laststate.last_value=DIGITAL16_GRAY_1.digital16_gray_state.value;
		//更新当前的值
		DIGITAL16_GRAY_1.digital16_gray_state.value = data;
		// //黑线计数
    }
    break;
    case 0x02:
    {
		//保存上一次的值
		DIGITAL16_GRAY_2.digital16_gray_laststate.last_value=DIGITAL16_GRAY_2.digital16_gray_state.value;
		//更新当前的值
		DIGITAL16_GRAY_2.digital16_gray_state.value = data;
	
    }
    break;
    case 0x03:
    {
		//保存上一次的值
		DIGITAL16_GRAY_3.digital16_gray_laststate.last_value=DIGITAL16_GRAY_3.digital16_gray_state.value;
		//更新当前的值
		DIGITAL16_GRAY_3.digital16_gray_state.value = data;
    }
    break;
    case 0x04:
    {
        //保存上一次的值
		DIGITAL16_GRAY_4.digital16_gray_laststate.last_value=DIGITAL16_GRAY_4.digital16_gray_state.value;
		//更新当前的值
		DIGITAL16_GRAY_4.digital16_gray_state.value = data;
    }
    break;
    }
}

//清0所有灰度的累计记线
void Reset_Gray_Cnt(void)
{	
	uint8_t i;
	//清零0
	for(i=0;i<=15;i++)
	{
		DIGITAL16_GRAY_1.sum_gray[i] = 0;
	}
	for(i=0;i<=15;i++)
	{
		DIGITAL16_GRAY_2.sum_gray[i] = 0;
	}
	for(i=0;i<=15;i++)
	{
		DIGITAL16_GRAY_3.sum_gray[i] = 0;
	}
    for(i=0;i<=15;i++)
	{
		DIGITAL16_GRAY_4.sum_gray[i] = 0;
	}
}

/*16路灰度循迹时功能函数*/
/*
适用情况：线与阵列灰度垂直时。
功能：计算出线相对于灰度的位置
返回值：（浮点数）某阵列灰度几号灰度在线上
*/
float GRAYx_FUNC_POS(DEF_16DIGITAL_GRAY Gray_BUFF)
{
	uint8_t i;
	uint8_t count=0;
	uint8_t sum=0;
	uint16_t buff;
    float index;
	buff = Gray_BUFF.digital16_gray_state.value;
	for(i = 1; i <= 16; i++)
	{
		if(buff & 1)
		{
			count++;
			sum += i;
		}
		buff>>= 1;
	}
    if(count == 0) 
    {
       index = 0; 
    }
	else 
    {
        index = (float) sum / count;
    }
	return index;
}

/*
适用情况：线与阵列灰度垂直时。
功能：计算出某阵列灰度上多少只灰度在线上
*/
uint8_t GRAYx_FUNC_Linecount(DEF_16DIGITAL_GRAY Gray_BUFF)
{
    uint8_t i;
	uint8_t count=0;
	uint8_t sum=0;
	uint16_t buff;
	buff = Gray_BUFF.digital16_gray_state.value;
	for(i = 1; i <= 16; ++i)
    {
		if(buff & 1)
        {
			count++;
			sum += i;
		}
		buff>>= 1;
	}
	return count;
}

/*灰度位置调整值更新*/
void GRAY_FUNC_DIR_UPDATE(void)
{
	//车的长度（Y方向的车长）单位：cm
	static uint8_t LONG=38;
	//车的宽度（X方向的车长）单位：cm
	static uint8_t WIDE=33;
	//相邻灰度间的距离 单位：cm
	static float GRAY_LEVEL=1.25;
	float l1,l2,a,b;
	//排除交界点干扰
	if((DIGITAL16_GRAY_1.digital16_gray_state.STATE.L1!=1)&&(DIGITAL16_GRAY_1.digital16_gray_state.STATE.L16!=1)&&(DIGITAL16_GRAY_3.digital16_gray_state.STATE.L1!=1)&&(DIGITAL16_GRAY_1.digital16_gray_state.STATE.L16!=1))
	{
		/*求X轴顺时针偏离角度*/
		//a和b符号相同
		a=GRAY_LEVEL*(8.5-GRAYx_FUNC_POS(DIGITAL16_GRAY_1));
		b=GRAY_LEVEL*(GRAYx_FUNC_POS(DIGITAL16_GRAY_3)-8.5);
		//角度在0~90度 车顺时针偏
		//角度在-90~0度 车逆时针偏
		if(((a>=0)&&(b<=0))||((a<=0)&&(b>=0)))
		{
			if((a+b)!=0)
			{
				l1=a*WIDE/(a-b);
				l2=WIDE-l1;
			}
			else
			{
				l1=l2=WIDE/2;
			}
			//弧度值，若要转角度值要* 180.0/3.1416
			if(atan(a/l1)* 180.0/3.1416<30)
			GRAY_DIR.X_DIR_ANGLE=atan(a/l1)* 180.0/3.1416;
			GRAY_DIR.X_DIR_DISTANCE=a*(l1-l2)/l1;
		}
		//前后中心点都在轴的一侧
		else if(fabs(a)>fabs(b))
		{
			l2=b*WIDE/(a-b);
			if(atan(b/l2)* 180.0/3.1416<30)
			GRAY_DIR.X_DIR_ANGLE=atan(b/l2)* 180.0/3.1416;
			GRAY_DIR.X_DIR_DISTANCE=b*(l2+WIDE/2)/l2;
		}
		else if(fabs(a)<fabs(b))
		{
			l1=a*WIDE/(b-a);
			if(-atan(a/l1)* 180.0/3.1416<30)
			GRAY_DIR.X_DIR_ANGLE=-atan(a/l1)* 180.0/3.1416;
			GRAY_DIR.X_DIR_DISTANCE=a*(l1+WIDE/2)/l1;
		}
		else if(fabs(a)==fabs(b))
		{
			GRAY_DIR.X_DIR_ANGLE=0;
			GRAY_DIR.X_DIR_DISTANCE=a;
		}
	}
	else
	{
		GRAY_DIR.X_DIR_ANGLE=0;
		GRAY_DIR.X_DIR_DISTANCE=0;
	}
	
	if((DIGITAL16_GRAY_2.digital16_gray_state.STATE.L1!=1)&&(DIGITAL16_GRAY_2.digital16_gray_state.STATE.L16!=1)&&(DIGITAL16_GRAY_4.digital16_gray_state.STATE.L1!=1)&&(DIGITAL16_GRAY_4.digital16_gray_state.STATE.L16!=1))
	{
		/*Y+方向为a Y方向上的位置调整量*/
		a=GRAY_LEVEL*(8.5-GRAYx_FUNC_POS(DIGITAL16_GRAY_4));
		b=GRAY_LEVEL*(GRAYx_FUNC_POS(DIGITAL16_GRAY_2)-8.5);
		//角度在0~90度 车顺时针偏
		//角度在-90~0度 车逆时针偏
		if(((a>=0)&&(b<=0))||((a<=0)&&(b>=0)))
		{
			if((a+b)!=0)
			{
				l1=a*LONG/(a-b);
				l2=LONG-l1;
			}
			else
			{
				l1=l2=LONG/2;
			}
			//弧度值，若要转角度值要* 180.0/3.1416
			if(atan(a/l1)* 180.0/3.1416<30)
			GRAY_DIR.Y_DIR_ANGLE=atan(a/l1)* 180.0/3.1416;
			GRAY_DIR.Y_DIR_DISTANCE=a*(l1-l2)/l1;
		}
		//前后中心点都在轴的一侧
		else if(fabs(a)>fabs(b))
		{
			l2=b*LONG/(a-b);
			if(atan(b/l2)* 180.0/3.1416<30)
			GRAY_DIR.Y_DIR_ANGLE=atan(b/l2)* 180.0/3.1416;
			GRAY_DIR.Y_DIR_DISTANCE=b*(l2+LONG/2)/l2;
		}
		else if(fabs(a)<fabs(b))
		{
			l1=a*LONG/(b-a);
			if(-atan(a/l1)* 180.0/3.1416<30)
			GRAY_DIR.Y_DIR_ANGLE=-atan(a/l1)* 180.0/3.1416;
			GRAY_DIR.Y_DIR_DISTANCE=a*(l1+LONG/2)/l1;
		}
		else if(fabs(a)==fabs(b))
		{
			GRAY_DIR.Y_DIR_ANGLE=0;
			GRAY_DIR.Y_DIR_DISTANCE=a;
		}
	}
	else
	{
		GRAY_DIR.Y_DIR_ANGLE=0;
		GRAY_DIR.Y_DIR_DISTANCE=0;
	}
	
}


