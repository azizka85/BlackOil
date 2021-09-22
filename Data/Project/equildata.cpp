#include "equildata.h"

namespace BlackOil {
namespace Data {
namespace Project {

EQUILData::EQUILData()
{
    InitVariables();
}

double EQUILData::DatumDepth()
{
    return datumDepth;
}

double EQUILData::DatumP()
{
    return datumP;
}

QVariant EQUILData::WOCDepth()
{
    return wocDepth;
}

QVariant EQUILData::WOCPc()
{
    return wocPc;
}

QVariant EQUILData::GOCDepth()
{
    return gocDepth;
}

QVariant EQUILData::GOCPc()
{
    return gocPc;
}

void EQUILData::SetDatumDepth(const double &datumDepth)
{
    this->datumDepth = datumDepth;
}

void EQUILData::SetDatumP(const double &datumP)
{
    this->datumP = datumP;
}

void EQUILData::SetWOCDepth(const QVariant &wocDepth)
{
    this->wocDepth = wocDepth;
}

void EQUILData::SetWOCPc(const QVariant &wocPc)
{
    this->wocPc = wocPc;
}

void EQUILData::SetGOCDepth(const QVariant &gocDepth)
{
    this->gocDepth = gocDepth;
}

void EQUILData::SetGOCPc(const QVariant &gocPc)
{
    this->gocPc = gocPc;
}

void EQUILData::InitVariables()
{
    datumDepth = 0;
    datumP = 0;

    wocDepth.clear();
    wocPc.clear();
    gocDepth.clear();
    gocPc.clear();
}

}}}
