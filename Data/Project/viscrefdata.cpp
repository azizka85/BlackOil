#include "viscrefdata.h"

namespace BlackOil {
namespace Data {
namespace Project {

VISCREFData::VISCREFData()
{
    InitVariables();
}

double VISCREFData::PRef()
{
    return pRef;
}

QVariant VISCREFData::RSRef()
{
    return rsRef;
}

QVariant VISCREFData::GRef()
{
    return gRef;
}

void VISCREFData::SetPRef(const double &pRef)
{
    this->pRef = pRef;
}

void VISCREFData::SetRSRef(const QVariant &rsRef)
{
    this->rsRef = rsRef;
}

void VISCREFData::SetGRef(const QVariant &gRef)
{
    this->gRef = gRef;
}

void VISCREFData::InitVariables()
{
    pRef = 0;
    rsRef.clear();
    gRef.clear();
}

}}}
