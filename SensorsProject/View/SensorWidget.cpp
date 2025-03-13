#include "InfoSensorVisitor.h"
#include "SensorWidget.h"
#include "ScrollSensorsWidget.h"

#include <QMessageBox>
#include <QMouseEvent>
#include <QVBoxLayout>

namespace View {

SensorWidget::SensorWidget(Sensor::Sensor* sensor, QWidget *parent)
    : QWidget{parent}
{
    this->sensor = sensor;

    QVBoxLayout *verticalLayout = new QVBoxLayout(this);

    QString title = QString::number(sensor->getId()) + QString::fromStdString(" - ") + QString::fromStdString(sensor->getName());

    nameLabel = new QLabel(title);
    descriptionLabel = new QLabel(QString::fromStdString(sensor->getDescription()));

    verticalLayout->addWidget(nameLabel);
    verticalLayout->addWidget(descriptionLabel);

    verticalLayout->addWidget(new QLabel("______________________________________________"));


    this->setLayout(verticalLayout);

    //STYLING
    nameLabel->setStyleSheet("font-size: 15px; font-weight: 600;");
    descriptionLabel->setStyleSheet("font-size: 12px;");
}

Sensor::Sensor *SensorWidget::getSensor() const
{
    return sensor;
}

void SensorWidget::modifyLabels(std::string newTitle, std::string newDesc)
{
    nameLabel->setText(QString::fromStdString(newTitle));
    descriptionLabel->setText(QString::fromStdString(newDesc));
}

void SensorWidget::mousePressEvent(QMouseEvent *event)
{
    event->accept();
    emit sendClickedSignal(this);
}


}
