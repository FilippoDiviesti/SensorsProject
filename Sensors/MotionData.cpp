#include "MotionData.h"

namespace Sensor {

    MotionData::MotionData() {}

    MotionData::MotionData(double x, double y, double z){
        xRotation = x;
        yRotation = y;
        zRotation = z;
    }




    double MotionData::getXRotation() const
    {
        return xRotation;
    }

    double MotionData::getYRotation() const
    {
        return yRotation;
    }

    double MotionData::getZRotation() const
    {
        return zRotation;
    }

    MotionData MotionData::operator-(MotionData const &s)
    {
        MotionData ris(xRotation-s.getXRotation(), yRotation-s.getYRotation(), zRotation-s.getZRotation());
        return ris;
    }

    std::string MotionData::toString()
    {
        std::string r = std::to_string(getXRotation()) + "° - " + std::to_string(getYRotation()) + "° - " + std::to_string(getZRotation()) + "°";
        return r;
    }

    void MotionData::setRandomData(){
        xRotation = (double)rand() / RAND_MAX;
        yRotation = (double)rand() / RAND_MAX;
        zRotation = (double)rand() / RAND_MAX;
    }

}



