#include "GeoPoint.h"

unsigned long int GeoPoint::counter = 0;

GeoPoint::GeoPoint(double outLatitude, double outLongitude, double outCartesianX, double outCartesianY, double outCartesianZ, unsigned char *pOutColor)
{
    set3UCharColorArr(pOutColor);
    counter++;
    this->id = counter;
    setValue(outLatitude, outLongitude, outCartesianX, outCartesianY, outCartesianZ);
    set3UCharColorArr(pOutColor);
}

void GeoPoint::setValue(double outLatitude, double outLongitude, double outCartesianX, double outCartesianY, double outCartesianZ)
{
    latitude = outLatitude;
    longitude = outLongitude;
    cartesianX = outCartesianX;
    cartesianY = outCartesianY;
    cartesianZ = outCartesianZ;
}

void GeoPoint::set3UCharColorArr(unsigned char *pOutColor)
{
    for(int i = 0; i < 3; i++)
    {
        color[i] = pOutColor[i];
    }
}

GeoPointValues GeoPoint::getValue() // return data fields of the GeoPoint throw PointStruct
{
    GeoPointValues PointStruct;
    PointStruct.id = id;
    PointStruct.latitude = latitude;
    PointStruct.longitude = longitude;
    PointStruct.cartesianX = cartesianX;
    PointStruct.cartesianY = cartesianY;
    PointStruct.cartesianZ = cartesianZ;
    for (int i = 0; i < 3; i++)
    {
        PointStruct.color[i] = color[i];
    }
    return PointStruct; // maybe pointer will be better?
}
