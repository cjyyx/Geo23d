#include "BackOrdinaryPolygon.h"

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
#include "FrontMain2d.h"

BACK_Geobj *BACK_OrdinaryPolygon_Creat(long *anBaseId, int len)
{
    if (len < 3)
    {
        Error("BACK_OrdinaryPolygon_Creat: too few len");
        return NULL;
    }

    BACK_OrdinaryPolygon *p_opo = (BACK_OrdinaryPolygon *)malloc(sizeof(BACK_OrdinaryPolygon));
    p_opo->len = len;

    for (int i = 0; i < p_opo->len; i++)
    {
        p_opo->anBaseId[i] = anBaseId[i];
    }

    BACK_Geobj *p_gb = BACK_Geobj_Creat();
    p_gb->en_class = ORDINARY_POLYGON_CLASS;
    p_gb->p_geobj = p_opo;

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
char *BACK_OrdinaryPolygon_Info(BACK_Geobj *p_gb)
{
    if (p_gb->en_class != ORDINARY_POLYGON_CLASS)
    {
        Error("BACK_OrdinaryPolygon_Info: Error type");
        return NULL;
    }

    // printf("start BACK_OrdinaryPolygon_Info\n");

    BACK_OrdinaryPolygon *p_opo = (BACK_OrdinaryPolygon *)(p_gb->p_geobj);
    char *info = (char *)malloc(sizeof(char) * 100);
    sprintf(info,
            "%s_%ld_%s  ",
            A_CLASS_NAME[ORDINARY_POLYGON_CLASS],
            p_gb->id,
            p_gb->name);

    // printf("info1: %s\n",info);

    char ts[10];
    sprintf(
        ts,
        "%ld",
        p_opo->anBaseId[0]);
    strcat(info, ts);

    for (int i = 1; i < p_opo->len; i++)
    {
        sprintf(
            ts,
            "*%ld",
            p_opo->anBaseId[i]);
        strcat(info, ts);
    }
    // printf("get info: %s\n",info);

    return info;
}
void BACK_OrdinaryPolygon_Draw(BACK_Geobj *p_gb)
{
    if (p_gb->en_class != ORDINARY_POLYGON_CLASS)
    {
        Error("BACK_OrdinaryPolygon_Info: Error type");
        return;
    }

    BACK_GeobjList *p_gbl = BACK_GetGeobjList();

    BACK_OrdinaryPolygon *p_opo = (BACK_OrdinaryPolygon *)(p_gb->p_geobj);

    BACK_Geobj *p_g_op0 = BACK_GeobjList_Visit(p_gbl, p_opo->anBaseId[0]);
    BACK_OrdinaryPoint *p_op0 = (BACK_OrdinaryPoint *)(p_g_op0->p_geobj);

    BACK_Geobj *p_g_op_cur = p_g_op0;
    BACK_OrdinaryPoint *p_op_cur = p_op0;

    BACK_Geobj *tp_g_op;
    BACK_OrdinaryPoint *tp_op;

    for (int i = 1; i < p_opo->len; i++)
    {
        tp_g_op = BACK_GeobjList_Visit(p_gbl, p_opo->anBaseId[i]);
        tp_op = (BACK_OrdinaryPoint *)(tp_g_op->p_geobj);

        SetPenColor("Blue");
        SetPenSize(3);
        FRONT_Main2dShow_DrawLine(p_op_cur->x, p_op_cur->y, tp_op->x, tp_op->y);
        BACK_Geobj_Draw(p_g_op_cur);

        p_g_op_cur = tp_g_op;
        p_op_cur = tp_op;
    }
    SetPenColor("Blue");
    SetPenSize(3);
    FRONT_Main2dShow_DrawLine(p_op_cur->x, p_op_cur->y, p_op0->x, p_op0->y);

    BACK_Geobj_Draw(p_g_op_cur);
    BACK_Geobj_Draw(p_g_op0);
}

void BACK_OrdinaryPolygon_DetectOperation()
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

            if (!(edgesCount >= 3 && edgesCount <= 10))
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
        if (An_selectedGeobj[edgesCount - 1] != NULL)
        {
            FRONT_Main2d_CurTool = MOVE_TOOL;
            if (!is_selectPoint)
            {
                return;
            }
            is_selectPoint = 0;

            long anBaseId[ORDINARY_POLYGON_MAX_LEN];
            for (int i = 0; i < edgesCount; i++)
            {
                anBaseId[i] = An_selectedGeobj[i]->id;
            }

            BACK_GeobjList *p_gbl = BACK_GetGeobjList();
            BACK_Geobj *p_gb = BACK_OrdinaryPolygon_Creat(anBaseId, edgesCount);
            // printf("creat success\n");
            BACK_GeobjList_Append(p_gbl, p_gb);

            if (FRONT_CONSOLE_LOG_MODE)
            {
                printf("creat: %s\n", BACK_Geobj_Info(p_gb));
            }
            // printf("log success\n");

            FRONT_Main2dShow_AnSelectedGeobj_Clear();
            // printf("return success\n");
        }
    }
}

char *BACK_OrdinaryPolygon_Seed(BACK_Geobj *p_gb)
{
    if (p_gb->en_class != ORDINARY_POLYGON_CLASS)
    {
        Error("BACK_OrdinaryPolygon_Seed: Error type");
        return;
    }

    char *str_seed = (char *)malloc(sizeof(char) * MAX_LINE);
    BACK_OrdinaryPolygon *p_opo = (BACK_OrdinaryPolygon *)(p_gb->p_geobj);

    sprintf(str_seed,
            "%d %ld %s %d",
            p_gb->en_class,
            p_gb->id,
            p_gb->name,
            p_opo->len);

    char ts[10];
    for (int i = 0; i < p_opo->len; i++)
    {
        sprintf(ts, " %ld", p_opo->anBaseId[i]);
        strcat(str_seed, ts);
    }

    return str_seed;
}
BACK_Geobj *BACK_OrdinaryPolygon_Relife(char *str_seed)
{
    BACK_Geobj *p_gb = (BACK_Geobj *)malloc(sizeof(BACK_Geobj));
    BACK_OrdinaryPolygon *p_opo = (BACK_OrdinaryPolygon *)malloc(sizeof(BACK_OrdinaryPolygon));
    p_gb->p_geobj = p_opo;
    p_gb->name = (char *)malloc(sizeof(char) * 10);

    int offset;
    sscanf(str_seed,
           "%d %ld %s %d%n",
           &(p_gb->en_class),
           &(p_gb->id),
           (p_gb->name),
           &(p_opo->len),
           &offset);

    char *ts = str_seed + offset;

    for (int i = 0; i < p_opo->len; i++)
    {
        ;
        sscanf(ts,
               " %ld%n",
               &(p_opo->anBaseId[i]),
               &offset);
        ts += offset;
    }
    return p_gb;
}
