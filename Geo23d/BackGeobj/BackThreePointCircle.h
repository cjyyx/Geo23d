#ifndef BACK_THREE_POINT_CIRCLE_H
#define BACK_THREE_POINT_CIRCLE_H
#include "BackGeobj.h"

/* 几何对象ThreePointCircle */
typedef struct
{
    long baseId1, baseId2, baseId3;
} BACK_ThreePointCircle;

/* 创建几何对象ThreePointCircle，存储在块中 */
BACK_Geobj *BACK_ThreePointCircle_Creat(long bid1, long bid2, long bid3);
/* 返回几何对象ThreePointCircle信息，info存储在块中 */
char *BACK_ThreePointCircle_Info(BACK_Geobj *p_gb);
/* 绘制几何对象ThreePointCircle */
void BACK_ThreePointCircle_Draw(BACK_Geobj *p_gb);
/* BACK_ThreePointCircle_DetectOperation */
void BACK_ThreePointCircle_DetectOperation();

/* 把ThreePointCircle保存在str中，str存储在块中 */
char *BACK_ThreePointCircle_Seed(BACK_Geobj *p_gb);
/* 从str_seed中提取ThreePointCircle并返回，ThreePointCircle存储在块中
失败返回NULL */
BACK_Geobj *BACK_ThreePointCircle_Relife(char *str_seed);

#endif