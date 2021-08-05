#include "track.h"
#include "module_arm.h"
//如果定义了它，相关标志位由机械臂决定是否置位
#define __ARM_VALID

DEF_CAR CAR;
DEF_TRACK TRACK;
COR_GRAY POS_GRAY_COUNT;

void TRACK_INIT(void)
{
  /*设定车的循迹基本量*/
  CAR.COR_MODE=NO_COR_MODE;
  CAR.DIR_MODE=NO_DIR_MODE;
	CAR.CUR_COR.X_COR=0;
	CAR.CUR_COR.Y_COR=0;  
	
	/*决定是自由循迹还是红方蓝方*/
	TRACK.id=5;//只取3  4 5 6（35红  46蓝）
	TRACK.STATE=START;
		
}

//只调先黄球
/* 红色方先红球再黄球再积木块*/
void TRACK_MODULE_RED_RY(void)
{
	
	switch(TRACK.STATE)
	{
    /*从出发区前往线上，坐标 5 0*/
		case START:
		{
      TRACK_CAR_CTOL(0,0,0,2000,0,0);
			if(DIGITAL16_GRAY_3.digital16_gray_state.STATE.L8==1&&DIGITAL16_GRAY_3.digital16_gray_state.STATE.L9==1)
			{		
				TRACK_CAR_CTOL(0,2,0,0,0,100);
				S_ADJUST();					//调整完毕
				TRACK_CAR_CTOL(0,0,0,0,0,500);
				CAR.CUR_COR.X_COR=5;
        CAR.CUR_COR.Y_COR=0;
				TRACK.STATE=BACK;
				PlatformControl(1, 0, 0);
			}	          
		}		
		break;		
    /*坐标法到达 4，2准备过储存区*/
    case TRACK_GO_FETCH_BALL_RED:
    {
      TRACK_COR_GO(4,2,5000,5000);
      if(TRACK.ARRIVE==ARRIVED)
      {
        TRACK_CAR_CTOL(0,2,0,0,0,100);
        P_ADJUST();	
				TRACK_CAR_CTOL(0,0,0,0,0,500);
        TRACK.STATE=TRACK_GO_FETCH_BALL_RED_2;
      }
	  }
		break;	
	  /*硬延时过储存区*/
    case TRACK_GO_FETCH_BALL_RED_2:
    {
	    TRACK_CAR_CTOL(0,2,0,0,0,0);	
      while(!TRACK_GO_STEP(0,3500,100));
      TRACK_CAR_CTOL(0,2,0,0,0,0);	
      S_ADJUST();								//调整完毕
			TRACK_CAR_CTOL(0,0,0,0,0,500);
      CAR.CUR_COR.X_COR=4;
      CAR.CUR_COR.Y_COR=4;
      TRACK.STATE=TRACK_GO_FETCH_BALL_RED_3;
	  }
		break;	
	  /*坐标法到达 4，6*/
		case TRACK_GO_FETCH_BALL_RED_3:
		{
      TRACK_COR_GO(4,6,5000,5000);
				
      if(TRACK.ARRIVE==ARRIVED)
      {
        TRACK_CAR_CTOL(0,2,0,0,0,1000);
        S_ADJUST();								//调整完毕
			  TRACK_CAR_CTOL(0,0,0,0,0,500);
        TRACK.STATE=TRACK_FETCH_BALL_RED;
      }
	  }
		break;
	  /*慢速前进到抓取位置*/
		case TRACK_FETCH_BALL_RED:
		{				
		  TRACK_CAR_CTOL(0,0,-1000,0,0,0);
			/*三号灰度 L1 L2灰度落在白线，并且有一激光小于12cm*/
			if(LASER.laser_value[1]<=90)
			{	
			  TRACK_CAR_CTOL(0,0,0,0,0,1000);
				TRACK.color=1;
				TRACK.STATE=WAITING_FUCK_BALL_RED;								
			}
		}
		break;
		case WAITING_FUCK_BALL_RED:
		{
		  waiting_fetch_ball();
			HAL_Delay(1000);
			finish_fetch(1);
			TRACK.STATE=FETCH_BALL_OVER_RED;
			PlatformControl(2,0,50);//平台下降以便放球
		}
		break;
		//		/*抓取完成 更新当前位置与坐标*/
		case FETCH_BALL_OVER_RED:
		{ 
		  //TRACK.color=3;
			while(!TRACK_GO_STEP(1500,0,15));
			if(CAR.CUR_POS==ON_X)
      {
			  TRACK_CAR_CTOL(0,2,0,0,0,200);
				S_ADJUST();								//调整完毕
			  TRACK_CAR_CTOL(0,0,0,0,0,500);								//调整完毕
				/*赋予坐标值*/
        CAR.CUR_COR.X_COR=3;
        CAR.CUR_COR.Y_COR=6;
        TRACK.STATE=FETCH_OVER_1;
			  TRACK_CAR_CTOL(0,0,0,0,0,500);
      }
		  if(CAR.CUR_POS==Yplus_CENTER)
      {
			  TRACK_CAR_CTOL(0,2,0,0,0,200);
				S_ADJUST();								//调整完毕
			  TRACK_CAR_CTOL(0,0,0,0,0,500);
				/*赋予坐标值*/
        CAR.CUR_COR.X_COR=4;
        CAR.CUR_COR.Y_COR=6;
        TRACK.STATE=FETCH_OVER_1;
			  TRACK_CAR_CTOL(0,0,0,0,0,1000);
      }
		}
		break;
	  case FETCH_OVER_1:
    {
      /*坐标法到达 4，4*/
      TRACK_COR_GO(4,4,5000,5000);
      if(TRACK.ARRIVE==ARRIVED)
      {
        //CAR.V.VX=0;
        //CAR.V.VY=0;
			  TRACK_CAR_CTOL(0,0,0,0,0,500);
        S_ADJUST();								//调整完毕
			  TRACK_CAR_CTOL(0,0,0,0,0,500);
        TRACK.STATE=GO_STORE_RED;
      }
	  }
		break;
		//储存本色球
		case GO_STORE_RED:
	  {
		  CAR.V.VX=0;
      CAR.V.VY=-2000;
		  if(DIGITAL16_GRAY_3.digital16_gray_state.STATE.L5==1&&DIGITAL16_GRAY_3.digital16_gray_state.STATE.L14==1&&DIGITAL16_GRAY_3.digital16_gray_state.STATE.L6==1)
			{
        CAR.V.VX=0;
        CAR.V.VY=0;				
				TRACK_CAR_CTOL(0,0,0,0,0,1500);
				while(!TRACK_GO_STEP(-1500,0,30));
				CAR.V.VX=0;
        CAR.V.VY=0;	
				TRACK.STATE=STORE_RED;
			}	
		}
		break;
		case STORE_RED:
		{
		  Duoji_angle(0x07, 500, 900);
		  TRACK_CAR_CTOL(0,0,0,0,0,2500);
			Duoji_angle(0x07, 220, 900);
			while(!TRACK_GO_STEP(1500,0,30));
      CAR.V.VX=0;
      CAR.V.VY=0;	
			TRACK.STATE=STORE_OVER_BACK_ONLINE;
			PlatformControl(1,0,50);//平台上升回原位
		}
		break;
		case STORE_OVER_BACK_ONLINE:
		{
      TRACK_CAR_CTOL(0,2,0,0,0,0);	
      while(!TRACK_GO_STEP(0,3500,40));
      TRACK_CAR_CTOL(0,2,0,0,0,0);	
      S_ADJUST();								//调整完毕
			TRACK_CAR_CTOL(0,0,0,0,0,500);
      CAR.CUR_COR.X_COR=4;
      CAR.CUR_COR.Y_COR=4;
      TRACK.STATE=TRACK_GO_FETCH_BALL_YELLOW;
		}
		break;
		/*坐标法到达 4，6*/
		case TRACK_GO_FETCH_BALL_YELLOW:
		{
      TRACK_COR_GO(4,6,5000,5000);
				
      if(TRACK.ARRIVE==ARRIVED)
      {
        TRACK_CAR_CTOL(0,2,0,0,0,1000);
        S_ADJUST();								//调整完毕
			  TRACK_CAR_CTOL(0,0,0,0,0,500);
        TRACK.STATE=TRACK_GO_FETCH_BALL_YELLOW_2;
      }
		}
		break;
		/*慢速前进到抓取位置*/
		case TRACK_GO_FETCH_BALL_YELLOW_2:
		{						
      TRACK_CAR_CTOL(0,0,-1000,0,0,0);
			/*三号灰度 L1 L2灰度落在白线，并且有一激光小于12cm*/
			if(LASER.laser_value[1]<=90)
			{	
			  TRACK_CAR_CTOL(0,0,0,0,0,1000);						
        TRACK.color=1;
			  TRACK.STATE=WAITING_FUCK_BALL_YELLOW;				
			}
		}
		break;
		case WAITING_FUCK_BALL_YELLOW:
		{
			waiting_fetch_ball();
			HAL_Delay(1000);
			finish_fetch(3);
			TRACK.STATE=FETCH_BALL_OVER_YELLOW;
			PlatformControl(2,0,50);//平台下降以便放球
		}
		break;
		//		/*抓取完成 更新当前位置与坐标*/
		case FETCH_BALL_OVER_YELLOW:
		{ 
      //TRACK.color=3;
			while(!TRACK_GO_STEP(1500,0,15));
			if(CAR.CUR_POS==ON_X)
      {
			  TRACK_CAR_CTOL(0,2,0,0,0,200);
				S_ADJUST();								//调整完毕
			  TRACK_CAR_CTOL(0,0,0,0,0,500);								//调整完毕
				/*赋予坐标值*/
        CAR.CUR_COR.X_COR=3;
        CAR.CUR_COR.Y_COR=6;
        TRACK.STATE=FETCH_OVER_2;
			  TRACK_CAR_CTOL(0,0,0,0,0,500);
      }
		  if(CAR.CUR_POS==Yplus_CENTER)
      {
		    TRACK_CAR_CTOL(0,2,0,0,0,200);
			  S_ADJUST();								//调整完毕
			  TRACK_CAR_CTOL(0,0,0,0,0,500);
				/*赋予坐标值*/
        CAR.CUR_COR.X_COR=4;
        CAR.CUR_COR.Y_COR=6;
        TRACK.STATE=FETCH_OVER_2;
			  TRACK_CAR_CTOL(0,0,0,0,0,1000);
      }
		}
		break;
		case FETCH_OVER_2:
    {
      /*坐标法到达 4，4*/
      TRACK_COR_GO(4,4,5000,5000);
      if(TRACK.ARRIVE==ARRIVED)
      {
        //CAR.V.VX=0;
        //CAR.V.VY=0;
				TRACK_CAR_CTOL(0,0,0,0,0,500);
        P_ADJUST();								//调整完毕
			  TRACK_CAR_CTOL(0,0,0,0,0,500);
        TRACK.STATE=GO_STORE_YELLOW;
      }
	  }
		break;
		//储存黄色球
		case GO_STORE_YELLOW:
		{
		  CAR.V.VX=0;
      CAR.V.VY=-2000;
		  if(DIGITAL16_GRAY_3.digital16_gray_state.STATE.L5==1&&DIGITAL16_GRAY_3.digital16_gray_state.STATE.L4==1)
			{
        CAR.V.VX=0;
        CAR.V.VY=0;				
				TRACK_CAR_CTOL(0,0,0,0,0,1500);
				while(!TRACK_GO_STEP(-1500,0,30));
				CAR.V.VX=0;
        CAR.V.VY=0;	
				TRACK.STATE=STORE_YELLOW;
			}	
		}
		break;
		case STORE_YELLOW:
		{
		  Duoji_angle(0x07, 500, 900);
			TRACK_CAR_CTOL(0,0,0,0,0,2500);
			Duoji_angle(0x07, 120, 900);
			while(!TRACK_GO_STEP(1500,0,30));
      CAR.V.VX=0;
      CAR.V.VY=0;	
		  TRACK.STATE=STORE_OVER_BACK_ONLINE_2;
			PlatformControl(1,0,46);//平台上升回原位，调试用为46，比赛务必改为50
		}
		break;
		case STORE_OVER_BACK_ONLINE_2:
		{
      TRACK_CAR_CTOL(0,2,0,0,0,0);	
      while(!TRACK_GO_STEP(0,3500,35));
      TRACK_CAR_CTOL(0,2,0,0,0,0);	
      S_ADJUST();								//调整完毕
			TRACK_CAR_CTOL(0,0,0,0,0,500);
      CAR.CUR_COR.X_COR=4;
      CAR.CUR_COR.Y_COR=4;
      TRACK.STATE=TRACK_GO_FETCH_BRICK;
		}
		break;
    case TRACK_GO_FETCH_BRICK:
    {
      /*坐标法到达 6，4*/
      TRACK_COR_GO(6,4,5000,5000);
      if(TRACK.ARRIVE==ARRIVED)
      {
        TRACK_CAR_CTOL(0,2,0,0,0,1000);
        S_ADJUST();								//调整完毕
			  TRACK_CAR_CTOL(0,0,0,0,0,500);
        TRACK.STATE=TRACK_GO_FETCH_BRICK_2;
      }
	  }
		break;	
		//转向180
		case TRACK_GO_FETCH_BRICK_2:
		{
      while(!TRACK_TURN_ANGLE(50,56));
			TRACK_CAR_CTOL(0,2,0,0,0,1000);
			S_ADJUST();								//调整完毕
			TRACK_CAR_CTOL(0,0,0,0,0,500);
			TRACK.STATE=TRACK_GO_FETCH_BRICK_3;	
		}
		break;			
		/*慢速向右到抓取位置*/
		case TRACK_GO_FETCH_BRICK_3:
		{
		  while(!TRACK_GO_STEP(0,2000,35));
      TRACK_CAR_CTOL(0,2,0,0,0,1000);
      TRACK.color=1;
		  S_ADJUST();								//调整完毕
			TRACK_CAR_CTOL(0,0,0,0,0,500);
			TRACK.STATE=TRACK_FETCH_BRICK;			
		}
		break;
	  /* 往前*/
		case TRACK_FETCH_BRICK:
		{
			TRACK_CAR_CTOL(0,0,-1000,0,0,0);
			if(LASER.laser_value[1]<=100)
			{
        TRACK_CAR_CTOL(0,0,0,0,0,2000);
        TRACK.color=1;
				TRACK.STATE=WAITING_FUCK_BRIKE;
			}	
		}
		break;
		case WAITING_FUCK_BRIKE:
		{
		  waiting_fetch_cube();
			//HAL_Delay(1000);
			//TRACK_CAR_CTOL(0,0,0,2000,0,10);
			finish_fetch(4);
			TRACK.STATE=FETCH_BRICK_OVER_BACK_ONLINE;
		}
		break;
		//		/*抓取完成 返回到 线上 更新坐标*/
		case FETCH_BRICK_OVER_BACK_ONLINE:
		{ 
      //TRACK.color=3;
			TRACK_CAR_CTOL(0,0,2000,0,0,0);
			if(DIGITAL16_GRAY_2.digital16_gray_state.STATE.L8==1&&DIGITAL16_GRAY_2.digital16_gray_state.STATE.L9==1)
			{
				//CAR.CUR_POS=ON_Y;
        TRACK_CAR_CTOL(0,2,0,0,0,0);
				S_ADJUST();								//调整完毕
			  TRACK_CAR_CTOL(0,0,0,0,0,500);
				/*赋予坐标值*/
        CAR.CUR_COR.X_COR=6;
        CAR.CUR_COR.Y_COR=3;
        TRACK.STATE=TRACK_GO_FETCH_BRICK_4;
				TRACK_CAR_CTOL(0,0,0,0,0,2000);
			}
		}
		break;
		case TRACK_GO_FETCH_BRICK_4:
		{
      TRACK_CAR_CTOL(0,0,0,-2000,0,0);
			if(DIGITAL16_GRAY_1.digital16_gray_state.STATE.L8==1)
			{		
			TRACK_CAR_CTOL(0,2,0,0,0,100);
			S_ADJUST();								//调整完毕
			TRACK_CAR_CTOL(0,0,0,0,0,500);
			TRACK.STATE=TRACK_GO_FETCH_BRICK_5;	
		  }
		}
		break;
			/*慢速向右到抓取位置*/
		case TRACK_GO_FETCH_BRICK_5:
		{
		  while(!TRACK_GO_STEP(0,2000,35));
      TRACK_CAR_CTOL(0,2,0,0,0,100);
      TRACK.color=1;
		  S_ADJUST();								//调整完毕
			TRACK_CAR_CTOL(0,0,0,0,0,500);
			TRACK.STATE=TRACK_FETCH_BRICK_2;			
		}
		break;
	  /* 往前*/
		case TRACK_FETCH_BRICK_2:
		{
			TRACK_CAR_CTOL(0,0,-1000,0,0,0);
			if(LASER.laser_value[1]<=100)
			{
        TRACK_CAR_CTOL(0,0,0,0,0,2000);
        TRACK.color=1;
				TRACK.STATE=WAITING_FUCK_BRIKE_2;
			}	
		}
		break;
		case WAITING_FUCK_BRIKE_2:
		{
		  waiting_fetch_cube();
			//HAL_Delay(1000);
			//TRACK_CAR_CTOL(0,0,0,2000,0,10);
			finish_fetch(7);
			TRACK.STATE=FETCH_BRICK_OVER_BACK_ONLINE_2;
		}
		break;
		//		/*抓取完成 返回到 线上 更新坐标*/
		case FETCH_BRICK_OVER_BACK_ONLINE_2:
		{ 
      //TRACK.color=3;
			TRACK_CAR_CTOL(0,0,2000,0,0,0);
			if(DIGITAL16_GRAY_2.digital16_gray_state.STATE.L8==1&&DIGITAL16_GRAY_2.digital16_gray_state.STATE.L9==1)
			{
				//CAR.CUR_POS=ON_Y;
        TRACK_CAR_CTOL(0,2,0,0,0,0);
				S_ADJUST();								//调整完毕
			  TRACK_CAR_CTOL(0,0,0,0,0,500);
				/*赋予坐标值*/
        CAR.CUR_COR.X_COR=6;
        CAR.CUR_COR.Y_COR=3;
        TRACK.STATE=TRACK_GO_FETCH_BRICK_6;
				//PlatformControl(2,0,50);//平台下降
				TRACK_CAR_CTOL(0,0,0,0,0,1000);
			}
		}
		break;
		//转向180
		case TRACK_GO_FETCH_BRICK_6:
		{
      while(!TRACK_TURN_ANGLE(50,56));
      TRACK_CAR_CTOL(0,2,0,0,0,1000);			
			S_ADJUST();								//调整完毕
			TRACK_CAR_CTOL(0,0,0,0,0,500);
			TRACK.STATE=FETCH_OVER_3;	
		}
		break;
		case FETCH_OVER_3:
    {
      /*坐标法到达 4，4*/
      TRACK_COR_GO(4,4,5000,5000);
      if(TRACK.ARRIVE==ARRIVED)
      {
        CAR.V.VX=0;
        CAR.V.VY=0;
			  TRACK_CAR_CTOL(0,0,0,0,0,500);
        P_ADJUST();								//调整完毕
			  TRACK_CAR_CTOL(0,0,0,0,0,500);
        TRACK.STATE=GO_STORE_BRIKE;
      }
	  }
		break;	
		//储存己方积木块
		case GO_STORE_BRIKE:
	  {
		  CAR.V.VX=0;
      CAR.V.VY=-2000;
			if(DIGITAL16_GRAY_3.digital16_gray_state.STATE.L5==1&&DIGITAL16_GRAY_3.digital16_gray_state.STATE.L14==1&&DIGITAL16_GRAY_3.digital16_gray_state.STATE.L6==1)
			{
				CAR.V.VX=0;
        CAR.V.VY=0;				
				TRACK_CAR_CTOL(0,0,0,0,0,500);
				while(!TRACK_GO_STEP(-1500,0,30));
				CAR.V.VX=0;
        CAR.V.VY=0;	
				TRACK_CAR_CTOL(0,0,0,0,0,500);
				TRACK.STATE=STORE_BRIKE;
			}	
		}
		break;
		case STORE_BRIKE:
		{
		  Duoji_angle(0x07, 680, 900);
			TRACK_CAR_CTOL(0,0,0,0,0,2500);
			Duoji_angle(0x07, 120, 900);
			while(!TRACK_GO_STEP(1500,0,30));
      CAR.V.VX=0;
      CAR.V.VY=0;	
			TRACK_CAR_CTOL(0,0,0,0,0,500);
			//PlatformControl(1,0,50);//平台上升回原位
			TRACK.STATE=STORE_OVER_BACK_ONLINE_3;
		}
		break;
		case STORE_OVER_BACK_ONLINE_3:
		{
      TRACK_CAR_CTOL(0,2,0,0,0,0);	
      while(!TRACK_GO_STEP(0,3500,40));
      TRACK_CAR_CTOL(0,2,0,0,0,200);	
      S_ADJUST();								//调整完毕
			TRACK_CAR_CTOL(0,0,0,0,0,500);
      CAR.CUR_COR.X_COR=4;
      CAR.CUR_COR.Y_COR=4;
      TRACK.STATE=TRACK_GO_FETCH_BRICK_YELLOWBALL;
		}
		break;
		//抓黄球
		case TRACK_GO_FETCH_BRICK_YELLOWBALL:
        {
            /*坐标法到达 6，4*/
            TRACK_COR_GO(6,4,5000,5000);
            if(TRACK.ARRIVE==ARRIVED)
            {
                TRACK_CAR_CTOL(0,2,0,0,0,1000);
                S_ADJUST();								//调整完毕
			          TRACK_CAR_CTOL(0,0,0,0,0,500);
                TRACK.STATE=TRACK_GO_FETCH_BRICK_YELLOWBALL_2;
            }
	    }
		break;	
		//转向180
				case TRACK_GO_FETCH_BRICK_YELLOWBALL_2:
		{
         while(!TRACK_TURN_ANGLE(50,56));
			   TRACK_CAR_CTOL(0,2,0,0,0,1000);
			   S_ADJUST();								//调整完毕
			   TRACK_CAR_CTOL(0,0,0,0,0,500);
				 TRACK.STATE=TRACK_GO_FETCH_BRICK_YELLOWBALL_3;	
		}
			break;			
			/*慢速向右到抓取位置*/
		case TRACK_GO_FETCH_BRICK_YELLOWBALL_3:
		{
				  while(!TRACK_GO_STEP(0,2000,35));
          TRACK_CAR_CTOL(0,2,0,0,0,1000);
          TRACK.color=1;
				  S_ADJUST();								//调整完毕
			    TRACK_CAR_CTOL(0,0,0,0,0,500);
				  TRACK.STATE=TRACK_FETCH_BRICK_3;			
		}
			break;
				/* 往前*/
		case TRACK_FETCH_BRICK_3:
		{
			TRACK_CAR_CTOL(0,0,-2000,0,0,0);
			if(LASER.laser_value[1]<=100)
			{
          TRACK_CAR_CTOL(0,0,0,0,0,2000);
          TRACK.color=1;
				  TRACK.STATE=WAITING_FUCK_BRIKE_3;
			}	
		}
		break;
			case WAITING_FUCK_BRIKE_3:
				{
					waiting_fetch_cube();
					//HAL_Delay(1000);
					//TRACK_CAR_CTOL(0,0,0,2000,0,10);
					finish_fetch(6);
					TRACK.STATE=FETCH_BRICK_OVER_BACK_ONLINE_3;
		    }
		break;
		//		/*抓取完成 返回到 线上 更新坐标*/
		case FETCH_BRICK_OVER_BACK_ONLINE_3:
		{ 
      //TRACK.color=3;
			TRACK_CAR_CTOL(0,0,2000,0,0,0);
			if(DIGITAL16_GRAY_2.digital16_gray_state.STATE.L8==1&&DIGITAL16_GRAY_2.digital16_gray_state.STATE.L9==1)
			{
				//CAR.CUR_POS=ON_Y;
        TRACK_CAR_CTOL(0,2,0,0,0,0);
				S_ADJUST();								//调整完毕
			  TRACK_CAR_CTOL(0,0,0,0,0,500);
				/*赋予坐标值*/
        CAR.CUR_COR.X_COR=6;
        CAR.CUR_COR.Y_COR=3;
        TRACK.STATE=TRACK_GO_FETCH_BRICK_YELLOWBALL_4;
				PlatformControl(2,0,50);//平台下降
				TRACK_CAR_CTOL(0,0,0,0,0,1000);
			}
		}
		break;
				//转向180
				case TRACK_GO_FETCH_BRICK_YELLOWBALL_4:
		{
         while(!TRACK_TURN_ANGLE(50,56));
         TRACK_CAR_CTOL(0,2,0,0,0,1000);			
			   S_ADJUST();								//调整完毕
			   TRACK_CAR_CTOL(0,0,0,0,0,500);
				 TRACK.STATE=FETCH_OVER_4;	
		}
			break;
			case FETCH_OVER_4:
        {
            /*坐标法到达 4，4*/
            TRACK_COR_GO(4,4,5000,5000);
            if(TRACK.ARRIVE==ARRIVED)
            {
                CAR.V.VX=0;
                CAR.V.VY=0;
							  TRACK_CAR_CTOL(0,0,0,0,0,500);
                P_ADJUST();								//调整完毕
			          TRACK_CAR_CTOL(0,0,0,0,0,500);
                TRACK.STATE=GO_STORE_BRIKE_YELLOWBALL;
            }
	    }
		break;	
			//储存黄球
		case GO_STORE_BRIKE_YELLOWBALL:
			{
		  CAR.V.VX=0;
      CAR.V.VY=-2000;
		  if(DIGITAL16_GRAY_3.digital16_gray_state.STATE.L5==1&&DIGITAL16_GRAY_3.digital16_gray_state.STATE.L4==1)
			{
        CAR.V.VX=0;
        CAR.V.VY=0;				
				TRACK_CAR_CTOL(0,0,0,0,0,1500);
				while(!TRACK_GO_STEP(-1500,0,30));
				CAR.V.VX=0;
        CAR.V.VY=0;	
				TRACK.STATE=STORE_BRIKE_YELLOWBALL;
			}	
		}
			break;
			case STORE_BRIKE_YELLOWBALL:
			{
				Duoji_angle(0x07, 500, 900);
				TRACK_CAR_CTOL(0,0,0,0,0,2500);
				Duoji_angle(0x07, 120, 900);
				while(!TRACK_GO_STEP(1500,0,30));
        CAR.V.VX=0;
        CAR.V.VY=0;	
				TRACK_CAR_CTOL(0,0,0,0,0,500);
				TRACK.STATE=STORE_OVER_BACK_ONLINE_4;
			}
			break;
			case STORE_OVER_BACK_ONLINE_4:
			{
          TRACK_CAR_CTOL(0,2,0,0,0,0);	
          while(!TRACK_GO_STEP(0,-3500,63));
          TRACK_CAR_CTOL(0,2,0,0,0,200);	
          S_ADJUST();								//调整完毕
			    TRACK_CAR_CTOL(0,0,0,0,0,500);
          CAR.CUR_COR.X_COR=4;
          CAR.CUR_COR.Y_COR=2;
          TRACK.STATE=BACK;
			}
			break;
		/*case Bizhang:
    {
      //坐标法到达 x，y
      TRACK_COR_GO(6,2,5000,5000);
      if(TRACK.ARRIVE==ARRIVED)
      {
        TRACK_CAR_CTOL(0,2,0,0,0,1000);
        CAR.V_ADJUST.p_ok=0;
				while(!PRECISE_ADJUST_OK());
        TRACK.STATE=Bizhang_1;
      }
	  }
		break;
				case Bizhang_1:
    {
      TRACK_CAR_CTOL(0,0,0,-2000,0,0);
      if(LASER.laser_value[3]<=200)
      {
        TRACK_CAR_CTOL(0,0,0,0,0,500);
				
        //CAR.V_ADJUST.p_ok=0;
				//while(!PRECISE_ADJUST_OK()); 
				
        TRACK.STATE=Bizhang_2;
      }
	  }
		break;
				case Bizhang_2:
    {
      if(LASER.laser_value[3]>=200)
      {
        TRACK_CAR_CTOL(0,0,0,0,0,500);
				CAR.CUR_COR.X_COR=6;
        CAR.CUR_COR.Y_COR=1;
        TRACK.STATE=BACK;
      }
			else
			{
				TRACK.STATE=Bizhang_2;
			}
	  }
		break;
		*/
		case BACK:
    {
      /*坐标法到达 4，0*/
      TRACK_COR_GO(4,0,5000,5000);
      if(TRACK.ARRIVE==ARRIVED)
      {
        TRACK_CAR_CTOL(0,2,0,0,0,1000);
        P_ADJUST();								//调整完毕
			  TRACK_CAR_CTOL(0,0,0,0,0,500);
        TRACK.STATE=FINISH;
      }
	  }
		break;
		case FINISH:
    {
      while(!TRACK_GO_STEP(3000,-1500,68));
      TRACK_CAR_CTOL(0,0,0,0,0,0);
			//CAR.CUR_COR.X_COR=0;
      //CAR.CUR_COR.Y_COR=0;
      TRACK.STATE=FINISH_2;
			//PlatformControl(2,0,50);//平台下降一半
	  }
		break;
		/*结束*/
		case FINISH_2:
		{
		}
		break;
	}
}
/*蓝色方先蓝球再黄球再积木*/
void TRACK_MODULE_BLUE_BY(void)
{
	switch(TRACK.STATE)
	{
    /*从出发区前往线上，坐标 5 6*/
		case START:
		{
      TRACK_CAR_CTOL(0,0,0,-2000,0,0);
			if(DIGITAL16_GRAY_3.digital16_gray_state.STATE.L8==1&&DIGITAL16_GRAY_3.digital16_gray_state.STATE.L9==1)
			{		
				TRACK_CAR_CTOL(0,2,0,0,0,100);
				S_ADJUST();								//调整完毕
			  TRACK_CAR_CTOL(0,0,0,0,0,500);
				CAR.CUR_COR.X_COR=5;
        CAR.CUR_COR.Y_COR=6;
				TRACK.STATE=TRACK_GO_FETCH_BALL_BLUE;
				PlatformControl(1, 0, 0);
			}	          
		}		
		break;
		 /*坐标法到达 4，4准备过储存区*/
        case TRACK_GO_FETCH_BALL_BLUE:
        {
            TRACK_COR_GO(4,4,5000,5000);
            if(TRACK.ARRIVE==ARRIVED)
            {
                TRACK_CAR_CTOL(0,2,0,0,0,100);
                P_ADJUST();								//调整完毕
			          TRACK_CAR_CTOL(0,0,0,0,0,500);
                TRACK.STATE=TRACK_GO_FETCH_BALL_BLUE_2;
            }
	    }
		break;	
			     /*硬延时过储存区*/
        case TRACK_GO_FETCH_BALL_BLUE_2:
        {
					TRACK_CAR_CTOL(0,2,0,0,0,0);	
          while(!TRACK_GO_STEP(0,-3500,100));
          TRACK_CAR_CTOL(0,2,0,0,0,0);	
          S_ADJUST();								//调整完毕
			    TRACK_CAR_CTOL(0,0,0,0,0,500);
          CAR.CUR_COR.X_COR=4;
          CAR.CUR_COR.Y_COR=2;
          TRACK.STATE=TRACK_GO_FETCH_BALL_BLUE_3;
	    }
		break;	
			/*坐标法到达 4，0*/
				case TRACK_GO_FETCH_BALL_BLUE_3:
			{
            TRACK_COR_GO(4,0,5000,5000);
				
            if(TRACK.ARRIVE==ARRIVED)
            {
                TRACK_CAR_CTOL(0,2,0,0,0,1000);
                S_ADJUST();								//调整完毕
			          TRACK_CAR_CTOL(0,0,0,0,0,500);
                TRACK.STATE=TRACK_FETCH_BALL_BLUE;
            }
			}
			break;
					/*慢速前进到抓取位置*/
		case TRACK_FETCH_BALL_BLUE:
		{				
						
       TRACK_CAR_CTOL(0,0,-1000,0,0,0);
			/*三号灰度 L1 L2灰度落在白线，并且有一激光小于12cm*/
			if(LASER.laser_value[1]<=90)
			{	
								TRACK_CAR_CTOL(0,0,0,0,0,500);							
                TRACK.color=1;
								TRACK.STATE=WAITING_FUCK_BALL_BLUE;				
			}
		}
		break;
		case WAITING_FUCK_BALL_BLUE:
			{
					waiting_fetch_ball();
					HAL_Delay(500);
					finish_fetch(2);		    
					TRACK.STATE=FETCH_BALL_OVER_BLUE;
			    PlatformControl(2,0,50);//平台下降以便放球
		}
		break;
		//		/*抓取完成 更新当前位置与坐标*/
		case FETCH_BALL_OVER_BLUE:
		{ 
      //TRACK.color=3;
			while(!TRACK_GO_STEP(1500,0,15));
			if(CAR.CUR_POS==ON_X)
     {
			  TRACK_CAR_CTOL(0,2,0,0,0,200);
				S_ADJUST();								//调整完毕
			  TRACK_CAR_CTOL(0,0,0,0,0,500);
				/*赋予坐标值*/
        CAR.CUR_COR.X_COR=3;
        CAR.CUR_COR.Y_COR=0;
        TRACK.STATE=FETCH_OVER_1;
			  TRACK_CAR_CTOL(0,0,0,0,0,500);
     }
		if(CAR.CUR_POS==Yminus_CENTER)
     {
			  TRACK_CAR_CTOL(0,2,0,0,0,200);
				S_ADJUST();								//调整完毕
			  TRACK_CAR_CTOL(0,0,0,0,0,500);
				/*赋予坐标值*/
        CAR.CUR_COR.X_COR=4;
        CAR.CUR_COR.Y_COR=0;
        TRACK.STATE=FETCH_OVER_1;
			  TRACK_CAR_CTOL(0,0,0,0,0,500);
     }
		}
		break;
			case FETCH_OVER_1:
        {
            /*坐标法到达 4，2*/
            TRACK_COR_GO(4,2,5000,5000);
            if(TRACK.ARRIVE==ARRIVED)
            {
                //CAR.V.VX=0;
                //CAR.V.VY=0;
							  TRACK_CAR_CTOL(0,0,0,0,0,500);
                S_ADJUST();								//调整完毕
			          TRACK_CAR_CTOL(0,0,0,0,0,500);
                TRACK.STATE=GO_STORE_BLUE;
            }
	    }
		break;
		//储存本色球
		case GO_STORE_BLUE:
			{
				CAR.V.VX=0;
        CAR.V.VY=2000;
				if(DIGITAL16_GRAY_3.digital16_gray_state.STATE.L5==1&&DIGITAL16_GRAY_3.digital16_gray_state.STATE.L14==1&&DIGITAL16_GRAY_3.digital16_gray_state.STATE.L6==1)
			{
        CAR.V.VX=0;
        CAR.V.VY=0;				
				TRACK_CAR_CTOL(0,0,0,0,0,1500);
				while(!TRACK_GO_STEP(-1500,0,30));
				CAR.V.VX=0;
        CAR.V.VY=0;	
				TRACK.STATE=STORE_BLUE;
			}	
			}
			break;
			case STORE_BLUE:
			{
				Duoji_angle(0x07, 500, 900);
				TRACK_CAR_CTOL(0,0,0,0,0,2500);
				Duoji_angle(0x07, 220, 900);
				while(!TRACK_GO_STEP(1500,0,30));
        CAR.V.VX=0;
        CAR.V.VY=0;	
				TRACK.STATE=STORE_OVER_BACK_ONLINE;
				PlatformControl(1,0,50);//平台上升到原位
			}
			break;
			case STORE_OVER_BACK_ONLINE:
			{
          TRACK_CAR_CTOL(0,2,0,0,0,0);	
          while(!TRACK_GO_STEP(0,-3500,60));
          TRACK_CAR_CTOL(0,2,0,0,0,0);	
          S_ADJUST();								//调整完毕
			    TRACK_CAR_CTOL(0,0,0,0,0,500);
          CAR.CUR_COR.X_COR=4;
          CAR.CUR_COR.Y_COR=2;
          TRACK.STATE=TRACK_GO_FETCH_BALL_YELLOW;
			}
			break;
			/*坐标法到达 4，0*/
				case TRACK_GO_FETCH_BALL_YELLOW:
			{
            TRACK_COR_GO(4,0,5000,5000);
				
            if(TRACK.ARRIVE==ARRIVED)
            {
                TRACK_CAR_CTOL(0,2,0,0,0,1000);
                S_ADJUST();								//调整完毕
			          TRACK_CAR_CTOL(0,0,0,0,0,500);
                TRACK.STATE=TRACK_GO_FETCH_BALL_YELLOW_2;
            }
			}
			break;
					/*慢速前进到抓取位置*/
		case TRACK_GO_FETCH_BALL_YELLOW_2:
		{				
						
       TRACK_CAR_CTOL(0,0,-1000,0,0,0);
			/*三号灰度 L1 L2灰度落在白线，并且有一激光小于12cm*/
			if(LASER.laser_value[1]<=90)
			{	
								TRACK_CAR_CTOL(0,0,0,0,0,1000);
							
                TRACK.color=1;
							TRACK.STATE=WAITING_FUCK_BALL_YELLOW;
								
			}
		}
		break;
		case WAITING_FUCK_BALL_YELLOW:{
					waiting_fetch_ball();
					HAL_Delay(1000);
					finish_fetch(3); 
					TRACK.STATE=FETCH_BALL_OVER_YELLOW;
					PlatformControl(2,0,50);//平台下降以便放球
		}
		break;
		//		/*抓取完成 更新当前位置与坐标*/
		case FETCH_BALL_OVER_YELLOW:
		{ 
      //TRACK.color=3;
			while(!TRACK_GO_STEP(1500,0,15));
			TRACK_CAR_CTOL(1,1,0,0,0,500);
			if(CAR.CUR_POS==ON_X)
     {
			  TRACK_CAR_CTOL(0,2,0,0,0,200);
				S_ADJUST();								//调整完毕
			  TRACK_CAR_CTOL(0,0,0,0,0,500);
				/*赋予坐标值*/
        CAR.CUR_COR.X_COR=3;
        CAR.CUR_COR.Y_COR=0;
        TRACK.STATE=FETCH_OVER_2;
			  TRACK_CAR_CTOL(0,0,0,0,0,500);
     }
		if(CAR.CUR_POS==Yminus_CENTER)
     {
			  TRACK_CAR_CTOL(0,2,0,0,0,200);
				S_ADJUST();								//调整完毕
			  TRACK_CAR_CTOL(0,0,0,0,0,500);
				/*赋予坐标值*/
        CAR.CUR_COR.X_COR=4;
        CAR.CUR_COR.Y_COR=0;
        TRACK.STATE=FETCH_OVER_2;
			  TRACK_CAR_CTOL(0,0,0,0,0,1000);
     }
		}
		break;
			case FETCH_OVER_2:
        {
            /*坐标法到达 4，2*/
            TRACK_COR_GO(4,2,5000,5000);
            if(TRACK.ARRIVE==ARRIVED)
            {
                //CAR.V.VX=0;
                //CAR.V.VY=0;
							  TRACK_CAR_CTOL(0,0,0,0,0,500);
                S_ADJUST();								//调整完毕
			          TRACK_CAR_CTOL(0,0,0,0,0,500);
                TRACK.STATE=GO_STORE_YELLOW;
            }
	    }
		break;
		//储存黄色球
		case GO_STORE_YELLOW:
			{
				CAR.V.VX=0;
        CAR.V.VY=2000;
				if(DIGITAL16_GRAY_3.digital16_gray_state.STATE.L5==1&&DIGITAL16_GRAY_3.digital16_gray_state.STATE.L14==1&&DIGITAL16_GRAY_3.digital16_gray_state.STATE.L6==1)
			{
        CAR.V.VX=0;
        CAR.V.VY=0;				
				TRACK_CAR_CTOL(0,0,0,0,0,1500);
				TRACK.STATE=GO_STORE_YELLOW_2;
			}	
			}
			break;
			case GO_STORE_YELLOW_2:
			{
				CAR.V.VX=0;
        CAR.V.VY=2000;
				if(DIGITAL16_GRAY_3.digital16_gray_state.STATE.L5==1&&DIGITAL16_GRAY_3.digital16_gray_state.STATE.L14!=1&&DIGITAL16_GRAY_3.digital16_gray_state.STATE.L15!=1&&DIGITAL16_GRAY_3.digital16_gray_state.STATE.L6==1)
			{
        CAR.V.VX=0;
        CAR.V.VY=0;				
				TRACK_CAR_CTOL(0,0,0,0,0,1500);
				while(!TRACK_GO_STEP(-1500,0,30));
				CAR.V.VX=0;
        CAR.V.VY=0;	
				TRACK.STATE=STORE_YELLOW;
			}	
			}
			break;
			case STORE_YELLOW:
			{
				Duoji_angle(0x07, 500, 900);
				TRACK_CAR_CTOL(0,0,0,0,0,2500);
				Duoji_angle(0x07, 120, 900);
				while(!TRACK_GO_STEP(1500,0,30));
        CAR.V.VX=0;
        CAR.V.VY=0;	
				TRACK.STATE=STORE_OVER_BACK_ONLINE_2;
				PlatformControl(1,0,50);//平台上升到原位
			}
			break;
			case STORE_OVER_BACK_ONLINE_2:
			{
          TRACK_CAR_CTOL(0,2,0,0,0,0);	
          while(!TRACK_GO_STEP(0,3500,35));
          TRACK_CAR_CTOL(0,2,0,0,0,0);	
          S_ADJUST();								//调整完毕
			    TRACK_CAR_CTOL(0,0,0,0,0,500);
          CAR.CUR_COR.X_COR=4;
          CAR.CUR_COR.Y_COR=4;
          TRACK.STATE=TRACK_GO_FETCH_BRICK;
			}
			break;
    case TRACK_GO_FETCH_BRICK:
    {
      /*坐标法到达 6，4*/
      TRACK_COR_GO(6,4,5000,5000);
      if(TRACK.ARRIVE==ARRIVED)
      {
        TRACK_CAR_CTOL(0,2,0,0,0,1000);
        S_ADJUST();								//调整完毕
			  TRACK_CAR_CTOL(0,0,0,0,0,500);
        TRACK.STATE=TRACK_GO_FETCH_BRICK_2;
      }
	  }
		break;	
		//转向180
		case TRACK_GO_FETCH_BRICK_2:
		{
      TRACK_CAR_CTOL(0,0,0,0,70,1500);
			TRACK_CAR_CTOL(0,2,0,0,0,1000);
			S_ADJUST();								//调整完毕
			TRACK_CAR_CTOL(0,0,0,0,0,500);
			TRACK.STATE=TRACK_GO_FETCH_BRICK_3;	
		}
		break;			
		/*慢速向右到抓取位置*/
		case TRACK_GO_FETCH_BRICK_3:
		{
		  while(!TRACK_GO_STEP(0,2000,35));
      TRACK_CAR_CTOL(0,2,0,0,0,1000);
      TRACK.color=1;
		  S_ADJUST();								//调整完毕
			TRACK_CAR_CTOL(0,0,0,0,0,500);
			TRACK.STATE=TRACK_FETCH_BRICK;			
		}
		break;
	  /* 往前*/
		case TRACK_FETCH_BRICK:
		{
			TRACK_CAR_CTOL(0,0,-1000,0,0,0);
			if(LASER.laser_value[1]<=100)
			{
        TRACK_CAR_CTOL(0,0,0,0,0,2000);
        TRACK.color=1;
				TRACK.STATE=WAITING_FUCK_BRIKE;
			}	
		}
		break;
		case WAITING_FUCK_BRIKE:
		{
		  waiting_fetch_cube();
			//HAL_Delay(1000);
			//TRACK_CAR_CTOL(0,0,0,2000,0,10);
			finish_fetch(5);
			TRACK.STATE=FETCH_BRICK_OVER_BACK_ONLINE;
		}
		break;
		//		/*抓取完成 返回到 线上 更新坐标*/
		case FETCH_BRICK_OVER_BACK_ONLINE:
		{ 
      //TRACK.color=3;
			TRACK_CAR_CTOL(0,0,2000,0,0,0);
			if(DIGITAL16_GRAY_2.digital16_gray_state.STATE.L8==1&&DIGITAL16_GRAY_2.digital16_gray_state.STATE.L9==1)
			{
				//CAR.CUR_POS=ON_Y;
        TRACK_CAR_CTOL(0,2,0,0,0,0);
				S_ADJUST();								//调整完毕
			  TRACK_CAR_CTOL(0,0,0,0,0,500);
				/*赋予坐标值*/
        CAR.CUR_COR.X_COR=6;
        CAR.CUR_COR.Y_COR=3;
        TRACK.STATE=TRACK_GO_FETCH_BRICK_4;
				TRACK_CAR_CTOL(0,0,0,0,0,2000);
			}
		}
		break;
		case TRACK_GO_FETCH_BRICK_4:
		{
      TRACK_CAR_CTOL(0,0,0,-2000,0,0);
			if(DIGITAL16_GRAY_1.digital16_gray_state.STATE.L8==1)
			{		
			TRACK_CAR_CTOL(0,0,0,0,0,100);
			S_ADJUST();								//调整完毕
			TRACK_CAR_CTOL(0,0,0,0,0,500);
			TRACK.STATE=TRACK_GO_FETCH_BRICK_5;	
		  }
		}
		break;
			/*慢速向右到抓取位置*/
		case TRACK_GO_FETCH_BRICK_5:
		{
		  while(!TRACK_GO_STEP(0,2000,35));
      TRACK_CAR_CTOL(0,2,0,0,0,1000);
      TRACK.color=1;
		  S_ADJUST();								//调整完毕
			TRACK_CAR_CTOL(0,0,0,0,0,500);
			TRACK.STATE=TRACK_FETCH_BRICK_2;			
		}
		break;
	  /* 往前*/
		case TRACK_FETCH_BRICK_2:
		{
			TRACK_CAR_CTOL(0,0,-1000,0,0,0);
			if(LASER.laser_value[1]<=100)
			{
        TRACK_CAR_CTOL(0,0,0,0,0,2000);
        TRACK.color=1;
				TRACK.STATE=WAITING_FUCK_BRIKE_2;
			}	
		}
		break;
		case WAITING_FUCK_BRIKE_2:
		{
		  waiting_fetch_cube();
			//HAL_Delay(1000);
			//TRACK_CAR_CTOL(0,0,0,2000,0,10);
			finish_fetch(8);
			TRACK.STATE=FETCH_BRICK_OVER_BACK_ONLINE_2;
		}
		break;
		//		/*抓取完成 返回到 线上 更新坐标*/
		case FETCH_BRICK_OVER_BACK_ONLINE_2:
		{ 
      //TRACK.color=3;
			TRACK_CAR_CTOL(0,0,2000,0,0,0);
			if(DIGITAL16_GRAY_2.digital16_gray_state.STATE.L8==1&&DIGITAL16_GRAY_2.digital16_gray_state.STATE.L9==1)
			{
				//CAR.CUR_POS=ON_Y;
        TRACK_CAR_CTOL(0,2,0,0,0,0);
				S_ADJUST();								//调整完毕
			  TRACK_CAR_CTOL(0,0,0,0,0,500);
				/*赋予坐标值*/
        CAR.CUR_COR.X_COR=6;
        CAR.CUR_COR.Y_COR=3;
        TRACK.STATE=TRACK_GO_FETCH_BRICK_6;
				//PlatformControl(2,0,50);//平台下降
				TRACK_CAR_CTOL(0,0,0,0,0,1000);
			}
		}
		break;
		//转向180
		case TRACK_GO_FETCH_BRICK_6:
		{
      TRACK_CAR_CTOL(0,0,0,0,70,1500);
      TRACK_CAR_CTOL(0,2,0,0,0,1000);			
			S_ADJUST();								//调整完毕
			TRACK_CAR_CTOL(0,0,0,0,0,500);
			TRACK.STATE=FETCH_OVER_3;	
		}
		break;
		case FETCH_OVER_3:
    {
      /*坐标法到达 4，2*/
      TRACK_COR_GO(4,2,5000,5000);
      if(TRACK.ARRIVE==ARRIVED)
      {
        CAR.V.VX=0;
        CAR.V.VY=0;
			  TRACK_CAR_CTOL(0,0,0,0,0,500);
        P_ADJUST();								//调整完毕
			  TRACK_CAR_CTOL(0,0,0,0,0,500);
        TRACK.STATE=GO_STORE_BRIKE;
      }
	  }
		break;	
		//储存己方积木块
		case GO_STORE_BRIKE:
	  {
		  CAR.V.VX=0;
      CAR.V.VY=2000;
			if(DIGITAL16_GRAY_3.digital16_gray_state.STATE.L3==1&&DIGITAL16_GRAY_3.digital16_gray_state.STATE.L12==1&&DIGITAL16_GRAY_3.digital16_gray_state.STATE.L4==1)
			{
				CAR.V.VX=0;
        CAR.V.VY=0;				
				TRACK_CAR_CTOL(0,0,0,0,0,500);
				while(!TRACK_GO_STEP(-1500,0,30));
				CAR.V.VX=0;
        CAR.V.VY=0;	
				TRACK_CAR_CTOL(0,0,0,0,0,500);
				TRACK.STATE=STORE_BRIKE;
			}	
		}
		break;
		case STORE_BRIKE:
		{
		  Duoji_angle(0x07, 680, 900);
			TRACK_CAR_CTOL(0,0,0,0,0,2500);
			Duoji_angle(0x07, 120, 900);
			while(!TRACK_GO_STEP(1500,0,30));
      CAR.V.VX=0;
      CAR.V.VY=0;	
			TRACK_CAR_CTOL(0,0,0,0,0,500);
			//PlatformControl(1,0,50);//平台上升回原位
			TRACK.STATE=STORE_OVER_BACK_ONLINE_3;
		}
		break;
		case STORE_OVER_BACK_ONLINE_3:
		{
      TRACK_CAR_CTOL(0,2,0,0,0,0);	
      while(!TRACK_GO_STEP(0,3500,40));
      TRACK_CAR_CTOL(0,2,0,0,0,200);	
      S_ADJUST();								//调整完毕
			TRACK_CAR_CTOL(0,0,0,0,0,500);
      CAR.CUR_COR.X_COR=4;
      CAR.CUR_COR.Y_COR=4;
      TRACK.STATE=TRACK_GO_FETCH_BRICK_YELLOWBALL;
		}
		break;
		//抓黄球
		case TRACK_GO_FETCH_BRICK_YELLOWBALL:
        {
            /*坐标法到达 6，4*/
            TRACK_COR_GO(6,4,5000,5000);
            if(TRACK.ARRIVE==ARRIVED)
            {
                TRACK_CAR_CTOL(0,2,0,0,0,1000);
                S_ADJUST();								//调整完毕
			          TRACK_CAR_CTOL(0,0,0,0,0,500);
                TRACK.STATE=TRACK_GO_FETCH_BRICK_YELLOWBALL_2;
            }
	    }
		break;	
		//转向180
				case TRACK_GO_FETCH_BRICK_YELLOWBALL_2:
		{
         TRACK_CAR_CTOL(0,0,0,0,70,1500);
			   TRACK_CAR_CTOL(0,2,0,0,0,1000);
			   S_ADJUST();								//调整完毕
			   TRACK_CAR_CTOL(0,0,0,0,0,500);
				 TRACK.STATE=TRACK_GO_FETCH_BRICK_YELLOWBALL_3;	
		}
			break;			
			/*慢速向右到抓取位置*/
		case TRACK_GO_FETCH_BRICK_YELLOWBALL_3:
		{
				  while(!TRACK_GO_STEP(0,2000,35));
          TRACK_CAR_CTOL(0,2,0,0,0,1000);
          TRACK.color=1;
				  S_ADJUST();								//调整完毕
			    TRACK_CAR_CTOL(0,0,0,0,0,500);
				  TRACK.STATE=TRACK_FETCH_BRICK_3;			
		}
			break;
				/* 往前*/
		case TRACK_FETCH_BRICK_3:
		{
			TRACK_CAR_CTOL(0,0,-1000,0,0,0);
			if(LASER.laser_value[1]<=100)
			{
          TRACK_CAR_CTOL(0,0,0,0,0,2000);
          TRACK.color=1;
				  TRACK.STATE=WAITING_FUCK_BRIKE_3;
			}	
		}
		break;
			case WAITING_FUCK_BRIKE_3:
				{
					waiting_fetch_cube();
					//HAL_Delay(1000);
					//TRACK_CAR_CTOL(0,0,0,2000,0,10);
					finish_fetch(6);
					TRACK.STATE=FETCH_BRICK_OVER_BACK_ONLINE_3;
		    }
		break;
		//		/*抓取完成 返回到 线上 更新坐标*/
		case FETCH_BRICK_OVER_BACK_ONLINE_3:
		{ 
      //TRACK.color=3;
			TRACK_CAR_CTOL(0,0,2000,0,0,0);
			if(DIGITAL16_GRAY_2.digital16_gray_state.STATE.L8==1&&DIGITAL16_GRAY_2.digital16_gray_state.STATE.L9==1)
			{
				//CAR.CUR_POS=ON_Y;
        TRACK_CAR_CTOL(0,2,0,0,0,0);
				S_ADJUST();								//调整完毕
			  TRACK_CAR_CTOL(0,0,0,0,0,500);
				/*赋予坐标值*/
        CAR.CUR_COR.X_COR=6;
        CAR.CUR_COR.Y_COR=3;
        TRACK.STATE=TRACK_GO_FETCH_BRICK_YELLOWBALL_4;
				PlatformControl(2,0,50);//平台下降
				TRACK_CAR_CTOL(0,0,0,0,0,1000);
			}
		}
		break;
				//转向180
				case TRACK_GO_FETCH_BRICK_YELLOWBALL_4:
		{
         TRACK_CAR_CTOL(0,0,0,0,70,1500);
         TRACK_CAR_CTOL(0,2,0,0,0,1000);			
			   S_ADJUST();								//调整完毕
			   TRACK_CAR_CTOL(0,0,0,0,0,500);
				 TRACK.STATE=FETCH_OVER_4;	
		}
			break;
			case FETCH_OVER_4:
        {
            /*坐标法到达 4，2*/
            TRACK_COR_GO(4,2,5000,5000);
            if(TRACK.ARRIVE==ARRIVED)
            {
                CAR.V.VX=0;
                CAR.V.VY=0;
							  TRACK_CAR_CTOL(0,0,0,0,0,500);
                P_ADJUST();								//调整完毕
			          TRACK_CAR_CTOL(0,0,0,0,0,500);
                TRACK.STATE=GO_STORE_BRIKE_YELLOWBALL;
            }
	    }
		break;	
			//储存黄球
		case GO_STORE_BRIKE_YELLOWBALL:
			{
				CAR.V.VX=0;
        CAR.V.VY=2000;
				if(DIGITAL16_GRAY_3.digital16_gray_state.STATE.L5==1&&DIGITAL16_GRAY_3.digital16_gray_state.STATE.L14==1&&DIGITAL16_GRAY_3.digital16_gray_state.STATE.L6==1)
			{
        CAR.V.VX=0;
        CAR.V.VY=0;				
				TRACK_CAR_CTOL(0,0,0,0,0,1500);
				TRACK.STATE=GO_STORE_BRIKE_YELLOWBALL_2;
			}	
			}
			break;
			case GO_STORE_BRIKE_YELLOWBALL_2:
			{
				CAR.V.VX=0;
        CAR.V.VY=2000;
				if(DIGITAL16_GRAY_3.digital16_gray_state.STATE.L5==1&&DIGITAL16_GRAY_3.digital16_gray_state.STATE.L14!=1&&DIGITAL16_GRAY_3.digital16_gray_state.STATE.L15!=1&&DIGITAL16_GRAY_3.digital16_gray_state.STATE.L6==1)
			{
        CAR.V.VX=0;
        CAR.V.VY=0;	
				while(!TRACK_GO_STEP(-1500,0,30));
				CAR.V.VX=0;
        CAR.V.VY=0;	
				TRACK.STATE=STORE_BRIKE_YELLOWBALL;
			}	
			}
			break;
			case STORE_BRIKE_YELLOWBALL:
			{
				Duoji_angle(0x07, 500, 900);
				TRACK_CAR_CTOL(0,0,0,0,0,2500);
				Duoji_angle(0x07, 120, 900);
				while(!TRACK_GO_STEP(1500,0,30));
        CAR.V.VX=0;
        CAR.V.VY=0;	
				TRACK_CAR_CTOL(0,0,0,0,0,500);
				TRACK.STATE=STORE_OVER_BACK_ONLINE_4;
			}
			break;
			case STORE_OVER_BACK_ONLINE_4:
			{
          TRACK_CAR_CTOL(0,2,0,0,0,0);	
          while(!TRACK_GO_STEP(0,3500,35));
          TRACK_CAR_CTOL(0,2,0,0,0,0);	
          S_ADJUST();								//调整完毕
			    TRACK_CAR_CTOL(0,0,0,0,0,500);
					TRACK_CAR_CTOL(0,0,0,0,0,0);
          CAR.CUR_COR.X_COR=4;
          CAR.CUR_COR.Y_COR=4;
          TRACK.STATE=BACK;
			}
			break;
	/*case Bizhang:
    {
      //坐标法到达 x，y
      TRACK_COR_GO(6,2,5000,5000);
      if(TRACK.ARRIVE==ARRIVED)
      {
        TRACK_CAR_CTOL(0,2,0,0,0,1000);
        CAR.V_ADJUST.p_ok=0;
				while(!PRECISE_ADJUST_OK());
        TRACK.STATE=Bizhang_1;
      }
	  }
		break;
				case Bizhang_1:
    {
      TRACK_CAR_CTOL(0,0,0,-2000,0,0);
      if(LASER.laser_value[3]<=200)
      {
        TRACK_CAR_CTOL(0,0,0,0,0,500);
				
        //CAR.V_ADJUST.p_ok=0;
				//while(!PRECISE_ADJUST_OK()); 
				
        TRACK.STATE=Bizhang_2;
      }
	  }
		break;
				case Bizhang_2:
    {
      if(LASER.laser_value[3]>=200)
      {
        TRACK_CAR_CTOL(0,0,0,0,0,500);
				CAR.CUR_COR.X_COR=6;
        CAR.CUR_COR.Y_COR=1;
        TRACK.STATE=BACK;
      }
			else
			{
				TRACK.STATE=Bizhang_2;
			}
	  }
		break;
		*/
			case BACK:
        {
            /*坐标法到达 4，6*/
            TRACK_COR_GO(4,6,5000,5000);
            if(TRACK.ARRIVE==ARRIVED)
            {
                TRACK_CAR_CTOL(0,2,0,0,0,1000);
                P_ADJUST();								//调整完毕
			          TRACK_CAR_CTOL(0,0,0,0,0,500);
                TRACK.STATE=FINISH;
            }
	    }
		break;
			case FINISH:
        {
          	while(!TRACK_GO_STEP(2000,3500,40));
            TRACK_CAR_CTOL(0,0,0,0,0,0);
			      //PlatformControl(2,0,53);//平台下降一半
            TRACK.STATE=FINISH_2;
	    }
		break;
		
		/*结束*/
		case FINISH_2:
		{
		}
		break;			
	}
}


/*红色方先黄球再红球再积木块  走中间 √*/
void TRACK_MODULE_RED_YR(void)
{
	switch(TRACK.STATE)
	{
    /*从出发区前往线上，坐标 5 0*/
		case START:
		{
      TRACK_CAR_CTOL(0,0,0,2000,0,0);
			if(DIGITAL16_GRAY_3.digital16_gray_state.STATE.L8==1&&DIGITAL16_GRAY_3.digital16_gray_state.STATE.L9==1)
			{		
				TRACK_CAR_CTOL(0,2,0,0,0,100);
				S_ADJUST();								//调整完毕
			  TRACK_CAR_CTOL(0,0,0,0,0,500);
				CAR.CUR_COR.X_COR=5;
        CAR.CUR_COR.Y_COR=0;
				TRACK.STATE=TRACK_GO_FETCH_BALL_YELLOW;
				PlatformControl(1, 0, 0);
			}	          
		}		
		break;		
    /*坐标法到达 4，2准备过储存区*/
    case TRACK_GO_FETCH_BALL_YELLOW:
    {
      TRACK_COR_GO(4,2,5000,5000);
      if(TRACK.ARRIVE==ARRIVED)
      {
        TRACK_CAR_CTOL(0,2,0,0,0,100);
        S_ADJUST();								//调整完毕
			  TRACK_CAR_CTOL(0,0,0,0,0,500);
        TRACK.STATE=TRACK_GO_FETCH_BALL_YELLOW_2;
      }
	  }
		break;	
	  /*硬延时过储存区*/
    case TRACK_GO_FETCH_BALL_YELLOW_2:
    {
	    TRACK_CAR_CTOL(0,2,0,0,0,0);	
      while(!TRACK_GO_STEP(0,3500,100));
      TRACK_CAR_CTOL(0,2,0,0,0,0);	
      S_ADJUST();								//调整完毕
			TRACK_CAR_CTOL(0,0,0,0,0,500);
      CAR.CUR_COR.X_COR=4;
      CAR.CUR_COR.Y_COR=4;
      TRACK.STATE=TRACK_GO_FETCH_BALL_YELLOW_3;
	  }
		break;	
	  /*坐标法到达 4，6*/
		case TRACK_GO_FETCH_BALL_YELLOW_3:
		{
      TRACK_COR_GO(4,6,5000,5000);
				
      if(TRACK.ARRIVE==ARRIVED)
      {
        TRACK_CAR_CTOL(0,2,0,0,0,200);
        S_ADJUST();								//调整完毕
			  TRACK_CAR_CTOL(0,0,0,0,0,500);
        TRACK.STATE=TRACK_FETCH_BALL_YELLOW;
      }
	  }
		break;
				/*慢速前进到抓取位置*/
		case TRACK_FETCH_BALL_YELLOW:
		{						
      TRACK_CAR_CTOL(0,0,-1000,0,0,0);
			if(LASER.laser_value[1]<=90)
			{	
			  TRACK_CAR_CTOL(0,0,0,0,0,1000);						
        TRACK.color=1;
			  TRACK.STATE=WAITING_FUCK_BALL_YELLOW;				
			}
		}
		break;
		case WAITING_FUCK_BALL_YELLOW:
		{
			waiting_fetch_ball();
			HAL_Delay(1000);
			finish_fetch(3);
			TRACK.STATE=FETCH_BALL_OVER_YELLOW;
			PlatformControl(2,0,50);//平台下降以便放球
		}
		break;
		//		/*抓取完成 更新当前位置与坐标*/
		case FETCH_BALL_OVER_YELLOW:
		{ 
      //TRACK.color=3;
			while(!TRACK_GO_STEP(1500,0,15));
			if(CAR.CUR_POS==ON_X)
      {
			  TRACK_CAR_CTOL(0,2,0,0,0,200);
				S_ADJUST();								//调整完毕
			  TRACK_CAR_CTOL(0,0,0,0,0,500);
				/*赋予坐标值*/
        CAR.CUR_COR.X_COR=3;
        CAR.CUR_COR.Y_COR=6;
        TRACK.STATE=FETCH_OVER_1;
			  TRACK_CAR_CTOL(0,0,0,0,0,500);
      }
		  if(CAR.CUR_POS==Yplus_CENTER)
      {
		    TRACK_CAR_CTOL(0,2,0,0,0,200);
			  S_ADJUST();								//调整完毕
			  TRACK_CAR_CTOL(0,0,0,0,0,500);
				/*赋予坐标值*/
        CAR.CUR_COR.X_COR=4;
        CAR.CUR_COR.Y_COR=6;
        TRACK.STATE=FETCH_OVER_1;
			  TRACK_CAR_CTOL(0,0,0,0,0,1000);
      }
		}
		break;
		case FETCH_OVER_1:
    {
      /*坐标法到达 4，4*/
      TRACK_COR_GO(4,4,5000,5000);
      if(TRACK.ARRIVE==ARRIVED)
      {
        //CAR.V.VX=0;
        //CAR.V.VY=0;
				TRACK_CAR_CTOL(0,0,0,0,0,500);
        S_ADJUST();								//调整完毕
			  TRACK_CAR_CTOL(0,0,0,0,0,500);
        TRACK.STATE=GO_STORE_YELLOW;
      }
	  }
		break;
		//储存黄色球
		case GO_STORE_YELLOW:
		{
		  CAR.V.VX=0;
      CAR.V.VY=-2000;
		  if(DIGITAL16_GRAY_3.digital16_gray_state.STATE.L5==1&&DIGITAL16_GRAY_3.digital16_gray_state.STATE.L4==1)
			{
        CAR.V.VX=0;
        CAR.V.VY=0;				
				TRACK_CAR_CTOL(0,0,0,0,0,1500);
				while(!TRACK_GO_STEP(-1500,0,30));
				CAR.V.VX=0;
        CAR.V.VY=0;	
				TRACK.STATE=STORE_YELLOW;
			}	
		}
		break;
		case STORE_YELLOW:
		{
		  Duoji_angle(0x07, 500, 900);
			TRACK_CAR_CTOL(0,0,0,0,0,2500);
			Duoji_angle(0x07, 120, 900);
			while(!TRACK_GO_STEP(1500,0,30));
      CAR.V.VX=0;
      CAR.V.VY=0;	
		  TRACK.STATE=STORE_OVER_BACK_ONLINE;
			PlatformControl(1,0,50);//平台上升回原位，调试用为46，比赛务必改为50
		}
		break;
		case STORE_OVER_BACK_ONLINE:
		{
      TRACK_CAR_CTOL(0,2,0,0,0,0);	
      while(!TRACK_GO_STEP(0,3500,35));
      TRACK_CAR_CTOL(0,2,0,0,0,200);	
      S_ADJUST();								//调整完毕
			TRACK_CAR_CTOL(0,0,0,0,0,500);
      CAR.CUR_COR.X_COR=4;
      CAR.CUR_COR.Y_COR=4;
      TRACK.STATE=TRACK_GO_FETCH_BALL_RED;
		}
		break;
		/*坐标法到达 4，6*/
		case TRACK_GO_FETCH_BALL_RED:
		{
      TRACK_COR_GO(4,6,5000,5000);
				
      if(TRACK.ARRIVE==ARRIVED)
      {
        TRACK_CAR_CTOL(0,2,0,0,0,200);
        S_ADJUST();								//调整完毕
			  TRACK_CAR_CTOL(0,0,0,0,0,500);
        TRACK.STATE=TRACK_FETCH_BALL_RED;
      }
	  }
		break;
	  /*慢速前进到抓取位置*/
		case TRACK_FETCH_BALL_RED:
		{				
		  TRACK_CAR_CTOL(0,0,-1000,0,0,0);
			/*三号灰度 L1 L2灰度落在白线，并且有一激光小于12cm*/
			if(LASER.laser_value[1]<=90)
			{	
			  TRACK_CAR_CTOL(0,0,0,0,0,500);
				TRACK.color=1;
				TRACK.STATE=WAITING_FUCK_BALL_RED;								
			}
		}
		break;
		case WAITING_FUCK_BALL_RED:
		{
		  waiting_fetch_ball();
			HAL_Delay(1000);
			finish_fetch(1);//圆盘机红球
			TRACK.STATE=FETCH_BALL_OVER_RED;
			PlatformControl(2,0,50);//平台下降以便放球
		}
		break;
		//		/*抓取完成 更新当前位置与坐标*/
		case FETCH_BALL_OVER_RED:
		{ 
		  //TRACK.color=3;
			while(!TRACK_GO_STEP(1500,0,15));
			if(CAR.CUR_POS==ON_X)
      {
			  TRACK_CAR_CTOL(0,2,0,0,0,200);
				S_ADJUST();								//调整完毕
			  TRACK_CAR_CTOL(0,0,0,0,0,500);
				/*赋予坐标值*/
        CAR.CUR_COR.X_COR=3;
        CAR.CUR_COR.Y_COR=6;
        TRACK.STATE=FETCH_OVER_2;
			  TRACK_CAR_CTOL(0,0,0,0,0,500);
      }
		  if(CAR.CUR_POS==Yplus_CENTER)
      {
			  TRACK_CAR_CTOL(0,2,0,0,0,200);
				S_ADJUST();								//调整完毕
			  TRACK_CAR_CTOL(0,0,0,0,0,500);
				/*赋予坐标值*/
        CAR.CUR_COR.X_COR=4;
        CAR.CUR_COR.Y_COR=6;
        TRACK.STATE=FETCH_OVER_2;
			  TRACK_CAR_CTOL(0,0,0,0,0,1000);
      }
		}
		break;
	  case FETCH_OVER_2:
    {
      /*坐标法到达 4，4*/
      TRACK_COR_GO(4,4,5000,5000);
      if(TRACK.ARRIVE==ARRIVED)
      {
        //CAR.V.VX=0;
        //CAR.V.VY=0;
			  TRACK_CAR_CTOL(0,0,0,0,0,500);
        S_ADJUST();								//调整完毕
			  TRACK_CAR_CTOL(0,0,0,0,0,500);
        TRACK.STATE=GO_STORE_RED;
      }
	  }
		break;
		//储存本色球
		case GO_STORE_RED:
	  {
		  CAR.V.VX=0;
      CAR.V.VY=-2000;
		  if(DIGITAL16_GRAY_3.digital16_gray_state.STATE.L5==1&&DIGITAL16_GRAY_3.digital16_gray_state.STATE.L14==1&&DIGITAL16_GRAY_3.digital16_gray_state.STATE.L6==1)
			{
        CAR.V.VX=0;
        CAR.V.VY=0;				
				TRACK_CAR_CTOL(0,0,0,0,0,1500);
				while(!TRACK_GO_STEP(-1500,0,30));
				CAR.V.VX=0;
        CAR.V.VY=0;	
				TRACK.STATE=STORE_RED;
			}	
		}
		break;
		case STORE_RED:
		{
		  Duoji_angle(0x07, 500, 900);
		  TRACK_CAR_CTOL(0,0,0,0,0,2500);
			Duoji_angle(0x07, 220, 900);
			while(!TRACK_GO_STEP(1500,0,30));
      CAR.V.VX=0;
      CAR.V.VY=0;	
			TRACK.STATE=STORE_OVER_BACK_ONLINE_2;
			PlatformControl(1,0,50);//平台上升回原位
		}
		break;
		case STORE_OVER_BACK_ONLINE_2:
		{
      TRACK_CAR_CTOL(0,2,0,0,0,0);	
      while(!TRACK_GO_STEP(0,3500,40));
      TRACK_CAR_CTOL(0,2,0,0,0,0);	
      S_ADJUST();								//调整完毕
			TRACK_CAR_CTOL(0,0,0,0,0,500);
      CAR.CUR_COR.X_COR=4;
      CAR.CUR_COR.Y_COR=4;
      TRACK.STATE=TRACK_GO_FETCH_BRICK;
		}
		break;
    case TRACK_GO_FETCH_BRICK:
    {
      /*坐标法到达 6，4*/
      TRACK_COR_GO(6,4,5000,5000);
      if(TRACK.ARRIVE==ARRIVED)
      {
        TRACK_CAR_CTOL(0,2,0,0,0,200);
        S_ADJUST();								//调整完毕
			  TRACK_CAR_CTOL(0,0,0,0,0,500);
        TRACK.STATE=TRACK_GO_FETCH_BRICK_2;
      }
	  }
		break;	
		//转向180
		case TRACK_GO_FETCH_BRICK_2:
		{
      while(!TRACK_TURN_ANGLE(50,55));
			TRACK_CAR_CTOL(0,2,0,0,0,200);
			S_ADJUST();								//调整完毕
			TRACK_CAR_CTOL(0,0,0,0,0,500);
			TRACK.STATE=TRACK_GO_FETCH_BRICK_3;	
		}
		break;			
		/*慢速向右到抓取位置*/
		case TRACK_GO_FETCH_BRICK_3:
		{
		  while(!TRACK_GO_STEP(0,2000,35));
      TRACK_CAR_CTOL(0,2,0,0,0,1000);
      TRACK.color=1;
		  S_ADJUST();								//调整完毕
			TRACK_CAR_CTOL(0,0,0,0,0,500);
			TRACK.STATE=TRACK_FETCH_BRICK;			
		}
		break;
	  /* 往前*/
		case TRACK_FETCH_BRICK:
		{
			TRACK_CAR_CTOL(0,0,-1000,0,0,0);
			if(LASER.laser_value[1]<=95)
			{
				while(!TRACK_GO_STEP(0,-2000,10));//往左来一点
        TRACK_CAR_CTOL(0,0,0,0,0,500);
        TRACK.color=1;
				TRACK.STATE=WAITING_FUCK_BRIKE;
			}	
		}
		break;
		case WAITING_FUCK_BRIKE:
		{
		  waiting_fetch_cube();
			//HAL_Delay(1000);
			//TRACK_CAR_CTOL(0,0,0,2000,0,10);
			finish_fetch(4);
			TRACK.STATE=FETCH_BRICK_OVER_BACK_ONLINE;
		}
		break;
		//		/*抓取完成 返回到 线上 更新坐标*/
		case FETCH_BRICK_OVER_BACK_ONLINE:
		{ 
      //TRACK.color=3;
			TRACK_CAR_CTOL(0,0,2000,0,0,0);
			if(DIGITAL16_GRAY_2.digital16_gray_state.STATE.L8==1&&DIGITAL16_GRAY_2.digital16_gray_state.STATE.L9==1)
			{
				//CAR.CUR_POS=ON_Y;
				while(!TRACK_GO_STEP(0,-2000,10));//往左来一点
        TRACK_CAR_CTOL(0,2,0,0,0,200);
				S_ADJUST();								//调整完毕
			  TRACK_CAR_CTOL(0,0,0,0,0,500);
				/*赋予坐标值*/
        CAR.CUR_COR.X_COR=6;
        CAR.CUR_COR.Y_COR=3;
        TRACK.STATE=TRACK_GO_FETCH_BRICK_6;
				PlatformControl(2,0,60);//平台下降
				TRACK_CAR_CTOL(0,0,0,0,0,1000);
			}
		}
		break;
//		case TRACK_GO_FETCH_BRICK_4:
//		{
//      TRACK_CAR_CTOL(0,0,0,-4000,0,0);
//			if(DIGITAL16_GRAY_1.digital16_gray_state.STATE.L8==1)
//			{		
//			TRACK_CAR_CTOL(0,2,0,0,0,100);
//			S_ADJUST();								//调整完毕
//			TRACK_CAR_CTOL(0,0,0,0,0,500);
//			TRACK.STATE=TRACK_GO_FETCH_BRICK_5;	
//		  }
//		}
//		break;
//			/*慢速向右到抓取位置*/
//		case TRACK_GO_FETCH_BRICK_5:
//		{
//		  while(!TRACK_GO_STEP(0,2000,35));
//      TRACK_CAR_CTOL(0,2,0,0,0,100);
//      TRACK.color=1;
//		  S_ADJUST();								//调整完毕
//			TRACK_CAR_CTOL(0,0,0,0,0,500);
//			TRACK.STATE=TRACK_FETCH_BRICK_2;			
//		}
//		break;
//	  /* 往前*/
//		case TRACK_FETCH_BRICK_2:
//		{
//			TRACK_CAR_CTOL(0,0,-1000,0,0,0);
//			if(LASER.laser_value[1]<=95)
//			{
//				while(!TRACK_GO_STEP(0,-2000,10));//往左来一点
//        TRACK_CAR_CTOL(0,0,0,0,0,500);
//        TRACK.color=1;
//				TRACK.STATE=WAITING_FUCK_BRIKE_2;
//			}	
//		}
//		break;
//		case WAITING_FUCK_BRIKE_2:
//		{
//		  waiting_fetch_cube();
//			//HAL_Delay(1000);
//			//TRACK_CAR_CTOL(0,0,0,2000,0,10);
//			finish_fetch(7);
//			TRACK.STATE=FETCH_BRICK_OVER_BACK_ONLINE_2;
//		}
//		break;
//		//		/*抓取完成 返回到 线上 更新坐标*/
//		case FETCH_BRICK_OVER_BACK_ONLINE_2:
//		{ 
//      //TRACK.color=3;
//			TRACK_CAR_CTOL(0,0,4000,0,0,0);
//			if(DIGITAL16_GRAY_2.digital16_gray_state.STATE.L8==1&&DIGITAL16_GRAY_2.digital16_gray_state.STATE.L9==1)
//			{
//				//CAR.CUR_POS=ON_Y;
//        TRACK_CAR_CTOL(0,2,0,0,0,200);
//				S_ADJUST();								//调整完毕
//			  TRACK_CAR_CTOL(0,0,0,0,0,500);
//				/*赋予坐标值*/
//        CAR.CUR_COR.X_COR=6;
//        CAR.CUR_COR.Y_COR=3;
//        TRACK.STATE=TRACK_GO_FETCH_BRICK_6;
//				//PlatformControl(2,0,50);//平台下降
//				TRACK_CAR_CTOL(0,0,0,0,0,500);
//			}
//		}
//		break;
		//转向180
		case TRACK_GO_FETCH_BRICK_6:
		{
      while(!TRACK_TURN_ANGLE(50,55));
      TRACK_CAR_CTOL(0,2,0,0,0,200);			
			S_ADJUST();								//调整完毕
			TRACK_CAR_CTOL(0,0,0,0,0,500);
			TRACK.STATE=FETCH_OVER_3;	
		}
		break;
		case FETCH_OVER_3:
    {
      /*坐标法到达 4，4*/
      TRACK_COR_GO(4,4,5000,5000);
      if(TRACK.ARRIVE==ARRIVED)
      {
        CAR.V.VX=0;
        CAR.V.VY=0;
			  TRACK_CAR_CTOL(0,2,0,0,0,200);
        S_ADJUST();								//调整完毕
			  TRACK_CAR_CTOL(0,0,0,0,0,500);
        TRACK.STATE=GO_STORE_BRIKE;
      }
	  }
		break;	
		//储存己方积木块与球
		case GO_STORE_BRIKE:
	  {
		  CAR.V.VX=0;
      CAR.V.VY=-2000;
			if(DIGITAL16_GRAY_3.digital16_gray_state.STATE.L5==1&&DIGITAL16_GRAY_3.digital16_gray_state.STATE.L14==1&&DIGITAL16_GRAY_3.digital16_gray_state.STATE.L6==1)
			{
				CAR.V.VX=0;
        CAR.V.VY=0;				
				TRACK_CAR_CTOL(0,0,0,0,0,500);
				while(!TRACK_GO_STEP(-1500,0,30));
				CAR.V.VX=0;
        CAR.V.VY=0;	
				TRACK_CAR_CTOL(0,0,0,0,0,500);
				TRACK.STATE=STORE_BRIKE;
			}	
		}
		break;
		case STORE_BRIKE:
		{
		  Duoji_angle(0x07, 680, 900);
			TRACK_CAR_CTOL(0,0,0,0,0,2500);
			Duoji_angle(0x07, 120, 900);
			while(!TRACK_GO_STEP(1500,0,30));
      CAR.V.VX=0;
      CAR.V.VY=0;	
			TRACK_CAR_CTOL(0,0,0,0,0,500);
			PlatformControl(1,0,60);//平台上升回原位
			TRACK.STATE=STORE_OVER_BACK_ONLINE_3;
		}
		break;
		case STORE_OVER_BACK_ONLINE_3:
		{
      TRACK_CAR_CTOL(0,2,0,0,0,0);	
      while(!TRACK_GO_STEP(0,3500,40));
      TRACK_CAR_CTOL(0,2,0,0,0,200);	
      S_ADJUST();								//调整完毕
			TRACK_CAR_CTOL(0,0,0,0,0,500);
      CAR.CUR_COR.X_COR=4;
      CAR.CUR_COR.Y_COR=4;
      TRACK.STATE=TRACK_GO_FETCH_BRICK_YELLOWBALL;
		}
		break;
		//抓黄球
		case TRACK_GO_FETCH_BRICK_YELLOWBALL:
        {
            /*坐标法到达 6，4*/
            TRACK_COR_GO(6,4,5000,5000);
            if(TRACK.ARRIVE==ARRIVED)
            {
                TRACK_CAR_CTOL(0,2,0,0,0,200);
                S_ADJUST();								//调整完毕
			          TRACK_CAR_CTOL(0,0,0,0,0,500);
                TRACK.STATE=TRACK_GO_FETCH_BRICK_YELLOWBALL_2;
            }
	    }
		break;	
		//转向180
				case TRACK_GO_FETCH_BRICK_YELLOWBALL_2:
		{
         while(!TRACK_TURN_ANGLE(50,55));
			   TRACK_CAR_CTOL(0,2,0,0,0,200);
			   S_ADJUST();								//调整完毕
			   TRACK_CAR_CTOL(0,0,0,0,0,500);
				 TRACK.STATE=TRACK_GO_FETCH_BRICK_YELLOWBALL_3;	
		}
			break;			
			/*慢速向右到抓取位置*/
		case TRACK_GO_FETCH_BRICK_YELLOWBALL_3:
		{
				  while(!TRACK_GO_STEP(0,2000,35));
          TRACK_CAR_CTOL(0,2,0,0,0,200);
          TRACK.color=1;
				  S_ADJUST();								//调整完毕
			    TRACK_CAR_CTOL(0,0,0,0,0,500);
				  TRACK.STATE=TRACK_FETCH_BRICK_3;			
		}
			break;
				/* 往前*/
		case TRACK_FETCH_BRICK_3:
		{
			TRACK_CAR_CTOL(0,0,-1000,0,0,0);
			if(LASER.laser_value[1]<=95)
			{
				  while(!TRACK_GO_STEP(0,-2000,10));//往左来一点
          TRACK_CAR_CTOL(0,0,0,0,0,500);
          TRACK.color=1;
				  TRACK.STATE=WAITING_FUCK_BRIKE_3;
			}	
		}
		break;
			case WAITING_FUCK_BRIKE_3:
				{
					waiting_fetch_cube();
					//HAL_Delay(1000);
					//TRACK_CAR_CTOL(0,0,0,2000,0,10);
					finish_fetch(6);
					TRACK.STATE=FETCH_BRICK_OVER_BACK_ONLINE_3;
		    }
		break;
		//		/*抓取完成 返回到 线上 更新坐标*/
		case FETCH_BRICK_OVER_BACK_ONLINE_3:
		{ 
      //TRACK.color=3;
			TRACK_CAR_CTOL(0,0,2000,0,0,0);
			if(DIGITAL16_GRAY_2.digital16_gray_state.STATE.L8==1&&DIGITAL16_GRAY_2.digital16_gray_state.STATE.L9==1)
			{
				//CAR.CUR_POS=ON_Y;
				while(!TRACK_GO_STEP(0,-2000,10));//往左来一点
        TRACK_CAR_CTOL(0,2,0,0,0,0);
				S_ADJUST();								//调整完毕
			  TRACK_CAR_CTOL(0,0,0,0,0,500);
				/*赋予坐标值*/
        CAR.CUR_COR.X_COR=6;
        CAR.CUR_COR.Y_COR=3;
        TRACK.STATE=TRACK_GO_FETCH_BRICK_YELLOWBALL_4;
				PlatformControl(2,0,50);//平台下降
				TRACK_CAR_CTOL(0,0,0,0,0,500);
			}
		}
		break;
				//转向180
				case TRACK_GO_FETCH_BRICK_YELLOWBALL_4:
		{
         while(!TRACK_TURN_ANGLE(50,55));
         TRACK_CAR_CTOL(0,2,0,0,0,200);			
			   S_ADJUST();								//调整完毕
			   TRACK_CAR_CTOL(0,0,0,0,0,500);
				 TRACK.STATE=FETCH_OVER_4;	
		}
			break;
			case FETCH_OVER_4:
        {
            /*坐标法到达 4，4*/
            TRACK_COR_GO(4,4,5000,5000);
            if(TRACK.ARRIVE==ARRIVED)
            {
                CAR.V.VX=0;
                CAR.V.VY=0;
							  TRACK_CAR_CTOL(0,0,0,0,0,500);
                S_ADJUST();								//调整完毕
			          TRACK_CAR_CTOL(0,0,0,0,0,500);
                TRACK.STATE=GO_STORE_BRIKE_YELLOWBALL;
            }
	    }
		break;	
			//储存黄球
		case GO_STORE_BRIKE_YELLOWBALL:
			{
		  CAR.V.VX=0;
      CAR.V.VY=-2000;
		  if(DIGITAL16_GRAY_3.digital16_gray_state.STATE.L5==1&&DIGITAL16_GRAY_3.digital16_gray_state.STATE.L4==1)
			{
        CAR.V.VX=0;
        CAR.V.VY=0;				
				TRACK_CAR_CTOL(0,0,0,0,0,1500);
				while(!TRACK_GO_STEP(-1500,0,30));
				CAR.V.VX=0;
        CAR.V.VY=0;	
				TRACK.STATE=STORE_BRIKE_YELLOWBALL;
			}	
		}
			break;
			case STORE_BRIKE_YELLOWBALL:
			{
				Duoji_angle(0x07, 500, 900);
				TRACK_CAR_CTOL(0,0,0,0,0,2500);
				Duoji_angle(0x07, 120, 900);
				while(!TRACK_GO_STEP(1500,0,30));
        CAR.V.VX=0;
        CAR.V.VY=0;	
				TRACK_CAR_CTOL(0,0,0,0,0,500);
				TRACK.STATE=STORE_OVER_BACK_ONLINE_4;
			}
			break;
			case STORE_OVER_BACK_ONLINE_4:
			{
          TRACK_CAR_CTOL(0,2,0,0,0,0);	
          while(!TRACK_GO_STEP(0,-3500,63));
          TRACK_CAR_CTOL(0,2,0,0,0,200);	
          S_ADJUST();								//调整完毕
			    TRACK_CAR_CTOL(0,0,0,0,0,500);
          CAR.CUR_COR.X_COR=4;
          CAR.CUR_COR.Y_COR=2;
          TRACK.STATE=Bizhang;
			}
			break;
				case Bizhang:
    {
      //坐标法到达 x，y
      TRACK_COR_GO(6,4,5000,5000);
      if(TRACK.ARRIVE==ARRIVED)
      {
        TRACK_CAR_CTOL(0,2,0,0,0,500);
        S_ADJUST();								//调整完毕
			  TRACK_CAR_CTOL(0,0,0,0,0,500);
        TRACK.STATE=Bizhang_1;
      }
	  }
		break;
				case Bizhang_1:
    {
      TRACK_CAR_CTOL(0,0,0,1500,0,0);
      if(LASER.laser_value[0]<=200)
      {
			  TRACK_CAR_CTOL(0,0,0,0,0,2000);
        TRACK.STATE=Bizhang_2;
      }
	  }
		break;
				case Bizhang_2:
    {
			TRACK_CAR_CTOL(0,0,0,-1500,0,0);
      if(DIGITAL16_GRAY_3.digital16_gray_state.STATE.L13==1)
      {
        TRACK_CAR_CTOL(0,2,0,0,0,500);
        S_ADJUST();								//调整完毕
			  TRACK_CAR_CTOL(0,0,0,0,0,500);
				CAR.CUR_COR.X_COR=6;
        CAR.CUR_COR.Y_COR=4;
        TRACK.STATE=BACK;		
      }
	  }
		break;
		case BACK:
    {
      /*坐标法到达 4，0*/
      TRACK_COR_GO(4,0,5000,5000);
      if(TRACK.ARRIVE==ARRIVED)
      {
        TRACK_CAR_CTOL(0,2,0,0,0,500);
        S_ADJUST();								//调整完毕
			  TRACK_CAR_CTOL(0,0,0,0,0,500);
        TRACK.STATE=FINISH;
      }
	  }
		break;
		case FINISH:
    {
      while(!TRACK_GO_STEP(3000,-1500,68));
      TRACK_CAR_CTOL(0,0,0,0,0,0);
			//CAR.CUR_COR.X_COR=0;
      //CAR.CUR_COR.Y_COR=0;
      TRACK.STATE=FINISH_2;
			//PlatformControl(2,0,53);//平台下降一半
	  }
		break;
		/*结束*/
		case FINISH_2:
		{
		}
		break;
	}
}


/*蓝色方先黄球再蓝球再积木块  走中间 √*/
void TRACK_MODULE_BLUE_YB(void)
{
	switch(TRACK.STATE)
	{
    /*从出发区前往线上，坐标 5 6*/
		case START:
		{
      TRACK_CAR_CTOL(0,0,0,-2000,0,0);
			if(DIGITAL16_GRAY_3.digital16_gray_state.STATE.L8==1&&DIGITAL16_GRAY_3.digital16_gray_state.STATE.L9==1)
			{		
				TRACK_CAR_CTOL(0,2,0,0,0,100);
				S_ADJUST();								//调整完毕
			  TRACK_CAR_CTOL(0,0,0,0,0,500);
				CAR.CUR_COR.X_COR=5;
        CAR.CUR_COR.Y_COR=6;
				TRACK.STATE=TRACK_GO_FETCH_BALL_YELLOW;
				PlatformControl(1, 0, 0);
			}	          
		}		
		break;	
    /*坐标法到达 4，4准备过储存区*/
    case TRACK_GO_FETCH_BALL_YELLOW:
    {
      TRACK_COR_GO(4,4,5000,5000);
      if(TRACK.ARRIVE==ARRIVED)
      {
        TRACK_CAR_CTOL(0,2,0,0,0,100);
        P_ADJUST();								//调整完毕
			  TRACK_CAR_CTOL(0,0,0,0,0,500);
        TRACK.STATE=TRACK_GO_FETCH_BALL_YELLOW_2;
      }
	  }
		break;	
	  /*硬延时过储存区*/
    case TRACK_GO_FETCH_BALL_YELLOW_2:
    {
	    TRACK_CAR_CTOL(0,2,0,0,0,0);	
      while(!TRACK_GO_STEP(0,-3500,100));
      TRACK_CAR_CTOL(0,2,0,0,0,200);	
      S_ADJUST();								//调整完毕
			TRACK_CAR_CTOL(0,0,0,0,0,500);
      CAR.CUR_COR.X_COR=4;
      CAR.CUR_COR.Y_COR=2;
      TRACK.STATE=TRACK_GO_FETCH_BALL_YELLOW_3;
	  }
		break;	
	  /*坐标法到达 4，0*/
		case TRACK_GO_FETCH_BALL_YELLOW_3:
		{
      TRACK_COR_GO(4,0,5000,5000);
				
      if(TRACK.ARRIVE==ARRIVED)
      {
        TRACK_CAR_CTOL(0,2,0,0,0,200);
        S_ADJUST();								//调整完毕
			  TRACK_CAR_CTOL(0,0,0,0,0,500);
        TRACK.STATE=TRACK_FETCH_BALL_YELLOW;
      }
	  }
		break;
				/*慢速前进到抓取位置*/
		case TRACK_FETCH_BALL_YELLOW:
		{						
      TRACK_CAR_CTOL(0,0,-1000,0,0,0);
			if(LASER.laser_value[1]<=90)
			{	
			  TRACK_CAR_CTOL(0,0,0,0,0,500);						
        TRACK.color=1;
			  TRACK.STATE=WAITING_FUCK_BALL_YELLOW;				
			}
		}
		break;
		case WAITING_FUCK_BALL_YELLOW:
		{
			waiting_fetch_ball();
			HAL_Delay(1000);
			finish_fetch(3);
			TRACK.STATE=FETCH_BALL_OVER_YELLOW;
			PlatformControl(2,0,50);//平台下降以便放球
		}
		break;
		//		/*抓取完成 更新当前位置与坐标*/
		case FETCH_BALL_OVER_YELLOW:
		{ 
      //TRACK.color=3;
			while(!TRACK_GO_STEP(1500,0,15));
			if(CAR.CUR_POS==ON_X)
      {
			  TRACK_CAR_CTOL(0,2,0,0,0,200);
				S_ADJUST();								//调整完毕
			  TRACK_CAR_CTOL(0,0,0,0,0,500);
				/*赋予坐标值*/
        CAR.CUR_COR.X_COR=3;
        CAR.CUR_COR.Y_COR=0;
        TRACK.STATE=FETCH_OVER_1;
			  TRACK_CAR_CTOL(0,0,0,0,0,500);
      }
		  if(CAR.CUR_POS==Yminus_CENTER)
      {
		    TRACK_CAR_CTOL(0,2,0,0,0,200);
			  S_ADJUST();								//调整完毕
			  TRACK_CAR_CTOL(0,0,0,0,0,500);
				/*赋予坐标值*/
        CAR.CUR_COR.X_COR=4;
        CAR.CUR_COR.Y_COR=0;
        TRACK.STATE=FETCH_OVER_1;
			  TRACK_CAR_CTOL(0,0,0,0,0,1000);
      }
		}
		break;
		case FETCH_OVER_1:
    {
      /*坐标法到达 4，2*/
      TRACK_COR_GO(4,2,5000,5000);
      if(TRACK.ARRIVE==ARRIVED)
      {
        //CAR.V.VX=0;
        //CAR.V.VY=0;
				TRACK_CAR_CTOL(0,0,0,0,0,200);
        S_ADJUST();								//调整完毕
			  TRACK_CAR_CTOL(0,0,0,0,0,500);
        TRACK.STATE=GO_STORE_YELLOW;
      }
	  }
		break;
		//储存黄色球
		case GO_STORE_YELLOW:
			{
				CAR.V.VX=0;
        CAR.V.VY=2000;
				if(DIGITAL16_GRAY_3.digital16_gray_state.STATE.L5==1&&DIGITAL16_GRAY_3.digital16_gray_state.STATE.L12==1&&DIGITAL16_GRAY_3.digital16_gray_state.STATE.L4==1)
			{
        CAR.V.VX=0;
        CAR.V.VY=0;				
				TRACK_CAR_CTOL(0,0,0,0,0,1500);
				TRACK.STATE=GO_STORE_YELLOW_2;
			}	
			}
			break;
			case GO_STORE_YELLOW_2:
			{
				CAR.V.VX=0;
        CAR.V.VY=2000;
				if(DIGITAL16_GRAY_3.digital16_gray_state.STATE.L5==1&&DIGITAL16_GRAY_3.digital16_gray_state.STATE.L12!=1&&DIGITAL16_GRAY_3.digital16_gray_state.STATE.L11!=1&&DIGITAL16_GRAY_3.digital16_gray_state.STATE.L4==1)
			{
        CAR.V.VX=0;
        CAR.V.VY=0;	
				while(!TRACK_GO_STEP(-1500,0,30));
				CAR.V.VX=0;
        CAR.V.VY=0;	
				TRACK.STATE=STORE_YELLOW;
			}	
			}
			break;
		case STORE_YELLOW:
		{
		  Duoji_angle(0x07, 500, 900);
			TRACK_CAR_CTOL(0,0,0,0,0,2500);
			Duoji_angle(0x07, 120, 900);
			while(!TRACK_GO_STEP(1500,0,30));
      CAR.V.VX=0;
      CAR.V.VY=0;	
		  TRACK.STATE=STORE_OVER_BACK_ONLINE;
			PlatformControl(1,0,50);//平台上升回原位，调试用为46，比赛务必改为50
		}
		break;
		case STORE_OVER_BACK_ONLINE:
		{
      TRACK_CAR_CTOL(0,2,0,0,0,0);	
      while(!TRACK_GO_STEP(0,-3500,65));
      TRACK_CAR_CTOL(0,2,0,0,0,0);	
      S_ADJUST();								//调整完毕
			TRACK_CAR_CTOL(0,0,0,0,0,500);
      CAR.CUR_COR.X_COR=4;
      CAR.CUR_COR.Y_COR=2;
      TRACK.STATE=TRACK_GO_FETCH_BALL_BLUE;
		}
		break;
		/*坐标法到达 4，0*/
		case TRACK_GO_FETCH_BALL_BLUE:
		{
      TRACK_COR_GO(4,0,5000,5000);
				
      if(TRACK.ARRIVE==ARRIVED)
      {
        TRACK_CAR_CTOL(0,2,0,0,0,200);
        S_ADJUST();								//调整完毕
			  TRACK_CAR_CTOL(0,0,0,0,0,500);
        TRACK.STATE=TRACK_FETCH_BALL_BLUE;
      }
	  }
		break;
	  /*慢速前进到抓取位置*/
		case TRACK_FETCH_BALL_BLUE:
		{				
		  TRACK_CAR_CTOL(0,0,-1000,0,0,0);
			/*三号灰度 L1 L2灰度落在白线，并且有一激光小于12cm*/
			if(LASER.laser_value[1]<=90)
			{	
			  TRACK_CAR_CTOL(0,0,0,0,0,500);
				TRACK.color=1;
				TRACK.STATE=WAITING_FUCK_BALL_BLUE;								
			}
		}
		break;
		case WAITING_FUCK_BALL_BLUE:
		{
		  waiting_fetch_ball();
			HAL_Delay(1000);
			finish_fetch(2);
			TRACK.STATE=FETCH_BALL_OVER_BLUE;
			PlatformControl(2,0,50);//平台下降以便放球
		}
		break;
		//		/*抓取完成 更新当前位置与坐标*/
		case FETCH_BALL_OVER_BLUE:
		{ 
		  //TRACK.color=3;
			while(!TRACK_GO_STEP(1500,0,15));
			if(CAR.CUR_POS==ON_X)
      {
			  TRACK_CAR_CTOL(0,2,0,0,0,200);
				S_ADJUST();								//调整完毕
			  TRACK_CAR_CTOL(0,0,0,0,0,500);
				/*赋予坐标值*/
        CAR.CUR_COR.X_COR=3;
        CAR.CUR_COR.Y_COR=0;
        TRACK.STATE=FETCH_OVER_2;
			  TRACK_CAR_CTOL(0,0,0,0,0,500);
      }
		  if(CAR.CUR_POS==Yminus_CENTER)
      {
			  TRACK_CAR_CTOL(0,2,0,0,0,200);
				S_ADJUST();								//调整完毕
			  TRACK_CAR_CTOL(0,0,0,0,0,500);
				/*赋予坐标值*/
        CAR.CUR_COR.X_COR=4;
        CAR.CUR_COR.Y_COR=0;
        TRACK.STATE=FETCH_OVER_2;
			  TRACK_CAR_CTOL(0,0,0,0,0,500);
      }
		}
		break;
	  case FETCH_OVER_2:
    {
      /*坐标法到达 4，2*/
      TRACK_COR_GO(4,2,5000,5000);
      if(TRACK.ARRIVE==ARRIVED)
      {
        //CAR.V.VX=0;
        //CAR.V.VY=0;
			  TRACK_CAR_CTOL(0,0,0,0,0,500);
        P_ADJUST();								//调整完毕
			  TRACK_CAR_CTOL(0,0,0,0,0,500);
        TRACK.STATE=GO_STORE_BLUE;
      }
	  }
		break;
		//储存本色球
		case GO_STORE_BLUE:
	  {
		  CAR.V.VX=0;
      CAR.V.VY=2000;
		  if(DIGITAL16_GRAY_3.digital16_gray_state.STATE.L5==1&&DIGITAL16_GRAY_3.digital16_gray_state.STATE.L12==1&&DIGITAL16_GRAY_3.digital16_gray_state.STATE.L4==1)
			{
        CAR.V.VX=0;
        CAR.V.VY=0;			
				while(!TRACK_GO_STEP(-1500,0,30));
				CAR.V.VX=0;
        CAR.V.VY=0;	
				TRACK.STATE=STORE_BLUE;
			}	
		}
		break;
		case STORE_BLUE:
		{
		  Duoji_angle(0x07, 500, 900);
		  TRACK_CAR_CTOL(0,0,0,0,0,2500);
			Duoji_angle(0x07, 220, 900);
			while(!TRACK_GO_STEP(1500,0,30));
      CAR.V.VX=0;
      CAR.V.VY=0;	
			TRACK.STATE=STORE_OVER_BACK_ONLINE_2;
			PlatformControl(1,0,50);//平台上升回原位
		}
		break;
		case STORE_OVER_BACK_ONLINE_2:
		{
      TRACK_CAR_CTOL(0,2,0,0,0,0);	
      while(!TRACK_GO_STEP(0,3500,40));
      TRACK_CAR_CTOL(0,2,0,0,0,0);	
      S_ADJUST();								//调整完毕
			TRACK_CAR_CTOL(0,0,0,0,0,500);
      CAR.CUR_COR.X_COR=4;
      CAR.CUR_COR.Y_COR=4;
      TRACK.STATE=TRACK_GO_FETCH_BRICK;
		}
		break;
    case TRACK_GO_FETCH_BRICK:
    {
      /*坐标法到达 6，4*/
      TRACK_COR_GO(6,4,5000,5000);
      if(TRACK.ARRIVE==ARRIVED)
      {
        TRACK_CAR_CTOL(0,2,0,0,0,200);
        S_ADJUST();								//调整完毕
			  TRACK_CAR_CTOL(0,0,0,0,0,500);
        TRACK.STATE=TRACK_GO_FETCH_BRICK_2;
      }
	  }
		break;	
		//转向180
		case TRACK_GO_FETCH_BRICK_2:
		{
      while(!TRACK_TURN_ANGLE(50,55));
			TRACK_CAR_CTOL(0,2,0,0,0,200);
			S_ADJUST();								//调整完毕
			TRACK_CAR_CTOL(0,0,0,0,0,500);
			TRACK.STATE=TRACK_GO_FETCH_BRICK_3;	
		}
		break;			
		/*慢速向右到抓取位置*/
		case TRACK_GO_FETCH_BRICK_3:
		{
		  while(!TRACK_GO_STEP(0,2000,35));
      TRACK_CAR_CTOL(0,2,0,0,0,200);
      TRACK.color=1;
		  S_ADJUST();								//调整完毕
			TRACK_CAR_CTOL(0,0,0,0,0,500);
			TRACK.STATE=TRACK_FETCH_BRICK;			
		}
		break;
	  /* 往前*/
		case TRACK_FETCH_BRICK:
		{
			TRACK_CAR_CTOL(0,0,-1000,0,0,0);
			if(LASER.laser_value[1]<=95)
			{
				while(!TRACK_GO_STEP(0,-2000,10));//往左来一点
        TRACK_CAR_CTOL(0,0,0,0,0,100);
        TRACK.color=1;
				TRACK.STATE=WAITING_FUCK_BRIKE;
			}	
		}
		break;
		case WAITING_FUCK_BRIKE:
		{
		  waiting_fetch_cube();
			//HAL_Delay(1000);
			//TRACK_CAR_CTOL(0,0,0,2000,0,10);
			finish_fetch(5);
			TRACK.STATE=FETCH_BRICK_OVER_BACK_ONLINE;
		}
		break;
		//		/*抓取完成 返回到 线上 更新坐标*/
		case FETCH_BRICK_OVER_BACK_ONLINE:
		{ 
      //TRACK.color=3;
			TRACK_CAR_CTOL(0,0,2000,0,0,0);
			if(DIGITAL16_GRAY_2.digital16_gray_state.STATE.L8==1&&DIGITAL16_GRAY_2.digital16_gray_state.STATE.L9==1)
			{
				//CAR.CUR_POS=ON_Y;
				while(!TRACK_GO_STEP(0,-2000,10));//往左来一点
        TRACK_CAR_CTOL(0,2,0,0,0,0);
				S_ADJUST();								//调整完毕
			  TRACK_CAR_CTOL(0,0,0,0,0,500);
				/*赋予坐标值*/
        CAR.CUR_COR.X_COR=6;
        CAR.CUR_COR.Y_COR=3;
        TRACK.STATE=TRACK_GO_FETCH_BRICK_6;
				PlatformControl(2,0,60);//平台下降
				TRACK_CAR_CTOL(0,0,0,0,0,500);
			}
		}
		break;
//		case TRACK_GO_FETCH_BRICK_4:
//		{
//      TRACK_CAR_CTOL(0,0,0,-4000,0,0);
//			if(DIGITAL16_GRAY_1.digital16_gray_state.STATE.L8==1)
//			{		
//			TRACK_CAR_CTOL(0,0,0,0,0,100);
//			S_ADJUST();								//调整完毕
//			TRACK_CAR_CTOL(0,0,0,0,0,500);
//			TRACK.STATE=TRACK_GO_FETCH_BRICK_5;	
//		  }
//		}
//		break;
//			/*慢速向右到抓取位置*/
//		case TRACK_GO_FETCH_BRICK_5:
//		{
//		  while(!TRACK_GO_STEP(0,2000,35));
//      TRACK_CAR_CTOL(0,2,0,0,0,200);
//      TRACK.color=1;
//		  S_ADJUST();								//调整完毕
//			TRACK_CAR_CTOL(0,0,0,0,0,500);
//			TRACK.STATE=TRACK_FETCH_BRICK_2;			
//		}
//		break;
//	  /* 往前*/
//		case TRACK_FETCH_BRICK_2:
//		{
//			TRACK_CAR_CTOL(0,0,-1000,0,0,0);
//			if(LASER.laser_value[1]<=95)
//			{
//				while(!TRACK_GO_STEP(0,-2000,10));//往左来一点
//        TRACK_CAR_CTOL(0,0,0,0,0,500);
//        TRACK.color=1;
//				TRACK.STATE=WAITING_FUCK_BRIKE_2;
//			}	
//		}
//		break;
//		case WAITING_FUCK_BRIKE_2:
//		{
//		  waiting_fetch_cube();
//			//HAL_Delay(1000);
//			//TRACK_CAR_CTOL(0,0,0,2000,0,10);
//			finish_fetch(8);
//			TRACK.STATE=FETCH_BRICK_OVER_BACK_ONLINE_2;
//		}
//		break;
//		//		/*抓取完成 返回到 线上 更新坐标*/
//		case FETCH_BRICK_OVER_BACK_ONLINE_2:
//		{ 
//      //TRACK.color=3;
//			TRACK_CAR_CTOL(0,0,4000,0,0,0);
//			if(DIGITAL16_GRAY_2.digital16_gray_state.STATE.L8==1&&DIGITAL16_GRAY_2.digital16_gray_state.STATE.L9==1)
//			{
//				//CAR.CUR_POS=ON_Y;
//        TRACK_CAR_CTOL(0,2,0,0,0,0);
//				S_ADJUST();								//调整完毕
//			  TRACK_CAR_CTOL(0,0,0,0,0,500);
//				/*赋予坐标值*/
//        CAR.CUR_COR.X_COR=6;
//        CAR.CUR_COR.Y_COR=3;
//        TRACK.STATE=TRACK_GO_FETCH_BRICK_6;
//				//PlatformControl(2,0,50);//平台下降
//				TRACK_CAR_CTOL(0,0,0,0,0,1000);
//			}
//		}
//		break;
		//转向180
		case TRACK_GO_FETCH_BRICK_6:
		{
      while(!TRACK_TURN_ANGLE(50,55));
      TRACK_CAR_CTOL(0,2,0,0,0,200);			
			S_ADJUST();								//调整完毕
			TRACK_CAR_CTOL(0,0,0,0,0,500);
			TRACK.STATE=FETCH_OVER_3;	
		}
		break;
		case FETCH_OVER_3:
    {
      /*坐标法到达 4，2*/
      TRACK_COR_GO(4,2,5000,5000);
      if(TRACK.ARRIVE==ARRIVED)
      {
        CAR.V.VX=0;
        CAR.V.VY=0;
			  TRACK_CAR_CTOL(0,0,0,0,0,200);
        S_ADJUST();								//调整完毕
			  TRACK_CAR_CTOL(0,0,0,0,0,500);
        TRACK.STATE=GO_STORE_BRIKE;
      }
	  }
		break;	
		//储存己方积木块
		case GO_STORE_BRIKE:
	  {
		  CAR.V.VX=0;
      CAR.V.VY=2000;
			if(DIGITAL16_GRAY_3.digital16_gray_state.STATE.L5==1&&DIGITAL16_GRAY_3.digital16_gray_state.STATE.L12==1&&DIGITAL16_GRAY_3.digital16_gray_state.STATE.L4==1)
			{
				CAR.V.VX=0;
        CAR.V.VY=0;				
				TRACK_CAR_CTOL(0,0,0,0,0,500);
				while(!TRACK_GO_STEP(-1500,0,30));
				CAR.V.VX=0;
        CAR.V.VY=0;	
				TRACK_CAR_CTOL(0,0,0,0,0,500);
				TRACK.STATE=STORE_BRIKE;
			}	
		}
		break;
		case STORE_BRIKE:
		{
		  Duoji_angle(0x07, 680, 900);
			TRACK_CAR_CTOL(0,0,0,0,0,2500);
			Duoji_angle(0x07, 120, 900);
			while(!TRACK_GO_STEP(1500,0,30));
      CAR.V.VX=0;
      CAR.V.VY=0;	
			TRACK_CAR_CTOL(0,0,0,0,0,500);
			PlatformControl(1,0,60);//平台上升回原位
			TRACK.STATE=STORE_OVER_BACK_ONLINE_3;
		}
		break;
		case STORE_OVER_BACK_ONLINE_3:
		{
      TRACK_CAR_CTOL(0,2,0,0,0,0);	
      while(!TRACK_GO_STEP(0,3500,40));
      TRACK_CAR_CTOL(0,2,0,0,0,200);	
      S_ADJUST();								//调整完毕
			TRACK_CAR_CTOL(0,0,0,0,0,500);
      CAR.CUR_COR.X_COR=4;
      CAR.CUR_COR.Y_COR=4;
      TRACK.STATE=TRACK_GO_FETCH_BRICK_YELLOWBALL;
		}
		break;
		//抓黄球
		case TRACK_GO_FETCH_BRICK_YELLOWBALL:
        {
            /*坐标法到达 6，4*/
            TRACK_COR_GO(6,4,5000,5000);
            if(TRACK.ARRIVE==ARRIVED)
            {
                TRACK_CAR_CTOL(0,2,0,0,0,200);
                S_ADJUST();								//调整完毕
			          TRACK_CAR_CTOL(0,0,0,0,0,500);
                TRACK.STATE=TRACK_GO_FETCH_BRICK_YELLOWBALL_2;
            }
	    }
		break;	
		//转向180
				case TRACK_GO_FETCH_BRICK_YELLOWBALL_2:
		{
         while(!TRACK_TURN_ANGLE(50,55));
			   TRACK_CAR_CTOL(0,2,0,0,0,200);
			   S_ADJUST();								//调整完毕
			   TRACK_CAR_CTOL(0,0,0,0,0,500);
				 TRACK.STATE=TRACK_GO_FETCH_BRICK_YELLOWBALL_3;	
		}
			break;			
			/*慢速向右到抓取位置*/
		case TRACK_GO_FETCH_BRICK_YELLOWBALL_3:
		{
				  while(!TRACK_GO_STEP(0,2000,35));
          TRACK_CAR_CTOL(0,2,0,0,0,1000);
          TRACK.color=1;
				  S_ADJUST();								//调整完毕
			    TRACK_CAR_CTOL(0,0,0,0,0,500);
				  TRACK.STATE=TRACK_FETCH_BRICK_3;			
		}
			break;
				/* 往前*/
		case TRACK_FETCH_BRICK_3:
		{
			TRACK_CAR_CTOL(0,0,-1000,0,0,0);
			if(LASER.laser_value[1]<=95)
			{
				 while(!TRACK_GO_STEP(0,-2000,10));//往左来一点
          TRACK_CAR_CTOL(0,0,0,0,0,500);
          TRACK.color=1;
				  TRACK.STATE=WAITING_FUCK_BRIKE_3;
			}	
		}
		break;
			case WAITING_FUCK_BRIKE_3:
				{
					waiting_fetch_cube();
					//HAL_Delay(1000);
					//TRACK_CAR_CTOL(0,0,0,2000,0,10);
					finish_fetch(6);
					TRACK.STATE=FETCH_BRICK_OVER_BACK_ONLINE_3;
		    }
		break;
		//		/*抓取完成 返回到 线上 更新坐标*/
		case FETCH_BRICK_OVER_BACK_ONLINE_3:
		{ 
      //TRACK.color=3;
			TRACK_CAR_CTOL(0,0,2000,0,0,0);
			if(DIGITAL16_GRAY_2.digital16_gray_state.STATE.L8==1&&DIGITAL16_GRAY_2.digital16_gray_state.STATE.L9==1)
			{
				//CAR.CUR_POS=ON_Y;
				while(!TRACK_GO_STEP(0,-2000,10));//往左来一点
        TRACK_CAR_CTOL(0,2,0,0,0,0);
				S_ADJUST();								//调整完毕
			  TRACK_CAR_CTOL(0,0,0,0,0,500);
				/*赋予坐标值*/
        CAR.CUR_COR.X_COR=6;
        CAR.CUR_COR.Y_COR=3;
        TRACK.STATE=TRACK_GO_FETCH_BRICK_YELLOWBALL_4;
				PlatformControl(2,0,50);//平台下降
				TRACK_CAR_CTOL(0,0,0,0,0,1000);
			}
		}
		break;
				//转向180
				case TRACK_GO_FETCH_BRICK_YELLOWBALL_4:
		{
         while(!TRACK_TURN_ANGLE(50,55));
         TRACK_CAR_CTOL(0,2,0,0,0,200);			
			   S_ADJUST();								//调整完毕
			   TRACK_CAR_CTOL(0,0,0,0,0,500);
				 TRACK.STATE=FETCH_OVER_4;	
		}
			break;
			case FETCH_OVER_4:
        {
            /*坐标法到达 4，2*/
            TRACK_COR_GO(4,2,5000,5000);
            if(TRACK.ARRIVE==ARRIVED)
            {
                CAR.V.VX=0;
                CAR.V.VY=0;
							  TRACK_CAR_CTOL(0,0,0,0,0,500);
                S_ADJUST();								//调整完毕
			          TRACK_CAR_CTOL(0,0,0,0,0,500);
                TRACK.STATE=GO_STORE_BRIKE_YELLOWBALL;
            }
	    }
		break;	
			//储存黄球
		case GO_STORE_BRIKE_YELLOWBALL:
			{
				CAR.V.VX=0;
        CAR.V.VY=2000;
				if(DIGITAL16_GRAY_3.digital16_gray_state.STATE.L5==1&&DIGITAL16_GRAY_3.digital16_gray_state.STATE.L12==1&&DIGITAL16_GRAY_3.digital16_gray_state.STATE.L4==1)
			{
        CAR.V.VX=0;
        CAR.V.VY=0;				
				TRACK_CAR_CTOL(0,0,0,0,0,500);
				TRACK.STATE=GO_STORE_BRIKE_YELLOWBALL_2;
			}	
			}
			break;
			case GO_STORE_BRIKE_YELLOWBALL_2:
			{
				CAR.V.VX=0;
        CAR.V.VY=2000;
				if(DIGITAL16_GRAY_3.digital16_gray_state.STATE.L5==1&&DIGITAL16_GRAY_3.digital16_gray_state.STATE.L12!=1&&DIGITAL16_GRAY_3.digital16_gray_state.STATE.L11!=1&&DIGITAL16_GRAY_3.digital16_gray_state.STATE.L5==1)
			{
        CAR.V.VX=0;
        CAR.V.VY=0;	
				while(!TRACK_GO_STEP(-1500,0,30));
				CAR.V.VX=0;
        CAR.V.VY=0;	
				TRACK.STATE=STORE_BRIKE_YELLOWBALL;
			}	
			}
			break;
			case STORE_BRIKE_YELLOWBALL:
			{
				Duoji_angle(0x07, 500, 900);
				TRACK_CAR_CTOL(0,0,0,0,0,2500);
				Duoji_angle(0x07, 120, 900);
				while(!TRACK_GO_STEP(1500,0,30));
        CAR.V.VX=0;
        CAR.V.VY=0;	
				TRACK_CAR_CTOL(0,0,0,0,0,500);
				TRACK.STATE=STORE_OVER_BACK_ONLINE_4;
			}
			break;
			case STORE_OVER_BACK_ONLINE_4:
			{
          TRACK_CAR_CTOL(0,2,0,0,0,0);	
          while(!TRACK_GO_STEP(0,3500,35));
          TRACK_CAR_CTOL(0,2,0,0,0,0);	
          S_ADJUST();								//调整完毕
			    TRACK_CAR_CTOL(0,0,0,0,0,500);
          CAR.CUR_COR.X_COR=4;
          CAR.CUR_COR.Y_COR=4;
          TRACK.STATE=Bizhang;
			}
			break;
    case Bizhang:
    {
      //坐标法到达 6，2
      TRACK_COR_GO(6,2,5000,5000);
      if(TRACK.ARRIVE==ARRIVED)
      {
        TRACK_CAR_CTOL(0,2,0,0,0,200);
        S_ADJUST();								//调整完毕
			  TRACK_CAR_CTOL(0,0,0,0,0,500);
        TRACK.STATE=Bizhang_1;
      }
	  }
		break;
		   case Bizhang_1:
    {
       //坐标法到达 4，0
      TRACK_COR_GO(4,0,5000,5000);
      if(TRACK.ARRIVE==ARRIVED)
      {
        TRACK_CAR_CTOL(0,2,0,0,0,200);
        S_ADJUST();								//调整完毕
			  TRACK_CAR_CTOL(0,0,0,0,0,500);
        TRACK.STATE=Bizhang_2;
      }
	  }
		break;
		 case Bizhang_2:
    {
       //坐标法到达 6，0
      TRACK_COR_GO(6,0,5000,5000);
      if(TRACK.ARRIVE==ARRIVED)
      {
        TRACK_CAR_CTOL(0,2,0,0,0,200);
        S_ADJUST();								//调整完毕
			  TRACK_CAR_CTOL(0,0,0,0,0,500);
        TRACK.STATE=Bizhang_3;
      }
	  }
		break;
				case Bizhang_3:
    {
      TRACK_CAR_CTOL(0,0,0,1500,0,0);
      if(LASER.laser_value[0]<=200)
      {
			  TRACK_CAR_CTOL(0,0,0,0,0,500);
        TRACK.STATE=Bizhang_4;
      }
	  }
		break;
				case Bizhang_4:
    {
      if(LASER.laser_value[3]>=200)
      {
        TRACK_CAR_CTOL(0,0,0,0,0,500);
        TRACK.STATE=Bizhang_5;
      }
			else
			{
				TRACK.STATE=Bizhang_4;
			}
	  }
		break;
			case Bizhang_5:
    {
      TRACK_CAR_CTOL(0,0,0,-1500,0,0);
      if(DIGITAL16_GRAY_3.digital16_gray_state.STATE.L12==1)
      {
			  TRACK_CAR_CTOL(0,0,0,0,0,500);
				S_ADJUST();								//调整完毕
			  TRACK_CAR_CTOL(0,0,0,0,0,500);
        TRACK.STATE=BACK;
      }
	  }
		break;
		case BACK:
    {
      /*坐标法到达 4，6*/
      TRACK_COR_GO(4,6,5000,5000);
      if(TRACK.ARRIVE==ARRIVED)
      {
        TRACK_CAR_CTOL(0,2,0,0,0,200);
        S_ADJUST();								//调整完毕
			  TRACK_CAR_CTOL(0,0,0,0,0,500);
        TRACK.STATE=FINISH;
      }
	  }
		break;
		case FINISH:
    {
      while(!TRACK_GO_STEP(2600,1500,68));
      TRACK_CAR_CTOL(0,0,0,0,0,0);
			//CAR.CUR_COR.X_COR=0;
      //CAR.CUR_COR.Y_COR=0;
      TRACK.STATE=FINISH_2;
			//PlatformControl(2,0,53);//平台下降一半
	  }
		break;
		/*结束*/
		case FINISH_2:
		{
		}
		break;
	}
}

/*红色方先黄球再红球再积木块  走边上√ 改循迹、不抓二维码 √*/
void TRACK_MODULE_RED_RYR(void)
{
	switch(TRACK.STATE)
	{
    /*从出发区前往线上，坐标 5 0*/
		case START:
		{
      TRACK_CAR_CTOL(0,0,0,2000,0,0);
			if(DIGITAL16_GRAY_3.digital16_gray_state.STATE.L8==1&&DIGITAL16_GRAY_3.digital16_gray_state.STATE.L9==1)
			{		
				TRACK_CAR_CTOL(0,2,0,0,0,100);
				S_ADJUST();								//调整完毕
			  TRACK_CAR_CTOL(0,0,0,0,0,500);
				CAR.CUR_COR.X_COR=5;
        CAR.CUR_COR.Y_COR=0;
				TRACK.STATE=TRACK_GO_FETCH_BALL_YELLOW;
				PlatformControl(1, 0, 0);
			}	          
		}		
		break;		
    /*坐标法到达 6，4*/
    case TRACK_GO_FETCH_BALL_YELLOW:
    {
      TRACK_COR_GO(6,4,5000,5000);
      if(TRACK.ARRIVE==ARRIVED)
      {
        TRACK_CAR_CTOL(0,2,0,0,0,100);
        S_ADJUST();								//调整完毕
			  TRACK_CAR_CTOL(0,0,0,0,0,500);
        TRACK.STATE=TRACK_GO_FETCH_BALL_YELLOW_3;
      }
	  }
		break;		
	  /*坐标法到达 4，6*/
		case TRACK_GO_FETCH_BALL_YELLOW_3:
		{
      TRACK_COR_GO(4,6,5000,5000);
				
      if(TRACK.ARRIVE==ARRIVED)
      {
        TRACK_CAR_CTOL(0,2,0,0,0,200);
        S_ADJUST();								//调整完毕
			  TRACK_CAR_CTOL(0,0,0,0,0,500);
        TRACK.STATE=TRACK_FETCH_BALL_YELLOW;
      }
	  }
		break;
				/*慢速前进到抓取位置*/
		case TRACK_FETCH_BALL_YELLOW:
		{						
      TRACK_CAR_CTOL(0,0,-1000,0,0,0);
			if(LASER.laser_value[1]<=75)
			{	
			  TRACK_CAR_CTOL(0,0,0,0,0,1000);						
        TRACK.color=1;
			  TRACK.STATE=WAITING_FUCK_BALL_YELLOW;				
			}
		}
		break;
		case WAITING_FUCK_BALL_YELLOW:
		{
			waiting_fetch_ball();
			HAL_Delay(1000);
			finish_fetch(3);//圆盘机黄球
			TRACK.STATE=FETCH_BALL_OVER_YELLOW;
			//PlatformControl(2,0,50);//平台下降以便放球
		}
		break;
		//		/*抓取完成 更新当前位置与坐标*/
		case FETCH_BALL_OVER_YELLOW:
		{ 
      //TRACK.color=3;
			while(!TRACK_GO_STEP(1500,0,15));
			if(CAR.CUR_POS==ON_X)
      {
			  TRACK_CAR_CTOL(0,2,0,0,0,200);
				S_ADJUST();								//调整完毕
			  TRACK_CAR_CTOL(0,0,0,0,0,500);
				/*赋予坐标值*/
        CAR.CUR_COR.X_COR=3;
        CAR.CUR_COR.Y_COR=6;
        TRACK.STATE=FETCH_OVER_1;
			  TRACK_CAR_CTOL(0,0,0,0,0,500);
      }
		  if(CAR.CUR_POS==Yplus_CENTER)
      {
		    TRACK_CAR_CTOL(0,2,0,0,0,200);
			  S_ADJUST();								//调整完毕
			  TRACK_CAR_CTOL(0,0,0,0,0,500);
				/*赋予坐标值*/
        CAR.CUR_COR.X_COR=4;
        CAR.CUR_COR.Y_COR=6;
        TRACK.STATE=FETCH_OVER_1;
			  TRACK_CAR_CTOL(0,0,0,0,0,1000);
      }
		}
		break;
		case FETCH_OVER_1:
    {
      /*坐标法到达 4，4*/
      TRACK_COR_GO(4,4,5000,5000);
      if(TRACK.ARRIVE==ARRIVED)
      {
        //CAR.V.VX=0;
        //CAR.V.VY=0;
				TRACK_CAR_CTOL(0,0,0,0,0,500);
        S_ADJUST();								//调整完毕
			  TRACK_CAR_CTOL(0,0,0,0,0,500);
				Duoji_angle(0x07, 225, 900);
        TRACK.STATE=TRACK_GO_FETCH_BRICK_YELLOWBALL;
      }
	  }
		break;
		//抓黄球
		case TRACK_GO_FETCH_BRICK_YELLOWBALL:
        {
            /*坐标法到达 6，4*/
            TRACK_COR_GO(6,4,5000,5000);
            if(TRACK.ARRIVE==ARRIVED)
            {
                TRACK_CAR_CTOL(0,2,0,0,0,200);
                S_ADJUST();								//调整完毕
			          TRACK_CAR_CTOL(0,0,0,0,0,500);
                TRACK.STATE=TRACK_GO_FETCH_BRICK_YELLOWBALL_2;
            }
	    }
		break;	
		//转向180
				case TRACK_GO_FETCH_BRICK_YELLOWBALL_2:
		{
         while(!TRACK_TURN_ANGLE(50,55));
			   TRACK_CAR_CTOL(0,2,0,0,0,200);
			   S_ADJUST();								//调整完毕
			   TRACK_CAR_CTOL(0,0,0,0,0,500);
			   TRACK_CAR_CTOL(0,2,0,0,0,0);
			   P_ADJUST();								//调整完毕
			   TRACK_CAR_CTOL(0,0,0,0,0,500);
				 TRACK.STATE=TRACK_GO_FETCH_BRICK_YELLOWBALL_3;	
		}
			break;			
			/*慢速向右到抓取位置*/
		case TRACK_GO_FETCH_BRICK_YELLOWBALL_3:
		{
				  while(!TRACK_GO_STEP(0,2000,35));
          TRACK_CAR_CTOL(0,2,0,0,0,200);
          TRACK.color=1;
				  S_ADJUST();								//调整完毕
			    TRACK_CAR_CTOL(0,0,0,0,0,500);
			    TRACK_CAR_CTOL(0,2,0,0,0,0);
			    P_ADJUST();								//调整完毕
			    TRACK_CAR_CTOL(0,0,0,0,0,500);
				  TRACK.STATE=TRACK_FETCH_BRICK_3;			
		}
			break;
				/* 往前*/
		case TRACK_FETCH_BRICK_3:
		{
			TRACK_CAR_CTOL(0,0,-1000,0,0,0);
			if(LASER.laser_value[1]<=95)
			{
				  while(!TRACK_GO_STEP(0,-2000,10));//往左来一点
          TRACK_CAR_CTOL(0,0,0,0,0,500);
          TRACK.color=1;
				  TRACK.STATE=WAITING_FUCK_BRIKE_3;
			}	
		}
		break;
			case WAITING_FUCK_BRIKE_3:
				{
					waiting_fetch_cube();
					//HAL_Delay(1000);
					//TRACK_CAR_CTOL(0,0,0,2000,0,10);
					finish_fetch(6);//平台黄球
					TRACK.STATE=FETCH_BRICK_OVER_BACK_ONLINE_3;
		    }
		break;
		//		/*抓取完成 返回到 线上 更新坐标*/
		case FETCH_BRICK_OVER_BACK_ONLINE_3:
		{ 
      //TRACK.color=3;
			TRACK_CAR_CTOL(0,0,2000,0,0,0);
			if(DIGITAL16_GRAY_2.digital16_gray_state.STATE.L8==1&&DIGITAL16_GRAY_2.digital16_gray_state.STATE.L9==1)
			{
				//CAR.CUR_POS=ON_Y;
				while(!TRACK_GO_STEP(0,-2000,20));//往左来一点
        TRACK_CAR_CTOL(0,2,0,0,0,200);
				S_ADJUST();								//调整完毕
			  TRACK_CAR_CTOL(0,0,0,0,0,500);
				/*赋予坐标值*/
        CAR.CUR_COR.X_COR=6;
        CAR.CUR_COR.Y_COR=3;
        TRACK.STATE=TRACK_GO_FETCH_BRICK_YELLOWBALL_4;
				PlatformControl(2,0,50);//平台下降
				TRACK_CAR_CTOL(0,0,0,0,0,500);
			}
		}
		break;
				//转向180
				case TRACK_GO_FETCH_BRICK_YELLOWBALL_4:
		{
         while(!TRACK_TURN_ANGLE(50,55));
         TRACK_CAR_CTOL(0,2,0,0,0,200);			
			   S_ADJUST();								//调整完毕
			   TRACK_CAR_CTOL(0,0,0,0,0,500);
				 TRACK.STATE=FETCH_OVER_2;	
		}
			break;
			case FETCH_OVER_2:
        {
            /*坐标法到达 4，4*/
            TRACK_COR_GO(4,4,5000,5000);
            if(TRACK.ARRIVE==ARRIVED)
            {
                CAR.V.VX=0;
                CAR.V.VY=0;
							  TRACK_CAR_CTOL(0,0,0,0,0,500);
                S_ADJUST();								//调整完毕
			          TRACK_CAR_CTOL(0,0,0,0,0,500);
                TRACK.STATE=GO_STORE_BRIKE_YELLOWBALL;
            }
	    }
		break;	
			//储存所有黄球
		case GO_STORE_BRIKE_YELLOWBALL:
			{
		  CAR.V.VX=0;
      CAR.V.VY=-2000;
		  if(DIGITAL16_GRAY_3.digital16_gray_state.STATE.L5==1&&DIGITAL16_GRAY_3.digital16_gray_state.STATE.L4==1)
			{
        CAR.V.VX=0;
        CAR.V.VY=0;				
				TRACK_CAR_CTOL(0,0,0,0,0,1500);
				while(!TRACK_GO_STEP(-1500,0,30));
				CAR.V.VX=0;
        CAR.V.VY=0;	
				TRACK.STATE=STORE_BRIKE_YELLOWBALL;
			}	
		}
			break;
			case STORE_BRIKE_YELLOWBALL:
			{
				Duoji_angle(0x07, 500, 900);
				TRACK_CAR_CTOL(0,0,0,0,0,2500);
				Duoji_angle(0x07, 120, 900);
				while(!TRACK_GO_STEP(1500,0,30));
        CAR.V.VX=0;
        CAR.V.VY=0;	
				TRACK_CAR_CTOL(0,0,0,0,0,500);
				TRACK.STATE=STORE_OVER_BACK_ONLINE;
			}
			break;
			case STORE_OVER_BACK_ONLINE:
			{
          TRACK_CAR_CTOL(0,2,0,0,0,0);	
          while(!TRACK_GO_STEP(0,3500,35));
          TRACK_CAR_CTOL(0,2,0,0,0,200);	
          S_ADJUST();								//调整完毕
			    TRACK_CAR_CTOL(0,0,0,0,0,500);
          CAR.CUR_COR.X_COR=4;
          CAR.CUR_COR.Y_COR=4;
				  PlatformControl(1,0,50);//平台上升
          TRACK.STATE=TRACK_GO_FETCH_BALL_RED;
			}
			break;
		/*坐标法到达 4，6*/
		case TRACK_GO_FETCH_BALL_RED:
		{
      TRACK_COR_GO(4,6,5000,5000);
				
      if(TRACK.ARRIVE==ARRIVED)
      {
        TRACK_CAR_CTOL(0,2,0,0,0,200);
        S_ADJUST();								//调整完毕
			  TRACK_CAR_CTOL(0,0,0,0,0,500);
        TRACK.STATE=TRACK_FETCH_BALL_RED;
      }
	  }
		break;
	  /*慢速前进到抓取位置*/
		case TRACK_FETCH_BALL_RED:
		{				
		  TRACK_CAR_CTOL(0,0,-1000,0,0,0);
			/*三号灰度 L1 L2灰度落在白线，并且有一激光小于12cm*/
			if(LASER.laser_value[1]<=75)
			{	
			  TRACK_CAR_CTOL(0,0,0,0,0,500);
				TRACK.color=1;
				TRACK.STATE=WAITING_FUCK_BALL_RED;								
			}
		}
		break;
		case WAITING_FUCK_BALL_RED:
		{
		  waiting_fetch_ball();
			HAL_Delay(1000);
			finish_fetch(1);//圆盘机红球
			TRACK.STATE=FETCH_BALL_OVER_RED;
		}
		break;
		//		/*抓取完成 更新当前位置与坐标*/
		case FETCH_BALL_OVER_RED:
		{ 
		  //TRACK.color=3;
			while(!TRACK_GO_STEP(1500,0,15));
			if(CAR.CUR_POS==ON_X)
      {
			  TRACK_CAR_CTOL(0,2,0,0,0,200);
				S_ADJUST();								//调整完毕
			  TRACK_CAR_CTOL(0,0,0,0,0,500);
				/*赋予坐标值*/
        CAR.CUR_COR.X_COR=3;
        CAR.CUR_COR.Y_COR=6;
        TRACK.STATE=FETCH_OVER_3;
			  TRACK_CAR_CTOL(0,0,0,0,0,500);
      }
		  if(CAR.CUR_POS==Yplus_CENTER)
      {
			  TRACK_CAR_CTOL(0,2,0,0,0,200);
				S_ADJUST();								//调整完毕
			  TRACK_CAR_CTOL(0,0,0,0,0,500);
				/*赋予坐标值*/
        CAR.CUR_COR.X_COR=4;
        CAR.CUR_COR.Y_COR=6;
        TRACK.STATE=FETCH_OVER_3;
			  TRACK_CAR_CTOL(0,0,0,0,0,1000);
      }
		}
		break;
	  case FETCH_OVER_3:
    {
      /*坐标法到达 4，4*/
      TRACK_COR_GO(4,4,5000,5000);
      if(TRACK.ARRIVE==ARRIVED)
      {
        //CAR.V.VX=0;
        //CAR.V.VY=0;
			  TRACK_CAR_CTOL(0,0,0,0,0,500);
        S_ADJUST();								//调整完毕
			  TRACK_CAR_CTOL(0,0,0,0,0,500);
				Duoji_angle(0x07, 225, 900);
        TRACK.STATE=TRACK_GO_FETCH_BRICK;
      }
	  }
		break;
    case TRACK_GO_FETCH_BRICK:
    {
      /*坐标法到达 6，4*/
      TRACK_COR_GO(6,4,5000,5000);
      if(TRACK.ARRIVE==ARRIVED)
      {
        TRACK_CAR_CTOL(0,2,0,0,0,200);
        S_ADJUST();								//调整完毕
			  TRACK_CAR_CTOL(0,0,0,0,0,500);
        TRACK.STATE=TRACK_GO_FETCH_BRICK_2;
      }
	  }
		break;	
		//转向180
		case TRACK_GO_FETCH_BRICK_2:
		{
      while(!TRACK_TURN_ANGLE(50,55));
			TRACK_CAR_CTOL(0,2,0,0,0,200);
			S_ADJUST();								//调整完毕
			TRACK_CAR_CTOL(0,0,0,0,0,500);
			TRACK_CAR_CTOL(0,2,0,0,0,0);
			P_ADJUST();								//调整完毕
			TRACK_CAR_CTOL(0,0,0,0,0,500);
			TRACK.STATE=TRACK_GO_FETCH_BRICK_3;	
		}
		break;			
		/*慢速向右到抓取位置*/
		case TRACK_GO_FETCH_BRICK_3:
		{
		  while(!TRACK_GO_STEP(0,2000,35));
      TRACK_CAR_CTOL(0,2,0,0,0,300);
		  S_ADJUST();								//调整完毕
			TRACK_CAR_CTOL(0,0,0,0,0,500);
			TRACK_CAR_CTOL(0,2,0,0,0,0);
			P_ADJUST();								//调整完毕
			TRACK_CAR_CTOL(0,0,0,0,0,500);
			TRACK.STATE=TRACK_FETCH_BRICK;			
		}
		break;
	  /* 往前*/
		case TRACK_FETCH_BRICK:
		{
			TRACK_CAR_CTOL(0,0,-1000,0,0,0);
			if(LASER.laser_value[1]<=95)
			{
				while(!TRACK_GO_STEP(0,-2000,10));//往左来一点
        TRACK_CAR_CTOL(0,0,0,0,0,500);
        TRACK.color=1;
				TRACK.STATE=WAITING_FUCK_BRIKE;
			}	
		}
		break;
		case WAITING_FUCK_BRIKE:
		{
		  waiting_fetch_cube();
			finish_fetch(4);//平台红球与积木
			TRACK.STATE=FETCH_BRICK_OVER_BACK_ONLINE;
		}
		break;
		//		/*抓取完成 返回到 线上 更新坐标*/
		case FETCH_BRICK_OVER_BACK_ONLINE:
		{ 
			TRACK_CAR_CTOL(0,0,2000,0,0,0);
			if(DIGITAL16_GRAY_2.digital16_gray_state.STATE.L8==1&&DIGITAL16_GRAY_2.digital16_gray_state.STATE.L9==1)
			{
				while(!TRACK_GO_STEP(0,-2000,20));//往左来一点
        TRACK_CAR_CTOL(0,2,0,0,0,200);
				S_ADJUST();								//调整完毕
			  TRACK_CAR_CTOL(0,0,0,0,0,500);
				/*赋予坐标值*/
        CAR.CUR_COR.X_COR=6;
        CAR.CUR_COR.Y_COR=3;
        TRACK.STATE=TRACK_GO_FETCH_BRICK_6;
				PlatformControl(2,0,60);//平台下降
				TRACK_CAR_CTOL(0,0,0,0,0,1000);
			}
		}
		break;
		//转向180
		case TRACK_GO_FETCH_BRICK_6:
		{
      while(!TRACK_TURN_ANGLE(50,55));
      TRACK_CAR_CTOL(0,2,0,0,0,200);			
			S_ADJUST();								//调整完毕
			TRACK_CAR_CTOL(0,0,0,0,0,500);
			TRACK.STATE=FETCH_OVER_4;	
		}
		break;
		case FETCH_OVER_4:
    {
      /*坐标法到达 4，4*/
      TRACK_COR_GO(4,4,5000,5000);
      if(TRACK.ARRIVE==ARRIVED)
      {
        CAR.V.VX=0;
        CAR.V.VY=0;
			  TRACK_CAR_CTOL(0,2,0,0,0,200);
        S_ADJUST();								//调整完毕
			  TRACK_CAR_CTOL(0,0,0,0,0,500);
        TRACK.STATE=GO_STORE_BRIKE;
      }
	  }
		break;	
		//储存己方积木块与球
		case GO_STORE_BRIKE:
	  {
		  CAR.V.VX=0;
      CAR.V.VY=-2000;
			if(DIGITAL16_GRAY_3.digital16_gray_state.STATE.L5==1&&DIGITAL16_GRAY_3.digital16_gray_state.STATE.L14==1&&DIGITAL16_GRAY_3.digital16_gray_state.STATE.L6==1)
			{
				CAR.V.VX=0;
        CAR.V.VY=0;				
				TRACK_CAR_CTOL(0,0,0,0,0,500);
				while(!TRACK_GO_STEP(-1500,0,30));
				CAR.V.VX=0;
        CAR.V.VY=0;	
				TRACK_CAR_CTOL(0,0,0,0,0,500);
				TRACK.STATE=STORE_BRIKE;
			}	
		}
		break;
		case STORE_BRIKE:
		{
		  Duoji_angle(0x07, 680, 900);
			TRACK_CAR_CTOL(0,0,0,0,0,2500);
			Duoji_angle(0x07, 120, 900);
			while(!TRACK_GO_STEP(1500,0,30));
      CAR.V.VX=0;
      CAR.V.VY=0;	
			TRACK_CAR_CTOL(0,0,0,0,0,500);
			TRACK.STATE=STORE_OVER_BACK_ONLINE_2;
		}
		break;
		case STORE_OVER_BACK_ONLINE_2:
		{
      TRACK_CAR_CTOL(0,2,0,0,0,0);	
      while(!TRACK_GO_STEP(0,3500,50));
      TRACK_CAR_CTOL(0,2,0,0,0,200);	
      S_ADJUST();								//调整完毕
			TRACK_CAR_CTOL(0,0,0,0,0,500);
      CAR.CUR_COR.X_COR=4;
      CAR.CUR_COR.Y_COR=4;
      TRACK.STATE=Bizhang;
		}
		break;		
				case Bizhang:
    {
      //坐标法到达 6，4
      TRACK_COR_GO(6,4,5000,5000);
      if(TRACK.ARRIVE==ARRIVED)
      {
        TRACK_CAR_CTOL(0,2,0,0,0,500);
        S_ADJUST();								//调整完毕
			  TRACK_CAR_CTOL(0,0,0,0,0,500);
        TRACK.STATE=Bizhang_1;
      }
	  }
		break;
				case Bizhang_1:
    {
      TRACK_CAR_CTOL(0,0,0,1500,0,0);
      if(LASER.laser_value[0]<=200)
      {
			  TRACK_CAR_CTOL(0,0,0,0,0,6000);
        TRACK.STATE=Bizhang_2;
      }
	  }
		break;
				case Bizhang_2:
    {
			TRACK_CAR_CTOL(0,0,0,-1500,0,0);
      if(DIGITAL16_GRAY_3.digital16_gray_state.STATE.L13==1)
      {
        TRACK_CAR_CTOL(0,2,0,0,0,500);
        S_ADJUST();								//调整完毕
			  TRACK_CAR_CTOL(0,0,0,0,0,500);
				CAR.CUR_COR.X_COR=6;
        CAR.CUR_COR.Y_COR=4;
        TRACK.STATE=BACK;		
      }
	  }
		break;
		
		case BACK:
    {
      /*坐标法到达 6，0*/
      TRACK_COR_GO(6,0,5000,5000);
      if(TRACK.ARRIVE==ARRIVED)
      {
        TRACK_CAR_CTOL(0,2,0,0,0,500);
        S_ADJUST();								//调整完毕
			  TRACK_CAR_CTOL(0,0,0,0,0,500);
        TRACK.STATE=FINISH;
      }
	  }
		break;
		case FINISH:
    {
      while(!TRACK_GO_STEP(-2600,-1800,68));
      TRACK_CAR_CTOL(0,0,0,0,0,0);
      TRACK.STATE=FINISH_2;
	  }
		break;
		/*结束*/
		case FINISH_2:
		{
		}
		break;
	}

}

/*蓝色方先黄球再蓝球再积木块  走边上√ 改循迹、不抓二维码 √*/
void TRACK_MODULE_BLUE_BYB(void)
{
	switch(TRACK.STATE)
	{
    /*从出发区前往线上，坐标 5 6*/
		case START:
		{
      TRACK_CAR_CTOL(0,0,0,-2000,0,0);
			if(DIGITAL16_GRAY_3.digital16_gray_state.STATE.L8==1&&DIGITAL16_GRAY_3.digital16_gray_state.STATE.L9==1)
			{		
				TRACK_CAR_CTOL(0,2,0,0,0,100);
				S_ADJUST();								//调整完毕
			  TRACK_CAR_CTOL(0,0,0,0,0,500);
				CAR.CUR_COR.X_COR=5;
        CAR.CUR_COR.Y_COR=6;
				TRACK.STATE=TRACK_GO_FETCH_BALL_YELLOW;
				PlatformControl(1, 0, 0);
			}	          
		}		
		break;	
    /*坐标法到达 6，2准备过储存区*/
    case TRACK_GO_FETCH_BALL_YELLOW:
    {
      TRACK_COR_GO(6,2,6000,6000);
      if(TRACK.ARRIVE==ARRIVED)
      {
        TRACK_CAR_CTOL(0,2,0,0,0,100);
        S_ADJUST();								//调整完毕
			  TRACK_CAR_CTOL(0,0,0,0,0,500);
        TRACK.STATE=TRACK_GO_FETCH_BALL_YELLOW_3;
      }
	  }
		break;	
	  /*坐标法到达 4，0*/
		case TRACK_GO_FETCH_BALL_YELLOW_3:
		{
      TRACK_COR_GO(4,0,6000,6000);
				
      if(TRACK.ARRIVE==ARRIVED)
      {
        TRACK_CAR_CTOL(0,2,0,0,0,200);
        S_ADJUST();								//调整完毕
			  TRACK_CAR_CTOL(0,0,0,0,0,500);
        TRACK.STATE=TRACK_FETCH_BALL_YELLOW;
      }
	  }
		break;
				/*慢速前进到抓取位置*/
		case TRACK_FETCH_BALL_YELLOW:
		{						
      TRACK_CAR_CTOL(0,0,-1000,0,0,0);
			if(LASER.laser_value[1]<=75)
			{	
			  TRACK_CAR_CTOL(0,0,0,0,0,200);						
        TRACK.color=1;
			  TRACK.STATE=WAITING_FUCK_BALL_YELLOW;				
			}
		}
		break;
		case WAITING_FUCK_BALL_YELLOW:
		{
			waiting_fetch_ball();
			HAL_Delay(300);
			finish_fetch(3);//圆盘机黄球
			TRACK.STATE=FETCH_BALL_OVER_YELLOW;
		}
		break;
			/*抓取完成 更新当前位置与坐标*/
		case FETCH_BALL_OVER_YELLOW:
		{ 
      //TRACK.color=3;
			while(!TRACK_GO_STEP(1500,0,15));
			if(CAR.CUR_POS==ON_X)
      {
			  TRACK_CAR_CTOL(0,2,0,0,0,200);
				S_ADJUST();								//调整完毕
			  TRACK_CAR_CTOL(0,0,0,0,0,500);
				/*赋予坐标值*/
        CAR.CUR_COR.X_COR=3;
        CAR.CUR_COR.Y_COR=0;
        TRACK.STATE=FETCH_OVER_1;
			  TRACK_CAR_CTOL(0,0,0,0,0,500);
      }
		  if(CAR.CUR_POS==Yminus_CENTER)
      {
		    TRACK_CAR_CTOL(0,2,0,0,0,200);
			  S_ADJUST();								//调整完毕
			  TRACK_CAR_CTOL(0,0,0,0,0,500);
				/*赋予坐标值*/
        CAR.CUR_COR.X_COR=4;
        CAR.CUR_COR.Y_COR=0;
        TRACK.STATE=FETCH_OVER_1;
			  TRACK_CAR_CTOL(0,0,0,0,0,200);
      }
		}
		break;
		case FETCH_OVER_1:
    {
      /*坐标法到达 4，2*/
      TRACK_COR_GO(4,2,6000,6000);
      if(TRACK.ARRIVE==ARRIVED)
      {
				TRACK_CAR_CTOL(0,0,0,0,0,200);
        S_ADJUST();								//调整完毕
			  TRACK_CAR_CTOL(0,0,0,0,0,500);
				Duoji_angle(0x07, 225, 900);
        TRACK.STATE=TRACK_GO_FETCH_BRICK_YELLOWBALL;
      }
	  }
		break;
		//抓平台黄球
		case TRACK_GO_FETCH_BRICK_YELLOWBALL:
        {
            /*坐标法到达 6，4*/
            TRACK_COR_GO(6,4,6000,6000);
            if(TRACK.ARRIVE==ARRIVED)
            {
                TRACK_CAR_CTOL(0,2,0,0,0,200);
                S_ADJUST();								//调整完毕
			          TRACK_CAR_CTOL(0,0,0,0,0,500);
                TRACK.STATE=TRACK_GO_FETCH_BRICK_YELLOWBALL_2;
            }
	    }
		break;	
		//转向180
				case TRACK_GO_FETCH_BRICK_YELLOWBALL_2:
		{
         while(!TRACK_TURN_ANGLE(50,55));
			   TRACK_CAR_CTOL(0,2,0,0,0,200);
			   S_ADJUST();								//调整完毕
			   TRACK_CAR_CTOL(0,0,0,0,0,500);
			   TRACK_CAR_CTOL(0,2,0,0,0,0);
			   P_ADJUST();								//调整完毕
			   TRACK_CAR_CTOL(0,0,0,0,0,500);
				 TRACK.STATE=TRACK_GO_FETCH_BRICK_YELLOWBALL_3;	
		}
			break;			
			/*慢速向右到抓取位置*/
		case TRACK_GO_FETCH_BRICK_YELLOWBALL_3:
		{
				  while(!TRACK_GO_STEP(0,2000,35));
          TRACK_CAR_CTOL(0,2,0,0,0,200);
          TRACK.color=1;
				  S_ADJUST();								//调整完毕
			    TRACK_CAR_CTOL(0,0,0,0,0,500);
			    TRACK_CAR_CTOL(0,2,0,0,0,0);
			    P_ADJUST();								//调整完毕
			    TRACK_CAR_CTOL(0,0,0,0,0,500);
				  TRACK.STATE=TRACK_FETCH_BRICK_3;			
		}
			break;
				/* 往前*/
		case TRACK_FETCH_BRICK_3:
		{
			TRACK_CAR_CTOL(0,0,-1000,0,0,0);
			if(LASER.laser_value[1]<=95)
			{
				 while(!TRACK_GO_STEP(0,-2000,10));//往左来一点
          TRACK_CAR_CTOL(0,0,0,0,0,500);
          TRACK.color=1;
				  TRACK.STATE=WAITING_FUCK_BRIKE_3;
			}	
		}
		break;
			case WAITING_FUCK_BRIKE_3:
				{
					waiting_fetch_cube();
					finish_fetch(6);//平台黄球
					TRACK.STATE=FETCH_BRICK_OVER_BACK_ONLINE_3;
		    }
		break;
		//		/*抓取完成 返回到 线上 更新坐标*/
		case FETCH_BRICK_OVER_BACK_ONLINE_3:
		{ 
      //TRACK.color=3;
			TRACK_CAR_CTOL(0,0,2000,0,0,0);
			if(DIGITAL16_GRAY_2.digital16_gray_state.STATE.L8==1&&DIGITAL16_GRAY_2.digital16_gray_state.STATE.L9==1)
			{
				//CAR.CUR_POS=ON_Y;
				while(!TRACK_GO_STEP(0,-2000,10));//往左来一点
        TRACK_CAR_CTOL(0,2,0,0,0,0);
				S_ADJUST();								//调整完毕
			  TRACK_CAR_CTOL(0,0,0,0,0,500);
				/*赋予坐标值*/
        CAR.CUR_COR.X_COR=6;
        CAR.CUR_COR.Y_COR=3;
        TRACK.STATE=TRACK_GO_FETCH_BRICK_YELLOWBALL_4;
				PlatformControl(2,0,50);//平台下降
				TRACK_CAR_CTOL(0,0,0,0,0,500);
			}
		}
		break;
				//转向180
				case TRACK_GO_FETCH_BRICK_YELLOWBALL_4:
		{
         while(!TRACK_TURN_ANGLE(50,55));
         TRACK_CAR_CTOL(0,2,0,0,0,200);			
			   S_ADJUST();								//调整完毕
			   TRACK_CAR_CTOL(0,0,0,0,0,500);
				 TRACK.STATE=FETCH_OVER_2;	
		}
			break;
			case FETCH_OVER_2:
        {
            /*坐标法到达 4，2*/
            TRACK_COR_GO(4,2,6000,6000);
            if(TRACK.ARRIVE==ARRIVED)
            {
                CAR.V.VX=0;
                CAR.V.VY=0;
							  TRACK_CAR_CTOL(0,0,0,0,0,500);
                S_ADJUST();								//调整完毕
			          TRACK_CAR_CTOL(0,0,0,0,0,500);
                TRACK.STATE=GO_STORE_BRIKE_YELLOWBALL;
            }
	    }
		break;	
		//储存黄球
		case GO_STORE_BRIKE_YELLOWBALL:
			{
				CAR.V.VX=0;
        CAR.V.VY=2000;
				if(DIGITAL16_GRAY_3.digital16_gray_state.STATE.L5==1&&DIGITAL16_GRAY_3.digital16_gray_state.STATE.L12==1&&DIGITAL16_GRAY_3.digital16_gray_state.STATE.L4==1)
			{
        CAR.V.VX=0;
        CAR.V.VY=0;				
				TRACK_CAR_CTOL(0,0,0,0,0,500);
				TRACK.STATE=GO_STORE_BRIKE_YELLOWBALL_2;
			}	
			}
			break;
			case GO_STORE_BRIKE_YELLOWBALL_2:
			{
				CAR.V.VX=0;
        CAR.V.VY=2000;
				if(DIGITAL16_GRAY_3.digital16_gray_state.STATE.L5==1&&DIGITAL16_GRAY_3.digital16_gray_state.STATE.L12!=1&&DIGITAL16_GRAY_3.digital16_gray_state.STATE.L11!=1&&DIGITAL16_GRAY_3.digital16_gray_state.STATE.L5==1)
			{
        CAR.V.VX=0;
        CAR.V.VY=0;	
				while(!TRACK_GO_STEP(-1500,0,30));
				CAR.V.VX=0;
        CAR.V.VY=0;	
				TRACK.STATE=STORE_BRIKE_YELLOWBALL;
			}	
			}
			break;
			case STORE_BRIKE_YELLOWBALL:
			{
				Duoji_angle(0x07, 500, 900);
				TRACK_CAR_CTOL(0,0,0,0,0,2500);
				Duoji_angle(0x07, 120, 900);
				while(!TRACK_GO_STEP(1500,0,30));
        CAR.V.VX=0;
        CAR.V.VY=0;	
				TRACK_CAR_CTOL(0,0,0,0,0,500);
				TRACK.STATE=STORE_OVER_BACK_ONLINE;
			}
			break;
			case STORE_OVER_BACK_ONLINE:
			{
          TRACK_CAR_CTOL(0,2,0,0,0,0);	
          while(!TRACK_GO_STEP(0,-3500,72));
          TRACK_CAR_CTOL(0,2,0,0,0,300);	
          S_ADJUST();								//调整完毕
			    TRACK_CAR_CTOL(0,0,0,0,0,500);
          CAR.CUR_COR.X_COR=4;
          CAR.CUR_COR.Y_COR=2;
				  PlatformControl(1,0,50);//平台上升
          TRACK.STATE=TRACK_GO_FETCH_BALL_BLUE;
			}
			break;
		/*坐标法到达 4，0*/
		case TRACK_GO_FETCH_BALL_BLUE:
		{
      TRACK_COR_GO(4,0,6000,6000);
				
      if(TRACK.ARRIVE==ARRIVED)
      {
        TRACK_CAR_CTOL(0,2,0,0,0,200);
        S_ADJUST();								//调整完毕
			  TRACK_CAR_CTOL(0,0,0,0,0,500);
        TRACK.STATE=TRACK_FETCH_BALL_BLUE;
      }
	  }
		break;
	  /*慢速前进到抓取位置*/
		case TRACK_FETCH_BALL_BLUE:
		{				
		  TRACK_CAR_CTOL(0,0,-1000,0,0,0);
			/*三号灰度 L1 L2灰度落在白线，并且有一激光小于12cm*/
			if(LASER.laser_value[1]<=75)
			{	
			  TRACK_CAR_CTOL(0,0,0,0,0,500);
				TRACK.color=1;
				TRACK.STATE=WAITING_FUCK_BALL_BLUE;								
			}
		}
		break;
		case WAITING_FUCK_BALL_BLUE:
		{
		  waiting_fetch_ball();
			HAL_Delay(1000);
			finish_fetch(2);//圆盘机蓝球
			TRACK.STATE=FETCH_BALL_OVER_BLUE;
			//PlatformControl(2,0,50);//平台下降以便放球
		}
		break;
		//		/*抓取完成 更新当前位置与坐标*/
		case FETCH_BALL_OVER_BLUE:
		{ 
		  //TRACK.color=3;
			while(!TRACK_GO_STEP(1500,0,15));
			if(CAR.CUR_POS==ON_X)
      {
			  TRACK_CAR_CTOL(0,2,0,0,0,200);
				S_ADJUST();								//调整完毕
			  TRACK_CAR_CTOL(0,0,0,0,0,500);
				/*赋予坐标值*/
        CAR.CUR_COR.X_COR=3;
        CAR.CUR_COR.Y_COR=0;
        TRACK.STATE=FETCH_OVER_3;
			  TRACK_CAR_CTOL(0,0,0,0,0,500);
      }
		  if(CAR.CUR_POS==Yminus_CENTER)
      {
			  TRACK_CAR_CTOL(0,2,0,0,0,200);
				S_ADJUST();								//调整完毕
			  TRACK_CAR_CTOL(0,0,0,0,0,500);
				/*赋予坐标值*/
        CAR.CUR_COR.X_COR=4;
        CAR.CUR_COR.Y_COR=0;
        TRACK.STATE=FETCH_OVER_3;
			  TRACK_CAR_CTOL(0,0,0,0,0,500);
      }
		}
		break;
	  case FETCH_OVER_3:
    {
      /*坐标法到达 4，2*/
      TRACK_COR_GO(4,2,6000,6000);
      if(TRACK.ARRIVE==ARRIVED)
      {
			  TRACK_CAR_CTOL(0,0,0,0,0,500);
        S_ADJUST();								//调整完毕
			  TRACK_CAR_CTOL(0,0,0,0,0,500);
				Duoji_angle(0x07, 225, 900);
        TRACK.STATE=TRACK_GO_FETCH_BRICK;
      }
	  }
		break;
		case TRACK_GO_FETCH_BRICK:
    {
      /*坐标法到达 6，4*/
      TRACK_COR_GO(6,4,6000,6000);
      if(TRACK.ARRIVE==ARRIVED)
      {
        TRACK_CAR_CTOL(0,2,0,0,0,200);
        S_ADJUST();								//调整完毕
			  TRACK_CAR_CTOL(0,0,0,0,0,500);
        TRACK.STATE=TRACK_GO_FETCH_BRICK_2;
      }
	  }
		break;	
		//转向180
		case TRACK_GO_FETCH_BRICK_2:
		{
      while(!TRACK_TURN_ANGLE(50,55));
			TRACK_CAR_CTOL(0,2,0,0,0,200);
			S_ADJUST();								//调整完毕
			TRACK_CAR_CTOL(0,0,0,0,0,500);
			TRACK_CAR_CTOL(0,2,0,0,0,0);
			P_ADJUST();								//调整完毕
			TRACK_CAR_CTOL(0,0,0,0,0,500);
			TRACK.STATE=TRACK_GO_FETCH_BRICK_3;	
		}
		break;			
		/*慢速向右到抓取位置*/
		case TRACK_GO_FETCH_BRICK_3:
		{
		  while(!TRACK_GO_STEP(0,2000,35));
      TRACK_CAR_CTOL(0,2,0,0,0,200);
      TRACK.color=1;
		  S_ADJUST();								//调整完毕
			TRACK_CAR_CTOL(0,0,0,0,0,500);
			TRACK_CAR_CTOL(0,2,0,0,0,0);
			P_ADJUST();								//调整完毕
			TRACK_CAR_CTOL(0,0,0,0,0,500);
			TRACK.STATE=TRACK_FETCH_BRICK;			
		}
		break;
	  /* 往前*/
		case TRACK_FETCH_BRICK:
		{
			TRACK_CAR_CTOL(0,0,-1000,0,0,0);
			if(LASER.laser_value[1]<=95)
			{
				while(!TRACK_GO_STEP(0,-2000,10));//往左来一点
        TRACK_CAR_CTOL(0,0,0,0,0,100);
        //TRACK.color=1;
				TRACK.STATE=WAITING_FUCK_BRIKE;
			}	
		}
		break;
		case WAITING_FUCK_BRIKE:
		{
		  waiting_fetch_cube();
			finish_fetch(5);//平台蓝球与积木块
			TRACK.STATE=FETCH_BRICK_OVER_BACK_ONLINE;
		}
		break;
		//		/*抓取完成 返回到 线上 更新坐标*/
		case FETCH_BRICK_OVER_BACK_ONLINE:
		{  
			TRACK_CAR_CTOL(0,0,2000,0,0,0);
			if(DIGITAL16_GRAY_2.digital16_gray_state.STATE.L8==1&&DIGITAL16_GRAY_2.digital16_gray_state.STATE.L9==1)
			{
				while(!TRACK_GO_STEP(0,-2000,20));//往左来一点
        TRACK_CAR_CTOL(0,2,0,0,0,0);
				S_ADJUST();								//调整完毕
			  TRACK_CAR_CTOL(0,0,0,0,0,500);
				/*赋予坐标值*/
        CAR.CUR_COR.X_COR=6;
        CAR.CUR_COR.Y_COR=3;
        TRACK.STATE=TRACK_GO_FETCH_BRICK_6;
				PlatformControl(2,0,60);//平台下降
				TRACK_CAR_CTOL(0,0,0,0,0,500);
			}
		}
		break;
		//转向180
		case TRACK_GO_FETCH_BRICK_6:
		{
      while(!TRACK_TURN_ANGLE(50,55));
      TRACK_CAR_CTOL(0,2,0,0,0,200);			
			S_ADJUST();								//调整完毕
			TRACK_CAR_CTOL(0,0,0,0,0,500);
			TRACK.STATE=FETCH_OVER_4;	
		}
		break;
		case FETCH_OVER_4:
    {
      /*坐标法到达 4，2*/
      TRACK_COR_GO(4,2,6000,6000);
      if(TRACK.ARRIVE==ARRIVED)
      {
        CAR.V.VX=0;
        CAR.V.VY=0;
			  TRACK_CAR_CTOL(0,0,0,0,0,200);
        S_ADJUST();								//调整完毕
			  TRACK_CAR_CTOL(0,0,0,0,0,500);
        TRACK.STATE=GO_STORE_BRIKE;
      }
	  }
		break;	
		//储存己方积木块与球
		case GO_STORE_BRIKE:
	  {
		  CAR.V.VX=0;
      CAR.V.VY=2000;
			if(DIGITAL16_GRAY_3.digital16_gray_state.STATE.L5==1&&DIGITAL16_GRAY_3.digital16_gray_state.STATE.L12==1&&DIGITAL16_GRAY_3.digital16_gray_state.STATE.L4==1)
			{
				CAR.V.VX=0;
        CAR.V.VY=0;				
				TRACK_CAR_CTOL(0,0,0,0,0,500);
				while(!TRACK_GO_STEP(-1500,0,30));
				CAR.V.VX=0;
        CAR.V.VY=0;	
				TRACK_CAR_CTOL(0,0,0,0,0,500);
				TRACK.STATE=STORE_BRIKE;
			}	
		}
		break;
		case STORE_BRIKE:
		{
		  Duoji_angle(0x07, 680, 900);
			TRACK_CAR_CTOL(0,0,0,0,0,2500);
			Duoji_angle(0x07, 120, 900);
			while(!TRACK_GO_STEP(1500,0,30));
      CAR.V.VX=0;
      CAR.V.VY=0;	
			TRACK_CAR_CTOL(0,0,0,0,0,500);
			//PlatformControl(1,0,60);//平台上升回原位
			TRACK.STATE=STORE_OVER_BACK_ONLINE_2;
		}
		break;
		case STORE_OVER_BACK_ONLINE_2:
		{
      TRACK_CAR_CTOL(0,2,0,0,0,0);	
      while(!TRACK_GO_STEP(0,-3500,60));
      TRACK_CAR_CTOL(0,2,0,0,0,200);	
      S_ADJUST();								//调整完毕
			TRACK_CAR_CTOL(0,0,0,0,0,500);
      CAR.CUR_COR.X_COR=4;
      CAR.CUR_COR.Y_COR=2;
      TRACK.STATE=Bizhang;
		}
		break;
    case Bizhang:
    {
      //坐标法到达 6，2
      TRACK_COR_GO(6,2,6000,6000);
      if(TRACK.ARRIVE==ARRIVED)
      {
        TRACK_CAR_CTOL(0,2,0,0,0,200);
        S_ADJUST();								//调整完毕
			  TRACK_CAR_CTOL(0,0,0,0,0,500);
        TRACK.STATE=Bizhang_1;
      }
	  }
		break;
		   case Bizhang_1:
    {
    //转向180
			while(!TRACK_TURN_ANGLE(50,55));
      TRACK_CAR_CTOL(0,2,0,0,0,200);			
			S_ADJUST();								//调整完毕
			TRACK_CAR_CTOL(0,0,0,0,0,500);
			TRACK.STATE=Bizhang_2;	
	  }
		break;
		 case Bizhang_2:
    {
      TRACK_CAR_CTOL(0,0,0,2000,0,0);
      if(LASER.laser_value[0]<=200)
      {
			  TRACK_CAR_CTOL(0,0,0,0,0,6000);
        TRACK.STATE=Bizhang_3;
      }
	  }
		break;
				case Bizhang_3:
    {
      TRACK_CAR_CTOL(0,0,0,-2000,0,0);
      if(DIGITAL16_GRAY_1.digital16_gray_state.STATE.L12==1)
      {
			  TRACK_CAR_CTOL(0,2,0,0,0,200);
				S_ADJUST();								//调整完毕
			  TRACK_CAR_CTOL(0,0,0,0,0,500);
        TRACK.STATE=Bizhang_4;
      }
	  }
		break;
			case Bizhang_4:
    {
     //转向180
			while(!TRACK_TURN_ANGLE(50,55));
      TRACK_CAR_CTOL(0,2,0,0,0,200);			
			S_ADJUST();								//调整完毕
			TRACK_CAR_CTOL(0,0,0,0,0,500);
			TRACK.STATE=BACK;
	  }
		break;
		case BACK:
    {
      /*坐标法到达 6，6*/
      TRACK_COR_GO(6,6,6000,6000);
      if(TRACK.ARRIVE==ARRIVED)
      {
        TRACK_CAR_CTOL(0,2,0,0,0,200);
        S_ADJUST();								//调整完毕
			  TRACK_CAR_CTOL(0,0,0,0,0,500);
        TRACK.STATE=FINISH;
      }
	  }
		break;
		case FINISH:
    {
      while(!TRACK_GO_STEP(-2600,1700,68));
      TRACK_CAR_CTOL(0,0,0,0,0,0);
      TRACK.STATE=FINISH_2;
	  }
		break;
		/*结束*/
		case FINISH_2:
		{
		}
		break;
	}
}






	/*循迹总函数*/
void TRACK_MODULE(void)
{
    switch(TRACK.id)
    {
        case 1:
        {
            TRACK_MODULE_RED_RY();
        }
        break;
        case 2:
        {
            TRACK_MODULE_BLUE_BY();
        }
        break;
        case 3:
        {
            TRACK_MODULE_RED_YR();
        }
        break;
        case 4:
        {
            TRACK_MODULE_BLUE_YB();
        }
        break;
        case 5:
        {
            TRACK_MODULE_RED_RYR();
        }
        break;
        case 6:
        {
            TRACK_MODULE_BLUE_BYB();
        }
        break;
    }
}


/*到达目标坐标*/
//循环执行，赋值不变，判断现有位置然后判断可走路径
uint8_t TRACK_COR_GO(uint8_t x,uint8_t y,uint16_t vx,uint16_t vy)
{
    //标记是否是启程（第一次进入此函数）
//    static uint8_t i=0;
    //标记是否完成目标
    uint8_t ok=0;
        /*记录下目标坐标*/
        TRACK.FINAL_COR.X_COR=x;
        TRACK.FINAL_COR.Y_COR=y;
				/*记录下目标速度*/
	      TRACK.FINAL_V.VX=vx;
	      TRACK.FINAL_V.VY=vy;
        /*决定先走的方向*/
        //判断当前可供选择的方向
        TRACK_DIR_GO();
        //判断是否需要微调和进行微调
        while(!TRACK_POS_GO());
        //循迹（进行速度赋值）
        switch(TRACK.FINAL_DIR)
        {
            case Xplus_DIR:
            {
								CAR.COR_MODE=COR_UPDATE_MODE;
								CAR.DIR_MODE=DIR_RUN_MODE;
                CAR.V.VX=TRACK.FINAL_V.VX;
                CAR.V.VY=0;
                CAR.V.VW=0;
            }break;
            case Xminus_DIR:
            {
								CAR.COR_MODE=COR_UPDATE_MODE;
								CAR.DIR_MODE=DIR_RUN_MODE;
                CAR.V.VX=-TRACK.FINAL_V.VX;
                CAR.V.VY=0;
                CAR.V.VW=0;
            }break;
            case Yplus_DIR:
            {
								CAR.COR_MODE=COR_UPDATE_MODE;
								CAR.DIR_MODE=DIR_RUN_MODE;
                CAR.V.VX=0;
                CAR.V.VY=TRACK.FINAL_V.VY;
                CAR.V.VW=0;
            }break;
            case Yminus_DIR:
            {
								CAR.COR_MODE=COR_UPDATE_MODE;
								CAR.DIR_MODE=DIR_RUN_MODE;
                CAR.V.VX=0;
                CAR.V.VY=-TRACK.FINAL_V.VY;
                CAR.V.VW=0;
            }break;
            case NO_DIR:
            {
                CAR.V.VX=0;
                CAR.V.VY=0;
                CAR.V.VW=0;
            }break;
        }
				if(TRACK.ARRIVE==ARRIVED)
          ok=1;
	return ok;
}

/*方向转换调整*/
uint8_t TRACK_POS_GO(void)
{
    //标志位：是否完成位置调整
    uint8_t ok=0;
    //如果已经抵达目标坐标点了
    if(TRACK.FINAL_DIR==NO_DIR&&TRACK.ARRIVE==ARRIVED)
    {
        //进行静止位置调整
        CAR.COR_MODE=NO_COR_MODE;
        CAR.DIR_MODE=DIR_SILENCE_MODE;
        CAR.V_ADJUST.ok=0;
        //还未调整好时
				while(!SILENCE_ADJUST_OK());
        //调整好以后
        //标记调整好了
        ok=1;
        //接下来已到达目标坐标点了，出去后要进入某个新的状态中
    }
    //如果在XY方向间转换
    else if(((CAR.DIR==Xplus_DIR||CAR.DIR==Xminus_DIR)&&(TRACK.FINAL_DIR==Yplus_DIR||TRACK.FINAL_DIR==Yminus_DIR))||((CAR.LAST_DIR==Yplus_DIR||CAR.LAST_DIR==Yminus_DIR)&&(TRACK.FINAL_DIR==Xplus_DIR||TRACK.FINAL_DIR==Xminus_DIR)))
    {
        //进行静止位置调整
        CAR.COR_MODE=COR_UPDATE_MODE;
        CAR.DIR_MODE=DIR_SILENCE_MODE;
        CAR.V_ADJUST.ok=0;
        //还未调整好时
			while(!SILENCE_ADJUST_OK());
        //调整好以后
        //标记调整好了
        ok=1;
        //继续走
        CAR.COR_MODE=COR_UPDATE_MODE;
        CAR.DIR_MODE=DIR_RUN_MODE;
    }
    else
    {
        //继续走
        ok=1;
        //继续走
        CAR.COR_MODE=COR_UPDATE_MODE;
        CAR.DIR_MODE=DIR_RUN_MODE;
    }
    return ok;
}

uint8_t SILENCE_ADJUST_OK(void)
{
	uint8_t adjust_ok=0;
	if(CAR.V_ADJUST.ok==1)
	{
		adjust_ok=1;
	}
	return adjust_ok;
}

uint8_t PRECISE_ADJUST_OK(void)
{
	uint8_t adjust_ok=0;
	if(CAR.V_ADJUST.p_ok==1)
	{
		adjust_ok=1;
	}
	return adjust_ok;
}
void P_ADJUST(void)
{
	CAR.V_ADJUST.p_ok=0;
	uint16_t fuck11 = 0;
	while(!PRECISE_ADJUST_OK())
	if(fuck11++>=50000) break;
}
void S_ADJUST(void)
{
	CAR.V_ADJUST.ok=0;
	uint16_t fuck11 = 0;
	while(!SILENCE_ADJUST_OK())
	if(fuck11++>=50000) break;
}
uint8_t adjust(void)
{
	if(DIGITAL16_GRAY_4.digital16_gray_state.STATE.L2==1||DIGITAL16_GRAY_4.digital16_gray_state.STATE.L3==1||DIGITAL16_GRAY_4.digital16_gray_state.STATE.L4==1||DIGITAL16_GRAY_4.digital16_gray_state.STATE.L5==1||DIGITAL16_GRAY_4.digital16_gray_state.STATE.L6==1)
	{
		TRACK_CAR_CTOL(0,0,0,0,-30,0);
	}
		if(DIGITAL16_GRAY_4.digital16_gray_state.STATE.L10==1||DIGITAL16_GRAY_4.digital16_gray_state.STATE.L11==1||DIGITAL16_GRAY_4.digital16_gray_state.STATE.L12==1||DIGITAL16_GRAY_4.digital16_gray_state.STATE.L13==1||DIGITAL16_GRAY_4.digital16_gray_state.STATE.L14==1)
	{
		TRACK_CAR_CTOL(0,0,0,0,30,0);
	}
		if(DIGITAL16_GRAY_4.digital16_gray_state.STATE.L8==1&&DIGITAL16_GRAY_4.digital16_gray_state.STATE.L9==1)
	{
		TRACK_CAR_CTOL(0,0,0,0,0,0);
		return 1;
	}
	   else 
		 {
			 TRACK_CAR_CTOL(0,0,0,0,0,0);
			 return 0;
		 }
}	

/*计算最优方向*/
void TRACK_DIR_GO(void)
{
    //用于计数
    uint8_t i=0;
		//记录速度
		int16_t vx=TRACK.FINAL_V.VX;
	  int16_t vy=TRACK.FINAL_V.VY; 
	//清零方向待选位
	TRACK.maybe_dir[0]=TRACK.maybe_dir[1]=TRACK.maybe_dir[2]=TRACK.maybe_dir[3]=TRACK.maybe_dir[4]=0;
    //待选方向NO_DIR X+ Y+ X- Y-  1：不可选 0：可选
    //保存上一次的方向
    TRACK.LAST_FINAL_DIR=TRACK.FINAL_DIR;
	//初始方向
	 if(CAR.CUR_COR.X_COR==0||CAR.CUR_COR.X_COR==4)
	{
			TRACK.maybe_dir[1]=0;
	}
	if(CAR.CUR_COR.X_COR==2||CAR.CUR_COR.X_COR==6)
	{
		TRACK.maybe_dir[3]=0;
	}
	if(CAR.CUR_COR.Y_COR==6)
	{
		TRACK.maybe_dir[4]=0;
	}
		if(CAR.CUR_COR.Y_COR==0)
	{
		TRACK.maybe_dir[2]=0;
	}
    /* 通过坐标和位置过滤掉不可能的方向 */
    //如果当前x坐标为奇数
    if(CAR.CUR_COR.X_COR%2!=0)
    {
        //Y方向不可能
        TRACK.maybe_dir[2]=TRACK.maybe_dir[4]=1;
    }
    //如果当前y坐标为奇数
    else if(CAR.CUR_COR.Y_COR%2!=0)
    {
        //X方向不可能
        TRACK.maybe_dir[1]=TRACK.maybe_dir[3]=1;
    }
    //过滤掉处于边缘的位置
    switch(CAR.CUR_POS)
    { 
        case CENTER:
        {
        }break;
        case ON_X:
        {
            //Y方向不可能
            TRACK.maybe_dir[2]=TRACK.maybe_dir[4]=1;
        }break;
        case ON_Y:
        {
            //X方向不可能
            TRACK.maybe_dir[1]=TRACK.maybe_dir[3]=1;
        }break;
        case Xplus_CENTER:
        {
            //X+方向不可能
            TRACK.maybe_dir[1]=1;
        }break;
        case Xminus_CENTER:
        {
            //X-方向不可能
            TRACK.maybe_dir[3]=1;
        }break;
        case Yplus_CENTER:
        {
            //Y+方向不可能
            TRACK.maybe_dir[2]=1;
        }break;
        case Yminus_CENTER:
        {
            //Y-方向不可能
            TRACK.maybe_dir[4]=1;
        }break;
        case Q1_CENTER:
        {
            //X+Y+方向不可能
            TRACK.maybe_dir[1]=TRACK.maybe_dir[2]=1;
        }break;
        case Q2_CENTER:
        {
            //X-Y+方向不可能
            TRACK.maybe_dir[3]=TRACK.maybe_dir[2]=1;
        }break;
        case Q3_CENTER:
        {
            //X-Y-方向不可能
            TRACK.maybe_dir[3]=TRACK.maybe_dir[4]=1;            
        }break;
        case Q4_CENTER:
        {
            //X+Y-方向不可能
            TRACK.maybe_dir[1]=TRACK.maybe_dir[4]=1;
        }break;
    }
    /*过滤特殊坐标点*/ /*2020年改变了坐标*/
    //（2，6）
    if(CAR.CUR_COR.X_COR==2&&CAR.CUR_COR.Y_COR==6)
    {
        //不能X+Y+
        TRACK.maybe_dir[1]=TRACK.maybe_dir[2]=1;
    }
    //(4,6)
    else if(CAR.CUR_COR.X_COR==4&&CAR.CUR_COR.Y_COR==6)
    {
        //不能X-Y+
        TRACK.maybe_dir[3]=TRACK.maybe_dir[2]=1;
    }
    //(4,2)和（4,4）
    else if((CAR.CUR_COR.Y_COR==2||CAR.CUR_COR.Y_COR==4)&&(CAR.CUR_COR.X_COR==4))
    {
        //不能X-
        TRACK.maybe_dir[3]=1;
    }
    //(2.2)（2，4）
    else if((CAR.CUR_COR.Y_COR==2||CAR.CUR_COR.Y_COR==4)&&(CAR.CUR_COR.X_COR==2))
    {
        //不能X+
        TRACK.maybe_dir[1]=1;
    }
    //（2，0）
    else if((CAR.CUR_COR.Y_COR==0)&&(CAR.CUR_COR.X_COR==2))
    {
        //不能X+Y-
        TRACK.maybe_dir[1]=TRACK.maybe_dir[4]=1;
    }
		//（4，0）
    else if((CAR.CUR_COR.Y_COR==0)&&(CAR.CUR_COR.X_COR==4))
    {
        //不能X-Y-
        TRACK.maybe_dir[3]=TRACK.maybe_dir[4]=1;
    }
		//4 2
		    else if((CAR.CUR_COR.Y_COR==2)&&(CAR.CUR_COR.X_COR==4))
    {
        //不能y+
        TRACK.maybe_dir[2]=1;
    }
				//4 4
		    else if((CAR.CUR_COR.Y_COR==4)&&(CAR.CUR_COR.X_COR==4))
    {
        //不能y-
        TRACK.maybe_dir[4]=1;
    }

		/* else if(CAR.CUR_COR.X_COR==2&&CAR.CUR_COR.Y_COR==2&&TRACK.id==11)
    {
        //红方（2.2）不能X-Y- 会撞到已经回出发点的对方的车
        TRACK.maybe_dir[3]=TRACK.maybe_dir[4]=1;
    }
		
		else if(CAR.CUR_COR.X_COR==4&&CAR.CUR_COR.Y_COR==6)
		{
			  //不能Y+
        TRACK.maybe_dir[2]=1;
		}*/
		
 /*避障过滤可选方向*/
 //过滤XY方向上的可选方向
// ************************************************************************************************************************************//
//	if (CAR.CUR_COR.X_COR!=10)
//	{2020测试时屏蔽
// switch(LASER.barrier_state.laser_bar_xy)
//	 {
//     //X+方向有障碍物
//     case LASER_Xplus_BARRIER:
//     {
// 				  //记录下遇到障碍物时的那一刻方向
//					TRACK.BARRIER_DIR=CAR.DIR;                              //好像没有用处，其他语句没有出现过
//            //被动避障（反向避障策略）
//            TRACK.FINAL_V.VX=(TRACK.FINAL_V.VX/300)*(LASER.barrier_state.barrier_dis[0])-TRACK.FINAL_V.VX;
//     }
//		 break;
//		 
//     case LASER_Yminus_BARRIER:
//     {
//            //被动避障（反向避障策略）
//            TRACK.FINAL_V.VY=(TRACK.FINAL_V.VY/300)*(LASER.barrier_state.barrier_dis[3])-TRACK.FINAL_V.VY;
//     }
//		 break;
//		 
//     case LASER_Xminus_BARRIER:
//     {
//            //根据与障碍物之间的距离改变方向和速度
//            TRACK.FINAL_V.VX= (TRACK.FINAL_V.VX/300)*(LASER.barrier_state.barrier_dis[2])-TRACK.FINAL_V.VX;
//     }
//		 break;
//		 
//     case LASER_Yplus_BARRIER:
//     {
//            //根据与障碍物之间的距离改变方向和速度，如果距离过近，即小于30cm时采取反向避障的策略
//            TRACK.FINAL_V.VY= (TRACK.FINAL_V.VY/300)*(LASER.barrier_state.barrier_dis[1])-TRACK.FINAL_V.VY;
//     }
//		 break;
//     case NO_XYBARRIER:
//     {
//     }
//		 break;
// }
//}
	

 //*********************************************************************************************************************8
  //判断斜角方向上的障碍物避障
//	if (CAR.CUR_COR.X_COR!=10)
//	{2020测试时屏蔽
//     switch(LASER.barrier_state.laser_bar_quard)
//     {
//         //X+方向有障碍物
//         case LASER_QUADRANT1_BARRIER:
//         {
//							 if(TRACK.FINAL_DIR==Xplus_DIR)
//							 {
//								  //根据与障碍物之间的距离改变方向和速度
//									vx= (vx/200)*(LASER.barrier_state.barrier_dis[4])-(7/4)*vx;
//							 }
//							 	else if(TRACK.FINAL_DIR==Yplus_DIR&&CAR.CUR_COR.X_COR!=10)
//							 {
//								  //根据与障碍物之间的距离改变方向和速度
//									vy= (vy/200)*(LASER.barrier_state.barrier_dis[4])-(7/4)*vy;
//							 }
//         }break;
//         case LASER_QUADRANT4_BARRIER:
//         {
//							 if(TRACK.FINAL_DIR==Xplus_DIR)
//							 {
//								  //根据与障碍物之间的距离改变方向和速度
//									vx= (vx/200)*(LASER.barrier_state.barrier_dis[7])-(7/4)*vx;
//							 }
//							 	else if(TRACK.FINAL_DIR==Yminus_DIR&&CAR.CUR_COR.X_COR!=10)
//							 {
//								  //根据与障碍物之间的距离改变方向和速度
//									vy= (vy/200)*(LASER.barrier_state.barrier_dis[7])-(7/4)*vy;
//							 }
//         }break;
//         case LASER_QUADRANT3_BARRIER:
//         {
//							 if(TRACK.FINAL_DIR==Xminus_DIR)
//							 {
//								  //根据与障碍物之间的距离改变方向和速度
//									vx= (vx/200)*(LASER.barrier_state.barrier_dis[6])-(7/4)*vx;
//							 }
//							 	else if(TRACK.FINAL_DIR==Yminus_DIR)
//							 {
//								  //根据与障碍物之间的距离改变方向和速度
//									vy= (vy/200)*(LASER.barrier_state.barrier_dis[6])-(7/4)*vy;
//							 }
//         }break;
//         case LASER_QUADRANT2_BARRIER:
//         {
//							 if(TRACK.FINAL_DIR==Xminus_DIR)
//							 {
//								  //根据与障碍物之间的距离改变方向和速度
//									vx= (vx/200)*(LASER.barrier_state.barrier_dis[5])-(7/4)*vx;
//							 }
//							 	else if(TRACK.FINAL_DIR==Yplus_DIR&&CAR.CUR_COR.X_COR!=10)
//							 {
//								  //根据与障碍物之间的距离改变方向和速度
//									vy= (vy/200)*(LASER.barrier_state.barrier_dis[5])-(7/4)*vy;
//							 }
//         }break;
//         case NO_QBARRIER:
//         {
//         }break;
//     }
////	 }
//		 /*计算出最优避障速度*/
//		 if(vy<TRACK.FINAL_V.VY)
//		 {
//			 TRACK.FINAL_V.VY=vy;
//		 }
//		if(vx<TRACK.FINAL_V.VX)
//		{
//			TRACK.FINAL_V.VX=vx;
//		} 
		
     /*通过目标坐标和优先级顺序确定最优方向*/
     //先实现X坐标再实现Y坐标障碍会少
     //在区域一内

    /*确定方向优先级
    1.先满足X再满足Y
    */
    //清零方向优先级位
    for(i=0;i<5;i++)
    {
        TRACK.prior_dir[i]=0;
    }
    /*被动避障*/
    //判断方向优先级和是否到达
    if(TRACK.FINAL_COR.X_COR>CAR.CUR_COR.X_COR)
    {
        //最高优先级方向为X+
        TRACK.prior_dir[1]=1;
        TRACK.ARRIVE=NO_ARRIVE;
			   if(TRACK.FINAL_COR.Y_COR>CAR.CUR_COR.Y_COR)
        {
            //最高优先级方向为Y+
            TRACK.prior_dir[2]=2;
            TRACK.ARRIVE=NO_ARRIVE;
        }
        else if(TRACK.FINAL_COR.Y_COR<CAR.CUR_COR.Y_COR)
        {
            //最高优先级方向为Y-
            TRACK.prior_dir[2]=4;
            TRACK.ARRIVE=NO_ARRIVE;
        }
    }
    else if(TRACK.FINAL_COR.X_COR<CAR.CUR_COR.X_COR)
    {
        //最高优先级方向为X-
        TRACK.prior_dir[1]=3;
        TRACK.ARRIVE=NO_ARRIVE;
				if(TRACK.FINAL_COR.Y_COR>CAR.CUR_COR.Y_COR)
        {
            //最高优先级方向为Y+
            TRACK.prior_dir[2]=2;
            TRACK.ARRIVE=NO_ARRIVE;
        }
        else if(TRACK.FINAL_COR.Y_COR<CAR.CUR_COR.Y_COR)
        {
            //最高优先级方向为Y-
            TRACK.prior_dir[2]=4;
            TRACK.ARRIVE=NO_ARRIVE;
        }
    }
    else if(TRACK.FINAL_COR.X_COR==CAR.CUR_COR.X_COR)
    {
        if(TRACK.FINAL_COR.Y_COR>CAR.CUR_COR.Y_COR)
        {
            //最高优先级方向为Y+
            TRACK.prior_dir[1]=2;
            TRACK.ARRIVE=NO_ARRIVE;
        }
        else if(TRACK.FINAL_COR.Y_COR<CAR.CUR_COR.Y_COR)
        {
            //最高优先级方向为Y-
            TRACK.prior_dir[1]=4;
            TRACK.ARRIVE=NO_ARRIVE;
        }
        else
        {
            TRACK.ARRIVE=ARRIVED;
        }
    }

    /*综合可能坐标与坐标优先级确定最后方向*/
    if(TRACK.ARRIVE==ARRIVED)
    {
        TRACK.FINAL_DIR=NO_DIR;
    }
    else if(TRACK.maybe_dir[TRACK.prior_dir[1]]==0)
    {
			switch(TRACK.prior_dir[1])
			{
           case 0:
				{
					TRACK.FINAL_DIR=NO_DIR;
				}
				break;
				case 1:
				{
					TRACK.FINAL_DIR=Xplus_DIR;
				}
				break;
				case 2:
				{
					TRACK.FINAL_DIR=Yplus_DIR;
				}
				break;
					case 3:
				{
					TRACK.FINAL_DIR=Xminus_DIR;
				}
				break;
				case 4:
				{
					TRACK.FINAL_DIR=Yminus_DIR;
				}
				break;
			}		
			TRACK.ARRIVE=NO_ARRIVE;
    }
    else if(TRACK.maybe_dir[TRACK.prior_dir[2]]==0)
    {
       switch(TRACK.prior_dir[2])
			{
                case 0:
				{
					TRACK.FINAL_DIR=NO_DIR;
				}
				break;
				case 1:
				{
					TRACK.FINAL_DIR=Xplus_DIR;
				}
				break;
				case 2:
				{
					TRACK.FINAL_DIR=Yplus_DIR;
				}
				break;
					case 3:
				{
					TRACK.FINAL_DIR=Xminus_DIR;
				}
				break;
				case 4:
				{
					TRACK.FINAL_DIR=Yminus_DIR;
				}
				break;
			}		
			TRACK.ARRIVE=NO_ARRIVE;
    }
    else if(TRACK.maybe_dir[TRACK.prior_dir[3]]==0)
    {
      switch(TRACK.prior_dir[3])
			{
                case 0:
				{
					TRACK.FINAL_DIR=NO_DIR;
				}
				break;
				case 1:
				{
					TRACK.FINAL_DIR=Xplus_DIR;
				}
				break;
				case 2:
				{
					TRACK.FINAL_DIR=Yplus_DIR;
				}
				break;
					case 3:
				{
					TRACK.FINAL_DIR=Xminus_DIR;
				}
				break;
				case 4:
				{
					TRACK.FINAL_DIR=Yminus_DIR;
				}
				break;
			}		
			TRACK.ARRIVE=NO_ARRIVE;
    }
    else if(TRACK.maybe_dir[TRACK.prior_dir[4]]==0)
    {
      switch(TRACK.prior_dir[4])
			{
                case 0:
				{
					TRACK.FINAL_DIR=NO_DIR;
				}
				break;
				case 1:
				{
					TRACK.FINAL_DIR=Xplus_DIR;
				}
				break;
				case 2:
				{
					TRACK.FINAL_DIR=Yplus_DIR;
				}
				break;
					case 3:
				{
					TRACK.FINAL_DIR=Xminus_DIR;
				}
				break;
				case 4:
				{
					TRACK.FINAL_DIR=Yminus_DIR;
				}
				break;
			}		
			TRACK.ARRIVE=NO_ARRIVE;
    }
    else
    {
        TRACK.FINAL_DIR=NO_DIR;
    }
		if(TRACK.FINAL_COR.Y_COR==CAR.CUR_COR.Y_COR&&TRACK.FINAL_COR.X_COR==CAR.CUR_COR.X_COR)
		{
			TRACK.FINAL_DIR=NO_DIR;
			TRACK.ARRIVE=ARRIVED;
			TRACK.barrier_ok[0]=TRACK.barrier_ok[1]=TRACK.barrier_ok[2]=TRACK.barrier_ok[3]=0;
		}
}


/*循迹状态赋值:
cor_mode:
0-NO_COR_MODE
1-COR_UPDATE_MODE
dir_mode:
0-NO_DIR_MODE
1-DIR_RUN_MODE
2-DIR_SILENCE_MODE
*/
void TRACK_CAR_CTOL(uint8_t cor_mode,uint8_t dir_mode,int16_t vx,int16_t vy,int8_t vw,uint16_t ms)
{
    CAR.COR_MODE=cor_mode;
    CAR.DIR_MODE=dir_mode;
    CAR.V.VX=vx;
    CAR.V.VY=vy;
    CAR.V.VW=vw;
    HAL_Delay(ms);
}

void TRACK_LASER_CTOL()
{ 
//	if(LASER.laser_value[4]<150&&LASER.laser_value[4]>70&&LASER.laser_value[4]<160&&LASER.laser_value[4]>80)
//	{
    CAR.V.VX= - (8*((LASER.laser_value[4]-110)+(LASER.laser_value[5]-124)));
    CAR.V.VW= 0.5*((LASER.laser_value[4]-110)-(LASER.laser_value[5]-124));
//	}
//	else 
//	{
//	  CAR.V.VX= 0;
//    CAR.V.VW =0;
//	}
}


/*前进一段里程*/
uint8_t TRACK_GO_STEP(int16_t vx,int16_t vy,int16_t step)
{
    //用于计数第几次进入该函数
    static uint8_t Count=0;
    //用于记录是否完成指定目标
    uint8_t ok=0;
    if(Count==0)
    {
        /*设定车的基本参数*/
        //不更新坐标
        CAR.COR_MODE=NO_COR_MODE;
        //不进行方向校准
        CAR.DIR_MODE=NO_DIR_MODE;
        CAR.V.VX=vx;
        CAR.V.VY=vy;
        CAR.V.VW=0;
        T3_module_update.step=0;
				
    }
   Count=1;
    if(T3_module_update.step>=step)
    {
        CAR.V.VX=0;
        CAR.V.VY=0;
	    	CAR.V.VW=0;
        ok=1;
        Count=0;
    }
		else
			ok=0;
    return ok;
}

/*转动一定角度*/
/*
转动90度
v=100时 20ms:7度
转动180度
while(!TRACK_TURN_ANGLE(100,27));
*/
uint8_t TRACK_TURN_ANGLE(int16_t vw,int16_t angle)
{
    //用于计数第几次进入该函数
    static uint8_t i=0;
    //用于记录是否完成指定目标
    uint8_t ok=0;
    if(i==0)
    {
        /*设定车的基本参数*/
        //不更新坐标
        CAR.COR_MODE=NO_COR_MODE;
        //不进行方向校准
        CAR.DIR_MODE=NO_DIR_MODE;
        CAR.V.VX=0;
        CAR.V.VY=0;
        CAR.V.VW=vw;
        T3_module_update.angle=0;
    }
    i=1;
    if(T3_module_update.angle>=angle)
    {
			  CAR.V.VX=0;
        CAR.V.VY=0;
				CAR.V.VW=0;
        ok=1;
        i=0;
    }
    return ok;
}
	
/*运动信息发送函数_CAN1发送ID：0x100*/
void  TRACK_INSTRUCTION_TX(CAN_HandleTypeDef *hcan)
{
    static CAN_TxHeaderTypeDef M2006_HDR =
    {
        //A型主控给B型主控发送循迹指令的ID号
        0x400,
        0,
        CAN_ID_STD,
        CAN_RTR_DATA,
        8,
        DISABLE
    };	
    //header1
    CAN1_TXMSG.txdata[0]=((CAR.V.VX+CAR.V_ADJUST.VX)>>8)&0xff;
    //header2
    CAN1_TXMSG.txdata[1] =(CAR.V.VX+CAR.V_ADJUST.VX)&0xff;
    //所要采集的激光ID号
    CAN1_TXMSG.txdata[2] =((CAR.V.VY+CAR.V_ADJUST.VY)>>8)&0xff;
    //采集指令
    CAN1_TXMSG.txdata[3] =(CAR.V.VY+CAR.V_ADJUST.VY)&0xff;
    //校验和
    CAN1_TXMSG.txdata[4] =((CAR.V.VW+CAR.V_ADJUST.VW)>>8)&0xff;
    CAN1_TXMSG.txdata[5] = ((CAR.V.VW+CAR.V_ADJUST.VW))&0xff;
    CAN1_TXMSG.txdata[6] = 0;
    CAN1_TXMSG.txdata[7] = 0;
	HAL_CAN_AddTxMessage(hcan, &M2006_HDR, CAN1_TXMSG.txdata, &CAN1_TXMSG.txmailbox);
}

/*运动方向信息更新*/
void TRACK_DIR_UPDATE(void)
{
	  //保存上一个方向
		CAR.LAST_DIR=CAR.DIR;
    // //求速度绝对值大小
    // CAR.V.Vmagnitude=sqrt(CAR.V.VX*CAR.V.VX+CAR.V.VY*CAR.V.VY);
    //求速度大致方向
    if(((CAR.CUR_V.VX)!=0)||((CAR.CUR_V.VY)!=0))
    {
            if(abs(CAR.CUR_V.VX)>abs(CAR.CUR_V.VY))
            {
                if(CAR.CUR_V.VX>0)
                {
                    CAR.DIR=Xplus_DIR;
                }
                else
                {
                    CAR.DIR=Xminus_DIR;
                }
            }
            else if (abs(CAR.CUR_V.VX)<abs(CAR.CUR_V.VY))
            {
                if(CAR.CUR_V.VY>0)
                {
                    CAR.DIR=Yplus_DIR;
                }
                else
                {
                    CAR.DIR=Yminus_DIR;
                }
            }
					}
    else
    {
        CAR.DIR=NO_DIR;
    }
    // if(CAR.V.VX==0)
    // {
    //     if(CAR.V.VY==0)
    //     {
    //         CAR.DIR=NO_DIR;
    //     }
    //     else if(CAR.V.VY>0)
    //     {
    //         CAR.DIR=Yplus_DIR;
    //     }
    //     else if(CAR.V.VY<0)
    //     {
    //         CAR.DIR=Yminus_DIR;
    //     }
    // }
    // else if(CAR.V.VX>0)
    // {
    //     if(CAR.V.VY==0)
    //     {
    //         CAR.DIR=Xplus_DIR;
    //     }
    //     else if(CAR.V.VY>0)
    //     {
    //         CAR.DIR=Q1_DIR;
    //     }
    //     else if(CAR.V.VY<0)
    //     {
    //         CAR.DIR=Q4_DIR;
    //     }
    // }
    // else
    // {
    //     if(CAR.V.VY==0)
    //     {
    //         CAR.DIR= Xminus_DIR;
    //     }
    //     else if(CAR.V.VY>0)
    //     {
    //         CAR.DIR=Q2_DIR;
    //     }
    //     else if(CAR.V.VY<0)
    //     {
    //         CAR.DIR=Q3_DIR;
    //     }
    // }
    //求速度方向角度
    // switch(CAR.DIR)
    // {
    //     case NO_DIR:
    //     {
    //         CAR.V.angle=0;
    //     }
    //     break;
    //     case Xplus_DIR:
    //     {
    //         CAR.V.angle=0;
    //     }
    //     break;
    //     case Xminus_DIR:
    //     {
    //         CAR.V.angle=180;
    //     }
    //     break;
    //     case Yplus_DIR:
    //     {
    //         CAR.V.angle=90;
    //     }
    //     break;
    //     case Yminus_DIR:
    //     {
    //         CAR.V.angle=-90;
    //     }
    //     break;
    //     case Q1_DIR:
    //     {
    //         CAR.V.angle=atan(CAR.V.VY/CAR.V.VX)*180/3.1416;
    //     }
    //     break;
    //     case Q2_DIR:
    //     {
    //         CAR.V.angle=180-atan(CAR.V.VY/-CAR.V.VX)*180/3.1416;
    //     }
    //     break;
    //     case Q3_DIR:
    //     {
    //         CAR.V.angle=-180+atan(CAR.V.VY/CAR.V.VX)*180/3.1416;
    //     }
    //     break;
    //     case Q4_DIR:
    //     {
    //         CAR.V.angle=atan(CAR.V.VY/CAR.V.VX)*180/3.1416;
    //     }
    //     break;
    // }
}

/*位置更新函数*/
void TRACK_POS_UPDATE(void)
{
    //将上一次的值保存
    POS_GRAY_COUNT.last_pos_xplus=POS_GRAY_COUNT.pos_xplus;
    POS_GRAY_COUNT.last_pos_xminus=POS_GRAY_COUNT.pos_xminus;
    POS_GRAY_COUNT.last_pos_yplus=POS_GRAY_COUNT.pos_yplus;
    POS_GRAY_COUNT.last_pos_yminus=POS_GRAY_COUNT.pos_yminus;
    //记录每只阵列灰度上多少只灰度在白线上的数值
    POS_GRAY_COUNT.pos_xplus=GRAYx_FUNC_Linecount(DIGITAL16_GRAY_1);
    POS_GRAY_COUNT.pos_xminus=GRAYx_FUNC_Linecount(DIGITAL16_GRAY_3);
    POS_GRAY_COUNT.pos_yplus=GRAYx_FUNC_Linecount(DIGITAL16_GRAY_4);
    POS_GRAY_COUNT.pos_yminus=GRAYx_FUNC_Linecount(DIGITAL16_GRAY_2);

    //将上一次的位置信息进行存储
    CAR.LAST_POS=CAR.CUR_POS;

    if(POS_GRAY_COUNT.pos_xplus==0&&POS_GRAY_COUNT.pos_xminus==0&&POS_GRAY_COUNT.pos_yplus==0&&POS_GRAY_COUNT.pos_yminus==0)
    {
        CAR.CUR_POS=OUT;
    }
    else if(POS_GRAY_COUNT.pos_yplus==0&&POS_GRAY_COUNT.pos_yminus==0)
    {
        CAR.CUR_POS=ON_X;
    }
    else if(POS_GRAY_COUNT.pos_xplus==0&&POS_GRAY_COUNT.pos_xminus==0)
    {
        CAR.CUR_POS=ON_Y;
    }
    else if(POS_GRAY_COUNT.pos_xplus==0&&POS_GRAY_COUNT.pos_yplus==0)
    {
        CAR.CUR_POS=Q1_CENTER;
    }
    else if(POS_GRAY_COUNT.pos_xminus==0&&POS_GRAY_COUNT.pos_yplus==0)
    {
        CAR.CUR_POS=Q2_CENTER;
    }
    else if(POS_GRAY_COUNT.pos_xminus==0&&POS_GRAY_COUNT.pos_yminus==0)
    {
        CAR.CUR_POS=Q3_CENTER;
    }
    else if(POS_GRAY_COUNT.pos_xplus==0&&POS_GRAY_COUNT.pos_yminus==0)
    {
        CAR.CUR_POS=Q4_CENTER;
    }
    else if(POS_GRAY_COUNT.pos_xminus==0)
    {
        CAR.CUR_POS=Xminus_CENTER;
    }
    else if(POS_GRAY_COUNT.pos_xplus==0)
    {
        CAR.CUR_POS=Xplus_CENTER;
    }
    else if(POS_GRAY_COUNT.pos_yplus==0)
    {
        CAR.CUR_POS=Yplus_CENTER;
    }
    else if(POS_GRAY_COUNT.pos_yminus==0)
    {
        CAR.CUR_POS=Yminus_CENTER;
    }
    if(POS_GRAY_COUNT.pos_xplus!=0&&POS_GRAY_COUNT.pos_xminus!=0&&POS_GRAY_COUNT.pos_yplus!=0&&POS_GRAY_COUNT.pos_yminus!=0)
    {
        CAR.CUR_POS=CENTER;
    }
}



/*坐标信息更新函数*/
void TRACK_COR_UPDATE(void)
{
    //判断坐标模式有没有开启
    if(CAR.COR_MODE==COR_UPDATE_MODE)
    {
        //如果开启了，将上一次的坐标保存
        CAR.LAST_COR=CAR.CUR_COR;
			
			  //在更新坐标前，先更新一次方向
			  TRACK_DIR_UPDATE();
        //判断运动方向
        switch(CAR.LAST_DIR)
        {
            //如果没方向，则什么也不做
            case NO_DIR:
            {

            }break;
            //如果为X+方向
            case Xplus_DIR:
            {
                //判断上一次的位置
                switch(CAR.LAST_POS)
                {
                    //在中间的线上行走时
                    case Xminus_CENTER:
                    {
                        if(CAR.CUR_POS==ON_X)
                        {
                            CAR.CUR_COR.X_COR++;
                        }
                    }break;
                    case ON_X:
                    {
                        if(CAR.CUR_POS==CENTER)
                        {
                            CAR.CUR_COR.X_COR++;
                        }
                        else if(CAR.CUR_POS==Xplus_CENTER)
                        {
                            CAR.CUR_COR.X_COR++;
                        }
                        else if(CAR.CUR_POS==Yplus_CENTER)
                        {
                            CAR.CUR_COR.X_COR++;
                        }
                        else if(CAR.CUR_POS==Q1_CENTER)
                        {
                            CAR.CUR_COR.X_COR++;
                        }
                        else if(CAR.CUR_POS==Q4_CENTER)
                        {
                            CAR.CUR_COR.X_COR++;
                        }
                        else if(CAR.CUR_POS==Yminus_CENTER)
                        {
                            CAR.CUR_COR.X_COR++;
                        }
                    }break;
                    case CENTER:
                    {
                        if(CAR.CUR_POS==ON_X)
                        {
                            CAR.CUR_COR.X_COR++;
                        }
                    }break;
                    //在Y+边边的线上行走时
                    case Q2_CENTER:
                    {
                        if(CAR.CUR_POS==ON_X)
                        {
                            CAR.CUR_COR.X_COR++;
                        }
                    }break;
                    case Yplus_CENTER:
                    {
                        if(CAR.CUR_POS==ON_X)
                        {
                            CAR.CUR_COR.X_COR++;
                        }
                    }break;
                    //在Y-边边上行走时
                    case Q3_CENTER:
                    {
                        if(CAR.CUR_POS==ON_X)
                        {
                            CAR.CUR_COR.X_COR++;
                        }
                    }break;
                    case Yminus_CENTER:
                    {
                        if(CAR.CUR_POS==ON_X)
                        {
                            CAR.CUR_COR.X_COR++;
                        }
                    }break;
                }
            }break;
            //如果为X-方向
            case Xminus_DIR:
            {
                //判断上一次的位置
                switch(CAR.LAST_POS)
                {
                    case Xplus_CENTER:
                    {
                        if(CAR.CUR_POS==ON_X)
                        {
                            CAR.CUR_COR.X_COR--;
                        }
                    }break;
                    case ON_X:
                    {
                        if(CAR.CUR_POS==CENTER)
                        {
                            CAR.CUR_COR.X_COR--;
                        }
                        else if(CAR.CUR_POS==Xminus_CENTER)
                        {
                            CAR.CUR_COR.X_COR--;
                        }
                        else if(CAR.CUR_POS==Yminus_CENTER)
                        {
                            CAR.CUR_COR.X_COR--;
                        }
                        else if(CAR.CUR_POS==Q3_CENTER)
                        {
                            CAR.CUR_COR.X_COR--;
                        }
                        else if(CAR.CUR_POS==Yplus_CENTER)
                        {
                            CAR.CUR_COR.X_COR--;
                        }
                        else if(CAR.CUR_POS==Q2_CENTER)
                        {
                            CAR.CUR_COR.X_COR--;
                        }
                    }break;
                    case CENTER:
                    {
                        if(CAR.CUR_POS==ON_X)
                        {
                            CAR.CUR_COR.X_COR--;
                        }
                    }break;
                    //在Y-边边行走时
                    case Q4_CENTER:
                    {
                        if(CAR.CUR_POS==ON_X)
                        {
                            CAR.CUR_COR.X_COR--;
                        }
                    }break;
                    case Yminus_CENTER:
                    {
                        if(CAR.CUR_POS==ON_X)
                        {
                            CAR.CUR_COR.X_COR--;
                        }
                    }break;
                    //在Y+边边行走时
                    case Q1_CENTER:
                    {
                        if(CAR.CUR_POS==ON_X)
                        {
                            CAR.CUR_COR.X_COR--;
                        }
                    }break;
                    case Yplus_CENTER:
                    {
                        if(CAR.CUR_POS==ON_X)
                        {
                            CAR.CUR_COR.X_COR--;
                        }
                    }break;
                }
            }break;
            //如果为Y+方向
            case Yplus_DIR:
            {
                /*特殊情况：遇到蓝色和红色，影响灰度识别*/
                if(CAR.CUR_COR.X_COR==0)
                {
                    if(POS_GRAY_COUNT.last_pos_xplus==0&&POS_GRAY_COUNT.pos_xplus>0)
                    {
                        CAR.CUR_COR.Y_COR++;
                    }
                    else if(POS_GRAY_COUNT.last_pos_xplus>0&&POS_GRAY_COUNT.pos_xplus==0)
                    {
                        CAR.CUR_COR.Y_COR++;
                    }
                }
//                else if((CAR.CUR_COR.Y_COR<=1)&&(CAR.CUR_COR.X_COR==4||CAR.CUR_COR.X_COR==8))
//                {
//                    if(POS_GRAY_COUNT.last_pos_xplus==0&&POS_GRAY_COUNT.pos_xplus>0)
//                    {
//                        CAR.CUR_COR.Y_COR++;
//                    }
//                    else if(POS_GRAY_COUNT.last_pos_xplus>0&&POS_GRAY_COUNT.pos_xplus==0)
//                    {
//                        CAR.CUR_COR.Y_COR++;
//                    }
//                }
//                else if((CAR.CUR_COR.Y_COR<=1)&&(CAR.CUR_COR.X_COR==2||CAR.CUR_COR.X_COR==6))
//                {
//                    if(POS_GRAY_COUNT.last_pos_xminus==0&&POS_GRAY_COUNT.pos_xminus>0)
//                    {
//                        CAR.CUR_COR.Y_COR++;
//                    }
//                    else if(POS_GRAY_COUNT.last_pos_xminus>0&&POS_GRAY_COUNT.pos_xminus==0)
//                    {
//                        CAR.CUR_COR.Y_COR++;
//                    }
//                }
//                else if((CAR.CUR_COR.X_COR==2&&CAR.CUR_COR.Y_COR==7))
//                {
//                    if(POS_GRAY_COUNT.last_pos_xminus==0&&POS_GRAY_COUNT.pos_xminus>0)
//                    {
//                        CAR.CUR_COR.Y_COR++;
//                    }
//                }
//                else if((CAR.CUR_COR.X_COR==8&&CAR.CUR_COR.Y_COR==7))
//                {
//                    if(POS_GRAY_COUNT.last_pos_xplus==0&&POS_GRAY_COUNT.pos_xplus>0)
//                    {
//                        CAR.CUR_COR.Y_COR++;
//                    }
//                }
                else
                {
                    //判断上一次的位置
                    switch(CAR.LAST_POS)
                    {
                        //在中间的线上行走时
                        case Yminus_CENTER:
                        {
                            if(CAR.CUR_POS==ON_Y)
                            {
                                CAR.CUR_COR.Y_COR++;
                            }
                        }break;
                        case ON_Y:
                        {
                            if(CAR.CUR_POS==CENTER)
                            {
                                CAR.CUR_COR.Y_COR++;
                            }
                            else if(CAR.CUR_POS==Yplus_CENTER)
                            {
                                CAR.CUR_COR.Y_COR++;
                            }
                            else if(CAR.CUR_POS==Xplus_CENTER)
                            {
                                CAR.CUR_COR.Y_COR++;
                            }
                            else if(CAR.CUR_POS==Q2_CENTER)
                            {
                                CAR.CUR_COR.Y_COR++;
                            }
                            else if(CAR.CUR_POS==Q1_CENTER)
                            {
                                CAR.CUR_COR.Y_COR++;
                            }
                            else if(CAR.CUR_POS==Xminus_CENTER)
                            {
                                CAR.CUR_COR.Y_COR++;
                            }
                        }break;
                        case CENTER:
                        {
                            if(CAR.CUR_POS==ON_Y)
                            {
                                CAR.CUR_COR.Y_COR++;
                            }
                        }break;
                        //在Y+边边的线上行走时
                        case Q4_CENTER:
                        {
                            if(CAR.CUR_POS==ON_Y)
                            {
                                CAR.CUR_COR.Y_COR++;
                            }
                        }break;
                        case Xplus_CENTER:
                        {
                            if(CAR.CUR_POS==ON_Y)
                            {
                                CAR.CUR_COR.Y_COR++;
                            }
                        }break;
                        //在Y-边边上行走时
                        case Q3_CENTER:
                        {
                            if(CAR.CUR_POS==ON_Y)
                            {
                                CAR.CUR_COR.Y_COR++;
                            }
                        }break;
                        case Xminus_CENTER:
                        {
                            if(CAR.CUR_POS==ON_Y)
                            {
                                CAR.CUR_COR.Y_COR++;
                            }
                        }break;
                    }
                }
                
            }break;
            case Yminus_DIR:
            {
                /*特殊情况：遇到蓝色和红色，影响灰度识别*/
                if(CAR.CUR_COR.X_COR==0)
                {
                    if(POS_GRAY_COUNT.last_pos_xplus==0&&POS_GRAY_COUNT.pos_xplus>0)
                    {
                        CAR.CUR_COR.Y_COR--;
                    }
                    else if(POS_GRAY_COUNT.last_pos_xplus>0&&POS_GRAY_COUNT.pos_xplus==0)
                    {
                        CAR.CUR_COR.Y_COR--;
                    }
                }
//                else if((CAR.CUR_COR.Y_COR<=1)&&(CAR.CUR_COR.X_COR==4||CAR.CUR_COR.X_COR==8))
//                {
//                    if(POS_GRAY_COUNT.last_pos_xplus==0&&POS_GRAY_COUNT.pos_xplus>0)
//                    {
//                        CAR.CUR_COR.Y_COR--;
//                    }
//                }
//                else if((CAR.CUR_COR.Y_COR<=1)&&(CAR.CUR_COR.X_COR==2||CAR.CUR_COR.X_COR==6))
//                {
//                    if(POS_GRAY_COUNT.last_pos_xminus==0&&POS_GRAY_COUNT.pos_xminus>0)
//                    {
//                        CAR.CUR_COR.Y_COR--;
//                    }
//                }
//                else if((CAR.CUR_COR.Y_COR>=7)&&(CAR.CUR_COR.X_COR==8))
//                {
//                    if(POS_GRAY_COUNT.last_pos_xplus==0&&POS_GRAY_COUNT.pos_xplus>0)
//                    {
//                        CAR.CUR_COR.Y_COR--;
//                    }
//                    else if(POS_GRAY_COUNT.last_pos_xplus>0&&POS_GRAY_COUNT.pos_xplus==0)
//                    {
//                        CAR.CUR_COR.Y_COR--;
//                    }
//                }
//                else if((CAR.CUR_COR.Y_COR>=7)&&(CAR.CUR_COR.X_COR==2))
//                {
//                    if(POS_GRAY_COUNT.last_pos_xminus==0&&POS_GRAY_COUNT.pos_xminus>0)
//                    {
//                        CAR.CUR_COR.Y_COR--;
//                    }
//                    else if(POS_GRAY_COUNT.last_pos_xminus>0&&POS_GRAY_COUNT.pos_xminus==0)
//                    {
//                        CAR.CUR_COR.Y_COR--;
//                    }
//                }
                else
                {
                    //判断上一次的位置
                    switch(CAR.LAST_POS)
                    {
                        case Yplus_CENTER:
                        {
                            if(CAR.CUR_POS==ON_Y)
                            {
                                CAR.CUR_COR.Y_COR--;
                            }
                        }break;
                        case ON_Y:
                        {
                            if(CAR.CUR_POS==CENTER)
                            {
                                CAR.CUR_COR.Y_COR--;
                            }
                            else if(CAR.CUR_POS==Yminus_CENTER)
                            {
                                CAR.CUR_COR.Y_COR--;
                            }
                            else if(CAR.CUR_POS==Xminus_CENTER)
                            {
                                CAR.CUR_COR.Y_COR--;
                            }
                            else if(CAR.CUR_POS==Q3_CENTER)
                            {
                                CAR.CUR_COR.Y_COR--;
                            }
                            else if(CAR.CUR_POS==Xplus_CENTER)
                            {
                                CAR.CUR_COR.Y_COR--;
                            }
                            else if(CAR.CUR_POS==Q4_CENTER)
                            {
                                CAR.CUR_COR.Y_COR--;
                            }
                        }break;
                        case CENTER:
                        {
                            if(CAR.CUR_POS==ON_Y)
                            {
                                CAR.CUR_COR.Y_COR--;
                            }
                        }break;
                        //在Y-边边行走时
                        case Q1_CENTER:
                        {
                            if(CAR.CUR_POS==ON_Y)
                            {
                                CAR.CUR_COR.Y_COR--;
                            }
                        }break;
                        case Xminus_CENTER:
                        {
                            if(CAR.CUR_POS==ON_Y)
                            {
                                CAR.CUR_COR.Y_COR--;
                            }
                        }break;
                        //在Y+边边行走时
                        case Q2_CENTER:
                        {
                            if(CAR.CUR_POS==ON_Y)
                            {
                                CAR.CUR_COR.Y_COR--;
                            }
                        }break;
                        case Xplus_CENTER:
                        {
                            if(CAR.CUR_POS==ON_Y)
                            {
                                CAR.CUR_COR.Y_COR--;
                            }
                        }break;
                    }
                }break;
            }
        }
    }
}




/*位置调整函数*/
void TRACK_POS_ADJUST(void)
{
    float kx=95,ky=95,kw=1.3;
    CAR.V_ADJUST.VW=0;
    float xd=GRAY_DIR.X_DIR_DISTANCE;
    float yd=GRAY_DIR.Y_DIR_DISTANCE;
    float xw=GRAY_DIR.X_DIR_ANGLE;
    float yw=GRAY_DIR.Y_DIR_ANGLE;
    //排除在边沿时的干扰
    if(GRAYx_FUNC_Linecount(DIGITAL16_GRAY_1)==0||GRAYx_FUNC_Linecount(DIGITAL16_GRAY_3)==0)
    {
        xd=0;
        xw=0;
    }
    if(GRAYx_FUNC_Linecount(DIGITAL16_GRAY_2)==0||GRAYx_FUNC_Linecount(DIGITAL16_GRAY_4)==0)
    {
        yd=0;
        yw=0;
    }
    switch(CAR.DIR_MODE)
    {
        //如果不允许进行位置调整，则什么也不做
        case NO_DIR_MODE:
        {
            CAR.V_ADJUST.VX=0;
            CAR.V_ADJUST.VY=0;
            CAR.V_ADJUST.VW=0;
        }
        break;
        //如果是在行进过程中要进行位置调整
        case DIR_RUN_MODE:
        {
            //忽略掉特殊情况
            if(CAR.CUR_COR.X_COR==0&&CAR.CUR_COR.Y_COR>=3&&CAR.CUR_COR.Y_COR<=5)
            {
                CAR.V_ADJUST.VX=0;
                CAR.V_ADJUST.VY=0;
                CAR.V_ADJUST.VW=0;
            }
            else
            {
                if(CAR.DIR==Xplus_DIR||CAR.DIR==Xminus_DIR&&GRAYx_FUNC_Linecount(DIGITAL16_GRAY_1)<5&&GRAYx_FUNC_Linecount(DIGITAL16_GRAY_3)<5)
                {
                    CAR.V_ADJUST.VX=0;
                    if(xd<0)
                        CAR.V_ADJUST.VY=-kx*xd*xd;
                    else
                    CAR.V_ADJUST.VY=kx*xd*xd;
                    CAR.V_ADJUST.VW=-kw*xw;
                }
                else if(CAR.DIR==Yplus_DIR||CAR.DIR==Yminus_DIR&&GRAYx_FUNC_Linecount(DIGITAL16_GRAY_2)<5&&GRAYx_FUNC_Linecount(DIGITAL16_GRAY_4)<5)
                {
                    CAR.V_ADJUST.VY=0;
                    if(yd<0)
                        CAR.V_ADJUST.VX=ky*yd*yd;
                    else
                        CAR.V_ADJUST.VX=-ky*yd*yd;
                        CAR.V_ADJUST.VW=-kw*yw;
                }
                //无方向=静止的时候，不赋值
                else
                {
                    CAR.V_ADJUST.VX=0;
                    CAR.V_ADJUST.VY=0;
                    CAR.V_ADJUST.VW=0;
                }
            }
        }
        break;
        //静止时的位置调整
        case DIR_SILENCE_MODE:
        {
            CAR.V.VX=0;
            CAR.V.VY=0;
            CAR.V.VW=0;
            //忽略掉特殊情况
            if(CAR.CUR_COR.X_COR==0&&CAR.CUR_COR.Y_COR>=3&&CAR.CUR_COR.Y_COR<=5)
            {
                CAR.V_ADJUST.VX=0;
                CAR.V_ADJUST.VY=0;
                CAR.V_ADJUST.VW=0;
            }
//						else if((CAR.CUR_COR.X_COR==2||CAR.CUR_COR.X_COR==6)&&CAR.CUR_COR.Y_COR==0)
//						{
//							          CAR.V_ADJUST.VX=4*kx*(GRAYx_FUNC_POS(DIGITAL16_GRAY_4)-8.5);
//                        CAR.V_ADJUST.VY=4*ky*(GRAYx_FUNC_POS(DIGITAL16_GRAY_3)-8.5);
//                        CAR.V_ADJUST.VW=0;

//						}
//						else if((CAR.CUR_COR.X_COR==4||CAR.CUR_COR.X_COR==8)&&CAR.CUR_COR.Y_COR==0)
//						{
//                        CAR.V_ADJUST.VX=4*kx*(GRAYx_FUNC_POS(DIGITAL16_GRAY_4)-8.5);
//                        CAR.V_ADJUST.VY=4*ky*(8.5-GRAYx_FUNC_POS(DIGITAL16_GRAY_1));
//                        CAR.V_ADJUST.VW=0;			

//						}
//						else if((CAR.CUR_COR.X_COR==2)&&CAR.CUR_COR.Y_COR==8)
//						{
//                        CAR.V_ADJUST.VX=4*kx*(8.5-GRAYx_FUNC_POS(DIGITAL16_GRAY_2));
//                        CAR.V_ADJUST.VY=4*ky*(GRAYx_FUNC_POS(DIGITAL16_GRAY_3)-8.5);
//                        CAR.V_ADJUST.VW=0;			

//						}
//						else if((CAR.CUR_COR.X_COR==8)&&CAR.CUR_COR.Y_COR==8)
//						{
//                        CAR.V_ADJUST.VX=4*kx*(8.5-GRAYx_FUNC_POS(DIGITAL16_GRAY_2));
//                        CAR.V_ADJUST.VY=4*ky*(8.5-GRAYx_FUNC_POS(DIGITAL16_GRAY_1));
//                        CAR.V_ADJUST.VW=0;

//						}
            else 
            {
                switch(CAR.CUR_POS)
                {
                    case CENTER:
                    {
                        CAR.V_ADJUST.VY=2*ky*(GRAYx_FUNC_POS(DIGITAL16_GRAY_3)-GRAYx_FUNC_POS(DIGITAL16_GRAY_1));
                        CAR.V_ADJUST.VX=2*kx*(GRAYx_FUNC_POS(DIGITAL16_GRAY_4)-GRAYx_FUNC_POS(DIGITAL16_GRAY_2));
                        CAR.V_ADJUST.VW=-kw*xw;
                    }break;
                    case ON_X:
                    {
                        CAR.V_ADJUST.VX=0;
                        if(xd<0)
                            CAR.V_ADJUST.VY=-kx*xd*xd;
                        else
                            CAR.V_ADJUST.VY=kx*xd*xd;
                        CAR.V_ADJUST.VW=-kw*xw;
                    }break;
                    case ON_Y:
                    {
                        CAR.V_ADJUST.VY=0;
                        if(yd<0)
                            CAR.V_ADJUST.VX=ky*yd*yd;
                        else
                            CAR.V_ADJUST.VX=-ky*yd*yd;
                        CAR.V_ADJUST.VW=-kw*yw;
                    }break;
                    case Xplus_CENTER:
                    {
                        CAR.V_ADJUST.VY=4*ky*(GRAYx_FUNC_POS(DIGITAL16_GRAY_3)-8.5);
                        CAR.V_ADJUST.VX=2*kx*(GRAYx_FUNC_POS(DIGITAL16_GRAY_4)-GRAYx_FUNC_POS(DIGITAL16_GRAY_2));
                        CAR.V_ADJUST.VW=-kw*yw;
                    }break;
                    case Xminus_CENTER:
                    {
                        CAR.V_ADJUST.VY=4*ky*(8.5-GRAYx_FUNC_POS(DIGITAL16_GRAY_1));
                        CAR.V_ADJUST.VX=2*kx*(GRAYx_FUNC_POS(DIGITAL16_GRAY_4)-GRAYx_FUNC_POS(DIGITAL16_GRAY_2));
                        CAR.V_ADJUST.VW=-kw*yw;
                    }break;
                    case Yplus_CENTER:
                    {
                        CAR.V_ADJUST.VX=4*kx*(8.5-GRAYx_FUNC_POS(DIGITAL16_GRAY_2));
                        CAR.V_ADJUST.VY=2*ky*(GRAYx_FUNC_POS(DIGITAL16_GRAY_3)-GRAYx_FUNC_POS(DIGITAL16_GRAY_1));
                        CAR.V_ADJUST.VW=-kw*xw;
                    }break;
                    case Yminus_CENTER:
                    {
                        CAR.V_ADJUST.VX=4*kx*(GRAYx_FUNC_POS(DIGITAL16_GRAY_4)-8.5);
                        CAR.V_ADJUST.VY=2*ky*(GRAYx_FUNC_POS(DIGITAL16_GRAY_3)-GRAYx_FUNC_POS(DIGITAL16_GRAY_1));
                        CAR.V_ADJUST.VW=-kw*xw;
                    }break;
                    case Q1_CENTER:
                    {
                        CAR.V_ADJUST.VX=4*kx*(8.5-GRAYx_FUNC_POS(DIGITAL16_GRAY_2));
                        CAR.V_ADJUST.VY=4*ky*(GRAYx_FUNC_POS(DIGITAL16_GRAY_3)-8.5);
                        CAR.V_ADJUST.VW=0;
                    }break;
                    case Q2_CENTER:
                    {
                        CAR.V_ADJUST.VX=4*kx*(8.5-GRAYx_FUNC_POS(DIGITAL16_GRAY_2));
                        CAR.V_ADJUST.VY=4*ky*(8.5-GRAYx_FUNC_POS(DIGITAL16_GRAY_1));
                        CAR.V_ADJUST.VW=0;
                    }break;
                    case Q3_CENTER:
                    {
                        CAR.V_ADJUST.VX=4*kx*(GRAYx_FUNC_POS(DIGITAL16_GRAY_4)-8.5);
                        CAR.V_ADJUST.VY=4*ky*(8.5-GRAYx_FUNC_POS(DIGITAL16_GRAY_1));
                        CAR.V_ADJUST.VW=0;
                    }break;
                    case Q4_CENTER:
                    {
                        CAR.V_ADJUST.VX=4*kx*(GRAYx_FUNC_POS(DIGITAL16_GRAY_4)-8.5);
                        CAR.V_ADJUST.VY=4*ky*(GRAYx_FUNC_POS(DIGITAL16_GRAY_3)-8.5);
                        CAR.V_ADJUST.VW=0;
                    }break;
                }

            }
				//判断是否完成位置调整
                if(abs(CAR.V_ADJUST.VX)<=150&&abs(CAR.V_ADJUST.VY)<=150&&abs(CAR.V_ADJUST.VW)<=5)
                {
                        CAR.V_ADJUST.ok=1;
                }
                else
                {
                        CAR.V_ADJUST.ok=0;
                }
                if(abs(CAR.V_ADJUST.VX)<=30&&abs(CAR.V_ADJUST.VY)<=30&&abs(CAR.V_ADJUST.VW)<=2)
                {
                        CAR.V_ADJUST.p_ok=1;
                }
                else
                {
                        CAR.V_ADJUST.p_ok=0;
                }
        }
        break;
    }
}

/*循迹在被逼无奈的特殊情况下*/
void TRACK_BARRIER_COR_GO(void)
{
	if(TRACK.FINAL_DIR==Yminus_DIR&&(LASER.barrier_state.laser_bar_xy==LASER_Yminus_BARRIER||LASER.barrier_state.laser_bar_quard==LASER_QUADRANT3_BARRIER||LASER.barrier_state.laser_bar_quard==LASER_QUADRANT4_BARRIER))
	{
		if(CAR.CUR_COR.Y_COR==6&&CAR.CUR_COR.X_COR==4)
		{
			while(!TRACK_COR_GO(2,4,7000,7000));
		}
		else if(CAR.CUR_COR.Y_COR==4&&CAR.CUR_COR.X_COR==4)
		{
			while(!TRACK_COR_GO(2,2,7000,7000));
		}
		else if(CAR.CUR_COR.Y_COR==6&&CAR.CUR_COR.X_COR==6)
		{
			while(!TRACK_COR_GO(8,4,7000,7000));
		}
	}
}

