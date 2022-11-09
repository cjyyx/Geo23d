#include "BackLineSegment.h"

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

BACK_Geobj *BACK_LineSegment_Creat(long bid1, long bid2)
{
    BACK_LineSegment *p_ls = (BACK_LineSegment *)malloc(sizeof(BACK_LineSegment));
    p_ls->baseId1 = bid1;
    p_ls->baseId2 = bid2;

    BACK_Geobj *p_gb = BACK_Geobj_Creat();
    p_gb->en_class = LINE_SEGMENT_CLASS;
    p_gb->p_geobj = p_ls;

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

char *BACK_LineSegment_Info(BACK_Geobj *p_gb)
{
    if (p_gb->en_class != LINE_SEGMENT_CLASS)
    {
        Error("BACK_LineSegment_Info: Error type");
        return NULL;
    }

    BACK_LineSegment *p_ls = (BACK_LineSegment *)(p_gb->p_geobj);
    char *info = (char *)malloc(sizeof(char) * 100);
    sprintf(info,
            "%s_%ld_%s  %ld*%ld",
            A_CLASS_NAME[LINE_SEGMENT_CLASS],
            p_gb->id,
            p_gb->name,
            p_ls->baseId1,
            p_ls->baseId2);

    return info;
}

void BACK_LineSegment_Draw(BACK_Geobj *p_gb)
{
    if (p_gb->en_class != LINE_SEGMENT_CLASS)
    {
        Error("BACK_LineSegment_Draw: Error type");
        return;
    }
    BACK_GeobjList *p_gbl = BACK_GetGeobjList();
    BACK_LineSegment *p_ls = (BACK_LineSegment *)(p_gb->p_geobj);
    BACK_Geobj *p_gbb1 = BACK_GeobjList_Visit(p_gbl, p_ls->baseId1);
    BACK_Geobj *p_gbb2 = BACK_GeobjList_Visit(p_gbl, p_ls->baseId2);
    BACK_OrdinaryPoint *p_op1 = (BACK_OrdinaryPoint *)(p_gbb1->p_geobj);
    BACK_OrdinaryPoint *p_op2 = (BACK_OrdinaryPoint *)(p_gbb2->p_geobj);

    SetPenColor("Blue");
    SetPenSize(3);
    FRONT_Main2dShow_DrawLine(p_op1->x, p_op1->y, p_op2->x, p_op2->y);
    BACK_Geobj_Draw(p_gbb1);
    BACK_Geobj_Draw(p_gbb2);
}

void BACK_LineSegment_DetectOperation()
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
        BACK_Geobj *p_gb = BACK_LineSegment_Creat(
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

char *BACK_LineSegment_Seed(BACK_Geobj *p_gb)
{
    if (p_gb->en_class != LINE_SEGMENT_CLASS)
    {
        Error("BACK_LineSegment_Seed: Error type");
        return;
    }
    char *str_seed = (char *)malloc(sizeof(char) * MAX_LINE);
    BACK_LineSegment *p_ls = (BACK_LineSegment *)(p_gb->p_geobj);

    sprintf(str_seed,
            "%d %ld %s %ld %ld",
            p_gb->en_class,
            p_gb->id,
            p_gb->name,
            p_ls->baseId1,
            p_ls->baseId2);

    return str_seed;
}

BACK_Geobj *BACK_LineSegment_Relife(char *str_seed)
{
    BACK_Geobj *p_gb = (BACK_Geobj *)malloc(sizeof(BACK_Geobj));
    BACK_LineSegment *p_ls = (BACK_LineSegment *)malloc(sizeof(BACK_LineSegment));
    p_gb->p_geobj = p_ls;
    p_gb->name = (char *)malloc(sizeof(char) * 10);

    sscanf(str_seed,
           "%d %ld %s %ld %ld",
           &(p_gb->en_class),
           &(p_gb->id),
           (p_gb->name),
           &(p_ls->baseId1),
           &(p_ls->baseId2));
    return p_gb;
}