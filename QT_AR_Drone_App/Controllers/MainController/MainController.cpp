#include "MainController.h"

MainController::MainController(const double &Latitude, const double &Longitude) : OnlineData()
{
    openGlViewInit();
    setZeroGeoPoint(Latitude, Longitude);
}

void MainController::setMode(bool online = true) // bool online
{
    if(online)
    {
        setOnlineMode();
    }
    else
    {
        setOfflineMode();
    }
}

void MainController::setOnlineMode() // connected with OnlineData
{
    // timer
    tmr = new QTimer(this);
    tmr->setInterval(1000); // timer interval 1 sec
    connect(tmr, SIGNAL(timeout()), this, SLOT(updateTime()));
    tmr->start();
}

void MainController::setOfflineMode() // connected with GeoMap
{
    Map.convertJsonToPoints(fileName);
    //Map.showJson();
    //Map.showAllPoints();
    openGlRedrawPoints();
    OpenGLView.updateGL(); // update open GL scene
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

void MainController::openGlRedrawPoints()
{
   OpenGLView.getAllPointsList(Map.getAllPointsList()); // add send it to View
   //OpenGLView.showAllPoints();
}

void MainController::addPointFromOnlineData()
{
    GeoPointValues *pTempGeoPointValues;
    unsigned char tempColor[3] = {0, 0, 0};

    pTempGeoPointValues = getOnlineData();

//    if(tempCartesianX != pTempGeoPointValues->cartesianX || tempCartesianY != pTempGeoPointValues->cartesianY
//            || tempCartesianZ != pTempGeoPointValues->cartesianZ)

    for(int i = 0; i< 3; i++)
    {
        tempColor[i] = pTempGeoPointValues->color[i];
    }

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
    addPointFromOnlineData();
    openGlRedrawPoints();
    OpenGLView.updateGL(); // update open GL scene
}
