#include "FrontFile.h"

#include <Windows.h>
#include <commdlg.h>
#include <ShlObj.h>
#include <stdio.h>

int FRONT_OpenFileDialog(char *path)
{
    OPENFILENAME ofn;
    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.lpstrFile = path;
    ofn.nMaxFile = MAX_PATH;
    ofn.lpstrFilter = "GEO2(*.geo2)\0*.geo2\0";
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
    return GetOpenFileName(&ofn);
}

int FRONT_SaveFileDialog(char *path)
{
    OPENFILENAME ofn;
    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.lpstrFile = path;
    ofn.nMaxFile = MAX_PATH;
    ofn.lpstrFilter = "GEO2(*.geo2)\0*.geo2\0";
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
    return GetSaveFileName(&ofn);
}

int FRONT_OpenFileFolderDialog(char *path)
{
    BROWSEINFO bInfo = {0};
    bInfo.hwndOwner = GetForegroundWindow(); //父窗口
    bInfo.lpszTitle = TEXT("Browse File Folder");
    bInfo.ulFlags = BIF_RETURNONLYFSDIRS | BIF_USENEWUI /*包含一个编辑框 用户可以手动填写路径 对话框可以调整大小之类的..*/ |
                    BIF_UAHINT /*带TIPS提示*/;
    LPITEMIDLIST lpDlist;
    lpDlist = SHBrowseForFolder(&bInfo);
    if (lpDlist != NULL)
    {
        SHGetPathFromIDList(lpDlist, path);
        return 1;
    }
    else
    {
        return 0;
    }
}