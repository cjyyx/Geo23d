#include "BackMiddlePoint.h"

#include <stdlib.h>
#include <math.h>

#include "Back.h"
#include "FrontMain2dShow.h"
#include <windows.h>
#include <winuser.h>
#include "graphics.h"
#include "extgraph.h"
#include "imgui.h"
#include "linkedlist.h"

#include "Front.h"

BACK_Geobj *BACK_MiddlePoint_Creat(long bid1, long bid2)
{
    BACK_MiddlePoint *p_mp = (BACK_MiddlePoint *)malloc(sizeof(BACK_MiddlePoint));
    p_mp->baseId1 = bid1;
    p_mp->baseId2 = bid2;

    BACK_Geobj *p_gb = BACK_Geobj_Creat();
    p_gb->en_class = MIDDLE_POINT_CLASS;
    p_gb->p_geobj = p_mp;

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

char *BACK_MiddlePoint_Info(BACK_Geobj *p_gb)
{
    if (p_gb->en_class != MIDDLE_POINT_CLASS)
    {
        Error("BACK_MiddlePoint_Info: Error type");
        return NULL;
    }

    BACK_MiddlePoint *p_mp = (BACK_MiddlePoint *)(p_gb->p_geobj);
    char *info = (char *)malloc(sizeof(char) * 100);
    sprintf(info,
            "%s_%ld_%s  %ld*%ld",
            A_CLASS_NAME[MIDDLE_POINT_CLASS],
            p_gb->id,
            p_gb->name,
            p_mp->baseId1,
            p_mp->baseId2);

    return info;
}

void BACK_MiddlePoint_Draw(BACK_Geobj *p_gb)
{
    if (p_gb->en_class != MIDDLE_POINT_CLASS)
    {
        Error("BACK_MiddlePoint_Draw: Error type");
        return;
    }
    BACK_GeobjList *p_gbl = BACK_GetGeobjList();
    BACK_MiddlePoint *p_mp = (BACK_MiddlePoint *)(p_gb->p_geobj);
    BACK_Geobj *p_gbb1 = BACK_GeobjList_Visit(p_gbl, p_mp->baseId1);
    BACK_Geobj *p_gbb2 = BACK_GeobjList_Visit(p_gbl, p_mp->baseId2);
    BACK_OrdinaryPoint *p_op1 = (BACK_OrdinaryPoint *)(p_gbb1->p_geobj);
    BACK_OrdinaryPoint *p_op2 = (BACK_OrdinaryPoint *)(p_gbb2->p_geobj);

    double vx[2], vy[2];
    FRONT_Main2dShow_GetVisualRange(vx, vy);

    double rx, ry;
    rx = (p_op1->x + p_op2->x) / 2;
    ry = (p_op1->y + p_op2->y) / 2;

    SetPenColor("Violet");
    FRONT_Main2dShow_DrawPoint(rx, ry, 15);

    SetPenColor("Black");
    SetPointSize(1);
    FRONT_Main2dShow_DrawText(rx, ry, p_gb->name);
}

void BACK_MiddlePoint_DetectOperation()
{
    double mouseImX, mouseImY;
    FRONT_Main2dShow_GetMouseIm(&mouseImX, &mouseImY);

    BACK_GeobjList *p_gbl = BACK_GetGeobjList();

    BACK_Geobj **An_selectedGeobj =
        FRONT_Main2dShow_GetAnSelectedGeobj();

    if (FRONT_Main2dShow_GetCurShowInterfaceState() == CLICK_STATE)
    {
        if (FRONT_Main2dShow_GetSelectedGeobjThisFrame() != NULL)
        {
            FRONT_Main2dShow_AnSelectedGeobj_Enter(
                FRONT_Main2dShow_GetSelectedGeobjThisFrame());
        }
    }
    if (An_selectedGeobj[1] != NULL)
    {
        BACK_Geobj *p_gb = BACK_MiddlePoint_Creat(
            An_selectedGeobj[0]->id,
            An_selectedGeobj[1]->id);
        BACK_GeobjList_Append(p_gbl, p_gb);

        if (FRONT_CONSOLE_LOG_MODE)
        {
            printf("creat: %s\n", BACK_Geobj_Info(p_gb));
        }

        FRONT_Main2dShow_AnSelectedGeobj_Clear();
    }
}

char *BACK_MiddlePoint_Seed(BACK_Geobj *p_gb)
{
    if (p_gb->en_class != MIDDLE_POINT_CLASS)
    {
        Error("BACK_MiddlePoint_Seed: Error type");
        return;
    }
    char *str_seed = (char *)malloc(sizeof(char) * MAX_LINE);
    BACK_MiddlePoint *p_mp = (BACK_MiddlePoint *)(p_gb->p_geobj);

    sprintf(str_seed,
            "%d %ld %s %ld %ld",
            p_gb->en_class,
            p_gb->id,
            p_gb->name,
            p_mp->baseId1,
            p_mp->baseId2);

    return str_seed;
}

BACK_Geobj *BACK_MiddlePoint_Relife(char *str_seed)
{
    BACK_Geobj *p_gb = (BACK_Geobj *)malloc(sizeof(BACK_Geobj));
    BACK_MiddlePoint *p_mp = (BACK_MiddlePoint *)malloc(sizeof(BACK_MiddlePoint));
    p_gb->p_geobj = p_mp;
    p_gb->name = (char *)malloc(sizeof(char) * 10);

    sscanf(str_seed,
           "%d %ld %s %ld %ld",
           &(p_gb->en_class),
           &(p_gb->id),
           (p_gb->name),
           &(p_mp->baseId1),
           &(p_mp->baseId2));
    return p_gb;
}