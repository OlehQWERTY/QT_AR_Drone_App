#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

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
