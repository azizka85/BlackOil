#include "slgofdata.h"

namespace BlackOil {
namespace Data {
namespace Project {

SLGOFData::SLGOFData()
{
    InitVariables();
}

double SLGOFData::SL()
{
    return sl;
}

QVariant SLGOFData::KrG()
{
    return krg;
}

QVariant SLGOFData::KrO()
{
    return kro;
}

QVariant SLGOFData::Pc()
{
    return pc;
}

void SLGOFData::SetSL(const double &sl)
{
    this->sl = sl;
}

void SLGOFData::SetKrG(const QVariant &krg)
{
    this->krg = krg;
}

void SLGOFData::SetKrO(const QVariant &kro)
{
    this->kro = kro;
}

void SLGOFData::SetPc(const QVariant &pc)
{
    this->pc = pc;
}

void SLGOFData::InitVariables()
{
    sl = 0;

    krg.clear();
    kro.clear();
    pc.clear();
}

}}}
