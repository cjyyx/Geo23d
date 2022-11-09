#include "BackOrdinaryLine.h"

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

BACK_Geobj *BACK_OrdinaryLine_Creat(long bid1, long bid2)
{
    BACK_OrdinaryLine *p_ol = (BACK_OrdinaryLine *)malloc(sizeof(BACK_OrdinaryLine));
    p_ol->baseId1 = bid1;
    p_ol->baseId2 = bid2;

    BACK_Geobj *p_gb = BACK_Geobj_Creat();
    p_gb->en_class = ORDINARY_LINE_CLASS;
    p_gb->p_geobj = p_ol;

    char *p_name = (char *)malloc(sizeof(char) * 10);
    strcpy(p_name, "");

    long t = p_gb->id;

    /* 根据id生成name */
    int count = 0;
    do
    {
        char tac[2];
        tac[0] = 'a' + (t % 26);
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

char *BACK_OrdinaryLine_Info(BACK_Geobj *p_gb)
{
    if (p_gb->en_class != ORDINARY_LINE_CLASS)
    {
        Error("BACK_OrdinaryLine_Info: Error type");
        return NULL;
    }

    BACK_OrdinaryLine *p_ol = (BACK_OrdinaryLine *)(p_gb->p_geobj);
    char *info = (char *)malloc(sizeof(char) * 100);
    sprintf(info,
            "%s_%ld_%s  %ld*%ld",
            A_CLASS_NAME[ORDINARY_LINE_CLASS],
            p_gb->id,
            p_gb->name,
            p_ol->baseId1,
            p_ol->baseId2);

    return info;
}

void BACK_OrdinaryLine_Draw(BACK_Geobj *p_gb)
{
    if (p_gb->en_class != ORDINARY_LINE_CLASS)
    {
        Error("BACK_OrdinaryLine_Draw: Error type");
        return;
    }
    BACK_GeobjList *p_gbl = BACK_GetGeobjList();
    BACK_OrdinaryLine *p_ol = (BACK_OrdinaryLine *)(p_gb->p_geobj);
    BACK_Geobj *p_gbb1 = BACK_GeobjList_Visit(p_gbl, p_ol->baseId1);
    BACK_Geobj *p_gbb2 = BACK_GeobjList_Visit(p_gbl, p_ol->baseId2);
    BACK_OrdinaryPoint *p_op1 = (BACK_OrdinaryPoint *)(p_gbb1->p_geobj);
    BACK_OrdinaryPoint *p_op2 = (BACK_OrdinaryPoint *)(p_gbb2->p_geobj);

    double vx[2], vy[2];
    FRONT_Main2dShow_GetVisualRange(vx, vy);

    /* 替代0 */
    double lim0 = 0.0;

    /* 判断两点有没有重合 */
    if ((fabs(p_op1->x - p_op2->x) + fabs(p_op1->y - p_op2->y)) < lim0)
    {
        return;
    }

    SetPenColor("Blue");
    SetPenSize(3);

    /* 如果直线平行y轴 */
    if (fabs(p_op1->x - p_op2->x) < lim0)
    {
        if (
            (p_op1->x > vx[0]) &&
            (p_op1->x < vx[1]))
        {
            FRONT_Main2dShow_DrawLine(p_op1->x, vy[0], p_op2->x, vy[1]);
            BACK_Geobj_Draw(p_gbb1);
            BACK_Geobj_Draw(p_gbb2);
            return;
        }
    }

    /* 如果直线平行x轴 */
    if (fabs(p_op1->y - p_op2->y) < lim0)
    {
        if (
            (p_op1->y > vy[0]) &&
            (p_op1->y < vy[1]))
        {
            FRONT_Main2dShow_DrawLine(vx[0], p_op1->y, vx[1], p_op2->y);
            BACK_Geobj_Draw(p_gbb1);
            BACK_Geobj_Draw(p_gbb2);
            return;
        }
    }

    /* 下面是一般情况直线 */

    /* 求直线A,B,C */
    double A, B, C;
    A = p_op1->y - p_op2->y;
    B = -(p_op1->x - p_op2->x);
    C = p_op1->x * p_op2->y - p_op1->y * p_op2->x;

    /* 与画布边框的交点 */
    double vx0_y, vx1_y, vy0_x, vy1_x;
    vx0_y = -(A * vx[0] + C) / B;
    vx1_y = -(A * vx[1] + C) / B;
    vy0_x = -(B * vy[0] + C) / A;
    vy1_x = -(B * vy[1] + C) / A;

    if (
        (vx0_y > vy[1] && vx1_y > vy[1]) ||
        (vx0_y < vy[0] && vx1_y < vy[0]))
    {
        return;
    }
    else
    {
        FRONT_Main2dShow_DrawLine(vx[0], vx0_y, vx[1], vx1_y);
        BACK_Geobj_Draw(p_gbb1);
        BACK_Geobj_Draw(p_gbb2);
        return;
    }
    // }
    // else if (
    //     vx0_y > vy[0] &&
    //     vx0_y < vy[1] &&
    //     vx1_y > vy[0] &&
    //     vx1_y < vy[1])
    // {
    //     FRONT_Main2dShow_DrawLine(vx[0], vx0_y, vx[1], vx1_y);
    //     return;
    // }
    // else if (
    //     vx0_y > vy[0] &&
    //     vx0_y < vy[1] &&
    //     vx1_y > vy[1])
    // {
    //     FRONT_Main2dShow_DrawLine(vx[0], vx0_y, vy1_x, vy[1]);
    //     return;
    // }
    // else if (
    //     vx0_y > vy[0] &&
    //     vx0_y < vy[1] &&
    //     vx1_y < vy[0])
    // {
    //     FRONT_Main2dShow_DrawLine(vx[0], vx0_y, vy0_x, vy[0]);
    //     return;
    // }
    // else if (
    //     vx1_y > vy[0] &&
    //     vx1_y < vy[1] &&
    //     vx0_y > vy[1])
    // {
    //     FRONT_Main2dShow_DrawLine(vy1_x, vy[1], vx[1], vx1_y);
    //     return;
    // }
    // else if (
    //     vx1_y > vy[0] &&
    //     vx1_y < vy[1] &&
    //     vx0_y < vy[0])
    // {
    //     FRONT_Main2dShow_DrawLine(vy0_x, vy[0], vx[1], vx1_y);
    //     return;
    // }
}

void BACK_OrdinaryLine_DetectOperation()
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
        BACK_Geobj *p_gb = BACK_OrdinaryLine_Creat(
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

char *BACK_OrdinaryLine_Seed(BACK_Geobj *p_gb)
{
    if (p_gb->en_class != ORDINARY_LINE_CLASS)
    {
        Error("BACK_OrdinaryLine_Seed: Error type");
        return;
    }
    char *str_seed = (char *)malloc(sizeof(char) * MAX_LINE);
    BACK_OrdinaryLine *p_ol = (BACK_OrdinaryLine *)(p_gb->p_geobj);

    sprintf(str_seed,
            "%d %ld %s %ld %ld",
            p_gb->en_class,
            p_gb->id,
            p_gb->name,
            p_ol->baseId1,
            p_ol->baseId2);

    return str_seed;
}

BACK_Geobj *BACK_OrdinaryLine_Relife(char *str_seed)
{

    BACK_Geobj *p_gb = (BACK_Geobj *)malloc(sizeof(BACK_Geobj));
    BACK_OrdinaryLine *p_ol = (BACK_OrdinaryLine *)malloc(sizeof(BACK_OrdinaryLine));
    p_gb->p_geobj = p_ol;
    p_gb->name = (char *)malloc(sizeof(char) * 10);

    sscanf(str_seed,
           "%d %ld %s %ld %ld",
           &(p_gb->en_class),
           &(p_gb->id),
           (p_gb->name),
           &(p_ol->baseId1),
           &(p_ol->baseId2));
    return p_gb;
}