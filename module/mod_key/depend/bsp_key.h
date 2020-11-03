//++++++++++++++++++++++++++++++start+++++++++++++++++++++++++++++++++++++++++++
#ifndef _BSP_KEY_H
#define _BSP_KEY_H
//------------------------------E N D-------------------------------------------
#include ".\SnailDataTypedef.h"

#define MAX_KEY_GROUP					1

typedef struct
{
	unsigned int (*bsp_scan)(unsigned int *read_keynumber);
}bsp_keyscan_function_t;


//++++++++++++++++++++++++++++++start+++++++++++++++++++++++++++++++++++++++++++
//组合键
#define  KeyGroupBit0     0x0100   
#define  KeyGroupBit1     0x0200   
#define  KeyGroupBit2     0x0400   
#define  KeyGroupBit3     0x0800   
#define  NOCONTINUE       0xffff   
//------------------------------E N D-------------------------------------------

//++++++++++++++++++++++++++++++start+++++++++++++++++++++++++++++++++++++++++++
//独立键
#define  KeyNull          0x0000
#define  KeyAloneBit0     0x0001    
#define  KeyAloneBit1     0x0002  
#define  KeyAloneBit2     0x0004  
#define  KeyAloneBit3     0x0008  
#define  KeyAloneBit4     0x0010
#define  KeyAloneBit5     0x0020  
#define  KeyAloneBit6     0x0040  
#define  KeyAloneBit7     0x0080  
#define  KeyAloneBit8     0x0100  
#define  KeyAloneBit9     0x0200  
#define  KeyAloneBit10    0x0400  
#define  KeyAloneBit11    0x0800  
#define  KeyAloneBit12    0x1000  
#define  KeyAloneBit13    0x2000  
#define  KeyAloneBit14    0x4000  
#define  KeyAloneBit15    0x8000  

//------------------------------E N D-------------------------------------------

/*****************************************************************************
按键地址定义*/

//主控界面
#define REG_KEY_HOT_SWITCH				0x5500
#define REG_KEY_SETTING					0x5501
#define REG_KEY_TEMP_ADD				0x5502
#define REG_KEY_TEMP_SUB				0x5503
#define REG_KEY_HUMIDITY_ADD			0x5504
#define REG_KEY_HUMIDITY_SUB			0x5505
#define REG_KEY_MODE					0x5506
#define REG_KEY_AIR_MODE				0x5507
#define REG_KEY_WIND_SWITCH				0x5508
#define REG_KEY_POWER_ONOFF				0x5509
#define REG_KEY_POWEROFF_SURE			0x550A
#define REG_KEY_POWEROFF_CANCEL			0x550B
#define REG_KEY_GOTO_GREEN_SCREEN		0x550C
#define REG_KEY_POWERON					0x550D

//设置界面
#define REG_KEY_SET_WIFI				0x5510
#define REG_KEY_SET_TIMING				0x5511
#define REG_KEY_SET_FILTER				0x5512
#define REG_KEY_SET_TIME				0x5513
#define REG_KEY_SET_HIGHSET				0x5514
#define REG_KEY_SET_AUTO				0x5515
#define REG_KEY_SET_ABOUT				0x5516
#define REG_KEY_SET_OTHER				0x5517
#define REG_KEY_SET_BACK				0x5518

//++++++++++++++++++++++++++++++start+++++++++++++++++++++++++++++++++++++++++++
//function
//名称: bsp_getKey 
//功能: 获取按键状态
//入口:  <<---------------------------------------按键编号0-7号，具体看使用到几个按键
//出口:  ---------------------------------------->BN_TRUE:有按键
//uint8_t bsp_getkey(uint8_t _in_keyNum);
INT16U keyscan(void);
void keyscan_fanset(INT16U *out_key_number);

//------------------------------E N D-------------------------------------------





//++++++++++++++++++++++++++++++start+++++++++++++++++++++++++++++++++++++++++++
//init
//名称: BSP_KeyHardWares_Configure
//功能: 按键初始化
//入口: 无
//出口:  ---------------------------------------->组合键指针
//INT16U* bsp_key_init(void);
//------------------------------E N D-------------------------------------------


INT16U* bsp_key_init(void);

void keyscan_1(INT16U *out_key_number);

extern bsp_keyscan_function_t get_key2_bsp_array[MAX_KEY_GROUP];
#endif

//-----------------------BSP_Keyboard.h--END------------------------------------
