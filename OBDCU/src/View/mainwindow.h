#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "stackedtabwrapper.h"

#include <QWidget>
#include <vector>

namespace Ui {
class MainWindow;
}

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    std::vector<StackedTabWrapper*> viewList_;

    void setupContentWindows();
    void initMap();
};

#endif // MAINWINDOW_H
