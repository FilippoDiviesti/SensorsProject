#ifndef CHARTSENSORVISITOR_H
#define CHARTSENSORVISITOR_H

#include <Sensors/TemperatureSensor.h>
//#include <Sensors/MotionSensor.h>
#include <Sensors/SmogSensor.h>
#include <Sensors/SensorVisitorInterface.h>


#include <QChart>

namespace View {

class ChartSensorVisitor : public Sensor::SensorVisitorInterface
{
private:
    QChart* chart;
public:
    ChartSensorVisitor();

    virtual void visit(const Sensor::TemperatureSensor& tempSensor);
    virtual void visit(const Sensor::MotionSensor& motionSensor);
    virtual void visit(const Sensor::SmogSensor& smogSensor);

    QChart *getChart() const;
};

}



#endif // CHARTSENSORVISITOR_H
