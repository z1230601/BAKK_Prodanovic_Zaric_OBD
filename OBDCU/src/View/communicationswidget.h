#ifndef COMMUNICATIONSWIDGET_H
#define COMMUNICATIONSWIDGET_H

#include <QWidget>
#include "abstractobdwidget.h"

namespace Ui {
class CommunicationsWidget;
}

class CommunicationsWidget : public AbstractOBDWidget
{
    Q_OBJECT

public:
    explicit CommunicationsWidget(QWidget *parent = 0);
    ~CommunicationsWidget();

private:
    Ui::CommunicationsWidget *ui;
};

#endif // COMMUNICATIONSWIDGET_H
