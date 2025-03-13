#include <QApplication>
#include <QMainWindow>

#include <View/MainWindow.h>
#include <View/SensorWidget.h>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    View::MainWindow* mainWindow = new View::MainWindow();

    //STYLE
    mainWindow->setMinimumSize(1000, 600);
    mainWindow->setMaximumSize(1000, 600);

    mainWindow->show();
    return app.exec();
}
