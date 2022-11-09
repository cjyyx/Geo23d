#include "BackEquationCurve.h"

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

BACK_Geobj *BACK_EquationCurve_Creat(char *strExpr)
{
    BACK_EquationCurve *p_ec = (BACK_EquationCurve *)malloc(sizeof(BACK_EquationCurve));

    int rt;
    double rrr;

    rt = EVIC_Cut(strExpr, &(p_ec->ec_expr));
    if (rt == 0)
        return NULL;

    EVIC_ValueLink(p_ec->ec_expr, "x", &(p_ec->x));
    EVIC_ValueLink(p_ec->ec_expr, "y", &(p_ec->y));

    rt = EVIC_Compile(&(p_ec->ec_expr));
    if (rt == 0)
        return NULL;

    p_ec->x = 0;
    p_ec->y = 0;
    rt = EVIC_Calculate(p_ec->ec_expr, &rrr);
    if (rt == 0)
        return NULL;

    strcpy(p_ec->strExpr, strExpr);

    BACK_Geobj *p_gb = BACK_Geobj_Creat();
    p_gb->en_class = EQUATION_CURVE_CLASS;
    p_gb->p_geobj = p_ec;
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

char *BACK_EquationCurve_Info(BACK_Geobj *p_gb)
{
    if (p_gb->en_class != EQUATION_CURVE_CLASS)
    {
        Error("BACK_EquationCurve_Info: Error type");
        return NULL;
    }

    BACK_EquationCurve *p_ec = (BACK_EquationCurve *)(p_gb->p_geobj);
    char *info = (char *)malloc(sizeof(char) * 100);
    sprintf(info,
            "%s_%ld_%s  %s",
            A_CLASS_NAME[EQUATION_CURVE_CLASS],
            p_gb->id,
            p_gb->name,
            p_ec->strExpr);

    return info;
}

void BACK_EquationCurve_DetectOperation()
{
    BACK_GeobjList *p_gbl = BACK_GetGeobjList();
    char *strExpr = FRONT_Input("Please Input The Equation f(x,y)=0");
    BACK_Geobj *p_gb = BACK_EquationCurve_Creat(strExpr);
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

void BACK_EquationCurve_Draw(BACK_Geobj *p_gb)
{
    if (p_gb->en_class != EQUATION_CURVE_CLASS)
    {
        Error("BACK_EquationCurve_Info: Error type");
        return NULL;
    }
    BACK_EquationCurve *p_ec = (BACK_EquationCurve *)(p_gb->p_geobj);
    double vx[2], vy[2],
        x_step, y_step, xx_step, yy_step,
        vx20, vy20,
        x1, y1, x2, y2,
        tx, ty,
        rrr;
    int marchingCube[FIRST_SCAN_SIZE + 1][FIRST_SCAN_SIZE + 1],
        marchingCube2[SECOND_SCAN_SIZE + 1][SECOND_SCAN_SIZE + 1],
        flag;

    FRONT_Main2dShow_GetVisualRange(vx, vy);

    SetPenColor("Blue");
    SetPenSize(EQUATION_CURVE_SIZE);

    /* 下面利用Marching square绘制方程 */
    /* 第一次采样 */
    x_step = (vx[1] - vx[0]) / FIRST_SCAN_SIZE;
    y_step = (vy[1] - vy[0]) / FIRST_SCAN_SIZE;
    for (int i = 0; i < FIRST_SCAN_SIZE + 1; i++)
    {
        for (int j = 0; j < FIRST_SCAN_SIZE + 1; j++)
        {
            p_ec->x = vx[0] + i * x_step;
            p_ec->y = vy[0] + j * y_step;
            EVIC_Calculate(p_ec->ec_expr, &rrr);
            if (rrr >= 0)
            {
                flag = 1;
                // SetPenColor("Violet");
                // FRONT_Main2dShow_DrawPoint(p_ec->x, p_ec->y, 15);
            }
            else
            {
                flag = 0;
            }
            marchingCube[i][j] = flag;
        }
    }
    /* 利用第一次采样结果判断是否存在解 */
    for (int i = 0; i < FIRST_SCAN_SIZE; i++)
    {
        for (int j = 0; j < FIRST_SCAN_SIZE; j++)
        {
            flag = 0b0000;
            flag += marchingCube[i][j + 1];
            flag *= 2;
            flag += marchingCube[i + 1][j + 1];
            flag *= 2;
            flag += marchingCube[i + 1][j];
            flag *= 2;
            flag += marchingCube[i][j];
            if (
                (flag == 0b0000) ||
                (flag == 0b1111))
            {
                /* 说明应该没有解 */
                continue;
            }
            else
            {
                // tx = vx[0] + (i + 0.5) * x_step;
                // ty = vy[0] + (j + 0.5) * y_step;
                // SetPenColor("Blue");
                // FRONT_Main2dShow_DrawPoint(tx, ty, 15);

                /* 进行局部采样 */
                vx20 = vx[0] + i * x_step;
                vy20 = vy[0] + j * y_step;
                xx_step = x_step / SECOND_SCAN_SIZE;
                yy_step = y_step / SECOND_SCAN_SIZE;
                for (int ii = 0; ii < SECOND_SCAN_SIZE + 1; ii++)
                {
                    for (int jj = 0; jj < SECOND_SCAN_SIZE + 1; jj++)
                    {
                        p_ec->x = vx20 + ii * xx_step;
                        p_ec->y = vy20 + jj * yy_step;
                        EVIC_Calculate(p_ec->ec_expr, &rrr);
                        if (rrr >= 0)
                        {
                            // SetPenColor("Violet");
                            // FRONT_Main2dShow_DrawPoint(p_ec->x, p_ec->y, 5);
                            flag = 1;
                        }
                        else
                        {
                            flag = 0;
                        }
                        marchingCube2[ii][jj] = flag;
                    }
                }
                /* 利用局部采样结果绘制方程 */
                for (int ii = 0; ii < SECOND_SCAN_SIZE; ii++)
                {
                    for (int jj = 0; jj < SECOND_SCAN_SIZE; jj++)
                    {
                        flag = 0b0000;
                        flag += marchingCube2[ii][jj + 1];
                        flag *= 2;
                        flag += marchingCube2[ii + 1][jj + 1];
                        flag *= 2;
                        flag += marchingCube2[ii + 1][jj];
                        flag *= 2;
                        flag += marchingCube2[ii][jj];

                        /* 测试用 */
                        // if (
                        //     (flag == 0b0000) ||
                        //     (flag == 0b1111))
                        // {
                        //     /* 说明应该没有解 */
                        //     continue;
                        // }
                        // else
                        // {
                        //     tx = vx20 + (ii + 0.5) * xx_step;
                        //     ty = vy20 + (jj + 0.5) * yy_step;
                        //     SetPenColor("Blue");
                        //     FRONT_Main2dShow_DrawPoint(tx, ty, 5);

                        //     continue;
                        // }

                        if (
                            (flag == 0b0000) ||
                            (flag == 0b1111))
                        {
                            /* 说明应该没有解 */
                            continue;
                        }
                        else if (
                            (flag == 0b1110) ||
                            (flag == 0b0001))
                        {
                            x1 = vx20 + ii * xx_step;
                            x2 = vx20 + ii * xx_step + xx_step / 2;
                            y1 = vy20 + jj * yy_step + yy_step / 2;
                            y2 = vy20 + jj * yy_step;
                            FRONT_Main2dShow_DrawLine(x1, y1, x2, y2);
                            continue;
                        }
                        else if (
                            (flag == 0b1101) ||
                            (flag == 0b0010))
                        {
                            x1 = vx20 + ii * xx_step + xx_step / 2;
                            x2 = vx20 + ii * xx_step + xx_step;
                            y1 = vy20 + jj * yy_step;
                            y2 = vy20 + jj * yy_step + yy_step / 2;
                            FRONT_Main2dShow_DrawLine(x1, y1, x2, y2);
                            continue;
                        }
                        else if (
                            (flag == 0b1011) ||
                            (flag == 0b0100))
                        {
                            x1 = vx20 + ii * xx_step + xx_step / 2;
                            x2 = vx20 + ii * xx_step + xx_step;
                            y1 = vy20 + jj * yy_step + yy_step;
                            y2 = vy20 + jj * yy_step + yy_step / 2;
                            FRONT_Main2dShow_DrawLine(x1, y1, x2, y2);
                            continue;
                        }
                        else if (
                            (flag == 0b0111) ||
                            (flag == 0b1000))
                        {
                            x1 = vx20 + ii * xx_step;
                            x2 = vx20 + ii * xx_step + xx_step / 2;
                            y1 = vy20 + jj * yy_step + yy_step / 2;
                            y2 = vy20 + jj * yy_step + yy_step;
                            FRONT_Main2dShow_DrawLine(x1, y1, x2, y2);
                            continue;
                        }
                        else if (
                            (flag == 0b1100) ||
                            (flag == 0b0011))
                        {
                            x1 = vx20 + ii * xx_step;
                            x2 = vx20 + ii * xx_step + xx_step;
                            y1 = vy20 + jj * yy_step + yy_step / 2;
                            y2 = vy20 + jj * yy_step + yy_step / 2;
                            FRONT_Main2dShow_DrawLine(x1, y1, x2, y2);
                            continue;
                        }
                        else if (
                            (flag == 0b1001) ||
                            (flag == 0b0110))
                        {
                            x1 = vx20 + ii * xx_step + xx_step / 2;
                            x2 = vx20 + ii * xx_step + xx_step / 2;
                            y1 = vy20 + jj * yy_step;
                            y2 = vy20 + jj * yy_step + yy_step;
                            FRONT_Main2dShow_DrawLine(x1, y1, x2, y2);
                            continue;
                        }
                        else if (
                            (flag == 0b1010))
                        {
                            p_ec->x = vx20 + ii * xx_step + xx_step / 2;
                            p_ec->y = vy20 + jj * yy_step + yy_step / 2;
                            EVIC_Calculate(p_ec->ec_expr, &rrr);
                            if (rrr >= 0)
                            {
                                x1 = vx20 + ii * xx_step + xx_step / 2;
                                x2 = vx20 + ii * xx_step + xx_step;
                                y1 = vy20 + jj * yy_step + yy_step;
                                y2 = vy20 + jj * yy_step + yy_step / 2;
                                FRONT_Main2dShow_DrawLine(x1, y1, x2, y2);
                                x1 = vx20 + ii * xx_step;
                                x2 = vx20 + ii * xx_step + xx_step / 2;
                                y1 = vy20 + jj * yy_step + yy_step / 2;
                                y2 = vy20 + jj * yy_step;
                                FRONT_Main2dShow_DrawLine(x1, y1, x2, y2);
                                continue;
                            }
                            else
                            {
                                x1 = vx20 + ii * xx_step;
                                x2 = vx20 + ii * xx_step + xx_step / 2;
                                y1 = vy20 + jj * yy_step + yy_step / 2;
                                y2 = vy20 + jj * yy_step + yy_step;
                                FRONT_Main2dShow_DrawLine(x1, y1, x2, y2);
                                x1 = vx20 + ii * xx_step + xx_step / 2;
                                x2 = vx20 + ii * xx_step + xx_step;
                                y1 = vy20 + jj * yy_step;
                                y2 = vy20 + jj * yy_step + yy_step / 2;
                                FRONT_Main2dShow_DrawLine(x1, y1, x2, y2);
                                continue;
                            }
                        }
                        else if (
                            (flag == 0b0101))
                        {
                            p_ec->x = vx20 + ii * xx_step + xx_step / 2;
                            p_ec->y = vy20 + jj * yy_step + yy_step / 2;
                            EVIC_Calculate(p_ec->ec_expr, &rrr);
                            if (rrr >= 0)
                            {
                                x1 = vx20 + ii * xx_step;
                                x2 = vx20 + ii * xx_step + xx_step / 2;
                                y1 = vy20 + jj * yy_step + yy_step / 2;
                                y2 = vy20 + jj * yy_step + yy_step;
                                FRONT_Main2dShow_DrawLine(x1, y1, x2, y2);
                                x1 = vx20 + ii * xx_step + xx_step / 2;
                                x2 = vx20 + ii * xx_step + xx_step;
                                y1 = vy20 + jj * yy_step;
                                y2 = vy20 + jj * yy_step + yy_step / 2;
                                FRONT_Main2dShow_DrawLine(x1, y1, x2, y2);
                                continue;
                            }
                            else
                            {
                                x1 = vx20 + ii * xx_step + xx_step / 2;
                                x2 = vx20 + ii * xx_step + xx_step;
                                y1 = vy20 + jj * yy_step + yy_step;
                                y2 = vy20 + jj * yy_step + yy_step / 2;
                                FRONT_Main2dShow_DrawLine(x1, y1, x2, y2);
                                x1 = vx20 + ii * xx_step;
                                x2 = vx20 + ii * xx_step + xx_step / 2;
                                y1 = vy20 + jj * yy_step + yy_step / 2;
                                y2 = vy20 + jj * yy_step;
                                FRONT_Main2dShow_DrawLine(x1, y1, x2, y2);
                                continue;
                            }
                        }
                        else
                        {
                            FRONT_Alart("Warning: BACK_EquationCurve_Draw");
                            continue;
                        }
                    }
                }
            }
        }
    }
}

char *BACK_EquationCurve_Seed(BACK_Geobj *p_gb)
{
    if (p_gb->en_class != EQUATION_CURVE_CLASS)
    {
        Error("BACK_EquationCurve_Seed: Error type");
        return;
    }
    char *str_seed = (char *)malloc(sizeof(char) * MAX_LINE);
    BACK_EquationCurve *p_ec = (BACK_EquationCurve *)(p_gb->p_geobj);

    sprintf(str_seed,
            "%d %ld %s %s",
            p_gb->en_class,
            p_gb->id,
            p_gb->name,
            p_ec->strExpr);

    return str_seed;
}

BACK_Geobj *BACK_EquationCurve_Relife(char *str_seed)
{
    BACK_Geobj *p_gb = (BACK_Geobj *)malloc(sizeof(BACK_Geobj));
    BACK_EquationCurve *p_ec = (BACK_EquationCurve *)malloc(sizeof(BACK_EquationCurve));
    p_gb->p_geobj = p_ec;
    p_gb->name = (char *)malloc(sizeof(char) * 10);

    sscanf(str_seed,
           "%d %ld %s %s",
           &(p_gb->en_class),
           &(p_gb->id),
           (p_gb->name),
           &(p_ec->strExpr));

    int rt;
    double rrr;

    rt = EVIC_Cut(p_ec->strExpr, &(p_ec->ec_expr));
    if (rt == 0)
        return NULL;

    EVIC_ValueLink(p_ec->ec_expr, "x", &(p_ec->x));
    EVIC_ValueLink(p_ec->ec_expr, "y", &(p_ec->y));

    rt = EVIC_Compile(&(p_ec->ec_expr));
    if (rt == 0)
        return NULL;

    p_ec->x = 0;
    p_ec->y = 0;
    rt = EVIC_Calculate(p_ec->ec_expr, &rrr);
    if (rt == 0)
        return NULL;

    return p_gb;
}