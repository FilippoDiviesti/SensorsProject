#ifndef CREATESENSORDIALOGWINDOW_H
#define CREATESENSORDIALOGWINDOW_H

#include <QDialog>
#include <QPushButton>
#include <QLabel>
#include <QComboBox>
#include <QLineEdit>
#include <QTextEdit>

#include <Sensors/Sensor.h>

namespace View {

class CreateSensorDialogWindow : public QDialog
{
    Q_OBJECT
private:
    QComboBox* typeComboBox;
    QLineEdit* nameLineEdit;
    QTextEdit* descriptionTextEdit;
    QPushButton* createButton;
public:
    CreateSensorDialogWindow();
private slots:
    void createbuttonClickedSlot();
signals:
    void sendCreateSignalToScrollW(Sensor::Sensor* newSensor);
};


}


#endif // CREATESENSORDIALOGWINDOW_H
