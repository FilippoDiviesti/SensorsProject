#ifndef SENSORSELECTEDOBSERVERINTERFACE_H
#define SENSORSELECTEDOBSERVERINTERFACE_H

#include "Sensor.h"


namespace Sensor {

class SensorSelectedObserverInterface
{
public:
    virtual ~SensorSelectedObserverInterface() = default;
    virtual void notifySelected(Sensor* sensor) = 0;
};

}

#endif // SENSORSELECTEDOBSERVERINTERFACE_H
