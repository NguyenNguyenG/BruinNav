#include "provided.h"
#include <string>
#include <vector>
#include <fstream>
using namespace std;

#include <iostream>
class MapLoaderImpl
{
public:
    MapLoaderImpl();
    ~MapLoaderImpl();
    bool load(string mapFile);
    size_t getNumSegments() const;
    bool getSegment(size_t segNum, StreetSegment& seg) const;
    //void check() const;
private:
    int m_segmentCounter;
    vector<StreetSegment> m_segment;
};

/*
void MapLoaderImpl::check() const
{
    for(int i = 0; i < m_segmentCounter; i++)
    {
        cerr << m_segment[i].streetName<<endl;
        cerr << m_segment[i].segment.start.latitudeText << ", " << m_segment[i].segment.start.longitudeText << " " <<
        m_segment[i].segment.end.latitudeText << "," << m_segment[i].segment.end.longitudeText << endl;
        cerr << m_segment[i].attractions.size() << endl;
        for(int j = 0; j < m_segment[i].attractions.size(); j++)
        {
            cerr <<  m_segment[i].attractions[j].name << "|" << m_segment[i].attractions[j].geocoordinates.latitudeText << ", " << m_segment[i].attractions[j].geocoordinates.longitudeText << endl;
        }
    }
}
*/

MapLoaderImpl::MapLoaderImpl()
{
    m_segmentCounter = 0;
}

MapLoaderImpl::~MapLoaderImpl()
{
}

bool MapLoaderImpl::load(string mapFile)
{
    ifstream input(mapFile);
    if(!input)
        return false;
    string name;
    while(getline(input,name))
    {
        StreetSegment newStreetSegment;
        newStreetSegment.streetName = name;
        char c;
        string streetLatLong;
        string startLat,startLong, endLat,endLong;
        int counter = 0;
        //getting the geocords of the starting and ending of a street segment
        while(input.get(c))
        {
            //very last coord is the long of the street
            if(c == '\n')
            {
                endLong = streetLatLong;
                break;
            }
            else if (c == ',' || c == ' ')
            {
                if(streetLatLong != "")
                {
                    //first coordinate is the lat of the start
                    if(counter == 0)
                    {
                        startLat = streetLatLong;
                    }
                    //second coord is the long of the start
                    else if(counter == 1)
                    {
                        startLong = streetLatLong;
                    }
                    //third coord is the lat of the end
                    else if(counter == 2)
                    {
                        endLat = streetLatLong;
                    }
                    counter++;
                }
                streetLatLong = "";
            }
            else
            {
                streetLatLong += c;
            }
        }
        //making the geocord of start and end
        GeoCoord streetStartCoord(startLat, startLong);
        GeoCoord streetEndCoord(endLat, endLong);
        
        //making the streetsegment
        newStreetSegment.segment.start = streetStartCoord;
        newStreetSegment.segment.end = streetEndCoord;
        
        int attr;
        input >> attr;
        
        input.ignore(100, '\n');
        if(attr > 0)
        {
            //going through all of the attraction
            for(; attr > 0; attr--)
            {
                //getting the attraction name
                string nameAttr;
                while(input.get(c) && c != '|')
                {
                    nameAttr  = nameAttr + c;
                }
                Attraction newAttraction;
                newAttraction.name = nameAttr;
                
                string attrLoc;
                string attrLocLat, attrLocLong;
                
                //getting the geocoord of the attraction
                while(input.get(c))
                {
                    if(c == '\n')
                    {
                        attrLocLong = attrLoc;
                        break;
                    }
                    else if (c == ',' || c == ' ')
                    {
                        if(attrLoc != "")
                        {
                            attrLocLat = attrLoc;
                        }
                        attrLoc = "";
                    }
                    else
                    {
                        attrLoc = attrLoc + c;
                    }
                }
                //make the new attraction and push back into the street attraction vector
                GeoCoord attrGeoCoord(attrLocLat, attrLoc);
                newAttraction.geocoordinates = attrGeoCoord;
                newStreetSegment.attractions.push_back(newAttraction);
            }
        }
        //put the segment inside a container and increment counter
        m_segment.push_back(newStreetSegment);
        m_segmentCounter++;
    }
    return true;
}

size_t MapLoaderImpl::getNumSegments() const
{
    return m_segmentCounter; 
}

bool MapLoaderImpl::getSegment(size_t segNum, StreetSegment &seg) const
{
    if(segNum < 0 || segNum >= m_segmentCounter)
        return false;
    seg = m_segment[segNum];
    return true;
}

//******************** MapLoader functions ************************************

// These functions simply delegate to MapLoaderImpl's functions.
// You probably don't want to change any of this code.

MapLoader::MapLoader()
{
    m_impl = new MapLoaderImpl;
}

MapLoader::~MapLoader()
{
    delete m_impl;
}

bool MapLoader::load(string mapFile)
{
    return m_impl->load(mapFile);
}

size_t MapLoader::getNumSegments() const
{
    return m_impl->getNumSegments();
}

bool MapLoader::getSegment(size_t segNum, StreetSegment& seg) const
{
    return m_impl->getSegment(segNum, seg);
}
