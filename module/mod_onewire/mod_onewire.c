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



//Uart5SendStr(mix_mm_oper->transmit_buff,modbus_master_solid[0].sendcompele);
//stop

uint8_t Uart5ReceiveByte(uint8_t *out_rx_data)
{
	static uint8_t start_adress = 0;
	uint8_t re_back;
	if(start_adress >= uart5_rx_count)
	{
		start_adress = 0;
		uart5_rx_count = 0;
		re_back = 0;
	}
	else
	{
		*out_rx_data = Uart5_Rx[start_adress];
		start_adress++;
		re_back = 1;
	}

	return re_back;
}

#define READ    0x00
#define WRITE   0x01
#define ADD     0x01
void mod_oneWire_task(void)
{    
	uart_receive_scan();  
}




//new start 20201021

	


//modbus操作结构体
//-----------------------------------------------------------------------------


static unsigned char modbus_master_receive_protocol(modbus_master_oper_def* mix_mm_oper);

static void modbus_master_oop_task(modbus_master_oper_def* mix_mm_oper,unsigned int runtimecount)
{
	static unsigned int lasttimecount = 0;
	static unsigned int difftimecount = 0;
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
           					//mix_mm_oper->push_transmit_str(mix_mm_oper->transmit_buff,mix_mm_oper->transmit_index);//死等发送
                            mix_mm_oper->mmoo_runStutus = mmRunS_transmit_stop;
							statecount++;
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
        	statecount = mmRunS_transmit_end;
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
                lasttimecount = runtimecount;
                //pbc_reload_timerClock(&mix_mm_oper->timer_revTimeOut,100); //100ms timeout
            }
            break;
        }
        case mmRunS_receive_wait:
        {
        	difftimecount = runtimecount - lasttimecount;
            if(mix_mm_oper->pull_receive_byte(&receive_byte))
            {
                mix_mm_oper->receive_buff[0] = receive_byte;
                mix_mm_oper->rev_index = 1;
                mix_mm_oper->mmoo_runStutus = mmRunS_receive_data;
                mix_mm_oper->restart_busFree_timer();
            }
            else if(difftimecount > 100)//(pbc_pull_timerIsCompleted(&mix_mm_oper->timer_revTimeOut))
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
}

//+++++++++++++++++++++++++++++++solid++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//#define max_solid    1
//--------------------------------------------------------------------------------------------------------------------------
modbus_master_oper_def modbus_master_solid[max_solid];
uint16_t statecount = 0;

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

uint8_t Uart5TransferByte(uint8_t out_tx_data)
{
	modbus_master_solid[0].transmit_buff[modbus_master_solid[0].transmit_index] = out_tx_data;
	return 1;
}

unsigned char bsp_pull_uart5_txd_cmp(void)
{
	if(modbus_master_solid[0].mmoo_runStutus == mmRunS_transmit_stop)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

static void modbus_master_solid_cfg(void)
{
//--------------------------------------------------------------------------------------------------------------------------
    //bsp_uart5_cfg();
    modbus_master_solid[0].pull_receive_byte = Uart5ReceiveByte;
    modbus_master_solid[0].push_transmit_byte = Uart5TransferByte;
	modbus_master_solid[0].push_transmit_str = Uart5SendStr;
    modbus_master_solid[0].pull_busFree = bsp_uart5_busfree;//发送和接收数据的延迟
    modbus_master_solid[0].restart_busFree_timer = bsp_uart5_restart_timecount;//清空延迟计数
    modbus_master_solid[0].phy_into_receive = bsp_uart5_into_receive;//硬件层的拉高拉低，下同
    modbus_master_solid[0].phy_into_transmit_status = bsp_uart5_into_transmit;
    modbus_master_solid[0].pull_transmit_complete =bsp_pull_uart5_txd_cmp;//临时通过编译
    modbus_master_solid[0].mmoo_runStutus = mmRunS_idle;
//---------------------------------------------------------------------------------------------------------------------------
}

void mde_mrtu_master_task(unsigned int systimecount)
{
	unsigned char i;
	static unsigned char cfged = 0;
	if(cfged)
	{
        //Uart5SendStr(&modbus_master_solid[0].transmit_buff[0],8);
        for(i = 0;i < max_solid;i ++)
        {
            modbus_master_oop_task(&modbus_master_solid[0],systimecount);
			
			modbus_master_solid[0].push_transmit_str(modbus_master_solid[0].transmit_buff,modbus_master_solid[0].transmit_index);

        }
	}
	else
	{
		cfged = 1;
		modbus_master_solid_cfg();
	}
}

static void append_crc_to_message(modbus_master_oper_def* mix_mm_oper)
{
    unsigned char crc_value[2];
        
    Crc16CalculateOfByte(&mix_mm_oper->transmit_buff[0],(unsigned int)mix_mm_oper->transmit_length,&crc_value[0]);//crc
    mix_mm_oper->transmit_buff[mix_mm_oper->transmit_length] = crc_value[1];
    mix_mm_oper->transmit_buff[mix_mm_oper->transmit_length+1] = crc_value[0];
    mix_mm_oper->transmit_length += 2;
}

void mde_mRtu_master_cmd0x03_transmit(unsigned char in_solidNum,unsigned char in_slave_addr,unsigned int in_reg_addr,unsigned int in_reg_length)
{
    modbus_master_solid[in_solidNum].transmit_buff[0] = in_slave_addr;
    modbus_master_solid[in_solidNum].transmit_buff[1] = 0x03;
    modbus_master_solid[in_solidNum].transmit_buff[2] = (unsigned char)(in_reg_addr >> 8);
    modbus_master_solid[in_solidNum].transmit_buff[3] = (unsigned char)(in_reg_addr);
    modbus_master_solid[in_solidNum].transmit_buff[4] = (unsigned char)(in_reg_length >> 8);
    modbus_master_solid[in_solidNum].transmit_buff[5] = (unsigned char)(in_reg_length);
    modbus_master_solid[in_solidNum].transmit_length = 6;
    append_crc_to_message(&modbus_master_solid[in_solidNum]);
    modbus_master_solid[in_solidNum].mmoo_runStutus = mmRunS_transmit_str;
}

//------------------------------E N D-------------------------------------------

/* EOF */
