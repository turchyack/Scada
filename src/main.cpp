#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "TagManager.h"  // путь укажи правильно

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    TagManager tagManager;  // создаем экземпляр

    QQmlApplicationEngine engine;

    // Регистрируем в контексте QML
    engine.rootContext()->setContextProperty("tagManager", &tagManager);

    engine.load(QUrl(QStringLiteral("qrc:/qml/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
