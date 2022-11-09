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
#include "FrontInput.h"

const char *A_TOOL_NAME[] = {
    "default tool",
    "Move",
    "OrdinaryPoint",
    "MiddlePoint",
    "OrdinaryLine",
    "LineSegment",
    "OrdinaryPolygon",
    "RegularPolygon",
    "CenterAndPointCircle",
    "ThreePointCircle"};

/* draw 最上方选项框 */
static void DrawTopMenu();
/* draw 工具选项窗口 */
static void DrawToolMenu();
/* draw 编辑窗口 */
static void DrawEditWindow();

/* 当前toolMode */
int FRONT_Main2d_CurTool;

void FRONT_Main2d_Display()
{

    FRONT_Main2dShow_Display();
    DrawEditWindow();
    SetPenColor("White");
    SetPenSize(1);
    drawRectangle(
        0,
        MAIN_INTERFACE_HEIGHT - MENU_HEIGHT * 2,
        MAIN_INTERFACE_WIDTH,
        MENU_HEIGHT * 2,
        1);
    DrawToolMenu();
    DrawTopMenu();
}

void DrawTopMenu()
{
    setButtonColors("White", "Black", "Blue", "White", 1);
    if (button(GenUIID(0),
               MENU_WIDTH * 0,
               MAIN_INTERFACE_HEIGHT - MENU_HEIGHT,
               MENU_WIDTH,
               MENU_HEIGHT,
               "Save"))
    {
        if (BACK_Save())
        {
            FRONT_Alart("Save Succeed!");
        }
        else
        {
            FRONT_Alart("Save Failed!");
        }
    }
    if (button(GenUIID(0),
               MENU_WIDTH * 1,
               MAIN_INTERFACE_HEIGHT - MENU_HEIGHT,
               MENU_WIDTH,
               MENU_HEIGHT,
               "About"))
    {
        FRONT_Alart("Author: cjy");
    }

    /* 下面是用menu写的代码 */
    // char *menuListFile[] = {"File",
    //                         "Save"};
    // char *menuListHelp[] = {"Help",
    //                         "About"};

    // char *selectedLabel = NULL;
    // int selection;

    // setMenuColors("White", "Black", "Blue", "White", 1);
    // selection = menuList(GenUIID(0),
    //                      MENU_WIDTH * 0,
    //                      MAIN_INTERFACE_HEIGHT - MENU_HEIGHT,
    //                      MENU_WIDTH,
    //                      MENU_WIDTH,
    //                      MENU_HEIGHT,
    //                      menuListFile,
    //                      sizeof(menuListFile) / sizeof(menuListFile[0]));

    // if (selection == 1)
    // {
    //     FRONT_Alart("save");
    // }

    // selection = menuList(GenUIID(0),
    //                      MENU_WIDTH * 1,
    //                      MAIN_INTERFACE_HEIGHT - MENU_HEIGHT,
    //                      MENU_WIDTH,
    //                      MENU_WIDTH,
    //                      MENU_HEIGHT,
    //                      menuListHelp,
    //                      sizeof(menuListHelp) / sizeof(menuListHelp[0]));

    // if (selection == 1)
    // {
    //     FRONT_Alart("About");
    // }

    // /* menu box */
    // SetPenColor("Black");
    // SetPenSize(1);
    // drawRectangle(
    //     0,
    //     MAIN_INTERFACE_HEIGHT - MENU_HEIGHT,
    //     MAIN_INTERFACE_WIDTH,
    //     MENU_HEIGHT,
    //     0);
}

void DrawToolMenu()
{
    /* mouse move */
    setButtonColors("White", "Black", "Blue", "White", 1);
    SetPenColor("Black");
    SetPenSize(5);
    if (button(GenUIID(0),
               MENU_WIDTH * 0,
               MAIN_INTERFACE_HEIGHT - MENU_HEIGHT * 2,
               MENU_WIDTH,
               MENU_HEIGHT,
               "Move"))
    {
        // FRONT_Alart("Move");
        FRONT_Main2d_CurTool = MOVE_TOOL;
    }

    char *menuListPoint[] = {
        "Point",
        "OrdinaryPoint",
        "MiddlePoint"};
    char *menuListLine[] = {
        "Line",
        "OrdinaryLine",
        "LineSegment"};
    char *menuListPolygon[] = {
        "Polygon",
        "OrdinaryPolygon",
        "RegularPolygon"};
    char *menuListCircle[] = {
        "Circle",
        "CenterPointCircle",
        "ThreePointCircle"};
    char *menuListCurve[] = {
        "Curve",
        "FunctionCurve",
        "EquationCurve"};

    int selection;

    setMenuColors("Black", "Black", "Blue", "Blue", 0);
    SetPenSize(5);

    selection = menuList(GenUIID(0),
                         MENU_WIDTH * 1,
                         MAIN_INTERFACE_HEIGHT - MENU_HEIGHT * 2,
                         MENU_WIDTH,
                         MENU_WIDTH,
                         MENU_HEIGHT,
                         menuListPoint,
                         sizeof(menuListPoint) / sizeof(menuListPoint[0]));

    if (selection == 1)
    {
        // FRONT_Alart("OrdinaryPoint");
        FRONT_Main2d_CurTool = ORDINARY_POINT_TOOL;
    }
    else if (selection == 2)
    {
        // FRONT_Alart("MiddlePoint");
        FRONT_Main2d_CurTool = MIDDLE_POINT_TOOL;
    }
    selection = menuList(GenUIID(0),
                         MENU_WIDTH * 2,
                         MAIN_INTERFACE_HEIGHT - MENU_HEIGHT * 2,
                         MENU_WIDTH,
                         MENU_WIDTH,
                         MENU_HEIGHT,
                         menuListLine,
                         sizeof(menuListLine) / sizeof(menuListLine[0]));

    if (selection == 1)
    {
        // FRONT_Alart("OrdinaryLine");
        FRONT_Main2d_CurTool = ORDINARY_LINE_TOOL;
    }
    else if (selection == 2)
    {
        // FRONT_Alart("LineSegment");
        FRONT_Main2d_CurTool = LINE_SEGMENT_TOOL;
    }
    selection = menuList(GenUIID(0),
                         MENU_WIDTH * 3,
                         MAIN_INTERFACE_HEIGHT - MENU_HEIGHT * 2,
                         MENU_WIDTH,
                         MENU_WIDTH,
                         MENU_HEIGHT,
                         menuListPolygon,
                         sizeof(menuListPolygon) / sizeof(menuListPolygon[0]));

    if (selection == 1)
    {
        // FRONT_Alart("OrdinaryPolygon");
        FRONT_Main2d_CurTool = ORDINARY_POLYGON_TOOL;
    }
    else if (selection == 2)
    {
        // FRONT_Alart("RegularPolygon");
        FRONT_Main2d_CurTool = REGULAR_POLYGON_TOOL;
    }

    selection = menuList(GenUIID(0),
                         MENU_WIDTH * 4,
                         MAIN_INTERFACE_HEIGHT - MENU_HEIGHT * 2,
                         MENU_WIDTH,
                         MENU_WIDTH,
                         MENU_HEIGHT,
                         menuListCircle,
                         sizeof(menuListCircle) / sizeof(menuListCircle[0]));

    if (selection == 1)
    {
        // FRONT_Alart("CenterAndPointCircle");
        FRONT_Main2d_CurTool = CENTER_POINT_CIRCLE_TOOL;
    }
    else if (selection == 2)
    {
        // FRONT_Alart("ThreePointCircle");
        FRONT_Main2d_CurTool = THREE_POINT_CIRCLE_TOOL;
    }

    selection = menuList(GenUIID(0),
                         MENU_WIDTH * 5,
                         MAIN_INTERFACE_HEIGHT - MENU_HEIGHT * 2,
                         MENU_WIDTH,
                         MENU_WIDTH,
                         MENU_HEIGHT,
                         menuListCurve,
                         sizeof(menuListCurve) / sizeof(menuListCurve[0]));

    if (selection == 1)
    {
        BACK_FunctionCurve_DetectOperation();
    }
    else if (selection == 2)
    {
        BACK_EquationCurve_DetectOperation();
    }
}

void DrawEditWindowOneInfo(BACK_Geobj *p_gb)
{
    static long curFrameCount = 0;
    static int drawTimes = 1;

    /* 判断是否为新帧 */
    if (curFrameCount != FRONT_frameCount)
    {
        drawTimes = 1;
        curFrameCount = FRONT_frameCount;
    }
    else
    {
        drawTimes++;
    }

    char *info = BACK_Geobj_Info(p_gb);
    SetPenSize(1);
    SetPointSize(1);
    drawBox(
        0,
        EDIT_WINDOW_HEIGHT - EDIT_WINDOW_ITEM_HEIGHT * drawTimes,
        EDIT_WINDOW_WIDTH,
        EDIT_WINDOW_ITEM_HEIGHT,
        0,
        info,
        'C',
        "Black");
    free(info);
}

void DrawEditWindow()
{
    /* 绘制边框 */
    SetPenColor("White");
    SetPenSize(5);
    drawRectangle(
        0,
        0,
        EDIT_WINDOW_WIDTH,
        EDIT_WINDOW_HEIGHT,
        1);
    SetPenColor("Black");
    SetPenSize(5);
    drawRectangle(
        0,
        0,
        EDIT_WINDOW_WIDTH,
        EDIT_WINDOW_HEIGHT,
        0);

    /* 绘制几何对象详细信息 */
    BACK_GeobjList *p_gbl = BACK_GetGeobjList();
    BACK_GeobjList_Traverse(p_gbl, DrawEditWindowOneInfo);
}

void FRONT_Main2d_MouseEventProcess(int button, int event)
{
    FRONT_Main2dShow_MouseEventProcess(button, event);
}
void FRONT_Main2d_Init()
{
    FRONT_Main2d_CurTool = MOVE_TOOL;

    FRONT_Main2dShow_Init();
}

void FRONT_Main2d_TimerEventProcess()
{
    FRONT_Main2dShow_TimerEventProcess();
}