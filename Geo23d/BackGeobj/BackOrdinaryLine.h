#ifndef BACK_ORDINARY_LINE_H
#define BACK_ORDINARY_LINE_H
#include "BackGeobj.h"

/* 几何对象OrdinaryLine */
typedef struct
{
    long baseId1,baseId2;
} BACK_OrdinaryLine;

/* 创建几何对象OrdinaryLine，存储在块中 */
BACK_Geobj *BACK_OrdinaryLine_Creat(long bid1, long bid2);
/* 返回几何对象OrdinaryLine信息，info存储在块中 */
char *BACK_OrdinaryLine_Info(BACK_Geobj *p_gb);
/* 绘制几何对象OrdinaryLine */
void BACK_OrdinaryLine_Draw(BACK_Geobj *p_gb);
/* BACK_OrdinaryLine_DetectOperation */
void BACK_OrdinaryLine_DetectOperation();

/* 把OrdinaryLine保存在str中，str存储在块中 */
char *BACK_OrdinaryLine_Seed(BACK_Geobj *p_gb);
/* 从str中提取OrdinaryLine并返回，OrdinaryLine存储在块中
失败返回NULL */
BACK_Geobj *BACK_OrdinaryLine_Relife(char *str_seed);

#endif