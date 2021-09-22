#include "prvddata.h"

namespace BlackOil {
namespace Data {
namespace Project {

PRVDData::PRVDData()
{
    InitVariables();
}

double PRVDData::Depth()
{
    return depth;
}

double PRVDData::PO()
{
    return po;
}

void PRVDData::SetDepth(const double &depth)
{
    this->depth = depth;
}

void PRVDData::SetPO(const double &po)
{
    this->po = po;
}

void PRVDData::InitVariables()
{
    depth = 0;
    po = 0;
}

}}}
