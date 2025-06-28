// #ifndef DEVICEMANAGER_H
// #define DEVICEMANAGER_H

// #include <QString>
// #include <QJsonObject>
// #include "DriveType.h"

// /**
//  * @brief Конфигурация одного устройства, загружаемая из JSON
//  */
// struct DeviceConfig
// {
//     QString id;              ///< Уникальный идентификатор
//     QString name;            ///< Название (например, "Конвейер 1")
//     QString type;            ///< Тип устройства (например, "conveyor")
//     DriveType driveType;     ///< Тип привода (контактор, ПЧ, обмен сигналами)
//     int startDelayMs = 0;    ///< Задержка запуска (мс)
//     int stopDelayMs = 0;     ///< Задержка остановки (мс)
//     bool supportsReverse = false; ///< Поддержка реверса

//     /**
//      * @brief Загружает конфигурацию из JSON-объекта
//      */
//     static DeviceConfig fromJson(const QJsonObject& obj);
// };

// #endif


#ifndef DEVICEMANAGER_H
#define DEVICEMANAGER_H

#include <QObject>
#include <QList>
#include <QMap>

#include "Device.h"

#include "config/DeviceConfigLoader.h"

class DeviceManager : public QObject
{
    Q_OBJECT

public:
    explicit DeviceManager(QObject* parent = nullptr);

    bool loadDevicesFromFile(const QString& path);

    const QList<Device*>& devices() const;
    Device* getDeviceById(int id) const;
    Device* getDeviceByAddress(int address) const;

private:
    QList<Device*> m_devices;
    QMap<int, Device*> m_idMap;
    QMap<int, Device*> m_addressMap;
};

#endif // DEVICEMANAGER_H
