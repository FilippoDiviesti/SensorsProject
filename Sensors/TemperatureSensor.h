#ifndef TEMPERATURESENSOR_H
#define TEMPERATURESENSOR_H

#include "Sensor.h"

#include <vector>

namespace Sensor {

class TemperatureSensor : public Sensor
{
private:
    std::vector<double> data;
    double maxData;
    double minData;

    void calculateMinMax();

public:
    TemperatureSensor();
    TemperatureSensor(const std::string& name, const std::string& description, unsigned int id);
    TemperatureSensor(std::vector<double> v, std::string name, std::string description, unsigned int id);

    std::vector<double> getData() const;
    double getMaxData() const;
    double getMinData() const;

    void setRandomData();

    void accept(SensorVisitorInterface& visitor) const;
};

}



#endif // TEMPERATURESENSOR_H
