#include "provided.h"
#include <string>
#include <vector>
#include "support.h"
#include <queue>
#include "MyMap.h"
using namespace std;

class NavigatorImpl
{
public:
    NavigatorImpl();
    ~NavigatorImpl();
    bool loadMapData(string mapFile);
    NavResult navigate(string start, string end, vector<NavSegment>& directions) const;
    void reconstructPath(NavNode* end, vector<NavSegment>& direction) const;
private:
    AttractionMapper m_attrMapper;
    SegmentMapper m_segMapper;
};

NavigatorImpl::NavigatorImpl()
{
}

NavigatorImpl::~NavigatorImpl()
{
}

bool NavigatorImpl::loadMapData(string mapFile)
{
    //preparing all of the data structure that we will use
    MapLoader ml;
    if(!ml.load(mapFile))
        return false;
    m_attrMapper.init(ml);
    m_segMapper.init(ml);
    return true;
}

NavResult NavigatorImpl::navigate(string start, string end, vector<NavSegment> &directions) const
{
    directions.clear();
    vector<NavNode*> toBeDelete;
    //getting the start coordinate
    GeoCoord startCoord;
    if(!(m_attrMapper.getGeoCoord(start, startCoord)))
    {
        return NAV_BAD_SOURCE;
    }
    
    //getting end coordinate
    GeoCoord endCoord;
    if(!(m_attrMapper.getGeoCoord(end, endCoord)))
    {
        return NAV_BAD_DESTINATION;
    }
    
    // if the start is end, you would just return with no navigation
    if(start == end || startCoord == endCoord)
    {
        return NAV_SUCCESS;
    }
    
    //keep track of which node to keep going with
    priority_queue<NavNode*, vector<NavNode*>, Comparison> openQueue;
    MyMap<GeoCoord, NavNode*> openMap; //which nodes to keep discover
    MyMap<GeoCoord, double> closeMap;  // which nodes is already examined
    
    //setting up the start node which has heuristic of distance from start to end
    // 0 g score because its the start and final score is just the heuristic score
    NavNode* startNode = new NavNode;
    startNode->h = distanceEarthMiles(startCoord, endCoord);
    startNode->g = 0;
    startNode->f = startNode-> h;
    startNode->parent = nullptr;
    startNode->coord = startCoord;
    
    openQueue.push(startNode);
    toBeDelete.push_back(startNode);
    openMap.associate(startNode-> coord, startNode);
    
    while(!openQueue.empty())
    {
        //exam the first coordinate
        NavNode* curr = openQueue.top();
        //if the end is found, just reconstruct the path and deallocate all nodes
        if(curr -> coord == endCoord)
        {
            reconstructPath(curr, directions);
            for(int l = 0; l < toBeDelete.size(); l++)
                delete toBeDelete[l];
            return NAV_SUCCESS;
        }
        
        //update queue and closeMap
        openQueue.pop();
        closeMap.associate(curr -> coord, curr -> f);
        
        vector<StreetSegment> assoStreet = m_segMapper.getSegments(curr -> coord);
        vector<GeoCoord> neighborCoord;
        
        //getting all the coordinates that are the neighbor of the current coordinates
        for(int i = 0; i < assoStreet.size(); i++)
        {
            //will get the start and end of a street segment but will also check if any of the
            //attractions is the end goal
            neighborCoord.push_back(assoStreet[i].segment.start);
            for(int j = 0; j < assoStreet[i].attractions.size();j++)
            {
                //if it is the end goal then reconstruct the path and deallocate all nodes
                if(assoStreet[i].attractions[j].geocoordinates == endCoord)
                {
                    NavNode* goal = new NavNode;
                    goal->parent = curr;
                    goal->g = curr->g + distanceEarthMiles(curr->coord, endCoord);
                    goal->coord = endCoord;
                    
                    reconstructPath(goal, directions);
                    for(int l = 0; l < toBeDelete.size(); l++)
                        delete toBeDelete[l];
                    delete goal;
                    return NAV_SUCCESS;
                }
            }
            neighborCoord.push_back(assoStreet[i].segment.end);
        }
        //checking if any of the neighbor coordinates should be put into the priority queue
        for(int i = 0; i < neighborCoord.size(); i++)
        {
            //if a node is already examined then we just skip
            double* temp = closeMap.find(neighborCoord[i]);
            if(temp != nullptr)
                continue;
            
            NavNode** temp2 = openMap.find(neighborCoord[i]);
            
            // if a node was never examined, then calculate its property which are f, h, and g scores
            // and also link it to the current coordinate for path reconstruction
            double tentative_gScore = curr->g + distanceEarthMiles(neighborCoord[i], curr->coord);
            if(temp2 == nullptr)
            {
                NavNode* newNode = new NavNode;
                newNode->g = tentative_gScore;
                newNode->h = distanceEarthMiles(neighborCoord[i], endCoord);
                newNode->f = newNode->g + newNode->h;
                newNode->parent = curr;
                newNode->coord = neighborCoord[i];
                
                openMap.associate(newNode->coord, newNode);
                toBeDelete.push_back(newNode);
                openQueue.push(newNode);
                continue;
            }
            // if the node is in the open map to be examined, compare their cost of getting from the
            // start to here, and take the route that is better
            else if(tentative_gScore >= (*temp2) -> g)
                continue;
            (*temp2) -> parent = curr;
            (*temp2) -> g = tentative_gScore;
            (*temp2) -> f = (*temp2) -> g + (*temp2) -> h;
        }
    }
    //delallocated all nodes before returning no route
    for(int l = 0; l < toBeDelete.size(); l++)
        delete toBeDelete[l];
    return NAV_NO_ROUTE;
}

void NavigatorImpl::reconstructPath(NavNode* endNode, vector<NavSegment>& direction) const
{
    //have to reverse all linking since its linked backward right now from end to start
    NavNode *nextNode = nullptr,*prevNode = nullptr, *current = endNode;
    while(current)
    {
        nextNode = current->parent;
        current->parent = prevNode;
        prevNode = current;
        current = nextNode;
    }
    
    NavNode end = *prevNode;
    string streetName;
    vector<StreetSegment> firstNodeStreets = m_segMapper.getSegments(end.coord);
    vector<StreetSegment>secondNodeStreets = m_segMapper.getSegments(end.parent->coord);
    
    //getting the street that the first two coordinates are on
    for(int i = 0; i < firstNodeStreets.size(); i++)
    {
        for(int j = 0; j < secondNodeStreets.size(); j++)
        {
            if(firstNodeStreets[i].streetName == secondNodeStreets[j].streetName)
            {
                streetName =firstNodeStreets[i].streetName;
                break;
            }
        }
        if(streetName!= "")
            break;
    }
    //constructing the geosegment with appropriate distance and direction
    GeoSegment newGeoSegment(end.coord, (end.parent) -> coord);
    string lineDir = directionOfLine(newGeoSegment);
    NavSegment newNavSegment(lineDir, streetName, (end.parent)->g - end.g, newGeoSegment);
    direction.push_back(newNavSegment);
    
    end = *(end.parent);
    //if there are more nodes to be examined
    while(end.parent != nullptr)
    {
        //getting the street that these two nodes are on
        string newStreetName;
        vector<StreetSegment> firstNewNodeStreets = m_segMapper.getSegments(end.coord);
        vector<StreetSegment>secondNewNodeStreets = m_segMapper.getSegments(end.parent->coord);
        
        for(int i = 0; i < firstNewNodeStreets.size(); i++)
        {
            for(int j = 0; j < secondNewNodeStreets.size(); j++)
            {
                if(firstNewNodeStreets[i].streetName == secondNewNodeStreets[j].streetName)
                {
                    newStreetName =firstNewNodeStreets[i].streetName;
                    break;
                }
            }
            if(newStreetName!= "")
                break;
        }
        // different streetname indicate a turn
        if(newStreetName != streetName)
        {
            //constructing the turn navigation
            GeoSegment diffSeg(end.coord, (end.parent) -> coord);
            
            string dir = angleBetween2Lines(newGeoSegment, diffSeg) >= 180? "right":"left";
            NavSegment turn(dir, newStreetName);
            
            direction.push_back(turn);
            //constructing the proceed navigation with appropriate distances
            streetName = newStreetName;
            string diffSegDir = directionOfLine(diffSeg);
            NavSegment NavSeg(diffSegDir, streetName, (end.parent)->g - end.g, diffSeg);
            direction.push_back(NavSeg);
            //update the segment to be compared against later
            newGeoSegment.start = diffSeg.start;
            newGeoSegment.end = diffSeg.end;
        }
        else
        {
            //otherwise this would just be a continuation of a street
            newGeoSegment.start = end.coord;
            newGeoSegment.end = (end.parent) -> coord;
            string lineDir = directionOfLine(newGeoSegment);
            NavSegment NavSeg(lineDir, streetName, (end.parent)->g - end.g, newGeoSegment);
            direction.push_back(NavSeg);
        }
        end = *(end.parent);
    }
    
}

//******************** Navigator functions ************************************

// These functions simply delegate to NavigatorImpl's functions.
// You probably don't want to change any of this code.

Navigator::Navigator()
{
    m_impl = new NavigatorImpl;
}

Navigator::~Navigator()
{
    delete m_impl;
}

bool Navigator::loadMapData(string mapFile)
{
    return m_impl->loadMapData(mapFile);
}

NavResult Navigator::navigate(string start, string end, vector<NavSegment>& directions) const
{
    return m_impl->navigate(start, end, directions);
}
