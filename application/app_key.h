//++++++++++++++++++++++++++++++start+++++++++++++++++++++++++++++++++++++++++++
#ifndef _APP_KEY_H
#define _APP_KEY_H
//------------------------------E N D-------------------------------------------

#define WATCH1_WINDOW			0x5100
#define WATCH2_WINDOW			0x5110
#define WATCH3_WINDOW			0x5120
#define WATCH4_WINDOW			0x5130
#define WATCH5_WINDOW			0x5140
#define WATCH6_WINDOW			0x5150

#define UPDTAT_485_SYSPOWER		0x0001
#define UPDTAT_485_MODE			0x0002
#define UPDTAT_485_HUMIDITY		0x0004
#define UPDTAT_485_WIND			0x0008



//++++++++++++++++++++++++++++++start+++++++++++++++++++++++++++++++++++++++++++
//Task
//名称: 按键扫描模块
//功能: 用于扫描按键，主函定时数调用。
//入口: 无
//出口: 无
void app_key_scanTask(void);
uint16_t get_485value(uint16_t adress);
void app_keyinit_jumppage(void);


//------------------------------E N D-------------------------------------------
#endif



//-----------------------APP_KeyBoard.h--END------------------------------------
