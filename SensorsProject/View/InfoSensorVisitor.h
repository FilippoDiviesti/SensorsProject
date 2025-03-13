#ifndef INFOSENSORVISITOR_H
#define INFOSENSORVISITOR_H

#include <Sensors/MotionSensor.h>
#include <Sensors/SensorVisitorInterface.h>
#include <Sensors/SmogSensor.h>
#include <Sensors/TemperatureSensor.h>

#include <QWidget>


namespace View {

class InfoSensorVisitor : public Sensor::SensorVisitorInterface
{
private:
    QWidget* otherInfoWidget;
public:
    InfoSensorVisitor();
    virtual void visit(const Sensor::TemperatureSensor& tempSensor);
    virtual void visit(const Sensor::MotionSensor& motionSensor);
    virtual void visit(const Sensor::SmogSensor& smogSensor);
    QWidget* getOtherInfo();
};

}



#endif // INFOSENSORVISITOR_H
