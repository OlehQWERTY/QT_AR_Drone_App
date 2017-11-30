#include "GeoMap.h"

GeoMap::GeoMap()
{
    getFileName();
}

void GeoMap::addPoint(double outLatitude, double outLongitude, double outCartesianX, double outCartesianY, double outCartesianZ, unsigned char outColor[3])
{
    unsigned char *pColor = &outColor[0];
    Points.append(GeoPoint(outLatitude, outLongitude, outCartesianX, outCartesianY, outCartesianZ, pColor));
}

GeoPointValues GeoMap::getFirst()
{
    GeoPointValues tempPointVal;
    tempPointVal = Points.first().getValue();// return only first element
    return tempPointVal;
}

GeoPointValues GeoMap::getLast()
{
    GeoPointValues tempPointVal;
    tempPointVal = Points.last().getValue();// return only last element
    return tempPointVal;
}

GeoPointValues GeoMap::getPoint(int number)
{
    GeoPointValues tempPointVal;

    int i = 1;
    QList<GeoPoint>::iterator it = Points.begin(); // iterator creation and set it to begine (first element of QList)
    while (it != Points.end()) {
        if(i >= number) // if number of element == number
        {
            tempPointVal = it->getValue();
            return tempPointVal;
        }
        i++;
        it++;
    }

    return tempPointVal; // init tempPointVal as NULL rewrite it like a pointer
    //and return * NULL if number > GeoMap.getLength
}

int GeoMap::getLength()
{
    int length = 0;
    foreach (GeoPoint tempGeoPoint, Points) {
        length++;
    }

    return length;
}

void GeoMap::convertPointsToJson()
{
    JsonObject.insert("type", QJsonValue::fromVariant("FeatureCollection"));
    QJsonArray pointsArray;
    int pointsLength = getLength();

    for(int i = 1; i <= pointsLength; i++)
    {
        GeoPointValues tempPointVal = getPoint(i);
        QJsonObject pointObject;

            pointObject.insert("type", QJsonValue::fromVariant("Feature"));

            int number = tempPointVal.id;
            QJsonObject propertiesObject;
            // colorString.append("ff") () because JavaScript can't use transformed string as color. I don't know wtf!
                colorString = '#';
                colorString.append(charNumbDecimalToHexadecimal(tempPointVal.color[0], true)
                        + charNumbDecimalToHexadecimal(tempPointVal.color[1], true)
                        + charNumbDecimalToHexadecimal(tempPointVal.color[2], true));
                colorString.append("ff");
                propertiesObject.insert("maker_color", QJsonValue::fromVariant(colorString)); //"#ee7e7e"
                propertiesObject.insert("maker_size", QJsonValue::fromVariant("small"));
                propertiesObject.insert("maker_symbol", number);

                pointObject.insert("properties", propertiesObject);

            QJsonObject geometryObject;
                geometryObject.insert("type", QJsonValue::fromVariant("Point"));

                QJsonArray coordinatesArray;
                    double latitude = tempPointVal.latitude;
                    double longitude = tempPointVal.longitude;
                    coordinatesArray.push_back(QJsonValue::fromVariant(longitude));
                    coordinatesArray.push_back(QJsonValue::fromVariant(latitude));

                geometryObject.insert("coordinates", coordinatesArray);

                QJsonArray cartesianCoordinatesArray;
                    double cartesianX = tempPointVal.cartesianX;
                    double cartesianY = tempPointVal.cartesianY;
                    double cartesianZ = tempPointVal.cartesianZ;
                    cartesianCoordinatesArray.push_back(QJsonValue::fromVariant(cartesianX));
                    cartesianCoordinatesArray.push_back(QJsonValue::fromVariant(cartesianY));
                    cartesianCoordinatesArray.push_back(QJsonValue::fromVariant(cartesianZ));

                geometryObject.insert("cartesian", cartesianCoordinatesArray);

            pointObject.insert("geometry", geometryObject);

    pointsArray.push_back(pointObject);

    }
    JsonObject.insert("features", pointsArray);
}

void GeoMap::convertJsonToPoints(QString tempFileName)
{
    readFromFile(tempFileName);
    QJsonValue featuresVal = JsonObject.value("features");

    if(featuresVal.isArray()){
        QJsonArray featuresArr = featuresVal.toArray();
        for(int i = 0; i < featuresArr.count(); i++){
            QJsonObject subtree = featuresArr.at(i).toObject();
            QJsonValue geometryVal = subtree.value("geometry");

            QJsonObject geometryObj = geometryVal.toObject();

            // cartesian coordinates
            QJsonValue cartesianVal = geometryObj.value("cartesian");
            QJsonArray cartesianArr = cartesianVal.toArray();

            double tempCartesianX = cartesianArr.at(0).toDouble();
            double tempCartesianY = cartesianArr.at(1).toDouble();
            double tempCartesianZ = cartesianArr.at(2).toDouble();

            //geo coordinates
            QJsonValue coordinatesVal = geometryObj.value("coordinates");
            QJsonArray coordinatesArr = coordinatesVal.toArray();
            //qWarning() << coordinatesArr.size();

            double tempLongitude = coordinatesArr.at(0).toDouble();
            double tempLatitude = coordinatesArr.at(1).toDouble();

            QJsonValue propertiesVal = subtree.value("properties");
            QJsonObject propertiesObj = propertiesVal.toObject();

            // properties
            QJsonValue maker_colorVal = propertiesObj.value("maker_color");
            QString tempCilorString = maker_colorVal.toString();

            QJsonValue maker_symbolVal = propertiesObj.value("maker_symbol");
            int tempSymbol = maker_symbolVal.toInt(); // not used here

            unsigned char tempColor[3] = {0, 0, 0};
            unsigned char *pTempColor = tempColor;
            bool ok = HexSpecQStringToColorChar(tempCilorString, pTempColor);
            if(ok) // if color can't be converted color will be equal {0, 0, 0}
            {
                for(int i = 0; i < 3; i++)
                {
                    tempColor[i] = pTempColor[i];
                }
            }
            addPoint(tempLatitude, tempLongitude, tempCartesianX, tempCartesianY, tempCartesianZ, tempColor); // add new point to QList Points
        }
    }
}

void GeoMap::save()
{
    saveToFile(false);
}

void GeoMap::mapUpdate()
{
    saveToFile(true);
}

void GeoMap::getFileName()
{
    //qDebug() << QDate::currentDate().toString("dd MM yy"); // "dd MM yy"
    //qDebug() << QTime::currentTime().toString("hh mm ss"); // "hh mm ss ms"       .toDouble()

    fileName = QDate::currentDate().toString("dd_MM_yy_") + QTime::currentTime().toString("hh_mm_ss")
            + ".json";
    //qDebug() << "FileName: " << ("./Json_files/" + fileName);
}

// int instead of unsigned char because JavaScript can't use transformed string as color. I don't know wtf!
QString GeoMap::charNumbDecimalToHexadecimal(unsigned char number, bool lowCase = true)
{
    QString str;
    if(lowCase)
    {
        str = QString::number(number, 16);
    }
    else
    {
        str = QString::number(number, 16).toUpper();
    }

    if(str.length() < 2) // "0a" isted of "a"
    {
        return '0' + str;
    }
    return str;
}

bool GeoMap::HexSpecQStringToColorChar(QString HexColor, unsigned char *pArr) //QString HexColor = "#3013bbff";
{
    bool ok = true;
    if(!HexColor.isEmpty())
    {
        for(int i = 0; i < 3; i++)
        {
            QString subRColor = HexColor.mid(1 + i * 2, 2); // for example "#3013bbff" -> from 1 to 1 + 2 (30, 13, bb) and so on
            if(ok)
            {
                pArr[i] = subRColor.toInt(&ok, 16);
            }
            else
            {
                return false;
            }
        }
    }
    return true;
}

void GeoMap::readFromFile(QString tempFileName) // 21_11_17_13_52_36.json
{
    QString val; // temp var
    QFile file;
    file.setFileName("Json/" + tempFileName); // QFile F("./Json_files/" + fileName);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    val = file.readAll();
    file.close();
    QJsonDocument doc = QJsonDocument::fromJson(val.toUtf8());
    JsonObject = doc.object(); // QJsonObject root = doc.object();
}

void GeoMap::saveToFile(bool geo) // if true - save to geo as Js func, else - ordinary Json
{
    convertPointsToJson();
    QString tempFilePath = "./Json/";
    if(geo)
    {
        tempFilePath.append(fileName);
    }
    else
    {
        tempFilePath.append("geo_json.json");
    }

    QFile F(tempFilePath);
    if(!F.open(QIODevice::WriteOnly))
    {
        qDebug() << "Error! Can't open file!" << tempFilePath;
    }

    QJsonDocument jsdoc(JsonObject); // renew jsdoc with new JsonObject
    if(geo) // geo json for internal app usage
    {
        F.write(jsdoc.toJson());
    }
    else // geo for JS script
    {
        F.write("eqfeed_callback(");
        F.write("\n");
        F.write(jsdoc.toJson());
        F.write(")");
    }
    F.close();
}

QList<GeoPoint> GeoMap::getAllPointsList()
{
    return Points;
}

void GeoMap::showAllPoints()
{
    foreach (GeoPoint tempGeoPoint, Points) {
        qDebug() << "Latitude   " << "[" << tempGeoPoint.id << "]" << tempGeoPoint.latitude;
        qDebug() << "Longitude  " << "[" << tempGeoPoint.id << "]" << tempGeoPoint.longitude;
        qDebug() << "CartesianX " << "[" << tempGeoPoint.id << "]" << tempGeoPoint.cartesianX;
        qDebug() << "cartesianY " << "[" << tempGeoPoint.id << "]" << tempGeoPoint.cartesianY;
        qDebug() << "cartesianZ " << "[" << tempGeoPoint.id << "]" << tempGeoPoint.cartesianZ;
        qDebug() << "Color      " << "[" << tempGeoPoint.id << "]"
                 << "r" << tempGeoPoint.color[0] << "g" << tempGeoPoint.color[1] << "b" << tempGeoPoint.color[2];
        qDebug() << "------------------";
    }
}

void GeoMap::showJson()
{
    convertPointsToJson();
    QJsonDocument jsdoc(JsonObject);
    qDebug() << jsdoc.toJson();
}
