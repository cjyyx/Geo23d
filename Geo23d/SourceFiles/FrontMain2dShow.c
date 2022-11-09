
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

/* ��ʼ��showInterface2D����任�����ϵ�� */
static void InitCoordinateTransformationCoefficient2D();
/* ����任������������ϵ�еĵ�任����������ϵ�еĵ� */
static void CoordinateTransformate2D(double x_im, double y_im, double *x_re, double *y_re);
/* ������任���Ѵ�������ϵ�еĵ�任����������ϵ�еĵ� */
static void InverseCoordinateTransformate2D(double x_re, double y_re, double *x_im, double *y_im);

/* ��������ϵ�����������ἰ������ */
static void DrawCoordinateSystem();
/* ��������ѡ�е�ͼ�ζ����ѡ��Ч�� */
static void DrawAllSelectedGeobj();
/* ��������ͼ�ζ��� */
static void DrawAllGeobj();
/* ����ѡ�е� OrdinaryPoint��ѡ��Ч�� */
static void DrawSelectedOrdinaryPoint(BACK_Geobj *p_gb);

/* ������������ϵ��һ���� */
static void DrawPoint2DIm(double x_im, double y_im, int size);
/* ������������ϵ��һ���� */
static void DrawLine2DIm(double x1_im, double y1_im, double x2_im, double y2_im);
/* ������������ϵ������ */
static void DrawText2DIm(double x_im, double y_im, char *text);

/* ����������ϵ���꣬�Ǵ������� */
static void GetMouseCoordIm(double *mouseImX, double *mouseImY);
/* ��ÿ������귶Χ,ע������������ */
static void GetVisualCoord2DImRange(double *visualCoord2DRangeX, double *visualCoord2DRangeY);

/* showInterface����ϵ�� */
static double coordExpansion2DX, coordExpansion2DY;
/* ����coordExpansion2DX, coordExpansion2DY */
static void coordExpansion2D_Updata(int event);
/* showInterface�ƶ�ϵ��
x_re = coordExpansion2DX * x_im + coordMove2DX;
y_re = coordExpansion2DY * y_im + coordMove2DY; */
static double coordMove2DX, coordMove2DY;
/* ����coordMove2DX, coordMove2DY */
static void coordMove2DXY_Updata();

/* ��¼ѡ�еļ��ζ������ */
static BACK_Geobj *An_selectedGeobj[FRONT_Main2dShow_SELECTED_GEOBJ_LEN_MAX];
/* ��¼��һ֡ѡ�еļ��ζ��� */
static BACK_Geobj *selectedGeobjThisFrame;
/* �����ÿռ������ѡ�еļ��ζ��󣬲��ж���� */
static void MarkSelectedGeobj(BACK_Geobj *p_gb);
/* ���ѡ�еļ��ζ������� */
static void An_selectedGeobj_Clear();
/* ѡ�еļ��ζ���������� */
static void An_selectedGeobj_Enter(BACK_Geobj *p_gb);

/* �жϷ����Ĳ��� */
void DetectOperation(int button, int event);

/* ��ǰshowInterface״̬ */
static int curShowInterfaceState;
/* �ж�ѡ�еļ��ζ����жϵ�ǰshowInterface״̬ */
static void curShowInterfaceState_Judge(int button, int event);

/* �ж�����Ƿ���showWindow�� */
static int MouseInShowWindow();

void FRONT_Main2dShow_Init()
{

    curShowInterfaceState = LOSE_FOCUS_STATE;
    InitCoordinateTransformationCoefficient2D();
    An_selectedGeobj_Clear();
}
void FRONT_Main2dShow_Display()
{

    /* showwindow �ı߿� */
    SetPenColor("Black");
    SetPenSize(5);
    drawRectangle(
        EDIT_WINDOW_WIDTH,
        0,
        SHOW_WINDOW_WIDTH,
        SHOW_WINDOW_HEIGHT,
        0);

    /* draw����ϵ */
    DrawCoordinateSystem();

    /* ��������ѡ�е�ͼ�ζ����ѡ��Ч�� */
    DrawAllSelectedGeobj();

    /* ��������ͼ�ζ��� */
    DrawAllGeobj();

    /* �������� */
    SetPenColor("Black");
    SetPointSize(10);

    /* �����ã���ʾ����任��ز��� */
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

    /* ���½���ʾ�����ָ������ϵ���꣬�Ǵ������� */
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

    /* ��ʾ��������ϵ�µ�������� */
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

    /* ShowWindow ���½���ʾ��ǰtool Mode */
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

        /* �϶��� */

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

    /* �ܿ����Ż� */
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

/* ��������ϵ�����������ἰ������ */
void DrawCoordinateSystem()
{
    /* �Ȼ������� */

    double visualCoord2DRangeX[2], visualCoord2DRangeY[2];
    GetVisualCoord2DImRange(visualCoord2DRangeX, visualCoord2DRangeY);

    /* �Ȼ����� */
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

        /* ����ܿ������ᣬ��û�й������ţ��ͻ�����ֵ */
        if (
            (0 > visualCoord2DRangeY[0]) &&
            (0 < visualCoord2DRangeY[1]) &&
            (coordExpansion2DX > 0.3))
        {
            /* �������� */
            SetPenColor("Black");
            SetPointSize(5);

            char info[10];
            sprintf(info, "%d", i);
            DrawText2DIm(x1_im, 0, info);
        }
    }

    /* �ٻ����� */
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

        /* ����ͬ�� */
        if (
            (0 > visualCoord2DRangeX[0]) &&
            (0 < visualCoord2DRangeX[1]) &&
            (coordExpansion2DX > 0.3))
        {
            /* �������� */
            SetPenColor("Black");
            SetPointSize(5);

            char info[10];
            sprintf(info, "%d", i);
            DrawText2DIm(0, y1_im, info);
        }
    }

    /* �������� */
    SetPenSize(1);
    /* ������ */
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
    /* ������ */
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
    /* ��ԭ�� */
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

    /* �������� */
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

    /* �ж��Ƿ�֡ */
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