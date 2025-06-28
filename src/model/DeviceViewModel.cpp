#include "DeviceViewModel.h"
#include "utils/Types.h"

// ===== TagListModel Implementation =====

TagListModel::TagListModel(QObject* parent)
    : QAbstractListModel(parent)
{
}

void TagListModel::addTag(Tag* tag)
{
    beginInsertRows(QModelIndex(), m_tags.size(), m_tags.size());
    m_tags.append(tag);
    endInsertRows();
}

int TagListModel::rowCount(const QModelIndex& parent) const
{
    if (parent.isValid())
        return 0;
    return m_tags.size();
}

QVariant TagListModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid() || index.row() >= m_tags.size())
        return QVariant();

    Tag* tag = m_tags.at(index.row());
    switch (role) {
    case NameRole:
        return tag->name();
    case ValueRole:
        return tag->value();
    case AddressRole:
        return tag->address();
    case TypeRole:
        return tag->type();
    default:
        return QVariant();
    }
}

QHash<int, QByteArray> TagListModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[NameRole] = "name";
    roles[ValueRole] = "value";
    roles[AddressRole] = "address";
    roles[TypeRole] = "type";
    return roles;
}

// ===== DeviceViewModel Implementation =====

DeviceViewModel::DeviceViewModel(const QString& name, const QString& driveType, QObject* parent)
    : QObject(parent), m_name(name), m_driveType(driveType), m_tagModel(this)
{
}

QString DeviceViewModel::name() const
{
    return m_name;
}

QString DeviceViewModel::driveType() const
{
    return m_driveType;
}

TagListModel* DeviceViewModel::tagModel()
{
    return &m_tagModel;
}

void DeviceViewModel::addTag(Tag* tag)
{
    m_tagModel.addTag(tag);
}
