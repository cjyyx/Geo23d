#ifndef BACK_CENTER_AND_POINT_CIRCLE_H
#define BACK_CENTER_AND_POINT_CIRCLE_H
#include "BackGeobj.h"

/* ���ζ���CenterAndPointCircle */
typedef struct
{
    /* center Բ��,radiusId Բ��һ�� */
    long centerId,radiusId;
} BACK_CenterAndPointCircle;

/* �������ζ���CenterAndPointCircle���洢�ڿ��� */
BACK_Geobj *BACK_CenterAndPointCircle_Creat(long cid, long rid);
/* ���ؼ��ζ���CenterAndPointCircle��Ϣ��info�洢�ڿ��� */
char *BACK_CenterAndPointCircle_Info(BACK_Geobj *p_gb);
/* ���Ƽ��ζ���CenterAndPointCircle */
void BACK_CenterAndPointCircle_Draw(BACK_Geobj *p_gb);
/* BACK_CenterAndPointCircle_DetectOperation */
void BACK_CenterAndPointCircle_DetectOperation();

/* ��CenterAndPointCircle������str�У�str�洢�ڿ��� */
char *BACK_CenterAndPointCircle_Seed(BACK_Geobj *p_gb);
/* ��str_seed����ȡCenterAndPointCircle�����أ�CenterAndPointCircle�洢�ڿ���
ʧ�ܷ���NULL */
BACK_Geobj *BACK_CenterAndPointCircle_Relife(char *str_seed);

#endif