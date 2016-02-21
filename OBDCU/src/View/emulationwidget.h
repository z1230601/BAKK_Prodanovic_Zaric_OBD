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

private slots:

    void on_saveBtn_clicked();

    void on_runBtn_clicked();

    void on_stopBtn_clicked();

    void on_refreshBtn_clicked();

private:
    Ui::EmulationWidget *ui;

    void fillDataFromModel();
};

#endif // EMULATIONWIDGET_H
