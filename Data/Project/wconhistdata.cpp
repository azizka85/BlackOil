#include "wconhistdata.h"

namespace BlackOil {
namespace Data {
namespace Project {

WCONHISTData::WCONHISTData()
{
    InitVariables();
}

QString WCONHISTData::WellName()
{
    return wellName;
}

QVariant WCONHISTData::WellStatus()
{
    return wellStatus;
}

QVariant WCONHISTData::WellControl()
{
    return wellControl;
}

QVariant WCONHISTData::ORAT()
{
    return orat;
}

QVariant WCONHISTData::WRAT()
{
    return wrat;
}

QVariant WCONHISTData::GRAT()
{
    return grat;
}

QDateTime WCONHISTData::Date()
{
    return date;
}

void WCONHISTData::SetWellName(const QString &wellName)
{
    this->wellName = wellName;
}

void WCONHISTData::SetWellStatus(const QVariant &wellStatus)
{
    this->wellStatus = wellStatus;
}

void WCONHISTData::SetWellControl(const QVariant &wellControl)
{
    this->wellControl = wellControl;
}

void WCONHISTData::SetORAT(const QVariant &orat)
{
    this->orat = orat;
}

void WCONHISTData::SetWRAT(const QVariant &wrat)
{
    this->wrat = wrat;
}

void WCONHISTData::SetGRAT(const QVariant &grat)
{
    this->grat = grat;
}

void WCONHISTData::SetDate(const QDateTime &date)
{
    this->date = date;
}

void WCONHISTData::InitVariables()
{
    wellName.clear();
    wellStatus.clear();
    wellControl.clear();
    orat.clear();
    wrat.clear();
    grat.clear();

    date = QDateTime::currentDateTime();
}

}}}
