#include "pvtodata.h"

namespace BlackOil {
namespace Data {
namespace Project {

PVTOData::PVTOData()
{
    InitVariables();
}

double PVTOData::RS()
{
    return rs;
}

double PVTOData::PO()
{
    return po;
}

double PVTOData::BO()
{
    return bo;
}

double PVTOData::MO()
{
    return mo;
}

void PVTOData::SetRS(const double &rs)
{
    this->rs = rs;
}

void PVTOData::SetPO(const double &po)
{
    this->po = po;
}

void PVTOData::SetBO(const double &bo)
{
    this->bo = bo;
}

void PVTOData::SetMO(const double &mo)
{
    this->mo = mo;
}

void PVTOData::InitVariables()
{
    rs = 0;
    po = 0;
    bo = 0;
    mo = 0;
}

}}}
