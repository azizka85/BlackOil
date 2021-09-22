#include "densitydata.h"

namespace BlackOil {
namespace Data {
namespace Project {

DENSITYData::DENSITYData()
{
    InitVariables();
}

QVariant DENSITYData::RO()
{
    return ro;
}

QVariant DENSITYData::RW()
{
    return rw;
}

QVariant DENSITYData::RG()
{
    return rg;
}

void DENSITYData::SetRO(const QVariant &ro)
{
    this->ro = ro;
}

void DENSITYData::SetRW(const QVariant &rw)
{
    this->rw = rw;
}

void DENSITYData::SetRG(const QVariant &rg)
{
    this->rg = rg;
}

void DENSITYData::InitVariables()
{
    ro.clear();
    rw.clear();
    rg.clear();
}

}}}
