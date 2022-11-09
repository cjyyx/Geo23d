
#include <windows.h>
#include <winuser.h>
#include "graphics.h"
#include "extgraph.h"
#include "imgui.h"
#include "linkedlist.h"

#include "Back.h"
#include "Front.h"
#include "FrontMain2d.h"
#include "FrontMain2dShow.h"

#include <math.h>

/* 初始化showInterface2D坐标变换的相关系数 */
static void InitCoordinateTransformationCoefficient2D();
/* 坐标变换，把理想坐标系中的点变换到窗口坐标系中的点 */
static void CoordinateTransformate2D(double x_im, double y_im, double *x_re, double *y_re);
/* 坐标逆变换，把窗口坐标系中的点变换到理想坐标系中的点 */
static void InverseCoordinateTransformate2D(double x_re, double y_re, double *x_im, double *y_im);

/* 绘制坐标系，包括坐标轴及网格线 */
static void DrawCoordinateSystem();
/* 绘制所有选中的图形对象的选中效果 */
static void DrawAllSelectedGeobj();
/* 绘制所有图形对象 */
static void DrawAllGeobj();
/* 绘制选中的 OrdinaryPoint的选中效果 */
static void DrawSelectedOrdinaryPoint(BACK_Geobj *p_gb);

/* 利用虚拟坐标系画一个点 */
static void DrawPoint2DIm(double x_im, double y_im, int size);
/* 利用虚拟坐标系画一条线 */
static void DrawLine2DIm(double x1_im, double y1_im, double x2_im, double y2_im);
/* 利用虚拟坐标系画文字 */
static void DrawText2DIm(double x_im, double y_im, char *text);

/* 获得鼠标坐标系坐标，非窗口坐标 */
static void GetMouseCoordIm(double *mouseImX, double *mouseImY);
/* 获得可视坐标范围,注意是虚拟坐标 */
static void GetVisualCoord2DImRange(double *visualCoord2DRangeX, double *visualCoord2DRangeY);

/* showInterface伸缩系数 */
static double coordExpansion2DX, coordExpansion2DY;
/* 调整coordExpansion2DX, coordExpansion2DY */
static void coordExpansion2D_Updata(int event);
/* showInterface移动系数
x_re = coordExpansion2DX * x_im + coordMove2DX;
y_re = coordExpansion2DY * y_im + coordMove2DY; */
static double coordMove2DX, coordMove2DY;
/* 调整coordMove2DX, coordMove2DY */
static void coordMove2DXY_Updata();

/* 记录选中的几何对象队列 */
static BACK_Geobj *An_selectedGeobj[FRONT_Main2dShow_SELECTED_GEOBJ_LEN_MAX];
/* 记录这一帧选中的几何对象 */
static BACK_Geobj *selectedGeobjThisFrame;
/* 仅利用空间距离标记选中的几何对象，不判断鼠标 */
static void MarkSelectedGeobj(BACK_Geobj *p_gb);
/* 清空选中的几何对象数组 */
static void An_selectedGeobj_Clear();
/* 选中的几何对象数组添加 */
static void An_selectedGeobj_Enter(BACK_Geobj *p_gb);

/* 判断发生的操作 */
void DetectOperation(int button, int event);

/* 当前showInterface状态 */
static int curShowInterfaceState;
/* 判断选中的几何对象判断当前showInterface状态 */
static void curShowInterfaceState_Judge(int button, int event);

/* 判断鼠标是否在showWindow中 */
static int MouseInShowWindow();

void FRONT_Main2dShow_Init()
{

    curShowInterfaceState = LOSE_FOCUS_STATE;
    InitCoordinateTransformationCoefficient2D();
    An_selectedGeobj_Clear();
}
void FRONT_Main2dShow_Display()
{

    /* showwindow 的边框 */
    SetPenColor("Black");
    SetPenSize(5);
    drawRectangle(
        EDIT_WINDOW_WIDTH,
        0,
        SHOW_WINDOW_WIDTH,
        SHOW_WINDOW_HEIGHT,
        0);

    /* draw坐标系 */
    DrawCoordinateSystem();

    /* 绘制所有选中的图形对象的选中效果 */
    DrawAllSelectedGeobj();

    /* 绘制所有图形对象 */
    DrawAllGeobj();

    /* 设置字体 */
    SetPenColor("Black");
    SetPointSize(10);

    /* 调试用，显示坐标变换相关参数 */
    if (FRONT_DEBUG_MODE)
    {
        char debug_text[500];
        MovePen(
            EDIT_WINDOW_WIDTH * 1.03,
            SHOW_WINDOW_HEIGHT * 0.5);
        sprintf(
            debug_text,
            "coordExpansion2DX: %lf, coordExpansion2DY: %lf",
            coordExpansion2DX,
            coordExpansion2DY);
        DrawTextString(debug_text);

        MovePen(
            EDIT_WINDOW_WIDTH * 1.03,
            SHOW_WINDOW_HEIGHT * 0.4);
        sprintf(
            debug_text,
            "coordMove2DX: %lf, coordMove2DY: %lf",
            coordMove2DX,
            coordMove2DY);
        DrawTextString(debug_text);
    }

    /* 右下角显示鼠标所指的坐标系坐标，非窗口坐标 */
    double mouseImX, mouseImY;
    GetMouseCoordIm(&mouseImX, &mouseImY);
    char info[50];
    sprintf(info,
            "mouse coordinate: ( %lf , %lf )",
            mouseImX,
            mouseImY);
    MovePen(
        EDIT_WINDOW_WIDTH + SHOW_WINDOW_WIDTH * 0.6,
        SHOW_WINDOW_HEIGHT * 0.01);
    DrawTextString(info);

    /* 显示窗口坐标系下的鼠标坐标 */
    if (FRONT_DEBUG_MODE)
    {
        double mouseReX, mouseReY;
        FRONT_GetMouseReVal(&mouseReX, &mouseReY);
        char info[50];
        sprintf(info,
                "real mouse coordinate: ( %lf , %lf )",
                mouseReX,
                mouseReY);
        MovePen(
            EDIT_WINDOW_WIDTH + SHOW_WINDOW_WIDTH * 0.5,
            SHOW_WINDOW_HEIGHT * 0.1);
        DrawTextString(info);

        sprintf(info,
                "curShowInterfaceState: %d",
                curShowInterfaceState);
        MovePen(
            EDIT_WINDOW_WIDTH + SHOW_WINDOW_WIDTH * 0.6,
            SHOW_WINDOW_HEIGHT * 0.2);
        DrawTextString(info);

        sprintf(info,
                "FRONT_buttonDownState: %d\n",
                FRONT_buttonDownState);
        MovePen(
            EDIT_WINDOW_WIDTH + SHOW_WINDOW_WIDTH * 0.6,
            SHOW_WINDOW_HEIGHT * 0.3);
        DrawTextString(info);

        sprintf(info,
                "AnSelectedGeobj_Len: %d\n",
                FRONT_Main2dShow_AnSelectedGeobj_Len());
        MovePen(
            EDIT_WINDOW_WIDTH + SHOW_WINDOW_WIDTH * 0.6,
            SHOW_WINDOW_HEIGHT * 0.4);
        DrawTextString(info);
    }

    /* ShowWindow 左下角提示当前tool Mode */
    MovePen(
        EDIT_WINDOW_WIDTH * 1.03,
        SHOW_WINDOW_HEIGHT * 0.01);
    DrawTextString("Tool Mode: ");
    DrawTextString(A_TOOL_NAME[FRONT_Main2d_CurTool]);
}

void An_selectedGeobj_Clear()
{
    for (int i = 0;
         i < (sizeof(An_selectedGeobj) / sizeof(An_selectedGeobj[0]));
         i++)
    {
        An_selectedGeobj[i] = NULL;
    }
}
void FRONT_Main2dShow_AnSelectedGeobj_Clear()
{
    An_selectedGeobj_Clear();
}
void FRONT_Main2dShow_AnSelectedGeobj_Enter(BACK_Geobj *p_gb)
{
    An_selectedGeobj_Enter(p_gb);
}

int FRONT_Main2dShow_AnSelectedGeobj_Len()
{
    int len = 0;
    for (; An_selectedGeobj[len] != NULL; len++)
        ;
    return len;
}

void FRONT_Main2dShow_MouseEventProcess(int button, int event)
{
    curShowInterfaceState_Judge(button, event);

    DetectOperation(button, event);
    coordMove2DXY_Updata();
    coordExpansion2D_Updata(event);
}
void FRONT_Main2dShow_TimerEventProcess()
{
}

void FRONT_Main2dShow_DrawPoint(double x_im, double y_im, int size)
{
    DrawPoint2DIm(x_im, y_im, size);
}
void FRONT_Main2dShow_DrawLine(double x1_im, double y1_im, double x2_im, double y2_im)
{
    DrawLine2DIm(x1_im, y1_im, x2_im, y2_im);
}
void FRONT_Main2dShow_DrawText(double x_im, double y_im, char *text)
{
    DrawText2DIm(x_im, y_im, text);
}

void FRONT_Main2dShow_DrawArc(double x_im, double y_im, double r, double startAngle, double sweep)
{
    double x_re, y_re;
    CoordinateTransformate2D(x_im, y_im, &x_re, &y_re);

    r *= sqrt((coordExpansion2DX * coordExpansion2DX +
               coordExpansion2DY * coordExpansion2DY) /
              2);

    MovePen(x_re + r, y_re);
    DrawArc(r, startAngle, sweep);
}

void FRONT_Main2dShow_GetMouseIm(double *mouseImX, double *mouseImY)
{
    GetMouseCoordIm(mouseImX, mouseImY);
}
void FRONT_Main2dShow_GetVisualRange(double *vx, double *vy)
{
    GetVisualCoord2DImRange(vx, vy);
}

void FRONT_Main2dShow_GetCooedExpansion(double *cex, double *cey)
{
    *cex = coordExpansion2DX;
    *cey = coordExpansion2DY;
}
int FRONT_Main2dShow_GetCurShowInterfaceState()
{
    return curShowInterfaceState;
}

BACK_Geobj **FRONT_Main2dShow_GetAnSelectedGeobj()
{
    return An_selectedGeobj;
}

BACK_Geobj *FRONT_Main2dShow_GetSelectedGeobjThisFrame()
{
    return selectedGeobjThisFrame;
}

static int MouseInShowWindow()
{
    double mouseReX, mouseReY;
    FRONT_GetMouseReVal(&mouseReX, &mouseReY);
    if ((mouseReX > EDIT_WINDOW_WIDTH) &&
        (mouseReX < (EDIT_WINDOW_WIDTH + SHOW_WINDOW_WIDTH)) &&
        (mouseReY > 0) &&
        (mouseReY < SHOW_WINDOW_HEIGHT))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
void curShowInterfaceState_Judge(int button, int event)
{

    double mouseReX, mouseReY;
    FRONT_GetMouseReVal(&mouseReX, &mouseReY);

    BACK_GeobjList *p_gbl = BACK_GetGeobjList();

    BACK_GeobjList_Traverse(p_gbl, MarkSelectedGeobj);

    if (MouseInShowWindow())
    {
        switch (event)
        {
        case BUTTON_DOWN:
            if (
                curShowInterfaceState == LOSE_FOCUS_STATE ||
                curShowInterfaceState == MOUSE_DISENGAGEMENT_STATE)
            {
                curShowInterfaceState = NO_ACTION_STATE;
                return;
            }
            else
            {
                curShowInterfaceState = CLICK_STATE;
                return;
            }
            break;

        case BUTTON_UP:
            if (curShowInterfaceState == CLICK_STATE)
            {
                curShowInterfaceState = NO_ACTION_STATE;
            }
            break;

        case MOUSEMOVE:
            if (curShowInterfaceState == CLICK_STATE)
            {
                curShowInterfaceState = NO_ACTION_STATE;
            }
            switch (curShowInterfaceState)
            {
            case DRAG_SHOW_INTERFACE_STATE:
                if (FRONT_buttonDownState)
                {
                    curShowInterfaceState = DRAG_SHOW_INTERFACE_STATE;
                    return;
                }
                else
                {
                    curShowInterfaceState = NO_ACTION_STATE;
                    return;
                }
                break;

            case DRAG_GEOBJ_STATE:
                if (FRONT_buttonDownState)
                {
                    curShowInterfaceState = DRAG_GEOBJ_STATE;
                    return;
                }
                else
                {
                    curShowInterfaceState = NO_ACTION_STATE;
                    return;
                }
                break;

            default:
                if (FRONT_buttonDownState)
                {
                    if (selectedGeobjThisFrame == NULL)
                    {
                        curShowInterfaceState = DRAG_SHOW_INTERFACE_STATE;
                        return;
                    }
                    else
                    {
                        curShowInterfaceState = DRAG_GEOBJ_STATE;
                        return;
                    }
                }
                break;
            }

            break;

        default:
            curShowInterfaceState = NO_ACTION_STATE;
            return;
            break;
        }
    }
    else
    {
        if (event == BUTTON_DOWN)
        {
            curShowInterfaceState = LOSE_FOCUS_STATE;
        }
        else
        {
            curShowInterfaceState = MOUSE_DISENGAGEMENT_STATE;
        }
    }
}

void DetectOperation(int button, int event)
{
    double mouseImX, mouseImY;
    GetMouseCoordIm(&mouseImX, &mouseImY);
    BACK_GeobjList *p_gbl = BACK_GetGeobjList();

    switch (FRONT_Main2d_CurTool)
    {
    case ORDINARY_POINT_TOOL:
        BACK_OrdinaryPoint_DetectOperation();
        break;
    case ORDINARY_LINE_TOOL:
        BACK_OrdinaryLine_DetectOperation();
        break;
    case CENTER_POINT_CIRCLE_TOOL:
        BACK_CenterAndPointCircle_DetectOperation();
        break;
    case MIDDLE_POINT_TOOL:
        BACK_MiddlePoint_DetectOperation();
        break;
    case LINE_SEGMENT_TOOL:
        BACK_LineSegment_DetectOperation();
        break;
    case REGULAR_POLYGON_TOOL:
        BACK_RegularPolygon_DetectOperation();
        break;
    case THREE_POINT_CIRCLE_TOOL:
        BACK_ThreePointCircle_DetectOperation();
        break;
    case MOVE_TOOL:
        if (curShowInterfaceState == CLICK_STATE)
        {
            An_selectedGeobj_Clear();
            An_selectedGeobj[0] = selectedGeobjThisFrame;
            if (
                FRONT_CONSOLE_LOG_MODE &&
                selectedGeobjThisFrame != NULL)
            {
                printf("select: %s\n", BACK_Geobj_Info(selectedGeobjThisFrame));
            }
        }

        /* 拖动点 */

        if (
            curShowInterfaceState == DRAG_GEOBJ_STATE &&
            selectedGeobjThisFrame != NULL)
        {
            BACK_Geobj *p_gb = selectedGeobjThisFrame;
            double mx_im, my_im;
            FRONT_Main2dShow_GetMouseIm(&mx_im, &my_im);

            ((BACK_OrdinaryPoint *)(p_gb->p_geobj))->x = mx_im;
            ((BACK_OrdinaryPoint *)(p_gb->p_geobj))->y = my_im;
        }
        break;
    case ORDINARY_POLYGON_TOOL:
        BACK_OrdinaryPolygon_DetectOperation();
        break;

    default:
        break;
    }
}

void InitCoordinateTransformationCoefficient2D()
{

    double x1 = -5, new_x1 = EDIT_WINDOW_WIDTH;
    double x2 = 5, new_x2 = MAIN_INTERFACE_WIDTH;
    double y1 = -5, new_y1 = 0;
    double y2 = 5, new_y2 = SHOW_WINDOW_HEIGHT;

    coordExpansion2DX = (new_x1 - new_x2) / (x1 - x2);
    coordMove2DX = new_x1 - coordExpansion2DX * x1;

    coordExpansion2DY = (new_y1 - new_y2) / (y1 - y2);
    coordMove2DY = new_y1 - coordExpansion2DY * y1;
}

void GetMouseCoordIm(double *mouseImX, double *mouseImY)
{
    double mouseReX, mouseReY;
    FRONT_GetMouseReVal(&mouseReX, &mouseReY);

    InverseCoordinateTransformate2D(mouseReX, mouseReY, mouseImX, mouseImY);
}

void GetVisualCoord2DImRange(double *visualCoord2DRangeX, double *visualCoord2DRangeY)
{
    double x1_re = EDIT_WINDOW_WIDTH;
    double y1_re = 0;
    double x2_re = MAIN_INTERFACE_WIDTH;
    double y2_re = SHOW_WINDOW_HEIGHT;

    double x1_im;
    double y1_im;
    double x2_im;
    double y2_im;

    InverseCoordinateTransformate2D(x1_re, y1_re, &x1_im, &y1_im);
    InverseCoordinateTransformate2D(x2_re, y2_re, &x2_im, &y2_im);

    visualCoord2DRangeX[0] = x1_im;
    visualCoord2DRangeX[1] = x2_im;
    visualCoord2DRangeY[0] = y1_im;
    visualCoord2DRangeY[1] = y2_im;
}

void DrawSelectedOrdinaryPoint(BACK_Geobj *p_gb)
{
    double x, y;
    x = ((BACK_OrdinaryPoint *)(p_gb->p_geobj))->x;
    y = ((BACK_OrdinaryPoint *)(p_gb->p_geobj))->y;

    double visualCoord2DRangeX[2], visualCoord2DRangeY[2];
    GetVisualCoord2DImRange(visualCoord2DRangeX, visualCoord2DRangeY);

    /* 能看到才画 */
    if (
        (x > visualCoord2DRangeX[0]) &&
        (x < visualCoord2DRangeX[1]) &&
        (y > visualCoord2DRangeY[0]) &&
        (y < visualCoord2DRangeY[1]))
    {
        SetPenColor("Blue");
        DrawPoint2DIm(x, y, 20);
    }
}

void DrawAllGeobj()
{
    BACK_GeobjList *p_gbl = BACK_GetGeobjList();
    BACK_GeobjList_Traverse(p_gbl, BACK_Geobj_Draw);
}
void DrawAllSelectedGeobj()
{
    for (int i = 0;
         i < (sizeof(An_selectedGeobj) / sizeof(An_selectedGeobj[0]));
         i++)
    {
        if (An_selectedGeobj[i] == NULL)
        {
            break;
        }
        else
        {
            BACK_Geobj *p_gb = An_selectedGeobj[i];
            switch (p_gb->en_class)
            {
            case ORDINARY_POINT_CLASS:
                DrawSelectedOrdinaryPoint(p_gb);
                break;

            default:
                break;
            }
        }
    }
}
void CoordinateTransformate2D(double x_im, double y_im, double *x_re, double *y_re)
{
    *x_re = coordExpansion2DX * x_im + coordMove2DX;
    *y_re = coordExpansion2DY * y_im + coordMove2DY;
}

void InverseCoordinateTransformate2D(double x_re, double y_re, double *x_im, double *y_im)
{
    *x_im = (x_re - coordMove2DX) / coordExpansion2DX;
    *y_im = (y_re - coordMove2DY) / coordExpansion2DY;
}

void DrawPoint2DIm(double x_im, double y_im, int size)
{
    SetPenSize(size);
    DrawLine2DIm(x_im, y_im, x_im, y_im);
}

void DrawLine2DIm(double x1_im, double y1_im, double x2_im, double y2_im)
{
    double x1_re;
    double y1_re;
    double x2_re;
    double y2_re;

    CoordinateTransformate2D(x1_im, y1_im, &x1_re, &y1_re);
    CoordinateTransformate2D(x2_im, y2_im, &x2_re, &y2_re);
    // printf("im->re: (%lf %lf %lf %lf) ->(%lf %lf %lf %lf) \n", x1_im, y1_im, x2_im, y2_im,
    //        x1_re,
    //        y1_re,
    //        x2_re,
    //        y2_re);

    MovePen(x1_re, y1_re);
    DrawLine(x2_re - x1_re, y2_re - y1_re);
}

void DrawText2DIm(double x_im, double y_im, char *text)
{
    double x_re, y_re;
    CoordinateTransformate2D(x_im, y_im, &x_re, &y_re);
    MovePen(x_re, y_re);
    DrawTextString(text);
}

/* 绘制坐标系，包括坐标轴及网格线 */
void DrawCoordinateSystem()
{
    /* 先画网格线 */

    double visualCoord2DRangeX[2], visualCoord2DRangeY[2];
    GetVisualCoord2DImRange(visualCoord2DRangeX, visualCoord2DRangeY);

    /* 先画竖线 */
    for (int i = (int)visualCoord2DRangeX[0] + 1;
         i <= (int)visualCoord2DRangeX[1];
         i++)
    {
        double x1_im = (double)i;
        double y1_im = visualCoord2DRangeY[0];
        double x2_im = (double)i;
        double y2_im = visualCoord2DRangeY[1];
        SetPenColor("Green");
        SetPenSize(0.1);
        DrawLine2DIm(x1_im, y1_im, x2_im, y2_im);

        /* 如果能看到横轴，且没有过度缩放，就画坐标值 */
        if (
            (0 > visualCoord2DRangeY[0]) &&
            (0 < visualCoord2DRangeY[1]) &&
            (coordExpansion2DX > 0.3))
        {
            /* 设置字体 */
            SetPenColor("Black");
            SetPointSize(5);

            char info[10];
            sprintf(info, "%d", i);
            DrawText2DIm(x1_im, 0, info);
        }
    }

    /* 再画横线 */
    for (int i = (int)visualCoord2DRangeY[0] + 1;
         i <= visualCoord2DRangeY[1];
         i++)
    {
        double x1_im = visualCoord2DRangeX[0];
        double y1_im = (double)i;
        double x2_im = visualCoord2DRangeX[1];
        double y2_im = (double)i;
        SetPenColor("Green");
        SetPenSize(0.1);

        DrawLine2DIm(x1_im, y1_im, x2_im, y2_im);

        /* 与上同理 */
        if (
            (0 > visualCoord2DRangeX[0]) &&
            (0 < visualCoord2DRangeX[1]) &&
            (coordExpansion2DX > 0.3))
        {
            /* 设置字体 */
            SetPenColor("Black");
            SetPointSize(5);

            char info[10];
            sprintf(info, "%d", i);
            DrawText2DIm(0, y1_im, info);
        }
    }

    /* 画坐标轴 */
    SetPenSize(1);
    /* 画横轴 */
    if (
        (0 > visualCoord2DRangeY[0]) &&
        (0 < visualCoord2DRangeY[1]))
    {
        SetPenColor("Blue");
        DrawLine2DIm(
            visualCoord2DRangeX[0],
            0,
            visualCoord2DRangeX[1],
            0);
        DrawLine2DIm(
            visualCoord2DRangeX[1],
            0,
            visualCoord2DRangeX[1] - (visualCoord2DRangeX[1] - visualCoord2DRangeX[0]) * 0.02,
            (visualCoord2DRangeY[1] - visualCoord2DRangeY[0]) * 0.007);
        DrawLine2DIm(
            visualCoord2DRangeX[1],
            0,
            visualCoord2DRangeX[1] - (visualCoord2DRangeX[1] - visualCoord2DRangeX[0]) * 0.02,
            (visualCoord2DRangeY[1] - visualCoord2DRangeY[0]) * -0.007);
    }
    /* 画纵轴 */
    if (
        (0 > visualCoord2DRangeX[0]) &&
        (0 < visualCoord2DRangeX[1]))
    {
        SetPenColor("Red");
        DrawLine2DIm(
            0,
            visualCoord2DRangeY[0],
            0,
            visualCoord2DRangeY[1]);
        DrawLine2DIm(
            0,
            visualCoord2DRangeY[1],
            (visualCoord2DRangeX[1] - visualCoord2DRangeX[0]) * 0.007,
            visualCoord2DRangeY[1] - (visualCoord2DRangeY[1] - visualCoord2DRangeY[0]) * 0.02);
        DrawLine2DIm(
            0,
            visualCoord2DRangeY[1],
            (visualCoord2DRangeY[1] - visualCoord2DRangeY[0]) * -0.007,
            visualCoord2DRangeY[1] - (visualCoord2DRangeY[1] - visualCoord2DRangeY[0]) * 0.02);
    }
    /* 画原点 */
    if (
        (0 > visualCoord2DRangeY[0]) &&
        (0 < visualCoord2DRangeY[1]) &&
        (0 > visualCoord2DRangeX[0]) &&
        (0 < visualCoord2DRangeX[1]))
    {
        SetPenColor("Black");
        DrawPoint2DIm(0, 0, 10);
    }
}

void coordExpansion2D_Updata(int event)
{

    static double curMouseImX, curMouseImY;

    double mouseReX, mouseReY;
    FRONT_GetMouseReVal(&mouseReX, &mouseReY);

    /* 用来放缩 */
    double expcc = 0.05;
    if (event == ROLL_UP)
    {
        coordExpansion2DX *= (1 + expcc);
        coordExpansion2DY *= (1 + expcc);
        coordMove2DX = mouseReX - coordExpansion2DX * curMouseImX;
        coordMove2DY = mouseReY - coordExpansion2DY * curMouseImY;
    }
    else if (event == ROLL_DOWN)
    {
        coordExpansion2DX *= (1 - expcc);
        coordExpansion2DY *= (1 - expcc);
        coordMove2DX = mouseReX - coordExpansion2DX * curMouseImX;
        coordMove2DY = mouseReY - coordExpansion2DY * curMouseImY;
    }
    else
    {
        GetMouseCoordIm(&curMouseImX, &curMouseImY);
    }
}

void MarkSelectedGeobj(BACK_Geobj *p_gb)
{
    static long curFrame = 0;
    static int endTraverse = 0;

    double mouseImX, mouseImY;
    GetMouseCoordIm(&mouseImX, &mouseImY);

    /* 判断是否换帧 */
    if (curFrame != FRONT_frameCount)
    {
        curFrame = FRONT_frameCount;
        selectedGeobjThisFrame = NULL;
        endTraverse = 0;
    }
    if (endTraverse)
    {
        return;
    }
    if (BACK_Geobj_Selected(p_gb, mouseImX, mouseImY))
    {
        selectedGeobjThisFrame = p_gb;
        endTraverse = 1;
    }
}

void An_selectedGeobj_Enter(BACK_Geobj *p_gb)
{
    for (
        int i = (sizeof(An_selectedGeobj) / sizeof(An_selectedGeobj[0])) - 1;
        i > 0;
        i--)
    {
        An_selectedGeobj[i] = An_selectedGeobj[i - 1];
    }
    An_selectedGeobj[0] = p_gb;
}

void coordMove2DXY_Updata()
{
    static double curMouseImX, curMouseImY;

    double mouseReX, mouseReY;
    FRONT_GetMouseReVal(&mouseReX, &mouseReY);

    if (curShowInterfaceState == DRAG_SHOW_INTERFACE_STATE)
    {

        coordMove2DX = mouseReX - coordExpansion2DX * curMouseImX;
        coordMove2DY = mouseReY - coordExpansion2DY * curMouseImY;
    }
    else
    {
        GetMouseCoordIm(&curMouseImX, &curMouseImY);
    }
}