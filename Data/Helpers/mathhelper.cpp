#include "mathhelper.h"

namespace BlackOil {
namespace Data {
namespace Helpers {

Point MathHelper::IntersectNotStrong(Line &line1, Line &line2)
{
    Point p = Plane(line1.P1(), line1.P2(), line2.P1()).GetProjectionPoint(line2.P2());

    Point res;
    Line line(line2.P1(), p);

    bool val = Intersect(line1, line, res);

    if(!val) res = line2.P2();

    return res;
}

bool MathHelper::Intersect(Line &line1, Line &line2, Point &p)
{
    double m1 = line1.P1().X() - line1.P2().X();
    double n1 = line1.P1().Y() - line1.P2().Y();
    double p1 = line1.P1().Z() - line1.P2().Z();

    double m2 = line2.P1().X() - line2.P2().X();
    double n2 = line2.P1().Y() - line2.P2().Y();
    double p2 = line2.P1().Z() - line2.P2().Z();

    bool anyX = false;
    bool anyY = false;
    bool anyZ = false;

    double tx = 0;
    double ty = 0;
    double tz = 0;

    if (ISEQUAL(m2 - m1, 0))
    {
        if (ISEQUAL(line1.P1().X() - line2.P1().X(), 0)) anyX = true;
        else return false;
    }
    else tx = (line1.P1().X() - line2.P1().X()) / (m2 - m1);

    if (ISEQUAL(n2 - n1, 0))
    {
        if (ISEQUAL(line1.P1().Y() - line2.P1().Y(), 0)) anyY = true;
        else return false;
    }
    else ty = (line1.P1().Y() - line2.P1().Y()) / (n2 - n1);

    if (ISEQUAL(p2 - p1, 0))
    {
        if (ISEQUAL(line1.P1().Z() - line2.P1().Z(), 0)) anyZ = true;
        else return false;
    }
    else tz = (line1.P1().Z() - line2.P1().Z()) / (p2 - p1);

    double t = -1;
    if (!anyX) t = tx;
    else if (!anyY) t = ty;
    else if (!anyZ) t = tz;
    else return false;

    if ((!anyX && !ISEQUAL(t - tx, 0)) || (!anyY && !ISEQUAL(t - ty, 0)) || (!anyZ && !ISEQUAL(t - tz, 0))) return false;

    p.SetX(line1.P1().X() + m1 * t);
    p.SetY(line1.P1().Y() + n1 * t);
    p.SetZ(line1.P1().Z() + p1 * t);

    return true;
}

void MathHelper::IntersectZPlane(Line &line, double &z, Point &point)
{
    double t = (z - line.P1().Z()) / (line.P2().Z() - line.P1().Z());

    double x = line.P1().X() + (line.P2().X() - line.P1().X()) * t;
    double y = line.P1().Y() + (line.P2().Y() - line.P1().Y()) * t;

    point.SetX(x);
    point.SetY(y);
    point.SetZ(z);
}

double MathHelper::ParallelepipedVolume(Point &v1, Point &v2, Point &v3)
{
    return qAbs(v1.X() * v2.Y() * v3.Z() + v2.X() * v3.Y() * v1.Z() + v1.Y() * v2.Z() * v3.X() - v1.Z() * v2.Y() * v3.X() - v3.Y() * v2.Z() * v1.X() - v1.Y() * v2.X() * v3.Z());
}

Point MathHelper::GetAveragePoint(QVector<Point> &p)
{
    int count = p.size();

    double cx = 0, cy = 0, cz = 0;

    for (int i = 0; i < p.size(); i++)
    {
        cx += p[i].X();
        cy += p[i].Y();
        cz += p[i].Z();
    }

    return Point(cx / count, cy / count, cz / count);
}

Point MathHelper::GetMassCenter(Point &p1, Point &p2, Point &p3, Point &p4, Point &p5, Point &p6, Point &p7, Point &p8)
{
    return Point((p1.X() + p2.X() + p3.X() + p4.X() + p5.X() + p6.X() + p7.X() + p8.X())/8,
                   (p1.Y() + p2.Y() + p3.Y() + p4.Y() + p5.Y() + p6.Y() + p7.Y() + p8.Y())/8,
                 (p1.Z() + p2.Z() + p3.Z() + p4.Z() + p5.Z() + p6.Z() + p7.Z() + p8.Z())/8);
}

double MathHelper::Volume(Block &block)
{
    Point v1, v2, v3;
    double ans = 0.0;

    Point &p1 = block.P1();
    Point &p2 = block.P2();
    Point &p3 = block.P3();
    Point &p4 = block.P4();
    Point &p5 = block.P5();
    Point &p6 = block.P6();
    Point &p7 = block.P7();
    Point &p8 = block.P8();

    v1 = Point::Subtract(p5, p7);
    v2 = Point::Subtract(p8, p7);
    v3 = Point::Subtract(p3, p7);
    ans += MathHelper::ParallelepipedVolume(v1, v2, v3);


    v1 = Point::Subtract(p8, p6);
    v2 = Point::Subtract(p5, p6);
    v3 = Point::Subtract(p2, p6);
    ans += MathHelper::ParallelepipedVolume(v1, v2, v3);


    v1 = Point::Subtract(p3, p5);
    v2 = Point::Subtract(p8, p5);
    v3 = Point::Subtract(p1, p5);
    ans += MathHelper::ParallelepipedVolume(v1, v2, v3);


    v1 = Point::Subtract(p2, p5);
    v2 = Point::Subtract(p8, p5);
    v3 = Point::Subtract(p1, p5);
    ans += MathHelper::ParallelepipedVolume(v1, v2, v3);


    v1 = Point::Subtract(p2, p1);
    v2 = Point::Subtract(p4, p1);
    v3 = Point::Subtract(p8, p1);
    ans += MathHelper::ParallelepipedVolume(v1, v2, v3);

    v1 = Point::Subtract(p4, p1);
    v2 = Point::Subtract(p3, p1);
    v3 = Point::Subtract(p8, p1);
    ans += MathHelper::ParallelepipedVolume(v1, v2, v3);

    return ans / 6.0;
}

Plane MathHelper::PlaneYZ()
{
    Point p1(0, 0, 0);
    Point p2(0, 10, 0);
    Point p3(0, 0, 10);

    return Plane(p1, p2, p3);
}

Plane MathHelper::PlaneXZ()
{
    Point p1(10, 0, 0);
    Point p2(0, 0, 0);
    Point p3(0, 0, 10);

    return Plane(p1, p2, p3);
}

Plane MathHelper::PlaneXY()
{
    Point p1(10, 0, 0);
    Point p2(0, 10, 0);
    Point p3(0, 0, 0);

    return Plane(p1, p2, p3);
}

double MathHelper::CosBetweenPlanes(Plane &plane1, Plane &plane2)
{
    return qAbs(plane1.A() * plane2.A() + plane1.B() * plane2.B() + plane1.C() * plane2.C()) /
          (qSqrt(plane1.A() * plane1.A() + plane1.B() * plane1.B() + plane1.C() * plane1.C()) *
           qSqrt(plane2.A() * plane2.A() + plane2.B() * plane2.B() + plane2.C() * plane2.C()));
}

double MathHelper::GetTriangleArea(Point &p0, Point &p1, Point &p2)
{
    Point v1 = Point::Subtract(p1, p0);
    Point v2 = Point::Subtract(p1, p2);

    return Point::AbsCrossProduct(v1, v2) / 2.0;
}

double MathHelper::GetTetragonArea(Point &p0, Point &p1, Point &p2, Point &p3)
{
    return GetTriangleArea(p0, p1, p2) + GetTriangleArea(p2, p3, p0);
}

double MathHelper::GetPentagonArea(Point &p0, Point &p1, Point &p2, Point &p3, Point &p4)
{
    return GetTetragonArea(p0, p1, p2, p3) + GetTriangleArea(p3, p4, p0);
}

double MathHelper::GetHexagonArea(Point &p0, Point &p1, Point &p2, Point &p3, Point &p4, Point &p5)
{
    return GetPentagonArea(p0, p1, p2, p3, p4) + GetTriangleArea(p4, p5, p0);
}

double MathHelper::GetContactArea(Point &a1Up, Point &a1Down, Point &b1Up, Point &b1Down, Point &a2Up, Point &a2Down, Point &b2Up, Point &b2Down, Point &contactAreaCenter)
{
    QVector<Point> points;

    Line line1Up(a1Up, b1Up);
    Line line1Down(a1Down, b1Down);
    Line line2Up(a2Up, b2Up);
    Line line2Down(a2Down, b2Down);

    if (a1Up.Z() > a2Up.Z())
    {
        if (a1Down.Z() > a2Up.Z()) { }

        if (a1Down.Z() <= a2Up.Z() && a1Down.Z() > a2Down.Z())
        {
            points.append(a1Down);
            points.append(a2Up);
        }

        if (a1Down.Z() <= a2Down.Z())
        {
            points.append(a2Down);
            points.append(a2Up);
        }
    }
    if (a1Up.Z() <= a2Up.Z() && a1Up.Z() >= a2Down.Z())
    {
        if (a1Down.Z() > a2Down.Z())
        {
            points.append(a1Down);
            points.append(a1Up);
        }
        if (a1Down.Z() <= a2Down.Z())
        {
            points.append(a2Down);
            points.append(a1Up);
        }
    }
    if (a1Up.Z() > a2Down.Z()) { }

    if (a1Down.Z() > a2Up.Z() && b1Down.Z() < b2Up.Z()) points.append(MathHelper::IntersectNotStrong(line1Down, line2Up));
    if (a1Up.Z() > a2Up.Z() && b1Up.Z() < b2Up.Z()) points.append(MathHelper::IntersectNotStrong(line1Up, line2Up));

    if (a1Up.Z() < a2Up.Z() && b1Up.Z() > b2Up.Z()) points.append(MathHelper::IntersectNotStrong(line1Up, line2Up));
    if (a1Down.Z() < a2Up.Z() && b1Down.Z() > b2Up.Z()) points.append(MathHelper::IntersectNotStrong(line1Down, line2Up));

    if (b1Up.Z() > b2Up.Z())
    {
        if (b1Down.Z() > b2Up.Z()) { }

        if (b1Down.Z() <= b2Up.Z() && b1Down.Z() > b2Down.Z())
        {
            points.append(b2Up);
            points.append(b1Down);
        }

        if (b1Down.Z() <= b2Down.Z())
        {
            points.append(b2Up);
            points.append(b2Down);
        }
    }
    if (b1Up.Z() <= b2Up.Z() && b1Up.Z() >= b2Down.Z())
    {
        if (b1Down.Z() > b2Down.Z())
        {
            points.append(b1Up);
            points.append(b1Down);
        }
        if (b1Down.Z() <= b2Down.Z())
        {
            points.append(b1Up);
            points.append(b2Down);
        }
    }
    if (b1Up.Z() > b2Down.Z()) { }

    if (a1Down.Z() < a2Down.Z() && b1Down.Z() > b2Down.Z()) points.append(MathHelper::IntersectNotStrong(line1Down, line2Down));
    if (a1Up.Z() < a2Down.Z() && b1Up.Z() > b2Down.Z()) points.append(MathHelper::IntersectNotStrong(line1Up, line2Down));

    if (a1Up.Z() > a2Down.Z() && b1Up.Z() < b2Down.Z()) points.append(MathHelper::IntersectNotStrong(line1Up, line2Down));
    if (a1Down.Z() > a2Down.Z() && b1Down.Z() < b2Down.Z()) points.append(MathHelper::IntersectNotStrong(line1Down, line2Down));


    contactAreaCenter = MathHelper::GetAveragePoint(points);

    if (points.size() < 3) return 0;

    if (points.size() == 3) return MathHelper::GetTriangleArea(points[0], points[1], points[2]);
    if (points.size() == 4) return MathHelper::GetTetragonArea(points[0], points[1], points[2], points[3]);
    if (points.size() == 5) return MathHelper::GetPentagonArea(points[0], points[1], points[2], points[3], points[4]);
    if (points.size() == 6) return MathHelper::GetHexagonArea(points[0], points[1], points[2], points[3], points[4], points[5]);

    if (points.size() > 6) return 0;

    return 0;
}

bool MathHelper::IsIntersectedSurfaces(Segment lside1, Segment rside1, Segment lside2, Segment rside2)
{
    if (lside1.IsIntersect(lside2) || rside1.IsIntersect(rside2)) return true;

    if (lside1.EndPoint() <= lside2.StartPoint() && rside1.StartPoint() >= rside2.EndPoint()) return true;

    if (lside1.StartPoint() >= lside2.EndPoint() && rside1.EndPoint() <= rside2.StartPoint()) return true;

    if (lside2.EndPoint() <= lside1.StartPoint() && rside2.StartPoint() >= rside1.EndPoint()) return true;

    if (lside2.StartPoint() >= lside1.EndPoint() && rside2.EndPoint() <= rside1.StartPoint()) return true;

    return false;
}

}}}
