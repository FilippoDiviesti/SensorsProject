#ifndef MOTIONDATA_H
#define MOTIONDATA_H

#include <random>

namespace Sensor {

    class MotionData
    {
    private:
        double xRotation;
        double yRotation;
        double zRotation;
    public:
        MotionData();
        MotionData(double x, double y, double z);
        double getXRotation() const;
        double getYRotation() const;
        double getZRotation() const;

        void setRandomData();

        MotionData operator-(MotionData const &s);

        std::string toString();

        ~MotionData() = default;
    };

}



#endif // MOTIONDATA_H
