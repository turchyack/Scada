#ifndef SIMULATORMANAGER_H
#define SIMULATORMANAGER_H

#include <QObject>
#include <QList>
#include "SensorSimulator.h"

class SimulatorManager : public QObject
{
    Q_OBJECT

public:
    explicit SimulatorManager(QObject *parent = nullptr);
    void addSimulator(SensorSimulator* simulator);
    void startAll();
    void stopAll();

private:
    QList<SensorSimulator*> m_simulators;
};

#endif // SIMULATORMANAGER_H
