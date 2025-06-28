// Device.h
#ifndef DEVICE_H
#define DEVICE_H

#include <QString>
#include <QObject>
#include "utils/Types.h"
#include "DeviceConfig.h"

/**
 * @brief Тип привода устройства
 */

/**
 * @brief Класс Device — абстракция одного устройства (мотор, конвейер и т.д.)
 */
class Device : public QObject {
    Q_OBJECT

public:
    /**
     * @brief Конструктор устройства
     * @param id Уникальный ID (например, "M1")
     * @param name Человеко-читаемое название
     * @param drive Тип привода
     */
    Device(const QString& id, const QString& name, DriveType drive);

    Device(const DeviceConfig& config, QObject* parent = nullptr);

    // --- Геттеры ---
    QString id() const;
    QString name() const;
    DriveType driveType() const;

    // --- Состояние устройства ---
    bool isRunning() const;
    bool isFault() const;
    bool isReady() const;

    // --- Управление устройством ---
    void start();  ///< Запуск устройства
    void stop();   ///< Остановка
    void fault();  ///< Вызов аварии
    void reset();  ///< Сброс аварии

signals:
    void stateChanged();  ///< Сигнал при изменении состояния

private:
    QString m_id;
    QString m_name;
    DriveType m_driveType;

    // Текущее состояние
    bool m_running = false;
    bool m_fault = false;
    bool m_ready = true;
};

#endif // DEVICE_H
