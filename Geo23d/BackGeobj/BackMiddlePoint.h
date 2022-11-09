#ifndef BACK_MIDDLE_POINT_H
#define BACK_MIDDLE_POINT_H
#include "BackGeobj.h"

/* 几何对象MiddlePoint */
typedef struct
{
    long baseId1,baseId2;
} BACK_MiddlePoint;

/* 创建几何对象MiddlePoint，存储在块中 */
BACK_Geobj *BACK_MiddlePoint_Creat(long bid1, long bid2);
/* 返回几何对象MiddlePoint信息，info存储在块中 */
char *BACK_MiddlePoint_Info(BACK_Geobj *p_gb);
/* 绘制几何对象MiddlePoint */
void BACK_MiddlePoint_Draw(BACK_Geobj *p_gb);
/* BACK_MiddlePoint_DetectOperation */
void BACK_MiddlePoint_DetectOperation();

/* 把MiddlePoint保存在str中，str存储在块中 */
char *BACK_MiddlePoint_Seed(BACK_Geobj *p_gb);
/* 从str_seed中提取MiddlePoint并返回，MiddlePoint存储在块中
失败返回NULL */
BACK_Geobj *BACK_MiddlePoint_Relife(char *str_seed);

#endif