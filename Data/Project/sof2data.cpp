#include "sof2data.h"

namespace BlackOil {
namespace Data {
namespace Project {

SOF2Data::SOF2Data()
{
    InitVariables();
}

double SOF2Data::SO()
{
    return so;
}

double SOF2Data::KrO()
{
    return kro;
}

void SOF2Data::SetSO(const double &so)
{
    this->so = so;
}

void SOF2Data::SetKrO(const double &kro)
{
    this->kro = kro;
}

void SOF2Data::InitVariables()
{
    so = 0;
    kro = 0;
}

}}}
