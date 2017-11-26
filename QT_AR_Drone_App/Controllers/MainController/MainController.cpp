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
