#include "wconinjedata.h"

namespace BlackOil {
namespace Data {
namespace Project {

WCONINJEData::WCONINJEData()
{
    InitVariables();
}

QString WCONINJEData::WellName()
{
    return wellName;
}

QVariant WCONINJEData::InjFluid()
{
    return injFluid;
}

QVariant WCONINJEData::WellStatus()
{
    return wellStatus;
}

QVariant WCONINJEData::WellControl()
{
    return wellControl;
}

QVariant WCONINJEData::RATE()
{
    return rate;
}

QVariant WCONINJEData::RESV()
{
    return resv;
}

QVariant WCONINJEData::BHP()
{
    return bhp;
}

QDateTime WCONINJEData::Date()
{
    return date;
}

void WCONINJEData::SetWellName(const QString &wellName)
{
    this->wellName = wellName;
}

void WCONINJEData::SetInjFluid(const QVariant &injFluid)
{
    this->injFluid = injFluid;
}

void WCONINJEData::SetWellStatus(const QVariant &wellStatus)
{
    this->wellStatus = wellStatus;
}

void WCONINJEData::SetWellControl(const QVariant &wellControl)
{
    this->wellControl = wellControl;
}

void WCONINJEData::SetRATE(const QVariant &rate)
{
    this->rate = rate;
}

void WCONINJEData::SetRESV(const QVariant &resv)
{
    this->resv = resv;
}

void WCONINJEData::SetBHP(const QVariant &bhp)
{
    this->bhp = bhp;
}

void WCONINJEData::SetDate(const QDateTime &date)
{
    this->date = date;
}

void WCONINJEData::InitVariables()
{
    wellName.clear();
    wellStatus.clear();
    wellControl.clear();
    injFluid.clear();
    rate.clear();
    resv.clear();
    bhp.clear();

    date = QDateTime::currentDateTime();
}

}}}
