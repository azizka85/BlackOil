#ifndef LINE_H
#define LINE_H

#include <point.h>

#include <data_global.h>

namespace BlackOil {
namespace Data {
namespace Grid {

class DATA_EXPORT Line
{
public:
    Line();
    Line(const Point& p1, const Point& p2);

    Point& P1();
    Point& P2();

    void SetP1(const Point& p1);
    void SetP2(const Point& p2);

    void InitVariables();

protected:
    Point p1, p2;
};

}}}

#endif // LINE_H
