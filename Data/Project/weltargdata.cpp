#include "weltargdata.h"

namespace BlackOil {
namespace Data {
namespace Project {

WELTARGData::WELTARGData()
{
    InitVariables();
}

QString WELTARGData::WellName()
{
    return wellName;
}

QVariant WELTARGData::WellControl()
{
    return wellControl;
}

QVariant WELTARGData::Value()
{
    return value;
}

QDateTime WELTARGData::Date()
{
    return date;
}

void WELTARGData::SetWellName(const QString &wellName)
{
    this->wellName = wellName;
}

void WELTARGData::SetWellControl(const QVariant &wellControl)
{
    this->wellControl = wellControl;
}

void WELTARGData::SetValue(const QVariant &value)
{
    this->value = value;
}

void WELTARGData::SetDate(const QDateTime &date)
{
    this->date = date;
}

void WELTARGData::InitVariables()
{
    wellName.clear();
    wellControl.clear();
    value.clear();
    date = QDateTime::currentDateTime();
}

}}}
