#ifndef TAG_H
#define TAG_H

#include <QObject>
#include <QString>

class Tag : public QObject {
    Q_OBJECT
    Q_PROPERTY(QString name READ name CONSTANT)
    Q_PROPERTY(int address READ address CONSTANT)
    Q_PROPERTY(QString type READ type CONSTANT)
    Q_PROPERTY(double value READ value WRITE setValue NOTIFY valueChanged)

public:
    explicit Tag(const QString& name,
                 double value = 0.0,
                 int address = 0,
                 const QString& type = "",
                 QObject* parent = nullptr);

    QString name() const;
    int address() const;
    QString type() const;
    double value() const;

    void setValue(double newValue);

signals:
    void valueChanged();

private:
    QString m_name;
    int m_address;
    QString m_type;
    double m_value = 0.0;
};

#endif // TAG_H
