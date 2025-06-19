#include "Device.h"


// Device::Device(const QJsonObject& obj)
// {
//     m_name = obj["name"].toString();
//     m_id = obj["deviceId"].toInt();

//     QString typeStr = obj["driveType"].toString();
//     if (typeStr == "FrequencyConverter")
//         m_driveType = DriveType::FrequencyConverter;
//     else if (typeStr == "Contactor")
//         m_driveType = DriveType::Contactor;
//     else
//         m_driveType = DriveType::Unknown;

//     QJsonObject modbus = obj["modbus"].toObject();
//     m_startCoil = modbus["startCoil"].toInt();
//     m_speedRegister = modbus["speedRegister"].toInt();
//     m_statusRegister = modbus["statusRegister"].toInt();

//     QJsonObject delays = obj["delays"].toObject();
//     m_startDelay = delays["startDelay"].toDouble();
//     m_stopDelay = delays["stopDelay"].toDouble();
// }
