#include "eqldimsdata.h"

namespace BlackOil {
namespace Data {
namespace Project {

EQLDIMSData::EQLDIMSData()
{
    InitVariables();
}

QVariant EQLDIMSData::NTEQUL() const
{
    return ntEQUL;
}

void EQLDIMSData::SetNTEQUL(const QVariant &ntEQUL)
{
    this->ntEQUL = ntEQUL;
}

void EQLDIMSData::InitVariables()
{
    ntEQUL.clear();
}

}}}
