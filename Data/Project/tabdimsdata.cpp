#include "tabdimsdata.h"

namespace BlackOil {
namespace Data {
namespace Project {

TABDIMSData::TABDIMSData()
{
    InitVariables();
}

QVariant TABDIMSData::NTSFUN()
{
    return ntSFUN;
}

QVariant TABDIMSData::NTPVT()
{
    return ntPVT;
}

QVariant TABDIMSData::NSSFUN()
{
    return nsSFUN;
}

void TABDIMSData::SetNTSFUN(const QVariant &ntSFUN)
{
    this->ntSFUN = ntSFUN;
}

void TABDIMSData::SetNTPVT(const QVariant &ntPVT)
{
    this->ntPVT = ntPVT;
}

void TABDIMSData::SetNSSFUN(const QVariant &nsSFUN)
{
    this->nsSFUN = nsSFUN;
}

void TABDIMSData::InitVariables()
{
    ntSFUN.clear();
    ntPVT.clear();
    nsSFUN.clear();
}

}}}
