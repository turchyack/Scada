#include "Device.h"
#include <QDebug>


Device::Device(const QString& id, const QString& name, DriveType drive)
    : m_id(id), m_name(name), m_driveType(drive)
{
}

Device::Device(const DeviceConfig& config, QObject* parent)
    : QObject(parent),
    m_id(QString::number(config.id)),
    m_name(config.name),
    m_driveType(config.driveType)
{
    // Можно логировать
    qDebug() << "Device создан из конфигурации:" << m_id << m_name;
}

QString Device::id() const {
    return m_id;
}

QString Device::name() const {
    return m_name;
}

DriveType Device::driveType() const {
    return m_driveType;
}

bool Device::isRunning() const {
    return m_running;
}

bool Device::isFault() const {
    return m_fault;
}

bool Device::isReady() const {
    return m_ready;
}

void Device::start() {
    if (m_fault || !m_ready) return;
    m_running = true;
    emit stateChanged();
}

void Device::stop() {
    m_running = false;
    emit stateChanged();
}

void Device::fault() {
    m_fault = true;
    m_running = false;
    m_ready = false;
    emit stateChanged();
}

void Device::reset() {
    m_fault = false;
    m_ready = true;
    emit stateChanged();
}
