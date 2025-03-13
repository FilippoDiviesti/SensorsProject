#ifndef SENSOR_H
#define SENSOR_H

#include "SensorVisitorInterface.h"

#include <string>
#include <random>


namespace Sensor {

    class Sensor
    {
        private:

            std::string name;
            std::string description;
            unsigned int id;

        public:

            Sensor();

            Sensor(const std::string& name, unsigned int id, const std::string& description = "");

            std::string getName() const;
            void setName(const std::string &newName);

            std::string getDescription() const;
            void setDescription(const std::string &newDescription);

            unsigned int getId() const;
            void setId(unsigned int newId);

            virtual void accept(SensorVisitorInterface& visitor) const = 0;

            virtual ~Sensor() = default;
    };

}



#endif // SENSOR_H
