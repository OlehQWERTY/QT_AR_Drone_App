#ifndef SERVERCONNECTIONERROR_H
#define SERVERCONNECTIONERROR_H

#include <QWidget>

namespace Ui {
class serverConnectionError;
}

class serverConnectionError : public QWidget
{
    Q_OBJECT

public:
    explicit serverConnectionError(QWidget *parent = 0);
    ~serverConnectionError();

private:
    Ui::serverConnectionError *ui;
};

#endif // SERVERCONNECTIONERROR_H
