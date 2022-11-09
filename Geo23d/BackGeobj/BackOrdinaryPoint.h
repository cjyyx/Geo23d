#ifndef BACK_ORDINARY_POINT_H
#define BACK_ORDINARY_POINT_H
#include "BackGeobj.h"

/* 几何对象OrdinaryPoint */
typedef struct
{
    double x, y;
} BACK_OrdinaryPoint;

/* 创建几何对象OrdinaryPoint，存储在块中
- x,y是虚拟坐标轴值 */
BACK_Geobj *BACK_OrdinaryPoint_Creat(double x, double y);
/* 判断鼠标是否选中几何对象OrdinaryPoint
- x,y是虚拟坐标轴值
- 选中1,没选中0 */
int BACK_OrdinaryPoint_Selected(
    BACK_Geobj *p_gb,
    double mx,
    double my);
/* 返回几何对象OrdinaryPoint信息，info存储在块中 */
char *BACK_OrdinaryPoint_Info(BACK_Geobj *p_gb);
/* 绘制几何对象OrdinaryPoint */
void BACK_OrdinaryPoint_Draw(BACK_Geobj *p_gb);
/* BACK_OrdinaryPoint_DetectOperation */
void BACK_OrdinaryPoint_DetectOperation();

/* 把OrdinaryPoint保存在str中，str存储在块中 */
char *BACK_OrdinaryPoint_Seed(BACK_Geobj *p_gb);
/* 从str中提取OrdinaryPoint并返回，OrdinaryPoint存储在块中
失败返回NULL */
BACK_Geobj *BACK_OrdinaryPoint_Relife(char *str_seed);

#endif