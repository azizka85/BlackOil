#ifndef AQUANCONDATA_H
#define AQUANCONDATA_H

#include <qvariant.h>

#include <data_global.h>

namespace BlackOil {
namespace Data {
namespace Project {

class DATA_EXPORT AQUANCONData
{
public:
    AQUANCONData();

    int Num();
    int I1();
    int I2();
    int J1();
    int J2();
    int K1();
    int K2();
    QVariant Side();
    QVariant InfluxCoef();
    QVariant InfluxMult();

    void SetNum(const int& num);
    void SetI1(const int& i1);
    void SetI2(const int& i2);
    void SetJ1(const int& j1);
    void SetJ2(const int& j2);
    void SetK1(const int& k1);
    void SetK2(const int& k2);
    void SetSide(const QVariant& side);
    void SetInfluxCoef(const QVariant& influxCoef);
    void SetInfluxMult(const QVariant& influxMult);

    void InitVariables();

protected:
    int num, i1, i2, j1, j2, k1, k2;
    QVariant side, influxCoef, influxMult;
};

}}}

#endif // AQUANCONDATA_H
