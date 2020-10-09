//++++++++++++++++++++++++++++++start+++++++++++++++++++++++++++++++++++++++++++
#ifndef _APP_ONE_WIRE_H
#define _APP_ONE_WIRE_H
//------------------------------E N D-------------------------------------------
//++++++++++++++++++++++++++++++start+++++++++++++++++++++++++++++++++++++++++++
//***********************单线模块使用的变量**************************************
//------------------------------E N D-------------------------------------------

//标准
#define MREGADDR_EQUIPMENT_TYPE		  0x2000	//R
#define MREGADDR_SOFTVISION			  0x2001	//R
#define MREGADDR_CLOCK_SECOND_WEEK	  0x2002	//R/W
#define MREGADDR_CLOCK_HOUR_MINUTE	  0x2003	//R/W
#define MREGADDR_CLOCK_MONTH_DAY	  0x2004	//R/W
#define MREGADDR_YEARS				  0x2005	//R/W
#define MREGADDR_SALVE_ADDRESS		  0x2006	//R/W
#define MREGADDR_SALVE_BAUDRATE		  0x2007	//R/W
#define MREGADDR_SALVE_PARITYBIT	  0x2008	//R/W
#define MREGADDR_RESTOR				  0x2009	//R/W


//拓展
#define MREGADDRESS_SYS_POWER						0x2400	//只写
#define MREGADDRESS_SYS_POWER_ON_CMD		0x0001//
#define MREGADDRESS_SYS_POWER_OFF_CMD		0x0002

#define MREGADDRESS_EQUIPMENT_STATE					0x2401	//只读

#define MREGADDRESS_SYS_MODE						0x2402
#define MREGADDRESS_SYS_MODE_NEWWIND_CMD	0x0000			//新风
#define MREGADDRESS_SYS_MODE_PURIFY_CMD		0x0001			//净化
#define MREGADDRESS_SYS_MODE_MIXEDWIND_CMD	0x0002			//保留(混风)
#define MREGADDRESS_SYS_MODE_REMOVEWET_CMD	0x0003			//除湿
#define MREGADDRESS_SYS_MODE_AUTO_CMD		0x0004			//自动

#define MREGADDRESS_SYS_INDOOR_TEMP					0x2403	//测试温度				R	
#define MREGADDRESS_SYS_INDOOR_HUMIDTY				0x2404	//测试湿度				R
#define MREGADDRESS_SYS_WIND_SPEED_CONTROL			0x2405	//风速设定值					R/W
#define MREGADDRESS_SYS_SET_LOWWIND			0x0001
#define MREGADDRESS_SYS_SET_MIDWIND			0x0002
#define MREGADDRESS_SYS_SET_HIGHWIND		0x0003
#define MREGADDRESS_SYS_WIND_SPEED_STATE			0x2406	//风速状态值					R

#define MREGADDRESS_SYS_LOW_FILTER_REPLACE_CYCLE	0x2407	//粗效过滤网更换周期				R/W
#define MREGADDRESS_SYS_HIGH_FILTER_REPLACE_CYCLE	0x2408	//高效过滤网更换周期				R/W
#define MREGADDRESS_SYS_LOW_FILTER_USE_TIEM			0x2409	//粗效过滤网使用时间				R/W
#define MREGADDRESS_SYS_HIGH_FILTER_USE_TIEM		0x240A	//高效过滤网使用时间				R/W
#define MREGADDRESS_SYS_HUMIDITY_CONTROL_SET		0x240B	//湿度控制设定值				R/W
#define MREGADDRESS_SYS_TEMP_CONTROL_NULL			0x240C	//湿度控制死区				R
#define MREGADDRESS_SYS_EQUIPMENT_PROTECT_BYTE		0x240D	//设备保护字					R
#define MREGADDRESS_SYS_EQUIPMENT_FAULT_BYTE		0x240E	//设备故障字					R
#define MREGADDRESS_SYS_CO2_VALUE					0x240F	//测量CO2值				R
#define MREGADDRESS_SYS_PM_2_5_VALUE				0x2410	//测量PM2.5值				R
#define MREGADDRESS_SYS_AIR_INTAKE					0x2411	//进风温度					R
#define MREGADDRESS_SYS_EVAP_TEMP					0x2412	//蒸发器温度					R
#define MREGADDRESS_SYS_HIGH_TEMP_COIL				0x2413	//高温盘管温度				R	
#define MREGADDRESS_SYS_AUTO_MODE_RUNSTATE			0x2414	//自动模式运行状态值				R
#define MREGADDRESS_SYS_EQUIPMENT_STATE_BYTE		0x2415	//设备状态字					R
#define MREGADDRESS_SYS_FAULT_RESET_BYTE			0x2416	//故障复位字					W


#define MREGADDRESS_SYS_WATER_STATE					0x2417	//水位状态					R		
#define MREGADDRESS_SYS_LIFT_WATER_STATE			0x2418	//提水泵状态					R		
#define MREGADDRESS_SYS_AC_OUTPUT_STATE				0x2419	//压缩机输出状态				R		

#define MREGADDRESS_SYS_HIGH_TEMP_COIL_PROTECT		0x241B	//进风设定温度				R/W
#define MREGADDRESS_RESERVE							0x241C	//高温盘管保护温度				R/W		

#define MRegaddr_NewairControlW              0x2200//新风设备操控字
#define MRegaddr_NewairStatusW               0x2201//新风设备状态字
#define MRegaddr_NewairErrorW                0x2202//新风设备错误字
#define MRegaddr_NewairFanSet                0x2203//风机设定值
#define MRegaddr_NewairFanStatus             0x2204//风机状态值
#define MRegaddr_Aircod_FRE                  0x2430//频率
#define MRegaddr_Aircod_RunFanSpeed          0x2431//外机运行风速
#define MRegaddr_Aircod_MeasureTemp          0x2432//测量温度																																										
#define MRegaddr_Aircod_ErrorStatus1         0x2433//错误字1
#define MRegaddr_Aircod_ErrorStatus2         0x2434//错误字2
#define MRegaddr_Aircod_ErrorStatus3         0x2435//错误字3
#define MRegaddr_Aircod_ErrorStatus4         0x2436//错误字4
#define MRegaddr_Aircod_ErrorStatus5         0x2437//错误字5
#define MRegaddr_Aircod_Mode                 0x2438//模式
#define MRegaddr_Aircod_airwindStatus        0x2439//通风状态
#define MRegaddr_Aircod_SetTemp              0x243A//设定温度
#define MRegaddr_Aircod_SetHumidity          0x243B//设定湿度
#define MRegaddr_Equipment_Output			 0x243D//
#define MRegaddr_Equipment_Error			 0x243E//

#define MRegaddr_Frespeed					 0x2440
#define MRegaddr_Recspeed					 0x2442

#define MREGADDRESS_SYS_INWIND_PWM_LOW_SPEED    0x2448		
#define MREGADDRESS_SYS_INWIND_PWM_MID_SPEED    0x2449		
#define MREGADDRESS_SYS_INWIND_PWM_HIGH_SPEED   0x244A		

#define MREGADDRESS_SYS_OUTWIND_PWM_LOW_SPEED    0x244B			
#define MREGADDRESS_SYS_OUTWIND_PWM_MID_SPEED    0x244C			
#define MREGADDRESS_SYS_OUTWIND_PWM_HIGH_SPEED   0x244D			

#define MREGADDRESS_SYS_MODE_COLD	    0x0001			//新风
#define MREGADDRESS_SYS_MODE_HEAT		  0x0002			//净化
#define MREGADDRESS_SYS_MODE_HUMIDTY  0x0003			//保留(混风)
#define MREGADDRESS_SYS_MODE_WIND  	  0x0004			//除湿

//++++++++++++++++++++++++++++++start+++++++++++++++++++++++++++++++++++++++++++
//Task
//名称: 单线扫描模块，主函数调用
//功能: 
//入口: 无
//出口: 无
 void APP_oneWire_task(void);
 void APP_oneWire_send_485_data(u16 address,u16 value);
 void APP_oneWire_read_485_data(u16 address,u16 len);
//------------------------------E N D-------------------------------------------



#endif



//--------------------------APP.oneWire.h--END--------------------------------------
