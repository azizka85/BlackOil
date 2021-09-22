#include "sof32dkrodata.h"

namespace BlackOil {
namespace Data {
namespace Project {

SOF32DKrOData::SOF32DKrOData()
{
    InitVariables();
}

double SOF32DKrOData::SG()
{
    return sg;
}

vector<double> &SOF32DKrOData::KrO()
{
    return kro;
}

void SOF32DKrOData::SetSG(const double &sg)
{
    this->sg = sg;
}

void SOF32DKrOData::InitVariables()
{
    sg = 0;

    kro.clear();
}

}}}
