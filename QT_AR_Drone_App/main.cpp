#include <QApplication>
#include "Controllers/MainController/MainController.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    // MainController
    MainController CMain(50.771135, 15.088055, 16, 19); // zero geo location and min - max sensor values in Celsius
    CMain.setFileName("cutted_11_12_17_15_30_09_temperature16to19.json"); // it is neaded only for offline mode (09_12_17_16_52_41.json)
    CMain.setMode(false); // true - online
    return a.exec();
}
