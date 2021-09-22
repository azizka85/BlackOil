#include "aquancondata.h"

namespace BlackOil {
namespace Data {
namespace Project {

AQUANCONData::AQUANCONData()
{
    InitVariables();
}

int AQUANCONData::Num()
{
    return num;
}

int AQUANCONData::I1()
{
    return i1;
}

int AQUANCONData::I2()
{
    return i2;
}

int AQUANCONData::J1()
{
    return j1;
}

int AQUANCONData::J2()
{
    return j2;
}

int AQUANCONData::K1()
{
    return k1;
}

int AQUANCONData::K2()
{
    return k2;
}

QVariant AQUANCONData::Side()
{
    return side;
}

QVariant AQUANCONData::InfluxCoef()
{
    return influxCoef;
}

QVariant AQUANCONData::InfluxMult()
{
    return influxMult;
}

void AQUANCONData::SetNum(const int &num)
{
    this->num = num;
}

void AQUANCONData::SetI1(const int &i1)
{
    this->i1 = i1;
}

void AQUANCONData::SetI2(const int &i2)
{
    this->i2 = i2;
}

void AQUANCONData::SetJ1(const int &j1)
{
    this->j1 = j1;
}

void AQUANCONData::SetJ2(const int &j2)
{
    this->j2 = j2;
}

void AQUANCONData::SetK1(const int &k1)
{
    this->k1 = k1;
}

void AQUANCONData::SetK2(const int &k2)
{
    this->k2 = k2;
}

void AQUANCONData::SetSide(const QVariant &side)
{
    this->side = side;
}

void AQUANCONData::SetInfluxCoef(const QVariant &influxCoef)
{
    this->influxCoef = influxCoef;
}

void AQUANCONData::SetInfluxMult(const QVariant &influxMult)
{
    this->influxMult = influxMult;
}

void AQUANCONData::InitVariables()
{
    num = i1 = i2 = j1 = j2 = k1 = k2 = -1;

    side.clear();
    influxCoef.clear();
    influxMult.clear();
}

}}}
