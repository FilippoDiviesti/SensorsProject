#ifndef SMOGSENSOR_H
#define SMOGSENSOR_H

#include "Sensor.h"
#include <random>

namespace Sensor{

class SmogSensor : public Sensor
{
private:
    std::vector<double> data;
    double averageData;

    void calculateAverage();

public:
    SmogSensor();
    SmogSensor(const std::string& name, const std::string& description, unsigned int id);
    SmogSensor(std::vector<double> v, std::string name, std::string description, unsigned int id);

    std::vector<double> getData() const;
    double getAverageData() const;

    void setRandomData();


    void accept(SensorVisitorInterface& visitor) const;
};


}


#endif // SMOGSENSOR_H
