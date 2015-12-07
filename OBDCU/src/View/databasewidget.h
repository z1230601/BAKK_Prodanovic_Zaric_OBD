#ifndef DATABASEWIDGET_H
#define DATABASEWIDGET_H

#include <QWidget>

namespace Ui {
class DatabaseWidget;
}

class DatabaseWidget : public QWidget
{
    Q_OBJECT

public:
    explicit DatabaseWidget(QWidget *parent = 0);
    ~DatabaseWidget();

private:
    Ui::DatabaseWidget *ui;
};

#endif // DATABASEWIDGET_H
