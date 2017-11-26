#ifndef MAINCONTROLLER_H
#define MAINCONTROLLER_H

#include "../../Models/OnlineData/OnlineData.h"

class MainController : public OnlineData
{
private:
    bool mode; // true - online, false - offline

    void setOnlineMode(); // add
    void setOfflineMode(); // add

public:
    MainController(bool online); //bool online
};

#endif // MAINCONTROLLER_H
