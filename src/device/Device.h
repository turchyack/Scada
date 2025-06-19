// Device.h
#ifndef DEVICE_H
#define DEVICE_H

#include <string>
#include <optional>

enum class DriveType {
    FrequencyConverter,
    Contactor,
    Unknown
};

class Device {
public:

    // Device::Device(const QJsonObject& obj);
    Device(const std::string& id, const std::string& name, DriveType type);

    const std::string& id() const;
    const std::string& name() const;
    DriveType driveType() const;

    void start();
    void stop();
    void setSpeed(int rpm);
    void setReverse(bool enabled);

private:
    std::string m_id;
    std::string m_name;
    DriveType m_driveType;

    int m_speed = 0;
    bool m_isRunning = false;
    bool m_isReverse = false;
};


#endif // DEVICE_H
