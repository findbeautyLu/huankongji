/*******************************************************************************
*
*	模块名称 : APP控制台
*	文件名称 : APP.control.c
*	版    本 : V1.0
*	说    明 : 1、处理逻辑
*                  
*                 
*	修改记录 :
*		版本号  日期        作者         说明
*		V1.0   2019-08-27  zhoujh&Linzl  正式发布
*	Copyright (C), 2015-2020,  menredGroup
*
*******************************************************************************/
#include ".\app_configure.h"
/******************************************************************************/ 
//static timeOutEvent_t timeOutEvent[DELAY_TIMER_MAX];
//preheatPara_t preheatPara;
//++++++++++++++++++++++++++++++start+++++++++++++++++++++++++++++++++++++++++++


#define TIME_1S				1000

#define SCREEN_SAVER_SWITCH_TIME			(TIME_1S * 10)
#define BACK_SCREEN_SAVER_TIME				(TIME_1S * 30)
SysPara_t s_sysPara;




SysPara_t * controler_getSysParaPt(void)
{

    return &s_sysPara;
}

/*RecordPara_t * controler_getSysParaRecordPt(void)
{
    return &s_sysPara.record;
}*/
//***********************系统参数和存储参数接口*********************************
//------------------------------E N D-------------------------------------------




//++++++++++++++++++++++++++++++start+++++++++++++++++++++++++++++++++++++++++++
//***************************控制台初始化***************************************

void app_con_gotoFac(void)
{
	s_sysPara.debugcount = 0;
	s_sysPara.sys_runstatus             = SYS_STATUS_RUN_MODE;
	s_sysPara.mode 						= MODE_INIT;
	s_sysPara.humidity_set 				= HUMIDITY_SET_INIT;
	s_sysPara.windspeed 				= WINDSPEED_INIT;
	s_sysPara.timer 					= TIMER_INIT;
	s_sysPara.setting 					= SETTING_INIT;
	s_sysPara.poweroff 					= POWEROFF_INIT;
	s_sysPara.humidity_dis_key			= KEY_INIT;//按键图标显示，后续图标可能要变化
	s_sysPara.mode_dis_key				= KEY_INIT;
	s_sysPara.page_number				= 0;
	s_sysPara.read_2401_adress_data     = 0;
	s_sysPara.key_week_message			= 0;
	s_sysPara.week_cursor 				= 0;
	s_sysPara.week_type_line[0]			= 0;
	s_sysPara.week_type_line[1] 		= 0;
	s_sysPara.week_type_line[2] 		= 0;
	s_sysPara.week_type_line[3] 		= 0;
	s_sysPara.week_type_line[4] 		= 0;
	s_sysPara.week_type_line[5] 		= 0;
	s_sysPara.week_type_line[6] 		= 0;
	s_sysPara.week_type_line[7] 		= 0;	
	s_sysPara.week_type_column			= 0;
	s_sysPara.debugdata					= 0;
	s_sysPara.set_time.year				= 2020;
	s_sysPara.set_time.month			= 9;
	s_sysPara.set_time.day				= 3;
	s_sysPara.set_time.hour				= 19;
	s_sysPara.set_time.minute			= 30;
	s_sysPara.dynamic_circular			= 79;
	s_sysPara.fanset_param.motor_type   = 0;
	s_sysPara.fanset_param.low_param	= 0;
	s_sysPara.fanset_param.mid_param	= 0;
	s_sysPara.fanset_param.high_param	= 0;
	s_sysPara.poweronflag				= 0;
	keynumber_1.key_sign.trigger_sign_lock		= 0;
	keynumber_1.key_sign.trigger_sign_timecount	= 0;
	keynumber_1.key_sign.trigger_sign			= 0;

	
}

//***************************控制台初始化***************************************
//------------------------------E N D-------------------------------------------


void app_control_timeout(void)
{
	static uint16_t lastSystemMsTime = 0;	  
	static uint16_t period = 0;
	SysPara_t *ptSysPara;  
	ptSysPara =  controler_getSysParaPt();
	period = GetSysTickMillisecond() - lastSystemMsTime;
	
	if(period >= 1000)
	{
		lastSystemMsTime = GetSysTickMillisecond(); 
		ptSysPara->communicationflag++;
	}
}





//++++++++++++++++++++++++++++++start+++++++++++++++++++++++++++++++++++++++++++
//************************测量温度和设定温度************************************

/*void blinktime_control(uint8_t *timercontrol)
{
	uint8_t timedate;
	timedate = *timercontrol;
	if(timedate > 1)
	{
		timedate--;
	}
	else if(timedate == 1)
	{
		timedate = 0;
	}
	else
	{
		timedate = 1;
	}

	*timercontrol = timedate;
}*/

void app_page_switch(void)
{
	SysPara_t *ptSysPara;  
	uint8_t now_page[4] = {0x5a,0x01,0x00,0x00};//01
	static uint8_t currentpage = 0;
	ptSysPara =  controler_getSysParaPt();
	if(ptSysPara->page_number != currentpage)//可以考虑增加一个锁,必须由开机界面才能正常页面切换
	{
		currentpage = ptSysPara->page_number;
		switch(currentpage)
		{
			//case POWER_ON_PAGE_0: ptSysPara->sys_runstatus = SYS_STATUS_POWER_OFF;						break;
			case ONE_MAIN_CONTROL_PAGE_29: ptSysPara->sys_runstatus = SYS_STATUS_RUN_MODE;				break;
			case TWO_MAIN_CONTROL_PAGE_30: ptSysPara->sys_runstatus = SYS_STATUS_RUN_MODE;				break;
			case TIMECONTROL_PAGE_32: ptSysPara->sys_runstatus = SYS_STATUS_SETTING;					break;
			case TIMECONTROL_WEEK_PAGE_34: ptSysPara->sys_runstatus = SYS_STATUS_TIMING_WEEK;			break;
			case TIMECONTROL_TIME_PAGE_35: ptSysPara->sys_runstatus = SYS_STATUS_TIMING_INTERVAL;		break;
			case TIMECONTROL_WEEK_EDIT_PAGE_36: ptSysPara->sys_runstatus = SYS_STATUS_TIMING_WEEK_ADD;	break;
			case TIMECONTROL_EDIT_PAGE_61: ptSysPara->sys_runstatus = SYS_STATUS_TIMING_TIMECONTROL_ADD;break;
			case WIFI_PAGE_42: ptSysPara->sys_runstatus = SYS_STATUS_WIFI;								break;
			case FILTER_PAGE_43: ptSysPara->sys_runstatus = SYS_STATUS_FILTER;							break;
			case TIME_PAGE_44: ptSysPara->sys_runstatus = SYS_STATUS_TIME;								break;
			case FACTORY_PAGE_45: ptSysPara->sys_runstatus = SYS_STATUS_FACTORY;						break;
			case FAULT_PAGE_46: ptSysPara->sys_runstatus = SYS_STATUS_FAULT;							break;
			case ABOUT_PAGE_47: ptSysPara->sys_runstatus = SYS_STATUS_ABOUT;							break;
			case OTHER_PAGE_48: ptSysPara->sys_runstatus = SYS_STATUS_OTHER;							break;
			default: ptSysPara->sys_runstatus = SYS_STATUS_RUN_MODE;									break;			
		}
		app_keyinit_jumppage();
		now_page[3] = currentpage;
		WriteDGUS(0x84,now_page,4); 
		//清除按键滞留
		
	}
}

void app_into_screen_saver(void)
{
    static uint16_t lastSystemMsTime = 0;     
    static uint16_t period = 0;
	static uint8_t keydowncount = 0;
    SysPara_t *ptSysPara;  
	ptSysPara =  controler_getSysParaPt();
    period = GetSysTickMillisecond() - lastSystemMsTime;
	if(keydowncount != ptSysPara->keydownflag)
	{
		keydowncount = ptSysPara->keydownflag;
		lastSystemMsTime = GetSysTickMillisecond(); 
	}
	else if(ptSysPara->page_number == 1)
	{
		if(period >= 80)
		{	
			lastSystemMsTime = GetSysTickMillisecond(); 
			ptSysPara->page_number++;
			APP_oneWire_send_485_data(MRegaddr_NewairControlW,get_485value(MRegaddr_NewairControlW));
		}
	}
	else if(ptSysPara->page_number <= 24 && ptSysPara->page_number > 1)//开机动画切换
	{
		if(period >= 80)
		{			
			lastSystemMsTime = GetSysTickMillisecond(); 
			ptSysPara->page_number++;
		}
	}
	else if(ptSysPara->page_number < 29 && ptSysPara->page_number >= 25)
	{//屏保切换
		if(period >= SCREEN_SAVER_SWITCH_TIME)
		{
			lastSystemMsTime = GetSysTickMillisecond(); 
			ptSysPara->page_number = 29;	
			/*if(ptSysPara->page_number == 28)
			{
				ptSysPara->page_number = 25;	
			}
			else
			{
				ptSysPara->page_number ++;
			}*/
		}
	}	
	else if(ptSysPara->page_number >= 29 && ptSysPara->page_number != 46)//在非屏保界面
	{
		if(period >= BACK_SCREEN_SAVER_TIME)
		{
			lastSystemMsTime = GetSysTickMillisecond(); 
			//ptSysPara->page_number = 25;
		}
	}
}

uint8_t app_power_control(void)
{
	static uint8_t powertime_control = 0; 
	
    static uint16_t lastSystemMsTime = 0;     
    static uint16_t period = 0;
    period = GetSysTickMillisecond() - lastSystemMsTime;
	if(period > 500)
	{
		lastSystemMsTime = GetSysTickMillisecond(); 
		if(powertime_control < 20)
		{
			powertime_control++;
		}
	}

	if(powertime_control > 4)
	{
		return 1;
	}
	else
	{
		return 0;
	}
	
}

void app_eeprom_logic(void)
{
	static uint16_t lastSystemMsTime = 0;
	static uint16_t lastSystemMsTime1 = 0;	  
	static uint16_t period = 0;
	static uint16_t period1 = 0;
	static uint8_t keydowncount = 0;
	static uint8_t storage_lock = 0;
	SysPara_t *ptSysPara;  
	ptSysPara =  controler_getSysParaPt();
	period = GetSysTickMillisecond() - lastSystemMsTime;
	period1 = GetSysTickMillisecond() - lastSystemMsTime1;

	if(period1 > 500)
	{
		lastSystemMsTime1 = GetSysTickMillisecond(); 
		rdtime();
	}
	
	if(keydowncount != ptSysPara->keydownflag)
	{
		storage_lock = 0;
		keydowncount = ptSysPara->keydownflag;
		lastSystemMsTime = GetSysTickMillisecond(); 
	}
	else
	{
		if(0 == storage_lock)
		{
			if(period > 5000)
			{
				storage_lock = 1;
				Write_Nor_Flash();//按键后5s提交储存一次
			}
		}
	}
}

void app_circular_switch(void)
{
	static uint16_t lastSystemMsTime = 0;	  
	static uint16_t period = 0;
	SysPara_t *ptSysPara;  
	ptSysPara =  controler_getSysParaPt();
	period = GetSysTickMillisecond() - lastSystemMsTime;
	if(0)//ptSysPara->page_number >= 25 && ptSysPara->page_number <= 30)
	{

	}
	else
	{
		if(period > 1000)
		{
			ptSysPara->updataflag = 1;
			lastSystemMsTime = GetSysTickMillisecond(); 
			//ptSysPara->count++;
			//APP_oneWire_send_485_data(MRegaddr_Aircod_Mode,get_485value(MRegaddr_Aircod_Mode));
			
			if(ptSysPara->fanset_param.motor_type == 0)//新风
			{
				if(ptSysPara->fanset_param.low_param == 0 && ptSysPara->read_244B_LOW_PWM < 100)
				{
					ptSysPara->fanset_param.low_param = ptSysPara->read_244B_LOW_PWM;
				}
				
				if(ptSysPara->fanset_param.mid_param == 0 && ptSysPara->read_244C_MID_PWM < 100)
				{
					ptSysPara->fanset_param.mid_param = ptSysPara->read_244C_MID_PWM;
				}
				
				if(ptSysPara->fanset_param.high_param == 0 && ptSysPara->read_244D_HIGH_PWM < 100)
				{
					ptSysPara->fanset_param.high_param = ptSysPara->read_244D_HIGH_PWM;
				}
			}
			else if(ptSysPara->fanset_param.motor_type == 1)//回风
			{
				if(ptSysPara->fanset_param.low_param == 0 && ptSysPara->read_2448_LOW_PWM < 100)
				{
					ptSysPara->fanset_param.low_param = ptSysPara->read_2448_LOW_PWM;
				}
				
				if(ptSysPara->fanset_param.mid_param == 0 && ptSysPara->read_2449_MID_PWM < 100)
				{
					ptSysPara->fanset_param.mid_param = ptSysPara->read_2449_MID_PWM;
				}
				
				if(ptSysPara->fanset_param.high_param == 0 && ptSysPara->read_244A_HIGH_PWM < 100)
				{
					ptSysPara->fanset_param.high_param = ptSysPara->read_244A_HIGH_PWM;
				}
			}
		}
	}

	/*if(ptSysPara->count > 300)
	{
		ptSysPara->count = 0;
		APP_oneWire_send_485_data(MRegaddr_Aircod_Mode,get_485value(MRegaddr_Aircod_Mode));
	}*/
}

uint8_t app_control_scanTask(void)
{
	if(app_power_control())
	{
		app_page_switch();//切换页面
		app_circular_switch();//动态切换
		app_into_screen_saver();//屏保
	//	app_control_timeout();//通讯异常计时
	//	app_eeprom_logic();//存储
		return 1; 
	}
	else
	{
		return 0;
	}
	
}
//**************************超时时间扫描****************************************
//------------------------------E N D-------------------------------------------


