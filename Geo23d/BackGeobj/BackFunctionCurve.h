#ifndef BACK_FUNCTION_CURVE_H
#define BACK_FUNCTION_CURVE_H

#include "BackGeobj.h"
#include "Evic.h"

/* 采样点数 */
#define SAMPLING_POINT_SIZE 100

/* 曲线宽度 */
#define FUNCTION_CURVE_SIZE 3

/* 几何对象FunctionCurve */
typedef struct
{
    char strExpr[MAX_EXPR_LEN];
    double x;
    EVIC_expr *ec_expr;
} BACK_FunctionCurve;

/* 创建几何对象FunctionCurve，存储在块中,
如果strExpr错误，返回NULL */
BACK_Geobj *BACK_FunctionCurve_Creat(char *strExpr);
/* 返回几何对象FunctionCurve信息，info存储在块中 */
char *BACK_FunctionCurve_Info(BACK_Geobj *p_gb);
/* 绘制几何对象FunctionCurve */
void BACK_FunctionCurve_Draw(BACK_Geobj *p_gb);
/* BACK_FunctionCurve_DetectOperation */
void BACK_FunctionCurve_DetectOperation();

/* 把FunctionCurve保存在str中，str存储在块中 */
char *BACK_FunctionCurve_Seed(BACK_Geobj *p_gb);
/* 从str_seed中提取FunctionCurve并返回，FunctionCurve存储在块中
失败返回NULL */
BACK_Geobj *BACK_FunctionCurve_Relife(char *str_seed);

#endif