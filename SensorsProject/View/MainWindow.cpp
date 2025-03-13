#include "MainWindow.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>

#include "Sensors/TemperatureSensor.h"

namespace View {

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow{parent}
{
    //SENSORS MANAGER
    sensorsManager = Sensor::SensorsManager();

    //TOOLBAR
    toolBar = new ActionToolBar();
    this->addToolBar(toolBar);


    QGridLayout* mainLayout = new QGridLayout();

    //SX PART
    searchSectionWidget = new SearchSensorWidget();
    scrollSectionWidget = new ScrollSensorsWidget(this->sensorsManager);

    //DX PART
    infoSensorWidget = new InfoSensorWidget();
    chartSensorWidget = new ChartSensorWidget();




    //ADD WIDGETS
    mainLayout->addWidget(searchSectionWidget, 0, 0);
    mainLayout->addWidget(infoSensorWidget, 0, 1);
    mainLayout->addWidget(scrollSectionWidget, 1, 0);
    mainLayout->addWidget(chartSensorWidget, 1, 1);


    //STYLING
    mainLayout->setColumnMinimumWidth(1, 700);
    mainLayout->setHorizontalSpacing(10);


    mainWidget = new QWidget(this);
    mainWidget->setLayout(mainLayout);

    setCentralWidget(mainWidget);

    //CONNECTION
    connect(scrollSectionWidget, &ScrollSensorsWidget::sendCreateSensorToMain, this, &MainWindow::createSensorSlot);
    connect(searchSectionWidget, &SearchSensorWidget::sendSearchInputToMain, scrollSectionWidget, &ScrollSensorsWidget::getSearchInput);
    connect(infoSensorWidget, &InfoSensorWidget::sensorDelitedSignal, this, &MainWindow::deleteSensorSlot);
    connect(infoSensorWidget, &InfoSensorWidget::sendModifiedToMain, this, &MainWindow::modifiedSensorSlot);
    connect(infoSensorWidget, &InfoSensorWidget::sendSimClickToMain, chartSensorWidget, &ChartSensorWidget::getSimSignal);
    connect(infoSensorWidget, &InfoSensorWidget::sensorDelitedSignal, chartSensorWidget, &ChartSensorWidget::getDelitedSignal);
    connect(toolBar, &ActionToolBar::saveSignal, this, &MainWindow::saveJson);
    connect(toolBar, &ActionToolBar::saveNewSignal, this, &MainWindow::saveNewJson);
    connect(toolBar, &ActionToolBar::openSignal, this, &MainWindow::openJson);

    //OBSERVER
    scrollSectionWidget->registerObserver(infoSensorWidget);
}

void MainWindow::createSensorSlot(Sensor::Sensor *newSensor)
{
    newSensor->setId(sensorsManager.getIdRef());
    sensorsManager.incrementIdRef();
    sensorsManager.addSensor(newSensor);
}

void MainWindow::deleteSensorSlot(Sensor::Sensor *sensor)
{
    sensorsManager.deleteSensor(sensor);
}

void MainWindow::modifiedSensorSlot(Sensor::Sensor *sensor, std::string newTitle, std::string newDesc)
{
    sensorsManager.editSensor(sensor, newTitle, newDesc);
}

void MainWindow::saveJson()
{
    if(this->sensorsManager.getPath() != ""){
        this->sensorsManager.saveFile();

        QMessageBox* msgbox = new QMessageBox();
        msgbox->setWindowTitle("Saved");
        msgbox->setText("Changes saved");
        msgbox->exec();
    }else{
        this->toolBar->showSaveNewMessageBox();
    }

}

void MainWindow::saveNewJson(std::string path)
{
    this->sensorsManager.saveNewFile(path);
}

void MainWindow::openJson(std::string path)
{
    if(path != ""){
        this->sensorsManager.openFile(path);
    }
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    event->ignore();

    QMessageBox* msgbox = new QMessageBox();
    msgbox->setWindowTitle("Confirm Exit");
    msgbox->setText("Are you sure you want to exit? \n File might not be saved!");
    msgbox->setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    auto response = msgbox->exec();

    if(response == QMessageBox::Yes){
        event->accept();
    }
}


}


