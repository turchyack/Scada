#ifndef SENSORSIMULATOR_H
#define SENSORSIMULATOR_H

#include <QObject>
#include "Tag.h"

class SensorSimulator : public QObject {
    Q_OBJECT
public:
    explicit SensorSimulator(Tag* tag, QObject* parent = nullptr);
    virtual ~SensorSimulator() = default;

    virtual void simulate() = 0;

    virtual void start() = 0;
    virtual void stop() = 0;

protected:
    Tag* m_tag;
};

#endif // SENSORSIMULATOR_H
