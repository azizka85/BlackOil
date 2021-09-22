#include "rockdata.h"

namespace BlackOil {
namespace Data {
namespace Project {

ROCKData::ROCKData()
{
    InitVariables();
}

QVariant ROCKData::PRef()
{
    return pRef;
}

QVariant ROCKData::CPP()
{
    return cpp;
}

void ROCKData::SetPRef(const QVariant &pRef)
{
    this->pRef = pRef;
}

void ROCKData::SetCPP(const QVariant &cpp)
{
    this->cpp = cpp;
}

void ROCKData::InitVariables()
{
    pRef.clear();
    cpp.clear();
}

}}}
