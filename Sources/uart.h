/******************************************************************************
�� �� ��   : uart.h
�� �� ��   : V1.0
��    ��   : pinot
��������   : 2020��04��13��
��������   : UART2345���ڶ�д
�޸���ʷ   :
��    ��   :
��    ��   :
�޸�����   :
******************************************************************************/

#ifndef _UART_H_
#define _UART_H_

/*****************************************************************************
ϵͳ��*/

/*****************************************************************************
�Զ���ͷ�ļ�*/
#include "sys.h"


/*****************************************************************************
�궨�����*/
#define UART2_MAX_LEN 2048
extern uint16_t uart2_rx_count;
extern uint8_t xdata Uart2_Rx[UART2_MAX_LEN];

#define UART3_MAX_LEN 128
extern uint16_t uart3_rx_count;
extern uint8_t xdata Uart3_Rx[UART3_MAX_LEN];

#define UART4_MAX_LEN 128
extern uint16_t uart4_rx_count;
extern uint8_t xdata Uart4_Rx[UART4_MAX_LEN];

#define UART5_MAX_LEN 128
extern uint16_t uart5_rx_count;
extern uint8_t xdata Uart5_Rx[UART5_MAX_LEN];

extern u8 delayTime;

/*****************************************************************************
���⺯������*/
void InitUart(void);
uint8_t Uart5SendByte(uint8_t dat);

void Uart2Init(void);
void Uart2SendByte(uint8_t dat);
void Uart2SendStr(uint8_t *pstr,uint8_t strlen);
void Uart3Init(void);
void Uart3SendByte(uint8_t dat);
void Uart3SendStr(uint8_t *pstr,uint8_t strlen);

void Uart4Init(void);
void Uart4SendByte(uint8_t dat);
void Uart4SendStr(uint8_t *pstr,uint8_t strlen);
void Uart5Init(void);
void Uart5Init(void);
void Uart5SendStr(uint8_t *pstr,uint8_t strlen);


void bsp_uart5_into_receive(void);
void bsp_uart5_into_transmit(void);


#endif
