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

#ifndef __SOFT_TIMER_H__
#define __SOFT_TIMER_H__

/*============================ INCLUDES ======================================*/

/*============================ MACROS ========================================*/
/*============================ MACROFIED FUNCTIONS ===========================*/
/*============================ TYPES =========================================*/
typedef struct{
                   unsigned char flag; 
                   unsigned short  delayTime; 
                   unsigned short  lastTick;
              }timeOutEvent_t; 
/*============================ GLOBAL VARIABLES ==============================*/
/*============================ LOCAL VARIABLES ===============================*/
/*============================ PROTOTYPES ====================================*/
//void Pub_softTimer_run_event(timeOutEvent_t *_in_delay_event,uint16_t _in_tick);
void Pub_softTimer_set_event(timeOutEvent_t *_in_delay_event,unsigned short delayTime);
bit Pub_softTimer_get_event(timeOutEvent_t *_in_delay_event,unsigned short _in_tick);
bit Pub_softTimer_get_event_and_clear(timeOutEvent_t *_in_delay_event,unsigned short _in_tick);
void Pub_softTimer_clear_event(timeOutEvent_t *_in_delay_event);
bit Pub_softTimer_get_timeOut(timeOutEvent_t *_in_delay_event,unsigned short _in_tick);
#endif
/* EOF */
