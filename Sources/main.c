/******************************************************************************
* 文 件 名   : main.c
* 版 本 号   : V1.0
* 作    者   : pinot
* 生成日期   : 2020年04月13日
* 功能描述   : 主函数，外设和参数初始化，主循环中主要功能函数入口。
* 修改历史   :
* 日    期   :
* 作    者   :
* 修改内容   :
******************************************************************************/

/*****************************************************************************
系统库*/

/*****************************************************************************
自定义头文件*/
#include "T5LOS8051.H"
#include "sys.h"
#include "handle.h"
#include "timer.h"

#include "..\application\APP_Configure.h"
/*****************************************************************************
主函数*/
void main(void)
{
	
	uint8_t timebuf[2] ={0,0};
	uint16_t value_temp;
	InitCPU();
	app_con_gotoFac();
	system_parm_init();
	init_rtc();
	while(1)
	{
	    WDT_RST();
	    HandleProc();
		systickTimeRun_task();	
		if(app_control_scanTask())
		{
			app_key_scanTask();
			app_display_scanTask();
			//APP_oneWire_task();
			app_onrwire_task1();
		}
	}
}
