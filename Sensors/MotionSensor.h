#ifndef MOTIONSENSOR_H


#include <vector>
#include <random>
#include "Sensor.h"
#include "MotionData.h"

namespace Sensor {

class MotionSensor : public Sensor
{
private:
    std::vector<MotionData> data;
    MotionData lastMotionData;
    MotionData deltaMotion;

    void calculateLastDelta();

public:
    MotionSensor();
    MotionSensor(const std::string &name, const std::string &description, unsigned int id);
    MotionSensor(std::vector<MotionData> v, std::string name, std::string description, unsigned int id);

    std::vector<MotionData> getData() const;
    MotionData getLastMotionData() const;
    MotionData getDeltaMotion() const;

    void setRandomData();

    void accept(SensorVisitorInterface& visitor) const;
};

}



#endif // MOTIONSENSOR_H
