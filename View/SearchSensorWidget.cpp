#include "SearchSensorWidget.h"

#include <QHBoxLayout>
#include <QLabel>

namespace View {


SearchSensorWidget::SearchSensorWidget(QWidget *parent)
    : QWidget{parent}
{
    QHBoxLayout* layout = new QHBoxLayout(this);

    searchInputLE = new QLineEdit();
    searchButton = new QPushButton("SEARCH");

    layout->addWidget(searchInputLE);
    layout->addWidget(searchButton);

    this->setLayout(layout);

    //CONNECTION
    connect(searchButton, &QPushButton::clicked, this, &SearchSensorWidget::searchButtonClicked);
}

void SearchSensorWidget::searchButtonClicked()
{
    emit sendSearchInputToMain(searchInputLE->text().toStdString());
}


}
