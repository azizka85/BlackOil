#include "wconproddata.h"

namespace BlackOil {
namespace Data {
namespace Project {

WCONPRODData::WCONPRODData()
{
    InitVariables();
}

QString WCONPRODData::WellName()
{
    return wellName;
}

QVariant WCONPRODData::WellStatus()
{
    return wellStatus;
}

QVariant WCONPRODData::WellControl()
{
    return wellControl;
}

QVariant WCONPRODData::ORAT()
{
    return orat;
}

QVariant WCONPRODData::WRAT()
{
    return wrat;
}

QVariant WCONPRODData::GRAT()
{
    return grat;
}

QVariant WCONPRODData::LRAT()
{
    return lrat;
}

QVariant WCONPRODData::RESV()
{
    return resv;
}

QVariant WCONPRODData::BHP()
{
    return bhp;
}

QDateTime WCONPRODData::Date()
{
    return date;
}

void WCONPRODData::SetWellName(const QString &wellName)
{
    this->wellName = wellName;
}

void WCONPRODData::SetWellStatus(const QVariant &wellStatus)
{
    this->wellStatus = wellStatus;
}

void WCONPRODData::SetWellControl(const QVariant &wellControl)
{
    this->wellControl = wellControl;
}

void WCONPRODData::SetORAT(const QVariant &orat)
{
    this->orat = orat;
}

void WCONPRODData::SetWRAT(const QVariant &wrat)
{
    this->wrat = wrat;
}

void WCONPRODData::SetGRAT(const QVariant &grat)
{
    this->grat = grat;
}

void WCONPRODData::SetLRAT(const QVariant &lrat)
{
    this->lrat = lrat;
}

void WCONPRODData::SetRESV(const QVariant &resv)
{
    this->resv = resv;
}

void WCONPRODData::SetBHP(const QVariant &bhp)
{
    this->bhp = bhp;
}

void WCONPRODData::SetDate(const QDateTime &date)
{
    this->date = date;
}

void WCONPRODData::InitVariables()
{
    wellName.clear();
    wellStatus.clear();
    wellControl.clear();
    orat.clear();
    wrat.clear();
    grat.clear();
    lrat.clear();
    resv.clear();
    bhp.clear();

    date = QDateTime::currentDateTime();
}

}}}
