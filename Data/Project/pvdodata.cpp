#include "pvdodata.h"

namespace BlackOil {
namespace Data {
namespace Project {

PVDOData::PVDOData()
{
    InitVariables();
}

double PVDOData::PO()
{
    return po;
}

double PVDOData::BO()
{
    return bo;
}

double PVDOData::MO()
{
    return mo;
}

void PVDOData::SetPO(const double &po)
{
    this->po = po;
}

void PVDOData::SetBO(const double &bo)
{
    this->bo = bo;
}

void PVDOData::SetMO(const double &mo)
{
    this->mo = mo;
}

void PVDOData::InitVariables()
{
    po = 0;
    bo = 0;
    mo = 0;
}

}}}
