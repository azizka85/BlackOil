#include "sgwfndata.h"

namespace BlackOil {
namespace Data {
namespace Project {

SGWFNData::SGWFNData()
{
    InitVariables();
}

double SGWFNData::SG()
{
    return sg;
}

QVariant SGWFNData::KrG()
{
    return krg;
}

QVariant SGWFNData::KrW()
{
    return krw;
}

QVariant SGWFNData::Pc()
{
    return pc;
}

void SGWFNData::SetSG(const double &sg)
{
    this->sg = sg;
}

void SGWFNData::SetKrG(const QVariant &krg)
{
    this->krg = krg;
}

void SGWFNData::SetKrW(const QVariant &krw)
{
    this->krw = krw;
}

void SGWFNData::SetPc(const QVariant &pc)
{
    this->pc = pc;
}

void SGWFNData::InitVariables()
{
    sg = 0;

    krg.clear();
    krw.clear();
    pc.clear();
}

}}}
