#ifndef BACK_FUNCTION_CURVE_H
#define BACK_FUNCTION_CURVE_H

#include "BackGeobj.h"
#include "Evic.h"

/* �������� */
#define SAMPLING_POINT_SIZE 100

/* ���߿�� */
#define FUNCTION_CURVE_SIZE 3

/* ���ζ���FunctionCurve */
typedef struct
{
    char strExpr[MAX_EXPR_LEN];
    double x;
    EVIC_expr *ec_expr;
} BACK_FunctionCurve;

/* �������ζ���FunctionCurve���洢�ڿ���,
���strExpr���󣬷���NULL */
BACK_Geobj *BACK_FunctionCurve_Creat(char *strExpr);
/* ���ؼ��ζ���FunctionCurve��Ϣ��info�洢�ڿ��� */
char *BACK_FunctionCurve_Info(BACK_Geobj *p_gb);
/* ���Ƽ��ζ���FunctionCurve */
void BACK_FunctionCurve_Draw(BACK_Geobj *p_gb);
/* BACK_FunctionCurve_DetectOperation */
void BACK_FunctionCurve_DetectOperation();

/* ��FunctionCurve������str�У�str�洢�ڿ��� */
char *BACK_FunctionCurve_Seed(BACK_Geobj *p_gb);
/* ��str_seed����ȡFunctionCurve�����أ�FunctionCurve�洢�ڿ���
ʧ�ܷ���NULL */
BACK_Geobj *BACK_FunctionCurve_Relife(char *str_seed);

#endif