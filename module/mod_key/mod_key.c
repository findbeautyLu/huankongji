
/*********************************************************************************************************
*
*	模块名称 : Mod按键模块
*	文件名称 : Mod_Keyboard.c
*	版    本 : V1.0
*	说    明 : 1、模块调用BSP_Keyboar和Mod_SystemTick组件
*                  2、供其他组件调用
*                  3、模块有配置按键、按键处理、按键扫描函数、
*                     重新操作一次按键、屏蔽一次按键功能和获取按键事件。
*	修改记录 :
*		版本号  日期        作者     说明
*		V1.0    2018-07-28  zhoujh  正式发布
*	Copyright (C), 2015-2020,   menredGroup
*
*********************************************************************************************************/

//++++++++++++++++++++++++++++++start+++++++++++++++++++++++++++++++++++++++++++
#include ".\depend\bsp_key.h"
#include ".\depend\SnailDataTypedef.h"

#include ".\mod_key.h"
//------------------------------E N D-------------------------------------------



//++++++++++++++++++++++++++++++start+++++++++++++++++++++++++++++++++++++++++++
//**************************按键事件类型****************************************
enum
{
    NoneKeyOccur      = 0x00,  //无键盘发生
    KeyChangeOccur    = 0x01,  //状态改变键盘
    KeyContinueOccur   =0x02,  //持续按键键盘
}KeyEvent;
//------------------------------E N D-------------------------------------------


//++++++++++++++++++++++++++++++start+++++++++++++++++++++++++++++++++++++++++++
//********************静态变量定义，仅作用与本模块******************************
static INT16U                 LastKeyWord;
static INT16U                 KeyWordOfChange;                //当前改变值
static INT16U                 KeyWordOfState;                 //当前状态值
static INT16U                 MaskOnceKeyWord;                //屏蔽一次按键
static INT16U                 KeyInContinue;                  //连续检测该键


static INT16U                 fristLongHitTime;
static INT16U                 continueHitTime;
//------------------------------E N D-------------------------------------------


static INT16U keyGroupAndAloneMap[4];

INT16U keynumber;

key_sign_t keynumber_1;
key_sign_t keynumber_1_up;
key_sign_t keynumber_2;
key_sign_t keynumber_2_up;
key_sign_t keynumber_3;
key_sign_t keynumber_3_up;
key_sign_t keynumber_4;
key_sign_t keynumber_4_up;
key_sign_t keynumber_5;
key_sign_t keynumber_5_up;
key_sign_t keynumber_6;
key_sign_t keynumber_6_up;
key_sign_t keynumber_7;
key_sign_t keynumber_7_up;
key_sign_t keynumber_8;
key_sign_t keynumber_8_up;

key_sign_t keynumber_44_long_and_continue;
key_time_t keynumber_44_timeparam;

void mod_key_configure(void)
{
    /*if(sizeof(keyGroupAndAloneMap) >= 4)
    {
        bsp_key_cofigure(&keyGroupAndAloneMap[0]);   
    }   */
}


BOOLEAN mod_key_getEvent(void)
{
    if(NoneKeyOccur != KeyEvent)
    {
        KeyEvent = NoneKeyOccur;
        return BN_TRUE;
    }
    return BN_FALSE;
} 


void mod_key_maskOnceOperation(INT16U _In_KeyInBit)
{
    MaskOnceKeyWord |= _In_KeyInBit;
}

void mod_key_reCaptureOperation(INT16U _In_KeyInBit)
{
    LastKeyWord   &= ~_In_KeyInBit;
    KeyInContinue &= ~_In_KeyInBit; 
}

INT16U ReadKeyAloneBits(void)
{
    INT16U  ReadPinBits;
    INT16U  ReadKeyWordBits; 
	INT8U i = 0;	
    ReadPinBits = 0;
    ReadKeyWordBits = 0;
    
    /*for(;i < 8;i++)
    {
        if(bsp_getkey(i))
        {
            ReadPinBits |= (1<<i);
        }
    }*/
   	ReadKeyWordBits = keyscan();
	

    return(ReadKeyWordBits);
}

void mode_key_runtime(unsigned int *timeparam,unsigned int difftick)
{
	unsigned int time = *timeparam;
	if(0 != time)
	{
		if(time >= difftick)
		{
			time -= difftick;
		}
		else
		{
			time = 0;
		}
	}
	
	*timeparam = time;
}
void mod_key_runTimeHandle(INT16U milliscond)
{
    static INT16U lastTick = 0;
           INT16U diffTick = 0;
    diffTick = milliscond - lastTick;
    lastTick = milliscond;
    if(0 != fristLongHitTime)
    {
        if(fristLongHitTime >= diffTick)
        {
            fristLongHitTime -= diffTick; 
        }
        else
        {
            fristLongHitTime = 0;
        }
    }
    
    if(0 != continueHitTime)
    {
        if(continueHitTime >= diffTick)
        {
            continueHitTime -= diffTick; 
        }
        else
        {
            continueHitTime = 0;
        }
    }    

	mode_key_runtime(&keynumber_44_timeparam.fristlonghit_time,diffTick);
	mode_key_runtime(&keynumber_44_timeparam.continue_time,diffTick);
}





unsigned int filter_keysign(unsigned int need_filter_sign,key_sign_t *key)
{
	key->key_sign.trigger_sign = need_filter_sign;
	if(key->key_sign.trigger_sign == 0)
	{
		key->key_sign.trigger_sign_lock = 0;
		key->key_sign.trigger_sign_timecount = 0;
	}
	else if(key->key_sign.trigger_sign_lock == 0)
	{
		key->key_sign.trigger_sign_timecount++;
		if(key->key_sign.trigger_sign_timecount > 5)
		{
			key->key_sign.trigger_sign_lock = 1;
			key->key_sign.trigger_sign_timecount = 0;
			return key->key_sign.trigger_sign;
		}
	}
	return 0;
}

unsigned int filter_keysign_up(key_sign_t *key,key_sign_t *keyup)
{
	static unsigned int keyupmes = 0;
	if(key->key_sign.trigger_sign != 0)
	{
		keyup->key_sign.trigger_sign = key->key_sign.trigger_sign;
	}
	else 
	{
		if(keyup->key_sign.trigger_sign != 0)
		{
			keyupmes = keyup->key_sign.trigger_sign;
			keyup->key_sign.trigger_sign = 0;
			keyup->key_sign.trigger_sign_lock = 0;
			keyup->key_sign.trigger_sign_timecount = 0;
		}
		else if(keyup->key_sign.trigger_sign_lock == 0)
		{
			keyup->key_sign.trigger_sign_timecount++;
			if(keyup->key_sign.trigger_sign_timecount > 5)
			{
				keyup->key_sign.trigger_sign_lock = 1;
				keyup->key_sign.trigger_sign_timecount = 0;	
				return keyupmes;
			}	
		}
	}
	return 0;
}


unsigned int filter_keysign_long(key_sign_t *key,key_sign_t *keylong,key_time_t *keytime)
{
	if(key->key_sign.trigger_sign == 0)
	{
		keylong->key_sign.trigger_sign_lock = 0;
		keytime->fristlonghit_time = 3000;
	}
	else
	{
		keylong->key_sign.trigger_sign = key->key_sign.trigger_sign;
		if(keylong->key_sign.trigger_sign_lock == 0)
		{
			if(keytime->fristlonghit_time == 0)
			{
				keylong->key_sign.trigger_sign_lock = 1;
				keytime->continue_time = 200;
				return keylong->key_sign.trigger_sign;
			}
		}
		else 
		{
			if(keytime->continue_time == 0)
			{
				keytime->continue_time = 200;
				return keylong->key_sign.trigger_sign;
				//按下 长按 连击 抬起，
			}
		}
	}
	return 0;
}


INT8U mod_key_scantask1(INT16U *_out_fanset_param_up)
{
	INT8U return_back = 0;
	INT16U fanset_param = 0;

	keyscan_fanset(&fanset_param);

	filter_keysign(fanset_param,&keynumber_1);
	*_out_fanset_param_up = filter_keysign_up(&keynumber_1,&keynumber_1_up);
	
	if(*_out_fanset_param_up != 0)
	{
		return_back = 1;
	}
	return return_back;
}

void mod_key_scanTask(INT16U milliscond)
{
    static INT8U initFlag = BN_TRUE;
    static INT8U ChangeCnt;   //电平改变计数
    static INT8U StateCnt;    //电平状态值计数
    INT16U ReadKeyWord;
    if(initFlag)
    {
        //mod_key_configure();
        initFlag = BN_FALSE;
		//ReadKeyAloneBits();
    }
    else
    {       
        mod_key_runTimeHandle(milliscond);

        ReadKeyWord = ReadKeyAloneBits();
		keynumber = ReadKeyWord;
        if(ReadKeyWord^LastKeyWord)
        {
            StateCnt = 0;
            ChangeCnt++;
            if(ChangeCnt > 5)
            {
                ChangeCnt = 0;
                KeyWordOfChange = ReadKeyWord^LastKeyWord;
                LastKeyWord = ReadKeyWord;
                KeyWordOfState = ReadKeyWord;
                KeyEvent = KeyChangeOccur;
                return;
            }
        } 
        else
        {
            ChangeCnt=0;
            if(ReadKeyWord != 0)
            {
                StateCnt++;
                if(StateCnt > 5)
                {
                    StateCnt = 0;
                    KeyWordOfState = ReadKeyWord;
                    KeyEvent = KeyContinueOccur;
                    return;
                }
            }
            else
            {
                ChangeCnt = 0;
                StateCnt = 0;
                KeyWordOfState = 0;
                MaskOnceKeyWord = 0;
                KeyInContinue = 0;
            }
        }
        KeyEvent=NoneKeyOccur;
    }   
}

keyActionType_t mod_keyOperation(INT16U keyNum,INT16U fristValid_ms,INT16U continueBlink_ms)
{
    if(MaskOnceKeyWord & keyNum)
    {
        return(PUSH_NONE);
    }   
    if(KeyInContinue & keyNum)  //处理该键的连续按键
    {
        if(KeyWordOfChange & keyNum)
        {
            KeyWordOfChange = 0;
            if(KeyWordOfState & keyNum)
            {
            }
            else
            {
                return(PUSH_UP);
            }
        }
        if(KeyWordOfState & keyNum)
        {           
            if((0 == fristLongHitTime) && (0 == continueHitTime))
            {
                continueHitTime = continueBlink_ms;
                return(PUSH_CONTINUE);
            }
        } 
    }
    else  
    {
        if(KeyWordOfChange & keyNum)
        {
            KeyWordOfChange=0;
            if(MaskOnceKeyWord & keyNum)
            {
                MaskOnceKeyWord &= ~keyNum;
                return(PUSH_NONE);
            }    
            else if(KeyWordOfState & keyNum)
            {
                if(fristValid_ms == NOCONTINUE)
                {
                    if(KeyWordOfState == keyNum)
                    {                       
                        fristLongHitTime = 0;
                        continueHitTime = 0;
                    }    
                    return(PUSH_DOWN); 
                }
                else
                {
                    KeyInContinue |= keyNum;
                    fristLongHitTime = fristValid_ms;
                    continueHitTime = 0;                   
                    return(PUSH_DOWN);  
                }                  
            }
            else
            {
                return(PUSH_UP);
            }
        }        
    }
    return(PUSH_NONE);
}


//更新接口


void mde_cfg(key_sign_1_t *out_key)
{
	//按键数据初始化，相关数据清零，长按或短按的时间设置
	out_key->key_down_lock = 0;
	out_key->key_down_longlock = 0;
	out_key->key_up_lock = 0;
	out_key->key_event_timecount = 0;
	out_key->key_down_sign = 0;
	out_key->in_longtime = 5000;
	out_key->in_continuetime = 500;
	//out_key->getkey2_bsp = keyscan_1;get_key2_bsp_array[i].bsp_scan;
}

unsigned char mde_filter_keysign(key_sign_1_t *out_key,unsigned int in_process_data,unsigned int group_number)
{
	unsigned char i = 0;
	unsigned char key_state = 0;
	static unsigned int down_key_number = 0;
	
	if(in_process_data == 0)
	{
		key_state = 0;
	}
	else
	{
		for(i = 0; i < 16; i++)//这边需要验证，多页还没验证
		{
			if(in_process_data & (0x0001 << i))
			{
				i = group_number * 16 + i;
				//小于16个键值已验证通过，按下 按下触发，长按，连击，抬起触发，抬起等状态显示
				//若大于50个数据，已处理，待验证
				break;
			}
		}	
		key_state = i * 5 + KEY_STATE;//触发 按键按下状态，将状态return出去
	}
	
	if(in_process_data == 0)//没有按键触发
	{
		if(out_key->key_up_lock == 0)
		{
			out_key->key_down_lock = 0;
			out_key->key_down_longlock = 0;
			out_key->key_event_timecount =0;	
			out_key->key_down_sign = 0;
			down_key_number = 0;
		}
		else
		{
			if(++out_key->key_event_timecount > 5)
			{
				out_key->key_up_lock = 0;
				out_key->key_down_sign = (down_key_number + KEY_UP);//触发 抬起，仅按下时第一次抬起有效
				down_key_number = 0;
			}
		}
	}
	else 
	{
		out_key->key_up_lock = 1;
		if(out_key->key_down_lock == 0)
		{
			if(++out_key->key_event_timecount > 5)
			{
				out_key->key_down_lock = 1;
				out_key->key_event_timecount = 0;
				out_key->key_down_sign = (i * 5 + KEY_DOWN);//触发 按下，一次按下仅触发一次
				down_key_number = i * 5;
			}
		}
		else if(out_key->key_down_longlock == 0)
		{
			if(++out_key->key_event_timecount > out_key->in_longtime)
			{
				out_key->key_down_longlock = 1;
				out_key->key_event_timecount = 0;
				out_key->key_down_sign = (i * 5 + LONG_KEY);//触发 长按
			}		
		}
		else if(out_key->key_down_longlock == 1)//连击触发一定是按下状态且长按触发之后
		{
			if(++out_key->key_event_timecount > out_key->in_continuetime)
			{
				out_key->key_event_timecount = 0;
				out_key->key_down_sign = (i * 5 + CONTINUE);//触发 连击
			}
			else
			{
				out_key->key_down_sign = 0;
			}
		}
	}		
	//ON_KEY_EVENT = 0,
	//KEY_STATE,//1 
	
	//key_state = i * 4 + KEY_STATE; 1 5 9 ~ ~ ~ 可追寻具体哪个按键处于按下状态
	
	return key_state;//返回按下或者松手的状态
}

unsigned int mde_getkey_event(key_sign_1_t *out_key)
{
	static unsigned char init_byte = 0;
	static unsigned char keybumberup_value = 0;
	unsigned int keystate = 0;
	
	unsigned int i = 0;
	unsigned int j = 0;
	unsigned int adress = 0;
	unsigned int keynumber[MAX_KEY_GROUP] = {0,0};//从bsp得到数据按键缓存
	
	
	if(init_byte)
	{
		for(j = 0; j < MAX_KEY_GROUP; j++)
		{
			out_key[j].getkey2_bsp(&keynumber[j]);
			if(keystate = mde_filter_keysign(&out_key[j],keynumber[j],j))
			{
				keybumberup_value = keystate;
				break;
			}
			else if(keybumberup_value != 0)
			{
				keystate = keybumberup_value;//out_key[j].key_down_sign;//松手后获取一次按键键值
				keybumberup_value = 0;
				break;
			}
			else
			{
				;
			}
		}
	}
	else
	{
		for(i = 0; i < MAX_KEY_GROUP; i++)
		{
			mde_cfg(&out_key[i]);
			out_key[0].getkey2_bsp = keyscan_1;//理论上函数地址放数组里面是可以的，但是cfg放进去之后i数值乱了，暂时做个问题点
			out_key[1].getkey2_bsp = keyscan_2;
		}
		init_byte = 1;
	}
	//0 没有按键触发			
	//非0 有触发 具体数据由按键值+1定义 
	
	return keystate;
}

