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
        if(i == 1) {
            emit countOne();
            add[i] = true;
        }
        else if(i == 2) {
            emit countTwo();
            add[i] = true;
        } else if(i == 3) {
            emit countThree();
            add[i] = true;
        } else if(i == 4) {
            emit countFour();
            add[i] = true;
        }
    }
}
//多线程run
void GetMouseData::run() {
    do {
        hWnd = ::FindWindowA(NULL, title);//找到qml窗口 并且勾住
        Sleep(1);
    } while(hWnd==GetDesktopWindow());//只要是windows窗口,我就一直找就完了
    //鼠标信息的注册
    RawRegister(hWnd);
    while(1) {
        //输出鼠标的信息
        countAdd(mouseCount());
        emit mouse();
        Sleep(10);
    }
}
GetMouseData::GetMouseData() {

}
//获取鼠标按键信息
unsigned long long GetMouseData::getButton(int p) {
    return  GetMouseButton(p);
}
unsigned short GetMouseData::getDistance(int p) {
    return GetDistance(p);
}
//获取鼠标x坐标
int GetMouseData::getX(int p) {
    return GetData(p, 1);
}
//获取鼠标y坐标
int GetMouseData::getY(int p) {
    return GetData(p, 0);
}
//获取鼠标设备个数
int GetMouseData::mouseCount() {
    return GetMouseCount();
}
//设置鼠标1状态
int GetMouseData::setMouse(int id, int i) {
    if(i == 1) { //鼠标id   第i种状态
        PositiveDirectionX(id);
        PositiveDirectionY(id);
        return 1;
    }
    else if(i == 2) { //
        PositiveDirectionX(id);
        OppositeDirectionY(id);
        return 2;
    }
    else if(i == 3) {
        OppositeDirectionX(id);
        OppositeDirectionY(id);
        return 3;
    }
    else if(i == 4) {
        OppositeDirectionX(id);
        PositiveDirectionY(id);
        return 4;
    }
}
int arr[10];
int GetMouseData::getKind(int id) { //获取鼠标种类
    return arr[id];
}
//更改鼠标移动方向
void GetMouseData::init() {
    arr[0] = setMouse(0, 1);
    arr[1] = setMouse(1, 1);
    arr[2] = setMouse(2, 1);
    arr[3] = setMouse(3, 1);
    this->start();
}
