#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQmlEngine>
#include <QDebug>

#include "TagManager.h"
#include "SimulatorManager.h"
#include "TemperatureSimulator.h"
#include "SensorSimulator.h"
#include "config/DeviceConfigLoader.h"
#include "device/DeviceConfig.h"
#include "model/DeviceListModel.h"
#include "model/DeviceViewModel.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    // Регистрируем типы для QML
    qmlRegisterType<DeviceListModel>("Scada", 1, 0, "DeviceListModel");
    qmlRegisterType<DeviceViewModel>("Scada", 1, 0, "DeviceViewModel");
    qmlRegisterType<TagListModel>("Scada", 1, 0, "TagListModel");

    TagManager tagManager;

    DeviceConfigLoader loader;
    QList<DeviceConfig> configs = loader.loadFromJsonFile("D:/Qtprojects/Scada/configs/device_config.json");
    SimulatorManager simManager;

    for (const DeviceConfig& cfg : configs) {
        qDebug() << "Загружено устройство:" << cfg.name << "тип:" << static_cast<int>(cfg.driveType);

        for (const TagConfig& tagCfg : cfg.tags) {
            QString tagName = QString("%1_%2").arg(cfg.name, tagCfg.name);
            Tag* tag = tagManager.createTag(tagName, tagCfg.value, tagCfg.address, tagCfg.type);

            // Подключаем симулятор, если указан
            if (tagCfg.simulator == "temperature") {
                simManager.addSimulator(new TemperatureSimulator(tag));
            } else if (tagCfg.simulator == "sensor") {
                simManager.addSimulator(new TemperatureSimulator (tag));
            }
        }
    }





    // // --- Теги с симуляцией ---
    // Tag* tempTag = tagManager.createTag("Temperature", 0.0, 15, "temperature");
    // Tag* pressureTag = tagManager.createTag("Pressure", 0.0, 16, "pressure");

    // // --- Теги без симуляции ---
    // Tag* staticTag1 = tagManager.createTag("Setpoint", 55.0, 17, "input");
    // Tag* staticTag2 = tagManager.createTag("Status", 1.0, 18, "state");

    // --- Запуск симуляторов ---
  //  SimulatorManager simManager;
  //  simManager.addSimulator(new TemperatureSimulator(tempTag));
  //   simManager.addSimulator(new TemperatureSimulator(pressureTag)); // условный повтор для примера

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
