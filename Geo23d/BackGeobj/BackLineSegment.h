#ifndef BACK_LINE_SEGMENT_H
#define BACK_LINE_SEGMENT_H
#include "BackGeobj.h"

/* ���ζ���LineSegment */
typedef struct
{
    long baseId1,baseId2;
} BACK_LineSegment;

/* �������ζ���LineSegment���洢�ڿ��� */
BACK_Geobj *BACK_LineSegment_Creat(long bid1, long bid2);
/* ���ؼ��ζ���LineSegment��Ϣ��info�洢�ڿ��� */
char *BACK_LineSegment_Info(BACK_Geobj *p_gb);
/* ���Ƽ��ζ���LineSegment */
void BACK_LineSegment_Draw(BACK_Geobj *p_gb);
/* BACK_LineSegment_DetectOperation */
void BACK_LineSegment_DetectOperation();

/* ��LineSegment������str�У�str�洢�ڿ��� */
char *BACK_LineSegment_Seed(BACK_Geobj *p_gb);
/* ��str_seed����ȡLineSegment�����أ�LineSegment�洢�ڿ���
ʧ�ܷ���NULL */
BACK_Geobj *BACK_LineSegment_Relife(char *str_seed);

#endif