#include "block.h"

namespace BlackOil {
namespace Data {
namespace Grid {

Block::Block()
{
    InitVariables();
}

Block::Block(int i, int j, int k, const Point &p1, const Point &p2, const Point &p3, const Point &p4, const Point &p5, const Point &p6, const Point &p7, const Point &p8)
{
    this->i = i;
    this->j = j;
    this->k = k;

    this->p1 = p1;
    this->p2 = p2;
    this->p3 = p3;
    this->p4 = p4;
    this->p5 = p5;
    this->p6 = p6;
    this->p7 = p7;
    this->p8 = p8;
}

int Block::I()
{
    return i;
}

int Block::J()
{
    return j;
}

int Block::K()
{
    return k;
}

Point &Block::P1()
{
    return p1;
}

Point &Block::P2()
{
    return p2;
}

Point &Block::P3()
{
    return p3;
}

Point &Block::P4()
{
    return p4;
}

Point &Block::P5()
{
    return p5;
}

Point &Block::P6()
{
    return p6;
}

Point &Block::P7()
{
    return p7;
}

Point &Block::P8()
{
    return p8;
}

double Block::Depth()
{
    return (P1().Z() + P2().Z() + P3().Z() + P4().Z() +
            P5().Z() + P6().Z() + P7().Z() + P8().Z()) / 8;
}

double Block::DX()
{
    return ((p2.X() - p1.X()) +
             (p4.X() - p3.X()) +
             (p6.X() - p5.X()) +
            (p8.X() - p7.X())) / 4.0;
}

double Block::DY()
{
    return ((p3.Y() - p1.Y()) +
             (p4.Y() - p2.Y()) +
             (p7.Y() - p5.Y()) +
            (p8.Y() - p6.Y())) / 4.0;
}

double Block::DZ()
{
    return ((p5.Z() - p1.Z()) +
             (p6.Z() - p2.Z()) +
             (p7.Z() - p3.Z()) +
            (p8.Z() - p4.Z())) / 4.0;
}

void Block::SetI(const int &i)
{
    this->i = i;
}

void Block::SetJ(const int &j)
{
    this->j = j;
}

void Block::SetK(const int &k)
{
    this->k = k;
}

void Block::SetP1(const Point &p1)
{
    this->p1 = p1;
}

void Block::SetP2(const Point &p2)
{
    this->p2 = p2;
}

void Block::SetP3(const Point &p3)
{
    this->p3 = p3;
}

void Block::SetP4(const Point &p4)
{
    this->p4 = p4;
}

void Block::SetP5(const Point &p5)
{
    this->p5 = p5;
}

void Block::SetP6(const Point &p6)
{
    this->p6 = p6;
}

void Block::SetP7(const Point &p7)
{
    this->p7 = p7;
}

void Block::SetP8(const Point &p8)
{
    this->p8 = p8;
}

void Block::InitVariables()
{
    i = -1;
    j = -1;
    k = -1;

    p1.InitVariables();
    p2.InitVariables();
    p3.InitVariables();
    p4.InitVariables();
    p5.InitVariables();
    p6.InitVariables();
    p7.InitVariables();
    p8.InitVariables();
}

}}}
