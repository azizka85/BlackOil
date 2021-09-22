#include "operatordata.h"

namespace BlackOil {
namespace Data {
namespace Project {

OperatorData::OperatorData()
{
    InitVariables();
}

QVariant OperatorData::ArrayName()
{
    return arrayName;
}

QString OperatorData::Value()
{
    return value;
}

QVariant OperatorData::Source()
{
    return source;
}

Box &OperatorData::Box()
{
    return box;
}

int OperatorData::OperatorType()
{
    return operatorType;
}

void OperatorData::SetArrayName(const QVariant &arrayName)
{
    this->arrayName = arrayName;
}

void OperatorData::SetValue(const QString &value)
{
    this->value = value;
}

void OperatorData::SetSource(const QVariant &source)
{
    this->source = source;
}

void OperatorData::SetBox(const class Box &box)
{
    this->box = box;
}

void OperatorData::SetOperatorType(int operatorType)
{
    this->operatorType = operatorType;
}

void OperatorData::InitVariables()
{
    SetOperatorType(OperatorTypeEnum::EQUALS);

    SetArrayName(QVariant());
    SetValue("");
    SetSource(QVariant());
    SetBox(Box());
}

}}}
