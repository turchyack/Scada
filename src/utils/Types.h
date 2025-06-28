#ifndef TYPES_H
#define TYPES_H

#include <QString>
#include <QList>

// ===== Перечисления =====

/**
 * @brief Типы приводов устройств
 */
enum class DriveType {
    Unknown,    // Неизвестный или не задан
    VFD,        // Преобразователь частоты (Variable Frequency Drive)
    Contactor,  // Контактор
    Signaling   // Сигнальный обмен (Пуск/Стоп, статус)
};

/**
 * @brief Роли для модели тегов (QML)
 */
enum TagRoles {
    NameRole = Qt::UserRole + 1,
    ValueRole,
    AddressRole,
    TypeRole
};

/**
 * @brief Роли для модели устройств (QML)
 */
enum DeviceRoles {
    DeviceNameRole = Qt::UserRole + 1,
    DeviceDriveTypeRole,
    DeviceTagModelRole
};

// ===== Структуры =====

/**
 * @brief Конфигурация тега
 */
struct TagConfig {
    QString name;
    double value = 0.0;
    int address = 0;
    QString type;
    QString simulator;
};

/**
 * @brief Конфигурация устройства
 */
struct DeviceConfig
{
    int id = 0;                  // ID устройства
    QString name;                // Имя
    DriveType driveType = DriveType::Unknown;  // Тип привода
    double power = 0.0;          // Мощность, кВт
    int address = 0;             // Адрес устройства (Modbus например)
    QString description;         // Описание
    QList<TagConfig> tags;       // Список тегов устройства
    
    DeviceConfig() = default;
};

// ===== Вспомогательные функции =====

/**
 * @brief Преобразует строку в тип привода
 */
DriveType stringToDriveType(const QString& s);

#endif // TYPES_H 