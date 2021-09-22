#ifndef PLANE_H
#define PLANE_H

#include <point.h>

#include <data_global.h>

namespace BlackOil {
namespace Data {
namespace Grid {

class DATA_EXPORT Plane
{
public:
    Plane(double a, double b, double c, double d);
    Plane(Point &p1, Point &p2, Point &p3);

    double A();
    double B();
    double C();
    double D();

    Point GetProjectionPoint(Point& p);

    void SetA(double& a);
    void SetB(double& b);
    void SetC(double& c);
    void SetD(double& d);

protected:
    double a, b, c, d;
};

}}}

#endif // PLANE_H
