#ifndef FRONT_H
#define FRONT_H

#define APP_NAME "geo23d"

/* 是否以debug模式运行 */
#define FRONT_DEBUG_MODE 0
#define FRONT_CONSOLE_LOG_MODE 1
/* 主界面的大小 */
#define MAIN_INTERFACE_WIDTH 14.0
#define MAIN_INTERFACE_HEIGHT 10.0

#include "FrontInput.h"
#include "FrontFile.h"

/* 界面ID */
enum
{
    DEFAULT_INTERFACE,
    START_INTERFACE,
    MAIN_INTERFACE_2D,
    INPUT_INTERFACE
};

/* 前端初始化 */
void FRONT_Init();
/* 绘制整个界面 */
void FRONT_Display();
/* 设置显示界面 */
void FRONT_SetInterface(int interfaceId);
/* 前端信息 */
void FRONT_Info(char *infoBuf);

/* 弹窗，text是说明内容 */
void FRONT_Alart(char *text);


/* 记录是否处于鼠标按下的状态 */
extern int FRONT_buttonDownState;
/* 记录display次数 */
extern long FRONT_frameCount;
/* get mouseReX, mouseReY */
void FRONT_GetMouseReVal(double *mx_re, double *my_re);

#endif