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
#define max_solid    1

/*============================ MACROFIED FUNCTIONS ===========================*/
/*============================ TYPES =========================================*/ 
typedef enum 
{
    mRtuS_master_none       = 0x00,
    mRtuS_master_complete   = 0x01,
    mRtuS_master_timeout    = 0x02,
    mRtuS_master_poterr     = 0x03,
}mRtu_master_status_def;

typedef enum
{
    mmRunS_idle             = 0x00,
    mmRunS_transmit_str,//1
    mmRunS_transmit_35T,//2
    mmRunS_transmit_data,//3
    mmRunS_transmit_stop,//4 
    mmRunS_transmit_end,//5
    mmRunS_receive_wait,//6
    mmRunS_receive_data,//7
    mmRunS_receive_end,//8
}modbus_master_runState_def;

//有点意向把实例化的代码挪到app层，有点纠结
typedef struct
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
    void (*push_transmit_str)(unsigned char *dat,unsigned char len);
	
    unsigned char (*pull_busFree)(unsigned char t_char_dis);
    void (*restart_busFree_timer)(void);
	
    void (*phy_into_receive)(void);
    void (*phy_into_transmit_status)(void);
	
    unsigned char (*pull_transmit_complete)(void);
}modbus_master_oper_def;

typedef struct
{
	modbus_master_runState_def runstate;
	unsigned char  transmit_buff[256];
    unsigned char  transmit_length;
    unsigned char  transmit_index;
	
	unsigned char  receive_buff[256];
	unsigned char  rev_index;

	void (*push_transmit_str)(unsigned char *,unsigned char );
}modbus_master_t;

typedef enum
{
	SINGLE_READ_ONLY = 0x03,
	SINGLE_WRITER_ONLY = 0x06,
	CONTINUE_WRITE = 0x10,
	CONTINUE_READ_WRITE = 0x17,
}modbus_cmd_t;

typedef struct
{
	modbus_cmd_t cmd;
	unsigned int length;
	unsigned int read_adress;
	unsigned int write_adress;
	unsigned int write_dat;
	unsigned char psendbuf[64];
}modbus_praram_t;
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

void mde_mrtu_master_task(unsigned int systimecount);

//------------------------------------------------------------------------------
//名称:模块单线接收帧
//说明：按modbus格式接收数据，应用层调用
//入口：*_out_remotePadData，结构体
//出口:true 有收到数据，  false 无数据
//void mod_oneWire_get_data(unsigned char *_out_Buffer, unsigned short _in_usAddress,unsigned short _in_usNRegs, unsigned char _in_eMode);



void mde_mRtu_master_cmd0x03_transmit(unsigned char in_solidNum,unsigned char in_slave_addr,unsigned int in_reg_addr,unsigned int in_reg_length);

extern modbus_master_oper_def modbus_master_solid[max_solid];
extern unsigned char modbus_master_tx[64];

extern unsigned int statecount[];





#endif
/* EOF */
