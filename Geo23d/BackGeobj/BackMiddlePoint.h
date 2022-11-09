#ifndef BACK_MIDDLE_POINT_H
#define BACK_MIDDLE_POINT_H
#include "BackGeobj.h"

/* ���ζ���MiddlePoint */
typedef struct
{
    long baseId1,baseId2;
} BACK_MiddlePoint;

/* �������ζ���MiddlePoint���洢�ڿ��� */
BACK_Geobj *BACK_MiddlePoint_Creat(long bid1, long bid2);
/* ���ؼ��ζ���MiddlePoint��Ϣ��info�洢�ڿ��� */
char *BACK_MiddlePoint_Info(BACK_Geobj *p_gb);
/* ���Ƽ��ζ���MiddlePoint */
void BACK_MiddlePoint_Draw(BACK_Geobj *p_gb);
/* BACK_MiddlePoint_DetectOperation */
void BACK_MiddlePoint_DetectOperation();

/* ��MiddlePoint������str�У�str�洢�ڿ��� */
char *BACK_MiddlePoint_Seed(BACK_Geobj *p_gb);
/* ��str_seed����ȡMiddlePoint�����أ�MiddlePoint�洢�ڿ���
ʧ�ܷ���NULL */
BACK_Geobj *BACK_MiddlePoint_Relife(char *str_seed);

#endif