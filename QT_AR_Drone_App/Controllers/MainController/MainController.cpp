#include "MainController.h"

MainController::MainController(int const &notused)
{
    //qDebug() << "MainController";
    UDialog = new Dialog;
    userDialogInit();

    connect(UDialog, SIGNAL(StartPressed()),this,SLOT(userLunchedApp())); // start (dialog.h) clicked - lunch View from widget.h
}

void MainController::initApp(/*bool online = true*/) // bool online
{
    getDataFromDialog(); // get data from dialog
    Online.setZeroGeoPoint(AppData.latitude, AppData.longitude);
    Online.setZeroGeoPoint(AppData.latitude, AppData.longitude);
    // auto color level in Online data
    minTemperature = AppData.minT;
    maxTemperature = AppData.maxT;

    qDebug() << "Online.isLaunched(): " << Online.isLaunched();
    if(AppData.mode)
    {

        setOnlineMode();
    }
    else
    {
        setFileName(AppData.fileName);
        setOfflineMode();
    }
}

bool MainController::setOnlineMode() // connected with OnlineData
{
    // server start checking (if false error and you should restart app)
    if(!Online.isLaunched())
    {
        serverConnectionError *ConnectionError;
        ConnectionError = new serverConnectionError;
        ConnectionError->setWindowTitle("Connection Error!");
        ConnectionError->setWindowIcon(QIcon("errorico.ico")); // app icon
        ConnectionError->show();
        // close dialog form
        UDialog->close(); // move it to more appropriate place
        delete UDialog; // move it to more appropriate place

        return false;
    }
    else
    {
        setOnlineMode(); // online mode normal start
    }

    // timer
    tmr = new QTimer(this);
    tmr->setInterval(1000); // timer interval 1 sec
    connect(tmr, SIGNAL(timeout()), this, SLOT(updateTime()));
    tmr->start();

    return true;
}

void MainController::setOfflineMode() // connected with GeoMap
{
    Map.convertJsonToPoints(fileName);
    //Map.showJson();
    //Map.showAllPoints();
    openGlRedrawPoints();
    OpenGLView.updateGL(); // update open GL scene
}

bool MainController::getDataFromDialog()
{
    AppData = UDialog->returnAppData();
    if(AppData.errorFlag)
    {
        inputError *Error;
        Error = new inputError; // don't forget to delete it (if it is neaded because now user manualy close error message)
        Error->setWindowTitle("Input Error!");
        Error->setWindowIcon(QIcon("errorico.ico")); // app icon
        Error->show();
        return false; // user data is wrong
    }
    return true; // user data is correct
}

void MainController::setFileName(QString tempFileName)
{
    fileName = tempFileName;
}

void MainController::openGlViewInit()
{
    OpenGLView.setSceneParam(800, 800, 80);
    OpenGLView.setWindowTitle("OpenGL Gas Map");
    OpenGLView.setWindowIcon(QIcon("myappico.ico")); // app icon
    OpenGLView.show();
}

void MainController::userDialogInit()
{
    UDialog->setWindowTitle("Settings");
    UDialog->setWindowIcon(QIcon("myappico.ico")); // app icon
    UDialog->show();
}

void MainController::openGlRedrawPoints()
{
   OpenGLView.getAllPointsList(Map.getAllPointsList()); // add send it to View
   //OpenGLView.showAllPoints();
}

void MainController::addPointFromOnlineData(const int &minTemperature, const int &maxTemperature)
{
    GeoPointValues *pTempGeoPointValues;
    unsigned char tempColor[3] = {0, 0, 0};

    pTempGeoPointValues = Online.getOnlineData(minTemperature, maxTemperature);

    for(int i = 0; i< 3; i++)
    {
        tempColor[i] = pTempGeoPointValues->color[i];
        qDebug() << "tempColor[" << i << "]: " << tempColor[i]; // test
    }
    //qDebug() << pTempGeoPointValues->latitude;
    Map.addPoint(pTempGeoPointValues->latitude, pTempGeoPointValues->longitude, pTempGeoPointValues->cartesianX,
                 pTempGeoPointValues->cartesianY, pTempGeoPointValues->cartesianZ, pTempGeoPointValues->timestamp, tempColor);
    Map.save();
    Map.mapUpdate();
    //Map.showAllPoints(); // debugging
    //get Point
    qDebug() << "Length" << Map.getLength();

//    GeoPointValues so = Map.getPoint(4);
//    GeoPointValues so1 = Map.getFirst();
//    GeoPointValues so2 = Map.getLast();

//    qDebug() << so.id;
//    qDebug() << so1.id;
//    qDebug() << so2.id;
}


void MainController::updateTime() // timer slot
{
    addPointFromOnlineData(minTemperature, maxTemperature);
    openGlRedrawPoints();
    OpenGLView.updateGL(); // update open GL scene
}

void MainController::userLunchedApp() // MainController gets signal Start Button clicked from dialog
{
    // getDataFromDialog - right input data
    // ( (AppData.mode && setOnlineMode()) || !AppData.mode) - online mode + server was started
    if(getDataFromDialog() && ( (AppData.mode && setOnlineMode()) || !AppData.mode) ) // wrong data was inputted in dialog form
    {
        initApp();
        UDialog->close(); // move it to more appropriate place
        delete UDialog; // move it to more appropriate place

        openGlViewInit(); // start widget (OpenGL view)
    }


    //qDebug() << "MainController get signal Start Button clicked from dialog!";
}
