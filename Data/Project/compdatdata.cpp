#include "compdatdata.h"

namespace BlackOil {
namespace Data {
namespace Project {

COMPDATData::COMPDATData()
{
    InitVariables();
}

QString COMPDATData::WellName()
{
    return wellName;
}

QVariant COMPDATData::I()
{
    return i;
}

QVariant COMPDATData::J()
{
    return j;
}

QVariant COMPDATData::K1()
{
    return k1;
}

QVariant COMPDATData::K2()
{
    return k2;
}

QVariant COMPDATData::WellStatus()
{
    return wellStatus;
}

QVariant COMPDATData::SATNUM()
{
    return satnum;
}

QVariant COMPDATData::TranFactor()
{
    return tranFactor;
}

QVariant COMPDATData::Diameter()
{
    return diameter;
}

QVariant COMPDATData::Kh()
{
    return kh;
}

QVariant COMPDATData::SkinFactor()
{
    return skinFactor;
}

QDateTime COMPDATData::Date()
{
    return date;
}

void COMPDATData::SetWellName(const QString &wellName)
{
    this->wellName = wellName;
}

void COMPDATData::SetI(const QVariant &i)
{
    this->i = i;
}

void COMPDATData::SetJ(const QVariant &j)
{
    this->j = j;
}

void COMPDATData::SetK1(const QVariant &k1)
{
    this->k1 = k1;
}

void COMPDATData::SetK2(const QVariant &k2)
{
    this->k2 = k2;
}

void COMPDATData::SetWellStatus(const QVariant &wellStatus)
{
    this->wellStatus = wellStatus;
}

void COMPDATData::SetSATNUM(const QVariant &satnum)
{
    this->satnum = satnum;
}

void COMPDATData::SetTranFactor(const QVariant &tranFactor)
{
    this->tranFactor = tranFactor;
}

void COMPDATData::SetDiameter(const QVariant &diameter)
{
    this->diameter = diameter;
}

void COMPDATData::SetKh(const QVariant &kh)
{
    this->kh = kh;
}

void COMPDATData::SetSkinFactor(const QVariant &skinFactor)
{
    this->skinFactor = skinFactor;
}

void COMPDATData::SetDate(const QDateTime &date)
{
    this->date = date;
}

void COMPDATData::InitVariables()
{
    wellName.clear();
    wellStatus.clear();
    i.clear();
    j.clear();
    k1.clear();
    k2.clear();
    satnum.clear();
    tranFactor.clear();
    diameter.clear();
    kh.clear();
    skinFactor.clear();
    date = QDateTime::currentDateTime();
}

}}}
