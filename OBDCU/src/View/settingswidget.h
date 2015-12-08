#ifndef SETTINGSWIDGET_H
#define SETTINGSWIDGET_H

#include <QWidget>
#include "abstractobdwidget.h"

namespace Ui {
class SettingsWidget;
}

class SettingsWidget : public AbstractOBDWidget
{
    Q_OBJECT

public:
    explicit SettingsWidget(QWidget *parent = 0);
    ~SettingsWidget();

private:
    Ui::SettingsWidget *ui;
};

#endif // SETTINGSWIDGET_H
