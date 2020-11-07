
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

//------------------------------E N D-------------------------------------------


//++++++++++++++++++++++++++++++start+++++++++++++++++++++++++++++++++++++++++++


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
	out_key->in_continuetime = 400;
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
			//if(++out_key->key_event_timecount > 5)
			//{
				out_key->key_up_lock = 0;
				out_key->key_down_sign = (down_key_number + KEY_UP);//触发 抬起，仅按下时第一次抬起有效
				down_key_number = 0;
			//}
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
	static unsigned char keyup_page = 0;
	unsigned int keystate = 0;
	
	unsigned int i = 0;
	unsigned int j = 0;
	unsigned int adress = 0;
	unsigned int keynumber[MAX_KEY_GROUP] = {0,0};//从bsp得到数据按键缓存
	
	
	if(init_byte)
	{
		for(; j < MAX_KEY_GROUP; j++)
		{
			if(keyup_page != 0)
			{
				j = keyup_page;
			}
			out_key[j].getkey2_bsp(&keynumber[j]);
			if(keystate = mde_filter_keysign(&out_key[j],keynumber[j],j))
			{
				keyup_page = j;//松手检测需要锁定页码
				keybumberup_value = keystate;
				break;
			}
			else if(keybumberup_value > keystate)
			{
				keyup_page = 0;
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
			out_key[0].getkey2_bsp = keyscan_1;//理论上函数地址放数组里面是可以的，但是cfg放进去之后i数值乱了，不知道哪里语法错了
			out_key[1].getkey2_bsp = keyscan_2;
			out_key[2].getkey2_bsp = keyscan_3;
		}
		init_byte = 1;
	}
	//0 没有按键触发			
	//非0 有触发 具体数据由按键值+1定义 
	
	return keystate;
}

