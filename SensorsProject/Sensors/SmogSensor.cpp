#include "SmogSensor.h"
namespace Sensor {

SmogSensor::SmogSensor() {}

SmogSensor::SmogSensor(const std::string& name, const std::string& description, unsigned int id) : Sensor(name, id, description)
{
    setRandomData();
    calculateAverage();
}

SmogSensor::SmogSensor(std::vector<double> v, std::string name, std::string description, unsigned int id) : Sensor(name, id, description)
{
    data = v;
    calculateAverage();
}

void SmogSensor::calculateAverage(){
    if(data.size() != 0){
        double sum = 0;
        for(auto i = data.begin(); i!=data.end(); i++){
            sum += *i;
        }
        averageData = sum/data.size();
    }
}

void SmogSensor::setRandomData(){
    data = std::vector<double>(0);

    for(int i = 0; i<10; i++){
        data.push_back((double)rand() / RAND_MAX);
    }
}

void SmogSensor::accept(SensorVisitorInterface &visitor) const
{
    visitor.visit(*this);
}

std::vector<double> SmogSensor::getData() const
{
    return data;
}

double SmogSensor::getAverageData() const
{
    return averageData;
}




}

