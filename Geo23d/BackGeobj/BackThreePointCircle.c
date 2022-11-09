#include "BackThreePointCircle.h"

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

#include "math.h"
#include "Front.h"

BACK_Geobj *BACK_ThreePointCircle_Creat(long bid1, long bid2, long bid3)
{
    BACK_ThreePointCircle *p_tpc = (BACK_ThreePointCircle *)malloc(sizeof(BACK_ThreePointCircle));
    p_tpc->baseId1 = bid1;
    p_tpc->baseId2 = bid2;
    p_tpc->baseId3 = bid3;

    BACK_Geobj *p_gb = BACK_Geobj_Creat();
    p_gb->en_class = THREE_POINT_CIRCLE_CLASS;
    p_gb->p_geobj = p_tpc;

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

char *BACK_ThreePointCircle_Info(BACK_Geobj *p_gb)
{
    if (p_gb->en_class != THREE_POINT_CIRCLE_CLASS)
    {
        Error("BACK_ThreePointCircle_Info: Error type");
        return NULL;
    }

    BACK_ThreePointCircle *p_tpc = (BACK_ThreePointCircle *)(p_gb->p_geobj);
    char *info = (char *)malloc(sizeof(char) * 100);
    sprintf(info,
            "%s_%ld_%s  %ld*%ld*%ld",
            A_CLASS_NAME[THREE_POINT_CIRCLE_CLASS],
            p_gb->id,
            p_gb->name,
            p_tpc->baseId1,
            p_tpc->baseId2,
            p_tpc->baseId3);

    return info;
}

void BACK_ThreePointCircle_Draw(BACK_Geobj *p_gb)
{
    if (p_gb->en_class != THREE_POINT_CIRCLE_CLASS)
    {
        Error("BACK_ThreePointCircle_Draw: Error type");
        return;
    }
    BACK_GeobjList *p_gbl = BACK_GetGeobjList();
    BACK_ThreePointCircle *p_tpc = (BACK_ThreePointCircle *)(p_gb->p_geobj);
    BACK_Geobj *p_gbb1 = BACK_GeobjList_Visit(p_gbl, p_tpc->baseId1);
    BACK_Geobj *p_gbb2 = BACK_GeobjList_Visit(p_gbl, p_tpc->baseId2);
    BACK_Geobj *p_gbb3 = BACK_GeobjList_Visit(p_gbl, p_tpc->baseId3);
    BACK_OrdinaryPoint *p_op1 = (BACK_OrdinaryPoint *)(p_gbb1->p_geobj);
    BACK_OrdinaryPoint *p_op2 = (BACK_OrdinaryPoint *)(p_gbb2->p_geobj);
    BACK_OrdinaryPoint *p_op3 = (BACK_OrdinaryPoint *)(p_gbb3->p_geobj);

    double x1, x2, x3, y1, y2, y3, x, y, r, A, B, C, D;

    x1 = p_op1->x;
    x2 = p_op2->x;
    x3 = p_op3->x;

    y1 = p_op1->y;
    y2 = p_op2->y;
    y3 = p_op3->y;

    A = x1 * (y2 - y3) - y1 * (x2 - x3) + x2 * y3 - x3 * y2;

    if (fabs(A) < LIM_ZERO)
    {
        return;
    }

    B = (x1 * x1 + y1 * y1) * (y3 - y2) + (x2 * x2 + y2 * y2) * (y1 - y3) + (x3 * x3 + y3 * y3) * (y2 - y1);
    C = (x1 * x1 + y1 * y1) * (x2 - x3) + (x2 * x2 + y2 * y2) * (x3 - x1) + (x3 * x3 + y3 * y3) * (x1 - x2);
    D = (x1 * x1 + y1 * y1) * (x3 * y2 - x2 * y3) + (x2 * x2 + y2 * y2) * (x1 * y3 - x3 * y1) + (x3 * x3 + y3 * y3) * (x2 * y1 - x1 * y2);

    x = -B / (2 * A);
    y = -C / (2 * A);
    r = sqrt((B * B + C * C - 4 * A * D) / (4 * A * A));

    SetPenColor("Blue");
    SetPenSize(3);
    FRONT_Main2dShow_DrawArc(x, y, r, 0, 360);

    BACK_OrdinaryPoint_Draw(p_gbb1);
    BACK_OrdinaryPoint_Draw(p_gbb2);
    BACK_OrdinaryPoint_Draw(p_gbb3);
}

void BACK_ThreePointCircle_DetectOperation()
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
    if (An_selectedGeobj[2] != NULL)
    {
        BACK_Geobj *p_gb = BACK_ThreePointCircle_Creat(
            An_selectedGeobj[0]->id,
            An_selectedGeobj[1]->id,
            An_selectedGeobj[2]->id);
        BACK_GeobjList_Append(p_gbl, p_gb);

        if (FRONT_CONSOLE_LOG_MODE)
        {
            printf("creat: %s\n", BACK_Geobj_Info(p_gb));
        }

        FRONT_Main2dShow_AnSelectedGeobj_Clear();
    }
}

char *BACK_ThreePointCircle_Seed(BACK_Geobj *p_gb)
{
    if (p_gb->en_class != THREE_POINT_CIRCLE_CLASS)
    {
        Error("BACK_ThreePointCircle_Seed: Error type");
        return;
    }
    char *str_seed = (char *)malloc(sizeof(char) * MAX_LINE);
    BACK_ThreePointCircle *p_tpc = (BACK_ThreePointCircle *)(p_gb->p_geobj);

    sprintf(str_seed,
            "%d %ld %s %ld %ld %ld",
            p_gb->en_class,
            p_gb->id,
            p_gb->name,
            p_tpc->baseId1,
            p_tpc->baseId2,
            p_tpc->baseId3);

    return str_seed;
}

BACK_Geobj *BACK_ThreePointCircle_Relife(char *str_seed)
{
    BACK_Geobj *p_gb = (BACK_Geobj *)malloc(sizeof(BACK_Geobj));
    BACK_ThreePointCircle *p_tpc = (BACK_ThreePointCircle *)malloc(sizeof(BACK_ThreePointCircle));
    p_gb->p_geobj = p_tpc;
    p_gb->name = (char *)malloc(sizeof(char) * 10);

    sscanf(str_seed,
           "%d %ld %s %ld %ld %ld",
           &(p_gb->en_class),
           &(p_gb->id),
           (p_gb->name),
           &(p_tpc->baseId1),
           &(p_tpc->baseId2),
           &(p_tpc->baseId3));
    return p_gb;
}