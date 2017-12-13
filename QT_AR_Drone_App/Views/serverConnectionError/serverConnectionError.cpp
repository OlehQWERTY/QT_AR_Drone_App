#include "serverConnectionError.h"
#include "ui_serverConnectionError.h"

serverConnectionError::serverConnectionError(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::serverConnectionError)
{
    ui->setupUi(this);
}

serverConnectionError::~serverConnectionError()
{
    delete ui;
}
