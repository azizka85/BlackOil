#include "rockoptsdata.h"

namespace BlackOil {
namespace Data {
namespace Project {

ROCKOPTSData::ROCKOPTSData()
{
    InitVariables();
}

QVariant ROCKOPTSData::MAOTP()
{
    return maotp;
}

QVariant ROCKOPTSData::RPO()
{
    return rpo;
}

QVariant ROCKOPTSData::RegionOption()
{
    return regionOption;
}

QVariant ROCKOPTSData::IHBOption()
{
    return ihbOption;
}

void ROCKOPTSData::SetMAOTP(const QVariant &maotp)
{
    this->maotp = maotp;
}

void ROCKOPTSData::SetRPO(const QVariant &rpo)
{
    this->rpo = rpo;
}

void ROCKOPTSData::SetRegionOption(const QVariant &regionOption)
{
    this->regionOption = regionOption;
}

void ROCKOPTSData::SetIHBOption(const QVariant &ihbOption)
{
    this->ihbOption = ihbOption;
}

void ROCKOPTSData::InitVariables()
{
    maotp.clear();
    rpo.clear();
    regionOption.clear();
    ihbOption.clear();
}

}}}
