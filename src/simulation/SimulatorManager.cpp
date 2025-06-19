#include "SimulatorManager.h"

SimulatorManager::SimulatorManager(QObject *parent)
    : QObject(parent)
{
}

void SimulatorManager::addSimulator(SensorSimulator* simulator)
{
    if (simulator)
        m_simulators.append(simulator);
}

void SimulatorManager::startAll()
{
    for (SensorSimulator* sim : m_simulators)
        sim->start();
}

void SimulatorManager::stopAll()
{
    for (SensorSimulator* sim : m_simulators)
        sim->stop();
}
