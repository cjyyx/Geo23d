#include "BackOrdinaryPoint.h"

#include <stdlib.h>

#include "Back.h"
#include "FrontMain2dShow.h"
#include <windows.h>
#include <winuser.h>
#include "graphics.h"
#include "extgraph.h"
#include "imgui.h"
#include "linkedlist.h"
#include "Front.h"

BACK_Geobj *BACK_OrdinaryPoint_Creat(double x, double y)
{
    BACK_OrdinaryPoint *p_op = (BACK_OrdinaryPoint *)malloc(sizeof(BACK_OrdinaryPoint));
    p_op->x = x;
    p_op->y = y;
    BACK_Geobj *p_gb = BACK_Geobj_Creat();
    p_gb->en_class = ORDINARY_POINT_CLASS;
    p_gb->p_geobj = p_op;
    char *p_name = (char *)malloc(sizeof(char) * 10);
    strcpy(p_name, "");

    long t = p_gb->id;

    /* 根据id生成name */
    int count = 0;
    do
    {
        char tac[2];
        tac[0] = 'A' + (t % 26);
        tac[1] = '\0';
        strcat(p_name, tac);
        count++;

        t /= 26;
    } while (t != 0);

    /* name倒序 */
    for (int i = 0; i < (count / 2); i++)
    {
        char t;
        t = p_name[i];
        p_name[i] = p_name[count - i - 1];
        p_name[count - i - 1] = t;
    }

    p_gb->name = p_name;

    return p_gb;
}
char *BACK_OrdinaryPoint_Info(BACK_Geobj *p_gb)
{
    if (p_gb->en_class != ORDINARY_POINT_CLASS)
    {
        Error("BACK_OrdinaryPoint_Info: Error type");
        return NULL;
    }

    char *info = (char *)malloc(sizeof(char) * 100);
    BACK_OrdinaryPoint *p_op = (BACK_OrdinaryPoint *)(p_gb->p_geobj);
    sprintf(info,
            "%s_%ld_%s  (%.2lf,%.2lf)",
            A_CLASS_NAME[ORDINARY_POINT_CLASS],
            p_gb->id,
            p_gb->name,
            p_op->x,
            p_op->y);

    return info;
}
int BACK_OrdinaryPoint_Selected(
    BACK_Geobj *p_gb,
    double mx, double my)
{
    if (p_gb->en_class != ORDINARY_POINT_CLASS)
    {
        Error("BACK_OrdinaryPoint_Selected: Error type");
        return NULL;
    }

    double coordExpansion2DX, coordExpansion2DY;
    FRONT_Main2dShow_GetCooedExpansion(&coordExpansion2DX, &coordExpansion2DY);

    double px = ((BACK_OrdinaryPoint *)(p_gb->p_geobj))->x;
    double py = ((BACK_OrdinaryPoint *)(p_gb->p_geobj))->y;
    // printf("%lf\n",((coordExpansion2DX * coordExpansion2DX) * ((mx - px) * (mx - px) + (my - py) * (my - py))));
    if (
        ((coordExpansion2DX * coordExpansion2DX) * ((mx - px) * (mx - px) + (my - py) * (my - py))) < 0.011)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
void BACK_OrdinaryPoint_Draw(BACK_Geobj *p_gb)
{
    if (p_gb->en_class != ORDINARY_POINT_CLASS)
    {
        printf("error at BACK_OrdinaryPoint_Draw\n");
        printf("p_gb->id: %ld\n", p_gb->id);
        printf("p_gb->en_class: %d\n", p_gb->en_class);
        Error("BACK_OrdinaryPoint_Draw: Error type");
        return NULL;
    }

    double x, y;
    x = ((BACK_OrdinaryPoint *)(p_gb->p_geobj))->x;
    y = ((BACK_OrdinaryPoint *)(p_gb->p_geobj))->y;

    double visualCoord2DRangeX[2], visualCoord2DRangeY[2];
    FRONT_Main2dShow_GetVisualRange(visualCoord2DRangeX, visualCoord2DRangeY);

    /* 能看到才画 */
    if (
        (x > visualCoord2DRangeX[0]) &&
        (x < visualCoord2DRangeX[1]) &&
        (y > visualCoord2DRangeY[0]) &&
        (y < visualCoord2DRangeY[1]))
    {
        SetPenColor("Violet");
        FRONT_Main2dShow_DrawPoint(x, y, 15);

        SetPenColor("Black");
        SetPointSize(1);
        FRONT_Main2dShow_DrawText(x, y, p_gb->name);
    }
}

void BACK_OrdinaryPoint_DetectOperation()
{
    double mouseImX, mouseImY;
    FRONT_Main2dShow_GetMouseIm(&mouseImX, &mouseImY);
    BACK_GeobjList *p_gbl = BACK_GetGeobjList();

    if (FRONT_Main2dShow_GetCurShowInterfaceState() == CLICK_STATE)
    {
        /* 创建新的OrdinaryPoint */

        BACK_Geobj *p_gb = BACK_OrdinaryPoint_Creat(mouseImX, mouseImY);

        BACK_GeobjList_Append(p_gbl, p_gb);

        if (FRONT_CONSOLE_LOG_MODE)
        {
            printf("creat: %s\n", BACK_Geobj_Info(p_gb));
            // printf("GeobjList:\n%s",BACK_GeobjList_Info(p_gbl));
        }
        /* 不需要选中任何对象 */
        FRONT_Main2dShow_AnSelectedGeobj_Clear();
    }
}

char *BACK_OrdinaryPoint_Seed(BACK_Geobj *p_gb)
{
    if (p_gb->en_class != ORDINARY_POINT_CLASS)
    {
        Error("BACK_OrdinaryPoint_Seed: Error type");
        return NULL;
    }

    char *str_seed = (char *)malloc(sizeof(char) * MAX_LINE);
    BACK_OrdinaryPoint *p_op = (BACK_OrdinaryPoint *)(p_gb->p_geobj);

    sprintf(str_seed,
            "%d %ld %s %lf %lf",
            p_gb->en_class,
            p_gb->id,
            p_gb->name,
            p_op->x,
            p_op->y);

    return str_seed;
}

BACK_Geobj *BACK_OrdinaryPoint_Relife(char *str_seed)
{
    BACK_Geobj *p_gb = (BACK_Geobj *)malloc(sizeof(BACK_Geobj));
    BACK_OrdinaryPoint *p_op = (BACK_OrdinaryPoint *)malloc(sizeof(BACK_OrdinaryPoint));
    p_gb->p_geobj = p_op;
    p_gb->name = (char *)malloc(sizeof(char) * 10);

    sscanf(str_seed,
           "%d %ld %s %lf %lf",
           &(p_gb->en_class),
           &(p_gb->id),
           (p_gb->name),
           &(p_op->x),
           &(p_op->y));
    return p_gb;
}
