#ifndef INPUTERROR_H
#define INPUTERROR_H

#include <QWidget>

namespace Ui {
class inputError;
}

class inputError : public QWidget
{
    Q_OBJECT

public:
    explicit inputError(QWidget *parent = 0);
    ~inputError();

private:
    Ui::inputError *ui;
};

#endif // INPUTERROR_H
