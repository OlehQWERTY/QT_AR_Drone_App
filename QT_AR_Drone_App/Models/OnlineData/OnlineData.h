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
    // wrapped classes
    GeoCoordinates GeoCoord;
    MyTcpServer TcpServer; // TCP IP

    // struct with PoinValues
    GeoPointValues *pGeoPoint = NULL;

    //unsigned char sensorVal = 0;
    unsigned char realSensorValToUChar(int);
    void sensorValToColor(unsigned char);

public:

    OnlineData();
    GeoPointValues *getOnlineData();
    void setZeroGeoPoint(double, double);

};

#endif // ONLINEDATA_H
