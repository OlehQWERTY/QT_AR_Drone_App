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

void Dialog::startButtonClicked() // _____________________________________________________________!!!!!!!!!!!!!!!!!!!
{


    // init data for returning
    QString tempText;
    //get data from input fielsd of dialog
   if(!AppData.mode) // offline mode
    {
        tempText = ui->filePathLine->text(); // get Path
        qDebug() << "TempText: " << tempText;
    }
//    bool ok = false;
// correct it to normal view // add wrong data checking
    tempText = ui->latitudeLine->text(); // get latitude
    qDebug() << "latitudeLine: " << tempText.toDouble();
    AppData.latitude = tempText.toDouble();

    tempText = ui->longitudeLine->text(); // get longitude
    qDebug() << "longitudeLine: " << tempText.toDouble(/*&ok*/);
    AppData.longitude = tempText.toDouble();

    tempText = ui->minTLine->text(); // get minTemperature
    qDebug() << "minTLine: " << tempText;
    AppData.minT = tempText.toDouble();

    tempText = ui->maxTLine->text(); // get maxTemperature
    qDebug() << "maxTLine: " << tempText;
    AppData.maxT = tempText.toDouble();

//    qDebug() << "all data is correct" << ok;

// -------------------------------
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
        // online mode
    }
    else
    {
        palette->setColor(QPalette::Base,Qt::white);
        palette->setColor(QPalette::Text,Qt::black);
        // offline mode
    }
    AppData.mode = flag; // online mode
    ui->filePathLine->setPalette(*palette);
}

AppInitData &Dialog::returnAppData()
{
    return AppData;
}
