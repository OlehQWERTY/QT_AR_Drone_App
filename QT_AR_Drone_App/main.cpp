#include <QApplication>

#include "Controllers/MainController/MainController.h"

#include <QThread>

class Sleeper : public QThread // delay
{
public:
    static void usleep(unsigned long usecs){QThread::usleep(usecs);}
    static void msleep(unsigned long msecs){QThread::msleep(msecs);}
    static void sleep(unsigned long secs){QThread::sleep(secs);}
};

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainController CMain(true);
    CMain.setZeroGeoPoint(50.771135, 15.088055);
    for(int i = 0; i < 100; i++)
    {
        GeoPointValues *pGeoPoint = CMain.getOnlineData();
        qDebug() << "OnlineData";
        qDebug() << "latitude: " << pGeoPoint->latitude;
        qDebug() << "longitude: " << pGeoPoint->longitude;
        qDebug() << "cartesianX: " << pGeoPoint->cartesianX;
        qDebug() << "cartesianY: " << pGeoPoint->cartesianY;
        qDebug() << "cartesianZ: " << pGeoPoint->cartesianZ;
        qDebug() << "r: " << pGeoPoint->color[0] << " g: " << pGeoPoint->color[1]
                    << " b: " << pGeoPoint->color[2];

        Sleeper::msleep(100);
    }
    a.exit();
}

// delay
//Sleeper::usleep(10);
//Sleeper::msleep(10);
//Sleeper::sleep(10);
