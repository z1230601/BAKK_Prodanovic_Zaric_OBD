#ifndef ADDDATABASEDTCDIALOG_H
#define ADDDATABASEDTCDIALOG_H

#include <QDialog>

namespace Ui {
class AddDatabaseDtcDialog;
}

class AddDatabaseDtcDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddDatabaseDtcDialog(QWidget *parent = 0);
    ~AddDatabaseDtcDialog();

    QString getCode();
    QString getDescription();

    void editValues(QString code, QString description);

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::AddDatabaseDtcDialog *ui;
    bool is_edit;
};

#endif // ADDDATABASEDTCDIALOG_H
