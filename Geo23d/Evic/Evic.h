#ifndef EVIC_H
#define EVIC_H
#include <stdlib.h>

#define MAX_TOKEN_LEN 16

#define EVIC_DEBUG_MODE 0

/* �ַ����� */
typedef struct
{
    int TokenClass;
    void *next;

    double number;
    char op[4];
    char token[MAX_TOKEN_LEN];
    double *val;
    double (*pfunc)(double x);
} Token;

/* ���ʽ���� */
typedef struct
{
    /* ָ��ͷ���ַ� */
    Token *head;
    /* �Ƿ񱻱���Ϊ��׺���ʽ */
    int compiled;
} EVIC_expr;

/* ������eval�Ա��ʽ��ֵ
expr�Ǳ��ʽ�ַ�����reBuf��Ž��
�ɹ���1��ʧ�ܷ�0 */
int EVIC_Eval(char *expr, double *rtBuf);

/* ��������ʼ�����ʽ����
����׺���ʽ�и��һ�����ַ������ֶ��󣬴���ڱ��ʽ������
�ɹ���1��ʧ�ܷ�0 */
int EVIC_Cut(char *expr, EVIC_expr **ec_expr);

/* ��ӡ���ʽ�����ڿ��У��ǵ�free
ʧ�ܷ�NULL */
char *EVIC_Print(EVIC_expr *ec_expr);

/* �����ʽ���ַ��������ϵ
�ɹ���1��ʧ�ܷ�0 */
int EVIC_ValueLink(EVIC_expr *ec_expr, char *tk, double *val);

/* �����ʽ���ַ��������ϵ
�ɹ���1��ʧ�ܷ�0 */
int EVIC_ConstLink(EVIC_expr *ec_expr, char *tk, double ct);

/* �����ʽ���ַ��뺯����ϵ
�ɹ���1��ʧ�ܷ�0 */
int EVIC_FuncLink(EVIC_expr *ec_expr, char *tk, double (*pfunc)(double x));

/* ����ַ�����ϵ��ת��Ϊ��׺���ʽ
�ɹ���1��ʧ�ܷ�0 */
int EVIC_Compile(EVIC_expr **ec_expr);

/* �Ա��ʽ����
�ɹ���1��ʧ�ܷ�0 */
int EVIC_Calculate(EVIC_expr *ec_expr, double *rt);

/* �ͷű��ʽ�ռ�
�ɹ���1��ʧ�ܷ�0 */
int EVIC_Free(EVIC_expr *ec_expr);

#endif