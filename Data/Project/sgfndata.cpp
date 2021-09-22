#include "sgfndata.h"

namespace BlackOil {
namespace Data {
namespace Project {

SGFNData::SGFNData()
{
    InitVariables();
}

double SGFNData::SG()
{
    return sg;
}

QVariant SGFNData::KrG()
{
    return krg;
}

QVariant SGFNData::Pc()
{
    return pc;
}

void SGFNData::SetSG(const double &sg)
{
    this->sg = sg;
}

void SGFNData::SetKrG(const QVariant &krg)
{
    this->krg = krg;
}

void SGFNData::SetPc(const QVariant &pc)
{
    this->pc = pc;
}

void SGFNData::InitVariables()
{
    sg = 0;

    krg.clear();
    pc.clear();
}

}}}
