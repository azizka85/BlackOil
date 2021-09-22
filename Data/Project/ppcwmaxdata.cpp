#include "ppcwmaxdata.h"

namespace BlackOil {
namespace Data {
namespace Project {

PPCWMAXData::PPCWMAXData()
{
    InitVariables();
}

QVariant PPCWMAXData::PcMax()
{
    return pcMax;
}

QVariant PPCWMAXData::SModify()
{
    return sModify;
}

void PPCWMAXData::SetPcMax(const QVariant &pcMax)
{
    this->pcMax = pcMax;
}

void PPCWMAXData::SetSModify(const QVariant &sModify)
{
    this->sModify = sModify;
}

void PPCWMAXData::InitVariables()
{
    pcMax.clear();
    sModify.clear();
}

}}}
