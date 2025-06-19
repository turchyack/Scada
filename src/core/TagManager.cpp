#include "TagManager.h"
#include "Tag.h"


TagManager::TagManager(QObject* parent)
    : QAbstractListModel(parent)
{

    m_tags.append(new Tag("Temperature", 24.5, 0x01, "float", this));
    m_tags.append(new Tag("Pressure", 1.2, 0x02, "float", this));
    m_tags.append(new Tag("ValveOpen", 1.0, 0x03, "bool", this));  // 1.0 = true
    m_tags.append(new Tag("Level", 78.0, 0x04, "int", this));

    m_tags.append(new Tag("Temperature", 1, 0x05, "float", this));
    m_tags.append(new Tag("Pressure", 2, 0x06, "float" ,  this));


}

TagManager::~TagManager()
{
    qDeleteAll(m_tags);
    m_tags.clear();
}

int TagManager::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;
    return m_tags.count();
}

QVariant TagManager::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    int row = index.row();
    if (row < 0 || row >= m_tags.count())
        return QVariant();

    Tag* tag = m_tags.at(row);
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

QHash<int, QByteArray> TagManager::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[NameRole] = "name";
    roles[ValueRole] = "value";
    roles[AddressRole] = "address";
    roles[TypeRole] = "type";
    return roles;
}

void TagManager::addTag(const QString& name, int address, const QString& type)
{
    beginInsertRows(QModelIndex(), m_tags.count(), m_tags.count());
    Tag* tag = new Tag(name, 0.0, address, type, this);
    connect(tag, &Tag::valueChanged, this, &TagManager::onTagValueChanged);
    m_tags.append(tag);
    endInsertRows();
}

Tag* TagManager::getTag(int index) const
{
    if (index < 0 || index >= m_tags.count())
        return nullptr;
    return m_tags.at(index);
}

void TagManager::onTagValueChanged()
{
    Tag* tag = qobject_cast<Tag*>(sender());
    if (!tag)
        return;

    int row = m_tags.indexOf(tag);
    if (row < 0)
        return;

    emit dataChanged(index(row), index(row), {ValueRole});

}

Tag* TagManager::createTag(const QString& name, double initialValue, int id, const QString& type)
{
    beginInsertRows(QModelIndex(), m_tags.count(), m_tags.count());
    Tag* tag = new Tag(name, initialValue, id, type, this);
    connect(tag, &Tag::valueChanged, this, &TagManager::onTagValueChanged);
    m_tags.append(tag);
    endInsertRows();
    return tag;
}


void TagManager::setTagValue(const QString& name, double value)
{
    for (Tag* tag : m_tags) {
        if (tag->name() == name) {
            tag->setValue(value);
            break;
        }
    }
}

void TagManager::setTagValueByAddress(int address, double value)
{
    for (Tag* tag : m_tags) {
        if (tag->address() == address) {
            tag->setValue(value);
            break;
        }
    }
}



Tag* TagManager::getTagByAddress(int address)
{
    for (auto& tag : m_tags) {
        if (tag->address() == address) {
            return tag;
        }
    }
    return nullptr;
}


