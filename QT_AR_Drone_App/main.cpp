#include <QApplication>

#include "Controllers/MainController/MainController.h"

int main(int argc, char *argv[])
{
    MainController CMain(true);
    CMain.setZeroGeoPoint(50.771135, 15.088055);
    GeoPointValues *pGeoPoint = CMain.getOnlineData();
    qDebug() << "OnlineData";
    qDebug() << "latitude: " << pGeoPoint->latitude;
    qDebug() << "longitude: " << pGeoPoint->longitude;
    qDebug() << "cartesianX: " << pGeoPoint->cartesianX;
    qDebug() << "cartesianY: " << pGeoPoint->cartesianY;
    qDebug() << "cartesianZ: " << pGeoPoint->cartesianZ;
    qDebug() << "r: " << pGeoPoint->color[0] << " g: " << pGeoPoint->color[1]
                << " b: " << pGeoPoint->color[2];

}
