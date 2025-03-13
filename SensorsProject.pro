TEMPLATE = app
TARGET = SensorProject
INCLUDEPATH += .
QT += widgets
QT += charts

SOURCES += \
    Sensors/JsonSensorVisitor.cpp \
    Sensors/MotionData.cpp \
    Sensors/MotionSensor.cpp \
    Sensors/Sensor.cpp \
    Sensors/SensorsManager.cpp \
    Sensors/SmogSensor.cpp \
    Sensors/TemperatureSensor.cpp \
    View/ActionToolBar.cpp \
    View/ChartSensorVisitor.cpp \
    View/ChartSensorWidget.cpp \
    View/CreateSensorDialogWindow.cpp \
    View/InfoSensorVisitor.cpp \
    View/InfoSensorWidget.cpp \
    View/MainWindow.cpp \
    View/ModifySensorDialogWindow.cpp \
    View/ScrollSensorsWidget.cpp \
    View/SearchSensorWidget.cpp \
    View/SensorWidget.cpp \
    main.cpp

HEADERS += \
    Sensors/JsonSensorVisitor.h \
    Sensors/MotionData.h \
    Sensors/MotionSensor.h \
    Sensors/Sensor.h \
    Sensors/SensorSelectedObserverInterface.h \
    Sensors/SensorVisitorInterface.h \
    Sensors/SensorsManager.h \
    Sensors/SensorsManagerObserverInterface.h \
    Sensors/SmogSensor.h \
    Sensors/TemperatureSensor.h \
    View/ActionToolBar.h \
    View/ChartSensorVisitor.h \
    View/ChartSensorWidget.h \
    View/CreateSensorDialogWindow.h \
    View/InfoSensorVisitor.h \
    View/InfoSensorWidget.h \
    View/MainWindow.h \
    View/ModifySensorDialogWindow.h \
    View/ScrollSensorsWidget.h \
    View/SearchSensorWidget.h \
    View/SensorWidget.h
