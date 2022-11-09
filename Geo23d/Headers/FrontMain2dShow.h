#ifndef FRONT_MAIN2D_SHOW_H
#define FRONT_MAIN2D_SHOW_H
#include "Back.h"

#define FRONT_Main2dShow_SELECTED_GEOBJ_LEN_MAX 10

/* showInterface状态分类 */
enum
{
    DEFAULT_STATE,             // 0
    LOSE_FOCUS_STATE,          //失去焦点，失去关注
    MOUSE_DISENGAGEMENT_STATE, //鼠标脱离
    NO_ACTION_STATE,           //鼠标无动作
    CLICK_STATE,               //单击状态
    DRAG_SHOW_INTERFACE_STATE, //鼠标移动，按键处于按下状态且为左键，且那一帧没有选中任何几何对象；此时认为是拖动showInterface
    DRAG_GEOBJ_STATE           //鼠标移动，按键处于按下状态且为左键，且那一帧选中了几何对象；此时认为是拖动几何对象
};
int FRONT_Main2dShow_GetCurShowInterfaceState();

/* 初始化展示窗口 */
void FRONT_Main2dShow_Init();
/* draw展示窗口 */
void FRONT_Main2dShow_Display();
/* ShowWindow鼠标事件处理 */
void FRONT_Main2dShow_MouseEventProcess(int button, int event);
/* ShowWindow定时器事件处理 */
void FRONT_Main2dShow_TimerEventProcess();

/* 利用虚拟坐标系画一个点 */
void FRONT_Main2dShow_DrawPoint(double x_im, double y_im, int size);
/* 利用虚拟坐标系画一条线 */
void FRONT_Main2dShow_DrawLine(double x1_im, double y1_im, double x2_im, double y2_im);
/* 利用虚拟坐标系画文字 */
void FRONT_Main2dShow_DrawText(double x_im, double y_im, char *text);
/* 利用虚拟坐标系画圆弧
x_im,y_im 圆心位置
startAngle起始角度
sweep弧度 */
void FRONT_Main2dShow_DrawArc(double x_im, double y_im, double r, double startAngle, double sweep);

/* 获得鼠标虚拟坐标，非窗口坐标 */
void FRONT_Main2dShow_GetMouseIm(double *mouseImX, double *mouseImY);
/* 获得可视坐标范围,注意是虚拟坐标
double visualCoord2DRangeX[2],visualCoord2DRangeY[2]; */
void FRONT_Main2dShow_GetVisualRange(double *vx, double *vy);

/* showInterface伸缩系数 */
void FRONT_Main2dShow_GetCooedExpansion(double *cex, double *cey);

/* 获得记录选中的几何对象 */
BACK_Geobj **FRONT_Main2dShow_GetAnSelectedGeobj();
/* 获得这一帧选中的几何对象 */
BACK_Geobj *FRONT_Main2dShow_GetSelectedGeobjThisFrame();
/* 清空选中的几何对象数组 */
void FRONT_Main2dShow_AnSelectedGeobj_Clear();
/* 选中的几何对象数组添加 */
void FRONT_Main2dShow_AnSelectedGeobj_Enter(BACK_Geobj *p_gb);
/* 获得选中的几何对象数组长度 */
int FRONT_Main2dShow_AnSelectedGeobj_Len();

#endif