#include "dialog.h"
#include "ui_dialog.h"
#include <QDebug> // del it after debugging

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

    connect(ui->onlineButton, SIGNAL(clicked()),this,SLOT(onlineButtonClicked())); // online mode active
    connect(ui->offlineButton, SIGNAL(clicked()),this,SLOT(offlineButtonClicked())); // offline mode active
    connect(ui->startButton, SIGNAL(clicked()),this,SLOT(startButtonClicked())); // MainController use this signal for launching widget
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::onlineButtonClicked()
{
    disableFilePathLineEdit(true);
    //qDebug() << "onlineButtonClicked!";
}

void Dialog::offlineButtonClicked()
{
    disableFilePathLineEdit(false);
    //qDebug() << "offlineButtonClicked!";
}

void Dialog::startButtonClicked()
{
    emit StartPressed();
    qDebug() << "startButtonClicked";
}

void Dialog::disableFilePathLineEdit(bool flag) // true - read only
{
    ui->filePathLine->setReadOnly(flag);
    QPalette *palette = new QPalette();
    if(flag)
    {
        palette->setColor(QPalette::Base,Qt::gray);
        palette->setColor(QPalette::Text,Qt::darkGray);
    }
    else
    {
        palette->setColor(QPalette::Base,Qt::white);
        palette->setColor(QPalette::Text,Qt::black);
    }
    ui->filePathLine->setPalette(*palette);
}
