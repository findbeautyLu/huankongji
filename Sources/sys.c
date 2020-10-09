/******************************************************************************
* �� �� ��   : sys.c
* �� �� ��   : V1.0
* ��    ��   : pinot
* ��������   : 2020��04��13��
* ��������   : ��ʼ��T5L ASIC �ļĴ���
* �޸���ʷ   :
* ��    ��   :
* ��    ��   :
* �޸�����   :
******************************************************************************/

/*****************************************************************************
�Զ���ͷ�ļ�*/
#include "sys.h"
#include "uart.h"
#include "timer.h"
#include "dgus.h"


/*****************************************************************************
ȫ�ֱ���*/

//��дNor Flash����
u8 code read_flash[8]={0x5A,0x00,0x10,0x00,0x25,0xE0,0x01,0x20};
u8 code write_flash[8]={0xA5,0x00,0x10,0x00,0x25,0xE0,0x01,0x20};
//��дNor Flash���ѯ״̬
u8 read_flash_status[8]={0};

//ħ����nor flash��ȡ��־λ
u16 magic_number=0;

const u8 code time_set_init[6]={19,5,1,12,00,05};

//ʱ��У׼
u8 time_calibra[8]={0};

u16 debug_flash = 0;
rtc_time_t rtc_time;


/*****************************************************************************
��ʱus*//*������T=1/206438400*/
//void DelayUs(uint16_t n)
//{
//  uint16_t i,j;
//  for(i=0;i<n;i++)
//    for(j=0;j<15;j++);
//}
/*****************************************************************************
��ʱms*/



void DelayMs(uint16_t n)
{
  uint16_t i,j;
  for(i=0;i<n;i++)
    for(j=0;j<7400;j++);
}

/*****************************************************************************
��ʼ��T5L�������õļĴ���*/
//void InitCFG(void)
//{
//  CKCON      = 0x00;
//  T2CON      = 0x70;
//  DPC        = 0x00;
//  PAGESEL    = 0x01;
//  D_PAGESEL  = 0x02;
//  MUX_SEL    = 0x60;
//  PORTDRV    = 0x01;
//  RAMMODE    = 0x00;
//}

/*****************************************************************************
�ж�����*/
void InitInt(void)
{
  IEN0       = 0x00;                     /*�ر������ж�*/
  IEN1       = 0x00;
  IEN2       = 0x00;
  IP0        = 0x00;                     /*�ж����ȼ�Ĭ��*/
  IP1        = 0x00;
}
/*****************************************************************************
GPIO���*/
void InitGPIO(void)
{
  PORTDRV    = 0x03;                     /*IO�����ģʽ��������������,0x03=32mA*/
  P0MDOUT    = 0x03;                     /*����P0_0��P0_1�����*/
  P1MDOUT    = 0x03;                     /*����P1_0��P1_1�����*/
  P2MDOUT    = 0x00;
  P3MDOUT    = 0x00;
  P0         = 0x00;
  P1         = 0x00;
  P2         = 0x00;
  P3         = 0x00;
}
void EX0_ISR_PC(void)    interrupt 0
{
    EA=0;

    EA=1;
}
void EX1_ISR_PC(void)    interrupt 2
{
    EA=0;

    EA=1;
}
/*****************************************************************************
��ʼ��T5L ASIC*/
void InitCPU(void)
{
  EA=0;
//  InitCFG();      /*��Ϊ��A51�����ļ���ʼ��*/
  InitInt();
  InitGPIO();
  InitUart();
  InitTimer();
  WDT_ON();
  EA=1;
}

void delay_ms(u16 n)
{
    timecount=n;
    while(timecount);   
}

//**********************RX8130�ӿڳ���SDA 10K������3.3V**************
//�ϵ�ʱ����һ��initrtc()��Ȼ��0.5��������һ��rdtime()��ȡʱ�䵽DGUS��Ӧϵͳ�ӿ�

sbit RTC_SDA = P3^3		;
sbit RTC_SCL = P3^2		;

void SDA_IN(void)
{	
	P3MDOUT=P3MDOUT&0xF7;
}

void SDA_OUT(void)
{   
	P3MDOUT=P3MDOUT|0x0C;
}

//delay t uS
void delayus(unsigned char t)
{	
	char i;
	while(t)
	{	
		for(i=0;i<17;i++)
		{
			i=i;
		}
		t--;
	}
}

void i2cstart(void)
{	
	SDA_OUT();
	RTC_SDA=1;
	RTC_SCL=1;
	delayus(15);
	RTC_SDA=0;
	delayus(15);
	RTC_SCL=0;
	delayus(15);
}

void i2cstop(void)
{	
	SDA_OUT();
	RTC_SDA=0;
	RTC_SCL=1;
	delayus(15);
	RTC_SDA=1;
	delayus(15);
	SDA_IN();
}

void mack(void)
{	
	SDA_OUT();
	RTC_SDA=0;
	delayus(5);
	RTC_SCL=1;
	delayus(5);
	RTC_SCL=0;
	delayus(5);
}

void mnak(void)
{	SDA_OUT();
	RTC_SDA=1;
	delayus(5);
	RTC_SCL=1;
	delayus(5);
	RTC_SCL=0;
	delayus(5);
}

void cack(void)
{	
	unsigned char i;
	SDA_IN();
	RTC_SDA=1;
	delayus(5);
	RTC_SCL=1;
	delayus(5);
	for(i=0;i<50;i++)
	{   
		if(!RTC_SDA)
		break;
		delayus(5);
	}
	RTC_SCL=0;
	delayus(5);
	SDA_OUT();
}

		//I2C д��1���ֽ�
void i2cbw(unsigned char dat)
{	
	char i;
	SDA_OUT();
	for(i=0;i<8;i++)
	{	
	if(dat&0x80) 
		RTC_SDA=1;
	else 
		RTC_SDA=0;
	dat=(dat<<1);
	delayus(5);
	RTC_SCL=1;
	delayus(5);
	RTC_SCL=0;
	delayus(5);}
	cack();
}

		//i2c ��ȡ1���ֽ�����
unsigned char i2cbr(void)
{	
	char i;
	unsigned char dat;
	SDA_IN();
	for(i=0;i<8;i++)
	{	
	delayus(5);
	RTC_SCL=1;
	delayus(5);
	dat=(dat<<1);
	if(RTC_SDA) 
		dat=dat|0x01;
	else 
		dat=dat&0xFE;
	RTC_SCL=0;
	delayus(5);}
	return(dat);
}

		//���8130��û�е��磬�������ʼ��8130������ʱ��Ϊ2017.01.01 ����һ 00:00:00
void init_rtc(void)
{	unsigned char i;
//�����û�е���
	i2cstart();
	i2cbw(0x64);
	i2cbw(0x1d);
	i2cstop();
	i2cstart();
	i2cbw(0x65);
	i=i2cbr();
	mack();
	i2cbr();
	mnak();
	i2cstop();
	if((i&0x02)==0x02)
	{	//��������ʱ��
		i2cstart();		//30=00
		i2cbw(0x64);
		i2cbw(0x30);
		i2cbw(0x00);
		i2cstop();
		i2cstart();		//1C-1F=48 00 40 10
		i2cbw(0x64);
		i2cbw(0x1C);
		i2cbw(0x48);
		i2cbw(0x00);
		i2cbw(0x40);
		i2cbw(0x10);
		i2cstop();
		i2cstart();		//10-16=RTC����ֵ BCD��ʽ
		i2cbw(0x64);
		i2cbw(0x10);
		i2cbw(0x00);	//��
		i2cbw(0x00);	//��
		i2cbw(0x00);	//ʱ
		i2cbw(0x01);	//����
		i2cbw(0x01);	//��
		i2cbw(0x01);	//��
		i2cbw(0x17);	//��
		i2cstop();
		i2cstart();		//1E-1F 00 10
		i2cbw(0x64);
		i2cbw(0x1E);
		i2cbw(0x00);	
		i2cbw(0x10);			
		i2cstop();
	}
}

void set_rtc(unsigned char year,unsigned char month,unsigned char day,unsigned char hour,unsigned char minute)
{
	i2cstart();		//30=00
	i2cbw(0x64);
	i2cbw(0x30);
	i2cbw(0x00);
	i2cstop();
	i2cstart();		//1C-1F=48 00 40 10
	i2cbw(0x64);
	i2cbw(0x1C);
	i2cbw(0x48);
	i2cbw(0x00);
	i2cbw(0x40);
	i2cbw(0x10);
	i2cstop();
	i2cstart();		//10-16=RTC����ֵ BCD��ʽ
	i2cbw(0x64);
	i2cbw(0x10);
	i2cbw(0x00);	//��
	i2cbw(minute);	//��
	i2cbw(hour);	//ʱ
	i2cbw(0x01);	//����
	i2cbw(day);	//��
	i2cbw(month);	//��
	i2cbw(year);	//��
	i2cstop();
	i2cstart();		//1E-1F 00 10
	i2cbw(0x64);
	i2cbw(0x1E);
	i2cbw(0x00);	
	i2cbw(0x10);			
	i2cstop();
}
//��RTC��ȡ������д��DGUS��Ӧ�ı����ռ䣬��������ÿ0.5�����һ��
void rdtime(void)
{	unsigned char rtcdata[8];
	unsigned char i,n,m;
	i2cstart();
	i2cbw(0x64);
	i2cbw(0x10);
	i2cstop();
	i2cstart();
	i2cbw(0x65);
	for(i=6;i>0;i--)
	{	
		rtcdata[i]=i2cbr();
		mack();
	}
	rtcdata[0]=i2cbr();
	mnak();
	i2cstop();
	for(i=0;i<3;i++)	//������ת����HEX
	{	
		n=rtcdata[i]/16;
		m=rtcdata[i]%16;
		rtcdata[i]=n*10+m;
	}
	for(i=4;i<7;i++)	//ʱ����ת����HEX
	{	
		n=rtcdata[i]/16;
		m=rtcdata[i]%16;
		rtcdata[i]=n*10+m;
	}
	//�������ڵ����ݸ�ʽ
	n=0;
	m=rtcdata[3];
	for(i=0;i<7;i++)
	{   
		if(m&0x01)  
			break;
		n++;
		m=(m>>1);
	}
	rtcdata[3]=n;
	rtcdata[7]=0x00;
	WriteDGUS(0x0010,rtcdata,8);	//д��DGUS�����ռ�
}


/*****************************************************************************
 �� �� ��  : void Read_Nor_Flash(void)
 ��������  : ��nor flashϵͳ�������̶�Ϊ25E0-26FF��ֵ
 �������  :	 
 �������  : 
 �޸���ʷ  :
  1.��    ��   : 2019��5��2��
    ��    ��   : chengjing
    �޸�����   : ����
*****************************************************************************/
void Read_Nor_Flash(void)
{	
	WriteDGUS(NOR_FLASH,(u8*)read_flash,8);
	do
	{
		delay_ms(5);
		ReadDGUS(NOR_FLASH,(u8*)read_flash_status,8);
	}while(read_flash_status[0]!=0);
}

void Write_Nor_Flash(void)
{
	WriteDGUS(NOR_FLASH,(u8*)write_flash,8);
	do
	{
		delay_ms(5);
		ReadDGUS(NOR_FLASH,(u8*)read_flash_status,8);		
	}while(read_flash_status[0]!=0);
}

void parm_reset_init(void)
{
	u16 mode = 62;
	u16 fan = 48;//WIND_DIS_MIN
	WriteDGUS(MODE_EEPROM,(u8*)&mode,2);
	WriteDGUS(FAN_EEPROM,(u8*)&fan,2);
}

void system_parm_init(void)
{
	//����22
	u16 key1mes = 1;
	u16 key2mes = 2;
	u16 key3mes = 3;
	WriteDGUS(0x5610,(u8*)&key1mes,2);
	WriteDGUS(0x5620,(u8*)&key2mes,2);
	WriteDGUS(0x5630,(u8*)&key3mes,2);
	
	Read_Nor_Flash();		//��Nor Flash
	delay_ms(5);
	ReadDGUS(MAGIC_NUMBER,(u8*)&magic_number,2);
	if(magic_number!=0x5AA5)
	{
		magic_number=0x5AA5;
		WriteDGUS(MAGIC_NUMBER,(u8*)&magic_number,2);
		parm_reset_init();
		Write_Nor_Flash();
		delay_ms(5);
	}
	
}

