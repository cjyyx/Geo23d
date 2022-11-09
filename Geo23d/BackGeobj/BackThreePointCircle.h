#ifndef BACK_THREE_POINT_CIRCLE_H
#define BACK_THREE_POINT_CIRCLE_H
#include "BackGeobj.h"

/* ���ζ���ThreePointCircle */
typedef struct
{
    long baseId1, baseId2, baseId3;
} BACK_ThreePointCircle;

/* �������ζ���ThreePointCircle���洢�ڿ��� */
BACK_Geobj *BACK_ThreePointCircle_Creat(long bid1, long bid2, long bid3);
/* ���ؼ��ζ���ThreePointCircle��Ϣ��info�洢�ڿ��� */
char *BACK_ThreePointCircle_Info(BACK_Geobj *p_gb);
/* ���Ƽ��ζ���ThreePointCircle */
void BACK_ThreePointCircle_Draw(BACK_Geobj *p_gb);
/* BACK_ThreePointCircle_DetectOperation */
void BACK_ThreePointCircle_DetectOperation();

/* ��ThreePointCircle������str�У�str�洢�ڿ��� */
char *BACK_ThreePointCircle_Seed(BACK_Geobj *p_gb);
/* ��str_seed����ȡThreePointCircle�����أ�ThreePointCircle�洢�ڿ���
ʧ�ܷ���NULL */
BACK_Geobj *BACK_ThreePointCircle_Relife(char *str_seed);

#endif