#include "DeviceConfigLoader.h"
#include "utils/Types.h"

#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QDebug>


QList<DeviceConfig> DeviceConfigLoader::loadFromJsonFile(const QString& path)
{
    QList<DeviceConfig> devices;

    QFile file(path);
    if (!file.open(QIODevice::ReadOnly)) {
        qWarning() << "Failed to open device config file:" << path;
        return devices;
    }

    QByteArray data = file.readAll();
    file.close();

    QJsonParseError parseError;
    QJsonDocument doc = QJsonDocument::fromJson(data, &parseError);
    if (parseError.error != QJsonParseError::NoError) {
        qWarning() << "JSON parse error:" << parseError.errorString();
        return devices;
    }

    QJsonArray arr = doc.array();

    for (const QJsonValue& val : arr) {
        if (!val.isObject()) continue;
        devices.append(parseDeviceObject(val.toObject()));
    }


    // for (const QJsonValue& val : arr) {
    //     if (!val.isObject()) continue;
    //     QJsonObject obj = val.toObject();

    //     DeviceConfig dev;
    //     dev.name = obj.value("name").toString();
    //     dev.address = obj.value("address").toInt();
    //     dev.power = obj.value("power").toDouble();
    //     dev.description = obj.value("description").toString();
    //     dev.driveType = stringToDriveType(obj.value("driveType").toString());

    //     devices.append(dev);
    // }

    return devices;
}


// DeviceConfig DeviceConfigLoader::parseDeviceObject(const QJsonObject& obj)
// {
//     DeviceConfig config;

//     config.name = obj.value("name").toString();
//     config.id = obj.value("id").toInt();
//     config.driveType = stringToDriveType(obj.value("driveType").toString());
//     config.power = obj.value("power").toDouble();
//     config.address = obj.value("address").toInt();
//     config.description = obj.value("description").toString();

//     return config;
// }


DeviceConfig DeviceConfigLoader::parseDeviceObject(const QJsonObject& obj)
{
    DeviceConfig dev;
    dev.id = obj["id"].toInt();
    dev.name = obj["name"].toString();
    dev.driveType = stringToDriveType(obj["driveType"].toString());
    dev.power = obj["power"].toDouble();
    dev.address = obj["address"].toInt();
    dev.description = obj["description"].toString();

    // --- Загрузка тегов ---
    if (obj.contains("tags") && obj["tags"].isArray()) {
        QJsonArray tagArray = obj["tags"].toArray();
        for (const QJsonValue& tagVal : tagArray) {
            QJsonObject tagObj = tagVal.toObject();
            TagConfig tag;

            tag.name = tagObj["name"].toString();
            tag.value = tagObj["value"].toDouble();
            tag.address = tagObj["address"].toInt();
            tag.type = tagObj["type"].toString();
            tag.simulator = tagObj["simulator"].toString();

            dev.tags.append(tag);
        }
    }

    return dev;
}
