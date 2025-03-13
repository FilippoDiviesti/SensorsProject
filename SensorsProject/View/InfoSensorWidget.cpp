#include "InfoSensorWidget.h"

#include <QHBoxLayout>
#include <QMessageBox>

namespace View {



InfoSensorWidget::InfoSensorWidget(QWidget *parent): QWidget{parent} {
    sensor = nullptr;
    infoVisitor = new InfoSensorVisitor();

    name = new QLabel();
    description = new QLabel();
    otherInfo = new QWidget();

    modifyButton = new QPushButton("EDIT");
    deleteButton = new QPushButton("DELETE");
    startSimulationButton = new QPushButton("START SIMULATION");


    hl = new QHBoxLayout();

    vlSx = new QVBoxLayout();
    vlDx = new QVBoxLayout();


    vlSx->addWidget(name);
    vlSx->addWidget(description);
    vlSx->addWidget(otherInfo);


    vlDx->addWidget(modifyButton);
    vlDx->addWidget(deleteButton);
    vlDx->addWidget(startSimulationButton);


    //STYLING
    name->setStyleSheet("font-size: 25px; font-weight: 900;");
    //

    hl->addLayout(vlSx, 90);
    hl->addLayout(vlDx);
    this->setLayout(hl);

    //SET BUTTONS VISIBILITY
    modifyButton->setVisible(false);
    deleteButton->setVisible(false);
    startSimulationButton->setVisible(false);

    //SIGNALS
    connect(deleteButton, &QPushButton::clicked, this, &InfoSensorWidget::showDeleteMessageBox);
    connect(modifyButton, &QPushButton::clicked, this, &InfoSensorWidget::showModifyDialogWindow);
    connect(startSimulationButton, &QPushButton::clicked, this, &InfoSensorWidget::simButtonClicked);
}

void InfoSensorWidget::setOtherInfo(QWidget *otherInfo)
{
    delete this->otherInfo;
    this->otherInfo = otherInfo;
}

void InfoSensorWidget::notifySelected(Sensor::Sensor *sensor)
{
    this->sensor = sensor;
    name->setText(QString::fromStdString(sensor->getName()));
    description->setText(QString::fromStdString(sensor->getDescription()));
    sensor->accept(*infoVisitor);
    otherInfo = infoVisitor->getOtherInfo();
    vlSx->addWidget(otherInfo);

    //SET BUTTONS VISIBILITY
    modifyButton->setVisible(true);
    deleteButton->setVisible(true);
    startSimulationButton->setVisible(true);
}



void InfoSensorWidget::showDeleteMessageBox(){
    QMessageBox* msgbox = new QMessageBox();
    msgbox->setWindowTitle("Confirm Delete");
    msgbox->setText("Are you sure you want to delete this sensor?");
    msgbox->setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    auto response = msgbox->exec();

    if(response == QMessageBox::Yes){
        name->setText(QString::fromStdString(""));
        description->setText(QString::fromStdString(""));
        delete this->infoVisitor;
        vlSx->removeWidget(otherInfo);
        delete otherInfo;
        this->infoVisitor = new InfoSensorVisitor();
        this->otherInfo = new QWidget();

        emit sensorDelitedSignal(this->sensor);
        this->sensor = nullptr;

        //SET BUTTONS VISIBILITY
        modifyButton->setVisible(false);
        deleteButton->setVisible(false);
        startSimulationButton->setVisible(false);
    }
}

void InfoSensorWidget::showModifyDialogWindow(){
    modifySensorDialogWindow = new ModifySensorDialogWindow(sensor);

    connect(modifySensorDialogWindow, &ModifySensorDialogWindow::sensorModified, this, &InfoSensorWidget::getModifiedSignal);

    modifySensorDialogWindow->setWindowTitle("Create sensor");
    modifySensorDialogWindow->resize(300, 300);
    modifySensorDialogWindow->setMinimumSize(300, 300);

    modifySensorDialogWindow->exec();

}

void InfoSensorWidget::getModifiedSignal(Sensor::Sensor *sensor, std::string newTitle, std::string newDesc)
{
    this->name->setText(QString::fromStdString(newTitle));
    this->description->setText(QString::fromStdString(newDesc));
    modifySensorDialogWindow->close();
    emit sendModifiedToMain(sensor, newTitle, newDesc);
}

void InfoSensorWidget::simButtonClicked()
{
    emit sendSimClickToMain(this->sensor);
}

ModifySensorDialogWindow *InfoSensorWidget::getModifySensorDialogWindow() const
{
    return modifySensorDialogWindow;
}

}


