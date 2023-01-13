#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <windows.h>
#include <Header/dllmain.h>
#include <Header/getmousedata.h>
#include <fstream>
extern DWORD g_thread_id;

int main(int argc, char *argv[])
{


    QGuiApplication  app(argc, argv);
    QQmlApplicationEngine engine;
    //C++”ÎqtΩªª•
    qmlRegisterType<GetMouseData>("GetMouseData", 1, 0, "GetMouseData");

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;
    g_thread_id = GetCurrentThreadId();

    return app.exec();
}
