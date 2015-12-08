#ifndef ABSTRACTOBDWIDGET_H
#define ABSTRACTOBDWIDGET_H

#include <QWidget>
class ActionSideBar;

class AbstractOBDWidget: public QWidget
{
    Q_OBJECT
public:
    explicit AbstractOBDWidget(QWidget* parent = 0);
    virtual QWidget* createActionSideBar(QWidget* parent);

signals:

public slots:

protected:
    QWidget* sidebar_;
};

#endif // ABSTRACTOBDWIDGET_H
