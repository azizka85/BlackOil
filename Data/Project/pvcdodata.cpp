#include "pvcdodata.h"

namespace BlackOil {
namespace Data {
namespace Project {

PVCDOData::PVCDOData()
{
    InitVariables();
}

double PVCDOData::PORef()
{
    return poRef;
}

double PVCDOData::BORef()
{
    return boRef;
}

double PVCDOData::CO()
{
    return co;
}

double PVCDOData::MORef()
{
    return moRef;
}

double PVCDOData::CVO()
{
    return cvo;
}

void PVCDOData::SetPORef(const double &poRef)
{
    this->poRef = poRef;
}

void PVCDOData::SetBORef(const double &boRef)
{
    this->boRef = boRef;
}

void PVCDOData::SetCO(const double &co)
{
    this->co = co;
}

void PVCDOData::SetMORef(const double &moRef)
{
    this->moRef = moRef;
}

void PVCDOData::SetCVO(const double &cvo)
{
    this->cvo = cvo;
}

void PVCDOData::InitVariables()
{
    poRef = 0;
    boRef = 0;
    co = 0;
    moRef = 0;
    cvo = 0;
}

}}}
