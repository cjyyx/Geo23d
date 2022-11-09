#ifndef FRONT_FILE_H
#define FRONT_FILE_H

/* 一个文件对话框，询问打开哪个文件，返回打开文件的地址到path
点击取消返回0 */
int FRONT_OpenFileDialog(char *path);

/* 一个文件夹对话框，询问打开哪个文件夹，返回打开文件夹的地址到path
点击取消返回0 */
int FRONT_OpenFileFolderDialog(char *path);

/* 一个文件对话框，询问保存文件到哪和文件名，返回保存文件路径到path
点击取消返回0 */
int FRONT_SaveFileDialog(char *path);

#endif