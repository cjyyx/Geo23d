#ifndef BACK_REGULAR_POLYGON_H
#define BACK_REGULAR_POLYGON_H
#include "BackGeobj.h"

/* 几何对象RegularPolygon */
typedef struct
{
    long baseId1, baseId2;
    int edgesCount;
} BACK_RegularPolygon;

/* 创建几何对象RegularPolygon，存储在块中 */
BACK_Geobj *BACK_RegularPolygon_Creat(long bid1, long bid2, int edgesCount);
/* 返回几何对象RegularPolygon信息，info存储在块中 */
char *BACK_RegularPolygon_Info(BACK_Geobj *p_gb);
/* 绘制几何对象RegularPolygon */
void BACK_RegularPolygon_Draw(BACK_Geobj *p_gb);
/* BACK_RegularPolygon_DetectOperation */
void BACK_RegularPolygon_DetectOperation();

/* 把RegularPolygon保存在str中，str存储在块中 */
char *BACK_RegularPolygon_Seed(BACK_Geobj *p_gb);
/* 从str_seed中提取RegularPolygon并返回，RegularPolygon存储在块中
失败返回NULL */
BACK_Geobj *BACK_RegularPolygon_Relife(char *str_seed);

#endif