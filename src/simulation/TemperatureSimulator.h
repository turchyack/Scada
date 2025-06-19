#ifndef TEMPERATURESIMULATOR_H
#define TEMPERATURESIMULATOR_H

#include "SensorSimulator.h"
#include <QTimer>

class TemperatureSimulator : public SensorSimulator {
    Q_OBJECT
public:
    explicit TemperatureSimulator(Tag* tag, QObject* parent = nullptr);

    void simulate() override;

    void start();
    void stop();

private slots:
    void updateValue();

private:
    QTimer m_timer;
};

#endif // TEMPERATURESIMULATOR_H
