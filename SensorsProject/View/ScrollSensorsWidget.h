#ifndef SCROLLSENSORSWIDGET_H
#define SCROLLSENSORSWIDGET_H

#include "CreateSensorDialogWindow.h"
#include "SensorWidget.h"

#include <vector>

#include <QPushButton>
#include <QScrollArea>
#include <QWidget>
#include "string"

#include <Sensors/SensorSelectedObserverInterface.h>
#include <Sensors/SensorsManager.h>

namespace View {

class ScrollSensorsWidget : public QWidget , public Sensor::SensorsManagerObserverInterface
{
    Q_OBJECT
private:
    QScrollArea* scrollArea;
    QPushButton* addButton;
    CreateSensorDialogWindow* createSensorDialogWindow;
    SensorWidget* selected;

    std::vector<Sensor::SensorSelectedObserverInterface*> observers;

    void addNewSensorWidget(Sensor::Sensor* newSensor);
public:
    explicit ScrollSensorsWidget(Sensor::SensorsManager& sensorManager, QWidget *parent = nullptr);
    virtual void notifyAdd(Sensor::Sensor* sensor);
    virtual void notifyDel(Sensor::Sensor* sensor);
    virtual void notifyEdit(Sensor::Sensor* sensor);
    void registerObserver(Sensor::SensorSelectedObserverInterface* observer);
public slots:
    void showCreateSensorDialogWindow();
    void getSensorWClicked(SensorWidget* sensorWidget);
    void getSearchInput(std::string searchInput);
private slots:
    void getCreatedSignalFromDW(Sensor::Sensor* newSensor);
signals:
    void sendCreateSensorToMain(Sensor::Sensor* newSensor);
};

}



#endif // SCROLLSENSORSWIDGET_H
