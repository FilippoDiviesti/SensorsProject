#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ActionToolBar.h"
#include "ChartSensorWidget.h"
#include "InfoSensorWidget.h"
#include "ScrollSensorsWidget.h"
#include "SearchSensorWidget.h"

#include <QMainWindow>
#include <QWidget>
#include "string"

#include <Sensors/SensorsManager.h>


namespace View {

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    Sensor::SensorsManager sensorsManager;

    QWidget* mainWidget;

    ActionToolBar* toolBar;

    SearchSensorWidget* searchSectionWidget;
    ScrollSensorsWidget* scrollSectionWidget;
    InfoSensorWidget* infoSensorWidget;
    ChartSensorWidget* chartSensorWidget;

    void closeEvent(QCloseEvent *event) override;
public:
    explicit MainWindow(QWidget *parent = nullptr);

private slots:
    void createSensorSlot(Sensor::Sensor* newSensor);
    void deleteSensorSlot(Sensor::Sensor* sensor);
    void modifiedSensorSlot(Sensor::Sensor* sensor, std::string newTitle, std::string newDesc);

    void saveJson();
    void saveNewJson(std::string path);
    void openJson(std::string path);
};

}



#endif // MAINWINDOW_H
