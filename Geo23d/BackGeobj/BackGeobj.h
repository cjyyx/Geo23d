#ifndef BACK_GEOBJ_H
#define BACK_GEOBJ_H

#define PI 3.1415926535898
#define LIM_ZERO 0.000000000001
#define MAX_EXPR_LEN 128


/* ���ζ��������� */
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

/* ���ζ������������� */
extern const char *A_CLASS_NAME[];

/* ���ζ���ͨ���� */
typedef struct
{
    /* ���ζ������ */
    int en_class;
    /* ���ζ���ID */
    long id;
    /* name */
    char *name;
    /* ָ��ļ��ζ��� */
    void *p_geobj;
} BACK_Geobj;

#endif