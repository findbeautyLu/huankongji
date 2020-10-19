//++++++++++++++++++++++++++++++start+++++++++++++++++++++++++++++++++++++++++++
#ifndef _MOD_KEY_H
#define _MOD_KEY_H
//------------------------------E N D-------------------------------------------

/*#define  KeyNull          0x0000
#define  KeyAloneBit0     0x0001    
#define  KeyAloneBit1     0x0002  
#define  KeyAloneBit2     0x0004  
#define  KeyAloneBit3     0x0008  
#define  KeyAloneBit4     0x0010
#define  KeyAloneBit5     0x0020  
#define  KeyAloneBit6     0x0040  
#define  KeyAloneBit7     0x0080  


#define  KeyGroupBit0     0x0100   
#define  KeyGroupBit1     0x0200   
#define  KeyGroupBit2     0x0400   
#define  KeyGroupBit3     0x0800   
#define  NOCONTINUE       0xffff  */
//++++++++++++++++++++++++++++++start+++++++++++++++++++++++++++++++++++++++++++
//**************************按键状态类型****************************************

typedef enum
{
    PUSH_NONE       = 0x00,
    PUSH_DOWN       = 0x01,
    PUSH_UP         = 0x02,
    PUSH_CONTINUE   = 0X04,
}keyActionType_t;

typedef enum
{
	ON_KEY_EVENT = 0,
	KEY_STATE,//1当前状态
	KEY_DOWN,//2第一次按下
	LONG_KEY,//3
	CONTINUE,//4
	KEY_UP,//5
}key_event_t;

//------------------------------E N D-------------------------------------------
typedef union
{
	unsigned int key_sign_parameter[2];
	struct
	{
		unsigned int trigger_sign_lock:8;
		unsigned int trigger_sign_timecount:8;//计数
		unsigned int trigger_sign:16;
	}key_sign;
}key_sign_t;

typedef struct
{
	unsigned int key_down_lock:1;
	unsigned int key_down_longlock:1;
	unsigned int key_up_lock:1;
	unsigned int key_event_timecount:13;//计数范围 0~8192  理想是放在1ms的中断扫描，若直接在主循环中，则该计数数据应该提取出来放到1ms的循环中自加
	unsigned int key_down_sign:16;
	unsigned int in_longtime:16;
	unsigned int in_continuetime:16;
	unsigned int (*getkey2_bsp)(unsigned int *read_keynumber);

}key_sign_1_t;

typedef struct
{
	unsigned int fristhit_time;//首次触发时间
	unsigned int fristlonghit_time;//首次触发长按时间
	unsigned int continue_time;//长按后联机时间
}key_time_t;

extern INT16U keynumber;
extern key_sign_t keynumber_1;
extern INT16U debug_keynumber;
extern key_time_t keynumber_44_timeparam;

//++++++++++++++++++++++++++++++start+++++++++++++++++++++++++++++++++++++++++++
//Event
//名称: mod_key_getEvent
//功能: 按键事件获取，读取按键前调用判断
//入口: 无
//出口:有按键状态发生改变返回BN_TURE,其他情况返回BN_FALSE  
BOOLEAN mod_key_getEvent(void);
//------------------------------E N D-------------------------------------------


//++++++++++++++++++++++++++++++start+++++++++++++++++++++++++++++++++++++++++++
//Function
//名称: mod_key_maskOnceOperation
//功能: 屏蔽一次按键,需要时调用。
//入口: 
//具体按键值              _In_KeyInBit      <<------------------------------传入
//
//出口: 无
void mod_key_maskOnceOperation(INT16U _In_KeyInBit);
//------------------------------E N D-------------------------------------------


//++++++++++++++++++++++++++++++start+++++++++++++++++++++++++++++++++++++++++++
//Function
//名称: mod_key_reCaptureOperation
//功能: 重读一次按键,需要时调用
//入口: 
//具体按键值              _In_KeyInBit      <<------------------------------传入
//
//出口: 无
void mod_key_reCaptureOperation(INT16U _In_KeyInBit); 
//------------------------------E N D-------------------------------------------


//++++++++++++++++++++++++++++++start+++++++++++++++++++++++++++++++++++++++++++
//Task
//名称: 按键扫描函数
//功能: 放入定时调用函数
//入口:                   milliscond        <<------------------------------传入
//出口: 无

INT8U mod_key_scantask1(INT16U *_out_fanset_param_up);



void mod_key_scanTask(INT16U milliscond);


//------------------------------E N D-------------------------------------------


//++++++++++++++++++++++++++++++start+++++++++++++++++++++++++++++++++++++++++++
//Function
//名称: 按键值操作
//功能: 处理扫描函数得到的按键值，软件滤波功能，并对其状态做出判断，其他组件可调用
//入口: 、和。
//      按键值           ： _IN_KeyInBit      <<-------------------------传入
//      首次长按有效时间 ： fristValid_ms    <<-------------------------传入
//      长按每次间隔时间 ： continueBlink_ms   <<-------------------------传入
//
//出口: KeyRetValue_Def类型的按键状态

keyActionType_t mod_keyOperation(INT16U keyNum,INT16U fristValid_ms,INT16U continueValid_ms);

unsigned char mde_getkey_event(key_sign_1_t *out_key);




//------------------------------E N D-------------------------------------------
#endif


//-----------------------Mod_Keyboard.h--END------------------------------------
