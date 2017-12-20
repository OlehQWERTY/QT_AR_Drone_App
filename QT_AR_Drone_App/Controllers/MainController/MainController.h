#ifndef MAINCONTROLLER_H
#define MAINCONTROLLER_H

//this class is Main Controller

#include "../../Models/OnlineData/OnlineData.h"
#include "../../Views/widget/widget.h"
#include "../../Models/GeoMap/GeoMap.h"
#include "../../Views/dialog/dialog.h"
#include "../../Views/inputError/inputerror.h"
#include "../../Views/serverConnectionError/serverConnectionError.h"

#include <QTimer> // timer
#include <QObject> // someware else included

#include <QMediaPlayer> // mp3 player
#include <QDir>
#include <QUrl>

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
    AppInitData AppData; // struct for saving init data from dialog wimdow
    double minTemperature = 0;
    double maxTemperature = 0;

    bool setOnlineMode(); // if server is not started - return false
    void setOfflineMode();
    bool getDataFromDialog();

public:
    MainController(const int&); // doesn't work if I call constructor without parameters MainController() (the base class
    //constructor is called to initialize the base class members and then the derived class constructor
    void openGlViewInit();
    void userDialogInit();
    void openGlRedrawPoints();
    void addPointFromOnlineData(const int &minTemperature, const int &maxTemperature);
    void setFileName(QString tempFileName);
    void initApp(/*bool online*/); // bool - online

public slots:
    void updateTime(); // slot for timer
    void userLaunchedApp(); // slot subscribed to dialog start button clicked
};

#endif // MAINCONTROLLER_H
