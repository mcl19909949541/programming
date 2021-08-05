/**
 ***************************************(C) COPYRIGHT 2018 DJI***************************************
 * @file       oled.c
 * @brief      this file contains sd card basic operating function
 * @note         
 * @Version    V1.0.0
 * @Date       Jan-28-2018      
 ***************************************(C) COPYRIGHT 2018 DJI***************************************
 */

#include "oled.h"
#include "oledfont.h"
#include "math.h"
#include "adc.h"
#include "track.h"
#include <stdio.h>
#include <stdarg.h>
#include <string.h>

/**
 * OLED flash Addr:
 * [0]0 1 2 3 ... 127
 * [1]0 1 2 3 ... 127
 * [2]0 1 2 3 ... 127
 * [3]0 1 2 3 ... 127
 * [4]0 1 2 3 ... 127
 * [5]0 1 2 3 ... 127
 * [6]0 1 2 3 ... 127
 * [7]0 1 2 3 ... 127
**/
char buff[15];
uint8_t oledwifi[7];
uint8_t oled_u1_can1[8];
int CheckProble[10];//存储故障信息
static uint8_t OLED_GRAM[128][8];
uint16_t oledorder ;
uint16_t oled_qr_order ;
uint16_t oled_cl_order ;
uint32_t v = 0;//存储模拟电压信号

DEF_KEY OlED_Key;
//short delay uesd in spi transmmit

/*用于显示车的POS信息*/
void OLED_TRACK_CAR(void)
{
	oled_refresh_gram();
    //第一行显示当前位置
	switch(CAR.CUR_POS)
	{
		case OUT:
		{
			strcpy(buff, "OUT");
		}break;
		case CENTER:
        {
            strcpy(buff, "CENTER");
        }break;
        case ON_X:
        {
            strcpy(buff, "ON_X");
        }break;
        case ON_Y:
        {
            strcpy(buff, "ON_Y");
        }break;
        case Xplus_CENTER:
        {
            strcpy(buff, "Xplus_CENTER");
        }break;
        case Xminus_CENTER:
        {
            strcpy(buff, "Xminus_CENTER");
        }break;
        case Yplus_CENTER:
        {
            strcpy(buff, "Yplus_CENTER");
        }break;
        case Yminus_CENTER:
        {
            strcpy(buff, "Yminus_CENTER");
        }break;
        case Q1_CENTER:
        {
            strcpy(buff, "Q1_CENTER");
        }break;
        case Q2_CENTER:
        {
            strcpy(buff, "Q2_CENTER");
        } break;
        case Q3_CENTER:
        {
            strcpy(buff, "Q3_CENTER");
        }break;
        case Q4_CENTER:
        {
            strcpy(buff, "Q4_CENTER");
        }break;
	}
  oled_showstring(1,1,buff);
	//第二行显示激光测距//
	strcpy(buff, "L1:");
  oled_showstring(2,1,buff);
	oled_shownum(2,4,LASER.laser_value[1],0,5);
	strcpy(buff, "PW:");
  oled_showstring(2,10,buff);
	oled_shownum(2,13,LASER.laser_value[2],0,5);
	
	
	//oled_shownum(2,1,LASER.laser_value[2],0,5);

    //第二行显示预选方向和已选方向
//    oled_shownum(2,1,TRACK.maybe_dir[1],0,1);
//    oled_shownum(2,2,TRACK.maybe_dir[2],0,1);
//    oled_shownum(2,3,TRACK.maybe_dir[3],0,1);
//    oled_shownum(2,4,TRACK.maybe_dir[4],0,1);
//	 oled_shownum(2,5,TRACK.STATE,0,2);
//	
//	switch(TRACK.FINAL_DIR)
//	{
//		case NO_DIR:
//		{
//			strcpy(buff, "NO_DIR");
//		}break;
//		case Xplus_DIR:
//        {
//            strcpy(buff, "X+");
//        }break;
//        case Xminus_DIR:
//        {
//            strcpy(buff, "X-");
//        }break;
//        case Yplus_DIR:
//        {
//            strcpy(buff, "Y+");
//        }break;
//        case Yminus_DIR:
//        {
//            strcpy(buff, "Y-");
//        }break;
//	}
//    oled_showstring(2,7,buff);
    //第三行显示坐标
    strcpy(buff, "X:");
    oled_showstring(3,1,buff);
    oled_shownum(3,3,CAR.CUR_COR.X_COR,0,2);
    strcpy(buff, "Y:");
    oled_showstring(3,6,buff);
    oled_shownum(3,9,CAR.CUR_COR.Y_COR,0,2);
	//第四行显示当前方向
	switch(CAR.DIR)
	{
		case NO_DIR:
		{
			strcpy(buff, "NO_DIR");
		}break;
		case Xplus_DIR:
        {
            strcpy(buff, "X+");
        }break;
        case Xminus_DIR:
        {
            strcpy(buff, "X-");
        }break;
        case Yplus_DIR:
        {
            strcpy(buff, "Y+");
        }break;
        case Yminus_DIR:
        {
            strcpy(buff, "Y-");
        }break;
	}
    oled_showstring(4,1,buff);
	 oled_showstring(4,7,buff);
	  oled_shownum(4,7,TRACK.ARRIVE,0,1);
}


void delay_oled_ms(uint16_t delaytimes)
{
    uint16_t i;
    for (i = 0; i < delaytimes; i++ )
    {
        int a = 10000;  //delay based on mian clock, 168Mhz
        while (a-- );
    }
}


/**
 * @brief   write data/command to OLED
 * @param   dat: the data ready to write
 * @param   cmd: 0x00,command 0x01,data
 * @retval  
 */
void oled_write_byte(uint8_t dat, uint8_t cmd)
{
    if (cmd != 0)
        OLED_CMD_Set();
    else
        OLED_CMD_Clr();

    HAL_SPI_Transmit(&hspi1, &dat, 1, 10);
}


/**
 * @brief   set OLED cursor position
 * @param   x: the X-axis of cursor
 * @param   y: the Y-axis of cursor
 * @retval  
 */
static void oled_set_pos(uint8_t x, uint8_t y)
{
    x += 2;
    oled_write_byte((0xb0 + y), OLED_CMD);              //set page address y
    oled_write_byte(((x&0xf0)>>4)|0x10, OLED_CMD);      //set column high address
    oled_write_byte((x&0xf0), OLED_CMD);                //set column low address
}

/**
 * @brief   turn on OLED display
 * @param   None
 * @param   None
 * @retval  
 */
void oled_display_on(void)
{
    oled_write_byte(0x8d, OLED_CMD);
    oled_write_byte(0x14, OLED_CMD);
    oled_write_byte(0xaf, OLED_CMD);
}

/**
 * @brief   turn off OLED display
 * @param   None
 * @param   None
 * @retval  
 */
void oled_display_off(void)
{
    oled_write_byte(0x8d, OLED_CMD);
    oled_write_byte(0x10, OLED_CMD);
    oled_write_byte(0xae, OLED_CMD);
}

/**
 * @brief   refresh the RAM of OLED
 * @param   None
 * @param   None
 * @retval  
 */
void oled_refresh_gram(void)
{
    uint8_t i, n;

    for (i = 0; i < 8; i++)
    {
        oled_set_pos(0, i);

        for (n = 0; n < 128; n++)
        {
            oled_write_byte(OLED_GRAM[n][i], OLED_DATA);
        }
    }
}

/**
 * @brief   clear the screen
 * @param   None
 * @param   None
 * @retval  
 */
void oled_clear(Pen_Typedef pen)
{
    uint8_t i, n;

    for (i = 0; i < 8; i++)
    {
        for (n = 0; n < 128; n++)
        {
            if (pen == Pen_Write)
                OLED_GRAM[n][i] = 0xff;
            else if (pen == Pen_Clear)
                OLED_GRAM[n][i] = 0x00;
            else
                OLED_GRAM[n][i] = 0xff - OLED_GRAM[n][i];
        }
    }
}

/**
 * @brief   draw a point at (x, y)
 * @param   x: the X-axis of cursor
 * @param   y: the Y-axis of cursor
 * @param   pen: Pen_Clear, Pen_Write, Pen_Inversion @Pen_Typedef
 * @retval  None
 */
void oled_drawpoint(int8_t x, int8_t y, Pen_Typedef pen)
{
    uint8_t page = 0, row = 0;

    /* check the corrdinate */
    if ((x < 0) || (x > (X_WIDTH - 1)) || (y < 0) || (y > (Y_WIDTH - 1)))
        return;

    page = y / 8;
    row = y % 8;

    if (pen == Pen_Write)
        OLED_GRAM[x][page] |= 1 << row;
    else if (pen == Pen_Inversion)
        OLED_GRAM[x][page] ^= 1 << row;
    else
        OLED_GRAM[x][page] &= ~(1 << row);
}

/**
 * @brief   draw a line from (x1, y1) to (x2, y2)
 * @param   x1, y1: the start point of line
 * @param   x2, y2: the end of line
 * @param   pen: Pen_Clear, Pen_Write, Pen_Inversion @Pen_Typedef
 * @retval  None
 */
void oled_drawline(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, Pen_Typedef pen)
{
    uint8_t col = 0, row = 0;
    uint8_t x_st = 0, x_ed = 0, y_st = 0, y_ed = 0;
    float k = 0.0f, b = 0.0f;

    if (y1 == y2)
    {
        (x1 <= x2) ? (x_st = x1):(x_st = x2);
        (x1 <= x2) ? (x_ed = x2):(x_ed = x1);

        for (col = x_st; col <= x_ed; col++)
        {
            oled_drawpoint(col, y1, pen);
        }
    }
    else if (x1 == x2)
    {
        (y1 <= y2) ? (y_st = y1):(y_st = y2);
        (y1 <= y2) ? (y_ed = y2):(y_ed = y1);

        for (row = y_st; row <= y_ed; row++)
        {
            oled_drawpoint(x1, row, pen);
        }
    }
    else
    {
        k = ((float)(y2 - y1)) / (x2 - x1);
        b = (float)y1 - k * x1;

        (x1 <= x2) ? (x_st = x1):(x_st = x2);
        (x1 <= x2) ? (x_ed = x2):(x_ed = x2);

        for (col = x_st; col <= x_ed; col++)
        {
            oled_drawpoint(col, (uint8_t)(col * k + b), pen);
        }
    }
}


//To add: rectangle, fillrectangle, circle, fillcircle, 

/**
 * @brief   show a character
 * @param   row: row of character
 * @param   col: column of character
 * @param   chr: the character ready to show
 * @retval  None
 */
void oled_showchar(uint8_t row, uint8_t col, uint8_t chr)
{
    uint8_t x = col * 6;
    uint8_t y = row * 12;
    uint8_t temp, t, t1;
    uint8_t y0 = y;
    chr = chr - ' ';

    for (t = 0; t < 12; t++)
    {
        temp = asc2_1206[chr][t];

        for (t1 = 0; t1 < 8; t1++)
        {
            if (temp&0x80)
                oled_drawpoint(x, y, Pen_Write);
            else
                oled_drawpoint(x, y, Pen_Clear);

            temp <<= 1;
            y++;
            if ((y - y0) == 12)
            {
                y = y0;
                x++;
                break;
            }
        }
    }
}

//m^n
static uint32_t oled_pow(uint8_t m, uint8_t n)
{
    uint32_t result = 1;

    while (n--)
        result *= m;

    return result;
}

/**
 * @brief   show a number
 * @param   row: row of number
 * @param   col: column of number
 * @param   num: the number ready to show
 * @param   mode: 0x01, fill number with '0'; 0x00, fill number with spaces
 * @param   len: the length of the number
 * @retval  None
 */
void oled_shownum(uint8_t row, uint8_t col, uint32_t num, uint8_t mode, uint8_t len)
{
    uint8_t t, temp;
    uint8_t enshow = 0;

    for (t = 0; t < len; t++)
    {
        temp = (num / oled_pow(10, len - t -1)) % 10;

        if (enshow == 0 && t < (len - 1))
        {
            if (temp == 0)
            {
                if (mode == 0)
                    oled_showchar(row, col + t, ' ');
                else
                    oled_showchar(row, col + t, '0');
                continue;
            }
            else
                enshow = 1;
        }

        oled_showchar(row, col + t, temp + '0');
    }
}


/**
 * @brief   show a character string
 * @param   row: row of character string begin
 * @param   col: column of character string begin
 * @param   chr: the pointer to character string
 * @retval  None
 */
void oled_showstring(uint8_t row, uint8_t col, uint8_t *chr)
{
    uint8_t n =0;

    while (chr[n] != '\0')
    {
        oled_showchar(row, col, chr[n]);
        col++;

        if (col > 20)
        {
            col = 0;
            row += 1;
        }
        n++;
    }
}

/**
 * @brief   formatted output in oled 128*64
 * @param   row: row of character string begin, 0 <= row <= 4;
 * @param   col: column of character string begin, 0 <= col <= 20;
 * @param   *fmt: the pointer to format character string
 * @retval  None
 * @note    if the character length is more than one row at a time, the extra characters will be truncated
 */
void oled_printf(uint8_t row, uint8_t col, const char *fmt,...)
{
    uint8_t LCD_BUF[128] = {0};
    uint8_t remain_size = 0;
    va_list ap;

    if ((row > 4) || (row < 1) || (col > 20) || (col < 1))
        return;

    va_start(ap, fmt);

    vsprintf((char *)LCD_BUF, fmt, ap);

    va_end(ap);

    remain_size = 21 - col;

    LCD_BUF[remain_size] = '\0';

    oled_showstring(row, col, LCD_BUF);
}

void oled_LOGO(void)
{
    oled_clear(Pen_Clear);
    uint8_t temp_char = 0;
    uint8_t x = 0, y = 0;
    uint8_t i = 0;
    for(; y < 64; y += 8)
    {
        for(x = 0; x < 128; x++)
        {
            temp_char = LOGO_BMP[x][y/8];
            for(i = 0; i < 8; i++)
            {
                if(temp_char & 0x80) oled_drawpoint(x, y + i,Pen_Write);
                else oled_drawpoint(x,y + i,Pen_Clear);
                temp_char <<= 1;
            }
        }
    }
    oled_refresh_gram();
}


//oled显示总的任务顺序函数
void Oled_Order(uint16_t order)
{
	uint8_t str1[]="The QR Order: ";
	uint8_t strred[]="Red";
	uint8_t strgreen[]="Green";	
	uint8_t strblue[]="Blue";	
	uint8_t defau[]="   Default";
	
	//oled_showstring(1,1,str1);
	switch (order)
	{
		case 123 : 
			oled_showstring(1,3,strred);
			oled_showstring(1,8,strgreen);
			oled_showstring(1,15,strblue);
		break;
		case 132 : 
			oled_showstring(1,2,strred);
			oled_showstring(1,8,strblue);			
		  oled_showstring(1,14,strgreen);
		break;
		case 213 : 
			oled_showstring(1,2,strgreen);
			oled_showstring(1,9,strred);
			oled_showstring(1,14,strblue);			
		break;
		case 231:
			oled_showstring(1,2,strgreen);
			oled_showstring(1,9,strblue);	
		  oled_showstring(1,15,strred);
		break;
		case 312:			
			oled_showstring(1,2,strblue);	 
		  oled_showstring(1,8,strred);
			oled_showstring(1,14,strgreen);
		break;
		case 321:
			oled_showstring(1,2,strblue);	 
			oled_showstring(1,8,strgreen);		  
		 oled_showstring(1,15,strred);
		break;
		default:
			 oled_showstring(1,2,defau);
		break;
	}
}
/**
 * @brief   initialize the oled module
 * @param   None
 * @retval  None
 */
void oled_init(void)
{
    OLED_RST_Clr();
    HAL_Delay(500);
    OLED_RST_Set();

    oled_write_byte(0xae, OLED_CMD);    //turn off oled panel
    oled_write_byte(0x00, OLED_CMD);    //set low column address
    oled_write_byte(0x10, OLED_CMD);    //set high column address
    oled_write_byte(0x40, OLED_CMD);    //set start line address
    oled_write_byte(0x81, OLED_CMD);    //set contrast control resigter
    oled_write_byte(0xcf, OLED_CMD);    //set SEG output current brightness
    oled_write_byte(0xa1, OLED_CMD);    //set SEG/column mapping
    oled_write_byte(0xc8, OLED_CMD);    //set COM/row scan direction
    oled_write_byte(0xa6, OLED_CMD);    //set nomarl display
    oled_write_byte(0xa8, OLED_CMD);    //set multiplex display
    oled_write_byte(0x3f, OLED_CMD);    //1/64 duty
    oled_write_byte(0xd3, OLED_CMD);    //set display offset
    oled_write_byte(0x00, OLED_CMD);    //not offest
    oled_write_byte(0xd5, OLED_CMD);    //set display clock divide ratio/oscillator frequency
    oled_write_byte(0x80, OLED_CMD);    //set divide ratio 
    oled_write_byte(0xd9, OLED_CMD);    //set pre-charge period
    oled_write_byte(0xf1, OLED_CMD);    //pre-charge: 15 clocks, discharge: 1 clock
    oled_write_byte(0xda, OLED_CMD);    //set com pins hardware configuration 
    oled_write_byte(0x12, OLED_CMD);    //
    oled_write_byte(0xdb, OLED_CMD);    //set vcomh
    oled_write_byte(0x40, OLED_CMD);    //set vcom deselect level
    oled_write_byte(0x20, OLED_CMD);    //set page addressing mode
    oled_write_byte(0x02, OLED_CMD);    //
    oled_write_byte(0x8d, OLED_CMD);    //set charge pump enable/disable
    oled_write_byte(0x14, OLED_CMD);    //charge pump disable
    oled_write_byte(0xa4, OLED_CMD);    //disable entire dispaly on
    oled_write_byte(0xa6, OLED_CMD);    //disable inverse display on
    oled_write_byte(0xaf, OLED_CMD);    //turn on oled panel

    oled_write_byte(0xaf, OLED_CMD);    //display on

    oled_clear(Pen_Clear);
    oled_set_pos(0, 0);

}
void oled_Problem(int A[])
{
	//A 数组是A[10];
	uint8_t str1[]="bad uart:";
	uint8_t str2[]="2";
	uint8_t str0[] =" ";
	uint8_t str3[]="6";
	uint8_t str4[]="8";	
	uint8_t str5[]="OK     ";	
	oled_showstring(4,1,str1);
	if(A[1] == 1)//表示串口2的灰度没接好
	{
	oled_showstring(4,10,str2);
	}
	else 
	{
	oled_showstring(4,10,str0);
	}
	
	if(A[2] == 1)//表示串口6的灰度没接好
	{
	oled_showstring(4,12,str3);
	}
	else 
	{
	oled_showstring(4,12,str0);
	}
	
		if(A[3] == 1)//表示串口6的灰度没接好
	{
	oled_showstring(4,14,str4);
	}
	else 
	{
	oled_showstring(4,14,str0);
	}
	
	if(A[1] == 0&&A[2] == 0&&A[3] == 0)
	{
		oled_showstring(4,10,str5);
	}
}
//oled的按键部分

void KeyStatics()
{
	HAL_ADC_Start(&hadc1);			
	v = HAL_ADC_GetValue(&hadc1);
	if(OlED_Key.temp > 2600 && v <10 )//说明中间按下去了
	{
	OlED_Key.center ++;
	}
//	else if(OlED_Key.temp > 2600 && (v > 800&& v < 1100 ))//说明左键被按下去了
//	{
//	OlED_Key.left ++;
//	}
//	else if(OlED_Key.temp > 2600 && (v > 1300 &&v <1900) )//说明右键被按下去了
//	{
//	OlED_Key.right ++;
//	}
//	else if(OlED_Key.temp > 2600 && (v >2100&& v <2300) )//说明上键被按下去了
//	{
//	OlED_Key.up ++;
//	}
//	else if(OlED_Key.temp > 2600 && (v>2700 && v <2800) )//说明下键被按下去了
//	{
//	OlED_Key.down ++;
//	}
	OlED_Key.temp = v ;   //更新数值
	
	if(OlED_Key.down >6)
	{
		OlED_Key.down = 0 ;//用向下的按键来翻页选择默认颜色顺序6中情况
	}
	
	if(OlED_Key.center > 6)
	{
		OlED_Key.center = 0; //用中间的按键来启动小车 有 0 1 两种状态 0 表示不能走 起初就不应该走 
	}
	
	if(OlED_Key.right > 1)
	{
		OlED_Key.right = 0;  //有右边按键 切换 颜色顺序听谁的 0 表示听openmv的 1表示听我的；
	}
	
	//对超出范围的做出限制
	//判断按键方向
	


}
	
//	void ShowWIFI()
//	{
//	uint8_t i;
//		for (i = 0 ;i<3;i++)
//		{
//	oledwifi[i] = WIFI.Rec_Data[i] + '0';
//		}
//		for(i = 4;i<7;i++)
//		{
//	oledwifi[i] = WIFI.Rec_Data[i-1] + '0';	
//		}
//	oledwifi[3] = '+';		
//		//存储WiFi信号
//		
//		oled_showstring(1,1,oledwifi);
//	}
	
