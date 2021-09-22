#include "subarray.h"

namespace BlackOil {
namespace Data {
namespace Arrays {

SubArray::SubArray(int index) : SubArray(index, -1, QVariant())
{
    isInterval = false;
}

SubArray::SubArray(int index, int length, const QVariant &value)
{
    isInterval = true;

    this->index = index;
    this->length = length;
    this->value = value;
}

bool SubArray::IsInterval() const
{
    return isInterval;
}

int SubArray::Index() const
{
    return index;
}

int SubArray::Length() const
{
    if(isInterval) return length;

    return list.size();
}

QVariant &SubArray::Value()
{
    return value;
}

vector<QVariant> &SubArray::List()
{
    return list;
}

void SubArray::SetIndex(int index)
{
    this->index = index;
}

void SubArray::SetLength(int length)
{
    this->length = length;
}

void SubArray::SetValue(const QVariant &value)
{
    this->value = value;
}

}}}
