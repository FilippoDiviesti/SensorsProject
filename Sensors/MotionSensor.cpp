#include "MotionSensor.h"

namespace Sensor {

MotionSensor::MotionSensor() {}

MotionSensor::MotionSensor(const std::string& name, const std::string& description, unsigned int id) : Sensor(name, id, description){
    setRandomData();
    calculateLastDelta();
}

MotionSensor::MotionSensor(std::vector<MotionData> v, std::string name, std::string description, unsigned int id) : Sensor(name, id, description){
    data = v;
    calculateLastDelta();
}

void MotionSensor::calculateLastDelta(){
    if(data.size() != 0){
        lastMotionData = *(data.end()-1);
        deltaMotion = *(data.begin()) - *(data.end()-1);
    }
    else{
        MotionData last;
        MotionData delta;
        lastMotionData = last;
        deltaMotion = delta;
    }
}

void MotionSensor::setRandomData(){
    data = std::vector<MotionData>(0);

    for(int i = 0; i<10; i++){
        MotionData n;
        n.setRandomData();
        data.push_back(n);
    }
}

void MotionSensor::accept(SensorVisitorInterface &visitor) const
{
    visitor.visit(*this);
}



std::vector<MotionData> MotionSensor::getData() const
{
    return data;
}

MotionData MotionSensor::getLastMotionData() const
{
    return lastMotionData;
}

MotionData MotionSensor::getDeltaMotion() const
{
    return deltaMotion;
}



}


