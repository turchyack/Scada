#include "Types.h"

DriveType stringToDriveType(const QString& s)
{
    if (s.compare("VFD", Qt::CaseInsensitive) == 0)
        return DriveType::VFD;
    else if (s.compare("CONTACTOR", Qt::CaseInsensitive) == 0)
        return DriveType::Contactor;
    else if (s.compare("SIGNALING", Qt::CaseInsensitive) == 0)
        return DriveType::Signaling;
    else
        return DriveType::Unknown;
} 