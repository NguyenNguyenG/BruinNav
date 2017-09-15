#include "provided.h"
#include <string>
#include "MyMap.h"
using namespace std;

class AttractionMapperImpl
{
public:
    AttractionMapperImpl();
    ~AttractionMapperImpl();
    void init(const MapLoader& ml);
    bool getGeoCoord(string attraction, GeoCoord& gc) const;
private:
    MyMap<string,GeoCoord> m_attrMap;
};

AttractionMapperImpl::AttractionMapperImpl()
{
}

AttractionMapperImpl::~AttractionMapperImpl()
{
}

void AttractionMapperImpl::init(const MapLoader& ml)
{
    //mapping aatraction to coordinate
    for(int i = 0; i < ml.getNumSegments(); i++)
    {
        StreetSegment temp;
        ml.getSegment(i, temp);
        for(int j = 0; j < temp.attractions.size(); j++)
        {
            //lower case all characters first
            string name;
            for(int k = 0; k < temp.attractions[j].name.size(); k++)
            {
                name += tolower(temp.attractions[j].name[k]);
            }
            //associate name with that coordinate
            m_attrMap.associate(name, temp.attractions[j].geocoordinates);
        }
    }
}

bool AttractionMapperImpl::getGeoCoord(string attraction, GeoCoord& gc) const
{
    string name;
    //lower case the attraction first before searching
    for(int i =0; i < attraction.size(); i++)
        name += tolower(attraction[i]);
    //find the name
    const GeoCoord* res = m_attrMap.find(name);
    if(res == nullptr)
        return false;
    gc = *(res);
    return true;
}

//******************** AttractionMapper functions *****************************

// These functions simply delegate to AttractionMapperImpl's functions.
// You probably don't want to change any of this code.

AttractionMapper::AttractionMapper()
{
    m_impl = new AttractionMapperImpl;
}

AttractionMapper::~AttractionMapper()
{
    delete m_impl;
}

void AttractionMapper::init(const MapLoader& ml)
{
    m_impl->init(ml);
}

bool AttractionMapper::getGeoCoord(string attraction, GeoCoord& gc) const
{
    return m_impl->getGeoCoord(attraction, gc);
}
