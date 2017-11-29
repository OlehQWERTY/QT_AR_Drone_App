#include "MainController.h"

MainController::MainController(bool online = true) : OnlineData() // bool online
{
    // timer
    tmr = new QTimer(this);
    tmr->setInterval(1000);
    connect(tmr, SIGNAL(timeout()), this, SLOT(updateTime()));
    tmr->start();
    //timer

    // open GL
    openGlViewInit();

    //set mode
    mode = online;
    if(mode)
    {
        setOnlineMode();
    }
    else
    {
        setOfflineMode();
    }
}

void MainController::setOnlineMode() // work with OnlineData
{

}

void MainController::setOfflineMode() // work with GeoMap
{

}

void MainController::openGlViewInit() // work with view
{
    //Widget OpenGLView;
    OpenGLView.setSceneParam(800, 800, 80);
    OpenGLView.show();
}

void MainController::openGlRedrawPoints()
{
   OpenGLView.getAllPointsList(Map.getAllPointsList()); // add send it to View
   //OpenGLView.showAllPoints();
}

void MainController::addPointOnlineData() // add data from Online Data
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
                 pTempGeoPointValues->cartesianY, pTempGeoPointValues->cartesianZ, tempColor);

    Map.save();
    Map.mapUpdate();

    //qDebug() << "timer test";
    //Map.showAllPoints();

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
    //qDebug() << "Timer!";
    addPointOnlineData();
    openGlRedrawPoints();

    OpenGLView.updateGL(); // update open GL scene
}
