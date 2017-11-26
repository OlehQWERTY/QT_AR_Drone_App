#ifndef ONLINEDATA_H
#define ONLINEDATA_H

// This is wrapper for GeoCoordinates and TCP/IP

// it provides combination of sensor val from TCP/IP (converted to unsigned char[3] color) and geo coordinates
// with cartesian data from GeoCoordinates inside struct GeoPointValues

#include "GeoCoordinates.h"
#include "TcpIpServer.h"

class OnlineData
{
private:
    unsigned char sensorVal = 0;
    void realSensorValToUChar(int); // add
    unsigned char *sensorValToColor(unsigned char); // add

    // signal and slot for TCP/IP use here and signal and slot for new data ros (new file data)

public:

    OnlineData();
    GeoPointValues getOnlineData(); // add
    void setZeroGeoPoint(double, double);

};

#endif // ONLINEDATA_H

//

//GeoCoordinates GeoCord(50.771135, 15.088055);
//GeoPointValues *b;
////qDebug() << "Read odometry: ";
//b = GeoCord.odometryToGeo();
//qDebug() << "latitude: " << b->latitude;
//qDebug() << "longitude: " << b->longitude;
//qDebug() << "cartesianX: " << b->cartesianX;
//qDebug() << "cartesianY: " << b->cartesianY;
//qDebug() << "cartesianZ: " << b->cartesianZ;
////    qDebug() << "Cartesian coordinates to geo: ";
//b = GeoCord.cartesianCoordinatesToGeo(5, 6);
////qDebug() << b->latitude;
////qDebug() << b->longitude;
