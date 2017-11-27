#include "MainController.h"

MainController::MainController(bool online = true) : OnlineData() // bool online
{
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

void MainController::getOnlineData() // add data from Online Data
{
    for(int i = 0; i < 3; i++)
    {
        unsigned char arr[3] = {125, 50 * i, 80 * i};
        Map.addPoint(14.89*i, 78.1*i, 0.1*i*i, 0.2*i, 100, arr); // bug I change x y z cartesian and it gets the same in one iteration
    }
    Map.save();
    Map.mapUpdate();
    //Map.showAllPoints();

    //get Point
//    qDebug() << "Length" << Map.getLength();

//    GeoPointValues so = Map.getPoint(4);
//    GeoPointValues so1 = Map.getFirst();
//    GeoPointValues so2 = Map.getLast();

//    qDebug() << so.id;
//    qDebug() << so1.id;
//    qDebug() << so2.id;
}
