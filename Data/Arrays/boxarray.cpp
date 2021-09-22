#include "boxarray.h"

namespace BlackOil {
namespace Data {
namespace Arrays {

BoxArray::BoxArray() { }

Box &BoxArray::Box()
{
    return box;
}

void BoxArray::SetBox(const class Box &box)
{
    this->box = box;
}

QVariant &BoxArray::operator()(int i)
{
    return Value(CalculateIndex(i));
}

QVariant &BoxArray::operator()(int i, int j)
{
    return Value(CalculateIndex(i, j));
}

QVariant &BoxArray::operator()(int i, int j, int k)
{
    return Value(CalculateIndex(i, j, k));
}

int BoxArray::CalculateIndex(int i)
{
    i = i - box.I1();

    if(i >= 0 && i < box.Nx())
        return i;
    else
        return -1;
}

int BoxArray::CalculateIndex(int i, int j)
{
    i = i - box.I1();
    j = j - box.J1();

    if(i >= 0 && i < box.Nx() && j >= 0 && j < box.Ny())
        return j * box.Nx() + i;
    else
        return -1;
}

int BoxArray::CalculateIndex(int i, int j, int k)
{
    i = i - box.I1();
    j = j - box.J1();
    k = k - box.K1();

    if(i >= 0 && i < box.Nx() && j >= 0 && j < box.Ny() && k >= 0 && k < box.Nz())
        return k * box.Nx() * box.Ny() + j * box.Nx() + i;
    else
        return -1;
}

int BoxArray::NextIndex()
{
    if(data.size() > 0)
    {
        auto item = data[data.size() - 1];

        return item.Index() + item.Length();
    }

    return 0;
}

QVariant &BoxArray::Value(int index)
{
    if(data.size() > 0 && index >= 0)
    {
        SubArray &array = Search(index);

        int i = index - array.Index();

        if(i < array.Length())
        {
            if(array.IsInterval())
                return array.Value();
            else
                return array.List()[i];
        }
    }

    return nullValue;
}

void BoxArray::AddInterval(int length, QVariant value)
{
    if(length > 0) data.push_back(SubArray(NextIndex(), length, value));
}

void BoxArray::Add(QVariant value)
{
    SubArray *subArray = nullptr;

    if(data.size() > 0)
    {
        SubArray *item = &data[data.size() - 1];

        if(!item->IsInterval()) subArray = item;
    }

    if(subArray == nullptr)
    {
        data.push_back(SubArray(NextIndex()));

        subArray = &data[data.size() - 1];
    }

    subArray->List().push_back(value);
}

void BoxArray::Clear()
{
    data.clear();
    box.InitVariables();
}

SubArray &BoxArray::Search(int index)
{
    auto it = upper_bound(data.begin(), data.end(), index, [](const int &val, const SubArray &array) {
        return  val < array.Index();
    });

    int i = it - data.begin();

    return data[i-1];
}

}}}
