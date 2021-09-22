#include "enspcvddata.h"

namespace BlackOil {
namespace Data {
namespace Project {

ENSPCVDData::ENSPCVDData()
{
    InitVariables();
}

double ENSPCVDData::Depth()
{
    return depth;
}

QVariant ENSPCVDData::SGL()
{
    return sgl;
}

QVariant ENSPCVDData::SWL()
{
    return swl;
}

void ENSPCVDData::SetDepth(const double &depth)
{
    this->depth = depth;
}

void ENSPCVDData::SetSGL(const QVariant &sgl)
{
    this->sgl = sgl;
}

void ENSPCVDData::SetSWL(const QVariant &swl)
{
    this->swl = swl;
}

void ENSPCVDData::InitVariables()
{
    depth = 0;
    sgl.clear();
    swl.clear();
}

}}}
