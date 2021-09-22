#ifndef SEGMENT_H
#define SEGMENT_H

#include <qglobal.h>

#include <data_global.h>

namespace BlackOil {
namespace Data {
namespace Grid {

class DATA_EXPORT Segment
{
public:
    Segment(double startPoint, double endPoint);

    double StartPoint();
    double EndPoint();

    double Length();

    bool IsIntersect(Segment seg);
    bool IsIntersect(double x1, double x2);

    Segment GetUnionWith(Segment seg);

protected:
    double startPoint, endPoint;
};

}}}

#endif // SEGMENT_H
