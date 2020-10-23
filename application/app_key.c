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
#define KEY_TEMP_ADD				  KeyAloneBit2
#define KEY_TEMP_SUB				  KeyAloneBit3
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

#define	KEY_NUMBER_POWER 				0
#define	KEY_NUMBER_POWEROFF				1
#define	KEY_NUMBER_TEMP_ADD				2
#define	KEY_NUMBER_TEMP_SUB				3
#define	KEY_NUMBER_HUMIDITY_ADD			4
#define	KEY_NUMBER_HUMIDITY_SUB			5
#define	KEY_NUMBER_MODE					6
#define	KEY_NUMBER_SET_UP_STATE			7
#define	KEY_NUMBER_WIND_SPEED			8
#define	KEY_NUMBER_POWEROFF_SURE		9
#define	KEY_NUMBER_POWEROFF_CANCEL		10

#define KEY_TYPE_NUMBER					5
#define	KEY_SERVICE_POWER_NULL					(0)
#define	KEY_SERVICE_POWER_STATE					(KEY_NUMBER_POWER * KEY_TYPE_NUMBER + KEY_STATE)
#define	KEY_SERVICE_POWER_FIRST_DOWN			(KEY_NUMBER_POWER * KEY_TYPE_NUMBER + KEY_DOWN)
#define	KEY_SERVICE_POWER_LONG					(KEY_NUMBER_POWER * KEY_TYPE_NUMBER + LONG_KEY)	
#define	KEY_SERVICE_CONTINUE					(KEY_NUMBER_POWER * KEY_TYPE_NUMBER + CONTINUE)
#define	KEY_SERVICE_POWER_UP					(KEY_NUMBER_POWER * KEY_TYPE_NUMBER + KEY_UP)
												
#define	KEY_NUMBER_POWEROFF_NULL				(0)
#define	KEY_NUMBER_POWEROFF_STATE				(KEY_NUMBER_POWEROFF * KEY_TYPE_NUMBER + KEY_STATE)
#define	KEY_NUMBER_POWEROFF_FIRST_DOWN			(KEY_NUMBER_POWEROFF * KEY_TYPE_NUMBER + KEY_DOWN)
#define	KEY_NUMBER_POWEROFF_LONG				(KEY_NUMBER_POWEROFF * KEY_TYPE_NUMBER + LONG_KEY)	
#define	KEY_NUMBER_POWEROFF_CONTINUE			(KEY_NUMBER_POWEROFF * KEY_TYPE_NUMBER + CONTINUE)
#define	KEY_NUMBER_POWEROFF_UP					(KEY_NUMBER_POWEROFF * KEY_TYPE_NUMBER + KEY_UP)												
												
#define	KEY_NUMBER_TEMP_ADD_NULL				(0)
#define	KEY_NUMBER_TEMP_ADD_STATE				(KEY_NUMBER_TEMP_ADD * KEY_TYPE_NUMBER + KEY_STATE)
#define	KEY_NUMBER_TEMP_ADD_FIRST_DOWN			(KEY_NUMBER_TEMP_ADD * KEY_TYPE_NUMBER + KEY_DOWN)
#define	KEY_NUMBER_TEMP_ADD_LONG				(KEY_NUMBER_TEMP_ADD * KEY_TYPE_NUMBER + LONG_KEY)	
#define	KEY_NUMBER_TEMP_ADD_CONTINUE			(KEY_NUMBER_TEMP_ADD * KEY_TYPE_NUMBER + CONTINUE)
#define	KEY_NUMBER_TEMP_ADD_UP					(KEY_NUMBER_TEMP_ADD * KEY_TYPE_NUMBER + KEY_UP)	

#define	KEY_NUMBER_TEMP_SUB_NULL				(0)
#define	KEY_NUMBER_TEMP_SUB_STATE				(KEY_NUMBER_TEMP_SUB * KEY_TYPE_NUMBER + KEY_STATE)
#define	KEY_NUMBER_TEMP_SUB_FIRST_DOWN			(KEY_NUMBER_TEMP_SUB * KEY_TYPE_NUMBER + KEY_DOWN)
#define	KEY_NUMBER_TEMP_SUB_LONG				(KEY_NUMBER_TEMP_SUB * KEY_TYPE_NUMBER + LONG_KEY)	
#define	KEY_NUMBER_TEMP_SUB_CONTINUE			(KEY_NUMBER_TEMP_SUB * KEY_TYPE_NUMBER + CONTINUE)
#define	KEY_NUMBER_TEMP_SUB_UP					(KEY_NUMBER_TEMP_SUB * KEY_TYPE_NUMBER + KEY_UP)	



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
	INT16U adressoffset = 0;
	INT8U writebuf[2] ={0,0};

	/*WriteDGUS(REG_KEY_MODE_ADD,writebuf,2);
	WriteDGUS(REG_KEY_MODE_SUB,writebuf,2);
	WriteDGUS(REG_KEY_HUMIDITY_ADD,writebuf,2);
	WriteDGUS(REG_KEY_HUMIDITY_SUB,writebuf,2);
	WriteDGUS(REG_KEY_WIND_SPEED,writebuf,2);
	WriteDGUS(REG_KEY_TIMING,writebuf,2);
	WriteDGUS(REG_KEY_SETTING,writebuf,2);
	WriteDGUS(REG_KEY_POWEROFF,writebuf,2);
	WriteDGUS(REG_KEY_POWEROFF_SURE,writebuf,2);
	WriteDGUS(REG_KEY_POWEROFF_CANCEL,writebuf,2);
	WriteDGUS(REG_KEY_POWER,writebuf,2);
	WriteDGUS(REG_KEY_RESET,writebuf,2);
	WriteDGUS(REG_KEY_SCREEN_SAVER,writebuf,2);
	
	adressoffset = REG_KEY_WEEK_CHOOSE_MONDAY;//0x5800
	do
	{
		WriteDGUS(adressoffset,writebuf,2);
		adressoffset += 2;
	}while(adressoffset > REG_PAGE35_KEY_CANCEL);*/
//36页面 周一 ~ 周日按键定义

	//WriteDGUS(REG_KEY_POWER,writebuf,2);
	//WriteDGUS(REG_KEY_SETTING,writebuf,2);
	//WriteDGUS(KEY_POWEROFF,writebuf,2);

		
	//WriteDGUS(REG_KEY_MODE_ADD,writebuf,2);
	//WriteDGUS(REG_KEY_MODE_SUB,writebuf,2);
	WriteDGUS(REG_KEY_HUMIDITY_ADD,writebuf,2);
	WriteDGUS(REG_KEY_HUMIDITY_SUB,writebuf,2);
	WriteDGUS(REG_KEY_WIND_SPEED,writebuf,2);
	//WriteDGUS(REG_KEY_TIMING,writebuf,2);
	//WriteDGUS(REG_KEY_SETTING,writebuf,2);
	WriteDGUS(REG_KEY_POWEROFF,writebuf,2);
	WriteDGUS(REG_KEY_POWEROFF_SURE,writebuf,2);
	WriteDGUS(REG_KEY_POWEROFF_CANCEL,writebuf,2);
	WriteDGUS(REG_KEY_POWER,writebuf,2);
	WriteDGUS(REG_KEY_RESET,writebuf,2);
	WriteDGUS(REG_KEY_OUT_SCREEN_SAVER,writebuf,2);
	WriteDGUS(REG_KEY_INTO_SCREEN_SAVER,writebuf,2);
	
	//32
	WriteDGUS(REG_KEY_WIFI,writebuf,2);
	WriteDGUS(REG_KEY_TIME_CONTROL,writebuf,2);
	WriteDGUS(REG_KEY_FILTER,writebuf,2);
	WriteDGUS(REG_KEY_TIME,writebuf,2);
	WriteDGUS(REG_KEY_FACTORY,writebuf,2);
	WriteDGUS(REG_KEY_FAULT,writebuf,2);
	WriteDGUS(REG_KEY_ABOUT,writebuf,2);	
	WriteDGUS(REG_KEY_OTHER,writebuf,2);
	WriteDGUS(REG_KEY_CANCEL_PAGE32,writebuf,2);

	//34
	WriteDGUS(REG_PAGE34_KEY_JUMP_35PAGE,writebuf,2);
	WriteDGUS(REG_PAGE34_KEY_CANCEL,writebuf,2);
	WriteDGUS(REG_PAGE34_KEY_WEEK_ADD,writebuf,2);
	WriteDGUS(REG_PAGE34_KEY_WEEK_EDIT,writebuf,2);
	//35
	WriteDGUS(REG_PAGE35_KEY_JUMP_34PAGE,writebuf,2);
	WriteDGUS(REG_PAGE35_KEY_CANCEL,writebuf,2);	
	WriteDGUS(REG_PAGE35_KEY_TIME_INTERVAL_ADD,writebuf,2);
	WriteDGUS(REG_PAGE35_KEY_TIME_INTERVAL_EDIT,writebuf,2);
	//36
	WriteDGUS(REG_KEY_WEEK_SURE,writebuf,2);
	WriteDGUS(REG_KEY_WEEK_CANCEL,writebuf,2);

	//42
	WriteDGUS(REG_PAGE42_KEY_CANCEL,writebuf,2);
	//43
	WriteDGUS(REG_PAGE43_KEY_CANCEL,writebuf,2);

	//44
	WriteDGUS(REG_PAGE44_KEY_SURE,writebuf,2);
	WriteDGUS(REG_PAGE44_KEY_CANCEL,writebuf,2);

	//45
	WriteDGUS(REG_PAGE45_KEY_SURE,writebuf,2);
	WriteDGUS(REG_PAGE45_KEY_CANCEL,writebuf,2);

	//46
	WriteDGUS(REG_PAGE46_KEY_CANCEL,writebuf,2);
	
	//47
	WriteDGUS(REG_PAGE47_KEY_CANCEL,writebuf,2);
	WriteDGUS(REG_PAGE47_FACTORY,writebuf,2);	
	//48
	WriteDGUS(REG_PAGE48_KEY_CANCEL,writebuf,2);

	//WriteDGUS(REG_PAGE61_SURE,writebuf,2);
//	WriteDGUS(REG_PAGE61_CANCEL,writebuf,2);	
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
	SysPara_t *ptSysPara;  
    int8_t keychangeflag = 0;
	int8_t ddr = 0;
	keyActionType_t key_action;
	uint16_t adress = 0;
	uint8_t	keynumber_buf[2] = {0,0};
	static uint8_t misoperationflag = 0;

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
	}
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








void app_key_update(systemRunStatus_t _in_sysRunStatus)
{
    switch(_in_sysRunStatus)
    {               
		case SYS_STATUS_POWER_OFF:        							;     				break;
		case SYS_STATUS_SCREEN_SAVER:								;	 	 			break;
		case SYS_STATUS_RUN_MODE:           app_key_main_control();
											app_key_fanset();
											break;
		case SYS_STATUS_SETTING:         	app_key_setting_choose();     				break;     
		case SYS_STATUS_TIMING_WEEK: 		app_key_timing_page_week();	  				break;
		case SYS_STATUS_TIMING_INTERVAL:	app_key_timing_page_time_interval();     	break;
		case SYS_STATUS_TIMING_WEEK_ADD:    app_key_week_choose();						break;
		case SYS_STATUS_TIMING_TIMECONTROL_ADD: app_key_timemessage_choose();           break;
		case SYS_STATUS_WIFI:				app_key_wifi();								break;
		case SYS_STATUS_FILTER:				app_key_filter();							break;
		case SYS_STATUS_TIME:				app_key_timeset();							break;
		case SYS_STATUS_FACTORY:			app_key_factory();							break;
		case SYS_STATUS_FAULT:				app_key_fault();							break;
		case SYS_STATUS_ABOUT:				app_key_about();							break;
		case SYS_STATUS_OTHER:				app_key_other();							break;
		default:break;
    }       
	//临时//清除故障
	if(PUSH_DOWN & mod_keyOperation(KEY_RESET,0xffff,0xffff))
	{
		//APP_oneWire_send_485_data(MREGADDRESS_SYS_FAULT_RESET_BYTE,0x003f);
	}
}

//++++++++++++++++++++++++++++++start+++++++++++++++++++++++++++++++++++++++++++
//****************************按键任务*****************************************
void app_key_scanTask(void)
{      
    SysPara_t *ptSysPara;  
	uint8_t timebuf[2] ={0,0};

	uint16_t key_trigger = 0;
	static uint16_t keycount = 0;
	static uint16_t time = 0;
	static unsigned int first_key_del = 0;
	static unsigned int debug[2] ={0,0};
	unsigned int value_temp = 0;
	unsigned char keytype_size = sizeof(key_sign_1_t);

	unsigned int keytype_state = 0;
	static key_sign_1_t key_sign_new[MAX_KEY_GROUP];
	
	ptSysPara =  controler_getSysParaPt();

	mod_key_scanTask(GetSysTickMillisecond());	 

	//new
	keytype_state = mde_getkey_event(&key_sign_new);
	if(1)
	{//有按键按下
		//keytype_state = 1;
		
		switch(key_sign_new[0].key_down_sign)
		{
			case KEY_NUMBER_TEMP_ADD_FIRST_DOWN:
					debug[0] = 10;
					break;

			case KEY_NUMBER_TEMP_ADD_LONG:
					debug[0] = 20;
					break;

			case KEY_NUMBER_TEMP_ADD_CONTINUE:
					if(debug[0] < 30)
					{
						debug[0] = 30;
					}
					else
					{
						debug[0]++;
					}
					break;

			case KEY_NUMBER_TEMP_ADD_UP:
					debug[0] = 100;
					break;

			case KEY_NUMBER_TEMP_SUB_FIRST_DOWN:
					debug[1] = 10;
					break;

			case KEY_NUMBER_TEMP_SUB_LONG:
					debug[1] = 20;
					break;

			case KEY_NUMBER_TEMP_SUB_CONTINUE:
					if(debug[1] < 30)
					{
						debug[1] = 30;
					}
					else
					{
						debug[1]++;
					}
					break;

			case KEY_NUMBER_TEMP_SUB_UP:
					debug[1] = 101;
					break;

			default: break;
		}
		
	}

	//end
	if(mod_key_scantask1(&ptSysPara->key_fanset_param))
	{
		key_trigger = 1;
	}	
	
	if(mod_key_getEvent() || 1 == key_trigger)
    {    
		app_key_update(ptSysPara->sys_runstatus);

		ptSysPara->keydownflag++;
		ptSysPara->updataflag = BN_TRUE;
    }  
	
	value_temp = key_sign_new[0].key_down_sign;
	timebuf[0] = (unsigned char)(value_temp>>8);
	timebuf[1] = (unsigned char)(value_temp);	
	WriteDGUS(0x5120,timebuf,2);
	
	value_temp = keytype_state;
	timebuf[0] = (unsigned char)(value_temp>>8);
	timebuf[1] = (unsigned char)(value_temp);
	WriteDGUS(0x5121,timebuf,2);

	value_temp = debug[0];
	timebuf[0] = (unsigned char)(value_temp>>8);
	timebuf[1] = (unsigned char)(value_temp);
	WriteDGUS(0x5122,timebuf,2);
	
	value_temp = debug[1];
	timebuf[0] = (unsigned char)(value_temp>>8);
	timebuf[1] = (unsigned char)(value_temp);
	WriteDGUS(0x5123,timebuf,2);
	
	//ReadDGUS(0x14,timebuf,2);//读取当前页
	//WriteDGUS(WATCH6_WINDOW,timebuf,2);

	
	if(timecount == 0)
	{
		timecount = 200;
	}
	else
	{
		time = timecount;
	}
	
}
//****************************按键任务******************************************


//++++++++++++++++++++++++++++++++end+++++++++++++++++++++++++++++++++++++++++++



//-----------------------APP_KeyBoard.c--END------------------------------------

