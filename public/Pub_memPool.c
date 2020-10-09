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
#include ".\Pub_memPool.h"
/*============================ MACROS ========================================*/
#define MP_NULL             0
/*============================ MACROFIED FUNCTIONS ===========================*/
/*============================ TYPES =========================================*/ 
/*============================ GLOBAL VARIABLES ==============================*/

/*============================ LOCAL VARIABLES ===============================*/ 
/*============================ PROTOTYPES ====================================*/
/*============================ IMPLEMENTATION ================================*/
bit MP_memPool_init(MP_mem_pool_t *me,MP_mem_object_t*ptBuff,unsigned short poolSize)
{
    unsigned short i=0;
    
    if((MP_NULL==me)||(MP_NULL==ptBuff)||(MP_NULL==poolSize))
    {
        return 0;
    }
    me->ptObject = ptBuff;
    me->size = poolSize;
    me->head = MP_NULL;
    me->tail = MP_NULL;
    for(i=0; i<me->size; i++)
    {
        me->ptObject->busyFlag = 0;
        me->ptObject->frameLength = 0;
    }
    return 1;
}

MP_mem_object_t* MP_memPool_new(MP_mem_pool_t *me)
{
  
    MP_mem_object_t *ptMem=MP_NULL;   
    
    if(MP_NULL==me)
    {
        return MP_NULL;
    }
    ptMem = &(me->ptObject[me->head]);
    ptMem->busyFlag = 1;
    if(me->head == (unsigned char)0)
    {
        me->head = me->size;
    }
    --me->head;
    return ptMem;
}

MP_mem_object_t* MP_memPool_peek(MP_mem_pool_t *me)
{
    
    MP_mem_object_t *ptMem=MP_NULL;   
    unsigned short i = 0;
    
   
    if(MP_NULL==me)
    {
        return MP_NULL;
    }
    for(i=0;i<me->size;i++){
        ptMem = &(me->ptObject[me->tail]);
        if(ptMem->busyFlag)
        { 
            return ptMem;
        }   
        if(me->tail == (unsigned char)0)
        {
            me->tail = me->size;
        }
        --me->tail;
    }
    return MP_NULL;
}
 

bit MP_memPool_free(MP_mem_object_t*item)
{
    if(MP_NULL==item)
    {
        return 0;
    }
    item->busyFlag = 0;
    item->frameLength = 0;
    return 1;
}

bit Memory_memCopy(void *dest ,const void *src ,unsigned short size){
    if((dest==0)||(src==0)){
        return 0;
    }
    while(size--){
        *(unsigned char *)dest = *(unsigned char *)src;
        dest = (unsigned char *)dest+1;
        src = (unsigned char *)src+1;
    }
    return 1;
}
/* EOF */
