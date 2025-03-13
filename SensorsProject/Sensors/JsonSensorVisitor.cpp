#include "JsonSensorVisitor.h"

#include <QJsonArray>

namespace Sensor {


JsonSensorVisitor::JsonSensorVisitor() {
    jsonObj = new QJsonObject();
}

void JsonSensorVisitor::visit(const TemperatureSensor &tempSensor)
{
    if(jsonObj != nullptr){
        delete jsonObj;
    }
    jsonObj = new QJsonObject();

    QJsonArray data;
    for(int i = 0; i<10; i++){
        data.push_back(tempSensor.getData()[i]);
    }

    jsonObj->insert("id", (int)tempSensor.getId());
    jsonObj->insert("type", "temperature");
    jsonObj->insert("name", QString::fromStdString(tempSensor.getName()));
    jsonObj->insert("description", QString::fromStdString(tempSensor.getDescription()));
    jsonObj->insert("data", data);
}

void JsonSensorVisitor::visit(const MotionSensor &motionSensor)
{
    if(jsonObj  != nullptr){
        delete jsonObj;
    }
    jsonObj = new QJsonObject();

    jsonObj->insert("id", (int)motionSensor.getId());
    jsonObj->insert("type", "motion");
    jsonObj->insert("name", QString::fromStdString(motionSensor.getName()));
    jsonObj->insert("description", QString::fromStdString(motionSensor.getDescription()));
    QJsonArray data;

    for(int i = 0; i<10; i++){
        QJsonObject ril;
        ril.insert("x", motionSensor.getData()[i].getXRotation());
        ril.insert("y", motionSensor.getData()[i].getYRotation());
        ril.insert("z", motionSensor.getData()[i].getZRotation());
        data.push_back(ril);
    }

    jsonObj->insert("data", data);
}

void JsonSensorVisitor::visit(const SmogSensor &smogSensor)
{
    if(jsonObj  != nullptr){
        delete jsonObj;
    }
    jsonObj = new QJsonObject();

    QJsonArray data;
    for(int i = 0; i<10; i++){
        data.push_back(smogSensor.getData()[i]);
    }
    jsonObj->insert("id", (int)smogSensor.getId());
    jsonObj->insert("type", "smog");
    jsonObj->insert("name", QString::fromStdString(smogSensor.getName()));
    jsonObj->insert("description", QString::fromStdString(smogSensor.getDescription()));
    jsonObj->insert("data", data);
}


QJsonObject* JsonSensorVisitor::getJsonObj() const
{
    return jsonObj;
}

}
