#ifndef BACK_ORDINARY_POINT_H
#define BACK_ORDINARY_POINT_H
#include "BackGeobj.h"

/* ���ζ���OrdinaryPoint */
typedef struct
{
    double x, y;
} BACK_OrdinaryPoint;

/* �������ζ���OrdinaryPoint���洢�ڿ���
- x,y������������ֵ */
BACK_Geobj *BACK_OrdinaryPoint_Creat(double x, double y);
/* �ж�����Ƿ�ѡ�м��ζ���OrdinaryPoint
- x,y������������ֵ
- ѡ��1,ûѡ��0 */
int BACK_OrdinaryPoint_Selected(
    BACK_Geobj *p_gb,
    double mx,
    double my);
/* ���ؼ��ζ���OrdinaryPoint��Ϣ��info�洢�ڿ��� */
char *BACK_OrdinaryPoint_Info(BACK_Geobj *p_gb);
/* ���Ƽ��ζ���OrdinaryPoint */
void BACK_OrdinaryPoint_Draw(BACK_Geobj *p_gb);
/* BACK_OrdinaryPoint_DetectOperation */
void BACK_OrdinaryPoint_DetectOperation();

/* ��OrdinaryPoint������str�У�str�洢�ڿ��� */
char *BACK_OrdinaryPoint_Seed(BACK_Geobj *p_gb);
/* ��str����ȡOrdinaryPoint�����أ�OrdinaryPoint�洢�ڿ���
ʧ�ܷ���NULL */
BACK_Geobj *BACK_OrdinaryPoint_Relife(char *str_seed);

#endif