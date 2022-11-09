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

/* 创建几何对象通用类，存在块中 */
BACK_Geobj *BACK_Geobj_Creat();
/* 返回几何对象信息,info存在块中，记得free */
char *BACK_Geobj_Info(BACK_Geobj *p_gb);
/* 判断鼠标是否选中几何对象
- x,y是虚拟坐标轴值
- 选中1,没选中0 */
int BACK_Geobj_Selected(BACK_Geobj *p_gb, double mx, double my);
/* draw几何对象 */
void BACK_Geobj_Draw(BACK_Geobj *p_gb);
/* 把几何对象保存在str中，str存储在块中 */
char *BACK_Geobj_Seed(BACK_Geobj *p_gb);
/* 从str_seed中提取几何对象并返回，几何对象存储在块中
失败返回NULL */
BACK_Geobj *BACK_Geobj_Relife(char *str_seed);

/* 几何对象链表 */
typedef struct
{
    /* 用通用链表存储几何对象 */
    linkedlistADT list;
} BACK_GeobjList;

/* 创建空几何对象链表,返回其指针 */
BACK_GeobjList *BACK_GeobjList_Creat();
/* 拷贝几何对象链表,返回其指针 */
BACK_GeobjList *BACK_GeobjList_Copy(BACK_GeobjList *p_geobjl);
/* 返回几何对象链表的长度 */
int BACK_GeobjList_Len(BACK_GeobjList *p_geobjl);
/* 返回几何对象链表信息 */
char *BACK_GeobjList_Info(BACK_GeobjList *p_geobjl);

/* 往几何对象链表加入新成员的指针 */
void BACK_GeobjList_Append(BACK_GeobjList *p_geobjl, BACK_Geobj *p_new_geobj);
/* 扩展p_geobjl */
void BACK_GeobjList_Extend(BACK_GeobjList *p_geobjl, BACK_GeobjList *p_new_geobjl);

/* 根据id获取几何对象链表成员 */
BACK_Geobj *BACK_GeobjList_Visit(BACK_GeobjList *p_geobjl, long id);
/* 获取第一个几何对象链表成员 */
BACK_Geobj *BACK_GeobjList_First(BACK_GeobjList *p_geobjl);
/* 利用静态变量迭代获取几何对象
- first==1，重置；否则下一位。
- 不能嵌套使用 */
BACK_Geobj *BACK_GeobjList_Iterate(int first);
/* 用traversefunptr指向的函数遍历几何对象链表 */
void BACK_GeobjList_Traverse(BACK_GeobjList *p_geobjl, void (*traversefunptr)(BACK_GeobjList *p_gb));

/* 设置程序运行基于的文件路径 */
void BACK_SetFilePath(char *path);
/* 把后端状态保存在字符串中，存在块中，返回字符串指针，记得free */
char *BACK_Seed();
/* 从路径为path的文件中提取后端状态并初始化后端
失败返回0 */
int BACK_Relife(char *file_path);
/* 把后端状态保存在字符串中，再把该字符串保存到FilePath文件中
失败返回0 */
int BACK_Save();

/* 后端初始化
- file_path:程序运行时基于的文件
- is_new:是否创建新的文件
失败返回0 */
int BACK_Init(char *file_path, int is_new);

/* 获取当前GeobjList */
BACK_GeobjList *BACK_GetGeobjList();

#endif