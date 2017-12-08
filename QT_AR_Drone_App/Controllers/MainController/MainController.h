#ifndef MAINCONTROLLER_H
#define MAINCONTROLLER_H

//this class is Main Controller

#include "../../Models/OnlineData/OnlineData.h"
#include "../../Views/widget/widget.h"
#include "../../Models/GeoMap/GeoMap.h"

#include <QTimer> // timer
#include <QObject> // someware else included

class MainController : public QObject//, public OnlineData//, private GeoMap
{
private:

    Q_OBJECT // it is neaded for signals & slots

    bool mode; // true - online, false - offline
    OnlineData Online;
    Widget OpenGLView; // view
    GeoMap Map;
    QTimer *tmr; // timer
    QString fileName;

    void setOnlineMode();
    void setOfflineMode();

public:
    MainController(const double &Latitude, const double &Longitude);
    void openGlViewInit();
    void openGlRedrawPoints();
    void addPointFromOnlineData();
    void setFileName(QString tempFileName);
    void setMode(bool online); // bool - online

public slots:
    void updateTime(); // slot for timer
};

#endif // MAINCONTROLLER_H
