#include "segment.h"

namespace BlackOil {
namespace Data {
namespace Grid {

Segment::Segment(double startPoint, double endPoint)
{
    this->startPoint = startPoint;
    this->endPoint = endPoint;
}

double Segment::StartPoint()
{
    return startPoint;
}

double Segment::EndPoint()
{
    return endPoint;
}

double Segment::Length()
{
    return endPoint - startPoint;
}

bool Segment::IsIntersect(Segment seg)
{
    double unionLen = GetUnionWith(seg).Length();

    return Length() + seg.Length() > unionLen;
}

bool Segment::IsIntersect(double x1, double x2)
{
    return IsIntersect(Segment(x1, x2));
}

Segment Segment::GetUnionWith(Segment seg)
{
    return Segment(qMin(startPoint, seg.startPoint), qMax(endPoint, seg.endPoint));
}

}}}
