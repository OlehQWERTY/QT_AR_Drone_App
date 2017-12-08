#include <QApplication>
#include "Controllers/MainController/MainController.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    // MainController
    MainController CMain(50.771135, 15.088055); // zero geo location
    CMain.setFileName("29_11_17_16_33_24.json"); // it is neaded only for offline mode (29_11_17_16_33_24.json)
    CMain.setMode(true); // true - online
    return a.exec();
}
