#include "Back.h"
#include "Front.h"

#include <stdlib.h>
#include <strlib.h>
#include <Windows.h>
#include <string.h>

#include "linkedlist.h"

/* 几何对象id基准 */
static long idBase;
/* 当前几何对象链表 */
static BACK_GeobjList *geobjList;
/* 程序运行时基于的路径 */
static char FilePath[MAX_PATH];

BACK_Geobj *BACK_Geobj_Creat()
{
    BACK_Geobj *p_gb = (BACK_Geobj *)malloc(sizeof(BACK_Geobj));
    p_gb->en_class = DEFAULR_CLASS;
    p_gb->id = idBase;
    idBase++;
    p_gb->p_geobj = NULL;
    p_gb->name = NULL;
    return p_gb;
}

BACK_GeobjList *BACK_GeobjList_Creat()
{
    BACK_GeobjList *p_gbl = (BACK_GeobjList *)malloc(sizeof(BACK_GeobjList));
    p_gbl->list = NewLinkedList();
    return p_gbl;
}

char *BACK_Geobj_Info(BACK_Geobj *p_gb)
{
    if (p_gb == NULL)
    {
        Error("BACK_Geobj_Info: geobj is null");
        return NULL;
    }

    char *info = NULL;

    switch (p_gb->en_class)
    {
    case ORDINARY_POINT_CLASS:
        info = (BACK_OrdinaryPoint_Info(p_gb));
        break;
    case ORDINARY_LINE_CLASS:
        info = (BACK_OrdinaryLine_Info(p_gb));
        break;
    case ORDINARY_POLYGON_CLASS:
        info = (BACK_OrdinaryPolygon_Info(p_gb));
        break;
    case CENTER_POINT_CIRCLE_CLASS:
        info = (BACK_CenterAndPointCircle_Info(p_gb));
        break;
    case MIDDLE_POINT_CLASS:
        info = BACK_MiddlePoint_Info(p_gb);
        break;
    case LINE_SEGMENT_CLASS:
        info = BACK_LineSegment_Info(p_gb);
        break;
    case REGULAR_POLYGON_CLASS:
        info = BACK_RegularPolygon_Info(p_gb);
        break;
    case THREE_POINT_CIRCLE_CLASS:
        info = BACK_ThreePointCircle_Info(p_gb);
        break;
    case FUNCTION_CURVE_CLASS:
        info = BACK_FunctionCurve_Info(p_gb);
        break;
    case EQUATION_CURVE_CLASS:
        info = BACK_EquationCurve_Info(p_gb);
        break;
    default:
        info = NULL;
        break;
    }

    if (info == NULL)
    {
        Error("BACK_Geobj_Info: info is null");
    }
    return info;
}
int BACK_Geobj_Selected(BACK_Geobj *p_gb, double mx, double my)
{
    if (p_gb == NULL)
    {
        Error("BACK_Geobj_Selected: geobj is null");
        return 0;
    }
    switch (p_gb->en_class)
    {
    case ORDINARY_POINT_CLASS:
        return BACK_OrdinaryPoint_Selected(p_gb, mx, my);
        break;
    default:
        return 0;
        break;
    }
}
void BACK_Geobj_Draw(BACK_Geobj *p_gb)
{
    if (p_gb == NULL)
    {
        Error("BACK_Geobj_Draw: geobj is null");
        return;
    }
    switch (p_gb->en_class)
    {
    case ORDINARY_POINT_CLASS:
        BACK_OrdinaryPoint_Draw(p_gb);
        break;
    case ORDINARY_LINE_CLASS:
        BACK_OrdinaryLine_Draw(p_gb);
        break;
    case ORDINARY_POLYGON_CLASS:
        BACK_OrdinaryPolygon_Draw(p_gb);
        break;
    case CENTER_POINT_CIRCLE_CLASS:
        BACK_CenterAndPointCircle_Draw(p_gb);
        break;
    case MIDDLE_POINT_CLASS:
        BACK_MiddlePoint_Draw(p_gb);
        break;
    case LINE_SEGMENT_CLASS:
        BACK_LineSegment_Draw(p_gb);
        break;
    case REGULAR_POLYGON_CLASS:
        BACK_RegularPolygon_Draw(p_gb);
        break;
    case THREE_POINT_CIRCLE_CLASS:
        BACK_ThreePointCircle_Draw(p_gb);
        break;
    case FUNCTION_CURVE_CLASS:
        BACK_FunctionCurve_Draw(p_gb);
        break;
    case EQUATION_CURVE_CLASS:
        BACK_EquationCurve_Draw(p_gb);
        break;
    default:
        break;
    }
}

char *BACK_Geobj_Seed(BACK_Geobj *p_gb)
{
    if (p_gb == NULL)
    {
        Error("BACK_Geobj_Seed: geobj is null");
        return 0;
    }
    switch (p_gb->en_class)
    {
    case ORDINARY_POINT_CLASS:
        return BACK_OrdinaryPoint_Seed(p_gb);
        break;
    case ORDINARY_LINE_CLASS:
        return BACK_OrdinaryLine_Seed(p_gb);
        break;
    case ORDINARY_POLYGON_CLASS:
        return BACK_OrdinaryPolygon_Seed(p_gb);
        break;
    case CENTER_POINT_CIRCLE_CLASS:
        return BACK_CenterAndPointCircle_Seed(p_gb);
        break;
    case MIDDLE_POINT_CLASS:
        return BACK_MiddlePoint_Seed(p_gb);
        break;
    case LINE_SEGMENT_CLASS:
        return BACK_LineSegment_Seed(p_gb);
        break;
    case REGULAR_POLYGON_CLASS:
        return BACK_RegularPolygon_Seed(p_gb);
        break;
    case THREE_POINT_CIRCLE_CLASS:
        return BACK_ThreePointCircle_Seed(p_gb);
        break;
    case FUNCTION_CURVE_CLASS:
        return BACK_FunctionCurve_Seed(p_gb);
        break;
    case EQUATION_CURVE_CLASS:
        BACK_EquationCurve_Seed(p_gb);
        break;
    default:
        return NULL;
        break;
    }
}
BACK_Geobj *BACK_Geobj_Relife(char *str_seed)
{
    int cid;
    sscanf(str_seed, "%d", &cid);
    switch (cid)
    {
    case ORDINARY_POINT_CLASS:
        return BACK_OrdinaryPoint_Relife(str_seed);
        break;
    case ORDINARY_LINE_CLASS:
        return BACK_OrdinaryLine_Relife(str_seed);
        break;
    case ORDINARY_POLYGON_CLASS:
        return BACK_OrdinaryPolygon_Relife(str_seed);
        break;
    case CENTER_POINT_CIRCLE_CLASS:
        return BACK_CenterAndPointCircle_Relife(str_seed);
        break;
    case MIDDLE_POINT_CLASS:
        return BACK_MiddlePoint_Relife(str_seed);
        break;
    case LINE_SEGMENT_CLASS:
        return BACK_LineSegment_Relife(str_seed);
        break;
    case REGULAR_POLYGON_CLASS:
        return BACK_RegularPolygon_Relife(str_seed);
        break;
    case THREE_POINT_CIRCLE_CLASS:
        return BACK_ThreePointCircle_Relife(str_seed);
        break;
    case FUNCTION_CURVE_CLASS:
        return BACK_FunctionCurve_Relife(str_seed);
        break;
    case EQUATION_CURVE_CLASS:
        BACK_EquationCurve_Relife(str_seed);
        break;
    default:
        return NULL;
        break;
    }
}

void BACK_GeobjList_Append(BACK_GeobjList *p_geobjl, BACK_Geobj *p_new_geobj)
{
    if (p_geobjl == NULL)
    {
        Error("BACK_GeobjList_Append: p_geobjl==NULL");
        return;
    }
    else
    {
        InsertNode(p_geobjl->list, NULL, p_new_geobj);
    }
}
BACK_Geobj *BACK_GeobjList_First(BACK_GeobjList *p_geobjl)
{
    if (p_geobjl == NULL)
    {
        Error("BACK_GeobjList_First: p_geobjl==NULL");
        return NULL;
    }

    return (BACK_Geobj *)(p_geobjl->list->dataptr);
}
void BACK_GeobjList_Traverse(BACK_GeobjList *p_geobjl, void (*traversefunptr)(BACK_GeobjList *p_gb))
{
    if (p_geobjl == NULL)
    {
        Error("BACK_GeobjList_Traverse: p_geobjl==NULL");
        return;
    }

    TraverseLinkedList(p_geobjl->list, traversefunptr);
}

int BACK_Init(char *file_path, int is_new)
{
    if (FRONT_DEBUG_MODE)
    {
        strcpy(FilePath, DEBUG_FILE_PATH);
        idBase = 0;
        geobjList = BACK_GeobjList_Creat();
        char *sseed = BACK_Seed(sseed);
        FILE *fp = NULL;
        fp = fopen(FilePath, "w");
        fprintf(fp, sseed);
        fclose(fp);
        free(sseed);
        return 1;
    }

    if (is_new)
    {
        /* 预处理文件名 */
        strcpy(FilePath, file_path);
        strcat(FilePath, ".geo2");
        /* 初始化后端相关参数 */
        idBase = 0;
        geobjList = BACK_GeobjList_Creat();
        /* 写入文件 */
        char *sseed = BACK_Seed(sseed);

        FILE *fp = NULL;
        fp = fopen(FilePath, "w");
        int result = fprintf(fp, sseed);
        fclose(fp);

        free(sseed);

        if (result < 0)
        {
            return 0;
        }
        else
        {
            return 1;
        }
    }
    else
    {
        return BACK_Relife(file_path);
    }
}
BACK_GeobjList *BACK_GetGeobjList()
{
    return geobjList;
}

BACK_Geobj *BACK_GeobjList_Visit(BACK_GeobjList *p_geobjl, long id)
{
    if (p_geobjl == NULL)
    {
        Error("BACK_GeobjList_Visit: p_geobjl==NULL");
        return NULL;
    }

    linkedlistADT nodeptr;

    nodeptr = p_geobjl->list->next;
    while (nodeptr != NULL)
    {
        BACK_Geobj *p_gb = (BACK_Geobj *)(nodeptr->dataptr);
        if (p_gb->id == id)
        {
            return p_gb;
        }
        nodeptr = nodeptr->next;
    }
    return NULL;
}

char *BACK_GeobjList_Info(BACK_GeobjList *p_geobjl)
{
    if (p_geobjl == NULL)
    {
        Error("BACK_GeobjList_Info: p_geobjl==NULL");
        return NULL;
    }

    char *info = (char *)malloc(sizeof(char) * 1000);
    sprintf(
        info,
        "len: %d\n",
        BACK_GeobjList_Len(p_geobjl));

    linkedlistADT nodeptr;

    nodeptr = p_geobjl->list->next;
    while (nodeptr != NULL)
    {
        BACK_Geobj *p_gb = (BACK_Geobj *)(nodeptr->dataptr);

        strcat(info, BACK_Geobj_Info(p_gb));
        strcat(info, "\n");

        nodeptr = nodeptr->next;
    }
    return info;
}
int BACK_GeobjList_Len(BACK_GeobjList *p_geobjl)
{
    if (p_geobjl == NULL)
    {
        Error("BACK_GeobjList_Len: p_geobjl==NULL");
        return NULL;
    }
    int count = 0;
    linkedlistADT nodeptr;
    nodeptr = p_geobjl->list->next;
    while (nodeptr != NULL)
    {
        count++;

        nodeptr = nodeptr->next;
    }
    return count;
}

char *BACK_Seed()
{
    char *str_seed =
        (char *)malloc(
            sizeof(char) * BACK_GeobjList_Len(geobjList) * MAX_LINE);
    str_seed[0] = '\0';

    sprintf(str_seed,
            "%ld\n",
            idBase);

    linkedlistADT nodeptr;
    nodeptr = geobjList->list->next;
    while (nodeptr != NULL)
    {
        strcat(str_seed,
               BACK_Geobj_Seed((BACK_Geobj *)(nodeptr->dataptr)));
        strcat(str_seed, "\n");
        nodeptr = nodeptr->next;
    }

    return str_seed;
}

void BACK_SetFilePath(char *path)
{
    strcpy(FilePath, path);
}

int BACK_Save()
{
    char *sseed = BACK_Seed(sseed);

    FILE *fp = fopen(FilePath, "w");
    int result = fprintf(fp, sseed);
    fclose(fp);

    free(sseed);

    if (result < 0)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

int BACK_Relife(char *file_path)
{
    strcpy(FilePath, file_path);

    FILE *fp = fopen(FilePath, "r");

    rewind(fp);

    fscanf(fp, "%ld\n", &idBase);
    if (FRONT_CONSOLE_LOG_MODE)
        printf("get idBase: %ld\n", idBase);

    char str_seed[MAX_LINE];
    geobjList = BACK_GeobjList_Creat();
    while (fgets(str_seed, MAX_LINE, fp) != NULL)
    {
        /* 确保一行一行读入，去换行符 */
        // fgetc(fp);
        if (FRONT_CONSOLE_LOG_MODE)
            printf("parse: %s", str_seed);

        BACK_Geobj *p_gb = BACK_Geobj_Relife(str_seed);
        if (p_gb == NULL)
        {
            FRONT_Alart("File Corruption");
            return 0;
        }

        if (FRONT_CONSOLE_LOG_MODE)
            printf(
                "get %s:%s\n",
                A_CLASS_NAME[p_gb->en_class],
                BACK_Geobj_Info(p_gb));

        BACK_GeobjList_Append(geobjList, p_gb);
    }

    fclose(fp);

    return 1;
}