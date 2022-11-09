#ifndef BACK_GEOBJ_H
#define BACK_GEOBJ_H

#define PI 3.1415926535898
#define LIM_ZERO 0.000000000001
#define MAX_EXPR_LEN 128


/* 几何对象类名称 */
enum
{
    DEFAULR_CLASS,
    ORDINARY_POINT_CLASS,
    MIDDLE_POINT_CLASS,
    ORDINARY_LINE_CLASS,
    LINE_SEGMENT_CLASS,
    ORDINARY_POLYGON_CLASS,
    REGULAR_POLYGON_CLASS,
    CENTER_POINT_CIRCLE_CLASS,
    THREE_POINT_CIRCLE_CLASS,
    FUNCTION_CURVE_CLASS,
    EQUATION_CURVE_CLASS
};

/* 几何对象类名称数组 */
extern const char *A_CLASS_NAME[];

/* 几何对象通用类 */
typedef struct
{
    /* 几何对象类别 */
    int en_class;
    /* 几何对象ID */
    long id;
    /* name */
    char *name;
    /* 指向的几何对象 */
    void *p_geobj;
} BACK_Geobj;

#endif