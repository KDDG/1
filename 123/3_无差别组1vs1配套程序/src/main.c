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

void qding()  //��ǰצ
{
	UP_CDS_SetAngle(5, 1000, 800);
	UP_CDS_SetAngle(6, 24, 800);
	UP_delay_ms(10);
	UP_CDS_SetAngle(5, 1000, 800);
	UP_CDS_SetAngle(6, 24, 800);
}

void hding()  //�պ�צ
{
	UP_CDS_SetAngle(7, 24, 800);
	UP_CDS_SetAngle(8, 1000, 800);
	UP_delay_ms(10);
	UP_CDS_SetAngle(7, 24, 800);
	UP_CDS_SetAngle(8, 1000, 800);
}

void chanzi()  //��̨�����״̬
{
	UP_CDS_SetAngle(5, 780, 800);
	UP_CDS_SetAngle(6, 244, 800);
	UP_CDS_SetAngle(7, 244, 800);
	UP_CDS_SetAngle(8, 780, 800);
}

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


#define FD  150  //
#define RD  150	 //
#define BD  150	 //
#define LD  180  //

/*unsigned char Fence()//��̨�¼�⳯��
{
	AD1 = UP_ADC_GetValue(1); //�ײ�ǰ��������
	AD2 = UP_ADC_GetValue(2); //�ײ��Ҳ������
	AD3 = UP_ADC_GetValue(3); //�ײ��󷽺�����
	AD4 = UP_ADC_GetValue(4); //�ײ���������
	AD5 = UP_ADC_GetValue(5); //ǰ�����ഫ����
	AD6 = UP_ADC_GetValue(6); //�Һ����ഫ����
	AD7 = UP_ADC_GetValue(7); //������ഫ����
	AD8 = UP_ADC_GetValue(8); //������ഫ����
	
	
	AD4=UP_ADC_GetIO(4);  //�ײ�ǰ������
	AD5=UP_ADC_GetIO(5);  //�ײ��������
  AD6=UP_ADC_GetIO(6);  //�ϲ�ǰ������
	AD7=UP_ADC_GetIO(7);  //�ϲ��������
	
	if(AD4==0)
	   return 0;  //ǰ����׼��̨
	else if(AD5==0&&AD7==1)
	   return 1;  //�󷽶�׼��̨
	else if(AD4==1&&AD5==1)
		 return 2;  //��û��׼
	else if(AD4==0&&AD6==0)
	   return 3;  //�󷽶�׼Χ��
	else if(AD5==0&&AD7==0)
		 return 4;  //ǰ����׼Χ��
 	  
/////////////////////////����̨��һ������⵽/////////////////////////
	if((AD3 < 1000)&&(AD2 > 1000)&&(AD4 > 1000)&&(AD5 > FD)&&(AD6 < RD)&&(AD7 < BD)&&(AD8 < LD))//ǰ���ͺ����
		{
			return 1;		//��̨�£��󷽶���̨
		}
	
	if((AD4 < 1000)&&(AD1 > 1000)&&(AD3 > 1000)&&(AD5 < FD)&&(AD6 > RD)&&(AD7 < BD)&&(AD8 < LD))//�Ҳ�������
		{
			return 2;		//��̨�£�������̨
		}		
	
	if((AD1 < 1000)&&(AD2 > 1000)&&(AD4 > 1000)&&(AD5 < FD)&&(AD6 < RD)&&(AD7 > BD)&&(AD8 < LD))//����ǰ����
		{
			return 3;		//��̨�£�ǰ������̨
		}		
	
	if((AD2 < 1000)&&(AD1 > 1000)&&(AD3 > 1000)&&(AD5 < FD)&&(AD6 < RD)&&(AD7 < BD)&&(AD8 > LD))//�����Һ���
		{
			return 4;		//��̨�£��Ҳ����̨
		}	
/////////////////////////��Χ�����������ڲ���⵽/////////////////////////
	
	if((AD2 > 1000)&&(AD3 > 1000)&&(AD5 > FD)&&(AD6 < RD)&&(AD7 < BD)&&(AD8 > LD))
		{
			return 5;		//��̨�£�ǰ���⵽Χ��
		}	
	if((AD3 > 1000)&&(AD4 > 1000)&&(AD5 > FD)&&(AD6 > RD)&&(AD7 < BD)&&(AD8 < LD))
		{
			return 6;		//��̨�£�ǰ�Ҽ�⵽Χ��
		}		

	if((AD1 > 1000)&&(AD4 > 1000)&&(AD5 < FD)&&(AD6 > RD)&&(AD7 > BD)&&(AD8 < LD))
		{
			return 7;		//��̨�£����Ҽ�⵽Χ��
		}	
	if((AD1 > 1000)&&(AD2 > 1000)&&(AD5 < FD)&&(AD6 < RD)&&(AD7 > BD)&&(AD8 > LD))
		{
			return 8;		//��̨�£������⵽Χ��
		}		

/////////////////////////̨���е��ˣ�������Բ���⵽/////////////////////////
	if((AD5 > FD)&&(AD6 < RD)&&(AD7 > BD)&&(AD8 < LD))
		{
			return 9;		//��̨�£�ǰ�������̨�ϵ���
		}	
	
	if((AD5 < FD)&&(AD6 > RD)&&(AD7 < BD)&&(AD8 > LD))
		{
			return 10;	//��̨�£������Ҳ���̨�ϵ���
		}	
		
/////////////////////////�������ϰ�����������⵽/////////////////////////
	if((AD5 > FD)&&(AD6 > RD)&&(AD7 < BD)&&(AD8 > LD))
		{
			return 11;	//��̨�£�ǰ���������Ҳ��⵽Χ��
		}	
	if((AD5 > FD)&&(AD6 > RD)&&(AD7 > BD)&&(AD8 < LD))
		{
			return 12;	//��̨�£�ǰ�����Ҳ�ͺ󷽼�⵽Χ��
		}	
	if((AD5 > FD)&&(AD6 < RD)&&(AD7 > BD)&&(AD8 > LD))
		{
			return 13;	//��̨�£�ǰ�������ͺ󷽼�⵽Χ��
		}	
	if((AD5 < FD)&&(AD6 > RD)&&(AD7 > BD)&&(AD8 > LD))
		{
			return 14;	//��̨�£��Ҳࡢ���ͺ󷽼�⵽Χ��
		}	
		
		
/////////////////////////б����̨�������������⵽/////////////////////////
	if((AD1 < 1000)&&(AD2 < 1000)&&(AD5 < FD)&&(AD6 < RD))
		{
			return 15;	//��̨�£�ǰ�����Ҳ����̨����������û��⵽
		}	
	if((AD1 < 1000)&&(AD4 < 1000)&&(AD5 < FD)&&(AD8 < LD))
		{
			return 16;	//��̨�£�ǰ����������̨����������û��⵽
		}
	if((AD2 < 1000)&&(AD3 < 1000)&&(AD6 < FD)&&(AD7 < RD))
		{
			return 17;	//��̨�£��󷽺��Ҳ����̨����������û��⵽
		}	
	if((AD3 < 1000)&&(AD4 < 1000)&&(AD7 < FD)&&(AD8 < LD))
		{
			return 18;	//��̨�£��󷽺�������̨����������û��⵽
		}
	
	//////////////
	else
		{
			return 101;//����
		}
		
}
*/



unsigned char Edge()  //����Ե
{
	AD1=UP_ADC_GetValue(1);
	AD2=UP_ADC_GetValue(2);
	AD3=UP_ADC_GetValue(3);
	/*����1
	if(AD1>2700&&AD2>2400&&AD3>1300)
		return 0;  //���м�
	else if(AD1<2700&&AD2<2400&&AD3<1300)
		return 1;  //����󷽼�⵽��Ե
	else if(AD1<2800&&AD2<2600&&AD3<1000)
	  return 2;  //����ǰ����⵽��Ե
	
	else if(AD1<2700&&AD2<2400&&AD3<1600)
		return 3;  //���󷽼�⵽��Ե
	else if(AD1<3000&&AD2<2800&&AD3<1300)
	  return 4;  //��ǰ����⵽��Ե
	else 
		return 5;  //�������
	*/
	
	//����2
	if(AD1>3000&&AD2>2500&&AD3>1400)
		return 0;  //���м�
	else if(AD1>3000&&AD2>2500&&AD3<1400)
		return 1;  //3������
	else if(AD1<3000&&AD2<2500&&AD3>1400)
		return 2;  //1,2������
	else if(AD1>3000&&AD2<2500&&AD3>1400)
		return 3;  //2������
	else if(AD1<3000&&AD2>2500&&AD3>1400)
		return 4;  //1������
	else if(AD1<3000&&AD2>2500&&AD3<1400)
		return 5;  //1,3������
	else if(AD1>3000&&AD2<2500&&AD3<1400)
		return 6;  //2,3������
	else
		return 7;  //�쳣
	
	
	
}

unsigned char Enemy()   //������
{
	AD1 = UP_ADC_GetValue(1); //ǰ�����ഫ����
	AD2 = UP_ADC_GetValue(2); //��ǰ�����紫����
	AD3 = UP_ADC_GetValue(3); //
	AD4 = UP_ADC_GetValue(4); //���к����紫����
	AD5 = UP_ADC_GetValue(5); //���к����紫����
	
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
}


unsigned char UStage()
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





/*����Timer�ж���ں���*/
void TimerHadler0(u32 timerchannel)
{
	
   //g_Timer0Count++;              //��Ӧ�ı�����1
	AD1=UP_ADC_GetValue(1);
	AD2=UP_ADC_GetValue(2);
	AD3=UP_ADC_GetValue(3);
	 nFence=UStage();
	 UP_LCD_ShowInt(0,0,nFence);
}

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
	while(1)
	{
		UP_LCD_ShowInt(0,0,AD1);
		UP_LCD_ShowInt(0,1,AD2);
		UP_LCD_ShowInt(0,2,AD3);
		
		  move(1000,1000);
			UP_delay_ms(800);
		
		if(nFence==0)
		{
			move(-700,-700);
			UP_delay_ms(400);
			move(1000,1000);
			UP_delay_ms(1000);
		}
		else if(nFence==1)
		{
			move(500,500);
			UP_delay_ms(300);
			move(650,-650);                //500,-500
			UP_delay_ms(500);              //320
		}
		else if(nFence==2)
		{
			move(650,-650);               //500,-500
			UP_delay_ms(320);             //320
		}
    else if(nFence==3)
		{
			move(500,500);
			UP_delay_ms(700);
		}
		else if(nFence==4)
		{
			move(500,500);
			UP_delay_ms(700);
		}
		else if(nFence==5)
		{
			move(-500,-500);
			UP_delay_ms(700);
		}
		else if(nFence==6)
		{
			move(-500,-500);
			UP_delay_ms(700);
		}
		else if(nFence==7)
		{
			move(650,-650);                //500,-500
			UP_delay_ms(150);              //150
		}
	
		/*
		UP_delay_ms(1500);
		move(600,-660);
		*/
	}
	/*while(1){
	 nFence=Fence();
	 UP_LCD_ShowInt(0,1,AD4);
	 UP_LCD_ShowInt(0,2,nFence);
	 if(nFence==0){
		 move(-400,-400);
		 UP_delay_ms(200);
	   qianshangtai();
	 }else if(nFence==1){
	   houshangtai();
	 }else if(nFence==2){
	   move(-500,500);
	 }else if(nFence==3){
		 move(-400,-400);
		 UP_delay_ms(200);
		 move(1000,1000);
		 UP_delay_ms(1500);
	 }else if(nFence==4){
	   move(-800,800);
		 UP_delay_ms(800);
		 move(1000,1000);
		 UP_delay_ms(1500);
	 }

	}
	*/

	
	/*
	while(1){
		nEdge=Edge();
	  UP_LCD_ShowInt(0,1,nEdge);
		
		if(nEdge==0){
		  move(400,400);
      UP_delay_ms(200);
			//move(0,0);
			//UP_delay_ms(100);
		}else if(nEdge==1){
		  move(-500,-500);
			UP_delay_ms(700);
			move(200,-500);
			UP_delay_ms(400);
		}else if(nEdge==2){
		  move(500,500);
			UP_delay_ms(400);
		}else if(nEdge==3){
		  move(-500,200);
			UP_delay_ms(400);
		}else if(nEdge==4){
		  move(200,-500);
			UP_delay_ms(400);
		}else if(nEdge==5){
		  move(200,-500);
			UP_delay_ms(400);
		}else if(nEdge==6){
		  move(-500,200);
			UP_delay_ms(400);
		}else if(nEdge==7){
		  move(200,-500);
			UP_delay_ms(500);
		}
	}
	*/
	//��������Ͷ��
	//UP_CDS_SetMode(1, CDS_MOTOMODE);
	//UP_CDS_SetMode(2, CDS_MOTOMODE);
	/*
	while(1){
		nEdge=Edge();
		UP_LCD_ShowInt(0,2,nEdge*1000);
		if(nEdge==0){
			move(400,400);
      UP_delay_ms(500);
			move(0,0);
			UP_delay_ms(200);
		}else if(nEdge==2){
			move(-500,-500);
		  UP_delay_ms(600);
		  move(300,-500);
      UP_delay_ms(400);
		}else if(nEdge==1){
			move(500,500);
		  UP_delay_ms(400);
		}else if(nEdge==4){
			move(-500,-500);
		  UP_delay_ms(600);
		  move(300,-500);
      UP_delay_ms(400);
		}else if(nEdge==3){
			move(500,500);
		  UP_delay_ms(400);
		}else{
		  move(0,0);
		}
	}*/
	/*
	
	UP_CDS_SetMode(5, CDS_SEVMODE);
	UP_CDS_SetMode(6, CDS_SEVMODE);
	UP_CDS_SetMode(7, CDS_SEVMODE);
	UP_CDS_SetMode(8, CDS_SEVMODE);

	zhong();
	UP_delay_ms(1000);
	
  while(1)
	{
		if((UP_ADC_GetValue(2) < 1000)||(UP_ADC_GetValue(4) < 1000))
		{
			break;
		}
		UP_delay_ms(10);
	}
	
	qianshangtai();
	
while(1)
{	
	nStage = Stage();	//�����̨
	
 	
 	UP_LCD_ShowInt(0, 0, nStage);
		switch(nStage)
		{
		  case 0:	//��̨��
// 				move(500,500);	
// 				UP_delay_ms(200);
				nFence = Fence();	//������
			 	UP_LCD_ClearScreen();
				switch(nFence)
				{
					case 1:	//��̨�º󷽶���̨
						houshangtai();
						break;
					case 2:	//������̨
						move(0,0);	
						UP_delay_ms(200);
						while(1)
						{	
							AD1 = UP_ADC_GetValue(1); 
							AD6 = UP_ADC_GetValue(6);
							AD4 = UP_ADC_GetValue(4);
							if((AD1<1000)&&(AD6<160)&&(AD4>1000))
								{
									UP_delay_ms(200);
									move(400,400);	
									UP_delay_ms(300);
									break;
								}
								else
								{
									move(-400,400);	
									UP_delay_ms(2);
								}
						}
						break;
					case 3:	//ǰ������̨
						qianshangtai();
						break;
					case 4:	//�Ҳ����̨
						move(0,0);	
						UP_delay_ms(200);
						while(1)
						{	
							AD1 = UP_ADC_GetValue(1); 
							AD6 = UP_ADC_GetValue(6);
							AD4 = UP_ADC_GetValue(4);
							if((AD1<1000)&&(AD6<160)&&(AD4>1000))
								{
									UP_delay_ms(200);
									move(400,400);	
									UP_delay_ms(300);
									break;
								}
								else
								{
									move(400,-400);	
									UP_delay_ms(2);
								}
						}
						break;
					case 5:	//ǰ���⵽Χ��
						move(-400,-400);	
				  	UP_delay_ms(400);
						break;
					case 6:	//ǰ�Ҽ�⵽Χ��
						move(-400,-400);	
 						UP_delay_ms(400);
 						break;
					case 7:	//���м�⵽Χ��
						move(400,400);	
 						UP_delay_ms(400);
						break;
					case 8:	//�����⵽Χ��
						move(400,400);	
 						UP_delay_ms(400);
						break;
					case 9:	//ǰ�������̨�ϵ���
						move(500,-500);	
						UP_delay_ms(300);
						move(400,400);	
						UP_delay_ms(400);
						break;
					case 10:	//�����Ҳ���̨�ϵ���
						move(400,400);	
						UP_delay_ms(400);
						break;
					case 11:	//ǰ���������Ҳ��⵽Χ��
						move(-400,-300);	
						UP_delay_ms(500);
						move(-400,400);	
						UP_delay_ms(300);
						break;
					case 12:	//ǰ�Һ��⵽Χ��
						move(300,600);	
						UP_delay_ms(400);
						break;
					case 13:	//ǰ����⵽Χ��
						move(600,300);	
						UP_delay_ms(400);
						break;
					case 14:	//������⵽Χ��
						move(-400,400);	
						UP_delay_ms(200);
						move(400,400);	
						UP_delay_ms(300);
						break;
					case 15:	//ǰ�Ҽ�⵽��̨
						move(0,0);	
						UP_delay_ms(200);
						while(1)
						{	
							AD1 = UP_ADC_GetValue(1); 
							AD6 = UP_ADC_GetValue(6);
							AD4 = UP_ADC_GetValue(4);
							if((AD1<1000)&&(AD6<160)&&(AD4>1000))
								{
									UP_delay_ms(200);
									move(400,400);	
									UP_delay_ms(300);
									break;
								}
								else
								{
									move(360,-400);	
									UP_delay_ms(2);
								}
						}
						break;
					case 16:	//ǰ���⵽��̨
						move(0,0);	
						UP_delay_ms(200);
						while(1)
						{	
							AD1 = UP_ADC_GetValue(1); 
							AD6 = UP_ADC_GetValue(6);
							AD4 = UP_ADC_GetValue(4);
							if((AD1<1000)&&(AD6<160)&&(AD4>1000))
								{
									UP_delay_ms(200);
									move(400,400);	
									UP_delay_ms(300);
									break;
								}
								else
								{
									move(-400,400);	
									UP_delay_ms(2);
								}
						}
						break;
						case 17:	//��̨�£��󷽺��Ҳ����̨����������û��⵽
						move(0,0);	
						UP_delay_ms(200);
						while(1)
						{	
							AD1 = UP_ADC_GetValue(1); 
							AD6 = UP_ADC_GetValue(6);
							AD4 = UP_ADC_GetValue(4);
							if((AD1<1000)&&(AD6<160)&&(AD4>1000))
								{
									UP_delay_ms(200);
									move(400,400);	
									UP_delay_ms(300);
									break;
								}
								else
								{
									move(400,-500);	
									UP_delay_ms(2);
								}
						}
						break;
					case 18:	//��̨�£��󷽺�������̨����������û��⵽
						move(0,0);	
						UP_delay_ms(200);
						while(1)
						{	
							AD1 = UP_ADC_GetValue(1); 
							AD6 = UP_ADC_GetValue(6);
							AD4 = UP_ADC_GetValue(4);
							if((AD1<1000)&&(AD6<160)&&(AD4>1000))
								{
									UP_delay_ms(200);
									move(400,400);	
									UP_delay_ms(300);
									break;
								}
								else
								{
									move(-420,350);	
									UP_delay_ms(2);
								}
						}
						break;
					case 101:	//����
						UP_delay_ms(10);
						break;

				}
				break;
				
			case 1:	//��̨��
				na=0;
				nb=0;
				nEdge = Edge();	//����Ե

				//UP_LCD_ClearScreen();
			
			
			
				UP_LCD_ShowInt(2, 2, nEdge);
				switch(nEdge)
				{
					case 0:	//û�м�⵽��Ե
					nEnemy = Enemy();	//������
					//UP_LCD_ClearScreen();
				
					UP_LCD_ShowInt(3, 3, nEnemy);
					switch(nEnemy)
						{
							case 0:	//�޵���
								move(400,400);	
								UP_delay_ms(10);
								break;
							case 1:	//ǰ��qizi
								move(800,800);	
								UP_delay_ms(20);
								break;
							case 2:	//�Ҳ��е���
								move(-400,-400);	
								UP_delay_ms(200);
								move(400,-400);	
								UP_delay_ms(300);
								break;
							case 3:	//���е���
								move(-400,400);	
								UP_delay_ms(800);
								break;
							case 4:	//����е���
								move(-400,-400);	
								UP_delay_ms(200);
								move(-400,400);	
								UP_delay_ms(300);
								break;
							case 11:	//ǰ����⵽����
								move(800,800);	
								UP_delay_ms(20);
								break;
							case 103:	//����
								move(400,400);	
								UP_delay_ms(10);
								break;
						}

						break;
					case 1:	//��ǰ��⵽��Ե
						move(-400,-400);	
						UP_delay_ms(400);
						move(400,-400);	
						UP_delay_ms(300);
						break;
					case 2:	//��ǰ��⵽��Ե
						move(-400,-400);	
						UP_delay_ms(400);
						move(400,-400);	
						UP_delay_ms(400);
						break;
					case 3:	//�Һ��⵽��Ե
						move(400,400);	
						UP_delay_ms(500);
						move(400,-400);	
						UP_delay_ms(500);
						break;
					case 4:	//����⵽��Ե
						move(400,400);	
						UP_delay_ms(500);
						move(400,-400);	
						UP_delay_ms(500);
						break;
					case 5:	//ǰ��������⵽��Ե

						move(-500,-500);	
						UP_delay_ms(700);
						move(500,-500);	
						UP_delay_ms(300);
					
						break;
// 					case 5:	//ǰ��������⵽��Ե
// 						nc++;
// 						move(-500,-500);	
// 						UP_delay_ms(700);
// 						move((40*nc),-(40*nc));	
// 						UP_delay_ms(500);
// 						if (nc==15)
// 						{
// 							nc=8;
// 						}
// 						break;
					case 6:	//��������⵽��Ե
						move(500,500);	
						UP_delay_ms(500);
						break;
					case 7:	//���������⵽��Ե
						move(500,-400);	
						UP_delay_ms(500);
						move(400,400);	
						UP_delay_ms(300);
						break;
					case 8:	//�Ҳ�������⵽��Ե
						move(-400,500);	
						UP_delay_ms(500);
						move(400,400);	
						UP_delay_ms(300);
						break;
					case 9:	//��ǳǰ�ڵ���
						nd++;
						if (nd>20)
						{
							nd=0;
							move(0,0);	
							UP_delay_ms(10);
							move(-500,-500);	
							UP_delay_ms(200);
							qding();
							move(-500,-500);	
							UP_delay_ms(800);
							zhong();
							move(-500,-500);	
							UP_delay_ms(500);
							move(500,-500);	
							UP_delay_ms(300);
							move(0,0);	
							UP_delay_ms(100);
						}
						else
						{
							UP_delay_ms(20);
						}
						
						
						break;
					case 10:	//��ǳǰ������
						ne++;
						if (ne>20)
						{
							ne=0;
							move(0,0);	
							UP_delay_ms(10);
							move(500,500);	
							UP_delay_ms(200);
							hding();
							move(500,500);	
							UP_delay_ms(800);
							zhong();
							move(500,500);	
							UP_delay_ms(400);
							move(0,0);	
							UP_delay_ms(100);
						}
						else
						{
							UP_delay_ms(20);
						}
						break;
					case 102:	//����
						move(500,500);
						UP_delay_ms(10);
						break;

				}
						break;
				case 3://��ǳ�������̨�Ҳ��ڵ���
					na++;
					if (na==350)
					{
						move(-500,500);	
						UP_CDS_SetAngle(5, 1000, 800);//���֧��
						UP_CDS_SetAngle(7, 24, 800);
						//UP_CDS_SetAngle(6, 24, 800);//�Ҳ�֧��
						//UP_CDS_SetAngle(8, 1000, 800);
						UP_delay_ms(800);
						zhong();
						UP_delay_ms(600);
						na=0;
					}
					else 
					{
						UP_delay_ms(1);
					}
					break;
				case 4://��ǳ�Ҳ�����̨����ڵ���
					na++;
					if(na==350)
					{	
						move(500,-500);	
						//UP_CDS_SetAngle(5, 1000, 800);//���֧��
						//UP_CDS_SetAngle(7, 24, 800);
						UP_CDS_SetAngle(6, 24, 800);//�Ҳ�֧��
						UP_CDS_SetAngle(8, 1000, 800);
						UP_delay_ms(800);
						zhong();
						UP_delay_ms(600);
						na=0;
					}
					else 
					{
						UP_delay_ms(1);
					}
					break;
		}
}*/
}

