#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "TagManager.h"
#include "SimulatorManager.h"
#include "TemperatureSimulator.h"
#include "SensorSimulator.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    TagManager tagManager;

    // --- Теги с симуляцией ---
    Tag* tempTag = tagManager.createTag("Temperature", 0.0, 1, "temperature");
    Tag* pressureTag = tagManager.createTag("Pressure", 0.0, 2, "pressure");

    // --- Теги без симуляции ---
    Tag* staticTag1 = tagManager.createTag("Setpoint", 55.0, 3, "input");
    Tag* staticTag2 = tagManager.createTag("Status", 1.0, 4, "state");

    // --- Запуск симуляторов ---
    SimulatorManager simManager;
    simManager.addSimulator(new TemperatureSimulator(tempTag));
    simManager.addSimulator(new TemperatureSimulator(pressureTag)); // условный повтор для примера

    simManager.startAll();

    // --- Привязка в QML ---
    engine.rootContext()->setContextProperty("tagManager", &tagManager);

    const QUrl url(u"qrc:/qml/main.qml"_qs);
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
                         if (!obj && url == objUrl)
                             QCoreApplication::exit(-1);
                     }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
