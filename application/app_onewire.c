/*******************************************************************************
*
*	模块名称 : APP单线扫描模块
*	文件名称 : APP.oneWire.c
*	版    本 : V1.0
*	说    明 : 1、发送接收单线数据
*              2、从站
                  
*	修改记录 :
*		版本号  日期        作者     说明
*		V1.0    2018-11-27  Linzl  正式发布
*	Copyright (C), 2015-2020,   menredGroup
*
*******************************************************************************/
#include ".\app_configure.h"
//++++++++++++++++++++++++++++++start+++++++++++++++++++++++++++++++++++++++++++
#define REG_DISPLAY_START   0x1000
#define REG_DISPLAY_NREGS   35

#define REG_UPDATA_START    0x1800
#define REG_UPDATA_NREGS    194

#define REG_HOLDING_START_PUBLIC1   0x2000
#define REG_HOLDING_NREGS_PUBLIC1   17

#define REG_HOLDING_START1   0x2200
#define REG_HOLDING_NREGS1   10

#define REG_HOLDING_START2   0x2430
#define REG_HOLDING_NREGS2   40

#define ONEWIRE_TX_BUFFER_SIZE             3
MP_mem_object_t onewire_txBuffer[ONEWIRE_TX_BUFFER_SIZE];
MP_mem_pool_t   onewire_txMemPool;

unsigned short      regAddress;
unsigned short      regCount;
u8 modbusSendLock = 0;
//*************************单线任务模块宏定义 **************************************
//++++++++++++++++++++++++++++++start+++++++++++++++++++++++++++++++++++++++++++
//****************************单线扫描******************************************
//++++++++++++++++++++++++++++++start+++++++++++++++++++++++++++++++++++++++++++
//****************************读写寄存器*****************************************


void processWriteHoldingRegData(unsigned short regAddress,unsigned short regData)
{
	SysPara_t *ptSysPara;  
	ptSysPara =  controler_getSysParaPt( );
    ptSysPara->communicationflag = 0;
    switch(regAddress)
    {        
    	case MREGADDRESS_SYS_POWER:
			//if(regData != get_485value(regAddress))
			//	sendflag = 1;
			break;
		case MRegaddr_NewairStatusW:
		{
			if(modbusSendLock == 0)
			{
				if((regData & 0x0001) == 0x0001)
				{//关机
					ptSysPara->page_number = 0x00;
				}
				else
				{					
					if(ptSysPara->page_number == 0)
					{
						ptSysPara->page_number = 1;
					}
					
				}
			}			
			break;
		}
		case MRegaddr_NewairFanSet:
		{
			if(modbusSendLock == 0)
			{
				ptSysPara->windspeed = regData;
			}			
			break;
		}
		case MRegaddr_Aircod_FRE:
			if(modbusSendLock == 0)
			{
				ptSysPara->freq = regData;
			}			
			break;
		case MRegaddr_Aircod_MeasureTemp:
			if(modbusSendLock == 0)
			{
				ptSysPara->measure_temp = regData;//测量温度
				
			}
			break;
		case MRegaddr_Aircod_ErrorStatus1:
			if(modbusSendLock == 0)
			{
				//ptSysPara->measure_temp = regData;//错误字1
			}
			break;
		case MRegaddr_Aircod_ErrorStatus2:
			if(modbusSendLock == 0)
			{
				//ptSysPara->measure_temp = regData;//错误字2
			}
			break;
		case MRegaddr_Aircod_ErrorStatus3:
			if(modbusSendLock == 0)
			{
				//ptSysPara->measure_temp = regData;//错误字3
			}
			break;
		case MRegaddr_Aircod_ErrorStatus4:
			if(modbusSendLock == 0)
			{
				//ptSysPara->measure_temp = regData;//错误字4
			}
			break;
		case MRegaddr_Aircod_ErrorStatus5:
			if(modbusSendLock == 0)
			{
				//ptSysPara->measure_temp = regData;//错误字5
			}
			break;
		case MRegaddr_Aircod_Mode:
			if(modbusSendLock == 0)
			{
				if(ptSysPara->poweronflag == 0)
				ptSysPara->mode = regData;
			}
			break;
		
		case MRegaddr_Aircod_airwindStatus:
		{
			if(modbusSendLock == 0)
			{
				ptSysPara->airmode = regData;				
			}
			break;
		}	
		case MRegaddr_Aircod_SetTemp:
		{
			if(modbusSendLock == 0)
			{
				ptSysPara->temp_set = regData;				
			}
			break;
		}	
		case MRegaddr_Aircod_SetHumidity:
		{
			if(modbusSendLock == 0)
			{
				ptSysPara->humidity_set = regData;				
			}
			break;
		}	
		case MRegaddr_Equipment_Output:
		{
			if(modbusSendLock == 0)
			{
				ptSysPara->outputstate = regData;				
			}
			break;
		}	
		case MRegaddr_Equipment_Error:
		{
			if(modbusSendLock == 0)
			{
				ptSysPara->errorstate = regData;				
			}
			break;
		}	
		case MRegaddr_Frespeed:
		{
			if(modbusSendLock == 0)
			{
				ptSysPara->fre_speed = regData;				
			}
			break;
		}	
		case MRegaddr_Recspeed:
		{
			if(modbusSendLock == 0)
			{
				ptSysPara->rec_speed = regData;				
			}
			break;
		}	
		case MREGADDRESS_SYS_INWIND_PWM_LOW_SPEED:
		{
			if(modbusSendLock == 0)
			{
				ptSysPara->read_2448_LOW_PWM = regData;				
			}
			break;
		}
		case MREGADDRESS_SYS_INWIND_PWM_MID_SPEED:
		{
			if(modbusSendLock == 0)
			{
				ptSysPara->read_2449_MID_PWM = regData;				
			}
			break;
		}
		case MREGADDRESS_SYS_INWIND_PWM_HIGH_SPEED:
		{
			if(modbusSendLock == 0)
			{
				ptSysPara->read_244A_HIGH_PWM = regData;				
			}
			break;
		}

		case MREGADDRESS_SYS_OUTWIND_PWM_LOW_SPEED:
		{
			if(modbusSendLock == 0)
			{
				ptSysPara->read_244B_LOW_PWM = regData;				
			}
			break;
		}
		case MREGADDRESS_SYS_OUTWIND_PWM_MID_SPEED:
		{
			if(modbusSendLock == 0)
			{
				ptSysPara->read_244C_MID_PWM = regData;				
			}
			break;
		}
		case MREGADDRESS_SYS_OUTWIND_PWM_HIGH_SPEED:
		{
			if(modbusSendLock == 0)
			{
				ptSysPara->read_244D_HIGH_PWM = regData;				
			}
			break;
		}
				
		case MREGADDRESS_EQUIPMENT_STATE:		
			if(modbusSendLock == 0)
			{
				ptSysPara->read_2401_adress_data = regData;

				if((ptSysPara->read_2401_adress_data & 0x0001) == 0x0001)
				{//关机
					//ptSysPara->poweroff = POWEROFF_DIS_OFF;
					//ptSysPara->page_number = 0x00;
				}
				else
				{					
					//ptSysPara->poweroff = POWEROFF_DIS_ON;
					if(ptSysPara->page_number == 0)
					{
						//ptSysPara->page_number = 1;
					}
					
				}

				if((ptSysPara->read_2401_adress_data & 0x0002) == 0x0002)
				{
					ptSysPara->child = 1;
				}
				else
				{					
					ptSysPara->child = 0;
				}
				
				if((ptSysPara->read_2401_adress_data & 0x0010) == 0x0010)
				{
					ptSysPara->timer = 54;//定时开
				}
				else if((ptSysPara->read_2401_adress_data & 0x0040) == 0x0040)
				{
					ptSysPara->timer = 56;//定时关
				}

				if((ptSysPara->read_2401_adress_data & 0x0800) == 0x0800)
				{
					ptSysPara->filter_change_message = 1;//滤网更换提示
				}
				else
				{
					ptSysPara->filter_change_message = 0;
				}

			}
			break;
		case MREGADDRESS_SYS_INDOOR_TEMP:				
			if(modbusSendLock == 0)
			{
				ptSysPara->read_2403_adress_data = regData;
				ptSysPara->measure_temp = ptSysPara->read_2403_adress_data;//R测量温度
			}
			break;
		case MREGADDRESS_SYS_INDOOR_HUMIDTY:			
			if(modbusSendLock == 0)
			{
				ptSysPara->read_2404_adress_data = regData;
				ptSysPara->measure_humidity = ptSysPara->read_2404_adress_data;//R测量湿度
			}
			
			break;
		case MREGADDRESS_SYS_WIND_SPEED_CONTROL:		
			if(modbusSendLock == 0)
			{
				ptSysPara->read_2405_adress_data = regData;
				if(ptSysPara->windspeed == 48 || ptSysPara->windspeed == 50 || ptSysPara->windspeed == 52)
				{//按键未松手状态不更新
					if(ptSysPara->read_2405_adress_data == 1)
					{
						ptSysPara->windspeed = 48;//低图标
					}
					else if(ptSysPara->read_2405_adress_data == 2)
					{
						ptSysPara->windspeed = 50;//中图标
					}
					else if(ptSysPara->read_2405_adress_data == 3)
					{
						ptSysPara->windspeed = 52;//高
					}
				}
			}
			break;
		case MREGADDRESS_SYS_WIND_SPEED_STATE:		
			if(modbusSendLock == 0)
			{
				ptSysPara->read_2406_adress_data = regData;
				if(ptSysPara->read_2406_adress_data == 1)
				{
					ptSysPara->windspeedstate = 48;
				}
				else if(ptSysPara->read_2406_adress_data == 2)
				{
					ptSysPara->windspeedstate = 50;
				}
				else if(ptSysPara->read_2406_adress_data == 3)
				{
					ptSysPara->windspeedstate = 52;
				}
				else
				{
					//无风
				}
			}
			break;
		case MREGADDRESS_SYS_LOW_FILTER_REPLACE_CYCLE:	
			if(modbusSendLock == 0)
			{
				ptSysPara->read_2407_adress_data = regData;
			}
			
			break;
		case MREGADDRESS_SYS_HIGH_FILTER_REPLACE_CYCLE:	
			if(modbusSendLock == 0)
			{
				ptSysPara->read_2408_adress_data = regData;
			}
			
			break;
		case MREGADDRESS_SYS_LOW_FILTER_USE_TIEM:		
			if(modbusSendLock == 0)
			{
				ptSysPara->read_2409_adress_data = regData;
			}
			break;
		case MREGADDRESS_SYS_HIGH_FILTER_USE_TIEM:		
			if(modbusSendLock == 0)
			{
				ptSysPara->read_240A_adress_data = regData;
			}
			
			break;
		case MREGADDRESS_SYS_HUMIDITY_CONTROL_SET:		
			if(modbusSendLock == 0)
			{
				ptSysPara->read_240B_adress_data = regData;
				ptSysPara->humidity_set = ptSysPara->read_240B_adress_data;//RW湿度控制设定值
			}
			
			break;
		case MREGADDRESS_SYS_TEMP_CONTROL_NULL:	
			
			if(modbusSendLock == 0)
			{
				ptSysPara->read_240C_adress_data = regData;
			}

			break;
		case MREGADDRESS_SYS_EQUIPMENT_PROTECT_BYTE:			
			if(modbusSendLock == 0)
			{
				ptSysPara->read_240D_adress_data = regData;
			}
			break;
		case MREGADDRESS_SYS_EQUIPMENT_FAULT_BYTE:	
			if(modbusSendLock == 0)
			{
				ptSysPara->read_240E_adress_data = regData;
			}
			break;
		case MREGADDRESS_SYS_CO2_VALUE:	
			if(modbusSendLock == 0)
			{
				ptSysPara->read_240F_adress_data = regData;
				ptSysPara->measure_co2 = ptSysPara->read_240F_adress_data;//R测量CO2值
			}
			break;
		case MREGADDRESS_SYS_PM_2_5_VALUE:	
			if(modbusSendLock == 0)
			{
				ptSysPara->read_2410_adress_data = regData;
				ptSysPara->measure_pm25 = ptSysPara->read_2410_adress_data;//R测量PM25值
			}
			break;
		case MREGADDRESS_SYS_AIR_INTAKE:	
			if(modbusSendLock == 0)
			{
				ptSysPara->read_2411_adress_data = regData;
			}
			break;
		case MREGADDRESS_SYS_EVAP_TEMP:		
			if(modbusSendLock == 0)
			{
				ptSysPara->read_2412_adress_data = regData;
			}
			break;
		case MREGADDRESS_SYS_HIGH_TEMP_COIL:
			if(modbusSendLock == 0)
			{
				ptSysPara->read_2413_adress_data = regData;
			}
			break;
		case MREGADDRESS_SYS_AUTO_MODE_RUNSTATE:		
			if(modbusSendLock == 0)
			{
				ptSysPara->read_2414_adress_data = regData;
				ptSysPara->automode = ptSysPara->read_2414_adress_data;//R自动模式运行状态

			}
			break;
		case MREGADDRESS_SYS_EQUIPMENT_STATE_BYTE:		
			if(modbusSendLock == 0)
			{
				ptSysPara->read_2415_adress_data = regData;
			}
			break;
		case MREGADDRESS_SYS_FAULT_RESET_BYTE:	
			if(modbusSendLock == 0)
			{
				ptSysPara->read_2416_adress_data = regData;
			}
			break;

		/*case MREGADDRESS_SYS_WATER_STATE:				
			ptSysPara->read_2417_adress_data = regData;
			break;
		case MREGADDRESS_SYS_LIFT_WATER_STATE:			
			ptSysPara->read_2418_adress_data = regData;
			break;
		case MREGADDRESS_SYS_AC_OUTPUT_STATE:		
			ptSysPara->read_2419_adress_data = regData;
			break;
		case MREGADDRESS_SYS_HIGH_TEMP_COIL_PROTECT:				
			ptSysPara->read_241B_adress_data = regData;
			break;
		case MREGADDRESS_RESERVE:
			break;*/
        default:			        break;    
    }
	//R设备状态字
		//ptSysPara->windspeed = ptSysPara->read_2406_adress_data;//R风速状态值
		//ptSysPara->read_2407_adress_data;//RW粗效过滤更换周期
		//ptSysPara->read_2408_adress_data;//RW高效过滤更换周期
		//ptSysPara->read_2409_adress_data;//RW粗效过滤使用时间
		//ptSysPara->read_240A_adress_data;//RW粗效过滤使用时间
		//ptSysPara->read_240C_adress_data;//RW湿度控制死区		
		//ptSysPara->read_240D_adress_data;//R设备保护字
		//ptSysPara->read_240E_adress_data;//R设备故障字
		//ptSysPara->read_2411_adress_data;//R进风温度
		//ptSysPara->read_2412_adress_data;//R低温盘管温度
		//ptSysPara->read_2413_adress_data;//R高温盘管温度
		//ptSysPara->read_2415_adress_data;//R设备状态字1
		//ptSysPara->read_2416_adress_data;//W故障复位字		
		//进风温度设置
		//高温盘管保护温度
		//除湿模式默认设定风速风速
		//湿度值修正系数
		//温度值修正系数

		//CO2修正系数
		//PM25修正系数
}
void mod_oneWire_get_data(unsigned char *_out_Buffer, unsigned short _in_usAddress,
	                               unsigned short _in_usNRegs, unsigned char _in_eMode)
{
    int  iRegIndex;
    u16 currentRegDate = 0;
    
    /*if( ( _in_usAddress >= REG_DISPLAY_START ) &&
        ( _in_usAddress + _in_usNRegs <= REG_DISPLAY_START + REG_DISPLAY_NREGS ) )
    {
        iRegIndex = ( int )( _in_usAddress);
        switch ( _in_eMode )
        {
            case 0X00:
            {
                while( _in_usNRegs > 0 )
                {    
//                    currentRegDate = oneWire_getHoldingRegData(iRegIndex);
                    *_out_Buffer++ = (unsigned char)(currentRegDate>>8);
                    *_out_Buffer++ = (unsigned char)(currentRegDate&0xFF);  
                    iRegIndex++;
                    _in_usNRegs--;                       
                }
                break;
            } 
            case 0X01:  
            {
                while( _in_usNRegs > 0)
                {
                    currentRegDate  = ((u16)(*_out_Buffer++) << 8);
                    currentRegDate |= *_out_Buffer++;
                    processWriteHoldingRegData(iRegIndex,currentRegDate);
                    iRegIndex++;
                    _in_usNRegs--;
                }
                break;
            }
            default:break;
        }
    }*/
 
	if( ( _in_usAddress >= REG_HOLDING_START1 ) &&
	( _in_usAddress + _in_usNRegs <= REG_HOLDING_START1 + REG_HOLDING_NREGS1 ) )
	{
		iRegIndex = ( int )( _in_usAddress);
		switch ( _in_eMode )
		{
			case 0X00:
			{
				while( _in_usNRegs > 0 )
				{    
				//     currentRegDate = oneWire_getHoldingRegData(iRegIndex);
				*_out_Buffer++ = (unsigned char)(currentRegDate>>8);
				*_out_Buffer++ = (unsigned char)(currentRegDate&0xFF);  
				iRegIndex++;
				_in_usNRegs--;                       
				}
				break;
			} 
			case 0X01:  
			{
				while( _in_usNRegs > 0)
				{
					currentRegDate  = ((u16)(*_out_Buffer++) << 8);
					currentRegDate |= *_out_Buffer++;
					processWriteHoldingRegData(iRegIndex,currentRegDate);
					iRegIndex++;
					_in_usNRegs--;
				}
				break;
			}
			default:break;
		}
	}
	else if( ( _in_usAddress >= REG_HOLDING_START_PUBLIC1 ) &&
        ( _in_usAddress + _in_usNRegs <= REG_HOLDING_START_PUBLIC1 + REG_HOLDING_NREGS_PUBLIC1 ) )
    {
        iRegIndex = ( int )( _in_usAddress);
        switch ( _in_eMode )
        {
            case 0X00:
            {
                while( _in_usNRegs > 0 )
                {    
//                    currentRegDate = oneWire_getHoldingRegData(iRegIndex);
                    *_out_Buffer++ = (unsigned char)(currentRegDate>>8);
                    *_out_Buffer++ = (unsigned char)(currentRegDate&0xFF);  
                    iRegIndex++;
                    _in_usNRegs--;                       
                }
                break;
            } 
            case 0X01:  
            {
                while( _in_usNRegs > 0)
                {
                    currentRegDate  = ((u16)(*_out_Buffer++) << 8);
                    currentRegDate |= *_out_Buffer++;
                    processWriteHoldingRegData(iRegIndex,currentRegDate);
                    iRegIndex++;
                    _in_usNRegs--;
                }
                break;
            }
            default:break;
        }
    }
	else if( ( _in_usAddress >= REG_HOLDING_START2 ) &&
	( _in_usAddress + _in_usNRegs <= REG_HOLDING_START2 + REG_HOLDING_NREGS2 ) )
	{
		iRegIndex = ( int )( _in_usAddress);
		switch ( _in_eMode )
		{
			case 0X00:
			{
				while( _in_usNRegs > 0 )
				{    
				//     currentRegDate = oneWire_getHoldingRegData(iRegIndex);
				*_out_Buffer++ = (unsigned char)(currentRegDate>>8);
				*_out_Buffer++ = (unsigned char)(currentRegDate&0xFF);  
				iRegIndex++;
				_in_usNRegs--;                       
				}
				break;
			} 
			case 0X01:  
			{
				while( _in_usNRegs > 0)
				{
					currentRegDate  = ((u16)(*_out_Buffer++) << 8);
					currentRegDate |= *_out_Buffer++;
					processWriteHoldingRegData(iRegIndex,currentRegDate);
					iRegIndex++;
					_in_usNRegs--;
				}
				break;
			}
			default:break;
		}
	}
}
void APP_oneWire_init(void)
{
		MP_memPool_init(&onewire_txMemPool,onewire_txBuffer,ONEWIRE_TX_BUFFER_SIZE);//
		onewire_txBuffer[0].busyFlag = 0;
		onewire_txBuffer[0].frameLength = 0;
		
		onewire_txBuffer[1].busyFlag = 0;
		onewire_txBuffer[1].frameLength = 0;
		
		onewire_txBuffer[2].busyFlag = 0;
		onewire_txBuffer[2].frameLength = 0;
}
void APP_oneWire_timing_send(void)
{
		u8 buff[6];
	  regAddress = 0x2430;
	  regCount = 32;
		buff[0] = 0xfa;
	  buff[1] = 0x03;
	  buff[2] = (unsigned char)(regAddress>>8);
	  buff[3] = (unsigned char)(regAddress);
		buff[4] = (unsigned char)(regCount>>8);
	  buff[5] = (unsigned char)(regCount);
	  mod_oneWire_send_frame(buff,6);
}
void APP_oneWire_timing_485_send(u16 cmd0, u16 cmd1)
{
	u8 buff[6];
	buff[0] = 0xFA;
	buff[1] = 0x06;
	buff[2] = (unsigned char)(cmd0>>8);
	buff[3] = (unsigned char)(cmd0);
	buff[4] = (unsigned char)(cmd1>>8);
	buff[5] = (unsigned char)(cmd1);
	mod_oneWire_send_frame(buff,6);
}

void APP_oneWire_readcmd_485_data(void)
{
	u8 buff[6];
	regAddress = 0x2201;
	regCount = 4;
	buff[0] = 0xfa;
	buff[1] = 0x03;
	buff[2] = (unsigned char)(regAddress>>8);
	buff[3] = (unsigned char)(regAddress);
	buff[4] = (unsigned char)(regCount>>8);
	buff[5] = (unsigned char)(regCount);
	mod_oneWire_send_frame(buff,6);
}


timeOutEvent_t  idata sendLockDelay;
void APP_oneWire_send_485_data(u16 address,u16 value)
{
		MP_mem_object_t *ptGetMemory = 0; 
		ptGetMemory = MP_memPool_new(&onewire_txMemPool);
		regAddress = address;
		if(ptGetMemory != NULL)
		{
			ptGetMemory->buffer[0] = 0xfa;	
			ptGetMemory->buffer[1] = 0x06;	
			ptGetMemory->buffer[2] = (u8)(address>>8);
			ptGetMemory->buffer[3] = (u8)(address);
			ptGetMemory->buffer[4] = (u8)(value>>8);
			ptGetMemory->buffer[5] = (u8)(value);
			ptGetMemory->frameLength = 6;
			modbusSendLock = 1;
			Pub_softTimer_set_event(&sendLockDelay,1000);
			return;
		}
		MP_memPool_free( ptGetMemory);     
}

void APP_oneWire_read_485_data(u16 address,u16 len)
{
		MP_mem_object_t *ptGetMemory = 0; 
		ptGetMemory = MP_memPool_new(&onewire_txMemPool);
		regAddress = address;
	  regCount = len;
		if(ptGetMemory != NULL)
		{
			  ptGetMemory->buffer[0] = 0x01;	
				ptGetMemory->buffer[1] = 0x03;	
			  ptGetMemory->buffer[2] = (u8)(address>>8);
				ptGetMemory->buffer[3] = (u8)(address);
				ptGetMemory->buffer[4] = (u8)(len>>8);
				ptGetMemory->buffer[5] = (u8)(len);
				ptGetMemory->frameLength = 6;
				return;
		}
		MP_memPool_free( ptGetMemory);     
}
void app_onrwire_task1(void)
{
	static u16 lastTick = 0;
	
    SysPara_t *ptSysPara;  
	ptSysPara =  controler_getSysParaPt();
	
	mde_mrtu_master_task(GetSysTickMillisecond());

	if((GetSysTickMillisecond() - lastTick) >= 2000)
	{
		lastTick = GetSysTickMillisecond();
		ptSysPara->debugcount++;
		mde_mRtu_master_cmd0x03_transmit(0,0xfa,0x1000,0x0003);
	}
}
void APP_oneWire_task(void)
{
  	SysPara_t *ptSysPara;  
	static u8 oneWire = 0;
	static u16 lastTick = 0;
	static u8 idleStatus = 0;
	static u8 step = 0;
	static timeOutEvent_t  oneWireReceiveDelay;
	static timeOutEvent_t  oneWireSendDelay;
	MP_mem_object_t *ptGetMemory = 0;
	
	u16 adress = 0;
	u16 cmd	   = 0;

	u8 writeBuff[2]={0,0};
	u8 buff[128];
	u16 length;
	ptSysPara =  controler_getSysParaPt();
	
	if(oneWire == 0)
	{
		//init
		oneWire = 1;
		modbusSendLock = 0;
		APP_oneWire_init();
	}
	else
	{
		if(mod_oneWire_receive_frame(buff,&length))
		{
			if(buff[1] == 0x03)
			{
				mod_oneWire_get_data(&buff[3],regAddress,regCount,0x01);
			}
			else if(buff[1] == 0x06)
			{
				modbusSendLock = 0;
			}
		}
		else
		{
			if(idleStatus == 0)
			{
				ptGetMemory = MP_memPool_peek(&onewire_txMemPool);
				if(0!= ptGetMemory)
				{
					//ptSysPara->debugdata = ptGetMemory->busyFlag;
					if(ptGetMemory->busyFlag)
					{ 
						mod_oneWire_send_frame(ptGetMemory->buffer,ptGetMemory->frameLength);
						MP_memPool_free(ptGetMemory);	
						lastTick = GetSysTickMillisecond();
						idleStatus = 1;
						Pub_softTimer_set_event(&oneWireSendDelay,200);
					}		
					
				}
				else if((GetSysTickMillisecond() - lastTick) >= 400)
				{
					lastTick = GetSysTickMillisecond();
					if(step == 0)
					{
							APP_oneWire_timing_send();
							step = 1;											
					}
					else
					{
							APP_oneWire_readcmd_485_data();
							step = 0;
					}
					//ptSysPara->debugdata = step+1;
					Pub_softTimer_set_event(&oneWireReceiveDelay,200);
				}
			}
		}
		
		if(Pub_softTimer_get_event_and_clear(&oneWireReceiveDelay,GetSysTickMillisecond()))
		{

		}
		if(Pub_softTimer_get_event_and_clear(&oneWireSendDelay,GetSysTickMillisecond()))
		{
			idleStatus = 0;
		}
		if(Pub_softTimer_get_event_and_clear(&sendLockDelay,GetSysTickMillisecond()))
		{
			modbusSendLock = 0;
		}
	}
	mod_oneWire_task();
}
//------------------------------E N D-------------------------------------------


//------------------------APP.oneWire.C--END----------------------------------


