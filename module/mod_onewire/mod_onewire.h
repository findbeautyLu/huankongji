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

#ifndef __MOD_ONE_WIRE_H__
#define __MOD_ONE_WIRE_H__  
/*============================ INCLUDES ======================================*/
/*============================ MACROS ========================================*/
/*============================ MACROFIED FUNCTIONS ===========================*/
/*============================ TYPES =========================================*/ 
/*============================ GLOBAL VARIABLES ==============================*/
/*============================ LOCAL VARIABLES ===============================*/
/*============================ PROTOTYPES ====================================*/
//------------------------------------------------------------------------------
//名称:模块单线任务扫描
// 入口:    _in_ms_tick,ms级时间 <<--- 传入
//出口:无
void mod_oneWire_task(void);
//------------------------------------------------------------------------------
//名称:模块单线发送帧
//说明：按modbus格式发送数据，应用层调用
//入口：*_in_remotePadData,结构体
//出口:true 数据可以正常发送， false 数据忙，需要等待再发
void mod_oneWire_send_frame(unsigned char *_in_buff,unsigned short _in_len);//发送数据
bit mod_oneWire_receive_frame(unsigned char *_out_buff,unsigned short *_out_len);//获取数据
//------------------------------------------------------------------------------
//名称:模块单线接收帧
//说明：按modbus格式接收数据，应用层调用
//入口：*_out_remotePadData，结构体
//出口:true 有收到数据，  false 无数据
//void mod_oneWire_get_data(unsigned char *_out_Buffer, unsigned short _in_usAddress,unsigned short _in_usNRegs, unsigned char _in_eMode);

typedef enum 
{
    mRtuS_master_none       = 0x00,
    mRtuS_master_complete   = 0x01,
    mRtuS_master_timeout    = 0x02,
    mRtuS_master_poterr     = 0x03,
}mRtu_master_status_def;









#endif
/* EOF */
