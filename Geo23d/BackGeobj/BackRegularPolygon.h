#ifndef BACK_REGULAR_POLYGON_H
#define BACK_REGULAR_POLYGON_H
#include "BackGeobj.h"

/* ���ζ���RegularPolygon */
typedef struct
{
    long baseId1, baseId2;
    int edgesCount;
} BACK_RegularPolygon;

/* �������ζ���RegularPolygon���洢�ڿ��� */
BACK_Geobj *BACK_RegularPolygon_Creat(long bid1, long bid2, int edgesCount);
/* ���ؼ��ζ���RegularPolygon��Ϣ��info�洢�ڿ��� */
char *BACK_RegularPolygon_Info(BACK_Geobj *p_gb);
/* ���Ƽ��ζ���RegularPolygon */
void BACK_RegularPolygon_Draw(BACK_Geobj *p_gb);
/* BACK_RegularPolygon_DetectOperation */
void BACK_RegularPolygon_DetectOperation();

/* ��RegularPolygon������str�У�str�洢�ڿ��� */
char *BACK_RegularPolygon_Seed(BACK_Geobj *p_gb);
/* ��str_seed����ȡRegularPolygon�����أ�RegularPolygon�洢�ڿ���
ʧ�ܷ���NULL */
BACK_Geobj *BACK_RegularPolygon_Relife(char *str_seed);

#endif