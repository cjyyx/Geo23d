#include "BackFunctionCurve.h"

#include <strlib.h>
#include <stdlib.h>
#include <string.h>
#include "Back.h"
#include "FrontMain2dShow.h"
#include <windows.h>
#include <winuser.h>
#include "graphics.h"
#include "extgraph.h"
#include "imgui.h"
#include "linkedlist.h"
#include "Front.h"

BACK_Geobj *BACK_FunctionCurve_Creat(char *strExpr)
{
    BACK_FunctionCurve *p_fc = (BACK_FunctionCurve *)malloc(sizeof(BACK_FunctionCurve));

    int rt;
    double rrr;

    rt = EVIC_Cut(strExpr, &(p_fc->ec_expr));
    if (rt == 0)
        return NULL;

    EVIC_ValueLink(p_fc->ec_expr, "x", &(p_fc->x));

    rt = EVIC_Compile(&(p_fc->ec_expr));
    if (rt == 0)
        return NULL;

    p_fc->x = 0;
    rt = EVIC_Calculate(p_fc->ec_expr, &rrr);
    if (rt == 0)
        return NULL;

    strcpy(p_fc->strExpr, strExpr);

    BACK_Geobj *p_gb = BACK_Geobj_Creat();
    p_gb->en_class = FUNCTION_CURVE_CLASS;
    p_gb->p_geobj = p_fc;
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

char *BACK_FunctionCurve_Info(BACK_Geobj *p_gb)
{
    if (p_gb->en_class != FUNCTION_CURVE_CLASS)
    {
        Error("BACK_FunctionCurve_Info: Error type");
        return NULL;
    }

    BACK_FunctionCurve *p_fc = (BACK_FunctionCurve *)(p_gb->p_geobj);
    char *info = (char *)malloc(sizeof(char) * 100);
    sprintf(info,
            "%s_%ld_%s  %s",
            A_CLASS_NAME[FUNCTION_CURVE_CLASS],
            p_gb->id,
            p_gb->name,
            p_fc->strExpr);

    return info;
}

void BACK_FunctionCurve_DetectOperation()
{
    BACK_GeobjList *p_gbl = BACK_GetGeobjList();
    char *strExpr = FRONT_Input("Please Input The Function y=f(x)");
    BACK_Geobj *p_gb = BACK_FunctionCurve_Creat(strExpr);

    if (p_gb == NULL)
    {
        FRONT_Alart("Error Expression!");
    }
    else
    {
        BACK_GeobjList_Append(p_gbl, p_gb);
        if (FRONT_CONSOLE_LOG_MODE)
        {
            printf("creat: %s\n", BACK_Geobj_Info(p_gb));
        }
    }
}

void BACK_FunctionCurve_Draw(BACK_Geobj *p_gb)
{
    if (p_gb->en_class != FUNCTION_CURVE_CLASS)
    {
        Error("BACK_FunctionCurve_Info: Error type");
        return NULL;
    }
    BACK_FunctionCurve *p_fc = (BACK_FunctionCurve *)(p_gb->p_geobj);
    double vx[2], vy[2], x_step, x1, y1, x2, y2;
    FRONT_Main2dShow_GetVisualRange(vx, vy);

    x1 = vx[0];
    p_fc->x = x1;
    EVIC_Calculate(p_fc->ec_expr, &y1);

    SetPenColor("Blue");
    SetPenSize(FUNCTION_CURVE_SIZE);

    x_step = (vx[1] - vx[0]) / SAMPLING_POINT_SIZE;
    for (x2 = vx[0] + x_step; x2 < vx[1]; x2 += x_step)
    {
        p_fc->x = x2;
        EVIC_Calculate(p_fc->ec_expr, &y2);

        if (
            (y2 > vy[0]) &&
            (y2 < vy[1]))
        {
            FRONT_Main2dShow_DrawLine(x1, y1, x2, y2);
        }

        x1 = x2;
        y1 = y2;
    }
}

char *BACK_FunctionCurve_Seed(BACK_Geobj *p_gb)
{
    if (p_gb->en_class != FUNCTION_CURVE_CLASS)
    {
        Error("BACK_FunctionCurve_Seed: Error type");
        return;
    }
    char *str_seed = (char *)malloc(sizeof(char) * MAX_LINE);
    BACK_FunctionCurve *p_fc = (BACK_FunctionCurve *)(p_gb->p_geobj);

    sprintf(str_seed,
            "%d %ld %s %s",
            p_gb->en_class,
            p_gb->id,
            p_gb->name,
            p_fc->strExpr);

    return str_seed;
}

BACK_Geobj *BACK_FunctionCurve_Relife(char *str_seed)
{
    BACK_Geobj *p_gb = (BACK_Geobj *)malloc(sizeof(BACK_Geobj));
    BACK_FunctionCurve *p_fc = (BACK_FunctionCurve *)malloc(sizeof(BACK_FunctionCurve));
    p_gb->p_geobj = p_fc;
    p_gb->name = (char *)malloc(sizeof(char) * 10);

    sscanf(str_seed,
           "%d %ld %s %s",
           &(p_gb->en_class),
           &(p_gb->id),
           (p_gb->name),
           &(p_fc->strExpr));

    int rt;
    double rrr;

    rt = EVIC_Cut(p_fc->strExpr, &(p_fc->ec_expr));
    if (rt == 0)
        return NULL;

    EVIC_ValueLink(p_fc->ec_expr, "x", &(p_fc->x));

    rt = EVIC_Compile(&(p_fc->ec_expr));
    if (rt == 0)
        return NULL;

    p_fc->x = 0;
    rt = EVIC_Calculate(p_fc->ec_expr, &rrr);
    if (rt == 0)
        return NULL;

    return p_gb;
}