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
*         Data:2016.9.26
*         Official release
****************************************************************************/

#ifndef __MP_MEM_POOL_H__
#define __MP_MEM_POOL_H__

/*============================ INCLUDES ======================================*/ 
//#include <stdbool.h> 
//#include <stdint.h>
/*============================ MACROS ========================================*/ 
/*============================ MACROFIED FUNCTIONS ===========================*/
/*============================ TYPES =========================================*/
typedef struct{
    unsigned char          buffer[20];
    unsigned char          frameLength;
    unsigned char          channel;
    unsigned char          busyFlag;
}MP_mem_object_t; 

typedef struct{ 
    unsigned char           head;
    unsigned char           tail;
    unsigned short          size;
    MP_mem_object_t  *ptObject;
}MP_mem_pool_t;   
/*============================ GLOBAL VARIABLES ==============================*/
/*============================ LOCAL VARIABLES ===============================*/
/*============================ PROTOTYPES ====================================*/
bit MP_memPool_init(MP_mem_pool_t *me,MP_mem_object_t*ptBuff,unsigned short poolSize);
MP_mem_object_t* MP_memPool_new(MP_mem_pool_t *me);
MP_mem_object_t* MP_memPool_peek(MP_mem_pool_t *me);
bit MP_memPool_free(MP_mem_object_t*item);
bit Memory_memCopy(void *dest ,const void *src ,unsigned short size);
 /*! \note  
 *  \param  
 *  \retval  
 *  \retval  
 */ 

#endif
/* EOF */
