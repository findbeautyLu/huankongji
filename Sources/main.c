/******************************************************************************
* �� �� ��   : main.c
* �� �� ��   : V1.0
* ��    ��   : pinot
* ��������   : 2020��04��13��
* ��������   : ������������Ͳ�����ʼ������ѭ������Ҫ���ܺ�����ڡ�
* �޸���ʷ   :
* ��    ��   :
* ��    ��   :
* �޸�����   :
******************************************************************************/

/*****************************************************************************
ϵͳ��*/

/*****************************************************************************
�Զ���ͷ�ļ�*/
#include "T5LOS8051.H"
#include "sys.h"
#include "handle.h"
#include "timer.h"

#include "..\application\APP_Configure.h"
/*****************************************************************************
������*/
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
