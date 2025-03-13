#ifndef CHARTSENSORWIDGET_H
#define CHARTSENSORWIDGET_H

#include "ChartSensorVisitor.h"

#include <QWidget>
#include <QChart>
#include <QChartView>
#include <QVBoxLayout>


namespace View {

class ChartSensorWidget : public QWidget
{
    Q_OBJECT
private:
    ChartSensorVisitor *chartvisitor;

    void generateChart(Sensor::Sensor* sensor);
public:
    explicit ChartSensorWidget(QWidget *parent = nullptr);
public slots:
    void getSimSignal(Sensor::Sensor* sensor);
    void getDelitedSignal();
};

}



#endif // CHARTSENSORWIDGET_H
