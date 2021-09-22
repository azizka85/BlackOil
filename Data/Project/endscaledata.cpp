#include "endscaledata.h"

namespace BlackOil {
namespace Data {
namespace Project {

ENDSCALEData::ENDSCALEData()
{
    InitVariables();
}

QVariant ENDSCALEData::Directional()
{
    return directional;
}

QVariant ENDSCALEData::Irreversible()
{
    return irreversible;
}

QVariant ENDSCALEData::NTENDP()
{
    return ntENDP;
}

QVariant ENDSCALEData::MaxNodesEPD()
{
    return maxNodesEPD;
}

void ENDSCALEData::SetDirectional(const QVariant &directional)
{
    this->directional = directional;
}

void ENDSCALEData::SetIrreversible(const QVariant &irreversible)
{
    this->irreversible = irreversible;
}

void ENDSCALEData::SetNTENDP(const QVariant &ntENDP)
{
    this->ntENDP = ntENDP;
}

void ENDSCALEData::SetMaxNodesEPD(const QVariant &maxNodesEPD)
{
    this->maxNodesEPD = maxNodesEPD;
}

void ENDSCALEData::InitVariables()
{
    directional.clear();
    irreversible.clear();
    ntENDP.clear();
    maxNodesEPD.clear();
}

}}}
