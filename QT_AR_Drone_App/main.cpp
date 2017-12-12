#include <QApplication>
#include "Controllers/MainController/MainController.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainController CMain(1); //doesn't work if I call constructor without parameters (the base class constructor is called
    //to initialize the base class members and then the derived class constructor
    return a.exec();
}
