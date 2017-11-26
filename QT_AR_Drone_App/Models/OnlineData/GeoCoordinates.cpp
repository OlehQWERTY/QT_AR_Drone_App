#include "GeoCoordinates.h"

GeoCoordinates::GeoCoordinates() // it was added because of next level is wrapper
{
    pGeoPoint = new GeoPointValues;
}

GeoCoordinates::GeoCoordinates(double outZeroDegLatitude, double outZeroDegLongitude)
{
    setZeroGeoPoint(outZeroDegLatitude, outZeroDegLongitude);
    pGeoPoint = new GeoPointValues;
}

GeoCoordinates::~GeoCoordinates()
{
    delete pGeoPoint;
}

void GeoCoordinates::setZeroGeoPoint(double outZeroDegLatitude, double outZeroDegLongitude)
{
    zeroDegLatitude = outZeroDegLatitude;
    zeroDegLongitude = outZeroDegLongitude;
}

double GeoCoordinates::cartesianPointToGeo(double outGeoValue, double outCartesianVal) // outGeoValue - latitude or longitude
{
    // we think it as 0 0 cartesian point (along latitude or longitude)
    double approxCartesianVal = (PI * outGeoValue * R)/180; // latitude or longitude convert to cartesian
    // add to cartesian x = 0 803000 m
    double approxCartesianChanged = approxCartesianVal + outCartesianVal; // + distance m
    // convert to geo next cartesian point
    return (180 * approxCartesianChanged) / (PI * R);
}

double GeoCoordinates::geoPointToCartesian(double outGeoValue) // outGeoValue - latitude or longitude
{
    // we think it as 0 0 cartesian point (along latitude or longitude)
    double approxCartesianVal = (PI * outGeoValue * R)/180; // latitude or longitude convert to cartesian
    return (PI * outGeoValue * R)/180 - approxCartesianVal;
}

QString GeoCoordinates::readFromFile(QString outFileName = "/home/oleg/catkin_ws/src/test1/src/odometryData.txt")
{
    QString fileName = outFileName;
    QFile inputFile(fileName);
    QString line;
    if (inputFile.open(QIODevice::ReadOnly))
    {
       QTextStream in(&inputFile);
       while (!in.atEnd())
       {
          line = in.readLine();
       }
       inputFile.close();
    }
    return line;
}

void GeoCoordinates::parseOdometry(QString line)
{
    odometryTime = line.section(',', 0, 0).toInt(); // return one field separated by ','
    odometryX = line.section(',', 1, 1).toDouble();
    odometryY = line.section(',', 2, 2).toDouble();
    odometryZ = line.section(',', 3, 3).toDouble();
}

GeoPointValues *GeoCoordinates::odometryToGeo()
{
    parseOdometry(readFromFile());
    // cartesian write to struct
    pGeoPoint->cartesianX = odometryX;
    pGeoPoint->cartesianY = odometryY;
    pGeoPoint->cartesianZ = odometryZ;
    // cartesian X and Y -> latitude and longitude
    pGeoPoint->latitude = cartesianPointToGeo(zeroDegLatitude, odometryX); // odometryX + geoLatitude to cartesian
    pGeoPoint->longitude = cartesianPointToGeo(zeroDegLongitude, odometryY); // the same
    return pGeoPoint;
}

GeoPointValues *GeoCoordinates::cartesianCoordinatesToGeo(double outOdometryX, double outOdometryY)
{ // !!!!! I don't use it and it doesn't return cartesian X Y Z !!!!!
    pGeoPoint->latitude = cartesianPointToGeo(zeroDegLatitude, outOdometryX); // odometryX + geoLatitude to cartesian
    pGeoPoint->longitude = cartesianPointToGeo(zeroDegLongitude, outOdometryY); // the same
    return pGeoPoint;
}
