#ifndef EMULATIONWIDGET_H
#define EMULATIONWIDGET_H

#include <QWidget>

namespace Ui {
class EmulationWidget;
}

class EmulationWidget : public QWidget
{
    Q_OBJECT

public:
    explicit EmulationWidget(QWidget *parent = 0);
    ~EmulationWidget();

private:
    Ui::EmulationWidget *ui;
};

#endif // EMULATIONWIDGET_H
