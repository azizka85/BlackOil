#ifndef MATHHELPER_H
#define MATHHELPER_H

#include <qmath.h>

#include <qvector.h>

#include <block.h>
#include <point.h>
#include <line.h>
#include <plane.h>
#include <segment.h>

#include <data_global.h>

#define EPSILON 1E-15

#define ISEQUAL(val1, val2) ((val1 - val2 < EPSILON) && (val1 - val2 > -EPSILON))

using namespace BlackOil::Data::Grid;

namespace BlackOil {
namespace Data {
namespace Helpers {

class DATA_EXPORT MathHelper
{
public:
    static Point IntersectNotStrong(Line &line1, Line &line2);
    static bool Intersect(Line &line1, Line &line2, Point& p);
    static void IntersectZPlane(Line& line, double& z, Point& point);
    static double ParallelepipedVolume(Point& v1, Point& v2, Point& v3);

    static Point GetAveragePoint(QVector<Point> &p);
    static Point GetMassCenter(Point &p1, Point &p2, Point &p3, Point &p4, Point &p5, Point &p6, Point &p7, Point &p8);

    static double Volume(Block &block);

    static Plane PlaneYZ();
    static Plane PlaneXZ();
    static Plane PlaneXY();
    static double CosBetweenPlanes(Plane &plane1, Plane &plane2);

    static double GetTriangleArea(Point &p0, Point &p1, Point &p2);
    static double GetTetragonArea(Point &p0, Point &p1, Point &p2, Point &p3);
    static double GetPentagonArea(Point &p0, Point &p1, Point &p2, Point &p3, Point &p4);
    static double GetHexagonArea(Point &p0, Point &p1, Point &p2, Point &p3, Point &p4, Point &p5);
    static double GetContactArea(Point &a1Up, Point &a1Down, Point &b1Up, Point &b1Down, Point &a2Up, Point &a2Down, Point &b2Up, Point &b2Down, Point &contactAreaCenter);

    static bool IsIntersectedSurfaces(Segment lside1, Segment rside1, Segment lside2, Segment rside2);
};

}}}

#endif // MATHHELPER_H
