#include "ChartSensorVisitor.h"

#include <QBarSeries>
#include <QBarSet>
#include <QLineSeries>

#include <Sensors/MotionSensor.h>

namespace View {

ChartSensorVisitor::ChartSensorVisitor() {
    chart = new QChart();
}

void ChartSensorVisitor::visit(const Sensor::TemperatureSensor &tempSensor)
{
    delete chart;


    chart = new QChart();

    QLineSeries* series = new QLineSeries();
    for(long long unsigned int i = 0; i<tempSensor.getData().size(); i++){
        series->append(i, tempSensor.getData()[i]);
    }
    chart->legend()->hide();
    chart->addSeries(series);
    chart->createDefaultAxes();
    chart->setTitle("CHART");
    chart->setAnimationOptions(QChart::SeriesAnimations);
}

void ChartSensorVisitor::visit(const Sensor::MotionSensor &motionSensor)
{

    delete chart;

    chart = new QChart();

    QBarSet* xSet = new QBarSet("X");
    QBarSet* ySet = new QBarSet("Y");
    QBarSet* zSet = new QBarSet("Z");

    for(long long unsigned int i = 0; i<motionSensor.getData().size(); i++){
        *xSet << motionSensor.getData()[i].getXRotation();
        *ySet << motionSensor.getData()[i].getYRotation();
        *zSet << motionSensor.getData()[i].getZRotation();
    }

    QBarSeries* series = new QBarSeries();
    series->append(xSet);
    series->append(ySet);
    series->append(zSet);

    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);
    chart->addSeries(series);
    chart->setTitle("CHART");
    chart->setAnimationOptions(QChart::SeriesAnimations);
    chart->createDefaultAxes();
}

void ChartSensorVisitor::visit(const Sensor::SmogSensor &smogSensor)
{
    delete chart;

    chart = new QChart();

    QBarSet* set = new QBarSet("data");

    for(long long unsigned int i = 0; i<smogSensor.getData().size(); i++){
        *set << smogSensor.getData()[i];
    }

    QBarSeries* series = new QBarSeries();
    series->append(set);

    chart->legend()->hide();
    chart->addSeries(series);
    chart->setTitle("CHART");
    chart->setAnimationOptions(QChart::SeriesAnimations);
    chart->createDefaultAxes();
}

QChart *ChartSensorVisitor::getChart() const
{
    return chart;
}

}
