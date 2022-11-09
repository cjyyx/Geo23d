#ifndef BACK_ORDINARY_LINE_H
#define BACK_ORDINARY_LINE_H
#include "BackGeobj.h"

/* ���ζ���OrdinaryLine */
typedef struct
{
    long baseId1,baseId2;
} BACK_OrdinaryLine;

/* �������ζ���OrdinaryLine���洢�ڿ��� */
BACK_Geobj *BACK_OrdinaryLine_Creat(long bid1, long bid2);
/* ���ؼ��ζ���OrdinaryLine��Ϣ��info�洢�ڿ��� */
char *BACK_OrdinaryLine_Info(BACK_Geobj *p_gb);
/* ���Ƽ��ζ���OrdinaryLine */
void BACK_OrdinaryLine_Draw(BACK_Geobj *p_gb);
/* BACK_OrdinaryLine_DetectOperation */
void BACK_OrdinaryLine_DetectOperation();

/* ��OrdinaryLine������str�У�str�洢�ڿ��� */
char *BACK_OrdinaryLine_Seed(BACK_Geobj *p_gb);
/* ��str����ȡOrdinaryLine�����أ�OrdinaryLine�洢�ڿ���
ʧ�ܷ���NULL */
BACK_Geobj *BACK_OrdinaryLine_Relife(char *str_seed);

#endif