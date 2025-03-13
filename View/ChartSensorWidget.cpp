#include "ChartSensorWidget.h"

#include <QChartView>

namespace View {

ChartSensorWidget::ChartSensorWidget(QWidget *parent)
    : QWidget{parent}
{
    chartvisitor = new ChartSensorVisitor();
}

void ChartSensorWidget::generateChart(Sensor::Sensor *sensor)
{
    if(this->layout()){
        delete this->layout();
    }

    QVBoxLayout* layout = new QVBoxLayout();
    sensor->accept(*chartvisitor);
    QChartView* chartView = new QChartView(chartvisitor->getChart());
    chartView->setRenderHint(QPainter::Antialiasing);
    layout->addWidget(chartView);
    this->setLayout(layout);
}

void ChartSensorWidget::getSimSignal(Sensor::Sensor *sensor)
{
    generateChart(sensor);
}

void ChartSensorWidget::getDelitedSignal()
{
    if(this->layout()){
        delete this->layout();
    }

    QVBoxLayout* layout = new QVBoxLayout();
    QChartView* chartView = new QChartView();
    layout->addWidget(chartView);
    this->setLayout(layout);
}

}


