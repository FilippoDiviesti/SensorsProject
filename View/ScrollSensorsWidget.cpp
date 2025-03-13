#include "ScrollSensorsWidget.h"
#include "SensorWidget.h"
#include "MainWindow.h"

#include "string"

#include <QVBoxLayout>
#include <QWidget>
#include "Sensors/Sensor.h"

namespace View {

ScrollSensorsWidget::ScrollSensorsWidget(Sensor::SensorsManager& sensorManager, QWidget *parent)
    : QWidget{parent}
{
    selected = nullptr;

    QVBoxLayout* layout = new QVBoxLayout();

    scrollArea = new QScrollArea();
    QWidget* w = new QWidget();
    QVBoxLayout* l = new QVBoxLayout();
    l->setAlignment(Qt::AlignTop);
    w->setLayout(l);
    scrollArea->setWidget(w);


    addButton = new QPushButton("+");


    layout->addWidget(scrollArea);
    layout->addWidget(addButton);


    //STYLING
    layout->setAlignment(addButton, Qt::AlignHCenter);
    const QSize btnSize = QSize(30, 30);
    addButton->setFixedSize(btnSize);

    this->setLayout(layout);

    //CONNECTION
    connect(addButton, &QPushButton::clicked, this, &ScrollSensorsWidget::showCreateSensorDialogWindow);

    //OBSERVERS
    sensorManager.registerObserver(this);
}


void ScrollSensorsWidget::showCreateSensorDialogWindow(){
    createSensorDialogWindow = new CreateSensorDialogWindow();

    //CONNECTION
    connect(createSensorDialogWindow, &CreateSensorDialogWindow::sendCreateSignalToScrollW, this, &ScrollSensorsWidget::getCreatedSignalFromDW);

    //STYLING
    createSensorDialogWindow->setWindowTitle("Create sensor");
    createSensorDialogWindow->resize(300, 300);
    createSensorDialogWindow->setMinimumSize(300, 300);

    createSensorDialogWindow->exec();
}

void ScrollSensorsWidget::getCreatedSignalFromDW(Sensor::Sensor *newSensor)
{
    emit sendCreateSensorToMain(newSensor);
}

void ScrollSensorsWidget::getSensorWClicked(SensorWidget *sensorWidget)
{
    selected = sensorWidget;

    //NOTIFY OBSERVERS
    for(auto o = observers.begin(); o != observers.end(); o++){
        (*o)->notifySelected(selected->getSensor());
    }
}




void ScrollSensorsWidget::notifyAdd(Sensor::Sensor *sensor)
{
    addNewSensorWidget(sensor);
}

void ScrollSensorsWidget::notifyDel(Sensor::Sensor *sensor)
{
    for(int i = 0; i<scrollArea->widget()->layout()->count(); i++){
        if((((Sensor::Sensor*)(((const SensorWidget*)(scrollArea->widget()->layout()->itemAt(i)->widget()))->getSensor()))) == sensor){
            scrollArea->widget()->layout()->itemAt(i)->widget()->deleteLater();
            scrollArea->widget()->layout()->removeWidget(scrollArea->widget()->layout()->itemAt(i)->widget());
        }
    }
}

void ScrollSensorsWidget::notifyEdit(Sensor::Sensor *sensor)
{
    for(int i = 0; i<scrollArea->widget()->layout()->count(); i++){
        if((((Sensor::Sensor*)(((const SensorWidget*)(scrollArea->widget()->layout()->itemAt(i)->widget()))->getSensor()))) == sensor){
            std::string newTitle = QString::number(sensor->getId()).toStdString() + " - " + sensor->getName();
            const_cast<SensorWidget*>((const SensorWidget*)(scrollArea->widget()->layout()->itemAt(i)->widget()))->modifyLabels(newTitle, sensor->getDescription());
        }
    }
}


void ScrollSensorsWidget::addNewSensorWidget(Sensor::Sensor* newSensor)
{
    QVBoxLayout* old = static_cast<QVBoxLayout*>(scrollArea->widget()->layout());

    QWidget* scrollAreaWidget = new QWidget();

    View::SensorWidget* newSensorWidget = new View::SensorWidget(newSensor, scrollAreaWidget);

    //STYLING
    newSensorWidget->setMinimumWidth(scrollArea->width()-20);
    scrollArea->setWidgetResizable(true);
    newSensorWidget->setMaximumHeight(100);

    old->addWidget(newSensorWidget);

    scrollAreaWidget->setLayout(old);
    scrollArea->setWidget(scrollAreaWidget);

    connect(newSensorWidget, &SensorWidget::sendClickedSignal, this, &ScrollSensorsWidget::getSensorWClicked);
}



void ScrollSensorsWidget::registerObserver(Sensor::SensorSelectedObserverInterface *observer)
{
    observers.push_back(observer);
}

void ScrollSensorsWidget::getSearchInput(std::string searchInput)
{
    //RESET SEARCH
    for(int i = 0; i<scrollArea->widget()->layout()->count(); i++){
        const_cast<SensorWidget*>((const SensorWidget*)(scrollArea->widget()->layout()->itemAt(i)->widget()))->setVisible(true);
    }

    //EMPTY INPUT --> ONLY RESET
    if(searchInput != ""){
        for(int i = 0; i<scrollArea->widget()->layout()->count(); i++){
            if(!((QString::fromStdString(((std::string)(((Sensor::Sensor*)(((const SensorWidget*)(scrollArea->widget()->layout()->itemAt(i)->widget()))->getSensor()))->getName())))).contains(QString::fromStdString(searchInput), Qt::CaseInsensitive))){
                const_cast<SensorWidget*>((const SensorWidget*)(scrollArea->widget()->layout()->itemAt(i)->widget()))->setVisible(false);
            }
        }
    }
}


}


