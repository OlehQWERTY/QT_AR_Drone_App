#ifndef GEOMAP_H
#define GEOMAP_H

//this class includes all points on the map and has all methods for create Json file

//Json includes
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
//file includes
#include <QFile>
//time includes
#include <QTime>
//list includes
#include <QList>
//my own class for store point
#include "../GeoPoint/GeoPoint.h"

class GeoMap
{
private:
    QList<GeoPoint> Points; // QList of Points on the Map
    QJsonObject JsonObject; // all Json obj connector
    QString fileName;
    QString colorString;

    void convertPointsToJson(); // write all Points to Json
    void getFileName(); // time and data .json
    // JavaScript can't use transformed string as color. I don't know wtf!
    QString charNumbDecimalToHexadecimal(unsigned char, bool); // unsigned char dec -> QString hex (255 -> "ff"), reg: true - ff, false - FF
    bool HexSpecQStringToColorChar(QString, unsigned char *); // QString ("#aa78bbff") -> unsigned char* (u char[3]) (ending ff doesn't have any influence on transformation)
    void readFromFile(QString); // (21_11_17_13_52_36.json) read from file and write content to JsonObj
    void saveToFile(bool); // save to file with name(data + time).json (false) or save geo_json.json as func for JS script (true)
public:
    GeoMap();
    void addPoint(double, double, double, double, double, unsigned long int, unsigned char[3]);  // add color
    GeoPointValues getFirst();
    GeoPointValues getLast();
    GeoPointValues getPoint(int);
    int getLength();
    void convertJsonToPoints(QString); // (21_11_17_13_52_36.json) read all Points from Json and load Points from Json file (for ofline mode)
    void save(); // saveToFile(false) - save Json
    void mapUpdate(); // saveToFile(true) - save geo_json.json for JS script Google maps API

    // test return QList<GeoPoint> Points;
    QList<GeoPoint> getAllPointsList(); // it is neaded for sending all points to View part of App

    void showAllPoints(); // just for Debugging
    void showJson(); // just for Debugging
};

#endif // GEOMAP_H
