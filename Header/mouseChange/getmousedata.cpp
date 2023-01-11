#pragma once
#include <Header/getmousedata.h>
#include <Header/dllmain.h>

//声明Dll句柄
HMODULE hDll = NULL;
HWND hWnd = NULL;
const char * title ="RawInputDemo2022";
bool add[6];
//鼠标出现以及坐标初始化信号
void GetMouseData::countAdd(int i) {
    if(add[i]) return;
    else {
        if(i == 1)
        {
            emit countOne();
            add[i] = true;
        }
        else if(i == 2)
        {
            emit countTwo();
            add[i] = true;
        }
        else if(i == 3)
        {
            emit countThree();
            add[i] = true;
        }
        else if(i == 4)
        {
            emit countFour();
            add[i] = true;
        }
    }
}
//多线程run
void GetMouseData::run()
{
    qDebug() << "hello";
    do
    {
        hWnd = ::FindWindowA(NULL, title);//找到qml窗口 并且勾住
        Sleep(1);
    } while(hWnd==GetDesktopWindow());//只要是windows窗口,我就一直找就完了
    //鼠标信息的注册
    RawRegister(hWnd);
    while(1) {
////        //输出鼠标的信息
//        for (int p = 0; p < GetDeviceCount() ; p++)
//        {
//            qDebug() << getButton(p);
//           // qDebug() << "Mouse Data:" << p <<GetData(p,1) << GetData(p,0);
//        }
//        qDebug() << endl;
        countAdd(mouseCount());

        emit mouse();
        Sleep(10);
    }
}
GetMouseData::GetMouseData()
{

}
//获取鼠标按键信息
unsigned long long GetMouseData::getButton(int p)
{
    return  GetButton(p);
}
unsigned short GetMouseData::getDistance(int p)
{
    return GetDistance(p);
}
//获取鼠标x坐标
int GetMouseData::getX(int p)
{
    return GetData(p, 1);
}
//获取鼠标y坐标
int GetMouseData::getY(int p)
{
    return GetData(p, 0);
}
//获取鼠标设备个数
int GetMouseData::mouseCount()
{
    return GetDeviceCount();
}

void GetMouseData::init()
{
    //x方向
    PositiveDirectionX(0);
    PositiveDirectionX(1);
    PositiveDirectionX(2);
    PositiveDirectionX(3);

    //y方向
    PositiveDirectionY(0);
    PositiveDirectionY(1);
    PositiveDirectionY(2);
    PositiveDirectionY(3);
    this->start();
}
