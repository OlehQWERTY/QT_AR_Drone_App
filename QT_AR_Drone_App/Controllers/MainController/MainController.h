#ifndef MAINCONTROLLER_H
#define MAINCONTROLLER_H

//this class is Main Controller

#include "../../Models/OnlineData/OnlineData.h"
#include "../../Views/widget/widget.h"
#include "../../Models/GeoMap/GeoMap.h"

#include <QTimer> // timer
#include <QObject> // someware else included

class MainController : public QObject
{
private:

    Q_OBJECT // it is neaded for signals & slots

    bool mode; // true - online, false - offline
    OnlineData Online;
    Widget OpenGLView; // view
    GeoMap Map;
    QTimer *tmr; // timer
    QString fileName;
    double minTemperature = 0;
    double maxTemperature = 0;

    void setOnlineMode();
    void setOfflineMode();

public:
    MainController(const double &Latitude, const double &Longitude, const double &minSensorVal, const double &maxSensorVal);
    void openGlViewInit();
    void openGlRedrawPoints();
    void addPointFromOnlineData(const int &minTemperature, const int &maxTemperature);
    void setFileName(QString tempFileName);
    void setMode(bool online); // bool - online

public slots:
    void updateTime(); // slot for timer
};

#endif // MAINCONTROLLER_H
