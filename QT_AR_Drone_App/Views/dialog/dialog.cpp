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

    ui->startButton->setDisabled(true); // start button disable until you chose mode
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::onlineButtonClicked()
{
    disableLineEdit(true);
    //qDebug() << "onlineButtonClicked!";
}

void Dialog::offlineButtonClicked()
{
    disableLineEdit(false);
    //qDebug() << "offlineButtonClicked!";
}

void Dialog::startButtonClicked() // _____________________________________________________________!!!!!!!!!!!!!!!!!!!
{

    getDataFromDialogForm();
// -------------------------------
   emit StartPressed();
   //qDebug() << "startButtonClicked";

}

void Dialog::disableLineEdit(bool flag) // true - read only
{
    ui->filePathLine->setReadOnly(flag);
    ui->latitudeLine->setReadOnly(!flag);
    ui->longitudeLine->setReadOnly(!flag);
    ui->maxTLine->setReadOnly(!flag);
    ui->minTLine->setReadOnly(!flag);
    QPalette *palette1 = new QPalette(); // this one for filePathLine
    QPalette *palette2 = new QPalette(); // this one for other lines
    if(flag)
    {
        palette1->setColor(QPalette::Base,Qt::gray);
        palette1->setColor(QPalette::Text,Qt::darkGray);

        palette2->setColor(QPalette::Base,Qt::white);
        palette2->setColor(QPalette::Text,Qt::black);
        // online mode
    }
    else
    {
        palette1->setColor(QPalette::Base,Qt::white);
        palette1->setColor(QPalette::Text,Qt::black);

        palette2->setColor(QPalette::Base,Qt::gray);
        palette2->setColor(QPalette::Text,Qt::darkGray);
        // offline mode
    }
    AppData.mode = flag;
    ui->filePathLine->setPalette(*palette1);
    ui->latitudeLine->setPalette(*palette2);
    ui->longitudeLine->setPalette(*palette2);
    ui->maxTLine->setPalette(*palette2);
    ui->minTLine->setPalette(*palette2);

    ui->startButton->setDisabled(false); // make start button abled
}

AppInitData &Dialog::returnAppData()
{
    return AppData;
}

void Dialog::getDataFromDialogForm() //get data from input fielsd of dialog
{
    QString tempText;

   if(!AppData.mode) // offline mode
    {
        tempText = ui->filePathLine->text(); // get Path
        AppData.fileName = tempText;
        //qDebug() << "TempText: " << tempText;
    }
    bool latitudeOk = false;
    bool longitudeOk = false;
    bool minTOk = false;
    bool maxTOk = false;
// correct it to normal view // add wrong data checking
    tempText = ui->latitudeLine->text(); // get latitude
    //qDebug() << "latitudeLine: " << tempText.toDouble();
    AppData.latitude = tempText.toDouble(&latitudeOk);

    tempText = ui->longitudeLine->text(); // get longitude
    //qDebug() << "longitudeLine: " << tempText.toDouble(/*&ok*/);
    AppData.longitude = tempText.toDouble(&longitudeOk);

    tempText = ui->minTLine->text(); // get minTemperature
    //qDebug() << "minTLine: " << tempText;
    AppData.minT = tempText.toDouble(&minTOk);

    tempText = ui->maxTLine->text(); // get maxTemperature
    //qDebug() << "maxTLine: " << tempText;
    AppData.maxT = tempText.toDouble(&maxTOk);

    // correction checking
    bool errorFlag = false;
    if(AppData.mode)
    {
        if(!latitudeOk || !longitudeOk || !minTOk || !maxTOk)
        {
            qDebug() << "latitudeOk || longitudeOk || minTOk || maxTOk Input error!";
            errorFlag = true;
        }
    }
    else
    {
        if(!AppData.fileName.contains(".json", Qt::CaseSensitive)) // not very intelligent approach
        {
            qDebug() << "fileName is wrong!";
            errorFlag = true;
        }
    }

    AppData.errorFlag = errorFlag; // MainController checks this flag

//    if(!errorFlag)
//    {
//        qDebug() << "all data is correct" << errorFlag;
//    }
}
