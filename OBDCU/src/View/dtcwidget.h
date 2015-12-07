#ifndef DTCWIDGET_H
#define DTCWIDGET_H

#include <QWidget>

namespace Ui {
class DTCWidget;
}

class DTCWidget : public QWidget
{
    Q_OBJECT

public:
    explicit DTCWidget(QWidget *parent = 0);
    ~DTCWidget();

private:
    Ui::DTCWidget *ui;
};

#endif // DTCWIDGET_H
