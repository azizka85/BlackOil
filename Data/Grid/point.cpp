#include "point.h"

namespace BlackOil {
namespace Data {
namespace Grid {

Point::Point()
{
    InitVariables();
}

Point::Point(double x, double y, double z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

double Point::X()
{
    return x;
}

double Point::Y()
{
    return y;
}

double Point::Z()
{
    return z;
}

Point Point::Subtract(Point &v1, Point &v2)
{
    return Point(v1.X() - v2.X(), v1.Y() - v2.Y(), v1.Z() - v2.Z());
}

double Point::AbsCrossProduct(Point &v1, Point &v2)
{
    double a = SQR(v1.Z() * v2.Y() - v1.Y() * v2.Z());
    double b = SQR(v1.X() * v2.Z() - v1.Z() * v2.X());
    double c = SQR(v1.Y() * v2.X() - v1.X() * v2.Y());

    return qSqrt(a + b + c);
}

Point Point::CrossProduct(Point &a, Point &b)
{
    double x = a.Y() * b.Z() - a.Z() * b.Y();
    double y = a.Z() * b.X() - a.X() * b.Z();
    double z = a.X() * b.Y() - a.Y() * b.X();

    return Point(x, y, z);
}

void Point::SetX(const double &x)
{
    this->x = x;
}

void Point::SetY(const double &y)
{
    this->y = y;
}

void Point::SetZ(const double &z)
{
    this->z = z;
}

void Point::InitVariables()
{
    x = y = z = 0;
}

}}}
