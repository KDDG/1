#include"UPLib\\UP_System.h"
#define hdEdge1          //灰度传感器1边缘检测数值 
#define hdEdge2          //灰度传感器2边缘检测数值
#define hdEdge3          //灰度传感器3边缘检测数值
#define hdDown1          //灰度传感器1台下检测数值
#define hdDown2          //灰度传感器2台下检测数值
#define hdDown3          //灰度传感器3台下检测数值
#define rightDJ  3       //左舵机号
#define leftDJ   6       //右舵机号
#define djUP4    440    //舵机3抬起
#define djUP5    682       //舵机6抬起
#define djDown4  991     //舵机3下降
#define djDown5  130    //舵机6下降
#define speedM   1000    //最大冲刺速度    
#define speedN   600     //行驶速度
#define speedR   900     //冲撞
#define speedm   500     //最小速度

int AD1 = 0;		//灰度1
int AD2 = 0;		//灰度2
int AD3 = 0;		//灰度3

int AD4 = 2000;		//
int AD5 = 2001;		//前红外测距传感器
int AD6 = 2001;		//右红外测距传感器
int AD7 = 2001;		//后红外测距传感器
int AD8 = 2001;		//左红外测距传感器
int AD9 = 2001;		//
int AD10 = 2001;		//
int AD11 = 2001;		//
int AD12 = 2001;		//
int AD13 = 2001;   //

int nStage = 0;	//检测在台上还是在台下
int nEdge = 0;	//边缘
int nEnemy = 0;	//敌人
int nFence = 0;	//台下状态

int Qian = 0;		//前有无敌人
int You = 0;		//有有无敌人
int Hou = 0;		//后有无敌人
int Zuo = 0;		//左有无敌人
int Summ = 0;	//前后左右几个检测到		
int left = 0;
int right = 0;

int na = 0;     //倾斜计时
int nb = 0;			//推箱子计时
int nc = 8;			//旋转计时
int nd = 0;			//前搁浅计时
int ne = 8;			//后搁浅计时
  
void zhong()    //上台默认动作
{
	UP_CDS_SetAngle(5, 384, 800);
	UP_CDS_SetAngle(6, 640, 800);
	UP_CDS_SetAngle(7, 640, 800);
	UP_CDS_SetAngle(8, 384, 800);
}
//
void qding()  //收前爪
{
	UP_CDS_SetAngle(5, 1000, 800);
	UP_CDS_SetAngle(6, 24, 800);
	UP_delay_ms(10);
	UP_CDS_SetAngle(5, 1000, 800);
	UP_CDS_SetAngle(6, 24, 800);
}
//
void chanzi()  //上台后铲子状态
{
	UP_CDS_SetAngle(5, 780, 800);
	UP_CDS_SetAngle(6, 244, 800);
	UP_CDS_SetAngle(7, 244, 800);
	UP_CDS_SetAngle(8, 780, 800);
}
//
void move(int leftforward,int rightforward) //移动函数
{
	left = leftforward;
	right = rightforward;
	if(left > 1023)
	{
		left = 1023;
	}
	if(left < -1023)
	{
		left = -1023;
	}
	if(right > 1023)
	{
		right = 1023;
	}
	if(right < -1023)
	{
		right = -1023;
	}
	UP_CDS_SetSpeed(1, left);
	UP_CDS_SetSpeed(2, right);
}
//
unsigned char Fence()//在台下检测朝向
{
	 AD4=UP_ADC_GetValue(4); //下 后
	 AD5=UP_ADC_GetValue(5); //上 后
	 AD6=UP_ADC_GetValue(6); //下 前
	 AD7=UP_ADC_GetValue(7); //上 前
	 AD8=UP_ADC_GetValue(8); //下 右
	 AD9=UP_ADC_GetValue(9); //下 左
	 
	  /*正对着台*/
	  if(AD4<1000&&AD5<1000&&AD6<1000&&AD7>1000&&AD8>1000&&AD9>1000)
		{
			 return 0;
    }
		
	  /*背对着台*/
		else if(AD4<1000&&AD6<1000&&AD7<1000&&AD5>1000&&AD8>1000&&AD9>1000)
		{
			 return 1;	
		}
		
		/*侧对着台*/
		else if(AD8<1000&&AD9<1000)
		{
			return 2;			
		}
		
		/*左后角*/
	  else if(AD9<1000&&AD4<1000&&AD5<1000)
		{
			return 3;
		}
		
		/*右后角*/
		else if(AD8<1000&&AD4<1000&&AD5<1000)
		{
			return 4;
		}
		
		/*左前角*/
		else if(AD9<1000&&AD6<1000&&AD7<1000)
		{
			return 5;
		}
		
		/*右前角*/
		else if(AD8<1000&&AD6<1000&&AD7<1000)
		{
			return 6;
		}
		
		/*其他*/
		else 
		{
			return 7; //unknow
		}
		
}
//
unsigned char Edge()  //检测边缘
{
	int g1=2865;          //2880
	int g2=3080;          //3072
	int g3=1500;          //1580
	
	AD1=UP_ADC_GetValue(1);
	AD2=UP_ADC_GetValue(2);
	AD3=UP_ADC_GetValue(3);
  //方案1
	if(AD1>g1&&AD2>g2){
		return 0;    //在里面
	}else if(AD1<g1&&AD2>g2){
		  if(AD3<1520)
		      return 1;    //1在外面
			else if(AD3>=1520)
				  return 4;
	}else if(AD1>g1&&AD2<g2){
		  if(AD3<1520)
		     return 2;    //2在外面
			else if(AD3>=1520)
				 return 4;
	}else if(AD1<g1&&AD2<g2){
			if(AD3>=1520){
				return 4; //朝里面
			}else if(AD3<1520){
				if(AD1>2820&&AD2>3040){
		   		return 3;  //朝外面
				}else if(AD1<2820||AD2<3040){
					return 5;  //朝里面
				}else{
				  return 5;
				}
			}
	}else 
	  return 6;
	//方案2
  /*
	if(AD1>g1&&AD2>g2&&AD3>g3)
		return 0;  //在中间
	else if(AD1<g1&&AD2>g2&&AD3>g3)
		return 1;  //1在外面
	else if(AD1>g1&&AD2<g2&&AD3>g3)
		return 2;  //2在外面
	else if(AD1>g1&&AD2>g2&&AD3<g3)
		return 3;  //3在外面
	else if(AD1<g1&&AD2<g2&&AD3>g3)
		return 4;  //1,2
	else if(AD1<g1&&AD2>g2&&AD3<g3)
		return 5;  //1,3
	else if(AD1>g1&&AD2<g2&&AD3<g3)
		return 6;  //2,3
	else if(AD1<2673&&AD2<2697&&AD3<855)
		return 8;  //角落正方向
	else if(AD1<2629&&AD2<2620&&AD3<1013)
		return 9;  //角落负方向
	else
		return 7;  //其他
	*/
}
//
unsigned char Enemy()   //检测敌人
 {
	AD4 = UP_ADC_GetValue(4); //后
	AD7 = UP_ADC_GetValue(7); //前红外测距传感器
	AD8 = UP_ADC_GetValue(8); //右
	AD9 = UP_ADC_GetValue(9); //左
	AD10= UP_ADC_GetValue(10); //前左
	AD11= UP_ADC_GetValue(11); //前右
	AD12= UP_ADC_GetValue(12); //后右
	AD13= UP_ADC_GetValue(13); //后左
	if(AD7<1000)
		return 1; //前方检测到
	else if(AD4<1000)
		return 2; //后边检测到
	else if(AD9<1000)
		return 3;  //左
	else if(AD8<1000)
		return 4;  //右
	else if(AD10<1000&&AD7>1000)
		return 5;  //前左
	else if(AD11<1000&&AD7>1000)
		return 6;  //前右
	else if(AD12<1000)
		return 7;  //后右
	else if(AD13<1000)
		return 8; //后左前方检测到
  else 
		return 9; //unknow
	
	/*
	*/
}



//
unsigned char Stage()//是否在台上
{
	int b1,b2,b3;
	AD1=UP_ADC_GetValue(1);
	AD2=UP_ADC_GetValue(2);
	AD3=UP_ADC_GetValue(3); 
	b1=2360;
	b2=2530;
	b3=930;
	if(AD1<b1||AD2<b2||AD3<b3)
	  return 0;
	else 
	  return 1;
}  
//
void TimerHadler0(u32 timerchannel) //定义Timer中断入口函数
{
	
   //g_Timer0Count++;              //相应的变量加1
	 nStage=Stage();
	 if(nStage==0)
	   nFence=Fence();
	 else if(nStage==1){
		 nEdge=Edge();
	   nEnemy=Enemy();
	 }
}



//
int main()  //主函数
{  
	//计时器初始设置
	UP_Timer_EnableIT(TIMER_CHANNEL0, 2);       //使能计时器0，计时时间20us
  UP_Timer_SetHadler(TIMER_CHANNEL0, TimerHadler0);//传递计时器0的中断入口函数指针

	/*外部中断检测上台	
	UP_Exti_EnableIT(EXTI_AD4, EXTI_Trigger_Falling);  
  UP_Exti_SetHadler(UP_ExtiHadler1);
*/	
	
	//系统初始化
	UP_System_Init();
	UP_CDS_SetMode(3,CDS_SEVMODE);
	UP_CDS_SetMode(6,CDS_SEVMODE);
 
	//UP_CDS_SetAngle(4,djUP4,800);
	//UP_CDS_SetAngle(5,djUP5,800);
	
	while(1){
		
		AD7=UP_ADC_GetIO(7);
		AD5=UP_ADC_GetIO(5);
		UP_LCD_ShowInt(0,2,AD7);
		UP_LCD_ShowInt(0,3,AD5);
	  if(AD7==1&&AD5==0){
			move(speedM,speedM);
			UP_delay_ms(950);
			break;
		}
	}
	
	while(1)
	{ 
		//UP_LCD_ClearScreen();
		
		
		UP_LCD_ShowInt(0,2,AD1);
		UP_LCD_ShowInt(6,2,AD2);
		UP_LCD_ShowInt(3,0,AD3);
		
		if(nStage==0){
		  UP_LCD_ShowInt(0,3,nStage);
		  UP_LCD_ShowInt(3,3,nFence);
		}else if(nStage==1){
		  UP_LCD_ShowInt(5,3,nEdge);
      UP_LCD_ShowInt(8,3,nEnemy);
		}		
		
	 if(nStage==0){
		UP_CDS_SetAngle(4,djUP4,1000);
	  UP_CDS_SetAngle(5,djUP5,1000);
		 
		if(nFence==0)
		{
			move(-speedR,-speedR);
			UP_delay_ms(400);
			move(speedM,speedM);
			UP_delay_ms(1300);
		} 
		else if(nFence==1)
		{
		//	move(speedN,speedN);
		//	UP_delay_ms(500);
			move(650,-650);                //500,-500
			UP_delay_ms(160);              //320
		}
		else if(nFence==2)
		{
			move(650,-650);               //500,-500
			UP_delay_us(1);             //320
		}
    else if(nFence==3)
		{
			move(speedN,speedN);
			UP_delay_ms(500);
		}
		else if(nFence==4)
		{
			move(speedN,speedN);
			UP_delay_ms(500);
		}
		else if(nFence==5)
		{
			move(-speedN,-speedN);
			UP_delay_ms(500);
		}
		else if(nFence==6)
		{
			move(-speedN,-speedN);
			UP_delay_ms(500);
		}
		else if(nFence==7)
		{
			move(650,-650);                //500,-500
			UP_delay_us(1);              //150
		}
	 }else if(nStage==1){
  	UP_CDS_SetAngle(4,djDown4,1000);
	  UP_CDS_SetAngle(5,djDown5,1000);
	  if(nEdge==0){
			if(nEnemy==1){
			    move(speedM,speedM);
				  UP_delay_us(1);
			}else if(nEnemy==2){
				move(speedM,-speedM);
				UP_delay_ms(450);
				move(speedM,speedM);
				UP_delay_us(1);
			}else if(nEnemy==3){
				move(-speedM,speedM);
				UP_delay_ms(160);
				move(speedM,speedM);
				UP_delay_us(1);
			}else if(nEnemy==4){
				move(speedM,-speedM);
				UP_delay_ms(160);
				move(speedM,speedM);
				UP_delay_us(1);
			}
			else if(nEnemy==5){
				move(-speedM,speedM);
				UP_delay_ms(90);
				move(speedM,speedM);
				UP_delay_us(1);
			}else if(nEnemy==6){
				move(speedM,-speedM);
				UP_delay_ms(90);
				move(speedM,speedM);
				UP_delay_us(1);
			}else if(nEnemy==7){
				move(speedM,-speedM);
				UP_delay_ms(380);
				move(speedM,speedM);
				UP_delay_us(1);
			}else if(nEnemy==8){
				move(-speedM,speedM);
				UP_delay_ms(380);
				move(speedM,speedM);
				UP_delay_us(1);
		  }else{
			  move(500,500);
			  UP_delay_us(1);
			}
		}else if(nEdge==1){
			move(-speedN,-speedN);
      UP_delay_ms(400);
		  move(speedM,-speedM);
		  UP_delay_ms(450);
			move(speedN,speedN);
			UP_delay_ms(100);
		}else if(nEdge==2){
			move(-speedN,-speedN);
		  UP_delay_ms(400);
		  move(-speedM,speedM);
			UP_delay_ms(450);
			move(speedN,speedN);
			UP_delay_ms(100);
		}else if(nEdge==3){
		  move(-speedN,-speedN);
			UP_delay_ms(400);
			move(speedM,-speedM);
		  UP_delay_ms(450);
		}else if(nEdge==4){ 
		  move(speedN,speedN);
			UP_delay_ms(100);
		}else if(nEdge==5){
			move(speedN,speedN);
		  UP_delay_ms(100);
		}else if(nEdge==6){
		  //move(-speedN,-speedN);
      //UP_delay_ms(100);			
		}
	 }
	
  }
}