#ifndef MAINCONTROLLER_H
#define MAINCONTROLLER_H

//this class is Main Controller

#include "../../Models/OnlineData/OnlineData.h"
#include "../../Views/widget/widget.h"
#include "../../Models/GeoMap/GeoMap.h"
#include "../../Views/dialog/dialog.h"

#include <QTimer> // timer
#include <QObject> // someware else included

class MainController : public QObject
{
private:

    Q_OBJECT // it is neaded for signals & slots

    bool mode; // true - online, false - offline
    OnlineData Online;
    Widget OpenGLView; // view
    Dialog *UDialog; // view (it sets first parameters)
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
    void userDialogInit();
    void openGlRedrawPoints();
    void addPointFromOnlineData(const int &minTemperature, const int &maxTemperature);
    void setFileName(QString tempFileName);
    void setMode(bool online); // bool - online

public slots:
    void updateTime(); // slot for timer
    void userLunchedApp(); // slot subscribed to dialog start button clicked
};

#endif // MAINCONTROLLER_H
