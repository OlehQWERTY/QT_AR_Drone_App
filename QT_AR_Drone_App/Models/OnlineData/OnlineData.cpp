#include "OnlineData.h"

//#include <iostream> // test

OnlineData::OnlineData()
{
    //qDebug() << "OnlineData constructor";
}

void OnlineData::sensorValToColor(int &val, const int &minTemperature, const int &maxTemperature) // test me !!!!!!!!!!!!!!!!!!!!!!!!!!
{
    qDebug() << "val: " << val;
    int coefficient = 100; // because float from arduino * 100 and sending here

    if(val < minTemperature * coefficient)
    {
        val = minTemperature * coefficient;
    }
    else if(val > maxTemperature * coefficient)
    {
        val = maxTemperature * coefficient;
    }


    int delta = (val - minTemperature) * coefficient;
    qDebug() << "delta: " << delta;
    float step = delta / coefficient / 255.0; // convert to uchar
    qDebug() << "step: " << step;
    unsigned char tempRelativeTemperature = (val - minTemperature * coefficient) / coefficient * step;
    qDebug() << "tempRelativeTemperature: " << tempRelativeTemperature;

    if(tempRelativeTemperature < 127)
    {
        pGeoPoint->color[0] = (tempRelativeTemperature + 1)/127.0;
        pGeoPoint->color[1] = 1.0;
        pGeoPoint->color[2] = 1.0;
        //glColor4f((color + 1)/127.0, 1.0, 0, 1.0);
        //qDebug() << (tempRelativeTemperature);
    }
    else
    {
        pGeoPoint->color[0] = 1.0;
        pGeoPoint->color[1] = 1.0 - (tempRelativeTemperature + 1)/256.0; // deffence (255 + 1)/255 > 1 -> 1 - 1.001 = minus number -> error
        pGeoPoint->color[2] = 1.0;
        //glColor4f(1.0, 1.0 - (color + 1)/255.0, 0, 1.0);
//        qDebug() << (tempRelativeTemperature);
    }
    //std::cout << tempRelativeTemperature << std::endl; // test
}

GeoPointValues *OnlineData::getOnlineData()
{
    pGeoPoint = GeoCoord.odometryToGeo();

    // tcp ip part
    // color val (char[3])
    int tempSensorVal = TcpServer.getLastData(); // QByteArray return TcpServer -> TcpServer.getLastData().toInt(&ok)

    sensorValToColor(tempSensorVal, 20, 40); // correct according to sensor type
    qDebug() << "OnlineData: " << tempSensorVal;

    return pGeoPoint;
}

void OnlineData::setZeroGeoPoint(double outZeroDegLatitude, double outZeroDegLongitude)
{
    GeoCoord.setZeroGeoPoint(outZeroDegLatitude, outZeroDegLongitude);
}
