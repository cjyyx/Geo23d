#include <windows.h>
#include <winuser.h>
#include "graphics.h"
#include "extgraph.h"
#include "imgui.h"
#include "linkedlist.h"

#include "Front.h"
#include "Back.h"
#include "FrontStart.h"

#include "FrontMain2d.h"
#include "FrontInput.h"

/* 用户的字符事件响应函数 */
static void CharEventProcess(char ch);
/* 用户的键盘事件响应函数 */
static void KeyboardEventProcess(int key, int event);
/* 用户的鼠标事件响应函数 */
static void MouseEventProcess(int x, int y, int button, int event);
/* 刷新计时器 */
#define REFRESH_TIMER_ID 0
#define REFRESH_INTERVAL 50
/* 用户的计时器时间响应函数 */
static void TimerEventProcess(int timerID);

/* 当前界面id */
static int en_currentInterface, en_curcurInterface;

/* Mouse real coord
不知道为什么，调用提供的getMouseXY函数会导致频闪，
只好自己写一个了(╬▔皿▔)╯ */
static double mouseReX, mouseReY;

/* 记录是否处于鼠标按下的状态 */
int FRONT_buttonDownState;
/* 判断是否处于鼠标按下的状态 */
static void buttonDownState_Judge(int event);

/* 记录display次数 */
long FRONT_frameCount;

void FRONT_Info(char *infoBuf)
{
    sprintf(
        infoBuf,
        "en_currentInterface: %d\n",
        en_currentInterface);
}

void FRONT_Init()
{
    /* first show StartInterface */
    if (!FRONT_DEBUG_MODE)
    {
        FRONT_SetInterface(START_INTERFACE);
        FRONT_Start_Init();
    }
    else
    {
        FRONT_SetInterface(MAIN_INTERFACE_2D);
        BACK_Init("", -1);
        FRONT_Main2d_Init();
    }

    FRONT_Input_Init();

    FRONT_buttonDownState = 0;

    FRONT_frameCount = 0;

    SetWindowTitle(APP_NAME);
    SetWindowSize(MAIN_INTERFACE_WIDTH, MAIN_INTERFACE_HEIGHT);
    InitGraphics();

    // 注册时间响应函数
    registerCharEvent(CharEventProcess);         // 字符
    registerKeyboardEvent(KeyboardEventProcess); // 键盘
    registerMouseEvent(MouseEventProcess);       // 鼠标
    registerTimerEvent(TimerEventProcess);       // 定时器

    // 开启定时器
    startTimer(REFRESH_TIMER_ID, REFRESH_INTERVAL);

    FRONT_Display();

    // char infoo[1000];
    // FRONT_Info(infoo);
    // printf("%s\n",infoo);
}

/* 用于显示,绘制整个界面 */
void FRONT_Display()
{
    switch (en_currentInterface)
    {
    case START_INTERFACE:
        DisplayClear();
        FRONT_Start_Display();
        break;

    case MAIN_INTERFACE_2D:
        DisplayClear();
        FRONT_Main2d_Display();
        break;
    default:
        break;
    }

    FRONT_frameCount++;
}

void FRONT_SetInterface(int interfaceId)
{
    en_currentInterface = interfaceId;
}

// 用户的字符事件响应函数
void CharEventProcess(char ch)
{
    uiGetChar(ch);   // GUI字符输入
    FRONT_Display(); //刷新显示
}

// 用户的键盘事件响应函数
void KeyboardEventProcess(int key, int event)
{
    uiGetKeyboard(key, event); // GUI获取键盘
    FRONT_Display();           // 刷新显示
}

void buttonDownState_Judge(int event)
{
    /* 用来判断按钮按下状态 */
    if (event == BUTTON_DOWN)
    {
        FRONT_buttonDownState = 1;
        // printf("down\t");
    }
    else if (event == BUTTON_UP)
    {
        FRONT_buttonDownState = 0;
        // printf("up\n");
    }
}

void FRONT_GetMouseReVal(double *mx_re, double *my_re)
{
    *mx_re = mouseReX;
    *my_re = mouseReY;
}

void MouseEventProcess(int x, int y, int button, int event)
{
    uiGetMouse(x, y, button, event); // GUI获取鼠标
    mouseReX = x / GetXResolution();
    mouseReY = MAIN_INTERFACE_HEIGHT - y / GetYResolution();

    buttonDownState_Judge(event);

    switch (en_currentInterface)
    {
    case MAIN_INTERFACE_2D:
        FRONT_Main2d_MouseEventProcess(button, event);
        break;

    default:
        break;
    }

    FRONT_Display(); // 刷新显示
}

// 用户的计时器时间响应函数
void TimerEventProcess(int timerID)
{

    if (timerID == REFRESH_TIMER_ID)
    {
        if (en_currentInterface == MAIN_INTERFACE_2D)
        {
            FRONT_Main2d_TimerEventProcess();
        }
        FRONT_Display();
    }
}

void FRONT_Alart(char *text)
{
    MessageBox(NULL, text, "FRONT_Alart", MB_OK);
}
