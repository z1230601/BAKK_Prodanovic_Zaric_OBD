#ifndef EMULATIONWIDGET_H
#define EMULATIONWIDGET_H

#include <QWidget>
#include "abstractobdwidget.h"

namespace Ui {
class EmulationWidget;
}

class EmulationWidget : public AbstractOBDWidget
{
    Q_OBJECT

public:
    explicit EmulationWidget(QWidget *parent = 0);
    ~EmulationWidget();

private:
    Ui::EmulationWidget *ui;
};

#endif // EMULATIONWIDGET_H
