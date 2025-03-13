#include "TemperatureSensor.h"

namespace Sensor {



TemperatureSensor::TemperatureSensor() {}

TemperatureSensor::TemperatureSensor(const std::string& name, const std::string& description, unsigned int id) : Sensor(name, id, description){
    setRandomData();
    calculateMinMax();
}

TemperatureSensor::TemperatureSensor(std::vector<double> v, std::string name, std::string description, unsigned int id) : Sensor(name, id, description){
    data = v;
    calculateMinMax();
}


void TemperatureSensor::calculateMinMax(){

    if(data.size() != 0){
        double min = *(data.begin());
        double max = *(data.begin());
        for(auto i = data.begin(); i != data.end(); i++){
            if(*i < min) {min = *i;}
            if(*i > max) {max = *i;}
        }
        minData = min;
        maxData = max;
    }
    else{
        minData = 0;
        maxData = 0;
    }

}

void TemperatureSensor::setRandomData(){

    data = std::vector<double>(0);

    for(int i = 0; i<10; i++){
        data.push_back((double)rand() / RAND_MAX);
    }
}

void TemperatureSensor::accept(SensorVisitorInterface &visitor) const
{
    visitor.visit(*this);
}



double TemperatureSensor::getMaxData() const
{
    return maxData;
}


double TemperatureSensor::getMinData() const
{
    return minData;
}

std::vector<double> TemperatureSensor::getData() const
{
    return data;
}




}

