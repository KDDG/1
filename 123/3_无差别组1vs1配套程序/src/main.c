#include"UPLib\\UP_System.h"


u32 g_Timer0Count= 0;        //��ʱ��0�ļ���ֵ

int AD1 = 0;		// 
int AD2 = 0;		//�ײ��Ҳ������
int AD3 = 0;		//�ײ��󷽺�����
int AD4 = 0;		//�ײ���������

int AD5 = 0;		//ǰ�����ഫ����
int AD6 = 0;		//�Һ����ഫ����
int AD7 = 0;		//������ഫ����
int AD8 = 0;		//������ഫ����

int AD9 = 0;		//��ǰ����̨������
int AD10 = 0;		//��ǰ����̨������
int AD11 = 0;		//�Һ����̨������
int AD12 = 0;		//������̨������
int AD13 = 0;
int AD14 = 0;
int AD15 = 0;		//��Ǵ�����

int nStage = 0;	//�����̨�ϻ�����̨��
int nEdge = 0;	//��Ե
int nEnemy = 0;	//����
int nFence = 0;	//̨��״̬

int Qian = 0;		//ǰ���޵���
int You = 0;		//�����޵���
int Hou = 0;		//�����޵���
int Zuo = 0;		//�����޵���
int Summ = 0;	//ǰ�����Ҽ�����⵽		
int left = 0;
int right = 0;

int na = 0;     //��б��ʱ
int nb = 0;			//�����Ӽ�ʱ
int nc = 8;			//��ת��ʱ
int nd = 0;			//ǰ��ǳ��ʱ
int ne = 8;			//���ǳ��ʱ

int QX = 0;			//��б

  
void zhong()    //��̨Ĭ�϶���
{
	UP_CDS_SetAngle(5, 384, 800);
	UP_CDS_SetAngle(6, 640, 800);
	UP_CDS_SetAngle(7, 640, 800);
	UP_CDS_SetAngle(8, 384, 800);
}
//

void qding()  //��ǰצ
{
	UP_CDS_SetAngle(5, 1000, 800);
	UP_CDS_SetAngle(6, 24, 800);
	UP_delay_ms(10);
	UP_CDS_SetAngle(5, 1000, 800);
	UP_CDS_SetAngle(6, 24, 800);
}
//

void hding()  //�պ�צ
{
	UP_CDS_SetAngle(7, 24, 800);
	UP_CDS_SetAngle(8, 1000, 800);
	UP_delay_ms(10);
	UP_CDS_SetAngle(7, 24, 800);
	UP_CDS_SetAngle(8, 1000, 800);
}
//

void chanzi()  //��̨�����״̬
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

void qianshangtai()  //ǰ��̨
{		move(0,0);	//ͣ��������ֹǰһ״̬��ת��ı���̨����
		UP_delay_ms(100);
		//zhong();//��֧��̧��Ϊ֧��̨��׼��
		//UP_delay_ms(400);
		move(400,400);//��׼��̨
		UP_delay_ms(700);
		//qding();//ǰצ֧��
		//UP_delay_ms(800);
		//UP_CDS_SetAngle(5, 384, 512);
		//UP_CDS_SetAngle(6, 640, 512);
		//UP_delay_ms(500);
		//hding();//֧����
		//UP_delay_ms(800);
		//zhong();
		//chanzi();//�պ�צ������״̬
		//UP_delay_ms(1000);
	  move(-800,800);
		UP_delay_ms(800);
		move(0,0);
		UP_delay_ms(200);
		move(1000,1000);	//
		UP_delay_ms(2000);
}
//

void houshangtai()  //����̨
{
		move(0,0);	//ͣ��������ֹǰһ״̬��ת��ı���̨����
		UP_delay_ms(100);
	  //zhong();//��֧��̧��Ϊ֧��̨��׼��
		//UP_delay_ms(400);
		move(-500,-500);//��׼��̨
		UP_delay_ms(600);
		//hding();//ǰצ֧��
		//UP_delay_ms(900);
		//UP_CDS_SetAngle(7, 640, 512);
		//UP_CDS_SetAngle(8, 384, 512);
		//UP_delay_ms(500);
		//qding();//֧����
		//UP_delay_ms(800);
		//zhong();
		//chanzi();//�պ�צ������״̬
		//UP_delay_ms(1000);
		move(1000,1000);	//
		UP_delay_ms(1500);
}
//

unsigned char Stage()//����Ƿ���̨��
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
			return 0;  //��̨��
		}
		else
		{
			return 1;   //��̨��
		}
	}
	else if (AD15<=2000)
	{
		return 3;   //������̨����ڵ����Ҳ�����̨
	}
	else 
	{
		return 4;   //������̨�Ҳ��ڵ����������̨
	}
}
//

#define FD  150  //
#define RD  150	 //
#define BD  150	 //
#define LD  180  //

unsigned char Fence()//��̨�¼�⳯��
{
	 AD4=UP_ADC_GetIO(4); //�� ��
	 AD5=UP_ADC_GetIO(5); //�� ��
	 AD6=UP_ADC_GetIO(6); //�� ǰ
	 AD7=UP_ADC_GetIO(7); //�� ǰ
	 AD8=UP_ADC_GetIO(8); //�� ��
	 AD9=UP_ADC_GetIO(9); //�� ��
	 
	  /*������̨*/
	  if(AD4==0&&AD5==0&&AD6==0&&AD7==1&&AD8==1&&AD9==1)
		{
			 return 0;
    }
		
	  /*������̨*/
		else if(AD4==0&&AD6==0&&AD7==0&&AD5==1&&AD8==1&&AD9==1)
		{
			 return 1;	
		}
		
		/*�����̨*/
		else if(AD8==0&&AD9==0)
		{
			return 2;			
		}
		
		/*����*/
	  else if(AD9==0&&AD4==0&&AD5==0)
		{
			return 3;
		}
		
		/*�Һ��*/
		else if(AD8==0&&AD4==0&&AD5==0)
		{
			return 4;
		}
		
		/*��ǰ��*/
		else if(AD9==0&&AD6==0&&AD7==0)
		{
			return 5;
		}
		
		/*��ǰ��*/
		else if(AD8==0&&AD6==0&&AD7==0)
		{
			return 6;
		}
		
		/*����*/
		else 
		{
			return 7;
		}
		
}
//

unsigned char Edge()  //����Ե
{
	int g1=2920;          //2920
	int g2=3120;          //3120
	int g3=1500;          //1580
	
	
	
	AD1=UP_ADC_GetValue(1);
	AD2=UP_ADC_GetValue(2);
	AD3=UP_ADC_GetValue(3);
  //����1
	if(AD1>g1&&AD2>g2)
		return 0;    //������
	else if(AD1<g1&&AD2>g2)
		return 1;    //1������
	else if(AD1>g1&&AD2<g2)
		return 2;    //2������
	else if(AD1<g1&&AD2<g2){
			if(AD3>g3)
				return 4; //������
			if(AD3<g3)
				return 3;  //������
	}else 
	  return 5;
	//����2
  /*
	if(AD1>g1&&AD2>g2&&AD3>g3)
		return 0;  //���м�
	else if(AD1<g1&&AD2>g2&&AD3>g3)
		return 1;  //1������
	else if(AD1>g1&&AD2<g2&&AD3>g3)
		return 2;  //2������
	else if(AD1>g1&&AD2>g2&&AD3<g3)
		return 3;  //3������
	else if(AD1<g1&&AD2<g2&&AD3>g3)
		return 4;  //1,2
	else if(AD1<g1&&AD2>g2&&AD3<g3)
		return 5;  //1,3
	else if(AD1>g1&&AD2<g2&&AD3<g3)
		return 6;  //2,3
	else if(AD1<2673&&AD2<2697&&AD3<855)
		return 8;  //����������
	else if(AD1<2629&&AD2<2620&&AD3<1013)
		return 9;  //���为����
	else
		return 7;  //����
	*/
}
//

unsigned char Enemy()   //������
{
	AD7 = UP_ADC_GetIO(7); //ǰ�����ഫ����
	AD8 = UP_ADC_GetIO(8);
	AD14 = UP_ADC_GetIO(14);
	AD15 = UP_ADC_GetIO(15);
	if(AD7==0)
		return 1; //ǰ����⵽
	else if(AD8==0)
		return 2; //�ұ߼�⵽
	else if(AD14==0)
		return 3; //��ǰ����⵽
	else 
		return 0;
	
	/*
	if ((AD1 > 100)&&(AD2 > 100)&&(AD3 > 100)&&(AD4 > 100))
	{
		return 0;  //�޵���
	}
	if ((AD1 < 100)&&(AD2 > 100)&&(AD3 > 100)&&(AD4 > 100))
	{
		if (AD5>1000)
		{
			return 11;  //ǰ��������
		}
		else
			{
				return 1;   //ǰ��������
			}
	}
	if ((AD1 > 100)&&(AD2 < 100)&&(AD3 > 100)&&(AD4 > 100))
	{
		return 2;   //�Ҳ��е��˻�����
	}
	if ((AD1 > 100)&&(AD2 > 100)&&(AD3 < 100)&&(AD4 > 100))
	{
		return 3;   //���е��˻�����
	}
	if ((AD1 > 100)&&(AD2 > 100)&&(AD3 > 100)&&(AD4 < 100))
	{
		return 4;   //����е��˻�����
	}
	else
	{
		
		
		
		
		return 103;//����
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

/*����Timer�ж���ں���*/
void TimerHadler0(u32 timerchannel)
{
	
   //g_Timer0Count++;              //��Ӧ�ı�����1
	 nStage=UStage();
	 if(nStage==0)
	   nFence=Fence();
	 else if(nStage==1){
		 nEdge=Edge();
	   nEnemy=Enemy();
	 }
}
//

/*�ⲿ�жϼ����̨
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

//������
int main()
{  
	//��ʱ����ʼ����
	UP_Timer_EnableIT(TIMER_CHANNEL0, 20);       //ʹ�ܼ�ʱ��0����ʱʱ��1s
  UP_Timer_SetHadler(TIMER_CHANNEL0, TimerHadler0);//���ݼ�ʱ��0���ж���ں���ָ��

	/*�ⲿ�жϼ����̨	
	UP_Exti_EnableIT(EXTI_AD4, EXTI_Trigger_Falling);  
  UP_Exti_SetHadler(UP_ExtiHadler1);
*/	
	
	//ϵͳ��ʼ��
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