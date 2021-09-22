#include "specheatdata.h"

namespace BlackOil {
namespace Data {
namespace Project {

SPECHEATData::SPECHEATData()
{
    InitVariables();
}

double SPECHEATData::T()
{
    return t;
}

double SPECHEATData::CO()
{
    return co;
}

double SPECHEATData::CW()
{
    return cw;
}

double SPECHEATData::CG()
{
    return cg;
}

void SPECHEATData::SetT(const double &t)
{
    this->t = t;
}

void SPECHEATData::SetCO(const double &co)
{
    this->co = co;
}

void SPECHEATData::SetCW(const double &cw)
{
    this->cw = cw;
}

void SPECHEATData::SetCG(const double &cg)
{
    this->cg = cg;
}

void SPECHEATData::InitVariables()
{
    t = 0;
    co = 0;
    cw = 0;
    cg = 0;
}

}}}
