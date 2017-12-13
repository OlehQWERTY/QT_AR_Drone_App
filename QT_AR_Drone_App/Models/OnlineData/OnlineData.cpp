#include "OnlineData.h"

OnlineData::OnlineData()
{
}

void OnlineData::sensorValToColor(int &val, const int &minTemperature, const int &maxTemperature) // test me !!!!!!!!!!!!!!!!!!!!!!!!!!
{
    qDebug() << "val: " << val;
    int coefficient = 100; // because float from arduino * 100 and sending here

    if(val < minTemperature * coefficient)
    {
        val = minTemperature * coefficient;
        qDebug() << "Temperature value out of min range!";
    }
    else if(val > maxTemperature * coefficient)
    {
        val = maxTemperature * coefficient;
        qDebug() << "Temperature value out of max range!";
    }

    int delta = (val - minTemperature * coefficient) / coefficient;
    float step = (maxTemperature - minTemperature) / 255.0; // convert to uchar          delta / coefficient / 255.0
    unsigned char tempRelativeTemperature = delta / step;
    qDebug() << "tempRelativeTemperature: " << tempRelativeTemperature;

    if(tempRelativeTemperature < 127)
    {
        pGeoPoint->color[0] = (tempRelativeTemperature + 1)/127.0 * 255;
        pGeoPoint->color[1] = 255;
        pGeoPoint->color[2] = 0;
    }
    else
    {
        pGeoPoint->color[0] = 255;
        pGeoPoint->color[1] = (1.0 - (tempRelativeTemperature + 1)/256.0) * 255; // deffence (255 + 1)/255 > 1 -> 1 - 1.001 = minus number -> error
        pGeoPoint->color[2] = 0;
    }
//    qDebug() << "Color: r " << pGeoPoint->color[0] << "Color: g " << pGeoPoint->color[1] <<
//                "Color: b " << pGeoPoint->color[2];
}

GeoPointValues *OnlineData::getOnlineData(const int &minTemperature, const int &maxTemperature)
{
    pGeoPoint = GeoCoord.odometryToGeo();

    // tcp ip part
    // color val (char[3])
    int tempSensorVal = TcpServer.getLastData(); // QByteArray return TcpServer -> TcpServer.getLastData().toInt(&ok)

    sensorValToColor(tempSensorVal, minTemperature, maxTemperature); // automatic correction according to sensor temperature
    qDebug() << "OnlineData: " << tempSensorVal;

    return pGeoPoint;
}

void OnlineData::setZeroGeoPoint(double outZeroDegLatitude, double outZeroDegLongitude)
{
    GeoCoord.setZeroGeoPoint(outZeroDegLatitude, outZeroDegLongitude);
}

bool OnlineData::isLaunched() const // it is neaded for MainController (is server is not started error message)
{
    return TcpServer.isLaunched();
}
