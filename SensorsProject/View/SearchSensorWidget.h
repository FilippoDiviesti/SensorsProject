#ifndef SEARCHSENSORWIDGET_H
#define SEARCHSENSORWIDGET_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include "string"

namespace View {

class SearchSensorWidget : public QWidget
{
    Q_OBJECT
private:
    QLineEdit* searchInputLE;
    QPushButton* searchButton;
public:
    explicit SearchSensorWidget(QWidget *parent = nullptr);
private slots:
    void searchButtonClicked();
signals:
    void sendSearchInputToMain(std::string searchInput);
};

}



#endif // SEARCHSENSORWIDGET_H
