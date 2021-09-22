#include "aqufetpdata.h"

namespace BlackOil {
namespace Data {
namespace Project {

AQUFETPData::AQUFETPData()
{
    InitVariables();
}

int AQUFETPData::Num()
{
    return num;
}

double AQUFETPData::DatumDepth()
{
    return datumDepth;
}

QVariant AQUFETPData::DatumP()
{
    return datumP;
}

double AQUFETPData::VW()
{
    return vw;
}

double AQUFETPData::C()
{
    return c;
}

double AQUFETPData::ProdIndex()
{
    return prodIndex;
}

int AQUFETPData::PVTWNum()
{
    return pvtwNum;
}

QVariant AQUFETPData::SALT()
{
    return salt;
}

void AQUFETPData::SetNum(const int &num)
{
    this->num = num;
}

void AQUFETPData::SetDatumDepth(const double &datumDepth)
{
    this->datumDepth = datumDepth;
}

void AQUFETPData::SetDatumP(const QVariant &datumP)
{
    this->datumP = datumP;
}

void AQUFETPData::SetVW(const double &vw)
{
    this->vw = vw;
}

void AQUFETPData::SetC(const double &c)
{
    this->c = c;
}

void AQUFETPData::SetProdIndex(const double &prodIndex)
{
    this->prodIndex = prodIndex;
}

void AQUFETPData::SetPVTWNum(const int &pvtwNum)
{
    this->pvtwNum = pvtwNum;
}

void AQUFETPData::SetSALT(const QVariant &salt)
{
    this->salt = salt;
}

void AQUFETPData::InitVariables()
{
    num = pvtwNum = -1;
    datumDepth = vw = c = prodIndex = 0;

    datumP.clear();
    salt.clear();
}

}}}
