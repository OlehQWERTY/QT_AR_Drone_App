#include "MainController.h"

MainController::MainController(bool online = true) : OnlineData() // bool online
{
    // timer
    tmr = new QTimer(this);
    tmr->setInterval(1000);
    connect(tmr, SIGNAL(timeout()), this, SLOT(updateTime()));
    tmr->start();
    //timer


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
   OpenGLView.showAllPoints();
}

//GeoPointValues *MainController::getOnlineData() // add data from Online Data
//{

////    for(int i = 0; i < 3; i++)
////    {
////        unsigned char arr[3] = {125, 50 * i, 80 * i};
////        Map.addPoint(14.89*i, 78.1*i, 0.1*i*i, 0.2*i, 100, arr); // bug I change x y z cartesian and it gets the same in one iteration
////    }
////    Map.save();
////    Map.mapUpdate();
//    //Map.showAllPoints();

//    //get Point
////    qDebug() << "Length" << Map.getLength();

////    GeoPointValues so = Map.getPoint(4);
////    GeoPointValues so1 = Map.getFirst();
////    GeoPointValues so2 = Map.getLast();

////    qDebug() << so.id;
////    qDebug() << so1.id;
////    qDebug() << so2.id;
//}

void MainController::addPointOnlineData() // add data from Online Data
{
    GeoPointValues *pTempGeoPointValues;
    unsigned char tempColor[3] = {0, 0, 0};
//    for(int i = 0; i < 3; i++)
//    {

        //unsigned char arr[3] = {125, 50 * i, 80 * i};
        //if(tempGeoPointValues != getOnlineData())
        //{
//    double tempCartesianX = 0;
//    double tempCartesianY = 0;
//    double tempCartesianZ = 0;

    pTempGeoPointValues = getOnlineData();

//    if(pTempGeoPointValues->id > 5)// test // id is set on higher level
        //pTempGeoPointValues->cartesianX += tempCartesianX; // test // for changing val


//    if(tempCartesianX != pTempGeoPointValues->cartesianX || tempCartesianY != pTempGeoPointValues->cartesianY
//            || tempCartesianZ != pTempGeoPointValues->cartesianZ)
//    {
//        qDebug() << "111111111111111111111111111111111111";
//        qDebug() << tempCartesianX;
//        qDebug() << pTempGeoPointValues->cartesianX;

//        tempCartesianX = pTempGeoPointValues->cartesianX;
//        tempCartesianY = pTempGeoPointValues->cartesianY;
//        tempCartesianZ = pTempGeoPointValues->cartesianZ;
            for(int i = 0; i< 3; i++)
            {
                tempColor[i] = pTempGeoPointValues->color[i];
            }

            Map.addPoint(pTempGeoPointValues->latitude, pTempGeoPointValues->longitude, pTempGeoPointValues->cartesianX,
                         pTempGeoPointValues->cartesianY, pTempGeoPointValues->cartesianZ, tempColor);

            Map.save();
            Map.mapUpdate();
        //}
    qDebug() << "timer test";
            //Map.showAllPoints();
//    }
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
    qDebug() << "Timer!";
    addPointOnlineData();
}
