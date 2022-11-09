#ifndef BACK_EQUATION_CURVE_H
#define BACK_EQUATION_CURVE_H

#include "BackGeobj.h"
#include "Evic.h"

/* �������� */
#define FIRST_SCAN_SIZE 20
#define SECOND_SCAN_SIZE 10

/* ���߿�� */
#define EQUATION_CURVE_SIZE 3

/* ���ζ���EquationCurve */
typedef struct
{
    char strExpr[MAX_EXPR_LEN];
    double x, y;
    EVIC_expr *ec_expr;
} BACK_EquationCurve;

/* �������ζ���EquationCurve���洢�ڿ���,
���strExpr���󣬷���NULL */
BACK_Geobj *BACK_EquationCurve_Creat(char *strExpr);
/* ���ؼ��ζ���EquationCurve��Ϣ��info�洢�ڿ��� */
char *BACK_EquationCurve_Info(BACK_Geobj *p_gb);
/* ���Ƽ��ζ���EquationCurve */
void BACK_EquationCurve_Draw(BACK_Geobj *p_gb);
/* BACK_EquationCurve_DetectOperation */
void BACK_EquationCurve_DetectOperation();

/* ��EquationCurve������str�У�str�洢�ڿ��� */
char *BACK_EquationCurve_Seed(BACK_Geobj *p_gb);
/* ��str_seed����ȡEquationCurve�����أ�EquationCurve�洢�ڿ���
ʧ�ܷ���NULL */
BACK_Geobj *BACK_EquationCurve_Relife(char *str_seed);

#endif