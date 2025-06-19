#include "ModbusClient.h"
#include "core/TagManager.h"

#include <modbus/modbus.h>
#include <QDebug>
#include <cerrno>

ModbusClient::ModbusClient(TagManager* manager, QObject* parent)
    : QObject(parent), m_tagManager(manager), m_ctx(nullptr)
{
}

ModbusClient::~ModbusClient() {
    disconnectFromServer();
}

void ModbusClient::connectToServer(const QString& ip, int port) {
    m_ctx = modbus_new_tcp(ip.toStdString().c_str(), port);
    if (!m_ctx) {
        qWarning() << "Не удалось создать контекст Modbus";
        return;
    }

    if (modbus_connect(static_cast<modbus_t*>(m_ctx)) == -1) {
        qWarning() << "Ошибка подключения к Modbus:" << modbus_strerror(errno);
        modbus_free(static_cast<modbus_t*>(m_ctx));
        m_ctx = nullptr;
        return;
    }

    qDebug() << "Успешное подключение к Modbus-серверу:" << ip << port;
}

void ModbusClient::disconnectFromServer() {
    if (m_ctx) {
        modbus_close(static_cast<modbus_t*>(m_ctx));
        modbus_free(static_cast<modbus_t*>(m_ctx));
        m_ctx = nullptr;
    }
}

void ModbusClient::startPolling(int intervalMs) {
    connect(&m_pollingTimer, &QTimer::timeout, this, &ModbusClient::readRegisters);
    m_pollingTimer.start(intervalMs);
}

void ModbusClient::stopPolling() {
    m_pollingTimer.stop();
}

void ModbusClient::readRegisters() {
    if (!m_ctx) return;

    uint16_t regs[10];
    int rc = modbus_read_registers(static_cast<modbus_t*>(m_ctx), 0, 10, regs);
    if (rc == -1) {
        qWarning() << "Ошибка чтения Modbus:" << modbus_strerror(errno);
        return;
    }

    for (int i = 0; i < rc; ++i) {
        double value = regs[i];
        m_tagManager->setTagValue(QString("tag%1").arg(i), value);
    }
}
