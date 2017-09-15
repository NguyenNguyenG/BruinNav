//
//  support.h
//  Project_Four
//
//  Created by nguyen nguyen on 3/13/17.
//  Copyright © 2017 nguyen nguyen. All rights reserved.
//

#ifndef support_h
#define support_h
#include "provided.h"
#include <string>

//used to hold the node in the graph that maps the direction
struct NavNode
{
    NavNode* parent;
    GeoCoord coord;
    double h;
    double g;
    double f;
};

//used for the priority queue
class Comparison
{
public:
    bool operator() (const NavNode* first, const NavNode* second)
    {
        return first->f > second->f;
    }
};

//used for the MyMap.h
inline bool operator>(const GeoCoord& first, const GeoCoord& second)
{
    if(first.latitude > second.latitude)
    {
        return true;
    }
    if(first.latitude == second.latitude)
    {
        if(first.longitude > second.longitude)
            return true;
    }
    return false;
}
//used for MyMap.h and Navigator.cpp
inline bool operator==(const GeoCoord& first, const GeoCoord& second)
{
    if(first.latitude == second.latitude && first.longitude == second.longitude)
        return true;
    return false;
}
//used for MyMap.h
inline bool operator<(const GeoCoord& first, const GeoCoord& second)
{
    if(first == second)
        return false;
    return!(first > second);
}

//getting direction of the a line 
inline std::string directionOfLine(const GeoSegment& seg)
{
    double angle = angleOfLine(seg);
    if(angle >= 0 && angle <= 22.5)
        return "east";
    else if(angle > 22.5 && angle <= 67.5)
        return "northeast";
    else if(angle > 67.5 && angle <= 112.5)
        return "north";
    else if(angle > 112.5 && angle <= 157.5)
        return "northwest";
    else if(angle > 157.5 && angle <= 202.5)
        return "west";
    else if(angle > 202.5 && angle <= 247.5)
        return "southwest";
    else if(angle > 247.5 && angle <= 292.5)
        return "south";
    else if(angle > 292.5 && angle <= 337.5)
        return "southeast";
    else if(angle > 337.5 && angle < 360)
        return "east";
    else
        return "";
}



#endif /* support_h */
