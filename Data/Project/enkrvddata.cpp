#include "enkrvddata.h"

namespace BlackOil {
namespace Data {
namespace Project {

ENKRVDData::ENKRVDData()
{
    InitVariables();
}

double ENKRVDData::Depth()
{
    return depth;
}

QVariant ENKRVDData::MaxKrW()
{
    return maxkrw;
}

QVariant ENKRVDData::MaxKrG()
{
    return maxkrg;
}

QVariant ENKRVDData::MaxKrO()
{
    return maxkro;
}

QVariant ENKRVDData::KrWCO()
{
    return krwCO;
}

QVariant ENKRVDData::KrGCO()
{
    return krgCO;
}

QVariant ENKRVDData::KrOCG()
{
    return kroCG;
}

QVariant ENKRVDData::KrOCW()
{
    return kroCW;
}

void ENKRVDData::SetDepth(const double &depth)
{
    this->depth = depth;
}

void ENKRVDData::SetMaxKrW(const QVariant &maxkrw)
{
    this->maxkrw = maxkrw;
}

void ENKRVDData::SetMaxKrG(const QVariant &maxkrg)
{
    this->maxkrg = maxkrg;
}

void ENKRVDData::SetMaxKrO(const QVariant &maxkro)
{
    this->maxkro = maxkro;
}

void ENKRVDData::SetKrWCO(const QVariant &krwCO)
{
    this->krwCO = krwCO;
}

void ENKRVDData::SetKrGCO(const QVariant &krgCO)
{
    this->krgCO = krgCO;
}

void ENKRVDData::SetKrOCG(const QVariant &kroCG)
{
    this->kroCG = kroCG;
}

void ENKRVDData::SetKrOCW(const QVariant &kroCW)
{
    this->kroCW = kroCW;
}

void ENKRVDData::InitVariables()
{
    depth = 0;
    maxkrw.clear();
    maxkrg.clear();
    maxkro.clear();
    krwCO.clear();
    krgCO.clear();
    kroCG.clear();
    kroCW.clear();
}

}}}
