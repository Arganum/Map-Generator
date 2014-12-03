#include "roadPainter.h"

roadPainter::roadPainter()
{
}

void roadPainter::intiImage(Bounds _bound)
{
    double ImageWidth, ImageHeight;

    A.nodeLatitude = _bound.minLatitude;
    A.nodeLongitude = _bound.minLongitude;

    B.nodeLatitude = _bound.minLatitude;
    B.nodeLongitude = _bound.maxLongitude;

    D.nodeLatitude = _bound.maxLatitude;
    D.nodeLongitude = _bound.minLongitude;

    ImageWidth = convLatLon(B.nodeLatitude, B.nodeLongitude, A.nodeLatitude, A.nodeLongitude)*MAP_SCALE;
    ImageHeight = convLatLon(D.nodeLatitude, D.nodeLongitude, A.nodeLatitude, A.nodeLongitude)*MAP_SCALE;

    a.setLine(0, 0, ImageWidth, 0);
    b.setLine(ImageWidth, 0, ImageWidth, ImageHeight);
    c.setLine(ImageWidth, ImageHeight, 0, ImageHeight);
    d.setLine(0, ImageHeight, 0, 0);

    std::cout << "Geod: " << ImageWidth << std::endl;
    std::cout << "Juli: " << ImageHeight << std::endl;

    QPointF hej(0,0);
    hej = Circle2CircleIntersect( 55.3960566, 10.3662904 );
    std::cout << "Hej:  " << hej.x() << " , " << hej.y() << std::endl;

    QImage tempImage( ImageWidth+1, ImageHeight+1, QImage::Format_RGB32);
    tempImage.fill(Qt::black);
    image = tempImage;
}

void roadPainter::intiPainter()
{
    painter.begin(&image);
    painter.setBrush(Qt::NoBrush);
    painter.setPen(Qt::white);
}

void roadPainter::endPainter()
{
    painter.end();
    //*
    QColor test = findRoadColor(5,1);
    std::cout << "Color: 1 " << test.red() << " , " << test.green() << " , " << test.blue() << std::endl;
    test = findRoadColor(5,2);
    std::cout << "Color: 2 " << test.red() << " , " << test.green() << " , " << test.blue() << std::endl;
    test = findRoadColor(5,3);
    std::cout << "Color: 3 " << test.red() << " , " << test.green() << " , " << test.blue() << std::endl;
    test = findRoadColor(5,4);
    std::cout << "Color: 4 " << test.red() << " , " << test.green() << " , " << test.blue() << std::endl;
    test = findRoadColor(5,5);
    std::cout << "Color: 5 " << test.red() << " , " << test.green() << " , " << test.blue() << std::endl;
    //*/
}

void roadPainter::drawLines(std::vector<Way> _ways)
{
    //*
    std::vector<QLineF> lines;
    QLineF tempLine;
    QPointF tempPoint1, tempPoint2;

    for (uint i = 0; i < _ways.size(); i++)
    {
        for (uint j = 0; j < _ways[i].wayNodeList.size()-1; j++)
        {
            tempPoint1 = Circle2CircleIntersect( _ways[i].wayNodeList[j].nodeLatitude, _ways[i].wayNodeList[j].nodeLongitude );
            tempPoint2 = Circle2CircleIntersect( _ways[i].wayNodeList[j+1].nodeLatitude, _ways[i].wayNodeList[j+1].nodeLongitude );
            tempLine.setPoints(tempPoint1,tempPoint2);
            lines.push_back(tempLine);
            if ( i == 1 )
            {
                std::cout << "Point " << j << ": " << tempPoint1.x() << " , " << tempPoint1.y() << std::endl;
                std::cout << "Point " << j << ": " << tempPoint2.x() << " , " << tempPoint2.y() << std::endl;
            }
        }
    }

    for (uint i = 0; i < lines.size(); i++)
    {
        if ( ( (lines[i].p1().x() > a.p1().x()) && (lines[i].p1().y() > a.p1().y()) ) && ( (lines[i].p2().x() > a.p1().x()) && (lines[i].p2().y() > a.p1().y()) ) )
        {
            //std::cout << "Point Draw1!" << std::endl;
            if ( ( (lines[i].p1().x() < c.p1().x()) && (lines[i].p1().y() < c.p1().y()) ) && ( (lines[i].p2().x() < c.p1().x()) && (lines[i].p2().y() < c.p1().y()) ) )
            {
                std::cout << "Point Draw!" << std::endl;
                painter.drawLine(lines[i]);
            }
        }

    }
    //*/

    /*
    std::vector<QPointF> points;
    QPointF tempPoint;

    for (uint i = 0; i < _ways.size(); i++)
    {
        for (uint j = 0; j < _ways[i].wayNodeList.size(); j++)
        {
            tempPoint = Circle2CircleIntersect( _ways[i].wayNodeList[j].nodeLatitude, _ways[i].wayNodeList[j].nodeLongitude );
            //std::cout << "Point Draw2!" << std::endl;
            if ( (tempPoint.x() > a.p1().x()) && (tempPoint.y() > a.p1().y()) )
            {
                //std::cout << "Point Draw1!" << std::endl;
                if ( (tempPoint.x() < c.p1().x()) && (tempPoint.y() < c.p1().y()) )
                {
                    std::cout << "Point Draw!" << std::endl;
                    painter.drawPoint(tempPoint);
                }
            }
        }
    }

    //*/

    /*
    QPointF p1, p2, p3, p4, p5;
    QLineF line, line1, line2;

    p5 = convLatLon(_bound.minLongitude , _bound.minLatitude);

    p1 = convLatLon(_ways[2].wayNodeList[0].nodeLongitude, _ways[2].wayNodeList[0].nodeLatitude);
    p2 = convLatLon(_ways[2].wayNodeList[1].nodeLongitude, _ways[2].wayNodeList[1].nodeLatitude);

    p3 = normalizePoint(p1, p5);
    p4 = normalizePoint(p2, p5);

    std::cout << "NP1 : " << p3.x() << " , " << p3.y() << std::endl;
    std::cout << "NP2 : " << p4.x() << " , " << p4.y() << std::endl;
    std::cout << "P1 : " << p1.x() << " , " << p1.y() << std::endl;
    std::cout << "P2 : " << p2.x() << " , " << p2.y() << std::endl;
    std::cout << std::endl;

    line.setPoints(p3,p4);
    line1.setLine(0,0,0,image.height());
    QPointF pIntersectionPoint;

    int test = line.intersect(line1,&pIntersectionPoint);

    if ( test == QLineF::BoundedIntersection )
    {
        std::cout << "Jo Dude!!!: " << test << std::endl;
    }

    std::cout << "InterPoint: " << pIntersectionPoint.x() << " , " << pIntersectionPoint.y() << std::endl;

    line2.setPoints(pIntersectionPoint, p4);
    */
    /*
    line.setLine(1,0,5,4);
    line1.setLine(0,0,5,0);
    QPointF pIntersectionPoint;

    int test = line.intersect(line1,&pIntersectionPoint);

    if ( test == QLineF::BoundedIntersection )
    {
        std::cout << "Jo Dude!!!: " << test << std::endl;
    }

    std::cout << "InterPoint: " << pIntersectionPoint.x() << " , " << pIntersectionPoint.y() << std::endl;

    std::cout << "Slope: " << line.dy()/line.dx() << std::endl;
    std::cout << "Slope: " << line.dx()*p4.x() << " , " << line.dy()*p4.y() << std::endl;
    //*/
    //Highways[_highwayNumber].wayNodeList[j]
    //_ways[2].wayNodeList[0];

    //painter.drawLine(line2);

    painter.drawLine(a);
    painter.drawLine(b);
    painter.drawLine(c);
    painter.drawLine(d);
}

QPointF roadPainter::normalizePoint(QPointF _pointNorm, QPointF _point)
{
    QPointF tempPoint;

    tempPoint.setX( _pointNorm.x() - _point.x() );
    tempPoint.setY( _pointNorm.y() - _point.y() );

    return tempPoint;
}

/*::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
/*::                                                                         :*/
/*::  This routine calculates the distance between two points (given the     :*/
/*::  latitude/longitude of those points). It is being used to calculate     :*/
/*::  the distance between two locations using GeoDataSource(TM) products.   :*/
/*::                                                                         :*/
/*::  Definitions:                                                           :*/
/*::    South latitudes are negative, east longitudes are positive           :*/
/*::                                                                         :*/
/*::  Passed to function:                                                    :*/
/*::    lat1, lon1 = Latitude and Longitude of point 1 (in decimal degrees)  :*/
/*::    lat2, lon2 = Latitude and Longitude of point 2 (in decimal degrees)  :*/
/*::    unit = 'K' is kilometers (default)                                   :*/
/*::                                                                         :*/
/*::  Worldwide cities and other features databases with latitude longitude  :*/
/*::  are available at http://www.geodatasource.com                          :*/
/*::                                                                         :*/
/*::  For enquiries, please contact sales@geodatasource.com                  :*/
/*::                                                                         :*/
/*::  Official Web site: http://www.geodatasource.com                        :*/
/*::                                                                         :*/
/*::           GeoDataSource.com (C) All Rights Reserved 2014                :*/
/*::                                                                         :*/
/*::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
double roadPainter::convLatLon(double _latitude1, double _longitude1, double _latitude2, double _longitude2)
{
    double theta, dist;
    theta = _longitude1 - _longitude2;
    dist = sin(deg2rad(_latitude1)) * sin(deg2rad(_latitude2)) + cos(deg2rad(_latitude1)) * cos(deg2rad(_latitude2)) * cos(deg2rad(theta));
    dist = acos(dist);
    dist = rad2deg(dist);
    dist = dist * 60 * 1.1515 * 1.609344;
    return dist;
}

QPointF roadPainter::convLatLon(double _longitude, double _latitude)
{
    double x, y, degX, degY;
    degX = _longitude * M_PI / 180;
    degY = _latitude * M_PI / 180;
    x = ( M_PI / 180 ) * 6378137.0 * cos( atan( 0.996647189328169 * tan( degX ) ) ); // Wiki Length_of_a_degree_of_longitude
    y = 111132.954 - 559.822 * cos( 2 * degY ) + 1.175 * cos( 4 * degY );
    //Lat = Y Long = X
    QPointF tempPoint;
    tempPoint.setX( x * MAP_SCALE );
    tempPoint.setY( y * MAP_SCALE );
    return tempPoint;
}

QPointF roadPainter::Circle2CircleIntersect(double _latitude, double _longitude)
{
    double dx,dy,dist,adist,r1,r2,r3,hdist,dist1,dist2;
    QPointF temp(0,0),point1(0,0),point2(0,0),result(0,0);

    dx = a.p2().x() - a.p1().x();
    dy = a.p2().y() - a.p1().y();

    dist = sqrt((dy * dy) + (dx * dx));

    r1 = convLatLon(_latitude, _longitude, A.nodeLatitude, A.nodeLongitude)*MAP_SCALE;
    r2 = convLatLon(_latitude, _longitude, B.nodeLatitude, B.nodeLongitude)*MAP_SCALE;
    r3 = convLatLon(_latitude, _longitude, D.nodeLatitude, D.nodeLongitude)*MAP_SCALE;

    //std::cout << r1 << " , " << r2 << " , " << r3 << std::endl;

    adist = ((r1 * r1) - (r2 * r2) + (dist * dist)) / (2.0 * dist);

    temp.setX( a.p1().x() + (dx * adist / dist) );
    temp.setY( a.p1().y() + (dy * adist / dist) );

    hdist = sqrt((r1 * r1) - (adist * adist));

    result.setX( (0 - dy) * (hdist / dist) );
    result.setY( dx * (hdist / dist) );

    point1.setX( temp.x() + result.x() );
    point1.setY( temp.y() + result.y() );

    point2.setX( temp.x() - result.x() );
    point2.setY( temp.y() - result.y() );

    //std::cout << point1.x() << " , " << point1.y() << std::endl;
    //std::cout << point2.x() << " , " << point2.y() << std::endl;

    dist1 = sqrt( (point1.x() - d.p1().x()) * (point1.x() - d.p1().x()) + (point1.y() - d.p1().y()) * (point1.y() - d.p1().y()) );
    dist2 = sqrt( (point2.x() - d.p1().x()) * (point2.x() - d.p1().x()) + (point2.y() - d.p1().y()) * (point2.y() - d.p1().y()) );

    //std::cout << dist1 << std::endl;
    //std::cout << dist2 << std::endl;

    //std::cout << r3 - dist1 << std::endl;
    //std::cout << r3 - dist2 << std::endl;

    if ( ((r3 - dist1) <= 0.005) && ((r3 - dist1) >= -0.005) )
    {
        result.setX( point1.x() );
        result.setY( point1.y() );
    }
    else if ( ((r3 - dist2) <= 0.005) && ((r3 - dist2) >= -0.005) )
    {
        result.setX( point2.x() );
        result.setY( point2.y() );
    }

    return result;
}

/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
/*::  This function converts decimal degrees to radians             :*/
/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
double roadPainter::deg2rad(double _deg)
{
    return (_deg * M_PI / 180);
}

/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
/*::  This function converts radians to decimal degrees             :*/
/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
double roadPainter::rad2deg(double _rad)
{
    return (_rad * 180 / M_PI);
}

QImage roadPainter::readImage()
{
    return image;
}

QColor roadPainter::findRoadColor(double _totalRoad, double _currRoad)
{
    //double value = MAX_ROAD/_totalRoad * _currRoad;
    //double thress = (value)/(MAX_ROAD);

    double thress = (_currRoad)/(_totalRoad);

    uchar r = 0;
    uchar g = 0;
    uchar b = 0;
    int sat = 255;

    if(thress <= 0.2)
    {
        b = sat;
        g = uchar(thress/0.2 * sat);

        return QColor(r,g,b);
    }
    else if(thress < 0.399)
    {
        g = sat;
        b = uchar(sat-(thress-0.4)/0.2 * sat);

        return QColor(r,g,b);
    }
    else if(thress < 0.599)
    {
        g = sat;
        r = uchar((thress-0.6)/0.2 * sat);

        return QColor(r,g,b);
    }
    else if(thress < 0.799)
    {
        r = sat;
        g = sat - uchar((thress-0.8)/0.2 * sat);

        return QColor(r,g,b);
    }
    else if(thress < 0.999)
    {
        r = sat;
        b = uchar((thress-1)/0.2 * sat);

        return QColor(r,g,b);
    }
    else if(thress >= 1)
    {
        r = sat;
        b = sat;
        return QColor(r,g,b);

    } else return QColor(255,255,255);
}

void roadPainter::saveImage(QFile *device)
{
    image = image.mirrored();
    if (!image.save(device)) //OBS! Quality kan sættes til 100, default settings -1
        std::cout << "Cannot save map" << std::endl;
}
