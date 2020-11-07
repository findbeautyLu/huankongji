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


#define  READ_REG_START_ADRESS_0 				MRegaddr_NewairControlW		//第一队列
#define  REG_S_ADRESS_0_OFFSET_1 				(READ_REG_START_ADRESS_0 + 1)
#define  REG_S_ADRESS_0_OFFSET_2 				(READ_REG_START_ADRESS_0 + 2)
#define  REG_S_ADRESS_0_OFFSET_3 				(READ_REG_START_ADRESS_0 + 3)
#define  REG_S_ADRESS_0_OFFSET_4 				(READ_REG_START_ADRESS_0 + 4)
#define  REG_S_ADRESS_0_OFFSET_5 				(READ_REG_START_ADRESS_0 + 5)
#define  REG_S_ADRESS_0_OFFSET_6 				(READ_REG_START_ADRESS_0 + 6)
#define  READ_REG_START_ADRESS_1 				MRegaddr_Aircod_FRE			//第二队列 更换地址接口
#define  REG_S_ADRESS_1_OFFSET_1 				(READ_REG_START_ADRESS_1 + 1)
#define  REG_S_ADRESS_1_OFFSET_2 				(READ_REG_START_ADRESS_1 + 2)
#define  REG_S_ADRESS_1_OFFSET_3 				(READ_REG_START_ADRESS_1 + 3)
#define  REG_S_ADRESS_1_OFFSET_4 				(READ_REG_START_ADRESS_1 + 4)
#define  REG_S_ADRESS_1_OFFSET_5 				(READ_REG_START_ADRESS_1 + 5)
#define  REG_S_ADRESS_1_OFFSET_6 				(READ_REG_START_ADRESS_1 + 6)
#define  REG_S_ADRESS_1_OFFSET_7 				(READ_REG_START_ADRESS_1 + 7)
#define  REG_S_ADRESS_1_OFFSET_8 				(READ_REG_START_ADRESS_1 + 8)
#define  REG_S_ADRESS_1_OFFSET_9 				(READ_REG_START_ADRESS_1 + 9)
#define  REG_S_ADRESS_1_OFFSET_a 				(READ_REG_START_ADRESS_1 + 10)
#define  REG_S_ADRESS_1_OFFSET_b 				(READ_REG_START_ADRESS_1 + 11)
#define  REG_S_ADRESS_1_OFFSET_c 				(READ_REG_START_ADRESS_1 + 12)
#define  REG_S_ADRESS_1_OFFSET_d 				(READ_REG_START_ADRESS_1 + 13)
#define  REG_S_ADRESS_1_OFFSET_e 				(READ_REG_START_ADRESS_1 + 14)
#define  REG_S_ADRESS_1_OFFSET_f				(READ_REG_START_ADRESS_1 + 15)
#define  REG_S_ADRESS_1_OFFSET_10 				(READ_REG_START_ADRESS_1 + 16)
#define  REG_S_ADRESS_1_OFFSET_11				(READ_REG_START_ADRESS_1 + 17)
#define  REG_S_ADRESS_1_OFFSET_12 				(READ_REG_START_ADRESS_1 + 18)
#define  REG_S_ADRESS_1_OFFSET_13 				(READ_REG_START_ADRESS_1 + 19)
#define  REG_S_ADRESS_1_OFFSET_14 				(READ_REG_START_ADRESS_1 + 20)
#define  REG_S_ADRESS_1_OFFSET_15 				(READ_REG_START_ADRESS_1 + 21)
#define  REG_S_ADRESS_1_OFFSET_16 				(READ_REG_START_ADRESS_1 + 22)
#define  REG_S_ADRESS_1_OFFSET_17 				(READ_REG_START_ADRESS_1 + 23)
#define  REG_S_ADRESS_1_OFFSET_18 				(READ_REG_START_ADRESS_1 + 24)
#define  REG_S_ADRESS_1_OFFSET_19 				(READ_REG_START_ADRESS_1 + 25)
#define  REG_S_ADRESS_1_OFFSET_1a 				(READ_REG_START_ADRESS_1 + 26)
#define  REG_S_ADRESS_1_OFFSET_1b 				(READ_REG_START_ADRESS_1 + 27)
#define  REG_S_ADRESS_1_OFFSET_1c 				(READ_REG_START_ADRESS_1 + 28)
#define  REG_S_ADRESS_1_OFFSET_1d 				(READ_REG_START_ADRESS_1 + 29)
#define  REG_S_ADRESS_1_OFFSET_1e 				(READ_REG_START_ADRESS_1 + 30)
#define  REG_S_ADRESS_1_OFFSET_1f 				(READ_REG_START_ADRESS_1 + 31)

//接口
#define  READ_REG_NUMBER			39
#define  MIN_REG_ADRESS				READ_REG_START_ADRESS_0	
#define  MAX_REG_ADRESS				REG_S_ADRESS_1_OFFSET_1f

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
	
typedef struct
{
	unsigned int reg_adress;
	unsigned int reg_dat;
}modbus_dat_t;

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
void mde_mrtu_master_set_stransmit(unsigned char in_control_cmd,unsigned char in_slave_addr,unsigned int in_reg_addr,unsigned int in_reg_length_or_dat);

extern modbus_master_oper_def modbus_master_solid[max_solid];
extern unsigned char modbus_master_tx[64];
extern modbus_dat_t rx_onewire_dat[];

extern unsigned int statecount[];


extern unsigned int pull_reg_dat(unsigned int reg_adress);



#endif
/* EOF */
