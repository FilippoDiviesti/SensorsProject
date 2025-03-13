#ifndef INFOSENSORWIDGET_H
#define INFOSENSORWIDGET_H

#include "InfoSensorVisitor.h"
#include "ModifySensorDialogWindow.h"

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>

#include <Sensors/Sensor.h>
#include <Sensors/SensorSelectedObserverInterface.h>

namespace View {

class InfoSensorWidget : public QWidget , public Sensor::SensorSelectedObserverInterface
{
    Q_OBJECT
private:
    Sensor::Sensor* sensor;

    InfoSensorVisitor* infoVisitor;

    QHBoxLayout* hl;
    QVBoxLayout* vlSx;
    QVBoxLayout* vlDx;

    QLabel* name;
    QLabel* description;
    QWidget* otherInfo;

    QPushButton* modifyButton;
    QPushButton* deleteButton;
    QPushButton* startSimulationButton;

    ModifySensorDialogWindow* modifySensorDialogWindow;
public:
    InfoSensorWidget(QWidget *parent = nullptr);
    void setOtherInfo(QWidget* otherInfo);
    virtual void notifySelected(Sensor::Sensor* sensor);
    ModifySensorDialogWindow *getModifySensorDialogWindow() const;

public slots:
    void showDeleteMessageBox();
    void showModifyDialogWindow();
    void getModifiedSignal(Sensor::Sensor* sensor, std::string newTitle, std::string newDesc);
    void simButtonClicked();
signals:
    void sensorDelitedSignal(Sensor::Sensor* sensor);
    void sendModifiedToMain(Sensor::Sensor* sensor, std::string newTitle, std::string newDesc);
    void sendSimClickToMain(Sensor::Sensor* sensor);

};

}



#endif // INFOSENSORWIDGET_H
