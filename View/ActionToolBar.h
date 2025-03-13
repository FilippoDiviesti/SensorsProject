#ifndef ACTIONTOOLBAR_H
#define ACTIONTOOLBAR_H

#include <QPushButton>
#include <QToolBar>

#include "string"


namespace View {

class ActionToolBar : public QToolBar
{
    Q_OBJECT
private:
    QPushButton* saveButton;
    QPushButton* saveNewButton;
    QPushButton* openButton;
public:
    explicit ActionToolBar(QToolBar *parent = nullptr);
public slots:
    void showSaveMessageBox();
    void showSaveNewMessageBox();
    void showOpenMessageBox();
signals:
    void saveSignal();
    void saveNewSignal(std::string path);
    void openSignal(std::string path);
};

}



#endif // ACTIONTOOLBAR_H
