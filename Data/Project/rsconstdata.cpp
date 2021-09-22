#include "rsconstdata.h"

namespace BlackOil {
namespace Data {
namespace Project {

RSCONSTData::RSCONSTData()
{
    InitVariables();
}

double RSCONSTData::RS()
{
    return rs;
}

double RSCONSTData::PBub()
{
    return pBub;
}

void RSCONSTData::SetRS(const double &rs)
{
    this->rs = rs;
}

void RSCONSTData::SetPBub(const double &pBub)
{
    this->pBub = pBub;
}

void RSCONSTData::InitVariables()
{
    rs = 0;
    pBub = 0;
}

}}}
