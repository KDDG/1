#include"UPLib\\UP_System.h"


u32 g_Timer0Count= 0;        //计时器0的计数值

int AD1 = 0;		// 
int AD2 = 0;		//底部右侧红外光电
int AD3 = 0;		//底部后方红外光电
int AD4 = 0;		//底部左侧红外光电

int AD5 = 0;		//前红外测距传感器
int AD6 = 0;		//右红外测距传感器
int AD7 = 0;		//后红外测距传感器
int AD8 = 0;		//左红外测距传感器

int AD9 = 0;		//左前防掉台红外光电
int AD10 = 0;		//右前防掉台红外光电
int AD11 = 0;		//右后防掉台红外光电
int AD12 = 0;		//左后防掉台红外光电
int AD13 = 0;
int AD14 = 0;
int AD15 = 0;		//倾角传感器

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

int QX = 0;			//倾斜

  
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

void hding()  //收后爪
{
	UP_CDS_SetAngle(7, 24, 800);
	UP_CDS_SetAngle(8, 1000, 800);
	UP_delay_ms(10);
	UP_CDS_SetAngle(7, 24, 800);
	UP_CDS_SetAngle(8, 1000, 800);
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

void move(int leftforward,int rightforward)
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

void qianshangtai()  //前上台
{		move(0,0);	//停下来，防止前一状态是转弯改变上台方向
		UP_delay_ms(100);
		//zhong();//四支架抬起为支擂台做准备
		//UP_delay_ms(400);
		move(400,400);//对准擂台
		UP_delay_ms(700);
		//qding();//前爪支地
		//UP_delay_ms(800);
		//UP_CDS_SetAngle(5, 384, 512);
		//UP_CDS_SetAngle(6, 640, 512);
		//UP_delay_ms(500);
		//hding();//支后腿
		//UP_delay_ms(800);
		//zhong();
		//chanzi();//收后爪到铲子状态
		//UP_delay_ms(1000);
	  move(-800,800);
		UP_delay_ms(800);
		move(0,0);
		UP_delay_ms(200);
		move(1000,1000);	//
		UP_delay_ms(2000);
}
//

void houshangtai()  //后上台
{
		move(0,0);	//停下来，防止前一状态是转弯改变上台方向
		UP_delay_ms(100);
	  //zhong();//四支架抬起为支擂台做准备
		//UP_delay_ms(400);
		move(-500,-500);//对准擂台
		UP_delay_ms(600);
		//hding();//前爪支地
		//UP_delay_ms(900);
		//UP_CDS_SetAngle(7, 640, 512);
		//UP_CDS_SetAngle(8, 384, 512);
		//UP_delay_ms(500);
		//qding();//支后腿
		//UP_delay_ms(800);
		//zhong();
		//chanzi();//收后爪到铲子状态
		//UP_delay_ms(1000);
		move(1000,1000);	//
		UP_delay_ms(1500);
}
//

unsigned char Stage()//检测是否在台上
{
	AD15 = UP_ADC_GetValue(15); 
	Qian = (!UP_ADC_GetIO(1))|UP_ADC_GetIO(5);
	You  = (!UP_ADC_GetIO(2))|UP_ADC_GetIO(6);
	Hou  = (!UP_ADC_GetIO(3))|UP_ADC_GetIO(7);
	Zuo  = (!UP_ADC_GetIO(4))|UP_ADC_GetIO(8);
	Summ = Qian + Hou + Zuo + You;
	if((AD15 > 2000)&&(AD15 < 2400))
	{
		if (Summ>=2)
		{
			return 0;  //在台下
		}
		else
		{
			return 1;   //在台上
		}
	}
	else if (AD15<=2000)
	{
		return 3;   //卡在擂台左侧在地面右侧在擂台
	}
	else 
	{
		return 4;   //卡在擂台右侧在地面左侧在擂台
	}
}
//

#define FD  150  //
#define RD  150	 //
#define BD  150	 //
#define LD  180  //

unsigned char Fence()//在台下检测朝向
{
	 AD4=UP_ADC_GetIO(4); //下 后
	 AD5=UP_ADC_GetIO(5); //上 后
	 AD6=UP_ADC_GetIO(6); //下 前
	 AD7=UP_ADC_GetIO(7); //上 前
	 AD8=UP_ADC_GetIO(8); //下 右
	 AD9=UP_ADC_GetIO(9); //下 左
	 
	  /*正对着台*/
	  if(AD4==0&&AD5==0&&AD6==0&&AD7==1&&AD8==1&&AD9==1)
		{
			 return 0;
    }
		
	  /*背对着台*/
		else if(AD4==0&&AD6==0&&AD7==0&&AD5==1&&AD8==1&&AD9==1)
		{
			 return 1;	
		}
		
		/*侧对着台*/
		else if(AD8==0&&AD9==0)
		{
			return 2;			
		}
		
		/*左后角*/
	  else if(AD9==0&&AD4==0&&AD5==0)
		{
			return 3;
		}
		
		/*右后角*/
		else if(AD8==0&&AD4==0&&AD5==0)
		{
			return 4;
		}
		
		/*左前角*/
		else if(AD9==0&&AD6==0&&AD7==0)
		{
			return 5;
		}
		
		/*右前角*/
		else if(AD8==0&&AD6==0&&AD7==0)
		{
			return 6;
		}
		
		/*其他*/
		else 
		{
			return 7;
		}
		
}
//

unsigned char Edge()  //检测边缘
{
	int g1=2920;          //2920
	int g2=3120;          //3120
	int g3=1500;          //1580
	
	
	
	AD1=UP_ADC_GetValue(1);
	AD2=UP_ADC_GetValue(2);
	AD3=UP_ADC_GetValue(3);
  //方案1
	if(AD1>g1&&AD2>g2)
		return 0;    //在里面
	else if(AD1<g1&&AD2>g2)
		return 1;    //1在外面
	else if(AD1>g1&&AD2<g2)
		return 2;    //2在外面
	else if(AD1<g1&&AD2<g2){
			if(AD3>g3)
				return 4; //朝里面
			if(AD3<g3)
				return 3;  //朝外面
	}else 
	  return 5;
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
	AD7 = UP_ADC_GetIO(7); //前红外测距传感器
	AD8 = UP_ADC_GetIO(8);
	AD14 = UP_ADC_GetIO(14);
	AD15 = UP_ADC_GetIO(15);
	if(AD7==0)
		return 1; //前方检测到
	else if(AD8==0)
		return 2; //右边检测到
	else if(AD14==0)
		return 3; //右前方检测到
	else 
		return 0;
	
	/*
	if ((AD1 > 100)&&(AD2 > 100)&&(AD3 > 100)&&(AD4 > 100))
	{
		return 0;  //无敌人
	}
	if ((AD1 < 100)&&(AD2 > 100)&&(AD3 > 100)&&(AD4 > 100))
	{
		if (AD5>1000)
		{
			return 11;  //前方是箱子
		}
		else
			{
				return 1;   //前方有棋子
			}
	}
	if ((AD1 > 100)&&(AD2 < 100)&&(AD3 > 100)&&(AD4 > 100))
	{
		return 2;   //右侧有敌人或棋子
	}
	if ((AD1 > 100)&&(AD2 > 100)&&(AD3 < 100)&&(AD4 > 100))
	{
		return 3;   //后方有敌人或棋子
	}
	if ((AD1 > 100)&&(AD2 > 100)&&(AD3 > 100)&&(AD4 < 100))
	{
		return 4;   //左侧有敌人或棋子
	}
	else
	{
		
		
		
		
		return 103;//错误
	}
	*/
}
//

unsigned char UStage()
{
	int b1,b2,b3;
	AD1=UP_ADC_GetValue(1);
	AD2=UP_ADC_GetValue(2);
	AD3=UP_ADC_GetValue(3); 
	b1=2300;
	b2=2550;
	b3=830;
	if(AD1<b1||AD2<b2||AD3<b3)
	  return 0;
	else 
	  return 1;
}  
//

/*定义Timer中断入口函数*/
void TimerHadler0(u32 timerchannel)
{
	
   //g_Timer0Count++;              //相应的变量加1
	 nStage=UStage();
	 if(nStage==0)
	   nFence=Fence();
	 else if(nStage==1){
		 nEdge=Edge();
	   nEnemy=Enemy();
	 }
}
//

/*外部中断检测上台
void UP_ExtiHadler1(u32 extichannel)
{
	AD5=UP_ADC_GetIO(5);
	AD6=UP_ADC_GetIO(6);
	if(extichannel==EXTI_AD4)
	{
		if(AD5==0&&AD6==0)
		{
		move(1000,1000);
		}
		else if(AD5==1&&AD6==0)
		{
		move(360,360);
		}
		else
		{
		}
		}
}
*/
//

//主函数
int main()
{  
	//计时器初始设置
	UP_Timer_EnableIT(TIMER_CHANNEL0, 20);       //使能计时器0，计时时间1s
  UP_Timer_SetHadler(TIMER_CHANNEL0, TimerHadler0);//传递计时器0的中断入口函数指针

	/*外部中断检测上台	
	UP_Exti_EnableIT(EXTI_AD4, EXTI_Trigger_Falling);  
  UP_Exti_SetHadler(UP_ExtiHadler1);
*/	
	
	//系统初始化
	UP_System_Init();
	UP_CDS_SetMode(3,CDS_SEVMODE);
	UP_CDS_SetMode(6,CDS_SEVMODE);
 
	//UP_CDS_SetAngle(3,1008,800);
	//UP_CDS_SetAngle(6,0,800);
	while(1)
	{
		UP_LCD_ClearScreen();
		UP_LCD_ShowInt(3,3,nFence);
		UP_LCD_ShowInt(0,3,nStage);
		UP_LCD_ShowInt(5,3,nEdge);
		UP_LCD_ShowInt(7,3,nEnemy);
		
		UP_LCD_ShowInt(0,2,AD1);
		UP_LCD_ShowInt(6,2,AD2);
		UP_LCD_ShowInt(3,0,AD3);
		
	 if(nStage==0){
		UP_CDS_SetAngle(3,1008,800);
	  UP_CDS_SetAngle(6,0,800);
		if(nFence==0)
		{
			move(-700,-700);
			UP_delay_ms(400);
			move(1000,1000);
			UP_delay_ms(650);
		}
		else if(nFence==1)
		{
			move(500,500);
			UP_delay_ms(500);
			move(550,-550);                //500,-500
			UP_delay_ms(160);              //320
		}
		else if(nFence==2)
		{
			move(550,-550);               //500,-500
			UP_delay_us(1);             //320
		}
    else if(nFence==3)
		{
			move(500,500);
			UP_delay_ms(500);
		}
		else if(nFence==4)
		{
			move(500,500);
			UP_delay_ms(500);
		}
		else if(nFence==5)
		{
			move(-500,-500);
			UP_delay_ms(500);
		}
		else if(nFence==6)
		{
			move(-500,-500);
			UP_delay_ms(500);
		}
		else if(nFence==7)
		{
			move(550,-450);                //500,-500
			UP_delay_us(1);              //150
		}
	}else if(nStage==1){
  	UP_CDS_SetAngle(3,496,800);
	  UP_CDS_SetAngle(6,512,800);
	  if(nEdge==0){
		  move(400,400);
			UP_delay_us(20);
		}else if(nEdge==1){
			move(-600,-600);
			UP_delay_ms(200);
		  move(600,-600);
			UP_delay_ms(300);
			move(500,500);
			UP_delay_ms(100);
		}else if(nEdge==2){
			move(-600,-600);
			UP_delay_ms(200);
		  move(-600,600);
			UP_delay_ms(300);
			move(500,500);
			UP_delay_ms(100);
		}else if(nEdge==3){
		  move(-600,-600);
			UP_delay_ms(400);
			move(600,-600);
			UP_delay_ms(400);
		}else if(nEdge==4){
		  move(600,600);
			UP_delay_ms(200);
		}else if(nEdge==5){
			move(-600,-600);
			UP_delay_ms(300);
		  move(600,-600);
			UP_delay_ms(400);
		}
	}
	

  }

}