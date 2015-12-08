#include "communicationswidget.h"
#include "ui_communicationswidget.h"

CommunicationsWidget::CommunicationsWidget(QWidget *parent) :
    AbstractOBDWidget(parent),
    ui(new Ui::CommunicationsWidget)
{
    ui->setupUi(this);
}

CommunicationsWidget::~CommunicationsWidget()
{
    delete ui;
}
