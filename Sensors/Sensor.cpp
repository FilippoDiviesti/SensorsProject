#include "Sensor.h"

namespace Sensor {



    Sensor::Sensor() {}

    Sensor::Sensor(const std::string& name, unsigned int id, const std::string& description)
    : name(name), description(description), id(id)
    {

    }

    std::string Sensor::getName() const
    {
        return name;
    }

    void Sensor::setName(const std::string &newName)
    {
        name = newName;
    }

    std::string Sensor::getDescription() const
    {
        return description;
    }

    void Sensor::setDescription(const std::string &newDescription)
    {
        description = newDescription;
    }


    unsigned int Sensor::getId() const
    {
        return id;
    }

    void Sensor::setId(unsigned int newId)
    {
        id = newId;
    }



}
