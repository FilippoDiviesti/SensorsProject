#include "JsonSensorVisitor.h"
#include "SensorsManager.h"
#include <QFile>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QByteArray>
#include <algorithm>

namespace Sensor {

SensorsManager::SensorsManager() {
    idRef = 0;
}


void SensorsManager::incrementIdRef()
{
    idRef++;
}

void SensorsManager::addSensor(Sensor* newSensor){
    if(newSensor){
        allSensorsVector.push_back(newSensor);

        //NOTIFY OBSERVERS
        for(auto o = observers.begin(); o != observers.end(); o++){
            (*o)->notifyAdd(newSensor);
        }
    }


}


void SensorsManager::deleteSensor(Sensor* toDeleteSensor){
    if(toDeleteSensor != nullptr){

        auto it = find(allSensorsVector.begin(), allSensorsVector.end(), toDeleteSensor);

        if(it != allSensorsVector.end()){
            allSensorsVector.erase(it);
            //NOTIFY OBSERVERS
            for(auto o = observers.begin(); o != observers.end(); o++){
                (*o)->notifyDel(toDeleteSensor);
            }

            delete toDeleteSensor;
        }
    }
}

void SensorsManager::editSensor(Sensor *toEditSensor, std::string newTitle, std::string newDesc)
{
    if(toEditSensor){

        toEditSensor->setName(newTitle);
        toEditSensor->setDescription(newDesc);

        //NOTIFY OBSERVERS
        for(auto o = observers.begin(); o != observers.end(); o++){
            (*o)->notifyEdit(toEditSensor);
        }
    }
}

std::vector<Sensor*> SensorsManager::searchSensor(std::string searchText){
    std::vector<Sensor*> searchRis(0);
    for(auto it = allSensorsVector.begin(); it != allSensorsVector.end(); it++){
        if((*it)->getName().find(searchText) != std::string::npos){
            searchRis.push_back((*it));
        }
    }
    return searchRis;
}

unsigned int SensorsManager::getIdRef() const
{
    return idRef;
}

std::vector<Sensor *> SensorsManager::getAllSensorsVector() const
{
    return allSensorsVector;
}



void SensorsManager::registerObserver(SensorsManagerObserverInterface *observer)
{
    observers.push_back(observer);
}

void SensorsManager::saveFile()
{
    std::string json = createJson();

    QFile file(QString::fromStdString(path));
    if(file.open(QIODevice::WriteOnly | QIODevice::Text)){
        QTextStream stream(&file);
        stream << QString::fromStdString(json);
        file.close();
    }
}

void SensorsManager::saveNewFile(std::string path)
{
    if(path != ""){
        std::string json = createJson();

        QFile file(QString::fromStdString(path));
        if(file.open(QIODevice::WriteOnly | QIODevice::Text)){
            QTextStream stream(&file);
            stream << QString::fromStdString(json);
            file.close();
        }
        this->path = path;
    }
}

void SensorsManager::openFile(std::string path)
{    
    this->path = path;

    //CLEAR ALL APPLICATION
    clearAll();

    QByteArray jsonData;

    QFile file(QString::fromStdString(path));
    if(file.open(QIODevice::ReadOnly)){
        QTextStream stream(&file);
        jsonData = stream.readAll().toUtf8();
        file.close();
    }

    QJsonDocument jsonDocument = QJsonDocument::fromJson(jsonData);
    QJsonObject object = jsonDocument.object();

    idRef = (unsigned int)object.value("idRef").toInt();

    QJsonArray allSensors = object.value("allSensors").toArray();
    for(int i = 0; i<allSensors.size(); i++){
        QJsonObject sensor = allSensors.at(i).toObject();

        std::string type = sensor.value("type").toString().toStdString();

        if(type == "temperature"){
            std::string name = sensor.value("name").toString().toStdString();
            unsigned int id = (unsigned int)sensor.value("id").toInt();
            std::string desc = sensor.value("description").toString().toStdString();
            QJsonArray dataJson = sensor.value("data").toArray();
            std::vector<double> data;
            for(int i = 0; i<dataJson.size(); i++){
                data.push_back(dataJson.at(i).toDouble());
            }

            TemperatureSensor* newTempSensor = new TemperatureSensor(data, name, desc, id);
            this->addSensor(newTempSensor);
        }


        if(type == "motion"){
            std::string name = sensor.value("name").toString().toStdString();
            unsigned int id = (unsigned int)sensor.value("id").toInt();
            std::string desc = sensor.value("description").toString().toStdString();
            QJsonArray dataJson = sensor.value("data").toArray();
            std::vector<MotionData> data;
            for(int i = 0; i<dataJson.size(); i++){
                QJsonObject d = dataJson.at(i).toObject();
                MotionData di(d.value("x").toDouble(), d.value("y").toDouble(), d.value("z").toDouble());
                data.push_back(di);
            }

            MotionSensor* newMotionSensor = new MotionSensor(data, name, desc, id);
            this->addSensor(newMotionSensor);
        }


        if(type == "smog"){
            std::string name = sensor.value("name").toString().toStdString();
            unsigned int id = (unsigned int)sensor.value("id").toInt();
            std::string desc = sensor.value("description").toString().toStdString();
            QJsonArray dataJson = sensor.value("data").toArray();
            std::vector<double> data;
            for(int i = 0; i<dataJson.size(); i++){
                data.push_back(dataJson.at(i).toDouble());
            }

            SmogSensor* newSmogSensor = new SmogSensor(data, name, desc, id);
            this->addSensor(newSmogSensor);
        }
    }
}

std::string SensorsManager::getPath() const
{
    return path;
}

std::string SensorsManager::createJson()
{
    QJsonObject mainObject;

    QJsonArray sensors;

    JsonSensorVisitor* visitor = new JsonSensorVisitor();

    for(auto i = allSensorsVector.begin(); i != allSensorsVector.end(); i++){
        (*i)->accept(*visitor);
        sensors.push_back(*(visitor->getJsonObj()));
    }

    delete visitor;

    mainObject.insert("allSensors", sensors);
    mainObject.insert("idRef", (int)idRef);

    QJsonDocument jsonDoc;
    jsonDoc.setObject(mainObject);
    return jsonDoc.toJson().toStdString();
}

void SensorsManager::clearAll()
{
    idRef = 0;

    long long unsigned int size = allSensorsVector.size();
    std::vector<Sensor*> toDeleteSensors;

    for(long long unsigned int i = 0; i < size; i++){
        //NOTIFY OBSERVERS
        for(auto o = observers.begin(); o != observers.end(); o++){
            (*o)->notifyDel(allSensorsVector[i]);
        }
        toDeleteSensors.push_back(allSensorsVector[i]);
    }

    allSensorsVector.clear();

    for(long long unsigned int i = 0; i<toDeleteSensors.size(); i++){
        delete toDeleteSensors[i];
    }
}

}
