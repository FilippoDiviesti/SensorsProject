#ifndef SENSORSMANAGEROBSERVERINTERFACE_H
#define SENSORSMANAGEROBSERVERINTERFACE_H

#include "Sensor.h"


namespace Sensor {

class SensorsManagerObserverInterface
{
public:
    virtual ~SensorsManagerObserverInterface() = default;
    virtual void notifyAdd(Sensor* sensor) = 0;
    virtual void notifyDel(Sensor* sensor) = 0;
    virtual void notifyEdit(Sensor* sensor) = 0;
};

}

#endif // SENSORSMANAGEROBSERVERINTERFACE_H
