#ifndef MAINCONTROLLER_H
#define MAINCONTROLLER_H

#include "../../Models/OnlineData/OnlineData.h"
#include "../../Views/widget/widget.h"
#include "../../Models/GeoMap/GeoMap.h"

class MainController : public OnlineData, private GeoMap
{
private:
    bool mode; // true - online, false - offline
    Widget OpenGLView; // view
    GeoMap Map;


    void setOnlineMode(); // add
    void setOfflineMode(); // add

public:
    MainController(bool online); //bool online
    void openGlViewInit(); // add
    void openGlRedrawPoints();

    void getOnlineData();
};

#endif // MAINCONTROLLER_H
