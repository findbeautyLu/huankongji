
/*******************************************************************************
*
*	模块名称 : BSP按键模块
*	文件名称 : BSP_Keyboard.c
*	版    本 : V1.0
*	说    明 : 1、模块独立，不访问其他任何模块
*                  2、供Mod_KeyBoard
                   3、仅做硬件配置和组合键配置
*	修改记录 :
*		版本号  日期        作者     说明
*		V1.0   2018-07-6  zhoujh  正式发布
*	Copyright (C), 2015-2020,   menredGroup
*            
*******************************************************************************/

//++++++++++++++++++++++++++++++start+++++++++++++++++++++++++++++++++++++++++++
#include ".\SnailDataTypedef.h"
#include ".\bsp_key.h"

#include ".\Sources\dgus.h"


//#include ".\SnailMacro.h"
//#include "intrinsics.h"

//#include "DeviceSelect.h"

void bsp_key_configure(void)
{
		
	;
}

//++++++++++++++++++++++++++++++start+++++++++++++++++++++++++++++++++++++++++++
//组合键设置函数，KeyGroupAndAloneMap[4]存储配置好的组合键键值************
static INT16U BSP_KeyGroupAndAloneMap[4];
void BSP_SetKeyGroupArray(INT8U KeyGroupNumber,INT16U GroupBits)
{    
    if(KeyGroupNumber < 4)
    {
        BSP_KeyGroupAndAloneMap[KeyGroupNumber]=GroupBits;
    }
    else
    {
        while(1);
    }
}
//------------------------------E N D-------------------------------------------


//++++++++++++++++++++++++++++++start+++++++++++++++++++++++++++++++++++++++++++
//******按键硬件配置为上拉输入，并启用两组组合键，并返回组合键数组指针**********
INT16U *bsp_key_init(void)
{   
    bsp_key_configure(); 
    BSP_SetKeyGroupArray(0,KeyAloneBit1|KeyAloneBit3); //+ -童锁
    BSP_SetKeyGroupArray(1,KeyAloneBit0|KeyAloneBit4); //菜单和-清理滤网
    BSP_SetKeyGroupArray(2,KeyAloneBit1|KeyAloneBit4); //WIFI 连接  
    BSP_SetKeyGroupArray(3,0);                         //未启用输入0   
    return (BSP_KeyGroupAndAloneMap);
}
//------------------------------E N D-------------------------------------------


//++++++++++++++++++++++++++++++start+++++++++++++++++++++++++++++++++++++++++++
//获取按键

//------------------------------E N D-------------------------------------------
INT8U getkey(INT16U read_addr, INT16U Len)
{
	INT8U readbuf[4];
	ReadDGUS(read_addr,readbuf,Len);	
	if(readbuf[1] == 0x01 || readbuf[1] == 0x02)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

/*INT16U keyscan(void)
{   
	uint8_t i;
	INT16U keyline = 0;
	INT16U keyadress[] = {REG_KEY_POWER,REG_KEY_POWEROFF,REG_KEY_TEMP_ADD,REG_KEY_TEMP_SUB,
						  REG_KEY_HUMIDITY_ADD,REG_KEY_HUMIDITY_SUB,REG_KEY_MODE,REG_KEY_SET_UP_STATE,
						  REG_KEY_WIND_SPEED,REG_KEY_POWEROFF_SURE,REG_KEY_POWEROFF_CANCEL};
	for(i = 0; i < (sizeof(keyadress)/sizeof(keyadress[0])); i++)
	{
		if(getkey(keyadress[i],2))
		{
			keyline |= (KeyAloneBit0 << i);
			break;
		}
	}

 	return keyline;
}*/

/*void keyscan_fanset(INT16U *out_key_number)
{
	uint8_t i;
	INT16U keyline = 0;
	INT16U keyadress[] = {REG_PAGE62_FANSET_FANMOTOR_UP,REG_PAGE62_FANSET_FANMOTOR_DOWN,REG_PAGE62_FANSET_FANMOTOR_TYPE_UP,
						  REG_PAGE62_FANSET_FANMOTOR_TYPE_DOWN,REG_PAGE62_FANSET_FANMOTOR_HIGHSPEED_UP,REG_PAGE62_FANSET_FANMOTOR_HIGHSPEED_DOWN,
						  REG_PAGE62_FANSET_FANMOTOR_MIDSPEED_UP,REG_PAGE62_FANSET_FANMOTOR_MIDSPEED_DOWN,REG_PAGE62_FANSET_FANMOTOR_LOWSPEED_UP,
						  REG_PAGE62_FANSET_FANMOTOR_LOWSPEED_DOWN,REG_PAGE62_FANSET_REMOVEWET_UP,REG_PAGE62_FANSET_REMOVEWET_DOWN,
						  REG_PAGE62_FANSET_485ADRESS_UP,REG_PAGE62_FANSET_485ADRESS_DOWN,REG_PAGE62_FANSET_BAUDRATE_UP,
						  REG_PAGE62_FANSET_BAUDRATE_DOWN};
	for(i = 0; i < (sizeof(keyadress)/sizeof(keyadress[0])); i++)
	{
		if(getkey(keyadress[i],2))
		{
			keyline |= (KeyAloneBit0 << i);
			break;
		}
	}

	*out_key_number = keyline;
}*/

//计划bsp层将所有函数封装进一个数组作为接口出去供mde层调用
//mde层的 mde_cfg()将变量数据和bsp层关联起来供app层调用


void keyscan_1(INT16U *out_key_number)
{
	uint8_t i;
	INT16U keyline = 0;
	INT16U keyadress[] = {	REG_KEY_HOT_SWITCH  	,
	 						REG_KEY_SETTING  		,
	 						REG_KEY_TEMP_ADD  		,
	 						REG_KEY_TEMP_SUB  		,
	 						REG_KEY_HUMIDITY_ADD  	,
	 						REG_KEY_HUMIDITY_SUB  	,
	 						REG_KEY_MODE  			,
	 						REG_KEY_AIR_MODE  		,
	 						REG_KEY_WIND_SWITCH  	,
	 						REG_KEY_POWER_ONOFF  	,
	 						REG_KEY_POWEROFF_SURE 	,
	 						REG_KEY_POWEROFF_CANCEL	,
							REG_KEY_GOTO_GREEN_SCREEN,
							REG_KEY_POWERON			,
							REG_KEY_GREEN_CHANGE	,
							REG_KEY_GOTO_MAIN_CONTROL
	 						};

	for(i = 0; i < (sizeof(keyadress)/sizeof(keyadress[0])); i++)
	{
		if(getkey(keyadress[i],2))
		{
			keyline |= (KeyAloneBit0 << i);
			break;
		}
	}

	*out_key_number = keyline;
}

void keyscan_2(INT16U *out_key_number)
{
	uint8_t i;
	INT16U keyline = 0;
	INT16U keyadress[] = {	REG_KEY_SET_WIFI ,
							REG_KEY_SET_TIMING ,
							REG_KEY_SET_FILTER ,
							REG_KEY_SET_TIME ,
							REG_KEY_SET_HIGHSET,
							REG_KEY_SET_AUTO,
							REG_KEY_SET_ABOUT,
							REG_KEY_SET_OTHER,
							REG_KEY_SET_BACK
	 						};
	
	for(i = 0; i < (sizeof(keyadress)/sizeof(keyadress[0])); i++)
	{
		if(getkey(keyadress[i],2))
		{
			keyline |= (KeyAloneBit0 << i);
			break;
		}
	}

	*out_key_number = keyline;
}

void keyscan_3(INT16U *out_key_number)
{
	uint8_t i;
	INT16U keyline = 0;
	INT16U keyadress[] = {	REG_KEY_SET_YEAR_UP ,
							REG_KEY_SET_YEAR_DOWN ,
							REG_KEY_SET_MONTH_UP ,
							REG_KEY_SET_MONTH_DOWN ,
							REG_KEY_SET_DAY_UP,
							REG_KEY_SET_DAY_DOWN,
							REG_KEY_SET_HOUR_UP,
							REG_KEY_SET_HOUR_DOWN,
							REG_KEY_SET_MINTUE_UP,
							REG_KEY_SET_MINTUE_DOWN,
							REG_KEY_SET_SURE_DOWN
	 						};
	
	for(i = 0; i < (sizeof(keyadress)/sizeof(keyadress[0])); i++)
	{
		if(getkey(keyadress[i],2))
		{
			keyline |= (KeyAloneBit0 << i);
			break;
		}
	}

	*out_key_number = keyline;
}

//bsp_keyscan_function_t get_key2_bsp_array[MAX_KEY_GROUP] ={keyscan_1};//keyscan_2


//-----------------------BSP_Keyboard.c--END------------------------------------
