#include "sgofdata.h"

namespace BlackOil {
namespace Data {
namespace Project {

SGOFData::SGOFData()
{
    InitVariables();
}

double SGOFData::SG()
{
    return sg;
}

QVariant SGOFData::KrG()
{
    return krg;
}

QVariant SGOFData::KrO()
{
    return kro;
}

QVariant SGOFData::Pc()
{
    return pc;
}

void SGOFData::SetSG(const double &sg)
{
    this->sg = sg;
}

void SGOFData::SetKrG(const QVariant &krg)
{
    this->krg = krg;
}

void SGOFData::SetKrO(const QVariant &kro)
{
    this->kro = kro;
}

void SGOFData::SetPc(const QVariant &pc)
{
    this->pc = pc;
}

void SGOFData::InitVariables()
{
    sg = 0;

    krg.clear();
    kro.clear();
    pc.clear();
}

}}}
