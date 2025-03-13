#include "InfoSensorVisitor.h"

#include <QHBoxLayout>
#include <QLabel>

namespace View {

InfoSensorVisitor::InfoSensorVisitor() {
    otherInfoWidget = new QWidget();
}

void InfoSensorVisitor::visit(const Sensor::TemperatureSensor& tempSensor)
{
    if(otherInfoWidget){
        delete otherInfoWidget;
    }

    otherInfoWidget = new QWidget();
    QHBoxLayout* l = new QHBoxLayout();
    QLabel* type = new QLabel("TYPE: Temperature");
    QLabel* min = new QLabel(QString::fromStdString("MIN: " + std::to_string(tempSensor.getMinData()) + "°C"));
    QLabel* max = new QLabel(QString::fromStdString("MAX: " + std::to_string(tempSensor.getMaxData()) + "°C"));

    l->addWidget(type);
    l->addWidget(min);
    l->addWidget(max);

    otherInfoWidget->setLayout(l);
}

void InfoSensorVisitor::visit(const Sensor::MotionSensor& motionSensor)
{
    if(otherInfoWidget){
        delete otherInfoWidget;
    }

    otherInfoWidget = new QWidget();
    QHBoxLayout* l = new QHBoxLayout();

    QLabel* type = new QLabel("TYPE: Motion");
    QLabel* last = new QLabel(QString::fromStdString("LAST: " + motionSensor.getLastMotionData().toString()));
    QLabel* delta = new QLabel(QString::fromStdString("DELTA: " + motionSensor.getDeltaMotion().toString()));

    l->addWidget(type);
    l->addWidget(last);
    l->addWidget(delta);

    otherInfoWidget->setLayout(l);
}

void InfoSensorVisitor::visit(const Sensor::SmogSensor& smogSensor)
{
    if(otherInfoWidget){
        delete otherInfoWidget;
    }

    otherInfoWidget = new QWidget();
    QHBoxLayout* l = new QHBoxLayout();

    QLabel* type = new QLabel("TYPE: Smog");
    QLabel* avg = new QLabel(QString::fromStdString("AVG: " + std::to_string(smogSensor.getAverageData()) + "%"));

    l->addWidget(type);
    l->addWidget(avg);

    otherInfoWidget->setLayout(l);
}

QWidget *InfoSensorVisitor::getOtherInfo()
{
    return otherInfoWidget;
}


}
