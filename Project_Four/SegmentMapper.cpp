#include "provided.h"
#include <vector>
#include "MyMap.h"
using namespace std;

class SegmentMapperImpl
{
public:
    SegmentMapperImpl();
    ~SegmentMapperImpl();
    void init(const MapLoader& ml);
    vector<StreetSegment> getSegments(const GeoCoord& gc) const;
private:
    MyMap<GeoCoord, vector<StreetSegment> > m_segmentMapper;
};

SegmentMapperImpl::SegmentMapperImpl()
{
}

SegmentMapperImpl::~SegmentMapperImpl()
{
}

void SegmentMapperImpl::init(const MapLoader& ml)
{
    // going through all of the street
    for(int i = 0; i < ml.getNumSegments(); i++)
    {
        StreetSegment currStreet;
        ml.getSegment(i, currStreet);
        vector<StreetSegment> associateStreet;
        associateStreet.push_back(currStreet);
        
        vector<StreetSegment>* value = m_segmentMapper.find(currStreet.segment.start);
        //if there is no street associated with this coordinate yet
        if( value == nullptr)
        {
            //just map the coordinate with the vector of street segments
            m_segmentMapper.associate(currStreet.segment.start,associateStreet);
        }
        else
            //otherwise just ass the street to the vector
            value ->push_back(currStreet);
        
        //repeat same process above but for the ending coordinate
        value = m_segmentMapper.find(currStreet.segment.end);
        if( value == nullptr)
        {
            m_segmentMapper.associate(currStreet.segment.end,associateStreet);
        }
        else
            value ->push_back(currStreet);
        
        //also map all of the attractions inside the street to the street segment
        for(int j = 0; j < currStreet.attractions.size(); j++)
        {
            vector<StreetSegment>* valueAttr = m_segmentMapper.find(currStreet.attractions[j].geocoordinates);
            if(valueAttr == nullptr)
            {
                m_segmentMapper.associate(currStreet.attractions[j].geocoordinates, associateStreet);
            }
            else
                valueAttr -> push_back(currStreet);
        }
    }
}

vector<StreetSegment> SegmentMapperImpl::getSegments(const GeoCoord& gc) const
{
    const vector<StreetSegment>* segments = m_segmentMapper.find(gc);
    if(segments != nullptr)
        return *segments;
    vector<StreetSegment> res;
    return res;
}

//******************** SegmentMapper functions ********************************

// These functions simply delegate to SegmentMapperImpl's functions.
// You probably don't want to change any of this code.

SegmentMapper::SegmentMapper()
{
    m_impl = new SegmentMapperImpl;
}

SegmentMapper::~SegmentMapper()
{
    delete m_impl;
}

void SegmentMapper::init(const MapLoader& ml)
{
    m_impl->init(ml);
}

vector<StreetSegment> SegmentMapper::getSegments(const GeoCoord& gc) const
{
    return m_impl->getSegments(gc);
}
