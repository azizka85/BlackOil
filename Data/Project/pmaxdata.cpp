#include "pmaxdata.h"

namespace BlackOil {
namespace Data {
namespace Project {

PMAXData::PMAXData()
{
    InitVariables();
}

QVariant PMAXData::PMax()
{
    return pMax;
}

QVariant PMAXData::PMaxComp()
{
    return pMaxComp;
}

QVariant PMAXData::PMinComp()
{
    return pMinComp;
}

QVariant PMAXData::NumNodes()
{
    return numNodes;
}

void PMAXData::SetPMax(const QVariant &pMax)
{
    this->pMax = pMax;
}

void PMAXData::SetPMaxComp(const QVariant &pMaxComp)
{
    this->pMaxComp = pMaxComp;
}

void PMAXData::SetPMinComp(const QVariant &pMinComp)
{
    this->pMinComp = pMinComp;
}

void PMAXData::SetNumNodes(const QVariant &numNodes)
{
    this->numNodes = numNodes;
}

void PMAXData::InitVariables()
{
    pMax.clear();
    pMaxComp.clear();
    pMinComp.clear();
    numNodes.clear();
}

}}}
