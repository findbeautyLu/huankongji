/******************************************************************************
* �� �� ��   : dgus.c
* �� �� ��   : V1.0
* ��    ��   : pinot
* ��������   : 2020��04��13��
* ��������   : ��дDGUS�����洢��
* �޸���ʷ   :
* ��    ��   :
* ��    ��   :
* �޸�����   :
******************************************************************************/

/*****************************************************************************
�Զ���ͷ�ļ�*/
#include "dgus.h"

/*****************************************************************************
��DGUS�Ĵ���*/
/*****************************************************************************
 �� �� ��  : ReadDGUS
 ��������  : ��DGUS�Ĵ���
 �������  : uint16_t Addr  DGUS�Ĵ�����ַ
             uint8_t* pBuf  ���ջ�����
             uint16_t Len   ��ȡ�����ֽڳ���(�ȸ����ٵ���)
 �������  : ��
 �޸���ʷ  :
 ��    ��  : 2019��11��04��
 ��    ��  :
 �޸�����  : ����
*****************************************************************************/
void ReadDGUS(uint16_t Addr, uint8_t *pBuf, uint16_t Len)
{
  uint8_t Aoffset;
  if(NULL == pBuf){return;}
  if(0 == Len){return;}
  if((Addr+Len/2) > (0xFFFF*2)){return;}
  EA = 0;
  Aoffset = Addr&0x01;                 /*ȡbit0��Ϊ��ż�ж�*/
  Addr  = Addr >> 1;                   /*���õ�ַ*/
  ADR_H = (uint8_t)(Addr >> 16);
  ADR_M = (uint8_t)(Addr >> 8);
  ADR_L = (uint8_t)(Addr);
  RAMMODE = 0x00;
  ADR_INC = 0x01;
  APP_REQ = 1;                         /*ռ��DGUS��д*/
  while(!APP_ACK);
  APP_RW  = 1;                         /*�������洢��*/

  if(1 == Aoffset)
  {                    /*��ַΪ����*/
    if(1 == Len){ APP_DATA3=0,APP_DATA2=0,APP_DATA1=1,APP_DATA0=0;}
    else{         APP_DATA3=0,APP_DATA2=0,APP_DATA1=1,APP_DATA0=1;}
    APP_EN  = 1;
    while(APP_EN);
    if(1 == Len){ *pBuf++=DATA1;Len=Len-1; }
    else{         *pBuf++=DATA1;*pBuf++=DATA0;Len=Len-2;}
  }
  while(1)             /*��ַΪż��*/
  {
    if(0 == Len) break;
    if(Len < 4)
    {
      switch(Len)
      {
        case 3: APP_DATA3=1,APP_DATA2=1,APP_DATA1=1,APP_DATA0=0;break;
        case 2: APP_DATA3=1,APP_DATA2=1,APP_DATA1=0,APP_DATA0=0;break;
        case 1: APP_DATA3=1,APP_DATA2=0,APP_DATA1=0,APP_DATA0=0;break;
      }
      APP_EN  = 1;
      while(APP_EN);
      switch(Len)
      {
        case 3: *pBuf++=DATA3;*pBuf++=DATA2;*pBuf++=DATA1;break;
        case 2: *pBuf++=DATA3;*pBuf++=DATA2;break;
        case 1: *pBuf++=DATA3;break;
      }
      break;
      }
    else
    {
      APP_DATA3=1,APP_DATA2=1,APP_DATA1=1,APP_DATA0=1;
      APP_EN  = 1;
      while(APP_EN);
      *pBuf++=DATA3;*pBuf++=DATA2;*pBuf++=DATA1;*pBuf++=DATA0;
      Len = Len - 4;
    }
  }

  RAMMODE = 0x00;                      /*��ռ��ʱ��������*/
  EA = 1;
}

/*****************************************************************************
дDGUS�Ĵ���*/
/*****************************************************************************
 �� �� ��  : WriteDGUS
 ��������  : ��DGUS�Ĵ���
 �������  : uint16_t Addr  DGUS�Ĵ�����ַ
             uint8_t* pBuf  ���ջ�����
             uint16_t Len   д�������ֽڳ���(�ȸ����ٵ���)
 �������  : ��
 �޸���ʷ  :
 ��    ��  : 2019��11��04��
 ��    ��  :
 �޸�����  : ����
*****************************************************************************/
void WriteDGUS(uint16_t Addr, uint8_t *pBuf, uint16_t Len)
{
  uint8_t Aoffset;
  if(NULL == pBuf){return;}
  if(0 == Len){return;}
  if((Addr+Len/2) > (0xFFFF*2)){return;}
  EA = 0;
  Aoffset = Addr&0x01;                 /*ȡbit0��Ϊ��ż�ж�*/
  Addr  = Addr >> 1;                   /*���õ�ַ*/
  ADR_H = (uint8_t)(Addr >> 16);
  ADR_M = (uint8_t)(Addr >> 8);
  ADR_L = (uint8_t)(Addr);
  RAMMODE = 0x00;
  ADR_INC = 0x01;
  APP_REQ = 1;                         /*ռ��DGUS��д*/
  while(!APP_ACK);
  APP_RW  = 0;                         /*д�����洢��*/

  if(1 == Aoffset)
  {                    /*��ַΪ����*/
    if(1 == Len){ APP_DATA3=0,APP_DATA2=0,APP_DATA1=1,APP_DATA0=0;}
    else{         APP_DATA3=0,APP_DATA2=0,APP_DATA1=1,APP_DATA0=1;}
    if(1 == Len){ DATA1=*pBuf++;Len=Len-1; }
    else{         DATA1=*pBuf++;DATA0=*pBuf++;Len=Len-2;}
    APP_EN  = 1;
    while(APP_EN);
  }
  while(1)             /*��ַΪż��*/
  {
    if(0 == Len) break;
    if(Len < 4)
    {
      switch(Len)
      {
        case 3: APP_DATA3=1,APP_DATA2=1,APP_DATA1=1,APP_DATA0=0;break;
        case 2: APP_DATA3=1,APP_DATA2=1,APP_DATA1=0,APP_DATA0=0;break;
        case 1: APP_DATA3=1,APP_DATA2=0,APP_DATA1=0,APP_DATA0=0;break;
      }
      switch(Len)
      {
        case 3: DATA3=*pBuf++;DATA2=*pBuf++;DATA1=*pBuf++;break;
        case 2: DATA3=*pBuf++;DATA2=*pBuf++;break;
        case 1: DATA3=*pBuf++;break;
      }
      APP_EN  = 1;
      while(APP_EN);
      break;
    }
    else
    {
      APP_DATA3=1,APP_DATA2=1,APP_DATA1=1,APP_DATA0=1;
      DATA3=*pBuf++;DATA2=*pBuf++;DATA1=*pBuf++;DATA0=*pBuf++;
      APP_EN  = 1;
      while(APP_EN);
      Len = Len - 4;
    }
  }

  RAMMODE = 0x00;                      /*��ռ��ʱ��������*/
  EA = 1;
}
