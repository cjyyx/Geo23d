#ifndef BACK_ORDINARY_POLYGON_H
#define BACK_ORDINARY_POLYGON_H
#include "BackGeobj.h"

#define ORDINARY_POLYGON_MAX_LEN 10

/* ���ζ���OrdinaryPolygon */
typedef struct
{
    long *anBaseId[ORDINARY_POLYGON_MAX_LEN];
    int len;
} BACK_OrdinaryPolygon;

/* �������ζ���OrdinaryPolygon��OrdinaryPolygon�洢�ڿ��� */
BACK_Geobj *BACK_OrdinaryPolygon_Creat(long *anBaseId, int len);
/* ���ؼ��ζ���OrdinaryPolygon��Ϣ��info�洢�ڿ��� */
char *BACK_OrdinaryPolygon_Info(BACK_Geobj *p_gb);
/* ���Ƽ��ζ���OrdinaryPolygon */
void BACK_OrdinaryPolygon_Draw(BACK_Geobj *p_gb);
/* BACK_OrdinaryPolygon_DetectOperation */
void BACK_OrdinaryPolygon_DetectOperation();

/* ��OrdinaryPolygon������str�У�str�洢�ڿ��� */
char *BACK_OrdinaryPolygon_Seed(BACK_Geobj *p_gb);
/* ��str_seed����ȡOrdinaryPolygon�����أ�OrdinaryPolygon�洢�ڿ���
ʧ�ܷ���NULL */
BACK_Geobj *BACK_OrdinaryPolygon_Relife(char *str_seed);

#endif