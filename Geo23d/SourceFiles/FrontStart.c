#include "FrontStart.h"

#include <windows.h>
#include <winuser.h>

#include "graphics.h"
#include "extgraph.h"
#include "imgui.h"
#include "linkedlist.h"

#include "Back.h"
#include "Front.h"

/* 显示startInterface */
static void DisplayStartInterface();
/* new 2d project */
static void NewProject2D();
/* open project */
static void OpenProject();

void FRONT_Start_Init()
{
}

void FRONT_Start_Display()
{
    DisplayStartInterface();
}

/* 显示startInterface */
void DisplayStartInterface()
{
    // 开始界面边框
    SetPenColor("Black");
    SetPenSize(10);
    drawRectangle(
        (MAIN_INTERFACE_WIDTH - START_INTERFACE_WIDTH) / 2,
        (MAIN_INTERFACE_HEIGHT - START_INTERFACE_HEIGHT) / 2,
        START_INTERFACE_WIDTH,
        START_INTERFACE_HEIGHT,
        0);

    // 开始界面布局
    // title
    MovePen(
        MAIN_INTERFACE_WIDTH * 0.4,
        MAIN_INTERFACE_HEIGHT * 0.6);
    SetPointSize(100);
    DrawTextString("Start!");

    setButtonColors("White", "Black", "Blue", "White", 1);
    SetPenColor("Black");

    // new button

    SetPointSize(20);
    SetPenSize(5);
    if (button(GenUIID(0),
               MAIN_INTERFACE_WIDTH * 0.3,
               MAIN_INTERFACE_HEIGHT * 0.3,
               MAIN_INTERFACE_WIDTH * 0.1,
               MAIN_INTERFACE_HEIGHT * 0.05,
               "New"))
    {
        NewProject2D();
    }

    // open button
    if (button(GenUIID(0),
               MAIN_INTERFACE_WIDTH * 0.5,
               MAIN_INTERFACE_HEIGHT * 0.3,
               MAIN_INTERFACE_WIDTH * 0.1,
               MAIN_INTERFACE_HEIGHT * 0.05,
               "Open"))
    {
        OpenProject();
    }
}

/* new 2d project */
void NewProject2D()
{
    static int is_creating = 0;

    if (!is_creating)
    {
        is_creating = 1;

        char FilePath[MAX_PATH];
        FilePath[0] = '\0';

        if (FRONT_SaveFileDialog(FilePath))
        {
            if (BACK_Init(FilePath, 1))
            {
                FRONT_Alart("Creat Succeed!");
                FRONT_SetInterface(MAIN_INTERFACE_2D);
                FRONT_Main2d_Init();
            }
            else
            {
                FRONT_Alart("Creat Failed!");
            }
        }
        else
        {
            FRONT_Alart("Creat Failed!");
        }

        is_creating = 0;
    }
    else if (is_creating)
    {
        return;
    }
}

/* open project */
void OpenProject()
{
    static int is_creating = 0;

    if (!is_creating)
    {
        is_creating = 1;

        char FilePath[MAX_PATH];
        FilePath[0] = '\0';

        if (FRONT_OpenFileDialog(FilePath))
        {
            if (BACK_Init(FilePath, 0))
            {
                FRONT_Alart("Open Succeed!");
                FRONT_SetInterface(MAIN_INTERFACE_2D);
                FRONT_Main2d_Init();
            }
            else
            {
                FRONT_Alart("Open Failed!");
            }
        }
        else
        {
            FRONT_Alart("Open Failed!");
        }

        is_creating = 0;
    }
    else if (is_creating)
    {
        return;
    }
}