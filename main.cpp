#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <windows.h>
#include <Header/dllmain.h>
#include <Header/getmousedata.h>
char *argv[10];

extern DWORD ThreadID;
class MQGuiApplication : public QGuiApplication
{
public:
    MQGuiApplication(int argc,char* argv[]) : QGuiApplication(argc,argv)
    {

    }

    bool  winEventFilter(MSG *msg, long *result);
};
bool MQGuiApplication::winEventFilter(MSG *msg, long *result) {
    qDebug()<<"Hello";

    return false;
}

int main(int argc, char *argv[])
{
    QGuiApplication  app(argc, argv);
    QQmlApplicationEngine engine;

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;
    ThreadID = GetCurrentThreadId();
    GetMouseData g;
    g.init();
    return app.exec();
}
