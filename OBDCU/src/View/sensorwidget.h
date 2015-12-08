#ifndef SENSORWIDGET_H
#define SENSORWIDGET_H

#include <QWidget>
#include "abstractobdwidget.h"

namespace Ui {
class SensorWidget;
}

class SensorWidget : public AbstractOBDWidget
{
    Q_OBJECT

public:
    explicit SensorWidget(QWidget *parent = 0);
    ~SensorWidget();

private:
    Ui::SensorWidget *ui;
};

#endif // SENSORWIDGET_H
