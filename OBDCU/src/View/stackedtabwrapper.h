#ifndef STACKEDTABWRAPPER_H
#define STACKEDTABWRAPPER_H

#include <QWidget>
#include <QStateMachine>

namespace Ui {
class StackedTabWrapper;
}

class StackedTabWrapper : public QWidget
{
    Q_OBJECT

public:
    explicit StackedTabWrapper( QWidget *parent = 0);
    ~StackedTabWrapper();


private:
    Ui::StackedTabWrapper *ui;

    QWidget* mainWidget_;
    QWidget* actionMenu_;
    QStateMachine stateMachine;

    void setupStateMachine();


};

#endif // STACKEDTABWRAPPER_H
