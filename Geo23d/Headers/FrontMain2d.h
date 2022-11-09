#ifndef FRONT_MAIN2D_H
#define FRONT_MAIN2D_H
#include "Front.h"

/* menu height */
#define MENU_HEIGHT 0.3
#define MENU_WIDTH 2.2

/* EditWindow config */
#define EDIT_WINDOW_WIDTH (MAIN_INTERFACE_WIDTH * 0.3)
#define EDIT_WINDOW_HEIGHT (MAIN_INTERFACE_HEIGHT - MENU_HEIGHT * 2)
#define EDIT_WINDOW_ITEM_HEIGHT 0.3

/* ShowWindow config */
#define SHOW_WINDOW_WIDTH (MAIN_INTERFACE_WIDTH - EDIT_WINDOW_WIDTH)
#define SHOW_WINDOW_HEIGHT SHOW_WINDOW_WIDTH
// #define SHOW_WINDOW_HEIGHT (MAIN_INTERFACE_HEIGHT - MENU_HEIGHT * 2)

/* tool id */
enum
{
    DEFAULR_TOOL,
    MOVE_TOOL,
    ORDINARY_POINT_TOOL,
    MIDDLE_POINT_TOOL,
    ORDINARY_LINE_TOOL,
    LINE_SEGMENT_TOOL,
    ORDINARY_POLYGON_TOOL,
    REGULAR_POLYGON_TOOL,
    CENTER_POINT_CIRCLE_TOOL,
    THREE_POINT_CIRCLE_TOOL
};
extern const char *A_TOOL_NAME[];

/* Main2dInterface init */
void FRONT_Main2d_Init();
/* display main interface 2d */
void FRONT_Main2d_Display();
/* Main2dInterface鼠标事件处理 */
void FRONT_Main2d_MouseEventProcess(int button, int event);
/* Main2dInterface定时器事件处理 */
void FRONT_Main2d_TimerEventProcess();

extern int FRONT_Main2d_CurTool;

#endif