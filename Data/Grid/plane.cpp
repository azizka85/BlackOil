#include "plane.h"

namespace BlackOil {
namespace Data {
namespace Grid {

Plane::Plane(double a, double b, double c, double d)
{
    this->a = a;
    this->b = b;
    this->c = c;
    this->d = d;
}

Plane::Plane(Point &p1, Point &p2, Point &p3)
{
    Point v1 = Point::Subtract(p1, p2);
    Point v2 = Point::Subtract(p3, p2);

    Point planeNormal = Point::CrossProduct(v1, v2);

    a = planeNormal.X();
    b = planeNormal.Y();
    c = planeNormal.Z();

    d = -a * p1.X() - b * p1.Y() - c * p1.Z();
}

double Plane::A()
{
    return a;
}

double Plane::B()
{
    return b;
}

double Plane::C()
{
    return c;
}

double Plane::D()
{
    return d;
}

Point Plane::GetProjectionPoint(Point &p)
{
    double t = -(a * p.X() + b * p.Y() + c * p.Z() + d) / (a * a + b * b + c * c);

    double x = p.X() + t * a;
    double y = p.Y() + t * b;
    double z = p.Z() + t * c;

    return Point(x, y, z);
}

void Plane::SetA(double &a)
{
    this->a = a;
}

void Plane::SetB(double &b)
{
    this->b = b;
}

void Plane::SetC(double &c)
{
    this->c = c;
}

void Plane::SetD(double &d)
{
    this->d = d;
}

}}}
