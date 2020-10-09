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
#include "Pub_softTimer.h"
/*============================ MACROS ========================================*/
/*============================ MACROFIED FUNCTIONS ===========================*/
/*============================ TYPES =========================================*/
/*============================ GLOBAL VARIABLES ==============================*/
/*============================ LOCAL VARIABLES ===============================*/
/*============================ PROTOTYPES ====================================*/
/*============================ IMPLEMENTATION ================================*/
void Pub_softTimer_run_event(timeOutEvent_t *_in_delay_event,unsigned short _in_tick)
{
    if(_in_delay_event->lastTick != _in_tick)
    {
        _in_delay_event->lastTick  = _in_tick;
        if(_in_delay_event->delayTime > 0)
        {
            _in_delay_event->delayTime--;
            if(_in_delay_event->delayTime == 0)
            {
                _in_delay_event->flag = 1;
            }
        }
    }
}
void Pub_softTimer_set_event(timeOutEvent_t *_in_delay_event,unsigned short delayTime)
{
     _in_delay_event->flag = 0;
     _in_delay_event->delayTime = delayTime;
}
bit Pub_softTimer_get_event(timeOutEvent_t *_in_delay_event,unsigned short _in_tick)
{
    Pub_softTimer_run_event(_in_delay_event,_in_tick);
    if(_in_delay_event->flag)
    {
        return 1;
    }
    return 0;
}
bit Pub_softTimer_get_event_and_clear(timeOutEvent_t *_in_delay_event,unsigned short _in_tick)
{
    Pub_softTimer_run_event(_in_delay_event,_in_tick);
    if(_in_delay_event->flag)
    {
        _in_delay_event->flag = 0;
        return 1;
    }
    return 0;
}
void Pub_softTimer_clear_event(timeOutEvent_t *_in_delay_event)
{
    _in_delay_event->flag = 0;
    _in_delay_event->delayTime  = 0;
}
bit Pub_softTimer_get_timeOut(timeOutEvent_t *_in_delay_event,unsigned short _in_tick)
{
    Pub_softTimer_run_event(_in_delay_event,_in_tick);
    if(_in_delay_event->delayTime == 0)
    {
        return 1;
    }
    return 0;
}
/* EOF */
