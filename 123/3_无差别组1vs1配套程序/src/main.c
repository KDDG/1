#include"UPLib\\UP_System.h"
#define hdEdge1          //�Ҷȴ�����1��Ե�����ֵ 
#define hdEdge2          //�Ҷȴ�����2��Ե�����ֵ
#define hdEdge3          //�Ҷȴ�����3��Ե�����ֵ
#define hdDown1          //�Ҷȴ�����1̨�¼����ֵ
#define hdDown2          //�Ҷȴ�����2̨�¼����ֵ
#define hdDown3          //�Ҷȴ�����3̨�¼����ֵ
#define rightDJ  3       //������
#define leftDJ   6       //�Ҷ����
#define djUP4    440    //���3̧��
#define djUP5    682       //���6̧��
#define djDown4  991     //���3�½�
#define djDown5  130    //���6�½�
#define speedM   1000    //������ٶ�    
#define speedN   600     //��ʻ�ٶ�
#define speedR   900     //��ײ
#define speedm   500     //��С�ٶ�

int AD1 = 0;		//�Ҷ�1
int AD2 = 0;		//�Ҷ�2
int AD3 = 0;		//�Ҷ�3

int AD4 = 2000;		//
int AD5 = 2001;		//ǰ�����ഫ����
int AD6 = 2001;		//�Һ����ഫ����
int AD7 = 2001;		//������ഫ����
int AD8 = 2001;		//������ഫ����
int AD9 = 2001;		//
int AD10 = 2001;		//
int AD11 = 2001;		//
int AD12 = 2001;		//
int AD13 = 2001;   //

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
	 AD4=UP_ADC_GetValue(4); //�� ��
	 AD5=UP_ADC_GetValue(5); //�� ��
	 AD6=UP_ADC_GetValue(6); //�� ǰ
	 AD7=UP_ADC_GetValue(7); //�� ǰ
	 AD8=UP_ADC_GetValue(8); //�� ��
	 AD9=UP_ADC_GetValue(9); //�� ��
	 
	  /*������̨*/
	  if(AD4<1000&&AD5<1000&&AD6<1000&&AD7>1000&&AD8>1000&&AD9>1000)
		{
			 return 0;
    }
		
	  /*������̨*/
		else if(AD4<1000&&AD6<1000&&AD7<1000&&AD5>1000&&AD8>1000&&AD9>1000)
		{
			 return 1;	
		}
		
		/*�����̨*/
		else if(AD8<1000&&AD9<1000)
		{
			return 2;			
		}
		
		/*����*/
	  else if(AD9<1000&&AD4<1000&&AD5<1000)
		{
			return 3;
		}
		
		/*�Һ��*/
		else if(AD8<1000&&AD4<1000&&AD5<1000)
		{
			return 4;
		}
		
		/*��ǰ��*/
		else if(AD9<1000&&AD6<1000&&AD7<1000)
		{
			return 5;
		}
		
		/*��ǰ��*/
		else if(AD8<1000&&AD6<1000&&AD7<1000)
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
	int g1=2865;          //2880
	int g2=3080;          //3072
	int g3=1500;          //1580
	
	AD1=UP_ADC_GetValue(1);
	AD2=UP_ADC_GetValue(2);
	AD3=UP_ADC_GetValue(3);
  //����1
	if(AD1>g1&&AD2>g2){
		return 0;    //������
	}else if(AD1<g1&&AD2>g2){
		  if(AD3<1520)
		      return 1;    //1������
			else if(AD3>=1520)
				  return 4;
	}else if(AD1>g1&&AD2<g2){
		  if(AD3<1520)
		     return 2;    //2������
			else if(AD3>=1520)
				 return 4;
	}else if(AD1<g1&&AD2<g2){
			if(AD3>=1520){
				return 4; //������
			}else if(AD3<1520){
				if(AD1>2820&&AD2>3040){
		   		return 3;  //������
				}else if(AD1<2820||AD2<3040){
					return 5;  //������
				}else{
				  return 5;
				}
			}
	}else 
	  return 6;
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
	AD4 = UP_ADC_GetValue(4); //��
	AD7 = UP_ADC_GetValue(7); //ǰ�����ഫ����
	AD8 = UP_ADC_GetValue(8); //��
	AD9 = UP_ADC_GetValue(9); //��
	AD10= UP_ADC_GetValue(10); //ǰ��
	AD11= UP_ADC_GetValue(11); //ǰ��
	AD12= UP_ADC_GetValue(12); //����
	AD13= UP_ADC_GetValue(13); //����
	if(AD7<1000)
		return 1; //ǰ����⵽
	else if(AD4<1000)
		return 2; //��߼�⵽
	else if(AD9<1000)
		return 3;  //��
	else if(AD8<1000)
		return 4;  //��
	else if(AD10<1000&&AD7>1000)
		return 5;  //ǰ��
	else if(AD11<1000&&AD7>1000)
		return 6;  //ǰ��
	else if(AD12<1000)
		return 7;  //����
	else if(AD13<1000)
		return 8; //����ǰ����⵽
  else 
		return 9; //unknow
	
	/*
	*/
}



//
unsigned char Stage()//�Ƿ���̨��
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
	UP_Timer_EnableIT(TIMER_CHANNEL0, 2);       //ʹ�ܼ�ʱ��0����ʱʱ��20us
  UP_Timer_SetHadler(TIMER_CHANNEL0, TimerHadler0);//���ݼ�ʱ��0���ж���ں���ָ��

	/*�ⲿ�жϼ����̨	
	UP_Exti_EnableIT(EXTI_AD4, EXTI_Trigger_Falling);  
  UP_Exti_SetHadler(UP_ExtiHadler1);
*/	
	
	//ϵͳ��ʼ��
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