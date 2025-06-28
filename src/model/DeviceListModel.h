#ifndef DEVICELISTMODEL_H
#define DEVICELISTMODEL_H

#include <QAbstractListModel>
#include "DeviceViewModel.h"
#include "utils/Types.h"

class DeviceListModel : public QAbstractListModel {
    Q_OBJECT
public:
    explicit DeviceListModel(QObject* parent = nullptr);

    void addDevice(DeviceViewModel* device);

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

    // DeviceRoles теперь определен в utils/Types.h
    // enum Roles {
    //     NameRole = Qt::UserRole + 1,
    //     DriveTypeRole,
    //     TagModelRole
    // };

private:
    QVector<DeviceViewModel*> m_devices;
};

#endif // DEVICELISTMODEL_H
