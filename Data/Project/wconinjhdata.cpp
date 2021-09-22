#include "wconinjhdata.h"

namespace BlackOil {
namespace Data {
namespace Project {

WCONINJHData::WCONINJHData()
{
    InitVariables();
}

QString WCONINJHData::WellName()
{
    return wellName;
}

QVariant WCONINJHData::InjFluid()
{
    return injFluid;
}

QVariant WCONINJHData::WellStatus()
{
    return wellStatus;
}

QVariant WCONINJHData::RATE()
{
    return rate;
}

QVariant WCONINJHData::BHP()
{
    return bhp;
}

QDateTime WCONINJHData::Date()
{
    return date;
}

void WCONINJHData::SetWellName(const QString &wellName)
{
    this->wellName = wellName;
}

void WCONINJHData::SetInjFluid(const QVariant &injFluid)
{
    this->injFluid = injFluid;
}

void WCONINJHData::SetWellStatus(const QVariant &wellStatus)
{
    this->wellStatus = wellStatus;
}

void WCONINJHData::SetRATE(const QVariant &rate)
{
    this->rate = rate;
}

void WCONINJHData::SetBHP(const QVariant &bhp)
{
    this->bhp = bhp;
}

void WCONINJHData::SetDate(const QDateTime &date)
{
    this->date = date;
}

void WCONINJHData::InitVariables()
{
    wellName.clear();
    injFluid.clear();
    wellStatus.clear();
    rate.clear();
    bhp.clear();
    date = QDateTime::currentDateTime();
}

}}}
