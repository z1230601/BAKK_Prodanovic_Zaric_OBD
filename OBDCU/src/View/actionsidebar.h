#ifndef ACTIONSIDEBAR_H
#define ACTIONSIDEBAR_H

#include <QWidget>

namespace Ui {
class ActionSideBar;
}

class ActionSideBar : public QWidget
{
    Q_OBJECT

public:
    explicit ActionSideBar(QWidget *parent = 0);
    ~ActionSideBar();

private:
    Ui::ActionSideBar *ui;
};

#endif // ACTIONSIDEBAR_H
