#include "TemperatureSimulator.h"
#include <QRandomGenerator>

TemperatureSimulator::TemperatureSimulator(Tag* tag, QObject* parent)
    : SensorSimulator(tag, parent)
{
    connect(&m_timer, &QTimer::timeout, this, &TemperatureSimulator::updateValue);
}

void TemperatureSimulator::simulate()
{
    updateValue();
}

void TemperatureSimulator::start()
{
    m_timer.start(1000); // обновление каждые 1000 мс
}

void TemperatureSimulator::stop()
{
    m_timer.stop();
}

void TemperatureSimulator::updateValue()
{
    if (!m_tag)
        return;

    double value = QRandomGenerator::global()->bounded(80.0) + 20.0; // 20..100
    m_tag->setValue(value);
}
