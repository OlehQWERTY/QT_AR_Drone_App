#ifndef ONLINEDATA_H
#define ONLINEDATA_H

// This is wrapper for GeoCoordinates and TCP/IP

// it provides combination of sensor val from TCP/IP (converted to unsigned char[3] color) and geo coordinates
// with cartesian data from GeoCoordinates inside struct GeoPointValues

#include "GeoCoordinates.h"
#include "TcpIpServer.h"

class OnlineData
{

//signals:
//    void dataChanged(int); // ros generated file || tcp/ip data changed

private:
    // wrapped classes
    GeoCoordinates GeoCoord;
    MyTcpServer TcpServer; // TCP IP

    // struct with PoinValues
    GeoPointValues *pGeoPoint = NULL;

    //unsigned char color[3] = {0, 0, 0}; // color arr = r g b

    //unsigned char sensorVal = 0;
    void sensorValToColor(int &, const int &, const int &);

public:

    OnlineData();
    GeoPointValues *getOnlineData(const int &, const int &);
    void setZeroGeoPoint(double, double);

    bool isLaunched() const; // based on isLaunched method from TcpIpServer class

};

#endif // ONLINEDATA_H
