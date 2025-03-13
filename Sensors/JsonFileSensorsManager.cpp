#include "JsonFileSensorsManager.h"

#include "JsonSensorVisitor.h"

#include <QFileDialog>
#include <QMessageBox>

#include <QFile>
#include <QTextStream>
#include <QIODevice>

#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>

namespace Sensor {

JsonFileSensorsManager::JsonFileSensorsManager() {
    this->path = "";
}

void JsonFileSensorsManager::saveJsonFile(std::vector<Sensor*>* allSensorsVector, unsigned int* idRef)
{
    if(this->path == ""){
        saveNewJsonFile(allSensorsVector, idRef);
    }
    else{

        std::string json = createJson(allSensorsVector, idRef);

        QFile file(QString::fromStdString(path));
        if(file.open(QIODevice::WriteOnly | QIODevice::Text)){
            QTextStream stream(&file);
            stream << QString::fromStdString(json);
            file.close();
        }

        QMessageBox* msgbox = new QMessageBox();
        msgbox->setWindowTitle("Saved");
        msgbox->setText("Changes saved");
        msgbox->exec();
    }
}

void JsonFileSensorsManager::saveNewJsonFile(std::vector<Sensor*>* allSensorsVector, unsigned int* idRef)
{
    QString defaultDirectory("SavedJsonFiles");
    QFileDialog* fileDialog = new QFileDialog();
    fileDialog->setDirectory(defaultDirectory);
    QString f = fileDialog->getSaveFileName(nullptr, "Save JSON File", defaultDirectory, "JSON File (*.json)");
    if(f != ""){
        this->path = f.toStdString();

        std::string json = createJson(allSensorsVector, idRef);

        QFile file(QString::fromStdString(path));
        if(file.open(QIODevice::WriteOnly | QIODevice::Text)){
            QTextStream stream(&file);
            stream << QString::fromStdString(json);
            file.close();
        }

        QMessageBox* msgbox = new QMessageBox();
        msgbox->setWindowTitle("Saved");
        msgbox->setText("File Saved");
        msgbox->exec();
    }
}

void JsonFileSensorsManager::openJsonFile()
{
    QString defaultDirectory("SavedJsonFiles");
    QFileDialog* filedialog = new QFileDialog();
    filedialog->setDirectory(defaultDirectory);
    QString f = filedialog->getOpenFileName(nullptr, "Select Json File", defaultDirectory, "JSON File (*.json);;All Files (*)");
    if(f != ""){
        this->path = f.toStdString();

        // APRIRE TUTT U COSSS !!!!
    }
}



std::string JsonFileSensorsManager::createJson(std::vector<Sensor *> *allSensorsVector, unsigned int *idRef)
{
    QJsonObject mainObject;

    QJsonArray sensors;

    JsonSensorVisitor* visitor = new JsonSensorVisitor();

    for(auto i = allSensorsVector->begin(); i != allSensorsVector->end(); i++){
        (*i)->accept(*visitor);
        sensors.push_back(*(visitor->getJsonObj()));
    }

    mainObject.insert("allSensors", sensors);
    mainObject.insert("idRef", (int)*idRef);

    QJsonDocument jsonDoc;
    jsonDoc.setObject(mainObject);
    return jsonDoc.toJson().toStdString();
}



std::string JsonFileSensorsManager::getPath() const
{
    return path;
}

void JsonFileSensorsManager::setPath(const std::string &newPath)
{
    path = newPath;
}

}

