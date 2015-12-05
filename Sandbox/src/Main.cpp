//#include <QtGui>
//
//int main(int argv, char **args) {
//	QApplication app(argv, args);
//
//	QTextEdit *textEdit = new QTextEdit;
//	QPushButton *quitButton = new QPushButton("&Quit");
//
//	QObject::connect(quitButton, SIGNAL(clicked()), qApp, SLOT(quit()));
//
//	QVBoxLayout *layout = new QVBoxLayout;
//	layout->addWidget(textEdit);
//	layout->addWidget(quitButton);
//
//	QWidget window;
//	window.setLayout(layout);
//
//	window.show();
//
//	return app.exec();
//}

#include <QApplication>
#include <QTextEdit>
#include <ui_OBDCUMainWindow.h>
#include <QFile>
#include <QTextStream>

int main(int argv, char **args) {
	QApplication app(argv, args);

	QFile f("./style/qdarkstyle/style.qss");
	if (!f.exists())
	{
	    printf("Unable to set stylesheet, file not found\n");
	}
	else
	{
	    f.open(QFile::ReadOnly | QFile::Text);
	    QTextStream ts(&f);
	    app.setStyleSheet(ts.readAll());
	}

	QMainWindow* window = new QMainWindow();

	Ui_OBDCU mainwindow;
	mainwindow.setupUi(window);

	window->show();

	return app.exec();
}
