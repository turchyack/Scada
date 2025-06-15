#ifndef TAGMANAGER_H
#define TAGMANAGER_H

#include <QAbstractListModel>
#include <QList>
#include "Tag.h"

class TagManager : public QAbstractListModel
{
    Q_OBJECT
public:
    enum TagRoles {
        NameRole = Qt::UserRole + 1,
        ValueRole,
        AddressRole,
        TypeRole
    };

    explicit TagManager(QObject* parent = nullptr);
    ~TagManager();

    // QAbstractListModel overrides
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

    Q_INVOKABLE void addTag(const QString& name, int address, const QString& type);
    Q_INVOKABLE Tag* getTag(int index) const;

private slots:
    void onTagValueChanged();

private:
    QList<Tag*> m_tags;
};

#endif // TAGMANAGER_H
