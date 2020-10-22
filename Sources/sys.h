/******************************************************************************
文 件 名   : sys.h
版 本 号   : V1.0
作    者   : pinot
生成日期   : 2020年04月13日
功能描述   : 系统寄存器配置相关
修改历史   :
日    期   :
作    者   :
修改内容   :
******************************************************************************/

#ifndef _SYS_H_
#define _SYS_H_

/*****************************************************************************
系统库*/

/*****************************************************************************
自定义头文件*/
#include "T5LOS8051.H"

/*****************************************************************************
宏定义变量*/
#ifndef uint8_t
typedef unsigned char uint8_t;
#endif
#ifndef uint16_t
typedef unsigned short uint16_t;
#endif
#ifndef uint32_t
typedef unsigned int uint32_t;
#endif
#ifndef int8_t
typedef char int8_t;
#endif
#ifndef int16_t
typedef short int16_t;
#endif
#ifndef int32_t
typedef int int32_t;
#endif
#ifndef long32_t
typedef long int long32_t;
#endif
#ifndef ulong32_t
typedef unsigned long int ulong32_t;
#endif

typedef unsigned char   u8;
typedef unsigned short  u16;
typedef unsigned long   u32;
typedef char            s8;
typedef short           s16;
typedef long            s32;

typedef struct
{
	u8 year;
	u8 month;
	u8 day;
	u8 week;
	u8 hour;
	u8 min;
	u8 sec;
	u8 res;
}rtc_time_t;


#define NULL                  ((void *)0)           /* 数据NULL */
#define FOSC                  (206438400UL)         /* T5L主频=晶体频率(11.0592M)*56/3 */
#define T1MS                  (65536-FOSC/12/1000)  /* 1MS定时器 */
//#define T_1US				  (65536-FOSC/12/1000000)

/*****************************************************************************
宏定义函数*/
#define WDT_ON()  MUX_SEL|=0x02         /******开启看门狗*********/
#define WDT_OFF() MUX_SEL&=0xFD         /******关闭看门狗*********/
#define WDT_RST() MUX_SEL|=0x01         /******喂狗*********/

/*****************************************
*			云变量地址宏定义              *
*****************************************/

#define		MODE_EEPROM				0x2600
#define		FAN_EEPROM				0x2601
#define		TIMER_SWITCH_EEPROM		0x2602
#define		TIME_CONTROL_EEPROM		0x2603
#define 	NOVOICE_EEPROM			0x2604
#define 	LIGHTSTATE_EEPROM		0x2605

//模式 风量 风速 定时开关 时空设置数据 静音状态 常亮状态

/*****************************************
*	    系统接口变量地址宏定义            *
*****************************************/
#define		NOR_FLASH				0x0008
#define		SOFT_VERSION			0x000F
#define		RTC						0x0010
#define		PIC_NOW					0x0014
#define		TP_STATUS				0x0016
#define		LED_NOW					0x0031
#define		AD_VALUE				0x0032
#define		LED_CONFIG				0x0082
#define		PIC_SET					0x0084
#define 	RTC_Set					0x009C
#define 	RTC_Set_Internet		0xF430


/*****************************************
*	     NORFLASH变量地址宏定义           *
*****************************************/
#define 	MAGIC_NUMBER			0x25E0
#define		NOR_FLASH_START			0x25E0
#define		RTC_TIME_SAVE			0x25F0

/*****************************************************************************
对外函数声明*/
void InitCPU(void);                    /* 寄存器配置初始化 */
//void DelayUs(uint16_t n);
void DelayMs(uint16_t n);
void Read_Nor_Flash(void);
void Write_Nor_Flash(void);

extern u8 read_flash_status[8];
extern u16 debug_flash;
extern rtc_time_t rtc_time;

void RTC_init(void);
void system_parm_init(void);

void init_rtc(void);
void rdtime(void);
void set_rtc(unsigned char year,unsigned char month,unsigned char day,unsigned char hour,unsigned char minute);





#endif
