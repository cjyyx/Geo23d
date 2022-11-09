#include <windows.h>
#include "FrontInput.h"
#include <stdio.h>
#include <string.h>
#include <strlib.h>
#include <stdlib.h>

#define INPUT_BOX_CLASS_NAME "Geo23d_InputBox"

#define INPUT_BOX_X 300
#define INPUT_BOX_Y 200
#define INPUT_BOX_W 400
#define INPUT_BOX_H 200

#define LABEL_X 100
#define LABEL_Y 20
#define LABEL_W 200
#define LABEL_H 40

#define EDIT_X 100
#define EDIT_Y 80
#define EDIT_W 200
#define EDIT_H 20

#define OK_X 170
#define OK_Y 120
#define OK_W 60
#define OK_H 30

#define INPUT_MAX_LEN 100

static WNDCLASSA wc = {0};
static HWND editHandle;
static int is_run;
static char *inputContent;

/* 参考资料
http://c.biancheng.net/cpp/html/2961.html
https://docs.microsoft.com/en-us/windows/win32/controls/using-buttons
https://zhuanlan.zhihu.com/p/353558221
 */

LRESULT CALLBACK InputBoxWndProc(HWND hWnd, UINT msgID, WPARAM wParam, LPARAM lParam)
{
    int wmId, wmEvent;
    HBRUSH hBrush; //画刷
    switch (msgID)
    {
    case WM_CLOSE:
        DestroyWindow(hWnd);
        break;
    case WM_COMMAND:
        wmId = LOWORD(wParam);
        wmEvent = HIWORD(wParam);
        switch (wmEvent)
        {
        case BN_CLICKED:
            GetWindowText(editHandle, inputContent, INPUT_MAX_LEN);
            DestroyWindow(hWnd);
            break;
        default:
            break;
        }
        break;

    case WM_CTLCOLORSTATIC:
        //创建画刷
        hBrush = CreateSolidBrush(RGB(0xff, 0xff, 0xff));
        return (INT_PTR)hBrush;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, msgID, wParam, lParam);
    }
}

void FRONT_Input_Init()
{
    is_run = 0;

    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = InputBoxWndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = GetModuleHandle(NULL);
    wc.hIcon = NULL;
    wc.hCursor = NULL;
    wc.hbrBackground = (HBRUSH)COLOR_WINDOWFRAME;
    wc.lpszMenuName = NULL;
    wc.lpszClassName = INPUT_BOX_CLASS_NAME;

    if (!RegisterClass(&wc))
    {
        MessageBox(NULL, "InputBox Registration Failed!", "Error!",
                   MB_ICONEXCLAMATION | MB_OK);
    }
}

HWND dialog_init(char *text)
{
    HWND dialog_hWnd = CreateWindow(
        wc.lpszClassName,
        "InputBox",
        WS_DLGFRAME,
        INPUT_BOX_X, INPUT_BOX_Y, INPUT_BOX_W, INPUT_BOX_H,
        0, 0, wc.hInstance, NULL);

    if (dialog_hWnd == NULL)
    {
        MessageBox(NULL, "InputBoxWindow Creation Failed!", "Error!",
                   MB_ICONEXCLAMATION | MB_OK);
        return NULL;
    }

    HWND LabelHandle = CreateWindow(
        "STATIC",
        text,
        WS_CHILD | WS_VISIBLE | SS_CENTER,
        LABEL_X, LABEL_Y, LABEL_W, LABEL_H,
        dialog_hWnd, 0, wc.hInstance, 0);

    editHandle = CreateWindow(
        "EDIT",
        "",
        WS_BORDER | WS_CHILD | WS_VISIBLE,
        EDIT_X, EDIT_Y, EDIT_W, EDIT_H,
        dialog_hWnd, 0, wc.hInstance, 0);

    HWND okButtonHandle = CreateWindow(
        "BUTTON",
        "OK",
        WS_CHILD | WS_VISIBLE,
        OK_X, OK_Y, OK_W, OK_H,
        dialog_hWnd, 0, wc.hInstance, 0);

    return dialog_hWnd;
}

char *FRONT_Input(char *text)
{
    if (is_run)
    {
        return NULL;
    }
    is_run = 1;

    inputContent = (char *)malloc(sizeof(INPUT_MAX_LEN));
    inputContent[0] = '\0';

    HWND dialog_hWnd = dialog_init(text);

    ShowWindow(dialog_hWnd, SW_SHOW);
    UpdateWindow(dialog_hWnd);

    MSG Msg = {0};
    while (GetMessage(&Msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&Msg);
        DispatchMessage(&Msg);
    }

    is_run = 0;

    return inputContent;
}