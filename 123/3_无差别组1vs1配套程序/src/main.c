#include"UPLib\\UP_System.h"
#define hdEdge1          //�Ҷȴ�����1��Ե�����ֵ 
#define hdEdge2          //�Ҷȴ�����2��Ե�����ֵ
#define hdEdge3          //�Ҷȴ�����3��Ե�����ֵ
#define hdDown1          //�Ҷȴ�����1̨�¼����ֵ
#define hdDown2          //�Ҷȴ�����2̨�¼����ֵ
#define hdDown3          //�Ҷȴ�����3̨�¼����ֵ
#define rightDJ  3       //������
#define leftDJ   6       //�Ҷ����
#define djUP3    1008    //���3̧��
#define djUP6    0       //���6̧��
#define djDown3  496     //���3�½�
#define djDown6  512     //���6�½�
#define speedM   1000    //������ٶ�    
#define speedN   600     //��ʻ�ٶ�
#define speedR   900     //��ײ
#define speedm   500     //��С�ٶ�

int AD1 = 0;		//�Ҷ�1
int AD2 = 0;		//�Ҷ�2
int AD3 = 0;		//�Ҷ�3

int AD4 = 1;		//
int AD5 = 1;		//ǰ�����ഫ����
int AD6 = 1;		//�Һ����ഫ����
int AD7 = 1;		//������ഫ����
int AD8 = 1;		//������ഫ����
int AD9 = 1;		//
int AD10 = 1;		//
int AD11 = 1;		//
int AD12 = 1;		//
int AD13 = 1;   //

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
void chanzi()  //��̨�����״̬
{
	UP_CDS_SetAngle(5, 780, 800);
	UP_CDS_SetAngle(6, 244, 800);
	UP_CDS_SetAngle(7, 244, 800);
	UP_CDS_SetAngle(8, 780, 800);
}
//
void move(int leftforward,int rightforward) //�ƶ�����
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
			return 7; //unknow
		}
		
}
//
unsigned char Edge()  //����Ե
{
	int g1=2940;          //2920
	int g2=3090;          //3120
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
			if(AD3>1600)
				return 4; //������
			if(AD3<1400)
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
	AD5 = UP_ADC_GetIO(5); //��
	AD7 = UP_ADC_GetIO(7); //ǰ�����ഫ����
	AD8 = UP_ADC_GetIO(8); //��
	AD9 = UP_ADC_GetIO(9); //��
	AD10= UP_ADC_GetIO(10); //ǰ��
	AD11= UP_ADC_GetIO(11); //ǰ��
	AD12= UP_ADC_GetIO(12); //����
	AD13= UP_ADC_GetIO(13); //����
	if(AD7==0&&AD8==1&&AD5==1&&AD9==1&&AD10==1&&AD11==1&&AD12==1&&AD13==1)
		return 1; //ǰ����⵽
	else if(AD5==0)
		return 2; //��߼�⵽
	else if(AD9==0)
		return 3;  //��
	else if(AD8==0)
		return 4;  //��
	else if(AD10==0)
		return 5;  //ǰ��
	else if(AD11==0)
		return 6;  //ǰ��
	else if(AD12==0)
		return 7;  //����
	else if(AD13==0)
		return 8; //����ǰ����⵽
  else 
		return 9; //unknow
	
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
unsigned char Stage()//�Ƿ���̨��
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
void TimerHadler0(u32 timerchannel) //����Timer�ж���ں���
{
	
   //g_Timer0Count++;              //��Ӧ�ı�����1
	 nStage=Stage();
	 if(nStage==0)
	   nFence=Fence();
	 else if(nStage==1){
		 nEdge=Edge();
	   nEnemy=Enemy();
	 }
}



//
int main()  //������
{  
	//��ʱ����ʼ����
	UP_Timer_EnableIT(TIMER_CHANNEL0, 20);       //ʹ�ܼ�ʱ��0����ʱʱ��20us
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
		
		UP_LCD_ShowInt(0,2,AD1);
		UP_LCD_ShowInt(6,2,AD2);
		UP_LCD_ShowInt(3,0,AD3);
		
		if(nStage==0){
		  UP_LCD_ShowInt(0,3,nStage);
		  UP_LCD_ShowInt(3,3,nFence);
		}else if(nStage==1){
		  UP_LCD_ShowInt(5,3,nEdge);
      UP_LCD_ShowInt(7,3,nEnemy);
		}		
		
	 if(nStage==0){
		UP_CDS_SetAngle(3,djUP3,800);
	  UP_CDS_SetAngle(6,djUP6,800);
		if(nFence==0)
		{
			move(-speedR,-speedR);
			UP_delay_ms(400);
			move(speedM,speedM);
			UP_delay_ms(650);
		}
		else if(nFence==1)
		{
			move(speedN,speedN);
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
			move(550,-450);                //500,-500
			UP_delay_us(1);              //150
		}
	 }else if(nStage==1){
  	UP_CDS_SetAngle(3,djDown3,800);
	  UP_CDS_SetAngle(6,djDown6,800);
	  if(nEdge==0){
			if(nEnemy==1){
			  move(speedR,speedR);
				UP_delay_us(5);
			}else if(nEnemy==2){
				move(speedN,-speedN);
			}else if(nEnemy==3){
				move(-speedN,speedN);
				UP_delay_ms(200);
			}else if(nEnemy==4){
				move(speedN,-speedN);
				UP_delay_ms(200);
			}else if(nEnemy==5){
				move(-speedN,speedN);
			}else if(nEnemy==6){
				move(speedN,-speedN);
			}else if(nEnemy==7){
				move(speedN,-speedN);
			}else if(nEnemy==8){
				move(-speedN,speedN);
			}
			move(speedN,speedN);
			UP_delay_us(5);
		}else if(nEdge==1){
			move(-speedN,-speedN);
			UP_delay_ms(200);
		  move(speedN,-speedN);
			UP_delay_ms(300);
			move(speedm,speedm);
			UP_delay_ms(100);
		}else if(nEdge==2){
			move(-speedN,-speedN);
			UP_delay_ms(200);
		  move(-speedN,speedN);
			UP_delay_ms(300);
			move(speedm,speedm);
			UP_delay_ms(100);
		}else if(nEdge==3){
		  move(-speedN,-speedN);
			UP_delay_ms(400);
			move(speedN,-speedN);
			UP_delay_ms(400);
		}else if(nEdge==4){
		  move(speedN,speedN);
			UP_delay_ms(200);
		}else if(nEdge==5){
			move(-speedN,-speedN);
			UP_delay_ms(300);
		  move(speedN,-speedN);
			UP_delay_ms(400);
		}
	 }
	
  }
}