#ifndef FRONT_FILE_H
#define FRONT_FILE_H

/* һ���ļ��Ի���ѯ�ʴ��ĸ��ļ������ش��ļ��ĵ�ַ��path
���ȡ������0 */
int FRONT_OpenFileDialog(char *path);

/* һ���ļ��жԻ���ѯ�ʴ��ĸ��ļ��У����ش��ļ��еĵ�ַ��path
���ȡ������0 */
int FRONT_OpenFileFolderDialog(char *path);

/* һ���ļ��Ի���ѯ�ʱ����ļ����ĺ��ļ��������ر����ļ�·����path
���ȡ������0 */
int FRONT_SaveFileDialog(char *path);

#endif