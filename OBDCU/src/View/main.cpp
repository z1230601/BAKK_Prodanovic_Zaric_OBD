#include "mainwindow.h"
#include <QApplication>
#include <QFile>
#include <QTextStream>
#include <iostream>
#include <QDir>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    w.show();

    std::cout << QDir::currentPath().toStdString() << std::endl;
    QFile f(":res/style.qss");
    if (!f.exists())
    {
        printf("Unable to set stylesheet, file not found\n");
    }
    else
    {
        f.open(QFile::ReadOnly | QFile::Text);
        QTextStream ts(&f);
        a.setStyleSheet(ts.readAll());
    }

    return a.exec();
}
