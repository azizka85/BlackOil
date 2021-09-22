#ifndef POINT_H
#define POINT_H

#include <qmath.h>

#include <data_global.h>

#define SQR(a) ((a)*(a))

namespace BlackOil {
namespace Data {
namespace Grid {

class DATA_EXPORT Point
{
public:
    Point();
    Point(double x, double y, double z);

    double X();
    double Y();
    double Z();

    static Point Subtract(Point& v1, Point& v2);
    static double AbsCrossProduct(Point &v1, Point &v2);
    static Point CrossProduct(Point &a, Point &b);

    void SetX(const double& x);
    void SetY(const double& y);
    void SetZ(const double& z);

    void InitVariables();

protected:
    double x, y, z;
};

}}}

#endif // POINT_H
