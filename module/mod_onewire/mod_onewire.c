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

//------------------------------E N D-------------------------------------------

/* EOF */
