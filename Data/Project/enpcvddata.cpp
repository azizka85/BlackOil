#include "enpcvddata.h"

namespace BlackOil {
namespace Data {
namespace Project {

ENPCVDData::ENPCVDData()
{
    InitVariables();
}

double ENPCVDData::Depth()
{
    return depth;
}

QVariant ENPCVDData::MaxPcGO()
{
    return maxPcGO;
}

QVariant ENPCVDData::MaxPcWO()
{
    return maxPcWO;
}

void ENPCVDData::SetDepth(const double &depth)
{
    this->depth = depth;
}

void ENPCVDData::SetMaxPcGO(const QVariant &maxPcGO)
{
    this->maxPcGO = maxPcGO;
}

void ENPCVDData::SetMaxPcWO(const QVariant &maxPcWO)
{
    this->maxPcWO = maxPcWO;
}

void ENPCVDData::InitVariables()
{
    depth = 0;
    maxPcGO.clear();
    maxPcWO.clear();
}

}}}
