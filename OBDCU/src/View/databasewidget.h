#ifndef DATABASEWIDGET_H
#define DATABASEWIDGET_H

#include <QWidget>
#include "abstractobdwidget.h"

namespace Ui {
class DatabaseWidget;
}

class DatabaseWidget : public AbstractOBDWidget
{
    Q_OBJECT

public:
    explicit DatabaseWidget(QWidget *parent = 0);
    ~DatabaseWidget();

private:
    Ui::DatabaseWidget *ui;
};

#endif // DATABASEWIDGET_H
