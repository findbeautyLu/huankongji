/******************************************************************************
* 文 件 名   : uart.c
* 版 本 号   : V1.0
* 作    者   : pinot
* 生成日期   : 2020年04月13日
* 功能描述   : UART2345串口读写
* 修改历史   :
* 日    期   :
* 作    者   :
* 修改内容   :
******************************************************************************/

/*****************************************************************************
系统库*/
#include "string.h"

/*****************************************************************************
自定义头文件*/
#include "uart.h"

/********************************
*  串口接受缓存区
*  缓存区大小可以根据实际进行修改
*  接收到缓存数据请尽快处理，否者
*  下一条数据会往尾端增加
********************************/
uint8_t uart2_busy = 0;
uint16_t uart2_rx_count = 0;
uint8_t xdata Uart2_Rx[UART2_MAX_LEN];

uint8_t uart3_busy = 0;
uint16_t uart3_rx_count = 0;
uint8_t xdata Uart3_Rx[UART3_MAX_LEN];

uint16_t uart4_rx_count=0;
uint8_t xdata Uart4_Rx[UART4_MAX_LEN];

uint16_t uart5_rx_count=0;
uint8_t xdata Uart5_Rx[UART5_MAX_LEN];

/*****************************************************************************
串口2配置*/
void Uart2Init(void)
{
  P0MDOUT    |= 0x10;
  MUX_SEL    |= 0x40;
  uart2_busy = 0;
  uart2_rx_count = 0;
  ADCON      = 0x80;        /*0x80=使用SREL0H:L*/
  SCON0      = 0x50;        /*方式1:10位UART*/
//  PCON      &= 0x7F;        /*.7=SMOD,波特率倍频选择,0=不倍频*/
  SREL0H     = 0x03;        /*1024-FOSC/(64*波特率)*/
  SREL0L     = 0xE4;        /*1024-206438400/(64*115200)*/
  ES0        = 1;
}
/*****************************************************************************
串口2发送字节*/
void Uart2SendByte(uint8_t dat)
{
  while(uart2_busy==1);
  uart2_busy=1;
  SBUF0 = dat;
}
/*****************************************************************************
串口2发送字符串*/
void Uart2SendStr(uint8_t *pstr,uint8_t strlen)
{
  if((NULL == pstr)||(0 == strlen))
  {
    return;
  }
  while(strlen--)
  {
    Uart2SendByte(*pstr);
    pstr++;
  }
}
/*****************************************************************************
串口2接收中断*/
void UART2_ISR_PC(void)    interrupt 4
{
  uint8_t res = 0;
	EA=0;
	if(RI0==1)
	{
		res=SBUF0;
		Uart2_Rx[uart2_rx_count]=res; 
		uart2_rx_count++;
		RI0=0; 
		if (uart2_rx_count >= UART2_MAX_LEN) {
				//防止溢出
				uart2_rx_count = 0;
		}
	}
	if(TI0==1)
	{
		TI0=0;
		uart2_busy=0;
	}
	EA=1;
}

/*****************************************************************************
串口3配置*/
void Uart3Init(void)
{
  P0MDOUT    |= 0x40;
  MUX_SEL    |= 0x20;
  uart3_busy = 0;
  uart3_rx_count = 0;
  SCON1      = 0xD0;
  SREL1H     = 0x03;        /*1024-FOSC/(32*波特率)*/
  SREL1L     = 0xC8;
  IEN2       = 0x01;
}
/*****************************************************************************
串口3发送字节*/
void Uart3SendByte(uint8_t dat)
{
  while(uart3_busy==1);
  uart3_busy=1;
  SBUF1 = dat;
}
//直接写入，不需要中断查询
//{
//  SBUF1 = dat;
//  while((SCON1&0x02)==0);
//  SCON1 &=0xFD;
//  SCON1 &=0xFD;
//}
/*****************************************************************************
串口3发送字符串*/
void Uart3SendStr(uint8_t *pstr,uint8_t strlen)
{
  if((NULL == pstr)||(0 == strlen))
  {
    return;
  }
  while(strlen--)
  {
    Uart3SendByte(*pstr);
    pstr++;
  }  
}
/*****************************************************************************
串口3接收中断*/
void UART3_ISR_PC(void)    interrupt 16
{
  uint8_t res=0;
  EA=0;
  if(SCON1&0x01)
  {
    res=SBUF1;
    Uart3_Rx[uart3_rx_count]=res; 
    uart3_rx_count++;
    SCON1 &= 0xFE;
    SCON1 &= 0xFE;
    if (uart3_rx_count >= UART3_MAX_LEN) {
        //防止溢出
        uart3_rx_count = 0;
		}
  }
  if(SCON1&0x02)
  {
    SCON1&=0xFD;
    SCON1&=0xFD;
    uart3_busy=0;
  }
  EA=1;
}

///*****************************************************************************
//串口4配置*/
void Uart4Init(void)
{
  uart4_rx_count=0;
  SCON2T     = 0x80;        /*开启UART4发送*/
  SCON2R     = 0x80;        /*开启UART4接收*/
  BODE2_DIV_H= 0x0A;        /*FCLK/(8*DIV)*/
  BODE2_DIV_L= 0x80;
  //ES2T=1;
  ES2R=1;
}
/*****************************************************************************
串口4发送字节*/
void Uart4SendByte(uint8_t dat)
{
  SBUF2_TX = dat;    
  while((SCON2T&0x01) == 0); 
  SCON2T &= 0xFE;  
}

void Uart4SendStr(uint8_t *pstr,uint8_t strlen)
{
  if((NULL == pstr)||(0 == strlen))
  {
    return;
  }
  while(strlen--)
  {
    Uart4SendByte(*pstr);
    pstr++;
  }
}
/*****************************************************************************
串口4发送中断*/
void UART4_TX_ISR_PC(void)    interrupt 10
{ 
}
/*****************************************************************************
串口4接收中断*/
void UART4_RX_ISR_PC(void)    interrupt 11
{
  uint8_t res=0;
  EA=0;
  if((SCON2R&0x01)==0x01)
  {
    res=SBUF2_RX;
    Uart4_Rx[uart4_rx_count]=res; 
    uart4_rx_count++;
    SCON2R&=0xFE;
    if (uart4_rx_count >= UART4_MAX_LEN) {
        //防止溢出
        uart4_rx_count = 0;
		}
  }
  EA=1;
}


///*****************************************************************************
//串口5配置*/
sbit controlIo=P1^0;
void Uart5Init(void)
{
  uart5_rx_count=0;
  SCON3T     = 0x80;        /*开启UART5发送*/
  SCON3R     = 0x80;        /*开启UART5接收*/
  BODE3_DIV_H= 0x05;        /*FCLK/(8*DIV)*/
  BODE3_DIV_L= 0x40;
  //ES2T=1;
  ES3R=1;
}
/*****************************************************************************
串口5发送字节*/
void Uart5SendByte(uint8_t dat)
{
  SBUF3_TX = dat;    
  while((SCON3T&0x01) == 0); 
  SCON3T &= 0xFE;
}
/*****************************************************************************
串口5发送字符串*/
void Uart5SendStr(uint8_t *pstr,uint8_t strlen)
{
  if((NULL == pstr)||(0 == strlen))
  {
    return;
  }
  
  P1MDOUT &= (~0x01);//P1.0
  SCON3R &= (~0x80);//
  ES3R=0;
  while(strlen--)
  {
    Uart5SendByte(*pstr);
    pstr++;
  }  
	P1MDOUT |= 0x01;//P1.0
	controlIo=0;
	SCON3R |= (0x80);
	ES3R=1;
}
/*****************************************************************************
串口5发送中断*/
void UART5_TX_ISR_PC(void)    interrupt 12
{ 
}
/*****************************************************************************
串口5接收中断*/
#define DELAY_RX    5
u8 delayTime = 0;

void UART5_RX_ISR_PC(void)    interrupt 13
{
  uint8_t res=0;
  EA=0;
  if((SCON3R&0x01)==0x01)
  {
    res=SBUF3_RX;
		delayTime = DELAY_RX;
    Uart5_Rx[uart5_rx_count]=res; 
    uart5_rx_count++;
    SCON3R&=0xFE;
    if (uart5_rx_count >= UART5_MAX_LEN) {
        //防止溢出
        uart5_rx_count = 0;
		}
  }
  EA=1;
}

/*****************************************************************************
串口总配置*/
void InitUart(void)
{
  Uart2Init();
  Uart3Init();
  Uart4Init();
  Uart5Init();
}

