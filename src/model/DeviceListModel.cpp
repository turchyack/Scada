#include "DeviceListModel.h"
#include "utils/Types.h"

DeviceListModel::DeviceListModel(QObject* parent)
    : QAbstractListModel(parent)
{
}

void DeviceListModel::addDevice(DeviceViewModel* device)
{
    beginInsertRows(QModelIndex(), m_devices.size(), m_devices.size());
    m_devices.append(device);
    endInsertRows();
}

int DeviceListModel::rowCount(const QModelIndex& parent) const
{
    if (parent.isValid())
        return 0;
    return m_devices.size();
}

QVariant DeviceListModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid() || index.row() >= m_devices.size())
        return QVariant();

    DeviceViewModel* device = m_devices.at(index.row());
    switch (role) {
    case DeviceNameRole:
        return device->name();
    case DeviceDriveTypeRole:
        return device->driveType();
    case DeviceTagModelRole:
        return QVariant::fromValue(device->tagModel());
    default:
        return QVariant();
    }
}

QHash<int, QByteArray> DeviceListModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[DeviceNameRole] = "name";
    roles[DeviceDriveTypeRole] = "driveType";
    roles[DeviceTagModelRole] = "tagModel";
    return roles;
}
