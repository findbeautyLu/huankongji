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
#include "Pub_ringBuffer.h"
/*============================ MACROS ========================================*/
/*============================ MACROFIED FUNCTIONS ===========================*/
#define  is_power_of_2(x) ((x) != 0 && (((x) & ((x) - 1)) == 0))
#define  get_min(a,b) 	  (((a)<(b))?(a):(b))
/*============================ TYPES =========================================*/

/*============================ GLOBAL VARIABLES ==============================*/
/*============================ LOCAL VARIABLES ===============================*/
/*============================ PROTOTYPES ====================================*/
/*============================ IMPLEMENTATION ================================*/

/*! \brief   
 *! \param  
 *! \retval  
 *! \retval  
 */
bit memory_set(void *_in_dest ,unsigned char _in_value ,unsigned short _in_size)
 {
    if(_in_dest==0)
    {
        return 0;
    }
    while(_in_size--)
    {
        *(unsigned char *)_in_dest = _in_value;
        _in_dest = (unsigned char *)_in_dest+1;
    }
    return 1;
}
bit memory_copy(void *_in_dest ,const void *_in_src ,unsigned short _in_size)
{
    if((_in_dest==0)||(_in_src==0))
    {
        return 0;
    }
    while(_in_size--)
    {
        *(unsigned char *)_in_dest = *(unsigned char *)_in_src;
        _in_dest = (unsigned char *)_in_dest+1;
        _in_src = (unsigned char *)_in_src+1;
    }
    return 1;
}
 

 /*! \brief   
 *! \param  
 *! \retval  
 *! \retval  
 */
 /*! \brief   
 *! \param  
 *! \retval  
 *! \retval  
 */

/* EOF */
//-----------------------Pub_ringBuffer.c--END-----------------------------------