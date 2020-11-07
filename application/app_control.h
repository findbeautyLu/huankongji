//++++++++++++++++++++++++++++++start+++++++++++++++++++++++++++++++++++++++++++
#ifndef _APP_CONTROL_H
#define _APP_CONTROL_H
//------------------------------E N D-------------------------------------------
#include ".\app_configure.h"
//#include "..\.\application\app_preheating.h"


#define STEP_TEMP                  5

#define  ms_200                    200
#define  ms_500                    500
#define  ms_1000                   1000
#define  ms_1500                   1500
#define  ms_2000                   2000
#define  ms_3000                   3000
#define  ms_5000                   5000
#define  ms_7000                   7000
#define  ms_10000                  10000
#define  ms_12000                  12000
#define  ms_30000                  30000
#define  ms_60000                  60000

#define HALFHOUR				  360

#define WIND_DIS_MIN				1
#define WIND_DIS_MAX				3
#define TIMER_DIS_MIN				54
#define TIMER_DIS_MAX				57
#define SETING_DIS_ON				58
#define SETING_DIS_OFF				59
#define POWEROFF_DIS_ON				60
#define POWEROFF_DIS_OFF			61
#define MODE_DIS_MIN				1
#define	MODE_DIS_MAX				4
#define AIR_MODE_DIS_MIN			0
#define AIR_MODE_DIS_MAX			2

#define HUMIDITY_MIN				45
#define	HUMIDITY_MAX				65
#define TEMP_MIN				   160
#define	TEMP_MAX				   300

#define MODE_INIT					MODE_DIS_MIN
#define HUMIDITY_SET_INIT			55		
#define WINDSPEED_INIT				WIND_DIS_MIN
#define TIMER_INIT					TIMER_DIS_MIN
#define SETTING_INIT				SETING_DIS_ON	
#define POWEROFF_INIT				POWEROFF_DIS_ON
#define KEY_INIT					1

#define MONDAY_INVALID							7
#define TUESDAY_INVALID							8
#define WEDNESDAY_INVALID						9
#define THURSDAY_INVALID						10
#define FRIDAY_INVALID							11
#define SATURDAY_INVALID						12
#define SUNDAY_INVALID							13

#define MONDAY_VALID							14
#define TUESDAY_VALID							15
#define WEDNESDAY_VALID							16
#define THURSDAY_VALID							17
#define FRIDAY_VALID							18
#define SATURDAY_VALID							19
#define SUNDAY_VALID							20

#define PAGE_29						29
#define PAGE_30						30
#define PAGE_32						32
#define PAGE_34						34
#define PAGE_35						35
#define PAGE_36						36

#define POWER_ON_PAGE_0						    0
#define ONE_MAIN_CONTROL_PAGE_29			29
#define TWO_MAIN_CONTROL_PAGE_30			30
//31 确认关机界面  33为32的按下状态，但现在位置对不齐暂不考虑
#define TIMECONTROL_WEEK_PAGE_34			34
#define TIMECONTROL_TIME_PAGE_35			35
#define TIMECONTROL_WEEK_EDIT_PAGE_36		36
#define TIMECONTROL_EDIT_PAGE_61   			61
//#define TIMECONTROL_TIME_EDIT

#define WIFI_PAGE_51				51
#define TIMECONTROL_PAGE_32			32
#define FILTER_PAGE_39				39
#define TIME_PAGE_41				41
#define FACTORY_PAGE_43				43
#define AUTO_PAGE_45				45

#define FAULT_PAGE_46				46
#define ABOUT_PAGE_47				47
#define OTHER_PAGE_49				49

#define YEAR_MAX					2050
#define YEAR_MIN					2000
#define MONTH_MAX					12
#define MONTH_MIN					1
#define DAY_MAX						31
#define DAY_MIN						1
#define HOURS_MAX					23
#define HOURS_MIN					0
#define MINUTE_MAX					59
#define MINUTE_MIN					0

//++++++++++++++++++++++++++++++start+++++++++++++++++++++++++++++++++++++++++++
//****************************系统状态******************************************
typedef enum
{
    SYS_STATUS_POWER_OFF = ((uint8_t)0x00), 
	SYS_STATUS_SCREEN_SAVER,
    SYS_STATUS_RUN_MODE,
    SYS_STATUS_SETTING,
    SYS_STATUS_TIMING_WEEK,//设置 - 定时 - 星期
	SYS_STATUS_TIMING_INTERVAL,//设置 - 定时 - 时段
	
    SYS_STATUS_TIMING_WEEK_ADD,//编辑和添加整合了，只有一项
    SYS_STATUS_TIMING_TIMECONTROL_ADD,
    SYS_STATUS_WIFI,
    SYS_STATUS_FILTER,
	SYS_STATUS_TIME,
	SYS_STATUS_FACTORY,
	SYS_STATUS_FAULT,
	SYS_STATUS_AUTO,
	SYS_STATUS_ABOUT,
	SYS_STATUS_OTHER,
	
	SYS_STATUS_NUMBER,
}systemRunStatus_t;

//++++++++++++++++++++++++++++++start+++++++++++++++++++++++++++++++++++++++++++
//*********************传感器、控温模式、风量模式、锁金和485******************************
typedef enum
{
    SENSOR_IN = ((uint8_t)0x00),
    SENSOR_OUT,
    SENSOR_ALL,      
}senCfg_t;

typedef enum
{
    SENSOR_3380_10K = ((uint8_t)0x00),
    SENSOR_3950_5K,
    //SENSOR_3950_10K,      
}senType_t;


typedef enum
{
    //WIND_SPEED_COLSE = ((uint8_t)0x00),
    WIND_SPEED_LOW = ((uint8_t)0x00),   
    WIND_SPEED_MID = ((uint8_t)0x01),
    WIND_SPEED_HIGH = ((uint8_t)0x02),
    WIND_SPEED_AUTO = ((uint8_t)0x03),
}windspeed_t;

typedef enum
{
	//UNDISPLAY,
    COOL,
    REMOVEWET,//除湿
    HOT,   
}airmode_t;

typedef enum
{
	UNDEFINE,
	ENERGY_CONSERVATION,
	COUNTTYSTANDARD,
	COMDORTABLE,
}experience_t;

typedef enum
{
    NONE_LOCK = 0x00,
    KEY_LOCK,
    KEY_STATUS_BLINK,
    //REMOTE_LOCK,
}lockStatus_t;


typedef enum
{
    RELAY_SAME_DIRECTION=((uint8_t)0x00),//主辅同向
    ASSIST_RELAY_REVERSE,               //主辅反向
    RELAY_ALL_REVERSE,                 //主辅同时反向
    MAIN_RELAY_REVERSE,
}outputType_t;
//*********************传感器、控温模式、锁金和485******************************
//------------------------------E N D-------------------------------------------


typedef enum
{
    OW_STATUS_INIT    = ((uint8_t)0x00),
    OW_STATUS_DELAY,
    OW_STATUS_CHECK,
    OW_STATUS_RUN,
}owStatus_t;
	
typedef struct
{
	uint16_t mon;
	uint16_t tues;
	uint16_t wed;
	uint16_t thur;
	uint16_t fri;
	uint16_t sat;
	uint16_t sun;
}week_t;

typedef struct
{
	uint8_t password[5];
	uint8_t keydowncount;
}factory_t;

typedef struct
{
	uint16_t year;
	uint16_t month;
	uint16_t day;
	uint16_t hour;
	uint16_t minute;		
}timeset_t;

typedef struct
{
	uint16_t up;
	uint16_t now;
	uint16_t down;
}dis_timeset_t;

typedef struct
{
	uint8_t windspeed:4;
	uint8_t mode:4;
	uint8_t poweron_hour;
	uint8_t poweron_minute;
	uint8_t poweroff_hour;
	uint8_t poweroff_minute;
}timecontrol_t;

typedef struct
{
	uint8_t motor_type;
	uint8_t tune_param_type;
	uint8_t high_param;
	uint8_t mid_param;
	uint8_t low_param;
	uint8_t removewet;
	uint8_t adress_485;
	uint16_t baudrate;
	uint8_t windvalueswitch;
	int16_t outdoortemp;
}fanset_t;

//++++++++++++++++++++++++++++++start+++++++++++++++++++++++++++++++++++++++++++
//****************************系统参数******************************************

typedef struct
{    
	systemRunStatus_t sys_runstatus;
	uint16_t debugcount;
	uint16_t count;
	uint8_t poweronflag;
	uint8_t communicationflag;
	uint8_t keydownflag;
	uint8_t updataflag;
	uint8_t child;
	uint8_t filter_change_message;
    int16_t mode;//模式
    int16_t airmode;
	int16_t automode;
	int16_t humidity_set;//设定湿度
	int16_t windspeed;//风速
	int16_t windspeedstate;
	int16_t timer;
	int16_t measure_temp;//测量温度
	int16_t measure_humidity;
	int16_t measure_co2;
	int16_t measure_pm25;
	uint16_t setting;
	uint16_t poweroff;
	uint16_t windStatsu;//状态
	int16_t temp_set;//设定温度
	uint16_t freq;//频率
	uint16_t outputstate;//状态
	uint16_t errorstate;//状态
	
	uint16_t fre_speed;//新风转速
	uint16_t rec_speed;//回风转速
	
	uint16_t read_2401_adress_data;
	uint16_t read_2402_adress_data;
	uint16_t read_2403_adress_data;
	uint16_t read_2404_adress_data;
	uint16_t read_2405_adress_data;
	uint16_t read_2406_adress_data;
	uint16_t read_2407_adress_data;
	uint16_t read_2408_adress_data;
	uint16_t read_2409_adress_data;
	uint16_t read_240A_adress_data;
	uint16_t read_240B_adress_data;
	uint16_t read_240C_adress_data;
	uint16_t read_240D_adress_data;
	uint16_t read_240E_adress_data;
	uint16_t read_240F_adress_data;
	uint16_t read_2410_adress_data;
	uint16_t read_2411_adress_data;
	uint16_t read_2412_adress_data;
	uint16_t read_2413_adress_data;
	uint16_t read_2414_adress_data;
	uint16_t read_2415_adress_data;
	uint16_t read_2416_adress_data;
	uint16_t read_2417_adress_data;
	uint16_t read_2418_adress_data;
	uint16_t read_2419_adress_data;
	uint16_t read_241A_adress_data;
	uint16_t read_241B_adress_data;

	
	uint16_t read_2448_LOW_PWM;
	uint16_t read_2449_MID_PWM;
	uint16_t read_244A_HIGH_PWM;
	uint16_t read_244B_LOW_PWM;
	uint16_t read_244C_MID_PWM;
	uint16_t read_244D_HIGH_PWM;

	
	uint16_t humidity_dis_key;
	uint8_t mode_dis_key;

	uint8_t page_number;
	uint16_t updata485control;

	uint8_t debugflag;

	//环控机
	uint8_t next_screen_flag:1;

	
	uint16_t page32_keynumberup;
	uint16_t page34_keynumberup;
	uint16_t page34_keynumberlong;
	uint16_t page35_keynumberup;
	uint16_t page36_keynumber;
	uint16_t page36_keynumberup;
	uint16_t page42_43_46_47_48keynumberup;
	uint16_t page44_keynumberup;
	uint16_t page44_keynumberlong;
	uint16_t page45_keynumberup;
	uint16_t page61_keynumberup;

	uint16_t key_fanset_param;
	
	uint8_t week_cursor;
	uint8_t week_function_type;
	uint8_t timecontrol_cursor;
	uint8_t timecontrol_function_type;//时段功能区别标志，用于区别是add还是edit
	uint8_t week_type_line[7];//一次最多设置7天7个时段
	uint8_t week_type_column;//一周最多设置7天7个时段
	uint8_t key_week_message;
	uint16_t dynamic_circular;
	uint16_t debugdata;
	uint8_t debugdata1;
	
	week_t dis_week;
	timeset_t set_time;
	factory_t factory;
	fanset_t fanset_param;
	timecontrol_t timecontrolmes[49];
    //RecordPara_t  record;                 
}SysPara_t;
//*****************************系统参数******************************************
//------------------------------E N D-------------------------------------------




//++++++++++++++++++++++++++++++start+++++++++++++++++++++++++++++++++++++++++++
//function
//名称  : controler_getSysParaPt
//功能  : 传出系统参数指针
//input : 无             
//output: SysPara_t类型指针首地址----------------------------->>传出
SysPara_t * controler_getSysParaPt(void);
//------------------------------E N D-------------------------------------------


//++++++++++++++++++++++++++++++start+++++++++++++++++++++++++++++++++++++++++++
//function
//名称  : controler_getSysParaPt
//功能  : 传出存储参数指针
//input : 无             
//output: RecordPara_t类型指针首地址----------------------------->>传出
//RecordPara_t * controler_getSysParaRecordPt(void);
//------------------------------E N D-------------------------------------------


//++++++++++++++++++++++++++++++start+++++++++++++++++++++++++++++++++++++++++++
//task
//名称  : app_control_scanTask
//功能  : 控制台运行扫描任务，所有参数的计算和刷新
//input : 无             
//output: return
uint8_t app_control_scanTask(void);
//------------------------------E N D-------------------------------------------


//++++++++++++++++++++++++++++++start+++++++++++++++++++++++++++++++++++++++++++
typedef enum
{
    DELAY_CONTROLER_COMMON = ((uint8_t)0x00),  
    DELAY_DIS_KEEP,
    DELAY_BILINK_5SECOND,
    DELAY_FAC,
    DELAY_HIGHSET,
    DELAY_HIGHSEITIME,
    DELAY_KEYLOCK,
    DELAY_TIMER_CLOSE_FUNCTION,
    DELAY_TIMER_OPEN_FUNCTION,
    DELAY_TIMER_MAX
}delayTime_t;
//function
//名称  : app_control_timeOut_get
//功能  : 判断是否超时
//input :              _in_type<<----------------------------->>传入
//output:true超时       bool类型 ----------------------------->>传出
//bool app_control_timeOut_get(delayTime_t type);

//function
//名称  : app_control_read_delaytime
//功能  : 读取delaytime时间
//input :              delayTime_t<<------------------------>>传入
//output:true超时       bool类型 ----------------------------->>传出
uint16_t app_control_read_delaytime(delayTime_t type);

//------------------------------E N D-------------------------------------------




//++++++++++++++++++++++++++++++start+++++++++++++++++++++++++++++++++++++++++++
//function
//名称  : app_control_timeOut_set
//功能  : 判断是否超时
//input :              _in_type<<----------------------------->>传入
//                  _in_delayMs<<----------------------------->>传入
//output:无
//void app_control_timeOut_set(delayTime_t _in_type,uint16_t _in_delayMs);
void app_control_timeOut_set(delayTime_t type,uint16_t milliscond);
//------------------------------E N D-------------------------------------------




//++++++++++++++++++++++++++++++start+++++++++++++++++++++++++++++++++++++++++++
//init
//名称  : APP_control_init
//功能  : 控制台初始化
//input : 无
//output: 无
void app_control_init(void);
//------------------------------E N D-------------------------------------------




//++++++++++++++++++++++++++++++start+++++++++++++++++++++++++++++++++++++++++++
//function
//名称  : app_con_gotoFac
//功能  : 系统参数恢复出厂设置
//input : 无
//output: 无
void app_con_gotoFac(void);
//------------------------------E N D-------------------------------------------




#endif
