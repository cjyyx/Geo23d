#ifndef BACK_CENTER_AND_POINT_CIRCLE_H
#define BACK_CENTER_AND_POINT_CIRCLE_H
#include "BackGeobj.h"

/* 几何对象CenterAndPointCircle */
typedef struct
{
    /* center 圆心,radiusId 圆上一点 */
    long centerId,radiusId;
} BACK_CenterAndPointCircle;

/* 创建几何对象CenterAndPointCircle，存储在块中 */
BACK_Geobj *BACK_CenterAndPointCircle_Creat(long cid, long rid);
/* 返回几何对象CenterAndPointCircle信息，info存储在块中 */
char *BACK_CenterAndPointCircle_Info(BACK_Geobj *p_gb);
/* 绘制几何对象CenterAndPointCircle */
void BACK_CenterAndPointCircle_Draw(BACK_Geobj *p_gb);
/* BACK_CenterAndPointCircle_DetectOperation */
void BACK_CenterAndPointCircle_DetectOperation();

/* 把CenterAndPointCircle保存在str中，str存储在块中 */
char *BACK_CenterAndPointCircle_Seed(BACK_Geobj *p_gb);
/* 从str_seed中提取CenterAndPointCircle并返回，CenterAndPointCircle存储在块中
失败返回NULL */
BACK_Geobj *BACK_CenterAndPointCircle_Relife(char *str_seed);

#endif