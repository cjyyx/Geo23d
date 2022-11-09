#ifndef BACK_LINE_SEGMENT_H
#define BACK_LINE_SEGMENT_H
#include "BackGeobj.h"

/* 几何对象LineSegment */
typedef struct
{
    long baseId1,baseId2;
} BACK_LineSegment;

/* 创建几何对象LineSegment，存储在块中 */
BACK_Geobj *BACK_LineSegment_Creat(long bid1, long bid2);
/* 返回几何对象LineSegment信息，info存储在块中 */
char *BACK_LineSegment_Info(BACK_Geobj *p_gb);
/* 绘制几何对象LineSegment */
void BACK_LineSegment_Draw(BACK_Geobj *p_gb);
/* BACK_LineSegment_DetectOperation */
void BACK_LineSegment_DetectOperation();

/* 把LineSegment保存在str中，str存储在块中 */
char *BACK_LineSegment_Seed(BACK_Geobj *p_gb);
/* 从str_seed中提取LineSegment并返回，LineSegment存储在块中
失败返回NULL */
BACK_Geobj *BACK_LineSegment_Relife(char *str_seed);

#endif