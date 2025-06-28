#include "DeviceManager.h"
#include <QCoreApplication>
#include <QDebug>

DeviceManager::DeviceManager(QObject* parent)
    : QObject(parent)
{
}

bool DeviceManager::loadDevicesFromFile(const QString& path)
{
    DeviceConfigLoader loader;
    QList<DeviceConfig> configs = loader.loadFromJsonFile(path);
    if (configs.isEmpty()) {
        qWarning() << "Device config is empty or failed to load.";
        return false;
    }

    for (const DeviceConfig& config : configs) {
        Device* device = new Device(config, this); // Владелец — manager
        m_devices.append(device);
        m_idMap[config.id] = device;
        m_addressMap[config.address] = device;
    }

    return true;
}

const QList<Device*>& DeviceManager::devices() const
{
    return m_devices;
}

Device* DeviceManager::getDeviceById(int id) const
{
    return m_idMap.value(id, nullptr);
}

Device* DeviceManager::getDeviceByAddress(int address) const
{
    return m_addressMap.value(address, nullptr);
}
