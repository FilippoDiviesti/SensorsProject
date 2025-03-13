#include "ActionToolBar.h"

#include <QCoreApplication>
#include <QFileDialog>
#include <QMessageBox>

namespace View {

ActionToolBar::ActionToolBar(QToolBar *parent) : QToolBar(parent)
{
    saveButton = new QPushButton("Save");
    saveNewButton = new QPushButton("Save new");
    openButton = new QPushButton("Open");

    this->addWidget(saveButton);
    this->addWidget(saveNewButton);
    this->addSeparator();
    this->addWidget(openButton);
    this->setMovable(false);

    //SIGNALS
    connect(saveButton, &QPushButton::clicked, this, &ActionToolBar::showSaveMessageBox);
    connect(saveNewButton, &QPushButton::clicked, this, &ActionToolBar::showSaveNewMessageBox);
    connect(openButton, &QPushButton::clicked, this, &ActionToolBar::showOpenMessageBox);
}

void ActionToolBar::showSaveMessageBox(){

    emit saveSignal();
}

void ActionToolBar::showSaveNewMessageBox(){

    QDir startDir(QCoreApplication::applicationDirPath());
    startDir.cdUp();
    startDir.cdUp();

    QFileDialog* fileDialog = new QFileDialog();
    QString file = fileDialog->getSaveFileName(this, "Save JSON File", startDir.absolutePath(), "JSON File (*.json)");
    emit saveNewSignal(file.toStdString());
    delete fileDialog;
}

void ActionToolBar::showOpenMessageBox(){

    QMessageBox* msgbox = new QMessageBox();
    msgbox->setWindowTitle("Confirm Open");
    msgbox->setText("Are you sure you want to opena new file? \n The current file may not be saved!");
    msgbox->setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    auto response = msgbox->exec();

    if(response == QMessageBox::Yes){
        QDir startDir(QCoreApplication::applicationDirPath());
        startDir.cdUp();
        startDir.cdUp();

        QFileDialog* fileDialog = new QFileDialog();
        QString file = fileDialog->getOpenFileName(this, "Save JSON File", startDir.absolutePath(), "JSON File (*.json)");
        emit openSignal(file.toStdString());
        delete fileDialog;
    }
}



}

