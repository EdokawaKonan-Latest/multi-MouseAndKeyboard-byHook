#pragma once
#include <Header/data.h>
#include <Header/dllmain.h>

//多线程run
void Data::run() {
    do {
        hWnd = ::FindWindowA(NULL, title);//找到qml窗口 并且勾住
        Sleep(1);
    } while(hWnd==GetDesktopWindow());//只要是windows窗口,我就一直找就完了
    //鼠标信息的注册
    RawRegister(hWnd);
    while(1) {
        countAdd(mouseCount());
        //      qDebug() << getKeyString(0);
        getAllData();
        emit mouse();
        Sleep(10);
    }
}
Data::Data() {}
Data::~Data() {
    quit();
    wait();
}

//全部数据获取
void Data::getAllData() {
    for(int i = 0; i < 4; i++) {
        //鼠标数据
        mouseData[i].x =  GetData(i, 1);
        mouseData[i].y =  GetData(i, 0);
        mouseData[i].distance = GetDistance(i);
        mouseData[i].button = GetMouseButton(i);
        //键盘数据
        keyWord[i].str = GetKeyString(i);
    }
}

void Data::countAdd(int i) {
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

//获取鼠标按键信息
unsigned long long Data::getButton(int p) {
    return  mouseData[p].button;
}

unsigned short Data::getDistance(int p) {
    return mouseData[p].distance;
}

//获取鼠标x坐标
int Data::getX(int p) {
    return mouseData[p].x;
}
//获取鼠标y坐标
int Data::getY(int p) {
    return mouseData[p].y;
}
//获取鼠标设备个数
int Data::mouseCount() {
    return GetMouseCount();
}
//设置鼠标1状态
int Data::getKind(int id) { //获取鼠标种类
    return arr[id];
}

//获取键盘数据
QString Data::getKeyString(int p) {
    return keyWord[p].str;
}

//更改鼠标移动方向
void Data::init() {
    KeyValueInit();
    //设置鼠标 1读 0写
    setMouseFlag(0);
    //设置键盘 1读 0写
    setKeyFlag(0);
    mouseIdInit();
    keyIdInit();
    arr[0] = setMouse(0, 1);
    arr[1] = setMouse(1, 1);
    arr[2] = setMouse(2, 1);
    arr[3] = setMouse(3, 1);
    this->start();
}
