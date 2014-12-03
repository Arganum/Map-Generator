#ifndef ROADPAINTER_H
#define ROADPAINTER_H

#include <QImage>
#include <QPainter>
#include <QFile>
#include <iostream>
#include <math.h>
#include "roadStructs.h"

class roadPainter
{
public:
    roadPainter();

    void intiImage(Bounds _bound);
    void intiPainter();
    void endPainter();
    void drawLines(std::vector<Way> _ways);

    QImage readImage();
    void saveImage(QFile *device);


    //QImage::Format_RGB32
private:
    Node A,B,D;     // The three cornors on a rectangle
    QImage image;
    QPainter painter;
    QLineF a,b,c,d; // The four sides on a rectangle    A---------a---------B
                    //                                  |                   |
                    //                                  d                   b
                    //                                  |                   |
                    //                                  D---------c---------C

    double convLatLon(double _latitude1, double _longitude1, double _latitude2, double _longitude2);
    QPointF convLatLon(double _longitude, double _latitude);
    QPointF normalizePoint(QPointF _pointNorm, QPointF _point);
    QColor findRoadColor(double _totalRoad, double _currRoad);

    QPointF Circle2CircleIntersect(double _latitude, double _longitude);

    double deg2rad(double _deg);
    double rad2deg(double _rad);
};

#endif // ROADPAINTER_H
