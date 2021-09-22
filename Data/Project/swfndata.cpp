#include "swfndata.h"

namespace BlackOil {
namespace Data {
namespace Project {

SWFNData::SWFNData()
{
    InitVariables();
}

double SWFNData::SW()
{
    return sw;
}

QVariant SWFNData::KrW()
{
    return krw;
}

QVariant SWFNData::Pc()
{
    return pc;
}

void SWFNData::SetSW(const double &sw)
{
    this->sw = sw;
}

void SWFNData::SetKrW(const QVariant &krw)
{
    this->krw = krw;
}

void SWFNData::SetPc(const QVariant &pc)
{
    this->pc = pc;
}

void SWFNData::InitVariables()
{
    sw = 0;

    krw.clear();
    pc.clear();
}

}}}
