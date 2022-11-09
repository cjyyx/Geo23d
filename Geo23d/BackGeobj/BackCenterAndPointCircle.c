#include "BackCenterAndPointCircle.h"

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

BACK_Geobj *BACK_CenterAndPointCircle_Creat(long cid, long rid)
{
    BACK_CenterAndPointCircle *p_cac = (BACK_CenterAndPointCircle *)malloc(sizeof(BACK_CenterAndPointCircle));
    p_cac->centerId = cid;
    p_cac->radiusId = rid;

    BACK_Geobj *p_gb = BACK_Geobj_Creat();
    p_gb->en_class = CENTER_POINT_CIRCLE_CLASS;
    p_gb->p_geobj = p_cac;

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

char *BACK_CenterAndPointCircle_Info(BACK_Geobj *p_gb)
{
    if (p_gb->en_class != CENTER_POINT_CIRCLE_CLASS)
    {
        Error("BACK_CenterAndPointCircle_Info: Error type");
        return NULL;
    }

    BACK_CenterAndPointCircle *p_cac = (BACK_CenterAndPointCircle *)(p_gb->p_geobj);
    char *info = (char *)malloc(sizeof(char) * 100);
    sprintf(info,
            "%s_%ld_%s  %ld*%ld",
            A_CLASS_NAME[CENTER_POINT_CIRCLE_CLASS],
            p_gb->id,
            p_gb->name,
            p_cac->centerId,
            p_cac->radiusId);

    return info;
}

void BACK_CenterAndPointCircle_Draw(BACK_Geobj *p_gb)
{
    if (p_gb->en_class != CENTER_POINT_CIRCLE_CLASS)
    {
        Error("BACK_CenterAndPointCircle_Draw: Error type");
        return;
    }
    BACK_GeobjList *p_gbl = BACK_GetGeobjList();
    BACK_CenterAndPointCircle *p_cac = (BACK_CenterAndPointCircle *)(p_gb->p_geobj);
    BACK_Geobj *p_c_gb = BACK_GeobjList_Visit(p_gbl, p_cac->centerId);
    BACK_Geobj *p_r_gb = BACK_GeobjList_Visit(p_gbl, p_cac->radiusId);
    BACK_OrdinaryPoint *p_c_op = (BACK_OrdinaryPoint *)(p_c_gb->p_geobj);
    BACK_OrdinaryPoint *p_r_op = (BACK_OrdinaryPoint *)(p_r_gb->p_geobj);

    double r;
    r = sqrt((p_c_op->x - p_r_op->x) * (p_c_op->x - p_r_op->x) +
             (p_c_op->y - p_r_op->y) * (p_c_op->y - p_r_op->y));

    SetPenColor("Blue");
    SetPenSize(3);
    FRONT_Main2dShow_DrawArc(p_c_op->x, p_c_op->y, r, 0, 360);
    BACK_OrdinaryPoint_Draw(p_r_gb);
}

void BACK_CenterAndPointCircle_DetectOperation()
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
        BACK_Geobj *p_gb = BACK_CenterAndPointCircle_Creat(
            An_selectedGeobj[1]->id,
            An_selectedGeobj[0]->id);
        BACK_GeobjList_Append(p_gbl, p_gb);

        if (FRONT_CONSOLE_LOG_MODE)
        {
            printf("creat: %s\n", BACK_Geobj_Info(p_gb));
        }

        FRONT_Main2dShow_AnSelectedGeobj_Clear();
    }
}

char *BACK_CenterAndPointCircle_Seed(BACK_Geobj *p_gb)
{
    if (p_gb->en_class != CENTER_POINT_CIRCLE_CLASS)
    {
        Error("BACK_CenterAndPointCircle_Seed: Error type");
        return;
    }
    char *str_seed = (char *)malloc(sizeof(char) * MAX_LINE);
    BACK_CenterAndPointCircle *p_cpc = (BACK_CenterAndPointCircle *)(p_gb->p_geobj);

    sprintf(str_seed,
            "%d %ld %s %ld %ld",
            p_gb->en_class,
            p_gb->id,
            p_gb->name,
            p_cpc->centerId,
            p_cpc->radiusId);

    return str_seed;
}

BACK_Geobj *BACK_CenterAndPointCircle_Relife(char *str_seed)
{

    BACK_Geobj *p_gb = (BACK_Geobj *)malloc(sizeof(BACK_Geobj));
    BACK_CenterAndPointCircle *p_cpc = (BACK_CenterAndPointCircle *)malloc(sizeof(BACK_CenterAndPointCircle));
    p_gb->p_geobj = p_cpc;
    p_gb->name = (char *)malloc(sizeof(char) * 10);

    sscanf(str_seed,
           "%d %ld %s %ld %ld",
           &(p_gb->en_class),
           &(p_gb->id),
           (p_gb->name),
           &(p_cpc->centerId),
           &(p_cpc->radiusId));
    return p_gb;
}