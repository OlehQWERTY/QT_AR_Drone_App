#include "inputerror.h"
#include "ui_inputerror.h"

inputError::inputError(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::inputError)
{
    ui->setupUi(this);
}

inputError::~inputError()
{
    delete ui;
}
