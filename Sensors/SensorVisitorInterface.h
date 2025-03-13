#ifndef SENSORVISITORINTERFACE_H
#define SENSORVISITORINTERFACE_H




namespace Sensor {

class TemperatureSensor;
class MotionSensor;
class SmogSensor;

class SensorVisitorInterface{
public:
    virtual ~SensorVisitorInterface() = default;
    virtual void visit(const TemperatureSensor& tempSensor) = 0;
    virtual void visit(const MotionSensor& motionSensor) = 0;
    virtual void visit(const SmogSensor& smogSensor) = 0;
};

}

#endif // SENSORVISITORINTERFACE_H
