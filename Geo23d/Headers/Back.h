#ifndef BACK_H
#define BACK_H
#include "linkedlist.h"

#include <stdlib.h>
#include <strlib.h>
#include <Windows.h>
#include <string.h>

#include "BackGeobj.h"
#include "BackOrdinaryPoint.h"
#include "BackOrdinaryLine.h"
#include "BackOrdinaryPolygon.h"
#include "BackCenterAndPointCircle.h"
#include "BackMiddlePoint.h"
#include "BackLineSegment.h"
#include "BackRegularPolygon.h"
#include "BackThreePointCircle.h"
#include "BackFunctionCurve.h"
#include "BackEquationCurve.h"

#define DEBUG_FILE_PATH "D:/MyProject/C_Programming/Geo23d/build/debugFile.geo2"
#define MAX_LINE 1024

/* �������ζ���ͨ���࣬���ڿ��� */
BACK_Geobj *BACK_Geobj_Creat();
/* ���ؼ��ζ�����Ϣ,info���ڿ��У��ǵ�free */
char *BACK_Geobj_Info(BACK_Geobj *p_gb);
/* �ж�����Ƿ�ѡ�м��ζ���
- x,y������������ֵ
- ѡ��1,ûѡ��0 */
int BACK_Geobj_Selected(BACK_Geobj *p_gb, double mx, double my);
/* draw���ζ��� */
void BACK_Geobj_Draw(BACK_Geobj *p_gb);
/* �Ѽ��ζ��󱣴���str�У�str�洢�ڿ��� */
char *BACK_Geobj_Seed(BACK_Geobj *p_gb);
/* ��str_seed����ȡ���ζ��󲢷��أ����ζ���洢�ڿ���
ʧ�ܷ���NULL */
BACK_Geobj *BACK_Geobj_Relife(char *str_seed);

/* ���ζ������� */
typedef struct
{
    /* ��ͨ������洢���ζ��� */
    linkedlistADT list;
} BACK_GeobjList;

/* �����ռ��ζ�������,������ָ�� */
BACK_GeobjList *BACK_GeobjList_Creat();
/* �������ζ�������,������ָ�� */
BACK_GeobjList *BACK_GeobjList_Copy(BACK_GeobjList *p_geobjl);
/* ���ؼ��ζ�������ĳ��� */
int BACK_GeobjList_Len(BACK_GeobjList *p_geobjl);
/* ���ؼ��ζ���������Ϣ */
char *BACK_GeobjList_Info(BACK_GeobjList *p_geobjl);

/* �����ζ�����������³�Ա��ָ�� */
void BACK_GeobjList_Append(BACK_GeobjList *p_geobjl, BACK_Geobj *p_new_geobj);
/* ��չp_geobjl */
void BACK_GeobjList_Extend(BACK_GeobjList *p_geobjl, BACK_GeobjList *p_new_geobjl);

/* ����id��ȡ���ζ��������Ա */
BACK_Geobj *BACK_GeobjList_Visit(BACK_GeobjList *p_geobjl, long id);
/* ��ȡ��һ�����ζ��������Ա */
BACK_Geobj *BACK_GeobjList_First(BACK_GeobjList *p_geobjl);
/* ���þ�̬����������ȡ���ζ���
- first==1�����ã�������һλ��
- ����Ƕ��ʹ�� */
BACK_Geobj *BACK_GeobjList_Iterate(int first);
/* ��traversefunptrָ��ĺ����������ζ������� */
void BACK_GeobjList_Traverse(BACK_GeobjList *p_geobjl, void (*traversefunptr)(BACK_GeobjList *p_gb));

/* ���ó������л��ڵ��ļ�·�� */
void BACK_SetFilePath(char *path);
/* �Ѻ��״̬�������ַ����У����ڿ��У������ַ���ָ�룬�ǵ�free */
char *BACK_Seed();
/* ��·��Ϊpath���ļ�����ȡ���״̬����ʼ�����
ʧ�ܷ���0 */
int BACK_Relife(char *file_path);
/* �Ѻ��״̬�������ַ����У��ٰѸ��ַ������浽FilePath�ļ���
ʧ�ܷ���0 */
int BACK_Save();

/* ��˳�ʼ��
- file_path:��������ʱ���ڵ��ļ�
- is_new:�Ƿ񴴽��µ��ļ�
ʧ�ܷ���0 */
int BACK_Init(char *file_path, int is_new);

/* ��ȡ��ǰGeobjList */
BACK_GeobjList *BACK_GetGeobjList();

#endif