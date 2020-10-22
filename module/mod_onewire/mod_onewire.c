/***************************************************************************
* Designed by Osman Li <Li.haimeng@menred.com> 
* Copyright , Menred Group Corporation.
* This software is owned by Menred Group and is protected by and subject to 
* worldwide patent protection (china and foreign)
 ***************************************************************************/
 /***************************************************************************
* Release Notes:
*     V1.1  
*         Data: 
*          
*     V1.0  
*         Data:2015.1.26
*         Official release
****************************************************************************/

/*============================ INCLUDES ======================================*/
//#include "..\Public\Pub_ringBuffer.h"
//#include "..\Public\Pub_crc.h"
//#include "..\Sources\uart.h"

#include ".\mod_onewire.h"
#include ".\application\app_configure.h"
/*============================ MACROS ========================================*/
/*============================ PROTOTYPES ====================================*/
/*============================ IMPLEMENTATION ================================*/
/*! \brief   
 *! \param  
 *! \retval  
 *! \retval  
 */
unsigned short      usRegAddress;
unsigned short      usRegCount;

void mod_oneWire_send_frame(unsigned char *_in_buff,unsigned short _in_len)
{
	unsigned short crc = 0;
	u8 buff[8];
	u8 i = 0;
	u16 len = _in_len+2;
	usRegAddress = (((unsigned short)_in_buff[2]) << 8) | _in_buff[3]; 
	usRegCount = (((unsigned short)_in_buff[4]) << 8) | _in_buff[5]; 
	for(i = 0;i < _in_len;i++)
	{
		buff[i]  = _in_buff[i];
	} 
	crc = crc16table(buff,_in_len);
	buff[6] = (unsigned char)(crc);
	buff[7] = (unsigned char)(crc>>8);
	Uart5SendStr(buff,len);
}


#define FIFO_STATUS_IDLE       0x01
#define FIFO_STATUS_ADD        0x02
#define FIFO_STATUS_COMMAND    0x03
#define FIFO_STATUS_DATA       0x04
#define ADDRESS                0x01
#define SIGNAL_READ            0x03
#define SIGNAL_WRITE           0x06
#define MUTIL_WRITE            0x10

/*unsigned char validBuffer[50];
void onewire_get_frame_from_ringBuff(void)
{
		static unsigned char fifoStatus = FIFO_STATUS_IDLE;
    switch(fifoStatus)
    {
        case FIFO_STATUS_IDLE:
        {
            if(ringBuffer_items_counter(&uartRxFifo))
            {              
                ringBuffer_read(&uartRxFifo,&validBuffer[0],1);
                if(validBuffer[0] == ADDRESS)
                {
                    fifoStatus = FIFO_STATUS_ADD;
                }
            }                  
            break;
        }
        case FIFO_STATUS_ADD:
        {
            if(ringBuffer_items_counter(&uartRxFifo))
            {
                ringBuffer_read(&uartRxFifo,&validBuffer[1],1);
                if((validBuffer[1] == SIGNAL_READ)||
									(validBuffer[1] == SIGNAL_WRITE||
								  (validBuffer[1] == MUTIL_WRITE)))
                {
                    fifoStatus = FIFO_STATUS_COMMAND;
                }
                else
                {
                    fifoStatus = FIFO_STATUS_IDLE;
                }
            }
            else
            {
                fifoStatus = FIFO_STATUS_IDLE;
            }
            break;
        }
        case FIFO_STATUS_COMMAND:
        {
            if(ringBuffer_items_counter(&uartRxFifo))
            {    
							  if(validBuffer[1] == SIGNAL_READ)
							  {
										ringBuffer_read(&uartRxFifo,&validBuffer[2],1);
										if(ringBuffer_items_counter(&uartRxFifo)>= (validBuffer[2]+2))
										{
												ringBuffer_read(&uartRxFifo,&validBuffer[3],(validBuffer[2]+2));
												oneWireHal.receivedDataFlag = 1;
										}
								}
								else
							  {
										if(ringBuffer_items_counter(&uartRxFifo)>= 6)
									  {
												ringBuffer_read(&uartRxFifo,&validBuffer[2],6); 
											  oneWireHal.receivedDataFlag = 1;										
										}
								}
            }
            else
            {
                fifoStatus = FIFO_STATUS_IDLE;
            }
            break;
        }
        default:
        {
            break;
        }
    }
}*/


u8 idata tempBuff[100];
u8 flag = 0;
u8 rxLen = 0;
void uart_receive_scan(void)
{
	u8 i = 0;
	static u16 lastTick = 0;
	if(GetSysTickMillisecond() != lastTick)
	{
		lastTick = GetSysTickMillisecond();
		if(delayTime!=0)
		{
			delayTime--;
			if(delayTime == 0)
			{
				if(uart5_rx_count < UART5_MAX_LEN)//60)//一次接受的最大缓存lzh
				{
					flag = 1;
					for(i = 0;i < uart5_rx_count;i++)
					{
						tempBuff[i] = Uart5_Rx[i];
					}	
					rxLen = uart5_rx_count;								
					uart5_rx_count = 0;
				}
			}
		}
	}
}

bit mod_oneWire_receive_frame(unsigned char *_out_buff,unsigned short *_out_len)
{
	u8 i = 0;
	if(flag == 1)
	{
		flag = 0;
		if((crc16table(tempBuff, rxLen) == 0))
		{
			for(i = 0;i < rxLen;i++)
			{
				_out_buff[i] = tempBuff[i];
			}			
			*_out_len = rxLen;
			return 1;
		}
		return 0;
	}
	return 0;
}


#define READ    0x00
#define WRITE   0x01
#define ADD     0x01
void mod_oneWire_task(void)
{    
	uart_receive_scan();  
}

//new start 20201021
typedef enum
{
    mmRunS_idle             = 0x00,
    mmRunS_transmit_str,
    mmRunS_transmit_35T,
    mmRunS_transmit_data,
    mmRunS_transmit_stop,    
    mmRunS_transmit_end,
    mmRunS_receive_wait,
    mmRunS_receive_data,
    mmRunS_receive_end,
}modbus_master_runState_def;

//modbus操作结构体
//-----------------------------------------------------------------------------
/*typedef struct
{
   // mRtu_parameter_def  mRtu_parameter;
    mRtu_master_status_def      mmRtu_status;
    modbus_master_runState_def  mmoo_runStutus;

    unsigned char  receive_buff[256];
    unsigned char  rev_index;
    unsigned char  transmit_buff[256];
    unsigned char  transmit_length;
    unsigned char  transmit_index;
    //timerClock_def timer_revTimeOut;

    unsigned int readReg_addr;
    unsigned char readReg_length;
    unsigned int writeReg_addr;
    unsigned char writeReg_length;

    unsigned char (*pull_receive_byte)(unsigned char *out_rByte);
    unsigned char (*push_transmit_byte)(unsigned char in_tByte);
	
    unsigned char (*pull_busFree)(unsigned char t_char_dis);
    void (*restart_busFree_timer)(void);
	
    void (*phy_into_receive)(void);
    void (*phy_into_transmit_status)(void);
	
    unsigned char (*pull_transmit_complete)(void);
}modbus_master_oper_def;

static unsigned char modbus_master_receive_protocol(modbus_master_oper_def* mix_mm_oper);

static void modbus_master_oop_task(modbus_master_oper_def* mix_mm_oper)
{
	unsigned char push_succeed;
	unsigned char  receive_byte;
    //pbc_timerMillRun_task(&mix_mm_oper->timer_revTimeOut);
    switch(mix_mm_oper->mmoo_runStutus)
    {
        case mmRunS_idle:
        {
            break;
        }
        case mmRunS_transmit_str:
        {
            mix_mm_oper->phy_into_transmit_status();
            mix_mm_oper->restart_busFree_timer();
            mix_mm_oper->mmoo_runStutus = mmRunS_transmit_35T;
            break;
        }
        case mmRunS_transmit_35T:
        {
            if(mix_mm_oper->pull_busFree(35))
            {
                mix_mm_oper->mmoo_runStutus = mmRunS_transmit_data;
                mix_mm_oper->transmit_index = 0;
            }
            break;
        }
        case mmRunS_transmit_data:
        {
            if(mix_mm_oper->transmit_length != 0)
            {
                while(1)
                {
                    push_succeed = mix_mm_oper->push_transmit_byte(mix_mm_oper->transmit_buff[mix_mm_oper->transmit_index]);
                    if(push_succeed)
                    {
                        mix_mm_oper->transmit_index ++;
                        mix_mm_oper->transmit_length --;
                        if(0 == mix_mm_oper->transmit_length)
                        {
                            mix_mm_oper->mmoo_runStutus = mmRunS_transmit_stop;
                            break;
                        }
                    }
                    else
                    {
                        break;
                    }
                }
            }
            break;
        }
        case mmRunS_transmit_stop:
        {
            if(mix_mm_oper->pull_transmit_complete())
            {
                mix_mm_oper->restart_busFree_timer();
                mix_mm_oper->mmoo_runStutus = mmRunS_transmit_end;
            }
            break;
        }
        case mmRunS_transmit_end:
        {
            if(mix_mm_oper->pull_busFree(25)) //标准3.5T，使用2.5T的结束符，放宽检测条件
            {
                mix_mm_oper->phy_into_receive();
                mix_mm_oper->mmoo_runStutus = mmRunS_receive_wait;//转入接收等待，设置超时
                pbc_reload_timerClock(&mix_mm_oper->timer_revTimeOut,100); //100ms timeout
            }
            break;
        }
        case mmRunS_receive_wait:
        {
            if(mix_mm_oper->pull_receive_byte(&receive_byte))
            {
                mix_mm_oper->receive_buff[0] = receive_byte;
                mix_mm_oper->rev_index = 1;
                mix_mm_oper->mmoo_runStutus = mmRunS_receive_data;
                mix_mm_oper->restart_busFree_timer();
            }
            else if(pbc_pull_timerIsCompleted(&mix_mm_oper->timer_revTimeOut))
            {
                mix_mm_oper->mmRtu_status = mRtuS_master_timeout;  //超时
                mix_mm_oper->mmoo_runStutus = mmRunS_idle;
            }
            break;
        }
        case mmRunS_receive_data:
        {
            while(1)
            {
                if(mix_mm_oper->pull_receive_byte(&receive_byte))
                {
                    mix_mm_oper->receive_buff[mix_mm_oper->rev_index] = receive_byte;
                    mix_mm_oper->rev_index ++;
                    mix_mm_oper->restart_busFree_timer();
                }
                else
                {
                    if(mix_mm_oper->pull_busFree(20))  //标准3.5T,检测2.0T视为报文完成
                    {
                        if(modbus_master_receive_protocol(mix_mm_oper))
                        {
                            mix_mm_oper->mmRtu_status = mRtuS_master_complete;
                            mix_mm_oper->mmoo_runStutus = mmRunS_idle;
                        }
                        else
                        {
                            mix_mm_oper->mmRtu_status = mRtuS_master_poterr; 
                            mix_mm_oper->mmoo_runStutus = mmRunS_idle;  //产生接收错误
                        }
                    }
                    break; 
                }
            }
            break;
        }

        default:
        {
            mix_mm_oper->mmoo_runStutus = mmRunS_idle;
            break;
        }
    }
}*/

//+++++++++++++++++++++++++++++++solid++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//#define max_solid    1
//--------------------------------------------------------------------------------------------------------------------------
//static modbus_master_oper_def modbus_master_solid[max_solid];
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
static void modbus_master_solid_cfg(void)
{
//--------------------------------------------------------------------------------------------------------------------------
    //bsp_uart5_cfg();
    /*modbus_master_solid[0].pull_receive_byte = bsp_pull_oneByte_uart5_rxd;
    modbus_master_solid[0].push_transmit_byte = bsp_push_oneByte_uart5_txd;
    modbus_master_solid[0].pull_busFree = bsp_uart5_busFree;
    modbus_master_solid[0].restart_busFree_timer = bsp_restart_tim4;
    modbus_master_solid[0].phy_into_receive = bps_uart5_into_receive;
    modbus_master_solid[0].phy_into_transmit_status = bps_uart5_into_transmit;
    modbus_master_solid[0].pull_transmit_complete =bsp_pull_uart5_txd_cmp;*/
//---------------------------------------------------------------------------------------------------------------------------
}

/*void mde_mrtu_master_task(void)
{
	unsigned char i;
	static unsigned char cfged = 0;
	if(cfged)
	{
        
        for(i = 0;i < max_solid;i ++)
        {
            modbus_master_oop_task(&modbus_master_solid[i]);
        }
	}
	else
	{
		cfged = 1;
		modbus_master_solid_cfg();
	}
}*/
//------------------------------E N D-------------------------------------------

/* EOF */
