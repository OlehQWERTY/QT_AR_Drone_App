#ifndef GEOPOINTVALUES_H
#define GEOPOINTVALUES_H

// struct that is used for returning data fields of the point

struct GeoPointValues
{
    unsigned long int id = 0;
    // geo coordinates
    double latitude = 0;
    double longitude = 0;
    // cartesian coordinates
    double cartesianX = 0;
    double cartesianY = 0;
    double cartesianZ = 0;
    unsigned long int timestamp = 0;
    unsigned char color[3] = {1, 1, 1};
};

#endif // GEOPOINTVALUES_H
