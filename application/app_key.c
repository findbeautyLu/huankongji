/*******************************************************************************
*
*	模块名称 : APP按键模块
*	文件名称 : APP.KeyBoard.c
*	版    本 : V1.0
*	说    明 : 1、按键扫描任务
*                  
*                 
*	修改记录 :
*		版本号  日期        作者     说明
*		V1.0    2018-08-27  zhoujh&Linzl  正式发布
*	Copyright (C), 2015-2020,   menredGroup
*
*******************************************************************************/

#include ".\app_configure.h"


//++++++++++++++++++++++++++++++start+++++++++++++++++++++++++++++++++++++++++++
//**************************模块使用的变量**************************************
//------------------------------E N D-------------------------------------------
//++++++++++++++++++++++++++++++start+++++++++++++++++++++++++++++++++++++++++++
//****************************按键宏定义****************************************

#define KEY_POWER			 		  KeyAloneBit0
#define KEY_POWEROFF				  KeyAloneBit1
//#define KEY_TEMP_ADD				  KeyAloneBit2
//#define KEY_TEMP_SUB				  KeyAloneBit3
#define KEY_HUMIDITY_ADD			  KeyAloneBit4
#define KEY_HUMIDITY_SUB			  KeyAloneBit5
#define KEY_MODE    				  KeyAloneBit6
#define KEY_SET_UP_STATE			  KeyAloneBit7
#define KEY_WIND_SPEED			      KeyAloneBit8
#define KEY_POWEROFF_SURE	 		  KeyAloneBit9
#define KEY_POWEROFF_CANCEL		      KeyAloneBit10

/*#define KEY_MODE_SUB       	KeyAloneBit0
#define KEY_MODE_ADD        KeyAloneBit1
#define KEY_HUMIDITY_SUB    KeyAloneBit2
#define KEY_HUMIDITY_ADD    KeyAloneBit3
#define KEY_WINDSPEED	   	KeyAloneBit4
#define KEY_TIMER	   		KeyAloneBit5
#define KEY_SETTING		 	KeyAloneBit6
#define KEY_POWEROFF	 	KeyAloneBit7
#define KEY_SURE		 	KeyAloneBit8
#define KEY_CANCEL		 	KeyAloneBit9
#define KEY_POWER		 	KeyAloneBit10*/
#define KEY_RESET		 	KeyAloneBit11
#define KEY_OUT_SCREEN_SAVER	KeyAloneBit12
#define KEY_INTO_SCREEN_SAVER	KeyAloneBit13

//#define KEY_TEMP_SUB        KeyAloneBit1
//#define KEY_TEMP_ADD        KeyAloneBit0
#define KEY_WIND_STATSU		 	KeyAloneBit5
#define KEY_MODE  		 	    KeyAloneBit6
//page 32
#define KEY_WIFI_PAGE32							KeyAloneBit0
#define KEY_TIME_CONTROL_PAGE32					KeyAloneBit1
#define KEY_FILTER_PAGE32						KeyAloneBit2
#define KEY_TIME_PAGE32							KeyAloneBit3
#define KEY_FACTORY_PAGE32						KeyAloneBit4
#define KEY_FAULT_PAGE32						KeyAloneBit5
#define KEY_ABOUT_PAGE32						KeyAloneBit6
#define KEY_OTHER_PAGE32						KeyAloneBit7
#define KEY_CANCEL_PAGE32						KeyAloneBit8

//page 34
#define KEY_WEEK_UP_PAGE34						KeyAloneBit0
#define KEY_WEEK_DOWN_PAGE34					KeyAloneBit1
#define KEY_TIME_INTERVAL_UP_PAGE34				KeyAloneBit2
#define KEY_TIME_INTERVAL_DOWN_PAGE34			KeyAloneBit3
#define KEY_JUMP_35PAGE_PAGE34					KeyAloneBit4
#define KEY_WEEK_ADD_PAGE34						KeyAloneBit5
#define KEY_WEEK_EDIT_PAGE34					KeyAloneBit6
#define KEY_WEEK_DELETE_PAGE34					KeyAloneBit7
#define KEY_CANCEL_PAGE34						KeyAloneBit8

//page 35
#define KEY_TIME_INTERVAL_UP_PAGE35				KeyAloneBit0
#define KEY_TIME_INTERVAL_DOWN_PAGE35			KeyAloneBit1
#define KEY_WEEK_UP_PAGE35						KeyAloneBit2
#define KEY_WEEK_DOWN_PAGE35					KeyAloneBit3
#define KEY_JUMP_34PAGE_PAGE35					KeyAloneBit4
#define KEY_TIME_INTERVAL_ADD_PAGE35			KeyAloneBit5
#define KEY_TIME_INTERVAL_EDIT_PAGE35			KeyAloneBit6
#define KEY_TIME_INTERVAL_DELETE_PAGE35			KeyAloneBit7
#define KEY_CANCEL_PAGE35						KeyAloneBit8

//page 36 星期选择
#define KEY_MONDAY_PAGE36						KeyAloneBit0
#define KEY_TUESDAY_PAGE36						KeyAloneBit1
#define KEY_WEDNESDAY_PAGE36					KeyAloneBit2
#define KEY_THURSDAY_PAGE36						KeyAloneBit3
#define KEY_FRIDAY_PAGE36						KeyAloneBit4
#define KEY_SATURDAY_PAGE36						KeyAloneBit5
#define KEY_SUNDAY_PAGE36						KeyAloneBit6
#define KEY_SURE_PAGE36							KeyAloneBit7
#define KEY_CANCEL_PAGE36						KeyAloneBit8

//42 43 46 47
#define KEY_CANCEL_PAGE42						KeyAloneBit0
#define KEY_CONNECT_PAGE42						KeyAloneBit1
#define KEY_FILTER_PAGE43						KeyAloneBit2
#define KEY_CYCLE_UP_PAGE43						KeyAloneBit3
#define KEY_CYCLE_DOWN_PAGE43					KeyAloneBit4
#define KEY_CANCEL_PAGE43						KeyAloneBit5
#define KEY_CANCEL_PAGE46						KeyAloneBit6
#define KEY_CANCEL_PAGE47						KeyAloneBit7
#define KEY_FACTORY_SET_PAGE47					KeyAloneBit8
#define KEY_QUIET_PAGE48						KeyAloneBit9
#define KEY_EVERBRIGHT_PAGE48					KeyAloneBit10
#define KEY_OUTDOOR_MESSAGE_PAGE48				KeyAloneBit11
#define KEY_HELP_PAGE48							KeyAloneBit12
#define KEY_CANCEL_PAGE48						KeyAloneBit13

//44
#define KEY_YEARS_UP_PAGE44						KeyAloneBit0
#define KEY_YEARS_DOWN_PAGE44					KeyAloneBit1
#define KEY_MONTH_UP_PAGE44						KeyAloneBit2
#define KEY_MONTH_DOWN_PAGE44					KeyAloneBit3
#define KEY_DAY_UP_PAGE44						KeyAloneBit4
#define KEY_DAY_DOWN_PAGE44						KeyAloneBit5
#define KEY_HOURS_UP_PAGE44						KeyAloneBit6
#define KEY_HOURS_DOWN_PAGE44					KeyAloneBit7
#define KEY_MINUTE_UP_PAGE44					KeyAloneBit8
#define KEY_MINUTE_DOWN_PAGE44					KeyAloneBit9
#define KEY_SURE_PAGE44							KeyAloneBit10
#define KEY_CANCEL_PAGE44						KeyAloneBit11

//45
#define KEY_0_PAGE45							KeyAloneBit0
#define KEY_1_PAGE45							KeyAloneBit1
#define KEY_2_PAGE45							KeyAloneBit2
#define KEY_3_PAGE45							KeyAloneBit3
#define KEY_4_PAGE45							KeyAloneBit4
#define KEY_5_PAGE45							KeyAloneBit5
#define KEY_6_PAGE45							KeyAloneBit6
#define KEY_7_PAGE45							KeyAloneBit7
#define KEY_8_PAGE45							KeyAloneBit8
#define KEY_9_PAGE45							KeyAloneBit9
#define KEY_DEL_PAGE45							KeyAloneBit10
#define KEY_SURE_PAGE45							KeyAloneBit11
#define KEY_CANCEL_PAGE45						KeyAloneBit12

#define KEY_POWERON_UP_PAGE61					KeyAloneBit0
#define KEY_POWERON_DOWN_PAGE61					KeyAloneBit1
#define KEY_POWEROFF_UP_PAGE61					KeyAloneBit2
#define KEY_POWEROFF_DOWN_PAGE61				KeyAloneBit3
#define KEY_WIND_UP_PAGE61						KeyAloneBit4
#define KEY_WIND_DOWN_PAGE61					KeyAloneBit5
#define KEY_MODE_UP_PAGE61						KeyAloneBit6
#define KEY_MODE_DOWN_PAGE61					KeyAloneBit7
#define KEY_SURE_PAGE61							KeyAloneBit8
#define KEY_CANCEL_PAGE61						KeyAloneBit9


#define KEY_FANSET_FANMOTOR_UP_PAGE62				KeyAloneBit0
#define KEY_FANSET_FANMOTOR_DOWN_PAGE62				KeyAloneBit1
#define KEY_FANSET_FANMOTOR_TYPE_UP_PAGE62			KeyAloneBit2
#define KEY_FANSET_FANMOTOR_TYPE_DOWN_PAGE62		KeyAloneBit3		
#define KEY_FANSET_FANMOTOR_HIGHSPEED_UP_PAGE62		KeyAloneBit4	
#define KEY_FANSET_FANMOTOR_HIGHSPEED_DOWN_PAGE62	KeyAloneBit5	
#define KEY_FANSET_FANMOTOR_MIDSPEED_UP_PAGE62		KeyAloneBit6
#define KEY_FANSET_FANMOTOR_MIDSPEED_DOWN_PAGE62	KeyAloneBit7			
#define KEY_FANSET_FANMOTOR_LOWSPEED_UP_PAGE62		KeyAloneBit8		
#define KEY_FANSET_FANMOTOR_LOWSPEED_DOWN_PAGE62	KeyAloneBit9
#define KEY_FANSET_REMOVEWET_UP_PAGE62				KeyAloneBit10
#define KEY_FANSET_REMOVEWET_DOWN_PAGE62			KeyAloneBit11
#define KEY_FANSET_485ADRESS_UP_PAGE62				KeyAloneBit12
#define KEY_FANSET_485ADRESS_DOWN_PAGE62			KeyAloneBit13
#define KEY_FANSET_BAUDRATE_UP_PAGE62				KeyAloneBit14
#define KEY_FANSET_BAUDRATE_DOWN_PAGE62				KeyAloneBit15

/*#define	KEY_NUMBER_POWER 				0
#define	KEY_NUMBER_POWEROFF				1
#define	KEY_NUMBER_TEMP_ADD				2
#define	KEY_NUMBER_TEMP_SUB				3
#define	KEY_NUMBER_HUMIDITY_ADD			4
#define	KEY_NUMBER_HUMIDITY_SUB			5
#define	KEY_NUMBER_MODE					6
#define	KEY_NUMBER_SET_UP_STATE			7
#define	KEY_NUMBER_WIND_SPEED			8
#define	KEY_NUMBER_POWEROFF_SURE		9
#define	KEY_NUMBER_POWEROFF_CANCEL		10*/

#define KEY_HOT_SWITCH					0
#define KEY_SETTING						1
#define KEY_TEMP_ADD					2
#define KEY_TEMP_SUB					3
#define KEY_HUMIDITY_ADD				4
#define KEY_HUMIDITY_SUB				5
#define KEY_MODE						6
#define KEY_AIR_MODE					7
#define KEY_WIND_SWITCH					8
#define KEY_POWER_ONOFF					9
#define KEY_POWEROFF_SURE				10
#define KEY_POWEROFF_CANCEL				11
#define KEY_GOTO_GREEN_SCREEN			12
#define KEY_POWERON						13
#define KEY_GREEN_CHANGE				14
#define KEY_GOTO_MAIN_CONTROL			15


#define KEY_TYPE_NUMBER							5
#define	KEY_HOT_SWITCH_NULL						(0)
#define	KEY_HOT_SWITCH_STATE					(KEY_HOT_SWITCH * KEY_TYPE_NUMBER + KEY_STATE)
#define	KEY_HOT_SWITCH_FIRST_DOWN				(KEY_HOT_SWITCH * KEY_TYPE_NUMBER + KEY_DOWN)
#define	KEY_HOT_SWITCH_LONG						(KEY_HOT_SWITCH * KEY_TYPE_NUMBER + LONG_KEY)	
#define	KEY_HOT_SWITCH_CONTINUE					(KEY_HOT_SWITCH * KEY_TYPE_NUMBER + CONTINUE)
#define	KEY_HOT_SWITCH_UP						(KEY_HOT_SWITCH * KEY_TYPE_NUMBER + KEY_UP)
												
#define	KEY_SETTING_NULL						(0)
#define	KEY_SETTING_STATE						(KEY_SETTING * KEY_TYPE_NUMBER + KEY_STATE)
#define	KEY_SETTING_FIRST_DOWN					(KEY_SETTING * KEY_TYPE_NUMBER + KEY_DOWN)
#define	KEY_SETTING_LONG						(KEY_SETTING * KEY_TYPE_NUMBER + LONG_KEY)	
#define	KEY_SETTING_CONTINUE					(KEY_SETTING * KEY_TYPE_NUMBER + CONTINUE)
#define	KEY_SETTING_UP							(KEY_SETTING * KEY_TYPE_NUMBER + KEY_UP)												
												
#define	KEY_TEMP_ADD_NULL						(0)
#define	KEY_TEMP_ADD_STATE						(KEY_TEMP_ADD * KEY_TYPE_NUMBER + KEY_STATE)
#define	KEY_TEMP_ADD_FIRST_DOWN					(KEY_TEMP_ADD * KEY_TYPE_NUMBER + KEY_DOWN)
#define	KEY_TEMP_ADD_LONG						(KEY_TEMP_ADD * KEY_TYPE_NUMBER + LONG_KEY)	
#define	KEY_TEMP_ADD_CONTINUE					(KEY_TEMP_ADD * KEY_TYPE_NUMBER + CONTINUE)
#define	KEY_TEMP_ADD_UP							(KEY_TEMP_ADD * KEY_TYPE_NUMBER + KEY_UP)	

#define	KEY_TEMP_SUB_NULL						(0)
#define	KEY_TEMP_SUB_STATE						(KEY_TEMP_SUB * KEY_TYPE_NUMBER + KEY_STATE)
#define	KEY_TEMP_SUB_FIRST_DOWN					(KEY_TEMP_SUB * KEY_TYPE_NUMBER + KEY_DOWN)
#define	KEY_TEMP_SUB_LONG						(KEY_TEMP_SUB * KEY_TYPE_NUMBER + LONG_KEY)	
#define	KEY_TEMP_SUB_CONTINUE					(KEY_TEMP_SUB * KEY_TYPE_NUMBER + CONTINUE)
#define	KEY_TEMP_SUB_UP							(KEY_TEMP_SUB * KEY_TYPE_NUMBER + KEY_UP)	

#define	KEY_HUMIDITY_ADD_NULL					(0)
#define	KEY_HUMIDITY_ADD_STATE					(KEY_HUMIDITY_ADD * KEY_TYPE_NUMBER + KEY_STATE)
#define	KEY_HUMIDITY_ADD_FIRST_DOWN				(KEY_HUMIDITY_ADD * KEY_TYPE_NUMBER + KEY_DOWN)
#define	KEY_HUMIDITY_ADD_LONG					(KEY_HUMIDITY_ADD * KEY_TYPE_NUMBER + LONG_KEY)	
#define	KEY_HUMIDITY_ADD_CONTINUE				(KEY_HUMIDITY_ADD * KEY_TYPE_NUMBER + CONTINUE)
#define	KEY_HUMIDITY_ADD_UP						(KEY_HUMIDITY_ADD * KEY_TYPE_NUMBER + KEY_UP)	

#define	KEY_HUMIDITY_SUB_NULL					(0)
#define	KEY_HUMIDITY_SUB_STATE					(KEY_HUMIDITY_SUB * KEY_TYPE_NUMBER + KEY_STATE)
#define	KEY_HUMIDITY_SUB_FIRST_DOWN				(KEY_HUMIDITY_SUB * KEY_TYPE_NUMBER + KEY_DOWN)
#define	KEY_HUMIDITY_SUB_LONG					(KEY_HUMIDITY_SUB * KEY_TYPE_NUMBER + LONG_KEY)	
#define	KEY_HUMIDITY_SUB_CONTINUE				(KEY_HUMIDITY_SUB * KEY_TYPE_NUMBER + CONTINUE)
#define	KEY_HUMIDITY_SUB_UP						(KEY_HUMIDITY_SUB * KEY_TYPE_NUMBER + KEY_UP)

#define	KEY_MODE_NULL							(0)
#define	KEY_MODE_STATE							(KEY_MODE * KEY_TYPE_NUMBER + KEY_STATE)
#define	KEY_MODE_FIRST_DOWN						(KEY_MODE * KEY_TYPE_NUMBER + KEY_DOWN)
#define	KEY_MODE_LONG							(KEY_MODE * KEY_TYPE_NUMBER + LONG_KEY)	
#define	KEY_MODE_CONTINUE						(KEY_MODE * KEY_TYPE_NUMBER + CONTINUE)
#define	KEY_MODE_UP								(KEY_MODE * KEY_TYPE_NUMBER + KEY_UP)

#define	KEY_AIR_MODE_NULL						(0)
#define	KEY_AIR_MODE_STATE						(KEY_AIR_MODE * KEY_TYPE_NUMBER + KEY_STATE)
#define	KEY_AIR_MODE_FIRST_DOWN					(KEY_AIR_MODE * KEY_TYPE_NUMBER + KEY_DOWN)
#define	KEY_AIR_MODE_LONG						(KEY_AIR_MODE * KEY_TYPE_NUMBER + LONG_KEY)	
#define	KEY_AIR_MODE_CONTINUE					(KEY_AIR_MODE * KEY_TYPE_NUMBER + CONTINUE)
#define	KEY_AIR_MODE_UP							(KEY_AIR_MODE * KEY_TYPE_NUMBER + KEY_UP)

#define	KEY_WIND_SWITCH_NULL					(0)
#define	KEY_WIND_SWITCH_STATE					(KEY_WIND_SWITCH * KEY_TYPE_NUMBER + KEY_STATE)
#define	KEY_WIND_SWITCH_FIRST_DOWN				(KEY_WIND_SWITCH * KEY_TYPE_NUMBER + KEY_DOWN)
#define	KEY_WIND_SWITCH_LONG					(KEY_WIND_SWITCH * KEY_TYPE_NUMBER + LONG_KEY)	
#define	KEY_WIND_SWITCH_CONTINUE				(KEY_WIND_SWITCH * KEY_TYPE_NUMBER + CONTINUE)
#define	KEY_WIND_SWITCH_UP						(KEY_WIND_SWITCH * KEY_TYPE_NUMBER + KEY_UP)

#define	KEY_POWER_ONOFF_NULL					(0)
#define	KEY_POWER_ONOFF_STATE					(KEY_POWER_ONOFF * KEY_TYPE_NUMBER + KEY_STATE)
#define	KEY_POWER_ONOFF_FIRST_DOWN				(KEY_POWER_ONOFF * KEY_TYPE_NUMBER + KEY_DOWN)
#define	KEY_POWER_ONOFF_LONG					(KEY_POWER_ONOFF * KEY_TYPE_NUMBER + LONG_KEY)	
#define	KEY_POWER_ONOFF_CONTINUE				(KEY_POWER_ONOFF * KEY_TYPE_NUMBER + CONTINUE)
#define	KEY_POWER_ONOFF_UP						(KEY_POWER_ONOFF * KEY_TYPE_NUMBER + KEY_UP)

#define	KEY_POWEROFF_SURE_NULL					(0)
#define	KEY_POWEROFF_SURE_STATE					(KEY_POWEROFF_SURE * KEY_TYPE_NUMBER + KEY_STATE)
#define	KEY_POWEROFF_SURE_FIRST_DOWN			(KEY_POWEROFF_SURE * KEY_TYPE_NUMBER + KEY_DOWN)
#define	KEY_POWEROFF_SURE_LONG					(KEY_POWEROFF_SURE * KEY_TYPE_NUMBER + LONG_KEY)	
#define	KEY_POWEROFF_SURE_CONTINUE				(KEY_POWEROFF_SURE * KEY_TYPE_NUMBER + CONTINUE)
#define	KEY_POWEROFF_SURE_UP					(KEY_POWEROFF_SURE * KEY_TYPE_NUMBER + KEY_UP)

#define	KEY_POWEROFF_CANCEL_NULL				(0)
#define	KEY_POWEROFF_CANCEL_STATE				(KEY_POWEROFF_CANCEL * KEY_TYPE_NUMBER + KEY_STATE)
#define	KEY_POWEROFF_CANCEL_FIRST_DOWN			(KEY_POWEROFF_CANCEL * KEY_TYPE_NUMBER + KEY_DOWN)
#define	KEY_POWEROFF_CANCEL_LONG				(KEY_POWEROFF_CANCEL * KEY_TYPE_NUMBER + LONG_KEY)	
#define	KEY_POWEROFF_CANCEL_CONTINUE			(KEY_POWEROFF_CANCEL * KEY_TYPE_NUMBER + CONTINUE)
#define	KEY_POWEROFF_CANCEL_UP					(KEY_POWEROFF_CANCEL * KEY_TYPE_NUMBER + KEY_UP)

#define	KEY_GOTO_GREEN_SCREEN_NULL				(0)
#define	KEY_GOTO_GREEN_SCREEN_STATE				(KEY_GOTO_GREEN_SCREEN * KEY_TYPE_NUMBER + KEY_STATE)
#define	KEY_GOTO_GREEN_SCREEN_FIRST_DOWN		(KEY_GOTO_GREEN_SCREEN * KEY_TYPE_NUMBER + KEY_DOWN)
#define	KEY_GOTO_GREEN_SCREEN_LONG				(KEY_GOTO_GREEN_SCREEN * KEY_TYPE_NUMBER + LONG_KEY)	
#define	KEY_GOTO_GREEN_SCREEN_CONTINUE			(KEY_GOTO_GREEN_SCREEN * KEY_TYPE_NUMBER + CONTINUE)
#define	KEY_GOTO_GREEN_SCREEN_UP				(KEY_GOTO_GREEN_SCREEN * KEY_TYPE_NUMBER + KEY_UP)

#define	KEY_POWERON_NULL						(0)
#define	KEY_POWERON_STATE						(KEY_POWERON * KEY_TYPE_NUMBER + KEY_STATE)
#define	KEY_POWERON_FIRST_DOWN					(KEY_POWERON * KEY_TYPE_NUMBER + KEY_DOWN)
#define	KEY_POWERON_LONG						(KEY_POWERON * KEY_TYPE_NUMBER + LONG_KEY)	
#define	KEY_POWERON_CONTINUE					(KEY_POWERON * KEY_TYPE_NUMBER + CONTINUE)
#define	KEY_POWERON_UP							(KEY_POWERON * KEY_TYPE_NUMBER + KEY_UP)

#define	KEY_GREEN_CHANGE_NULL					(0)
#define	KEY_GREEN_CHANGE_STATE					(KEY_GREEN_CHANGE * KEY_TYPE_NUMBER + KEY_STATE)
#define	KEY_GREEN_CHANGE_FIRST_DOWN				(KEY_GREEN_CHANGE * KEY_TYPE_NUMBER + KEY_DOWN)
#define	KEY_GREEN_CHANGE_LONG					(KEY_GREEN_CHANGE * KEY_TYPE_NUMBER + LONG_KEY)	
#define	KEY_GREEN_CHANGE_CONTINUE				(KEY_GREEN_CHANGE * KEY_TYPE_NUMBER + CONTINUE)
#define	KEY_GREEN_CHANGE_UP						(KEY_GREEN_CHANGE * KEY_TYPE_NUMBER + KEY_UP)

#define	KEY_GOTO_MAIN_CONTROL_NULL				(0)
#define	KEY_GOTO_MAIN_CONTROL_STATE				(KEY_GOTO_MAIN_CONTROL * KEY_TYPE_NUMBER + KEY_STATE)
#define	KEY_GOTO_MAIN_CONTROL_FIRST_DOWN		(KEY_GOTO_MAIN_CONTROL * KEY_TYPE_NUMBER + KEY_DOWN)
#define	KEY_GOTO_MAIN_CONTROL_LONG				(KEY_GOTO_MAIN_CONTROL * KEY_TYPE_NUMBER + LONG_KEY)	
#define	KEY_GOTO_MAIN_CONTROL_CONTINUE			(KEY_GOTO_MAIN_CONTROL * KEY_TYPE_NUMBER + CONTINUE)
#define	KEY_GOTO_MAIN_CONTROL_UP				(KEY_GOTO_MAIN_CONTROL * KEY_TYPE_NUMBER + KEY_UP)

#define KEY_SET_WIFI				16
#define KEY_SET_TIMING				17
#define KEY_SET_FILTER				18
#define KEY_SET_TIME				19
#define KEY_SET_HIGHSET				20
#define KEY_SET_AUTO				21
#define KEY_SET_ABOUT				22
#define KEY_SET_OTHER				23
#define KEY_SET_BACK				24

#define KEY_SET_WIFI_UP							(KEY_SET_WIFI * KEY_TYPE_NUMBER + KEY_UP)
#define KEY_SET_TIMING_UP						(KEY_SET_TIMING * KEY_TYPE_NUMBER + KEY_UP)
#define KEY_SET_FILTER_UP						(KEY_SET_FILTER * KEY_TYPE_NUMBER + KEY_UP)
#define KEY_SET_TIME_UP							(KEY_SET_TIME * KEY_TYPE_NUMBER + KEY_UP)
#define KEY_SET_HIGHSET_UP						(KEY_SET_HIGHSET * KEY_TYPE_NUMBER + KEY_UP)
#define KEY_SET_AUTO_UP							(KEY_SET_AUTO * KEY_TYPE_NUMBER + KEY_UP)
#define KEY_SET_ABOUT_UP						(KEY_SET_ABOUT * KEY_TYPE_NUMBER + KEY_UP)
#define KEY_SET_OTHER_UP						(KEY_SET_OTHER * KEY_TYPE_NUMBER + KEY_UP)
#define KEY_SET_BACK_UP							(KEY_SET_BACK * KEY_TYPE_NUMBER + KEY_UP)

#define KEY_SET_YEAR_UP				32	//+
#define KEY_SET_YEAR_DOWN			33
#define KEY_SET_MONTH_UP			34
#define KEY_SET_MONTH_DOWN			35
#define KEY_SET_DAY_UP				36
#define KEY_SET_DAY_DOWN			37
#define KEY_SET_HOUR_UP				38
#define KEY_SET_HOUR_DOWN			39
#define KEY_SET_MINTUE_UP			40
#define KEY_SET_MINTUE_DOWN			41
#define KEY_SET_SURE_DOWN			42

#define KEY_SET_YEAR_ADD_CONTINUE				(KEY_SET_YEAR_UP * KEY_TYPE_NUMBER + CONTINUE)
#define KEY_SET_YEAR_ADD_UP						(KEY_SET_YEAR_UP * KEY_TYPE_NUMBER + KEY_UP)

#define KEY_SET_YEAR_SUB_CONTINUE				(KEY_SET_YEAR_DOWN * KEY_TYPE_NUMBER + CONTINUE)
#define KEY_SET_YEAR_SUB_UP						(KEY_SET_YEAR_DOWN * KEY_TYPE_NUMBER + KEY_UP)

#define KEY_SET_MONTH_ADD_CONTINUE				(KEY_SET_MONTH_UP * KEY_TYPE_NUMBER + CONTINUE)
#define KEY_SET_MONTH_ADD_UP					(KEY_SET_MONTH_UP * KEY_TYPE_NUMBER + KEY_UP)

#define KEY_SET_MONTH_SUB_CONTINUE				(KEY_SET_MONTH_DOWN * KEY_TYPE_NUMBER + CONTINUE)
#define KEY_SET_MONTH_SUB_UP					(KEY_SET_MONTH_DOWN * KEY_TYPE_NUMBER + KEY_UP)

#define KEY_SET_DAY_ADD_CONTINUE				(KEY_SET_DAY_UP * KEY_TYPE_NUMBER + CONTINUE)
#define KEY_SET_DAY_ADD_UP						(KEY_SET_DAY_UP * KEY_TYPE_NUMBER + KEY_UP)

#define KEY_SET_DAY_SUB_CONTINUE				(KEY_SET_DAY_DOWN * KEY_TYPE_NUMBER + CONTINUE)
#define KEY_SET_DAY_SUB_UP						(KEY_SET_DAY_DOWN * KEY_TYPE_NUMBER + KEY_UP)

#define KEY_SET_HOUR_ADD_CONTINUE				(KEY_SET_HOUR_UP * KEY_TYPE_NUMBER + CONTINUE)
#define KEY_SET_HOUR_ADD_UP						(KEY_SET_HOUR_UP * KEY_TYPE_NUMBER + KEY_UP)

#define KEY_SET_HOUR_SUB_CONTINUE				(KEY_SET_HOUR_DOWN * KEY_TYPE_NUMBER + CONTINUE)
#define KEY_SET_HOUR_SUB_UP						(KEY_SET_HOUR_DOWN * KEY_TYPE_NUMBER + KEY_UP)

#define KEY_SET_MINTUE_ADD_CONTINUE				(KEY_SET_MINTUE_UP * KEY_TYPE_NUMBER + CONTINUE)
#define KEY_SET_MINTUE_ADD_UP					(KEY_SET_MINTUE_UP * KEY_TYPE_NUMBER + KEY_UP)

#define KEY_SET_MINTUE_SUB_CONTINUE				(KEY_SET_MINTUE_DOWN * KEY_TYPE_NUMBER + CONTINUE)
#define KEY_SET_MINTUE_SUB_UP					(KEY_SET_MINTUE_DOWN * KEY_TYPE_NUMBER + KEY_UP)

#define KEY_SET_SURE_UP							(KEY_SET_SURE_DOWN * KEY_TYPE_NUMBER + KEY_UP)


//------------------------------E N D-------------------------------------------
#define KEY_CHILD      KeyGroupBit0
#define KEY_HIGHSET    KeyGroupBit1  
#define KEY_LINK	   KeyGroupBit2
//++++++++++++++++++++++++++++++start+++++++++++++++++++++++++++++++++++++++++++
//**************************高级设定按键处理************************************

#define DDR_ADD                   BN_TRUE
#define DDR_DEC                   BN_FALSE
#define DATA_LOOP                 BN_TRUE
#define DATA_KEEP                 BN_FALSE

extern u8 idata tempBuff[100];

typedef enum
{
	MODE = 1,
	AIRMODE,
	HUMIDITY,
	WIND,
	TIMER,
	POWER,
	TYPE_NUMBER,
	TEMP,
	WINDSTATUS,
}x_t;




//Task
//名称: keyOperation
//功能: 用于数据计算，限制加减法类型(循环或者保持)和最大最小值限制
//入口: 方向				ddr
//		类型				loop(0:极限值保持					1:循环自加)
//		步长				step
//		最大值				max
//		最小值				min
//		待处理数据			*dat
//出口:
//		待处理数据			*dat
//		返回				return
int16_t keyOperation(int8_t ddr,int8_t loop,int16_t step,int16_t max,int16_t min,int16_t* dat)
{
    int16_t DateCalculation;
    
    DateCalculation = *dat;
    
    if(DDR_ADD == ddr)
    {         
        if(DateCalculation >= max)
        {
            if(loop)
            {
                DateCalculation = min;
            }
            else
            {
                DateCalculation = max; 
            }           
        }
        else
        {
            DateCalculation += step;            
        }
    }
    else if(DDR_DEC == ddr)
    {
        if(DateCalculation <= min)
        {
            if(loop)
            {
                DateCalculation = max;
            }
            else
            {
                DateCalculation = min; 
            }
        }
        else
        {
            DateCalculation -= step;
        }
    }
    *dat  = DateCalculation;
    return DateCalculation;
}

void u8_calculation(uint8_t ddr,uint8_t loop,uint8_t max,uint8_t min,uint8_t *src)
{
    uint8_t DateCalculation;
    DateCalculation = *src;
	if(DDR_ADD == ddr)
	{
        if(DateCalculation >= max)
        {
            if(loop)
            {
                DateCalculation = min;
            }
            else
            {
                DateCalculation = max; 
            }           
        }
        else
        {
            DateCalculation++;            
        }
	}
	else if(DDR_DEC == ddr)
	{
        if(DateCalculation <= min)
        {
            if(loop)
            {
                DateCalculation = max;
            }
            else
            {
                DateCalculation = min; 
            }
        }
        else
        {
            DateCalculation--;
        }
	}
	*src = DateCalculation;
}

//十进制20  转换成  0x20(32) BCD还是hex?
//理论最大数据为59
uint8_t dec_to_bcd(uint8_t process_data)
{
	uint8_t return_value = 0;
	uint8_t bit_one;	
	uint8_t bit_ten;	
	uint8_t bit_hunred;	
	if(process_data < 10)
	{
		bit_one = process_data % 10;
		return_value = bit_one;
	}
	else if(process_data < 100)
	{
		bit_one = process_data % 10;
		bit_ten = process_data / 10;
		return_value = bit_ten * 16 + bit_one;
	}
	else if(process_data < 256)
	{
		
		bit_one = process_data % 10;//个位数
		bit_ten = process_data / 10;//十位数
		bit_hunred = process_data / 100;//百位
		return_value = bit_hunred * 16 * 16 + bit_ten * 16 + bit_one;
	}
	else
	{
		;
	}
		
	return return_value;
}


void app_keyinit_jumppage(void)
{
	uint8_t i;
	INT16U reset[] ={REG_KEY_SETTING,REG_KEY_POWER_ONOFF,REG_KEY_POWEROFF_SURE,REG_KEY_POWEROFF_CANCEL,
					 REG_KEY_GOTO_GREEN_SCREEN,REG_KEY_POWERON,REG_KEY_SET_WIFI,REG_KEY_SET_TIMING,
					 REG_KEY_SET_FILTER,REG_KEY_SET_TIME,REG_KEY_SET_HIGHSET,REG_KEY_SET_AUTO,
					 REG_KEY_SET_ABOUT,REG_KEY_SET_OTHER,REG_KEY_SET_BACK};

	INT8U writebuf[2] ={0,0};

	for(i = 0; i < (sizeof(reset)/sizeof(reset[0])); i++)
	{
		WriteDGUS(reset[i],writebuf,2);
	}
	
}

uint16_t get_485value(uint16_t adress)
{
    SysPara_t *ptSysPara;  
	uint16_t re_cmd = 0;
	ptSysPara =  controler_getSysParaPt();
	
	switch (adress)
	{
		 case MRegaddr_NewairControlW:
		 {//开关机
			if(ptSysPara->poweroff == POWEROFF_DIS_OFF)
			{
				re_cmd = MREGADDRESS_SYS_POWER_OFF_CMD;
			}
			else if(ptSysPara->poweroff == POWEROFF_DIS_ON)
			{
				re_cmd = MREGADDRESS_SYS_POWER_ON_CMD;
				//ptSysPara->poweronflag = 1;
			}
			break;
		 } 		
		/*case MREGADDRESS_SYS_MODE: 
			if(ptSysPara->mode == 62)//新风
			{
				re_cmd = MREGADDRESS_SYS_MODE_NEWWIND_CMD;
			}
			else if(ptSysPara->mode == 63)//净化
			{
				re_cmd = MREGADDRESS_SYS_MODE_PURIFY_CMD;
			}
			else if(ptSysPara->mode == 64)//除湿
			{
				re_cmd = MREGADDRESS_SYS_MODE_REMOVEWET_CMD;
			}
			else 
			{
				re_cmd = MREGADDRESS_SYS_MODE_AUTO_CMD;
			}
			break;*/
		case MRegaddr_Aircod_Mode: //模式
			if(ptSysPara->mode == 1)//冷
			{
				re_cmd = MREGADDRESS_SYS_MODE_COLD;
			}
			else if(ptSysPara->mode == 2)//热
			{
				re_cmd = MREGADDRESS_SYS_MODE_HEAT;
			}
			else if(ptSysPara->mode == 3)//除湿
			{
				re_cmd = MREGADDRESS_SYS_MODE_HUMIDTY;
			}
			else if(ptSysPara->mode == 4)//通风
			{
				re_cmd = MREGADDRESS_SYS_MODE_WIND;
			}
			break;
		case MRegaddr_Aircod_airwindStatus://通风状态
			if(ptSysPara->airmode == 0)
			{
				re_cmd = 0x00;
			}
			else if(ptSysPara->airmode == 1)
			{
				re_cmd = 0x01;
			}
			else if(ptSysPara->airmode == 2)
			{
				re_cmd = 0x02;
			}
			break;//通风状态
		case MRegaddr_NewairFanSet://设定风速
			if(ptSysPara->windspeed == 1)
			{
				re_cmd = MREGADDRESS_SYS_SET_LOWWIND;
			}
			else if(ptSysPara->windspeed == 2)
			{
				re_cmd = MREGADDRESS_SYS_SET_MIDWIND;
			}
			else if(ptSysPara->windspeed == 3)
			{
				re_cmd = MREGADDRESS_SYS_SET_HIGHWIND;
			}
			break;//风速
		case MREGADDRESS_SYS_WIND_SPEED_CONTROL:
			if(ptSysPara->windspeed == 5)
			{
				re_cmd = MREGADDRESS_SYS_SET_LOWWIND;
			}
			else if(ptSysPara->windspeed == 6)
			{
				re_cmd = MREGADDRESS_SYS_SET_MIDWIND;
			}
			else if(ptSysPara->windspeed == 7)
			{
				re_cmd = MREGADDRESS_SYS_SET_HIGHWIND;
			}
			break;//风速
		case MRegaddr_Aircod_SetHumidity:
			re_cmd = ptSysPara->humidity_set;
			break;//湿度
	 case MRegaddr_Aircod_SetTemp:
			re_cmd = ptSysPara->temp_set;
			break;//温度
	 case MREGADDRESS_SYS_OUTWIND_PWM_LOW_SPEED:
			re_cmd = ptSysPara->fanset_param.low_param;
			break;
	 case MREGADDRESS_SYS_OUTWIND_PWM_MID_SPEED:
			re_cmd = ptSysPara->fanset_param.mid_param;
			break;
	 case MREGADDRESS_SYS_OUTWIND_PWM_HIGH_SPEED:
			re_cmd = ptSysPara->fanset_param.high_param;
			break;
	 case MREGADDRESS_SYS_INWIND_PWM_LOW_SPEED:
			re_cmd = ptSysPara->fanset_param.low_param;
			break;
	 case MREGADDRESS_SYS_INWIND_PWM_MID_SPEED:
			re_cmd = ptSysPara->fanset_param.mid_param;
			break;
	 case MREGADDRESS_SYS_INWIND_PWM_HIGH_SPEED:
			re_cmd = ptSysPara->fanset_param.high_param;
			break;
	
		default: re_cmd = 0xFFFF;break;
	}
	return re_cmd;
}
void app_key_power_on(void)
{
	SysPara_t *ptSysPara;  
	ptSysPara =  controler_getSysParaPt();
	
}
void app_key_main_control()
{
	/*SysPara_t *ptSysPara;  
    int8_t keychangeflag = 0;
	int8_t ddr = 0;
	keyActionType_t key_action;
	uint16_t adress = 0;
	uint8_t	keynumber_buf[2] = {0,0};
	//static uint8_t misoperationflag = 0;

	ptSysPara =  controler_getSysParaPt();

	if((PUSH_DOWN | PUSH_CONTINUE) & mod_keyOperation(KEY_POWER,0xffff,0xffff))
	{//开机
		ptSysPara->page_number = 1;
		ptSysPara->poweroff = POWEROFF_DIS_ON;
		keychangeflag = POWER;
	}
	else if((PUSH_DOWN | PUSH_CONTINUE) & mod_keyOperation(KEY_POWEROFF,0xffff,0xffff))
	{//关机
		//keychangeflag = POWER;
	}
	else if((PUSH_DOWN | PUSH_CONTINUE) & mod_keyOperation(KEY_TEMP_ADD,3000,200))
	{//温度 -
		ddr = DDR_DEC;
		keychangeflag = TEMP;
	}
	else if((PUSH_DOWN | PUSH_CONTINUE) & mod_keyOperation(KEY_TEMP_SUB,3000,200))
	{//温度 +
		ddr = DDR_ADD;
		keychangeflag = TEMP;
	}
	else if((PUSH_DOWN | PUSH_CONTINUE) & mod_keyOperation(KEY_HUMIDITY_ADD,3000,200))
	{//湿度 +
		ddr = DDR_ADD;
		keychangeflag = HUMIDITY;
	}
	else if((PUSH_DOWN | PUSH_CONTINUE) & mod_keyOperation(KEY_HUMIDITY_SUB,3000,200))
	{//湿度 -
		ddr = DDR_DEC;
		keychangeflag = HUMIDITY;
	}	
	else if((PUSH_DOWN | PUSH_CONTINUE) & mod_keyOperation(KEY_MODE,3000,200))
	{//模式
		ddr = DDR_ADD;
		keychangeflag = MODE;
	}
	else if((PUSH_DOWN | PUSH_CONTINUE) & mod_keyOperation(KEY_SET_UP_STATE,3000,200))
	{//设定状态
		ddr = DDR_ADD;
		keychangeflag = AIRMODE;
	}
	else if((PUSH_DOWN | PUSH_CONTINUE) & mod_keyOperation(KEY_WIND_SPEED,3000,200))
	{//风速
		ddr = DDR_ADD;
		keychangeflag = WIND;
	}
	else if((PUSH_DOWN | PUSH_UP) & (key_action = mod_keyOperation(KEY_POWEROFF_SURE,0xffff,0xffff)))
	{//关机确认
		ptSysPara->page_number = 0;
		ptSysPara->poweroff = POWEROFF_DIS_OFF;
		keychangeflag = POWER;
	}
	else if((PUSH_DOWN | PUSH_UP) & (key_action = mod_keyOperation(KEY_POWEROFF_CANCEL,0xffff,0xffff)))
	{//关机取消
		if(ptSysPara->page_number >= 25)
		{
			ptSysPara->page_number = 29;
		}
	}
	
	switch(keychangeflag)
	{
		case MODE:		
				ptSysPara->updataflag = BN_TRUE;
				keyOperation(ddr,DATA_LOOP,1,MODE_DIS_MAX,MODE_DIS_MIN,&ptSysPara->mode);
				adress = MRegaddr_Aircod_Mode;
				break;
		case AIRMODE: 
				ptSysPara->updataflag = BN_TRUE;
				keyOperation(ddr,DATA_LOOP,1,AIR_MODE_DIS_MAX,AIR_MODE_DIS_MIN,&ptSysPara->airmode);
				adress = MRegaddr_Aircod_airwindStatus;
				break;
		case HUMIDITY:				
				ptSysPara->updataflag = BN_TRUE;
				keyOperation(ddr,DATA_KEEP,1,HUMIDITY_MAX,HUMIDITY_MIN,&ptSysPara->humidity_set);
				adress = MRegaddr_Aircod_SetHumidity;
				break;
		case TEMP:				
				if(ptSysPara->mode != 4)
				{
					ptSysPara->updataflag = BN_TRUE;
					keyOperation(ddr,DATA_KEEP,10,TEMP_MAX,TEMP_MIN,&ptSysPara->temp_set);
					adress = MRegaddr_Aircod_SetTemp;
				}
				break;
		case WIND:		
				ptSysPara->updataflag = BN_TRUE;
				keyOperation(ddr,DATA_LOOP,1,WIND_DIS_MAX,WIND_DIS_MIN,&ptSysPara->windspeed);
				adress = MRegaddr_NewairFanSet;
				break;
		case POWER:
				ptSysPara->updataflag = BN_TRUE;
				adress = MRegaddr_NewairControlW;
				break;
				
		default: break;
	}
	
	if(keychangeflag != 0)//进入缓存等待发送
	{
		APP_oneWire_send_485_data(adress,get_485value(adress));
	}*/
}

void get_pwm_data(void)
{	
	SysPara_t *ptSysPara;  
	ptSysPara =  controler_getSysParaPt();
	if(ptSysPara->fanset_param.motor_type == 0)//新风
	{
		if(ptSysPara->read_244B_LOW_PWM < 100)
		{
			ptSysPara->fanset_param.low_param = ptSysPara->read_244B_LOW_PWM;
		}
		
		if(ptSysPara->read_244C_MID_PWM < 100)
		{
			ptSysPara->fanset_param.mid_param = ptSysPara->read_244C_MID_PWM;
		}
		
		if(ptSysPara->read_244D_HIGH_PWM < 100)
		{
			ptSysPara->fanset_param.high_param = ptSysPara->read_244D_HIGH_PWM;
		}
	}
	else if(ptSysPara->fanset_param.motor_type == 1)//回风
	{
		if(ptSysPara->read_2448_LOW_PWM < 100)
		{
			ptSysPara->fanset_param.low_param = ptSysPara->read_2448_LOW_PWM;
		}
		
		if(ptSysPara->read_2449_MID_PWM < 100)
		{
			ptSysPara->fanset_param.mid_param = ptSysPara->read_2449_MID_PWM;
		}
		
		if(ptSysPara->read_244A_HIGH_PWM < 100)
		{
			ptSysPara->fanset_param.high_param = ptSysPara->read_244A_HIGH_PWM;
		}
	}
}
void app_key_fanset(void)
{	
	//62页数据 20左右的按键数据
	SysPara_t *ptSysPara;  
	uint8_t sendbuf[13] ={0,0,0,0,0,0,0,0,0,0,0,0,0};
	uint8_t limit_max = 0;
	uint8_t limit_min = 0;
	uint16_t adress = 0;
	uint8_t key_type = 0;
	ptSysPara =  controler_getSysParaPt();
	
	switch(ptSysPara->key_fanset_param)
	{
		case KEY_FANSET_FANMOTOR_UP_PAGE62: 
							ptSysPara->fanset_param.motor_type ^= 0x01;
							get_pwm_data();
							break;
		case KEY_FANSET_FANMOTOR_DOWN_PAGE62: 
							ptSysPara->fanset_param.motor_type ^= 0x01;
							get_pwm_data();
							break;
		case KEY_FANSET_FANMOTOR_TYPE_UP_PAGE62:
							break;
		case KEY_FANSET_FANMOTOR_TYPE_DOWN_PAGE62: 
							break;
		case KEY_FANSET_FANMOTOR_HIGHSPEED_UP_PAGE62: 
							limit_max = 100;
							limit_min = 0;
							u8_calculation(DDR_ADD,DATA_LOOP,limit_max,limit_min,&ptSysPara->fanset_param.high_param);
							if(ptSysPara->fanset_param.motor_type == 0)//新风
							{
								adress = MREGADDRESS_SYS_OUTWIND_PWM_HIGH_SPEED;
							}
							else if(ptSysPara->fanset_param.motor_type == 1)
							{
								adress = MREGADDRESS_SYS_INWIND_PWM_HIGH_SPEED;
							}
							break;
		case KEY_FANSET_FANMOTOR_HIGHSPEED_DOWN_PAGE62: 
							limit_max = 100;
							limit_min = 0;
							u8_calculation(DDR_DEC,DATA_LOOP,limit_max,limit_min,&ptSysPara->fanset_param.high_param);
							
							if(ptSysPara->fanset_param.motor_type == 0)//新风
							{
								adress = MREGADDRESS_SYS_OUTWIND_PWM_HIGH_SPEED;
							}
							else if(ptSysPara->fanset_param.motor_type == 1)
							{
								adress = MREGADDRESS_SYS_INWIND_PWM_HIGH_SPEED;
							}
							break;
		case KEY_FANSET_FANMOTOR_MIDSPEED_UP_PAGE62: 
							limit_max = 100;
							limit_min = 0;
							u8_calculation(DDR_ADD,DATA_LOOP,limit_max,limit_min,&ptSysPara->fanset_param.mid_param);
							if(ptSysPara->fanset_param.motor_type == 0)//新风
							{
								adress = MREGADDRESS_SYS_OUTWIND_PWM_MID_SPEED;
							}
							else if(ptSysPara->fanset_param.motor_type == 1)
							{
								adress = MREGADDRESS_SYS_INWIND_PWM_MID_SPEED;
							}
							break;
		case KEY_FANSET_FANMOTOR_MIDSPEED_DOWN_PAGE62: 
							limit_max = 100;
							limit_min = 0;
							u8_calculation(DDR_DEC,DATA_LOOP,limit_max,limit_min,&ptSysPara->fanset_param.mid_param);
							if(ptSysPara->fanset_param.motor_type == 0)//新风
							{
								adress = MREGADDRESS_SYS_OUTWIND_PWM_MID_SPEED;
							}
							else if(ptSysPara->fanset_param.motor_type == 1)
							{
								adress = MREGADDRESS_SYS_INWIND_PWM_MID_SPEED;
							}
							break;
		case KEY_FANSET_FANMOTOR_LOWSPEED_UP_PAGE62: 
							limit_max = 100;
							limit_min = 0;
							u8_calculation(DDR_ADD,DATA_LOOP,limit_max,limit_min,&ptSysPara->fanset_param.low_param);
							if(ptSysPara->fanset_param.motor_type == 0)//新风
							{
								adress = MREGADDRESS_SYS_OUTWIND_PWM_LOW_SPEED;
							}
							else if(ptSysPara->fanset_param.motor_type == 1)
							{
								adress = MREGADDRESS_SYS_INWIND_PWM_LOW_SPEED;
							}
							break;
		case KEY_FANSET_FANMOTOR_LOWSPEED_DOWN_PAGE62: 
							limit_max = 100;
							limit_min = 0;
							u8_calculation(DDR_DEC,DATA_LOOP,limit_max,limit_min,&ptSysPara->fanset_param.low_param);
							if(ptSysPara->fanset_param.motor_type == 0)//新风
							{
								adress = MREGADDRESS_SYS_OUTWIND_PWM_LOW_SPEED;
							}
							else if(ptSysPara->fanset_param.motor_type == 1)
							{
								adress = MREGADDRESS_SYS_INWIND_PWM_LOW_SPEED;
							}
							break;
		case KEY_FANSET_REMOVEWET_UP_PAGE62:
							break;
		case KEY_FANSET_REMOVEWET_DOWN_PAGE62: 	
							break;
		case KEY_FANSET_485ADRESS_UP_PAGE62: 
							break;
		case KEY_FANSET_485ADRESS_DOWN_PAGE62: 
							break;
		case KEY_FANSET_BAUDRATE_UP_PAGE62: 
							break;
		case KEY_FANSET_BAUDRATE_DOWN_PAGE62: 
							break;
		default: break;
	}

	if(adress != 0)
	{
		APP_oneWire_send_485_data(adress,get_485value(adress));
	}

}


void app_key_setting_choose(void)
{
	//32页-页切换
    SysPara_t *ptSysPara;  
	ptSysPara =  controler_getSysParaPt();

	switch(ptSysPara->page32_keynumberup)
	{
		case KEY_WIFI_PAGE32: 
								ptSysPara->page_number = 42;
								break;//WIFI
		case KEY_TIME_CONTROL_PAGE32: 
								ptSysPara->page_number = 34;
								break;//定时
		case KEY_FILTER_PAGE32: 
								ptSysPara->page_number = 43;
								break;//滤芯
		case KEY_TIME_PAGE32:
								ptSysPara->page_number = 44;
								break;//时间
		case KEY_FACTORY_PAGE32: 
								ptSysPara->page_number = 45;
								break;//工厂
		case KEY_FAULT_PAGE32: 
								ptSysPara->page_number = 46;
								break;//故障
		case KEY_ABOUT_PAGE32: 
								ptSysPara->page_number = 47;
								break;//关于
		case KEY_OTHER_PAGE32: 
								ptSysPara->page_number = 48;
								break;//其他
		case KEY_CANCEL_PAGE32: 
								if(64 == ptSysPara->mode || 65 == ptSysPara->mode)
								{
									ptSysPara->page_number = 30;
								}
								else if(ptSysPara->mode >= 62)
								{
									ptSysPara->page_number = 29;
								}
								break;
				default: break;
	}
	
}

void app_key_timing_page_week(void)
{
	//页34 增加星期
	SysPara_t *ptSysPara;  
	uint8_t i;
	ptSysPara =  controler_getSysParaPt();
	switch(ptSysPara->page34_keynumberup)
	{
		case KEY_WEEK_UP_PAGE34: 
								if(ptSysPara->week_cursor > 0)
								{
									ptSysPara->week_cursor--;//间隔时间需要检测，防止从中间删除导致排序异常 
								}
								else
								{
									for(i = 0; i < 7; i++)//范围0~6
									{
										if((ptSysPara->week_type_line[6-i] & 0x80) == 0x80)
										{
											ptSysPara->week_cursor = 6-i;
											break;
										}
									}
								}
								break;//待定，预留接口
		case KEY_WEEK_DOWN_PAGE34:
								if(ptSysPara->week_cursor > 6)
								{
									ptSysPara->week_cursor = 0;
								}
								else 
								{
									if((ptSysPara->week_type_line[ptSysPara->week_cursor+1] & 0x80) == 0x80)
									{
										ptSysPara->week_cursor++;
									}
									else
									{
										ptSysPara->week_cursor = 0;
									}
								}

							 	break;
		case KEY_TIME_INTERVAL_UP_PAGE34: ;break;
		case KEY_TIME_INTERVAL_DOWN_PAGE34:; ;break;
		case KEY_JUMP_35PAGE_PAGE34: 
								ptSysPara->page_number = 35; 
								
								break;
		case KEY_WEEK_ADD_PAGE34: 
								//显示未勾选的数据
								ptSysPara->week_function_type = 1;
								ptSysPara->page_number = 36;
								break;
		case KEY_WEEK_EDIT_PAGE34: 
								//在已勾选的数据内重新选择
								ptSysPara->week_function_type = 2;
								if(ptSysPara->key_week_message == 0)
								{
									ptSysPara->key_week_message = ptSysPara->week_type_line[ptSysPara->week_cursor];
									ptSysPara->week_type_line[ptSysPara->week_cursor] &= ~0x80;
								}
								ptSysPara->page_number = 36;
								break;
		case KEY_WEEK_DELETE_PAGE34: 
								ptSysPara->week_type_line[ptSysPara->week_cursor] = 0x00;
								for(i = 1; i < 7; i++)
								{
									if(ptSysPara->week_cursor + i < 7)
									{
										if((ptSysPara->week_type_line[ptSysPara->week_cursor+i] & 0x80) == 0x80)
										{
											ptSysPara->week_type_line[ptSysPara->week_cursor+i-1] = ptSysPara->week_type_line[ptSysPara->week_cursor+i];
											ptSysPara->week_type_line[ptSysPara->week_cursor+i] = 0x00;
										}
									}
								}
								if(ptSysPara->week_cursor > 0)

								{
									ptSysPara->week_cursor--;
								}
								break;
		case KEY_CANCEL_PAGE34: 
								
								ptSysPara->page_number = 32; 
								break;
		default: break;
	}
}

void app_key_timing_page_time_interval(void)
{
	//页35 增加时间段
	SysPara_t *ptSysPara;  
	ptSysPara =  controler_getSysParaPt();
	switch(ptSysPara->page35_keynumberup)
	{
		case KEY_TIME_INTERVAL_UP_PAGE35: ;break;//待定，预留接口
		case KEY_TIME_INTERVAL_DOWN_PAGE35: 
							 	break;
		case KEY_WEEK_UP_PAGE35: 
								//ptSysPara->timecontrol_cursor 
								break;
		case KEY_WEEK_DOWN_PAGE35: 
								
								break;
		case KEY_JUMP_34PAGE_PAGE35: 
								ptSysPara->page_number = 34; 
								//ptSysPara->sys_runstatus = SYS_STATUS_TIMING_WEEK;
								break;
		case KEY_TIME_INTERVAL_ADD_PAGE35: 
								ptSysPara->timecontrol_function_type = 1;
								ptSysPara->page_number = 61;//增加
								break;
		case KEY_TIME_INTERVAL_EDIT_PAGE35: 
								ptSysPara->timecontrol_function_type = 2;
								ptSysPara->page_number = 61; //修改
								break;
		case KEY_TIME_INTERVAL_DELETE_PAGE35: ;break;
		case KEY_CANCEL_PAGE35: 
								ptSysPara->page_number = 34; 
								//ptSysPara->sys_runstatus = SYS_STATUS_TIMING_WEEK;
								break;
		default: break;
	}
}

void app_key_week_choose(void)
{
	//页36 星期选择确认	
	SysPara_t *ptSysPara;  
	uint8_t i;
	ptSysPara =  controler_getSysParaPt();

	switch(ptSysPara->page36_keynumber)
	{
		case KEY_MONDAY_PAGE36: 
								if(ptSysPara->dis_week.mon != MONDAY_INVALID)
								{
									ptSysPara->key_week_message ^= 0x01;
									ptSysPara->dis_week.mon = 0;
								}
								break;
		case KEY_TUESDAY_PAGE36: 
								if(ptSysPara->dis_week.tues != TUESDAY_INVALID)
								{
									ptSysPara->key_week_message ^= 0x02;
									ptSysPara->dis_week.tues = 0;
								}
								break;
		case KEY_WEDNESDAY_PAGE36: 
								if(ptSysPara->dis_week.wed != WEDNESDAY_INVALID)
								{
									ptSysPara->key_week_message ^= 0x04;
									ptSysPara->dis_week.wed = 0;
								}
								break;
		case KEY_THURSDAY_PAGE36: 
								if(ptSysPara->dis_week.thur != THURSDAY_INVALID)
								{
									ptSysPara->key_week_message ^= 0x08;
									ptSysPara->dis_week.thur = 0;
								}
								break;
		case KEY_FRIDAY_PAGE36: 
								if(ptSysPara->dis_week.fri != FRIDAY_INVALID)
								{
									ptSysPara->key_week_message ^= 0x10;
									ptSysPara->dis_week.fri = 0;
								}
								break;
		case KEY_SATURDAY_PAGE36: 
								if(ptSysPara->dis_week.sat != SATURDAY_INVALID)
								{
									ptSysPara->key_week_message ^= 0x20;
									ptSysPara->dis_week.sat = 0;
								}
								break;
		case KEY_SUNDAY_PAGE36: 
								if(ptSysPara->dis_week.sun != SUNDAY_INVALID)
								{
									ptSysPara->key_week_message ^= 0x40;
									ptSysPara->dis_week.sun = 0;
								}
								break;

	}

	
	switch(ptSysPara->page36_keynumberup)
	{
		case KEY_SURE_PAGE36: 
								//在34界面显示已选中的星期数据，要建立一个显示的缓存
								if(ptSysPara->week_function_type == 1)
								{
									for(i = 0; i < 8; i++)
									{
										//bit7 标志 bit6 ~bit0 星期数据(7位数据，1位标志)
										if(ptSysPara->key_week_message != 0)
										{
											if((ptSysPara->week_type_line[i] & 0x80) == 0x00)
											{
												ptSysPara->week_type_line[i] |= 0x80;//置位
												ptSysPara->week_type_line[i] |= ptSysPara->key_week_message;
												ptSysPara->key_week_message = 0;
												ptSysPara->week_cursor = i;
												break;
											}
										}
										else
										{
											break;
										}
									}
								}
								else if(ptSysPara->week_function_type == 2)
								{
									if((ptSysPara->week_type_line[ptSysPara->week_cursor] & 0x80) == 0x00)
									{
										ptSysPara->week_type_line[ptSysPara->week_cursor] = 0;
										ptSysPara->week_type_line[ptSysPara->week_cursor] |= 0x80;//置位
										ptSysPara->week_type_line[ptSysPara->week_cursor] |= ptSysPara->key_week_message;
										ptSysPara->key_week_message = 0;
									}
									
								}
								
								ptSysPara->page_number = 34; 
								break;
		case KEY_CANCEL_PAGE36: 
								if(ptSysPara->week_function_type == 2)
								{
									ptSysPara->week_type_line[ptSysPara->week_cursor] |= 0x80;
									ptSysPara->key_week_message = 0;
								}
								else
								{
									ptSysPara->key_week_message = 0;
								}
								ptSysPara->page_number = 34; 
								break;
		default : break;
	}
}

void app_key_timemessage_choose(void)//时段选择页面
{
	SysPara_t *ptSysPara;  
//	uint8_t i;
	ptSysPara =  controler_getSysParaPt();
	

}

void app_key_wifi(void)//42
{
	SysPara_t *ptSysPara;  
	ptSysPara =  controler_getSysParaPt();
	switch(ptSysPara->page42_43_46_47_48keynumberup)
	{
		case KEY_CANCEL_PAGE42: 
							ptSysPara->page_number = 32; 
							break;
		case KEY_CONNECT_PAGE42: break;
		default: break;
	}
}

void app_key_filter(void)//43
{
	SysPara_t *ptSysPara;  
	ptSysPara =  controler_getSysParaPt();
	switch(ptSysPara->page42_43_46_47_48keynumberup)
	{
		case KEY_FILTER_PAGE43: break;
		case KEY_CYCLE_UP_PAGE43: break;		
		case KEY_CYCLE_DOWN_PAGE43: break;
		case KEY_CANCEL_PAGE43: 
							ptSysPara->page_number = 32; 
							break;
		default: break;
	}
}

void app_key_timeset(void)//44
{
	SysPara_t *ptSysPara;  
	uint8_t buff = 0;
	uint8_t year = 0;//2020   0x20
	uint8_t month = 0;
	uint8_t day = 0;
	uint8_t hour = 0;
	uint8_t minute = 0;
	ptSysPara =  controler_getSysParaPt();
	//按下效果由diwen软件实现
	switch(ptSysPara->page44_keynumberup|ptSysPara->page44_keynumberlong)
	{
		case KEY_YEARS_UP_PAGE44: 		
									keyOperation(DDR_ADD,DATA_KEEP,1,YEAR_MAX,YEAR_MIN,&ptSysPara->set_time.year);
									break;
		case KEY_YEARS_DOWN_PAGE44: 	
									keyOperation(DDR_DEC,DATA_KEEP,1,YEAR_MAX,YEAR_MIN,&ptSysPara->set_time.year);
									break;		
		case KEY_MONTH_UP_PAGE44: 		
									keyOperation(DDR_ADD,DATA_LOOP,1,MONTH_MAX,MONTH_MIN,&ptSysPara->set_time.month);
									break;
		case KEY_MONTH_DOWN_PAGE44: 	
									keyOperation(DDR_DEC,DATA_LOOP,1,MONTH_MAX,MONTH_MIN,&ptSysPara->set_time.month);
									break;		
		case KEY_DAY_UP_PAGE44: 		
									keyOperation(DDR_ADD,DATA_LOOP,1,DAY_MAX,DAY_MIN,&ptSysPara->set_time.day);
									break;
		case KEY_DAY_DOWN_PAGE44: 		
									keyOperation(DDR_DEC,DATA_LOOP,1,DAY_MAX,DAY_MIN,&ptSysPara->set_time.day);
									break;		
		case KEY_HOURS_UP_PAGE44: 		
									keyOperation(DDR_ADD,DATA_LOOP,1,HOURS_MAX,HOURS_MIN,&ptSysPara->set_time.hour);
									break;
		case KEY_HOURS_DOWN_PAGE44: 	
									keyOperation(DDR_DEC,DATA_LOOP,1,HOURS_MAX,HOURS_MIN,&ptSysPara->set_time.hour);
									break;		
		case KEY_MINUTE_UP_PAGE44: 		
									keyOperation(DDR_ADD,DATA_LOOP,1,MINUTE_MAX,MINUTE_MIN,&ptSysPara->set_time.minute);
									break;
		case KEY_MINUTE_DOWN_PAGE44: 	
									keyOperation(DDR_DEC,DATA_LOOP,1,MINUTE_MAX,MINUTE_MIN,&ptSysPara->set_time.minute);
									break;
		case KEY_SURE_PAGE44: 	//转BCD码
								buff = (uint8_t)(ptSysPara->set_time.year-2000);
								year = dec_to_bcd(buff);//偏移2000，
								month = dec_to_bcd((uint8_t)ptSysPara->set_time.month);//12转0x12 10转0x10
								day = dec_to_bcd((uint8_t)ptSysPara->set_time.day);//
								hour = dec_to_bcd((uint8_t)ptSysPara->set_time.hour);//
								minute = dec_to_bcd((uint8_t)ptSysPara->set_time.minute);//
								set_rtc(year,month,day,hour,minute);
								//set_rtc(0x24,0x11,0x22,0x11,0x40);
								//显示数据确认更改  					等待迪文确认
								break;
		case KEY_CANCEL_PAGE44: 		
								//显示数据不更改，定时数据可做储存
								ptSysPara->page_number = 32; 			
								break;
		default: break;
	}
}

void app_key_factory(void)//45
{
	SysPara_t *ptSysPara;  
	ptSysPara =  controler_getSysParaPt();
	switch(ptSysPara->page45_keynumberup)
	{
		//5位数 密码，满5位则再次按下 无效
		//按下一位储存 且显示对应按下位数的图形
		case KEY_0_PAGE45: 
							if(ptSysPara->factory.keydowncount < 5)
							{
								ptSysPara->factory.password[ptSysPara->factory.keydowncount] = 1;
								ptSysPara->factory.keydowncount++;
							}
							break;
		case KEY_1_PAGE45: 					
							if(ptSysPara->factory.keydowncount < 5)
							{
								ptSysPara->factory.password[ptSysPara->factory.keydowncount] = 1;
								ptSysPara->factory.keydowncount++;
							}
							break;
		case KEY_2_PAGE45: 					
							if(ptSysPara->factory.keydowncount < 5)
							{
								ptSysPara->factory.password[ptSysPara->factory.keydowncount] = 2;
								ptSysPara->factory.keydowncount++;
							}
							break;
		case KEY_3_PAGE45: 					
							if(ptSysPara->factory.keydowncount < 5)
							{
								ptSysPara->factory.password[ptSysPara->factory.keydowncount] = 3;
								ptSysPara->factory.keydowncount++;
							}
							break;
		case KEY_4_PAGE45: 					
							if(ptSysPara->factory.keydowncount < 5)
							{
								ptSysPara->factory.password[ptSysPara->factory.keydowncount] = 4;
								ptSysPara->factory.keydowncount++;
							}
							break;
		case KEY_5_PAGE45: 					
							if(ptSysPara->factory.keydowncount < 5)
							{
								ptSysPara->factory.password[ptSysPara->factory.keydowncount] = 5;
								ptSysPara->factory.keydowncount++;
							}
							break;
		case KEY_6_PAGE45: 					
							if(ptSysPara->factory.keydowncount < 5)
							{
								ptSysPara->factory.password[ptSysPara->factory.keydowncount] = 6;
								ptSysPara->factory.keydowncount++;
							}

							break;
		case KEY_7_PAGE45: 					
							if(ptSysPara->factory.keydowncount < 5)
							{
								ptSysPara->factory.password[ptSysPara->factory.keydowncount] = 7;
								ptSysPara->factory.keydowncount++;
							}

							break;
		case KEY_8_PAGE45: 					
							if(ptSysPara->factory.keydowncount < 5)
							{
								ptSysPara->factory.password[ptSysPara->factory.keydowncount] = 8;
								ptSysPara->factory.keydowncount++;
							}


							break;
		case KEY_9_PAGE45: 					
							if(ptSysPara->factory.keydowncount < 5)
							{
								ptSysPara->factory.password[ptSysPara->factory.keydowncount] = 9;
								ptSysPara->factory.keydowncount++;
							}
							break;
		case KEY_DEL_PAGE45: 	
								//删除最后输入的一位数据
							ptSysPara->factory.password[ptSysPara->factory.keydowncount] = 0xff;
							ptSysPara->factory.keydowncount--;
							break;
		case KEY_SURE_PAGE45: 	
								if( ptSysPara->factory.password[0] == 9 &&
									ptSysPara->factory.password[1] == 5 &&
									ptSysPara->factory.password[2] == 7 &&
									ptSysPara->factory.password[3] == 1 &&
									ptSysPara->factory.password[4] == 6)
								{//密码正确进入下一级菜单
									
								}
								else
								{
									//错误则清楚密码，显示密码错误菜单
								}
								
								break;
		case KEY_CANCEL_PAGE45: 	
								ptSysPara->factory.keydowncount = 0;
								ptSysPara->factory.password[0] = 0xff;
								ptSysPara->factory.password[1] = 0xff;
								ptSysPara->factory.password[2] = 0xff;
								ptSysPara->factory.password[3] = 0xff;
								ptSysPara->factory.password[4] = 0xff;
								ptSysPara->page_number = 32; 			
								break;
		default: break;
	}
}

void app_key_about(void)//45
{
	SysPara_t *ptSysPara;  
	ptSysPara =  controler_getSysParaPt();
	switch(ptSysPara->page42_43_46_47_48keynumberup)
	{
		case KEY_CANCEL_PAGE47: 					
								ptSysPara->page_number = 32;
								break;
		case KEY_FACTORY_SET_PAGE47: 	
									
								break;
		default: break;
	}
}

void app_key_other(void)
{
	SysPara_t *ptSysPara;  
	ptSysPara =  controler_getSysParaPt();
	switch(ptSysPara->page42_43_46_47_48keynumberup)
	{
		case KEY_QUIET_PAGE48: 					
								break;
		case KEY_EVERBRIGHT_PAGE48: 	
								break;								
		case KEY_OUTDOOR_MESSAGE_PAGE48: 					
								break;
		case KEY_HELP_PAGE48: 	
								break;
		case KEY_CANCEL_PAGE48: 
								ptSysPara->page_number = 32; 	
								break;
		default: break;
	}
}

void app_key_fault(void)
{
	SysPara_t *ptSysPara;  
	ptSysPara =  controler_getSysParaPt();
	switch(ptSysPara->page42_43_46_47_48keynumberup)
	{
		case KEY_CANCEL_PAGE46: 
							ptSysPara->page_number = 32; 
							break;
		default: break;
	}
}
//new
void app_main_control_key_service(unsigned int keynumber)
{
	SysPara_t *ptSysPara;  
	ptSysPara =  controler_getSysParaPt();
	switch(keynumber)	 
	{
		case KEY_HOT_SWITCH_FIRST_DOWN:
							break;
		
		case KEY_HOT_SWITCH_LONG:
				break;

		case KEY_HOT_SWITCH_CONTINUE:
				break;

		case KEY_HOT_SWITCH_UP:
				break;

		case KEY_SETTING_FIRST_DOWN:
				break;

		case KEY_SETTING_LONG:
				break;

		case KEY_SETTING_CONTINUE:

				break;

		case KEY_SETTING_UP:
				ptSysPara->page_number = 32;
				break;

		case KEY_TEMP_ADD_FIRST_DOWN:
				ptSysPara->debugdata = 1;
				break;

		case KEY_TEMP_ADD_LONG:
				ptSysPara->debugdata = 10;
				break;

		case KEY_TEMP_ADD_CONTINUE:
				ptSysPara->debugdata++;
				break;

		case KEY_TEMP_ADD_UP:
				ptSysPara->debugdata = 100;
				break;
		

		case KEY_POWERON_STATE:
				break;
		case KEY_POWERON_UP:
				ptSysPara->page_number = 1;
				break;
		case KEY_GREEN_CHANGE_UP://切换屏保页
				ptSysPara->next_screen_flag = BN_TRUE;
				break;

		case KEY_GOTO_MAIN_CONTROL_UP:
				ptSysPara->page_number = 29;
				break;
		default: break;
	}
}

void app_setting_key_service(unsigned int keynumber)
{
	SysPara_t *ptSysPara;  
	ptSysPara =  controler_getSysParaPt();

	switch(keynumber)
	{
		case KEY_SET_WIFI_UP: ptSysPara->page_number = 51; break;
		case KEY_SET_TIMING_UP: ptSysPara->page_number = 34; break;
		case KEY_SET_FILTER_UP: ptSysPara->page_number = 39; break;
		case KEY_SET_TIME_UP: ptSysPara->page_number = 41; break;
		case KEY_SET_HIGHSET_UP: ptSysPara->page_number = 43;break;
		case KEY_SET_AUTO_UP: ptSysPara->page_number = 45; break;
		case KEY_SET_ABOUT_UP: ptSysPara->page_number = 47; break;
		case KEY_SET_OTHER_UP: ptSysPara->page_number = 49; break;
		case KEY_SET_BACK_UP: ptSysPara->page_number = 29; break;
		default: break;
	}

}

void app_wifi_key_service(unsigned int keynumber)
{
	SysPara_t *ptSysPara;  
	ptSysPara =  controler_getSysParaPt();

	switch(keynumber)
	{
		//连接
		case KEY_SET_BACK_UP: ptSysPara->page_number = 32; break;
		default: break;
	}
}

void app_timecontrol_key_service(unsigned int keynumber)//时段控制
{
	SysPara_t *ptSysPara;  
	ptSysPara =  controler_getSysParaPt();

	switch(keynumber)
	{
		//切换时间编译
		//星期+-
		//时段+-
		//增加
		//编辑
		//删除
		case KEY_SET_BACK_UP: ptSysPara->page_number = 32; break;
		default: break;
	}
}

void app_filter_key_service(unsigned int keynumber)
{
	SysPara_t *ptSysPara;  
	ptSysPara =  controler_getSysParaPt();

	switch(keynumber)
	{
		//周期+-
		//长按复位
		case KEY_SET_BACK_UP: ptSysPara->page_number = 32; break;
		default: break;
	}
}

void app_settime_key_service(unsigned int keynumber)
{
	SysPara_t *ptSysPara;  
	uint8_t offset = 0;
	uint8_t year = 0;
	uint8_t month = 0;
	uint8_t day = 0;
	uint8_t hour = 0;
	uint8_t minute = 0;
	
	ptSysPara =  controler_getSysParaPt();


	switch(keynumber)
	{
		//年+- 连击
		//月+-
		//日+-
		//小时+-
		//分+-
		case KEY_SET_YEAR_ADD_CONTINUE		:  keyOperation(DDR_ADD,DATA_LOOP,1,YEAR_MAX,YEAR_MIN,&ptSysPara->set_time.year);break;
		case KEY_SET_YEAR_ADD_UP			:  keyOperation(DDR_ADD,DATA_LOOP,1,YEAR_MAX,YEAR_MIN,&ptSysPara->set_time.year);break;
		case KEY_SET_YEAR_SUB_CONTINUE		:  keyOperation(DDR_DEC,DATA_LOOP,1,YEAR_MAX,YEAR_MIN,&ptSysPara->set_time.year);break;
		case KEY_SET_YEAR_SUB_UP			:  keyOperation(DDR_DEC,DATA_LOOP,1,YEAR_MAX,YEAR_MIN,&ptSysPara->set_time.year);break;
		case KEY_SET_MONTH_ADD_CONTINUE		:  keyOperation(DDR_ADD,DATA_LOOP,1,MONTH_MAX,MONTH_MIN,&ptSysPara->set_time.month);break;
		case KEY_SET_MONTH_ADD_UP			:  keyOperation(DDR_ADD,DATA_LOOP,1,MONTH_MAX,MONTH_MIN,&ptSysPara->set_time.month);break;
		case KEY_SET_MONTH_SUB_CONTINUE		:  keyOperation(DDR_DEC,DATA_LOOP,1,MONTH_MAX,MONTH_MIN,&ptSysPara->set_time.month);break;
		case KEY_SET_MONTH_SUB_UP			:  keyOperation(DDR_DEC,DATA_LOOP,1,MONTH_MAX,MONTH_MIN,&ptSysPara->set_time.month);break;
		case KEY_SET_DAY_ADD_CONTINUE		:  keyOperation(DDR_ADD,DATA_LOOP,1,DAY_MAX,DAY_MIN,&ptSysPara->set_time.day);break;
		case KEY_SET_DAY_ADD_UP				:  keyOperation(DDR_ADD,DATA_LOOP,1,DAY_MAX,DAY_MIN,&ptSysPara->set_time.day);break;
		case KEY_SET_DAY_SUB_CONTINUE		:  keyOperation(DDR_DEC,DATA_LOOP,1,DAY_MAX,DAY_MIN,&ptSysPara->set_time.day);break;
		case KEY_SET_DAY_SUB_UP				:  keyOperation(DDR_DEC,DATA_LOOP,1,DAY_MAX,DAY_MIN,&ptSysPara->set_time.day);break;
		case KEY_SET_HOUR_ADD_CONTINUE		:  keyOperation(DDR_ADD,DATA_LOOP,1,HOURS_MAX,HOURS_MIN,&ptSysPara->set_time.hour);break;
		case KEY_SET_HOUR_ADD_UP			:  keyOperation(DDR_ADD,DATA_LOOP,1,HOURS_MAX,HOURS_MIN,&ptSysPara->set_time.hour);break;
		case KEY_SET_HOUR_SUB_CONTINUE		:  keyOperation(DDR_DEC,DATA_LOOP,1,HOURS_MAX,HOURS_MIN,&ptSysPara->set_time.hour);break;
		case KEY_SET_HOUR_SUB_UP			:  keyOperation(DDR_DEC,DATA_LOOP,1,HOURS_MAX,HOURS_MIN,&ptSysPara->set_time.hour);break;
		case KEY_SET_MINTUE_ADD_CONTINUE	:  keyOperation(DDR_ADD,DATA_LOOP,1,MINUTE_MAX,MINUTE_MIN,&ptSysPara->set_time.minute);break;
		case KEY_SET_MINTUE_ADD_UP			:  keyOperation(DDR_ADD,DATA_LOOP,1,MINUTE_MAX,MINUTE_MIN,&ptSysPara->set_time.minute);break;
		case KEY_SET_MINTUE_SUB_CONTINUE	:  keyOperation(DDR_DEC,DATA_LOOP,1,MINUTE_MAX,MINUTE_MIN,&ptSysPara->set_time.minute);break;
		case KEY_SET_MINTUE_SUB_UP			:  keyOperation(DDR_DEC,DATA_LOOP,1,MINUTE_MAX,MINUTE_MIN,&ptSysPara->set_time.minute);break;
		case KEY_SET_SURE_UP				:  
											offset = (uint8_t)(ptSysPara->set_time.year-2000);
											year   = dec_to_bcd(offset);//偏移2000，
											month  = dec_to_bcd((uint8_t)ptSysPara->set_time.month);//12转0x12 10转0x10
											day    = dec_to_bcd((uint8_t)ptSysPara->set_time.day);//
											hour   = dec_to_bcd((uint8_t)ptSysPara->set_time.hour);//
											minute = dec_to_bcd((uint8_t)ptSysPara->set_time.minute);//
											set_rtc(year,month,day,hour,minute);
											break;
		case KEY_SET_BACK_UP: ptSysPara->page_number = 32; break;
		default: break;
	}

		
}

void app_factory_key_service(unsigned int keynumber)
{
	SysPara_t *ptSysPara;  
	ptSysPara =  controler_getSysParaPt();

	switch(keynumber)
	{
		//数字键盘
		//删除
		//确认
		case KEY_SET_BACK_UP: ptSysPara->page_number = 32; break;
		default: break;
	}
}

void app_auto_key_service(unsigned int keynumber)
{
	SysPara_t *ptSysPara;  
	ptSysPara =  controler_getSysParaPt();

	switch(keynumber)
	{
		//调节*4 +-
		case KEY_SET_BACK_UP: ptSysPara->page_number = 32; break;
		default: break;
	}
}

void app_about_key_service(unsigned int keynumber)
{
	SysPara_t *ptSysPara;  
	ptSysPara =  controler_getSysParaPt();

	switch(keynumber)
	{
		//恢复出厂设置
		case KEY_SET_BACK_UP: ptSysPara->page_number = 32; break;
		default: break;
	}
}

void app_other_key_service(unsigned int keynumber)
{
	SysPara_t *ptSysPara;  
	ptSysPara =  controler_getSysParaPt();

	switch(keynumber)
	{
		//静音
		//常量
		//室外信息
		//强制制冷
		case KEY_SET_BACK_UP: ptSysPara->page_number = 32; break;
		default: break;
	}
}

void app_key_service(unsigned int runstate,unsigned int keynumber)
{
	switch(runstate)	
	{
		case SYS_STATUS_RUN_MODE: app_main_control_key_service(keynumber); break;
		case SYS_STATUS_SETTING: app_setting_key_service(keynumber); break;
		case SYS_STATUS_WIFI: app_wifi_key_service(keynumber); break;
		case SYS_STATUS_TIMING_WEEK: app_timecontrol_key_service(keynumber); break;
		case SYS_STATUS_FILTER: app_filter_key_service(keynumber); break;
		case SYS_STATUS_TIME: app_settime_key_service(keynumber); break;
		case SYS_STATUS_FACTORY: app_factory_key_service(keynumber); break;
		case SYS_STATUS_AUTO: app_auto_key_service(keynumber); break;
		case SYS_STATUS_ABOUT: app_about_key_service(keynumber); break;
		case SYS_STATUS_OTHER: app_other_key_service(keynumber); break;
		default: break;

	}
}

void app_key_update(systemRunStatus_t _in_sysRunStatus)
{

}

//++++++++++++++++++++++++++++++start+++++++++++++++++++++++++++++++++++++++++++
//****************************按键任务*****************************************
void app_key_scanTask(void)
{      
    SysPara_t *ptSysPara;
	static uint16_t lastSystemMsTime = 0;
	static uint16_t period = 0;
	
	uint8_t i = 0;
	uint8_t timebuf[2] ={0,0};

	uint16_t key_trigger = 0;
	static uint16_t keycount = 0;
	static unsigned int debug[2] ={0,0};
	unsigned int value_temp = 0;
	unsigned char keytype_size = sizeof(key_sign_1_t);

	unsigned int keytype_state = 0;
	static key_sign_1_t key_sign_new[MAX_KEY_GROUP];
	
	ptSysPara =  controler_getSysParaPt();
	period = GetSysTickMillisecond() - lastSystemMsTime;

	//keycount++;



	if(keytype_state = mde_getkey_event(&key_sign_new))
	{
		for(i = 0; i < MAX_KEY_GROUP; i++)
		{
			if(key_sign_new[i].key_down_sign != 0)
			{
				app_key_service(ptSysPara->sys_runstatus,key_sign_new[i].key_down_sign);
				break;
			}
		}
		ptSysPara->updataflag = 5;
	}


	//end
	/*if(mod_key_scantask1(&ptSysPara->key_fanset_param))
	{
		key_trigger = 1;
	}	
	
	if(mod_key_getEvent() || 1 == key_trigger)
    {    
		app_key_update(ptSysPara->sys_runstatus);

		ptSysPara->keydownflag++;
		ptSysPara->updataflag = BN_TRUE;
    }  */
	
	value_temp = ptSysPara->debugdata;
	timebuf[0] = (unsigned char)(value_temp>>8);
	timebuf[1] = (unsigned char)(value_temp);	
	WriteDGUS(0x5120,timebuf,2);


	value_temp = keytype_state;
	timebuf[0] = (unsigned char)(value_temp>>8);
	timebuf[1] = (unsigned char)(value_temp);
	WriteDGUS(0x5121,timebuf,2);

	//显示按键值
	value_temp = debug[0];
	timebuf[0] = (unsigned char)(value_temp>>8);
	timebuf[1] = (unsigned char)(value_temp);
	WriteDGUS(0x5122,timebuf,2);
	
	value_temp = debug[1];
	timebuf[0] = (unsigned char)(value_temp>>8);
	timebuf[1] = (unsigned char)(value_temp);
	WriteDGUS(0x5123,timebuf,2);


	value_temp = ptSysPara->debugcount;
	timebuf[0] = (unsigned char)(value_temp>>8);
	timebuf[1] = (unsigned char)(value_temp);
	WriteDGUS(0x5126,timebuf,2);

	
	value_temp = modbus_master_solid[0].mmoo_runStutus;
	timebuf[0] = (unsigned char)(value_temp>>8);
	timebuf[1] = (unsigned char)(value_temp);
	WriteDGUS(0x5127,timebuf,2);

	value_temp = rx_onewire_dat[8].reg_dat;//modbus_master_solid[0].transmit_buff[0];
	timebuf[0] = (unsigned char)(value_temp>>8);
	timebuf[1] = (unsigned char)(value_temp);
	WriteDGUS(0x5128,timebuf,2);
	
	value_temp = rx_onewire_dat[9].reg_dat;//modbus_master_solid[0].transmit_buff[1];
	timebuf[0] = (unsigned char)(value_temp>>8);
	timebuf[1] = (unsigned char)(value_temp);
	WriteDGUS(0x5129,timebuf,2);
	
	value_temp = rx_onewire_dat[10].reg_dat;//modbus_master_solid[0].receive_buff[0];
	timebuf[0] = (unsigned char)(value_temp>>8);
	timebuf[1] = (unsigned char)(value_temp);
	WriteDGUS(0x512A,timebuf,2);

	value_temp = pull_reg_dat(REG_S_ADRESS_1_OFFSET_1f);//modbus_master_solid[0].receive_buff[1];
	timebuf[0] = (unsigned char)(value_temp>>8);
	timebuf[1] = (unsigned char)(value_temp);
	WriteDGUS(0x512B,timebuf,2);
	
	value_temp = tempBuff[4];
	timebuf[0] = (unsigned char)(value_temp>>8);
	timebuf[1] = (unsigned char)(value_temp);
	WriteDGUS(0x512c,timebuf,2);

	value_temp = statecount[5];
	timebuf[0] = (unsigned char)(value_temp>>8);
	timebuf[1] = (unsigned char)(value_temp);
	WriteDGUS(0x512D,timebuf,2);

	value_temp = statecount[2];
	timebuf[0] = (unsigned char)(value_temp>>8);
	timebuf[1] = (unsigned char)(value_temp);
	WriteDGUS(0x512E,timebuf,2);

	value_temp = statecount[1];//tempBuff[7];
	timebuf[0] = (unsigned char)(value_temp>>8);
	timebuf[1] = (unsigned char)(value_temp);
	WriteDGUS(0x512F,timebuf,2);

	value_temp = statecount[0];//modbus_master_solid[0].transmit_length;
	timebuf[0] = (unsigned char)(value_temp>>8);
	timebuf[1] = (unsigned char)(value_temp);
	WriteDGUS(0x5130,timebuf,2);
	
	value_temp = statecount[4];//key_sign_new[0].key_down_sign;
	timebuf[0] = (unsigned char)(value_temp>>8);
	timebuf[1] = (unsigned char)(value_temp);
	WriteDGUS(0x5131,timebuf,2);
}
//****************************按键任务******************************************


//++++++++++++++++++++++++++++++++end+++++++++++++++++++++++++++++++++++++++++++



//-----------------------APP_KeyBoard.c--END------------------------------------

