#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include "appinitdata.h" // struct for returning init data from gialog window

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();
    AppInitData AppData; // struct for saving init data from dialog wimdow
    AppInitData &returnAppData(); // return

protected slots:
    void onlineButtonClicked();
    void offlineButtonClicked();
    void startButtonClicked(); // call StartPressed signal (MainController is subscribed for this signal)
signals:
    void StartPressed(); // signal for MainController

private:
    Ui::Dialog *ui;
    void disableFilePathLineEdit(bool);
};

#endif // DIALOG_H
