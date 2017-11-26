#ifndef GEOPOINT_H
#define GEOPOINT_H

//class for saving one point on the map

#include <QDebug> // test! Del me)

#include "GeoPointValues.h"

class GeoPoint
{
public:
    static unsigned long int counter;
    unsigned long int id = 0;
    double latitude = 0;
    double longitude = 0;
    double cartesianX = 0;
    double cartesianY = 0;
    double cartesianZ = 0;
    unsigned char color[3] = {0, 0, 0}; // colour rgb (255 255 255) X16 * 3

    GeoPoint(double, double,  double, double, double, unsigned char*);
    void setValue(double, double,  double, double, double);
    void set3UCharColorArr(unsigned char*);
    GeoPointValues getValue();
};

#endif // GEOPOINT_H
