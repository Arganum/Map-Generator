#include <QCoreApplication>
#include <QFile>
#include <iostream>

#include <roadXML.h>
#include <roadPainter.h>
#include <roadStructs.h>

CircleIntersect cir2cir(double x0, double y0, double r0, double x1, double y1, double r1, double x2, double y2, double r2);

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    roadXML reader;

    QFile file("D:/Dropbox/Litteratur/OSM/map.osm");

    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        std::cout << "Cannot read file" << std::endl;
        return a.exec();
    }

    if (!reader.readFirstParse(&file))
    {
        std::cout << "First Parse error in file" << std::endl;
    } else {
        std::cout << "First Parse file successfully read" << std::endl;
    }

    file.close();

    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        std::cout << "Cannot read file" << std::endl;
        return a.exec();
    }

    if (!reader.readSecondParse(&file))
    {
        std::cout << "Second Parse error in file" << std::endl;
    } else {
        std::cout << "Second Parse file successfully read" << std::endl;
    }

    std::cout << std::endl;

    reader.printWayNodeID();
    reader.deleteNodeIDLists();

    std::cout << "nodeIDLists for each Way deleted" << std::endl << std::endl;

    reader.printHighways();
    reader.printWayNode();

    roadPainter painter;

    painter.intiImage(reader.Boundary);
    painter.intiPainter();
    painter.drawLines(reader.Highways);
    painter.endPainter();

    QImage image = painter.readImage();

    QFile roadMap("D:/Dropbox/Litteratur/OSM/RoadMap.png");

    painter.saveImage(&roadMap);

    file.close();
    roadMap.close();

    std::cout << "All Files Closed" << std::endl;

    long double x, y, x1, y1, x2, y2, param1, param2, dec1, dec2, dec3, dec4;
    dec1 = 10.3649600;
    dec2 = 55.3954200;
    param1 = dec1 * M_PI / 180;
    param2 = dec2 * M_PI / 180;
    x1 = ( M_PI / 180 ) * 6378137.0 * cos( atan( 0.996647189328169 * tan( param1 ) ) ); // Wiki Length_of_a_degree_of_longitude
    y1 = 111132.954 - 559.822 * cos( 2 * param2 ) + 1.175 * cos( 4 * param2 );

    dec3 = 10.3685200;
    dec4 = 55.3967400;
    param1 = dec3 * M_PI / 180;
    param2 = dec4 * M_PI / 180;
    x2 = ( M_PI / 180 ) * 6378137.0 * cos( atan( 0.996647189328169 * tan( param1 ) ) ); // Wiki Length_of_a_degree_of_longitude
    y2 = 111132.954 - 559.822 * cos( 2 * param2 ) + 1.175 * cos( 4 * param2 );

    x = x2 - x1;
    y = y2 - y1;

    std::cout.precision(15);
    std::cout << std::endl;
    std::cout << "X is: " << x << " At: " << dec1 << " Degrees" << std::endl;
    std::cout << "Y is: " << y << " At: " << dec2 << " Degrees" << std::endl;
    /*
    double result, param;
    param = 90;
    result = atan( tan( param * M_PI / 180 ) );
    std::cout << result << std::endl;
    //*/

    CircleIntersect circle;

    circle = cir2cir(0,0,2,3,3,sqrt(8),4,-3,sqrt(15.48));

    std::cout << circle.point1.x() << " , " << circle.point1.y() << std::endl;
    std::cout << circle.point2.x() << " , " << circle.point2.y() << std::endl;

    return a.exec();
}

CircleIntersect cir2cir(double x0, double y0, double r0, double x1, double y1, double r1, double x2, double y2, double r2)
{
    double dx,dy,d,a,x3,y3,h,rx,ry;

    dx = x1 - x0;
    dy = y1 - y0;

    d = sqrt((dy*dy) + (dx*dx));


    a = ((r0*r0) - (r1*r1) + (d*d)) / (2.0 * d);

    x3 = x0 + (dx * a/d);
    y3 = y0 + (dy * a/d);

    h = sqrt((r0*r0) - (a*a));

    rx = (0-dy) * (h/d);
    ry = dx * (h/d);

    CircleIntersect result;

    result.point1.setX( x3 + rx );
    result.point1.setY( y3 + ry );
    result.point2.setX( x3 - rx );
    result.point2.setY( y3 - ry );

    double dist1 = sqrt( (result.point1.x() - x2) * (result.point1.x() - x2) + (result.point1.y() - y2) * (result.point1.y() - y2) );
    double dist2 = sqrt( (result.point2.x() - x2) * (result.point2.x() - x2) + (result.point2.y() - y2) * (result.point2.y() - y2) );

    std::cout << "Dist1: " << dist1 << " , " << r2 - dist1 << std::endl;
    std::cout << "Dist2: " << dist2 << " , " << r2 - dist2 << std::endl;

    if ( ((r2 - dist1) <= 0.0005) && ((r2 - dist1) >= -0.0005) )
    {
        std::cout << "Dist1 er point!" << std::endl;
    }
    else if ( ((r2 - dist2) <= 0.0005) && ((r2 - dist2) >= -0.0005) )
    {
        std::cout << "Dist2 er point!" << std::endl;
    }

    return result;
}
