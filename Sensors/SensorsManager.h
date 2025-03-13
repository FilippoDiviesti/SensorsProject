#ifndef SENSORSMANAGER_H
#define SENSORSMANAGER_H

#include "Sensor.h"
#include "SensorsManagerObserverInterface.h"

#include <vector>
#include <string>


namespace Sensor {

class SensorsManager
{
private:

    std::vector<Sensor*> allSensorsVector;
    unsigned int idRef;
    std::vector<SensorsManagerObserverInterface*> observers;

    std::string path;
    std::string createJson();

    void clearAll();

public:
    SensorsManager();

    void addSensor(Sensor* newSensor);
    void deleteSensor(Sensor* toDeleteSensor);
    void editSensor(Sensor* toEditSensor, std::string newTitle, std::string newDesc);

    std::vector<Sensor*> searchSensor(std::string searchText);

    unsigned int getIdRef() const;
    std::vector<Sensor *> getAllSensorsVector() const;

    void incrementIdRef();


    void registerObserver(SensorsManagerObserverInterface* observer);

    void saveFile();
    void saveNewFile(std::string path);
    void openFile(std::string path);

    std::string getPath() const;
};

}



#endif // SENSORSMANAGER_H
