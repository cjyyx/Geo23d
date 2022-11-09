#include "BackRegularPolygon.h"

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
#include "FrontMain2d.h"

BACK_Geobj *BACK_RegularPolygon_Creat(long bid1, long bid2, int edgesCount)
{
    BACK_RegularPolygon *p_rp = (BACK_RegularPolygon *)malloc(sizeof(BACK_RegularPolygon));
    p_rp->baseId1 = bid1;
    p_rp->baseId2 = bid2;
    p_rp->edgesCount = edgesCount;

    BACK_Geobj *p_gb = BACK_Geobj_Creat();
    p_gb->en_class = REGULAR_POLYGON_CLASS;
    p_gb->p_geobj = p_rp;

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

char *BACK_RegularPolygon_Info(BACK_Geobj *p_gb)
{
    if (p_gb->en_class != REGULAR_POLYGON_CLASS)
    {
        Error("BACK_RegularPolygon_Info: Error type");
        return NULL;
    }

    BACK_RegularPolygon *p_rp = (BACK_RegularPolygon *)(p_gb->p_geobj);
    char *info = (char *)malloc(sizeof(char) * 100);
    sprintf(info,
            "%s_%ld_%s  %ld*%ld/%d",
            A_CLASS_NAME[REGULAR_POLYGON_CLASS],
            p_gb->id,
            p_gb->name,
            p_rp->baseId1,
            p_rp->baseId2,
            p_rp->edgesCount);

    return info;
}

void BACK_RegularPolygon_Draw(BACK_Geobj *p_gb)
{
    if (p_gb->en_class != REGULAR_POLYGON_CLASS)
    {
        Error("BACK_RegularPolygon_Draw: Error type");
        return;
    }
    BACK_GeobjList *p_gbl = BACK_GetGeobjList();
    BACK_RegularPolygon *p_rp = (BACK_RegularPolygon *)(p_gb->p_geobj);
    BACK_Geobj *p_gbb1 = BACK_GeobjList_Visit(p_gbl, p_rp->baseId1);
    BACK_Geobj *p_gbb2 = BACK_GeobjList_Visit(p_gbl, p_rp->baseId2);
    BACK_OrdinaryPoint *p_op1 = (BACK_OrdinaryPoint *)(p_gbb1->p_geobj);
    BACK_OrdinaryPoint *p_op2 = (BACK_OrdinaryPoint *)(p_gbb2->p_geobj);

    double x0, y0, T[2][2], A[2][2], B[2][2], C[2], dAngle, D, t1x_0, t1y_0, t2x_0, t2y_0, t1, t2;

    dAngle = 2 * PI / (p_rp->edgesCount);

    T[0][0] = cos(dAngle);
    T[0][1] = -sin(dAngle);
    T[1][0] = sin(dAngle);
    T[1][1] = cos(dAngle);

    A[0][0] = T[0][0] - 1;
    A[0][1] = T[0][1];
    A[1][0] = T[1][0];
    A[1][1] = T[1][1] - 1;

    D = A[0][0] * A[1][1] - A[1][0] * A[0][1];

    if (fabs(D) < 0.000000001)
    {
        return;
    }

    B[0][0] = A[1][1] / D;
    B[0][1] = -A[0][1] / D;
    B[1][0] = -A[1][0] / D;
    B[1][1] = A[0][0] / D;

    C[0] = (p_op1->x) * cos(dAngle) - (p_op1->y) * sin(dAngle) - p_op2->x;
    C[1] = (p_op1->x) * sin(dAngle) + (p_op1->y) * cos(dAngle) - p_op2->y;

    x0 = B[0][0] * C[0] + B[0][1] * C[1];
    y0 = B[1][0] * C[0] + B[1][1] * C[1];

    t1x_0 = (p_op1->x) - x0;
    t1y_0 = (p_op1->y) - y0;
    t2x_0 = (p_op2->x) - x0;
    t2y_0 = (p_op2->y) - y0;

    for (int i = 0; i < p_rp->edgesCount; i++)
    {
        SetPenColor("Blue");
        SetPenSize(3);
        FRONT_Main2dShow_DrawLine(t1x_0 + x0, t1y_0 + y0, t2x_0 + x0, t2y_0 + y0);

        t1 = t1x_0 = t2x_0;
        t2 = t1y_0 = t2y_0;

        t2x_0 = T[0][0] * t1 + T[0][1] * t2;
        t2y_0 = T[1][0] * t1 + T[1][1] * t2;
    }

    BACK_Geobj_Draw(p_gbb1);
    BACK_Geobj_Draw(p_gbb2);
}

void BACK_RegularPolygon_DetectOperation()
{
    static int is_query = 0;
    static int is_selectPoint = 0;
    static int edgesCount;

    if ((!is_query) && (!is_selectPoint))
    {
        is_query = 1;
        while (1)
        {
            char *inp = FRONT_Input("Please enter the number of polygon edges: ");
            sscanf(inp, "%d", &edgesCount);

            if (!(edgesCount >= 3))
            {
                FRONT_Alart("illegal edges! or illegal input!");
            }
            else
            {
                break;
            }
        }
        is_selectPoint = 1;
        is_query = 0;
    }
    else if (is_selectPoint && (!is_query))
    {
        if (FRONT_Main2dShow_GetCurShowInterfaceState() == CLICK_STATE)
        {
            if (FRONT_Main2dShow_GetSelectedGeobjThisFrame() != NULL)
            {
                FRONT_Main2dShow_AnSelectedGeobj_Enter(
                    FRONT_Main2dShow_GetSelectedGeobjThisFrame());
            }
        }

        BACK_Geobj **An_selectedGeobj =
            FRONT_Main2dShow_GetAnSelectedGeobj();
        if (An_selectedGeobj[1] != NULL)
        {
            FRONT_Main2d_CurTool = MOVE_TOOL;
            if (!is_selectPoint)
            {
                return;
            }
            is_selectPoint = 0;

            BACK_GeobjList *p_gbl = BACK_GetGeobjList();
            BACK_Geobj *p_gb = BACK_RegularPolygon_Creat(
                An_selectedGeobj[0]->id,
                An_selectedGeobj[1]->id,
                edgesCount);
            BACK_GeobjList_Append(p_gbl, p_gb);

            if (FRONT_CONSOLE_LOG_MODE)
            {
                printf("creat: %s\n", BACK_Geobj_Info(p_gb));
            }

            FRONT_Main2dShow_AnSelectedGeobj_Clear();
        }
    }
}

char *BACK_RegularPolygon_Seed(BACK_Geobj *p_gb)
{
    if (p_gb->en_class != REGULAR_POLYGON_CLASS)
    {
        Error("BACK_RegularPolygon_Seed: Error type");
        return;
    }

    char *str_seed = (char *)malloc(sizeof(char) * MAX_LINE);
    BACK_RegularPolygon *p_rp = (BACK_RegularPolygon *)(p_gb->p_geobj);

    sprintf(str_seed,
            "%d %ld %s %ld %ld %d",
            p_gb->en_class,
            p_gb->id,
            p_gb->name,
            p_rp->baseId1,
            p_rp->baseId2,
            p_rp->edgesCount);

    return str_seed;
}

BACK_Geobj *BACK_RegularPolygon_Relife(char *str_seed)
{
    BACK_Geobj *p_gb = (BACK_Geobj *)malloc(sizeof(BACK_Geobj));
    BACK_RegularPolygon *p_rp = (BACK_RegularPolygon *)malloc(sizeof(BACK_RegularPolygon));
    p_gb->p_geobj = p_rp;
    p_gb->name = (char *)malloc(sizeof(char) * 10);

    sscanf(str_seed,
           "%d %ld %s %ld %ld %d",
           &(p_gb->en_class),
           &(p_gb->id),
           (p_gb->name),
           &(p_rp->baseId1),
           &(p_rp->baseId2),
           &(p_rp->edgesCount));
    return p_gb;
}