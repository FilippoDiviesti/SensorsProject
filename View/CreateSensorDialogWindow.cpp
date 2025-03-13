#include "CreateSensorDialogWindow.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QMessageBox>

#include <Sensors/MotionSensor.h>
#include <Sensors/SmogSensor.h>
#include <Sensors/TemperatureSensor.h>

namespace View {

CreateSensorDialogWindow::CreateSensorDialogWindow(){
    typeComboBox = new QComboBox();
    typeComboBox->addItem("Temperature");
    typeComboBox->addItem("Motion");
    typeComboBox->addItem("Smog");

    nameLineEdit = new QLineEdit();

    descriptionTextEdit = new QTextEdit();

    createButton = new QPushButton("Create");


    QVBoxLayout* vl = new QVBoxLayout();

    QHBoxLayout* hl1 = new QHBoxLayout();
    QHBoxLayout* hl2 = new QHBoxLayout();
    QHBoxLayout* hl3 = new QHBoxLayout();

    hl1->addWidget(new QLabel("Type : "));
    hl1->addWidget(typeComboBox);

    hl2->addWidget(new QLabel("Name : "));
    hl2->addWidget(nameLineEdit);

    hl3->addWidget(new QLabel("Description : "));
    hl3->addWidget(descriptionTextEdit);


    vl->addLayout(hl1);
    vl->addLayout(hl2);
    vl->addLayout(hl3);
    QLabel* txt = new QLabel("It will be created with random data. \nTYPE will not be editable.");
    vl->addWidget(txt);
    vl->addWidget(createButton);

    //STYLING
    txt->setAlignment(Qt::AlignCenter);

    this->setLayout(vl);

    //CONNECTION
    connect(createButton, &QPushButton::clicked, this, &CreateSensorDialogWindow::createbuttonClickedSlot);
}

void CreateSensorDialogWindow::createbuttonClickedSlot(){
    if(typeComboBox->currentText() != "" && nameLineEdit->text().toStdString() != ""){
        std::string name = nameLineEdit->text().toStdString();
        std::string desc = descriptionTextEdit->toPlainText().toStdString();
        unsigned int id = 1; //default id - the real one it will be setted by manager

        Sensor::Sensor* newSensor;

        if(typeComboBox->currentText() == "Temperature"){
            newSensor = new Sensor::TemperatureSensor(name, desc, id);
            emit sendCreateSignalToScrollW(newSensor);
        }
        if(typeComboBox->currentText() == "Motion"){
            newSensor = new Sensor::MotionSensor(name, desc, id);
            emit sendCreateSignalToScrollW(newSensor);
        }
        if(typeComboBox->currentText() == "Smog"){
            newSensor = new Sensor::SmogSensor(name, desc, id);
            emit sendCreateSignalToScrollW(newSensor);
        }

    }else{
        QMessageBox* msgbox = new QMessageBox();
        msgbox->setWindowTitle("Error");
        msgbox->setText("Insert name");
        msgbox->exec();
    }
}


}

