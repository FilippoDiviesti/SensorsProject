#include "ModifySensorDialogWindow.h"

#include <QHBoxLayout>
#include <QLabel>
#include <QMessageBox>
#include <QPushButton>

namespace View {

ModifySensorDialogWindow::ModifySensorDialogWindow(Sensor::Sensor* sensor) {
    this->sensor = sensor;

    nameLineEdit = new QLineEdit(QString::fromStdString(sensor->getName()));
    descriptionTextEdit = new QTextEdit(QString::fromStdString(sensor->getDescription()));
    modifyButton = new QPushButton("Save Changes");

    QVBoxLayout* vl = new QVBoxLayout();

    QHBoxLayout* hl2 = new QHBoxLayout();
    QHBoxLayout* hl3 = new QHBoxLayout();


    hl2->addWidget(new QLabel("Name : "));
    hl2->addWidget(nameLineEdit);

    hl3->addWidget(new QLabel("Description : "));
    hl3->addWidget(descriptionTextEdit);

    vl->addLayout(hl2);
    vl->addLayout(hl3);
    vl->addWidget(modifyButton);

    this->setLayout(vl);

    //SIGNALS
    connect(modifyButton, &QPushButton::clicked, this, &ModifySensorDialogWindow::showConfirmChangesDialogWindow);
}

void ModifySensorDialogWindow::showConfirmChangesDialogWindow(){
    QMessageBox* msgbox = new QMessageBox();
    msgbox->setWindowTitle("Confirm Changes");
    msgbox->setText("Are you sure you want to save changes?");
    msgbox->setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    auto response = msgbox->exec();

    if(response == QMessageBox::Yes){
        emit sensorModified(this->sensor, nameLineEdit->text().toStdString(), descriptionTextEdit->toPlainText().toStdString());
    }
}

}

