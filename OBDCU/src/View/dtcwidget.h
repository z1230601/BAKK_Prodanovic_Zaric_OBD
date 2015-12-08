#ifndef DTCWIDGET_H
#define DTCWIDGET_H

#include <QWidget>
#include "abstractobdwidget.h"

namespace Ui {
class DTCWidget;
}

class DTCWidget : public AbstractOBDWidget
{
    Q_OBJECT

public:
    explicit DTCWidget(QWidget *parent = 0);
    ~DTCWidget();

private:
    Ui::DTCWidget *ui;
};

#endif // DTCWIDGET_H
