#ifndef DEVICEVIEWMODEL_H
#define DEVICEVIEWMODEL_H

#include <QObject>
#include <QString>
#include <QVector>
#include <QAbstractListModel>
#include "Tag.h"

class TagListModel : public QAbstractListModel {
    Q_OBJECT
public:
    explicit TagListModel(QObject* parent = nullptr);

    void addTag(Tag* tag);

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

private:
    QVector<Tag*> m_tags;
};

class DeviceViewModel : public QObject {
    Q_OBJECT
    Q_PROPERTY(QString name READ name CONSTANT)
    Q_PROPERTY(QString driveType READ driveType CONSTANT)
    Q_PROPERTY(TagListModel* tagModel READ tagModel CONSTANT)

public:
    DeviceViewModel(const QString& name, const QString& driveType, QObject* parent = nullptr);

    QString name() const;
    QString driveType() const;
    TagListModel* tagModel();

    void addTag(Tag* tag);

private:
    QString m_name;
    QString m_driveType;
    TagListModel m_tagModel;
};

#endif // DEVICEVIEWMODEL_H
