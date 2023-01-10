#pragma once
#include "getmousedata.h"
#include <Header/dllmain.h>


//声明Dll句柄

HMODULE hDll = NULL;

HWND hWnd = NULL;
const char * title ="RawInputDemo2022";
//多线程run
void GetMouseData::run()
{
    do
    {
        qDebug() <<"finding";
        hWnd = ::FindWindowA(NULL, title);//找到qml窗口 并且勾住
        Sleep(1);
    } while(hWnd==GetDesktopWindow());//只要是windows窗口,我就一直找就完了
    //鼠标信息的注册
    RawRegister(hWnd);
    while(1)
    {
        //输出鼠标的信息
        for (int p = 0; p < GetDeviceCount() ; p++)
        {
            qDebug() << "Mouse Data:" << p <<GetData(p,1) << GetData(p,0);
        }
        qDebug() << "Device Count" << GetDeviceCount();;
        Sleep(1000);
    }
}
GetMouseData::GetMouseData()
{

    //return GetData(p,1);
}

int GetMouseData::getx()
{
    return 0;
    //return GetData(p,1)
}

int GetMouseData::gety()
{
    return 0;
}

void GetMouseData::init()
{
    this->start();
}
