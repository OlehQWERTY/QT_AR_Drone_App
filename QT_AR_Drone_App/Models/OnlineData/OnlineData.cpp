#include "OnlineData.h"

OnlineData::OnlineData()
{

}

unsigned char OnlineData::realSensorValToUChar(int val) // add
{
    unsigned char tempVal = val; // correct it according to sensor type
    return tempVal;
}

void OnlineData::sensorValToColor(unsigned char sensorVal) // test me !!!!!!!!!!!!!!!!!!!!!!!!!!
{
    if(sensorVal < 127)
    {
        pGeoPoint->color[0] = (sensorVal + 1)/127.0;
        pGeoPoint->color[1] = 1.0;
        pGeoPoint->color[2] = 1.0;
        //glColor4f((color + 1)/127.0, 1.0, 0, 1.0);
        //qDebug() << (color + 1);
    }
    else
    {
        pGeoPoint->color[0] = 1.0;
        pGeoPoint->color[1] = 1.0 - (sensorVal + 1)/255.0;
        pGeoPoint->color[2] = 1.0;
        //glColor4f(1.0, 1.0 - (color + 1)/255.0, 0, 1.0);
        //qDebug() << (color + 1);
    }
}

GeoPointValues *OnlineData::getOnlineData()
{
    pGeoPoint = GeoCoord.odometryToGeo();

    // color val (char[3])
    bool ok = true;
    int tempSensorVal = TcpServer.getLastData().toInt(&ok);
    if(ok)
    {
        unsigned char sensorVal = realSensorValToUChar(tempSensorVal); // correct according to sensor type
        sensorValToColor(sensorVal);
    }
    return pGeoPoint;
}

void OnlineData::setZeroGeoPoint(double outZeroDegLatitude, double outZeroDegLongitude)
{
    GeoCoord.setZeroGeoPoint(outZeroDegLatitude, outZeroDegLongitude);
}
