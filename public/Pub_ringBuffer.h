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

#ifndef __RING_BUFFER_H__
#define __RING_BUFFER_H__

/*============================ INCLUDES ======================================*/
/*============================ MACROS ========================================*/
/*============================ MACROFIED FUNCTIONS ===========================*/
/*============================ TYPES =========================================*/
typedef struct{
	unsigned short 	in;
	unsigned short 	out;
	unsigned short 	size;
	unsigned char		*ptBuffer;
}ringBuffer_t;
/*============================ GLOBAL VARIABLES ==============================*/
/*============================ LOCAL VARIABLES ===============================*/
/*============================ PROTOTYPES ====================================*/
//++++++++++++++++++++++++++++++start+++++++++++++++++++++++++++++++++++++++++++
//Function
//名称: 环形队列初始化
//功能: 配置环形队列的大小及缓存区
//入口: *_in_ringBuf   输入队列地址        <<-------------------------传入
//入口: *_in_ptBuffer  输入缓冲区地址      <<-------------------------传入
//入口: _in_size    输入长度               <<-------------------------传入
//出口: true 初始化成功  false 初始化失败
bit ringBuffer_init(ringBuffer_t *_in_ringBuf,unsigned char *_in_ptBuffer,unsigned short _in_size);
//++++++++++++++++++++++++++++++start+++++++++++++++++++++++++++++++++++++++++++
//Function
//名称: 清空环形队列
//功能: 将指定环形队列清空
//入口: *_in_ringBuf   输入队列地址 <<-------------------------传入
//出口: 无
void ringBuffer_flush(ringBuffer_t *_in_ringBuf);
//++++++++++++++++++++++++++++++start+++++++++++++++++++++++++++++++++++++++++++
//Function
//名称: 查询队列是否为空
//功能: 查询指定队列是否为空
//入口: *_in_ringBuf   输入队列地址 <<-------------------------传入
//出口: true 空  false 非空
bit ringBuffer_is_empty(ringBuffer_t *_in_ringBuf);
//++++++++++++++++++++++++++++++start+++++++++++++++++++++++++++++++++++++++++++
//Function
//名称: 查询队列长度
//功能: 查询指定队列有效数据的长度
//入口: *_in_ringBuf   输入队列地址 <<-------------------------传入
//出口: 队列里面有效数据的值
unsigned short ringBuffer_items_counter(ringBuffer_t *_in_ringBuf);
//++++++++++++++++++++++++++++++start+++++++++++++++++++++++++++++++++++++++++++
//Function
//名称: 写入指定大小的数据到队列中
//功能: 将指定大小数据写入到队列中
//入口: *_in_ringBuf   输入队列地址        <<-------------------------传入
//入口: *_in_buffer   输入缓冲区数据       <<-------------------------传入
//入口: _in_size      输入长度             <<-------------------------传入
//出口: true 设置成功  false 设置失败
unsigned short ringBuffer_write(ringBuffer_t *_in_ringBuf,unsigned char *_in_buffer,unsigned short _in_size);
//++++++++++++++++++++++++++++++start+++++++++++++++++++++++++++++++++++++++++++
//Function
//名称: 从队列中读出指定大小的数据
//功能: 从队列中读出指定大小数据 
//入口: *_in_ringBuf   输入队列地址           <<-------------------------传入
//入口: *_out_buffer   输入缓冲区数据         <<-------------------------传入
//入口: _in_size    输入长度                  <<-------------------------传入
//出口: 输入长度
unsigned short ringBuffer_read(ringBuffer_t *_in_ringBuf,unsigned char *_out_buffer,unsigned short _in_size);
bit memory_copy(void *_in_dest ,const void *_in_src ,unsigned short _in_size);
/*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */ 
 /*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */ 

#endif
/* EOF */
//-----------------------Pub_ringBuffer.h--END-----------------------------------