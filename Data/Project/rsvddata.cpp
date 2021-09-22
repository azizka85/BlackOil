#include "rsvddata.h"

namespace BlackOil {
namespace Data {
namespace Project {

RSVDData::RSVDData()
{
    InitVariables();
}

double RSVDData::Depth()
{
    return depth;
}

double RSVDData::RS()
{
    return rs;
}

void RSVDData::SetDepth(const double &depth)
{
    this->depth = depth;
}

void RSVDData::SetRS(const double &rs)
{
    this->rs = rs;
}

void RSVDData::InitVariables()
{
    depth = 0;
    rs = 0;
}

}}}
