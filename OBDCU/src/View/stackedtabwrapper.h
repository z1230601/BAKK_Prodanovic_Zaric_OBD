#ifndef STACKEDTABWRAPPER_H
#define STACKEDTABWRAPPER_H

#include <abstractobdwidget.h>

#include <QWidget>
#include <QStateMachine>

namespace Ui {
class StackedTabWrapper;
}

class StackedTabWrapper : public QWidget
{
    Q_OBJECT

public:
    explicit StackedTabWrapper(QString widgetId, QWidget *parent = 0);
    ~StackedTabWrapper();

    QString getTabName() const;
private:
    Ui::StackedTabWrapper *ui;

    QString tabName_;
    QStateMachine stateMachine;

    void setupStateMachine();

    AbstractOBDWidget* createWidget(QString widgetId);
    AbstractOBDWidget* tabContentWidget_;

};

#endif // STACKEDTABWRAPPER_H
