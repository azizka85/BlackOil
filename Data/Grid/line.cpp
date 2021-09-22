#include "line.h"

namespace BlackOil {
namespace Data {
namespace Grid {

Line::Line()
{
    InitVariables();
}

Line::Line(const Point &p1, const Point &p2)
{
    this->p1 = p1;
    this->p2 = p2;
}

Point &Line::P1()
{
    return p1;
}

Point &Line::P2()
{
    return p2;
}

void Line::SetP1(const Point &p1)
{
    this->p1 = p1;
}

void Line::SetP2(const Point &p2)
{
    this->p2 = p2;
}

void Line::InitVariables()
{
    p1.InitVariables();
    p2.InitVariables();
}


}}}
