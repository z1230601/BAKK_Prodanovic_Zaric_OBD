#ifndef ERRORPAGE_H
#define ERRORPAGE_H

#include <QWidget>
#include "abstractobdwidget.h"

namespace Ui {
class ErrorPage;
}

class ErrorPage : public AbstractOBDWidget
{
    Q_OBJECT

public:
    explicit ErrorPage(QWidget *parent = 0);
    ~ErrorPage();

private:
    Ui::ErrorPage *ui;
};

#endif // ERRORPAGE_H
