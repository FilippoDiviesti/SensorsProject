#ifndef SENSORWIDGET_H
#define SENSORWIDGET_H

#include "InfoSensorVisitor.h"
#include "InfoSensorWidget.h"

#include <QWidget>
#include <QLabel>
#include <string>

#include <Sensors/Sensor.h>

namespace View {

class SensorWidget : public QWidget
{
    Q_OBJECT
private:
    Sensor::Sensor* sensor;
    QLabel* nameLabel;
    QLabel* descriptionLabel;
    InfoSensorVisitor* visitor;
public:
    explicit SensorWidget(Sensor::Sensor* sensor, QWidget *parent = nullptr);
    void mousePressEvent(QMouseEvent *event) override;
    Sensor::Sensor *getSensor() const;
    void modifyLabels(std::string newTitle, std::string newDesc);
signals:
    void sendClickedSignal(SensorWidget* sensorWidget);
};

}


#endif // SENSORWIDGET_H
