#ifndef BACK_ORDINARY_POLYGON_H
#define BACK_ORDINARY_POLYGON_H
#include "BackGeobj.h"

#define ORDINARY_POLYGON_MAX_LEN 10

/* 几何对象OrdinaryPolygon */
typedef struct
{
    long *anBaseId[ORDINARY_POLYGON_MAX_LEN];
    int len;
} BACK_OrdinaryPolygon;

/* 创建几何对象OrdinaryPolygon，OrdinaryPolygon存储在块中 */
BACK_Geobj *BACK_OrdinaryPolygon_Creat(long *anBaseId, int len);
/* 返回几何对象OrdinaryPolygon信息，info存储在块中 */
char *BACK_OrdinaryPolygon_Info(BACK_Geobj *p_gb);
/* 绘制几何对象OrdinaryPolygon */
void BACK_OrdinaryPolygon_Draw(BACK_Geobj *p_gb);
/* BACK_OrdinaryPolygon_DetectOperation */
void BACK_OrdinaryPolygon_DetectOperation();

/* 把OrdinaryPolygon保存在str中，str存储在块中 */
char *BACK_OrdinaryPolygon_Seed(BACK_Geobj *p_gb);
/* 从str_seed中提取OrdinaryPolygon并返回，OrdinaryPolygon存储在块中
失败返回NULL */
BACK_Geobj *BACK_OrdinaryPolygon_Relife(char *str_seed);

#endif