//++++++++++++++++++++++++++++++start+++++++++++++++++++++++++++++++++++++++++++
#ifndef _BSP_KEY_H
#define _BSP_KEY_H
//------------------------------E N D-------------------------------------------
#include ".\SnailDataTypedef.h"


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

#define REG_KEY_POWER			 		  0x57A0//开机
#define REG_KEY_POWEROFF				  0x5770//关机
#define REG_KEY_TEMP_ADD				  0x5700
#define REG_KEY_TEMP_SUB				  0x5710
#define REG_KEY_HUMIDITY_ADD			  0x5720//湿度+
#define REG_KEY_HUMIDITY_SUB			  0x5730//湿度-
#define REG_KEY_MODE    				  0x5740//模式
#define REG_KEY_SET_UP_STATE			  0x5750//状态
#define REG_KEY_WIND_SPEED			      0x5760//风速
#define REG_KEY_POWEROFF_SURE	 		  0x5780//关机确定
#define REG_KEY_POWEROFF_CANCEL		      0x5790//关机取消

//#define REG_KEY_TIMING					  0x5750
//#define REG_KEY_SETTING					  0x5760


#define REG_KEY_RESET			 		0x57B0
#define REG_KEY_OUT_SCREEN_SAVER	 	0x57C0
#define REG_KEY_INTO_SCREEN_SAVER 		0x57D0
 

//36页面 周一 ~ 周日按键定义
#define REG_KEY_WEEK_CHOOSE_MONDAY		0x5800
#define REG_KEY_WEEK_CHOOSE_TUESDAY		0x5802
#define REG_KEY_WEEK_CHOOSE_WEDNESDAY	0x5804
#define REG_KEY_WEEK_CHOOSE_THURSDAY	0x5806
#define REG_KEY_WEEK_CHOOSE_FRIDAY		0x5808
#define REG_KEY_WEEK_CHOOSE_SATURDAY	0x580A
#define REG_KEY_WEEK_CHOOSE_SUNDAY		0x580C
#define REG_KEY_WEEK_SURE				0x580E
#define REG_KEY_WEEK_CANCEL				0x5810

//32页 设置跳转 ~
#define REG_KEY_WIFI					0x5812
#define REG_KEY_TIME_CONTROL			0x5814
#define REG_KEY_FILTER					0x5816
#define REG_KEY_TIME					0x5818
#define REG_KEY_FACTORY					0x581A
#define REG_KEY_FAULT					0x581C
#define REG_KEY_ABOUT					0x581E
#define REG_KEY_OTHER					0x5820
#define REG_KEY_CANCEL_PAGE32			0x5822

//34页 定时设置 星期
#define REG_PAGE34_KEY_WEEK_UP				0x5824
#define REG_PAGE34_KEY_WEEK_DOWN			0x5826
#define REG_PAGE34_KEY_TIME_INTERVAL_UP		0x5828
#define REG_PAGE34_KEY_TIME_INTERVAL_DOWN	0x582A
#define REG_PAGE34_KEY_JUMP_35PAGE			0x582C
#define REG_PAGE34_KEY_WEEK_ADD				0x582E
#define REG_PAGE34_KEY_WEEK_EDIT			0x5830
#define REG_PAGE34_KEY_WEEK_DELETE			0x5832
#define REG_PAGE34_KEY_CANCEL				0x5834

//35页 定时设置 时段
#define REG_PAGE35_KEY_WEEK_UP				0x5836
#define REG_PAGE35_KEY_WEEK_DOWN			0x5838
#define REG_PAGE35_KEY_TIME_INTERVAL_UP		0x583A
#define REG_PAGE35_KEY_TIME_INTERVAL_DOWN	0x583C
#define REG_PAGE35_KEY_JUMP_34PAGE			0x583E
#define REG_PAGE35_KEY_TIME_INTERVAL_ADD	0x5840
#define REG_PAGE35_KEY_TIME_INTERVAL_EDIT	0x5842
#define REG_PAGE35_KEY_TIME_INTERVAL_DELETE	0x5844
#define REG_PAGE35_KEY_CANCEL				0x5846

//42页 返回 连接 
#define REG_PAGE42_KEY_CANCEL				0x5848
#define REG_PAGE42_KEY_CONNECT				0x584A

//43页 返回 上 下 长按滤芯复位
#define REG_PAGE43_KEY_FILTER				0x584C
#define REG_PAGE43_KEY_CYCLE_UP				0x584E
#define REG_PAGE43_KEY_CYCLE_DOWN			0x5850
#define REG_PAGE43_KEY_CANCEL				0x5852

//44页 返回 年上下 月上下 日上下 时上下 分上下
#define REG_PAGE44_KEY_YEARS_UP				0x5854
#define REG_PAGE44_KEY_YEARS_DOWN			0x5856
#define REG_PAGE44_KEY_MONTH_UP				0x5858
#define REG_PAGE44_KEY_MONTH_DOWN			0x585A
#define REG_PAGE44_KEY_DAY_UP				0x585C
#define REG_PAGE44_KEY_DAY_DOWN				0x585E
#define REG_PAGE44_KEY_HOURS_UP				0x5860
#define REG_PAGE44_KEY_HOURS_DOWN			0x5862
#define REG_PAGE44_KEY_MINUTE_UP			0x5864
#define REG_PAGE44_KEY_MINUTE_DOWN			0x5866
#define REG_PAGE44_KEY_SURE					0x5868
#define REG_PAGE44_KEY_CANCEL				0x586A

//45页 返回 数字键盘0~9 删除 确认
#define REG_PAGE45_KEY_0					0x586C
#define REG_PAGE45_KEY_1					0x586E
#define REG_PAGE45_KEY_2					0x5870
#define REG_PAGE45_KEY_3					0x5872
#define REG_PAGE45_KEY_4					0x5874
#define REG_PAGE45_KEY_5					0x5876
#define REG_PAGE45_KEY_6					0x5878
#define REG_PAGE45_KEY_7					0x587A
#define REG_PAGE45_KEY_8					0x587C
#define REG_PAGE45_KEY_9					0x587E
#define REG_PAGE45_KEY_DEL					0x5880
#define REG_PAGE45_KEY_SURE					0x5882
#define REG_PAGE45_KEY_CANCEL				0x5884
//46页 返回
#define REG_PAGE46_KEY_CANCEL				0x5886
//47页 返回 恢复出厂设置
#define REG_PAGE47_KEY_CANCEL				0x5888
#define REG_PAGE47_FACTORY					0x588A

//48页 返回 静音已关 常亮已关 室外信息 帮助
#define REG_PAGE48_KEY_QUIET				0x588C
#define REG_PAGE48_KEY_EVERBRIGHT			0x588E
#define REG_PAGE48_KEY_OUTDOOR_MESSAGE		0x5890
#define REG_PAGE48_KEY_HELP					0x5892
#define REG_PAGE48_KEY_CANCEL				0x5894

#define REG_PAGE62_FANSET_FANMOTOR_UP				0x58A9
#define REG_PAGE62_FANSET_FANMOTOR_DOWN				0x58AA
#define REG_PAGE62_FANSET_FANMOTOR_TYPE_UP			0x58AB	
#define REG_PAGE62_FANSET_FANMOTOR_TYPE_DOWN		0x58AC		
#define REG_PAGE62_FANSET_FANMOTOR_HIGHSPEED_UP		0x58AD			
#define REG_PAGE62_FANSET_FANMOTOR_HIGHSPEED_DOWN	0x58AE			
#define REG_PAGE62_FANSET_FANMOTOR_MIDSPEED_UP		0x58AF		
#define REG_PAGE62_FANSET_FANMOTOR_MIDSPEED_DOWN	0x58B0			
#define REG_PAGE62_FANSET_FANMOTOR_LOWSPEED_UP		0x58B1		
#define REG_PAGE62_FANSET_FANMOTOR_LOWSPEED_DOWN	0x58B2
#define REG_PAGE62_FANSET_REMOVEWET_UP				0x58B3
#define REG_PAGE62_FANSET_REMOVEWET_DOWN			0x58B4
#define REG_PAGE62_FANSET_485ADRESS_UP				0x58B5
#define REG_PAGE62_FANSET_485ADRESS_DOWN			0x58B6
#define REG_PAGE62_FANSET_BAUDRATE_UP				0x58B7
#define REG_PAGE62_FANSET_BAUDRATE_DOWN				0x58B8











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
#endif

//-----------------------BSP_Keyboard.h--END------------------------------------
