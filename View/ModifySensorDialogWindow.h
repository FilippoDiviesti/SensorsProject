#ifndef MODIFYSENSORDIALOGWINDOW_H
#define MODIFYSENSORDIALOGWINDOW_H

#include <QDialog>
#include <QLineEdit>
#include <QTextEdit>
#include <string>

#include <Sensors/Sensor.h>


namespace View {

class ModifySensorDialogWindow : public QDialog
{
    Q_OBJECT
private:
    Sensor::Sensor* sensor;

    QLineEdit* nameLineEdit;
    QTextEdit* descriptionTextEdit;
    QPushButton* modifyButton;
public:
    ModifySensorDialogWindow(Sensor::Sensor* sensor);
public slots:
    void showConfirmChangesDialogWindow();
signals:
    void sensorModified(Sensor::Sensor* sensor, std::string newTitle, std::string newDesc);
};

}



#endif // MODIFYSENSORDIALOGWINDOW_H
