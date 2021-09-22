#include "somwatdata.h"

namespace BlackOil {
namespace Data {
namespace Project {

SOMWATData::SOMWATData()
{
    InitVariables();
}

double SOMWATData::SW()
{
    return sw;
}

double SOMWATData::SOMin()
{
    return soMin;
}

void SOMWATData::SetSW(const double &sw)
{
    this->sw = sw;
}

void SOMWATData::SetSOMin(const double &soMin)
{
    this->soMin = soMin;
}

void SOMWATData::InitVariables()
{
    sw = 0;
    soMin = 0;
}

}}}
