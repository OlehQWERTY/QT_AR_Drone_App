#ifndef APPINITDATA_H
#define APPINITDATA_H

#include <QString>

// struct that is used for returning init data fields from Views/dialog

struct AppInitData
{
    bool mode = false; // default - offline mode
    // geo coordinates
    double latitude = 0;
    double longitude = 0;
    // file Path (for offline mode)
    QString fileName; // e.g. 01_02_17.json
    // temperature range
    int minT = 0;
    int maxT = 0;
};

#endif // APPINITDATA_H
