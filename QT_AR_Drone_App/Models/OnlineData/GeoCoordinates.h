#ifndef GEOCOORDINATES_H
#define GEOCOORDINATES_H

//this class takes odometry from ROS and convert it to geolocation coordinates

#include <iostream>
using namespace std;

#include <QFile>
#include <QTextStream>
#include <QString>
#include <QDebug>

#include "../GeoPoint/GeoPointValues.h"
//#include "TcpIpServer.h"

class GeoCoordinates
{
private:
    const double PI = 3.14159265358979;
    const double R = 6371000.0;
    double zeroDegLatitude = 0;
    double zeroDegLongitude = 0;

    unsigned long int odometryTime = 0; // not used now
    double odometryX = 0;
    double odometryY = 0;
    double odometryZ = 0;

    GeoPointValues *pGeoPoint = NULL;

    //void setZeroGeoPoint(double, double);
    double cartesianPointToGeo(double, double);
    double geoPointToCartesian(double); // I don't use it. Additional func! It is for providing GeoCoordinatesToCartesian functionality
    QString readFromFile(QString);
    void parseOdometry(QString);
public:
    GeoCoordinates(); // it was added because of next level is wrapper
    GeoCoordinates(double, double);
    void setZeroGeoPoint(double, double);
    ~GeoCoordinates();
    GeoPointValues *odometryToGeo();
    GeoPointValues *cartesianCoordinatesToGeo(double, double); // !!!!! I don't use it and it doesn't return cartesian X Y Z !!!!!
    //void GeoCoordinatesToCartesian(double, double); // I don't use it. Additional func! As returned type it neeads spec struct.
    // or input values pointer can be as returned type
};

#endif // GEOCOORDINATES_H
