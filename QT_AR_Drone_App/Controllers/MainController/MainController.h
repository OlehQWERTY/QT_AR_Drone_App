#ifndef MAINCONTROLLER_H
#define MAINCONTROLLER_H

#include "../../Models/OnlineData/OnlineData.h"
#include "../../Views/widget/widget.h"
#include "../../Models/GeoMap/GeoMap.h"

#include <QTimer> // timer
#include <QObject> // someware included

class MainController : public QObject, public OnlineData, private GeoMap
{
private:

    Q_OBJECT // it is neaded for signals & slots

    bool mode; // true - online, false - offline
    Widget OpenGLView; // view
    GeoMap Map;

    QTimer *tmr; // timer


    void setOnlineMode(); // add
    void setOfflineMode(); // add

public:
    MainController(bool online); //bool online
    void openGlViewInit(); // add
    void openGlRedrawPoints();
    void addPointOnlineData();

public slots:
    void updateTime(); // slot for timer
};

#endif // MAINCONTROLLER_H
