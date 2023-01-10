#pragma  once
#ifndef GETMOUSEDATA_H
#define GETMOUSEDATA_H
#include <QObject>
#include <QQuickItem>
#include <QThread>
#include <Windows.h>
#pragma comment(lib,"User32.lib")
#pragma comment(lib,"Kernel32.lib")
#pragma comment(lib,"Gdi32.lib")



class GetMouseData : public QThread
{
    Q_OBJECT
protected:
    void run() override;
public:
    GetMouseData();
    int getx();
    int gety();
    void init();
};

#endif // GETMOUSEDATA_H
