#ifndef FRONT_H
#define FRONT_H

#define APP_NAME "geo23d"

/* �Ƿ���debugģʽ���� */
#define FRONT_DEBUG_MODE 0
#define FRONT_CONSOLE_LOG_MODE 1
/* ������Ĵ�С */
#define MAIN_INTERFACE_WIDTH 14.0
#define MAIN_INTERFACE_HEIGHT 10.0

#include "FrontInput.h"
#include "FrontFile.h"

/* ����ID */
enum
{
    DEFAULT_INTERFACE,
    START_INTERFACE,
    MAIN_INTERFACE_2D,
    INPUT_INTERFACE
};

/* ǰ�˳�ʼ�� */
void FRONT_Init();
/* ������������ */
void FRONT_Display();
/* ������ʾ���� */
void FRONT_SetInterface(int interfaceId);
/* ǰ����Ϣ */
void FRONT_Info(char *infoBuf);

/* ������text��˵������ */
void FRONT_Alart(char *text);


/* ��¼�Ƿ�����갴�µ�״̬ */
extern int FRONT_buttonDownState;
/* ��¼display���� */
extern long FRONT_frameCount;
/* get mouseReX, mouseReY */
void FRONT_GetMouseReVal(double *mx_re, double *my_re);

#endif