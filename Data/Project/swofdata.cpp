#include "swofdata.h"

namespace BlackOil {
namespace Data {
namespace Project {

SWOFData::SWOFData()
{
    InitVariables();
}

double SWOFData::SW()
{
    return sw;
}

QVariant SWOFData::KrW()
{
    return krw;
}

QVariant SWOFData::KrO()
{
    return kro;
}

QVariant SWOFData::Pc()
{
    return pc;
}

void SWOFData::SetSW(const double &sw)
{
    this->sw = sw;
}

void SWOFData::SetKrW(const QVariant &krw)
{
    this->krw = krw;
}

void SWOFData::SetKrO(const QVariant &kro)
{
    this->kro = kro;
}

void SWOFData::SetPc(const QVariant &pc)
{
    this->pc = pc;
}

void SWOFData::InitVariables()
{
    sw = 0;

    krw.clear();
    kro.clear();
    pc.clear();
}

}}}
