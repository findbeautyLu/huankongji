/******************************************************************************
* 文 件 名   : handle.c
* 版 本 号   : V1.0
* 作    者   : pinot
* 生成日期   : 2020年04月13日
* 功能描述   : 逻辑处理
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
#include "handle.h"
#include "dgus.h"
#include "uart.h"
#include "timer.h"


/*****************************************************************************
全局变量*/
//内部RAM
uint8_t value0F00[4] = {0};

//外部RAM
uint16_t xdata set_pageid=0;

uint8_t code CUart2[] = "Uart2Init Done!!!";
uint8_t code CUart3[] = "Uart3Init Done!!!";
uint8_t code CUart4[] = "Uart4Init Done!!!";
uint8_t code CUart5[] = "Uart5Init Done!!!";

/*****************************************************************************
控制亮度*/
void SetBlight(uint8_t n)
{
//	uint8_t temp[4]={0};
  WriteDGUS(DHW_LEDCFG,(uint8_t *)&n,sizeof(n));
//	do
//	{
//    DelayMs(5);
//	  ReadDGUS(DHW_LEDNOW,temp,2);//设置亮度与获取到的亮度不一致
//	}while(!(temp[1]==n));
}
/*****************************************************************************
控制伴音*/
void SetVoice(int8_t status)
{
	uint8_t temp[4]={0};
	ReadDGUS(DHW_SYSCFG,temp,sizeof(temp));
	temp[0]=0x5A;
	if(1==status){temp[3]&=0xF7;}
	else if(2==status){temp[3]|=0x08;}
	else{return;}
  WriteDGUS(DHW_SYSCFG,temp,sizeof(temp));
	do
	{
    DelayMs(5);
	  ReadDGUS(DHW_SYSCFG,temp,1);
	}while(temp[0]!=0);
}
/*****************************************************************************
判断按键值是否有上传*/
int8_t GetValue0F00(void)
{
	/*uint8_t cleanData[4]={0};
	ReadDGUS(DHW_0F00,value0F00,sizeof(value0F00));
	if(0x5A == value0F00[0])
	{
		WriteDGUS(DHW_0F00,cleanData,sizeof(cleanData));
		return 1;
	}
	return 0;*/
	//unsigned char writeBuff[2]={0,0};
	//unsigned char writeBuff1[2]={0,0};
	//unsigned int regData = 64;
	//unsigned int regData1 = 50;
	
	//WriteDGUS(0x5070,writeBuff,2);
	unsigned char cleanData[4]={0};
	ReadDGUS(DHW_0F00,value0F00,sizeof(value0F00));

	
	//writeBuff[0] = (unsigned char)(regData>>8);
	//writeBuff[1] = (unsigned char)(regData);
	//writeBuff1[0] = (unsigned char)(regData1>>8);
	//writeBuff1[1] = (unsigned char)(regData1);
	//WriteDGUS(0x5130,writeBuff,2);
	//WriteDGUS(0x5110,writeBuff1,2);
	//WriteDGUS(0x5005,writeBuff,2);
	//WriteDGUS(0x5015,writeBuff1,2);
	if(0x5A == value0F00[0])
	{
		WriteDGUS(DHW_0F00,cleanData,sizeof(cleanData));
		return 1;
	}
	return 0;

}
/*****************************************************************************
串口初次打印*/
void InitUartSend(void)
{
  Uart2SendStr(CUart2,sizeof(CUart2));
  Uart3SendStr(CUart3,sizeof(CUart3));
  Uart4SendStr(CUart4,sizeof(CUart4));
  Uart5SendStr(CUart5,sizeof(CUart5));
}
/*****************************************************************************
跳转指定页面*/
void JumpPage(uint16_t pageId)
{
	uint8_t temp[4]={0x5A,0x01,0,0};
	temp[2]=(uint8_t)(pageId>>8);
	temp[3]=pageId;
  WriteDGUS(DHW_SPAGE,temp,sizeof(temp));
	do
	{
    DelayMs(5);
	  ReadDGUS(DHW_SPAGE,temp,1);
	}while(temp[0]!=0);
}
/*****************************************************************************
按键按压之后处理流程*/
void TouchHandle(void)
{
	uint8_t temp[16]={0};
	uint16_t getDar=0;
  getDar = value0F00[1]<<8|value0F00[2];
	LOG((uint8_t *)&getDar,sizeof(getDar));
	switch(getDar)
	{
		case 1:

		break;
		//
		default:
		break;
	}
}


/*****************************************************************************
主流程*/
void HandleProc(void)
{
		if(GetValue0F00())
		{
		  TouchHandle();
		}
}
