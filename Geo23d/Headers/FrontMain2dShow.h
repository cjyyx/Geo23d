#ifndef FRONT_MAIN2D_SHOW_H
#define FRONT_MAIN2D_SHOW_H
#include "Back.h"

#define FRONT_Main2dShow_SELECTED_GEOBJ_LEN_MAX 10

/* showInterface״̬���� */
enum
{
    DEFAULT_STATE,             // 0
    LOSE_FOCUS_STATE,          //ʧȥ���㣬ʧȥ��ע
    MOUSE_DISENGAGEMENT_STATE, //�������
    NO_ACTION_STATE,           //����޶���
    CLICK_STATE,               //����״̬
    DRAG_SHOW_INTERFACE_STATE, //����ƶ����������ڰ���״̬��Ϊ���������һ֡û��ѡ���κμ��ζ��󣻴�ʱ��Ϊ���϶�showInterface
    DRAG_GEOBJ_STATE           //����ƶ����������ڰ���״̬��Ϊ���������һ֡ѡ���˼��ζ��󣻴�ʱ��Ϊ���϶����ζ���
};
int FRONT_Main2dShow_GetCurShowInterfaceState();

/* ��ʼ��չʾ���� */
void FRONT_Main2dShow_Init();
/* drawչʾ���� */
void FRONT_Main2dShow_Display();
/* ShowWindow����¼����� */
void FRONT_Main2dShow_MouseEventProcess(int button, int event);
/* ShowWindow��ʱ���¼����� */
void FRONT_Main2dShow_TimerEventProcess();

/* ������������ϵ��һ���� */
void FRONT_Main2dShow_DrawPoint(double x_im, double y_im, int size);
/* ������������ϵ��һ���� */
void FRONT_Main2dShow_DrawLine(double x1_im, double y1_im, double x2_im, double y2_im);
/* ������������ϵ������ */
void FRONT_Main2dShow_DrawText(double x_im, double y_im, char *text);
/* ������������ϵ��Բ��
x_im,y_im Բ��λ��
startAngle��ʼ�Ƕ�
sweep���� */
void FRONT_Main2dShow_DrawArc(double x_im, double y_im, double r, double startAngle, double sweep);

/* �������������꣬�Ǵ������� */
void FRONT_Main2dShow_GetMouseIm(double *mouseImX, double *mouseImY);
/* ��ÿ������귶Χ,ע������������
double visualCoord2DRangeX[2],visualCoord2DRangeY[2]; */
void FRONT_Main2dShow_GetVisualRange(double *vx, double *vy);

/* showInterface����ϵ�� */
void FRONT_Main2dShow_GetCooedExpansion(double *cex, double *cey);

/* ��ü�¼ѡ�еļ��ζ��� */
BACK_Geobj **FRONT_Main2dShow_GetAnSelectedGeobj();
/* �����һ֡ѡ�еļ��ζ��� */
BACK_Geobj *FRONT_Main2dShow_GetSelectedGeobjThisFrame();
/* ���ѡ�еļ��ζ������� */
void FRONT_Main2dShow_AnSelectedGeobj_Clear();
/* ѡ�еļ��ζ���������� */
void FRONT_Main2dShow_AnSelectedGeobj_Enter(BACK_Geobj *p_gb);
/* ���ѡ�еļ��ζ������鳤�� */
int FRONT_Main2dShow_AnSelectedGeobj_Len();

#endif