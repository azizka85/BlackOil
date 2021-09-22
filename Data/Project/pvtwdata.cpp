#include "pvtwdata.h"

namespace BlackOil {
namespace Data {
namespace Project {

PVTWData::PVTWData()
{
    InitVariables();
}

QVariant PVTWData::PWRef()
{
    return pwRef;
}

QVariant PVTWData::BWRef()
{
    return bwRef;
}

QVariant PVTWData::CW()
{
    return cw;
}

QVariant PVTWData::MWRef()
{
    return mwRef;
}

QVariant PVTWData::CVW()
{
    return cvw;
}

void PVTWData::SetPWRef(const QVariant &pwRef)
{
    this->pwRef = pwRef;
}

void PVTWData::SetBWRef(const QVariant &bwRef)
{
    this->bwRef = bwRef;
}

void PVTWData::SetCW(const QVariant &cw)
{
    this->cw = cw;
}

void PVTWData::SetMWRef(const QVariant &mwRef)
{
    this->mwRef = mwRef;
}

void PVTWData::SetCVW(const QVariant &cvw)
{
    this->cvw = cvw;
}

void PVTWData::InitVariables()
{
    pwRef.clear();
    bwRef.clear();
    cw.clear();
    mwRef.clear();
    cvw.clear();
}

}}}
