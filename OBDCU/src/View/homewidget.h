#ifndef HOMEWIDGET_H
#define HOMEWIDGET_H

#include <QWidget>

#include "abstractobdwidget.h"

namespace Ui {
class HomeWidget;
}

class HomeWidget : public AbstractOBDWidget
{

public:
    explicit HomeWidget(QWidget *parent = 0);
    ~HomeWidget();

    QWidget* createActionSideBar(QWidget* parent = 0);
protected:
    void openActionArea();

private:
    Ui::HomeWidget *ui;

};

#endif // HOMEWIDGET_H
