#ifndef TAGMANAGER_H
#define TAGMANAGER_H

#include <QAbstractListModel>
#include <QList>
#include "Tag.h"
#include "utils/Types.h"

class TagManager : public QAbstractListModel
{
    Q_OBJECT
public:
    // TagRoles теперь определен в utils/Types.h
    // enum TagRoles {
    //     NameRole = Qt::UserRole + 1,
    //     ValueRole,
    //     AddressRole,
    //     TypeRole
    // };

    explicit TagManager(QObject* parent = nullptr);
    ~TagManager();

    // QAbstractListModel overrides
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

    Tag* createTag(const QString& name, double initialValue, int id, const QString& type);
    Tag* getTagByAddress(int address);


    Q_INVOKABLE void addTag(const QString& name, int address, const QString& type);
    Q_INVOKABLE Tag* getTag(int index) const;
    Q_INVOKABLE void setTagValue(const QString& name, double value);
    Q_INVOKABLE void setTagValueByAddress(int address, double value);




private slots:
    void onTagValueChanged();

private:
    QList<Tag*> m_tags;
};

#endif // TAGMANAGER_H
