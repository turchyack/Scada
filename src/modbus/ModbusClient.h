#ifndef MODBUSCLIENT_H
#define MODBUSCLIENT_H

#include <QObject>
#include <QTimer>
#include <QString>

class TagManager;

class ModbusClient : public QObject {
    Q_OBJECT

public:
    ModbusClient(TagManager* manager, QObject* parent = nullptr);
    ~ModbusClient();

    void connectToServer(const QString& ip, int port);
    void disconnectFromServer();

    void startPolling(int intervalMs);
    void stopPolling();

private slots:
    void readRegisters();

private:
    TagManager* m_tagManager;
    QTimer m_pollingTimer;
    void* m_ctx;  // modbus_t*
};

#endif // MODBUSCLIENT_H
