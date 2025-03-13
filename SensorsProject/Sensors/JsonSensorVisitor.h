#ifndef JSONSENSORVISITOR_H
#define JSONSENSORVISITOR_H

#include "SensorVisitorInterface.h"
#include <Sensors/TemperatureSensor.h>
#include <Sensors/MotionSensor.h>
#include <Sensors/SmogSensor.h>

#include <QJsonObject>


namespace Sensor {

class JsonSensorVisitor : public SensorVisitorInterface
{
private:
    QJsonObject* jsonObj;
public:
    JsonSensorVisitor();
    virtual void visit(const TemperatureSensor& tempSensor);
    virtual void visit(const MotionSensor& motionSensor);
    virtual void visit(const SmogSensor& smogSensor);
    QJsonObject* getJsonObj() const;
};

}



#endif // JSONSENSORVISITOR_H
