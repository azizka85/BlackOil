#ifndef BLOCK_H
#define BLOCK_H

#include <point.h>

#include <data_global.h>

namespace BlackOil {
namespace Data {
namespace Grid {

class DATA_EXPORT Block
{
public:
    Block();
    Block(int i, int j, int k, const Point& p1, const Point& p2, const Point& p3,
          const Point& p4, const Point& p5, const Point& p6, const Point& p7, const Point& p8);

    int I();
    int J();
    int K();

    Point& P1();
    Point& P2();
    Point& P3();
    Point& P4();
    Point& P5();
    Point& P6();
    Point& P7();
    Point& P8();

    double Volume();
    double Depth();

    double DX();
    double DY();
    double DZ();

    void SetI(const int& i);
    void SetJ(const int& j);
    void SetK(const int& k);

    void SetP1(const Point& p1);
    void SetP2(const Point& p2);
    void SetP3(const Point& p3);
    void SetP4(const Point& p4);
    void SetP5(const Point& p5);
    void SetP6(const Point& p6);
    void SetP7(const Point& p7);
    void SetP8(const Point& p8);

    void InitVariables();

protected:
    int i, j, k;
    Point p1;
    Point p2;
    Point p3;
    Point p4;
    Point p5;
    Point p6;
    Point p7;
    Point p8;
};

}}}

#endif // BLOCK_H
