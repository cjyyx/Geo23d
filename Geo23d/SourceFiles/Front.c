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

/* �û����ַ��¼���Ӧ���� */
static void CharEventProcess(char ch);
/* �û��ļ����¼���Ӧ���� */
static void KeyboardEventProcess(int key, int event);
/* �û�������¼���Ӧ���� */
static void MouseEventProcess(int x, int y, int button, int event);
/* ˢ�¼�ʱ�� */
#define REFRESH_TIMER_ID 0
#define REFRESH_INTERVAL 50
/* �û��ļ�ʱ��ʱ����Ӧ���� */
static void TimerEventProcess(int timerID);

/* ��ǰ����id */
static int en_currentInterface, en_curcurInterface;

/* Mouse real coord
��֪��Ϊʲô�������ṩ��getMouseXY�����ᵼ��Ƶ����
ֻ���Լ�дһ����(�p����)�s */
static double mouseReX, mouseReY;

/* ��¼�Ƿ�����갴�µ�״̬ */
int FRONT_buttonDownState;
/* �ж��Ƿ�����갴�µ�״̬ */
static void buttonDownState_Judge(int event);

/* ��¼display���� */
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

    // ע��ʱ����Ӧ����
    registerCharEvent(CharEventProcess);         // �ַ�
    registerKeyboardEvent(KeyboardEventProcess); // ����
    registerMouseEvent(MouseEventProcess);       // ���
    registerTimerEvent(TimerEventProcess);       // ��ʱ��

    // ������ʱ��
    startTimer(REFRESH_TIMER_ID, REFRESH_INTERVAL);

    FRONT_Display();

    // char infoo[1000];
    // FRONT_Info(infoo);
    // printf("%s\n",infoo);
}

/* ������ʾ,������������ */
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

// �û����ַ��¼���Ӧ����
void CharEventProcess(char ch)
{
    uiGetChar(ch);   // GUI�ַ�����
    FRONT_Display(); //ˢ����ʾ
}

// �û��ļ����¼���Ӧ����
void KeyboardEventProcess(int key, int event)
{
    uiGetKeyboard(key, event); // GUI��ȡ����
    FRONT_Display();           // ˢ����ʾ
}

void buttonDownState_Judge(int event)
{
    /* �����жϰ�ť����״̬ */
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
    uiGetMouse(x, y, button, event); // GUI��ȡ���
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

    FRONT_Display(); // ˢ����ʾ
}

// �û��ļ�ʱ��ʱ����Ӧ����
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
