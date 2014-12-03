#ifndef ROADSTRUCTS_H
#define ROADSTRUCTS_H

#include <vector>
#include <QPointF>

#define MAX_ROAD 16581375
#define MAP_SCALE 1000 //1pixel = 1m

struct Bounds
{
    Bounds() :
        minLatitude(0), minLongitude(0),
        maxLatitude(0), maxLongitude(0),
        minFrameLatitude(0), minFrameLongitude(0),
        maxFrameLatitude(0),maxFrameLongitude(0)  {}
    double minLatitude;
    double minLongitude;
    double maxLatitude;
    double maxLongitude;

    double minFrameLatitude;
    double minFrameLongitude;
    double maxFrameLatitude;
    double maxFrameLongitude;
};

struct Node
{
    Node() : nodeID(0), nodeLatitude(0), nodeLongitude(0) {}
    uint sequenceNumber;
    unsigned long nodeID;
    double nodeLatitude;
    double nodeLongitude;

    bool operator<(const Node& a) const
    {
        return sequenceNumber < a.sequenceNumber;
    }
};

struct Way
{
    Way() : aHighway(false), wayName("None"), wayHighwayType("None") {}
    bool aHighway;
    std::vector<Node> wayNodeList;
    std::vector<unsigned long> nodeIDList;
    std::string wayName;
    std::string wayHighwayType;
};

struct CircleIntersect
{
    CircleIntersect() : point1(0,0), point2(0,0) {}
    QPointF point1;
    QPointF point2;
};

#endif // ROADSTRUCTS_H
