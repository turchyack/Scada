#ifndef DEVICECONFIGLOADER_H
#define DEVICECONFIGLOADER_H

#include <QList>
#include <QString>
#include <QJsonObject>
#include "utils/Types.h"

class DeviceConfigLoader
{
public:
    static QList<DeviceConfig> loadFromJsonFile(const QString& filePath);

private:
    static DeviceConfig parseDeviceObject(const QJsonObject& obj);
};

#endif // DEVICECONFIGLOADER_H
