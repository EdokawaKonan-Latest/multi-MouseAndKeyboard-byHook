#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <Header/dllmain.h>
#include <Header/data.h>
extern DWORD g_thread_id;

int main(int argc, char *argv[])
{


    QGuiApplication  app(argc, argv);
    QQmlApplicationEngine engine;
    //C++与qt交互
    qmlRegisterType<Data>("GetMouseData", 1, 0, "GetMouseData");
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;
    g_thread_id = GetCurrentThreadId();
    qDebug() <<GetCurrentThreadId();
    return app.exec();
}
