#include "pvcodata.h"

namespace BlackOil {
namespace Data {
namespace Project {

PVCOData::PVCOData()
{
    InitVariables();
}

double PVCOData::PO()
{
    return po;
}

QVariant PVCOData::RS()
{
    return rs;
}

QVariant PVCOData::BO()
{
    return bo;
}

QVariant PVCOData::MO()
{
    return mo;
}

QVariant PVCOData::CO()
{
    return co;
}

QVariant PVCOData::CVO()
{
    return cvo;
}

void PVCOData::SetPO(const double &po)
{
    this->po = po;
}

void PVCOData::SetRS(const QVariant &rs)
{
    this->rs = rs;
}

void PVCOData::SetBO(const QVariant &bo)
{
    this->bo = bo;
}

void PVCOData::SetMO(const QVariant &mo)
{
    this->mo = mo;
}

void PVCOData::SetCO(const QVariant &co)
{
    this->co = co;
}

void PVCOData::SetCVO(const QVariant &cvo)
{
    this->cvo = cvo;
}

void PVCOData::InitVariables()
{
    po = 0;

    rs.clear();
    bo.clear();
    mo.clear();
    co.clear();
    cvo.clear();
}

}}}
