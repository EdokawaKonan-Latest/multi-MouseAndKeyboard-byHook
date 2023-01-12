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
    Q_INVOKABLE int getX(int p);
    Q_INVOKABLE int getY(int p);
    Q_INVOKABLE int mouseCount();
    Q_INVOKABLE unsigned long long getButton(int p);
    Q_INVOKABLE void init();
    Q_INVOKABLE unsigned short getDistance(int p);
    Q_INVOKABLE int setMouse(int id, int i);
    Q_INVOKABLE int getKind(int id);
    void countAdd(int i );
signals:
    void mouse();
    void countOne();
    void countTwo();
    void countThree();
    void countFour();
};

#endif // GETMOUSEDATA_H
