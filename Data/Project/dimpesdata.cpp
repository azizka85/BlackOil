#include "dimpesdata.h"

namespace BlackOil {
namespace Data {
namespace Project {

DIMPESData::DIMPESData()
{
    InitVariables();
}

QVariant DIMPESData::DSTARG()
{
    return dsTARG;
}

QVariant DIMPESData::DSMAX()
{
    return dsMAX;
}

QVariant DIMPESData::DPMAX()
{
    return dpMAX;
}

void DIMPESData::SetDSTARG(const QVariant &dsTARG)
{
    this->dsTARG = dsTARG;
}

void DIMPESData::SetDSMAX(const QVariant &dsMAX)
{
    this->dsMAX = dsMAX;
}

void DIMPESData::SetDPMAX(const QVariant &dpMAX)
{
    this->dpMAX = dpMAX;
}

void DIMPESData::InitVariables()
{
    dsTARG.clear();
    dsMAX.clear();
    dpMAX.clear();
}

}}}
