#ifndef BACK_EQUATION_CURVE_H
#define BACK_EQUATION_CURVE_H

#include "BackGeobj.h"
#include "Evic.h"

/* 采样点数 */
#define FIRST_SCAN_SIZE 20
#define SECOND_SCAN_SIZE 10

/* 曲线宽度 */
#define EQUATION_CURVE_SIZE 3

/* 几何对象EquationCurve */
typedef struct
{
    char strExpr[MAX_EXPR_LEN];
    double x, y;
    EVIC_expr *ec_expr;
} BACK_EquationCurve;

/* 创建几何对象EquationCurve，存储在块中,
如果strExpr错误，返回NULL */
BACK_Geobj *BACK_EquationCurve_Creat(char *strExpr);
/* 返回几何对象EquationCurve信息，info存储在块中 */
char *BACK_EquationCurve_Info(BACK_Geobj *p_gb);
/* 绘制几何对象EquationCurve */
void BACK_EquationCurve_Draw(BACK_Geobj *p_gb);
/* BACK_EquationCurve_DetectOperation */
void BACK_EquationCurve_DetectOperation();

/* 把EquationCurve保存在str中，str存储在块中 */
char *BACK_EquationCurve_Seed(BACK_Geobj *p_gb);
/* 从str_seed中提取EquationCurve并返回，EquationCurve存储在块中
失败返回NULL */
BACK_Geobj *BACK_EquationCurve_Relife(char *str_seed);

#endif