#include "SensorSimulator.h"

SensorSimulator::SensorSimulator(Tag* tag, QObject* parent)
    : QObject(parent), m_tag(tag)
{
}
