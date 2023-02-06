
#pragma  once
#ifndef GETMOUSEDATA_H
#define GETMOUSEDATA_H
#include <QObject>
#include <QQuickItem>
#include <QThread>
#include <Windows.h>
//下面这个一定不能加
//#include <Header/dllmain.h>
#pragma comment(lib,"User32.lib")
#pragma comment(lib,"Kernel32.lib")
#pragma comment(lib,"Gdi32.lib")

class Data : public QThread
{
    Q_OBJECT
protected:
    //声明Dll句柄
    HMODULE hDll = NULL;
    HWND hWnd = NULL;
    const char * title ="RawInputDemo2022";
    bool add[6] = {0};
    int arr[10] = {0};
    //鼠标出现以及坐标初始化信号
    //存储鼠标数据
        struct MouseData {
            int x = 0;//鼠标x
            int y = 0;//鼠标y
            unsigned long long button = 0;//按键状态
            unsigned short distance = 0;//
        }mouseData[5];

        //存储键盘数据
        struct KeyWord {
            QString str = "";
        }keyWord[5];
    void run() override;
public:
    Data();
    ~Data();
    Q_INVOKABLE int getX(int p);
    Q_INVOKABLE int getY(int p);
    Q_INVOKABLE int mouseCount();
    Q_INVOKABLE unsigned long long getButton(int p);
    Q_INVOKABLE void init();
    Q_INVOKABLE unsigned short getDistance(int p);
    Q_INVOKABLE int getKind(int id);
    Q_INVOKABLE QString getKeyString(int p);
    void getAllData();
    void countAdd(int i );
signals:
    void mouse();
    void countOne();
    void countTwo();
    void countThree();
    void countFour();
};

#endif // GETMOUSEDATA_H
