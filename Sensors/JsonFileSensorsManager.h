#ifndef JSONFILESENSORSMANAGER_H
#define JSONFILESENSORSMANAGER_H

#include <string>
#include <vector>

#include "Sensor.h"

namespace Sensor {

class JsonFileSensorsManager
{
private:
    std::string path;

    std::string createJson(std::vector<Sensor*>* allSensorsVector, unsigned int* idRef);
public:
    JsonFileSensorsManager();

    void saveJsonFile(std::vector<Sensor*>* allSensorsVector, unsigned int* idRef);
    void saveNewJsonFile(std::vector<Sensor*>* allSensorsVector, unsigned int* idRef);
    void openJsonFile();

    std::string getPath() const;
    void setPath(const std::string &newPath);
};

}



#endif // JSONFILESENSORSMANAGER_H
