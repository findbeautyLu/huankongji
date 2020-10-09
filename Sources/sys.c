/******************************************************************************
* 文 件 名   : sys.c
* 版 本 号   : V1.0
* 作    者   : pinot
* 生成日期   : 2020年04月13日
* 功能描述   : 初始化T5L ASIC 的寄存器
* 修改历史   :
* 日    期   :
* 作    者   :
* 修改内容   :
******************************************************************************/

/*****************************************************************************
自定义头文件*/
#include "sys.h"
#include "uart.h"
#include "timer.h"
#include "dgus.h"


/*****************************************************************************
全局变量*/

//读写Nor Flash命令
u8 code read_flash[8]={0x5A,0x00,0x10,0x00,0x25,0xE0,0x01,0x20};
u8 code write_flash[8]={0xA5,0x00,0x10,0x00,0x25,0xE0,0x01,0x20};
//读写Nor Flash后查询状态
u8 read_flash_status[8]={0};

//魔数，nor flash读取标志位
u16 magic_number=0;

const u8 code time_set_init[6]={19,5,1,12,00,05};

//时间校准
u8 time_calibra[8]={0};

u16 debug_flash = 0;
rtc_time_t rtc_time;


/*****************************************************************************
延时us*//*振荡周期T=1/206438400*/
//void DelayUs(uint16_t n)
//{
//  uint16_t i,j;
//  for(i=0;i<n;i++)
//    for(j=0;j<15;j++);
//}
/*****************************************************************************
延时ms*/



void DelayMs(uint16_t n)
{
  uint16_t i,j;
  for(i=0;i<n;i++)
    for(j=0;j<7400;j++);
}

/*****************************************************************************
初始化T5L必须配置的寄存器*/
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
中断配置*/
void InitInt(void)
{
  IEN0       = 0x00;                     /*关闭所有中断*/
  IEN1       = 0x00;
  IEN2       = 0x00;
  IP0        = 0x00;                     /*中断优先级默认*/
  IP1        = 0x00;
}
/*****************************************************************************
GPIO输出*/
void InitGPIO(void)
{
  PORTDRV    = 0x03;                     /*IO口输出模式的驱动能力配置,0x03=32mA*/
  P0MDOUT    = 0x03;                     /*开启P0_0和P0_1的输出*/
  P1MDOUT    = 0x03;                     /*开启P1_0和P1_1的输出*/
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
初始化T5L ASIC*/
void InitCPU(void)
{
  EA=0;
//  InitCFG();      /*改为在A51启动文件初始化*/
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

//**********************RX8130接口程序，SDA 10K上拉到3.3V**************
//上电时运行一次initrtc()，然后0.5秒间隔运行一次rdtime()读取时间到DGUS相应系统接口

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

		//I2C 写入1个字节
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

		//i2c 读取1个字节数据
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

		//检查8130有没有掉电，掉电则初始化8130，设置时间为2017.01.01 星期一 00:00:00
void init_rtc(void)
{	unsigned char i;
//检查有没有掉电
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
	{	//重新配置时间
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
		i2cstart();		//10-16=RTC设置值 BCD格式
		i2cbw(0x64);
		i2cbw(0x10);
		i2cbw(0x00);	//秒
		i2cbw(0x00);	//分
		i2cbw(0x00);	//时
		i2cbw(0x01);	//星期
		i2cbw(0x01);	//日
		i2cbw(0x01);	//月
		i2cbw(0x17);	//年
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
	i2cstart();		//10-16=RTC设置值 BCD格式
	i2cbw(0x64);
	i2cbw(0x10);
	i2cbw(0x00);	//秒
	i2cbw(minute);	//分
	i2cbw(hour);	//时
	i2cbw(0x01);	//星期
	i2cbw(day);	//日
	i2cbw(month);	//月
	i2cbw(year);	//年
	i2cstop();
	i2cstart();		//1E-1F 00 10
	i2cbw(0x64);
	i2cbw(0x1E);
	i2cbw(0x00);	
	i2cbw(0x10);			
	i2cstop();
}
//把RTC读取并处理，写到DGUS对应的变量空间，主程序中每0.5秒调用一次
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
	for(i=0;i<3;i++)	//年月日转换成HEX
	{	
		n=rtcdata[i]/16;
		m=rtcdata[i]%16;
		rtcdata[i]=n*10+m;
	}
	for(i=4;i<7;i++)	//时分秒转换成HEX
	{	
		n=rtcdata[i]/16;
		m=rtcdata[i]%16;
		rtcdata[i]=n*10+m;
	}
	//处理星期的数据格式
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
	WriteDGUS(0x0010,rtcdata,8);	//写入DGUS变量空间
}


/*****************************************************************************
 函 数 名  : void Read_Nor_Flash(void)
 功能描述  : 读nor flash系统参数，固定为25E0-26FF的值
 输入参数  :	 
 输出参数  : 
 修改历史  :
  1.日    期   : 2019年5月2日
    作    者   : chengjing
    修改内容   : 创建
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
	//更改22
	u16 key1mes = 1;
	u16 key2mes = 2;
	u16 key3mes = 3;
	WriteDGUS(0x5610,(u8*)&key1mes,2);
	WriteDGUS(0x5620,(u8*)&key2mes,2);
	WriteDGUS(0x5630,(u8*)&key3mes,2);
	
	Read_Nor_Flash();		//读Nor Flash
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

