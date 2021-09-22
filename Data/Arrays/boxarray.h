#ifndef BOXARRAY_H
#define BOXARRAY_H

#include <vector>
#include <algorithm>

#include <qvariant.h>

#include <box.h>
#include <subarray.h>

#include <data_global.h>

using namespace std;

using namespace BlackOil::Data::Grid;

namespace BlackOil {
namespace Data {
namespace Arrays {

class DATA_EXPORT BoxArray
{
public:
    BoxArray();

    Box &Box();
    void SetBox(const class Box &box);

    QVariant &operator() (int i);
    QVariant &operator() (int i, int j);
    QVariant &operator() (int i, int j, int k);

    int CalculateIndex(int i);
    int CalculateIndex(int i, int j);
    int CalculateIndex(int i, int j, int k);

    int NextIndex();

    QVariant &Value(int index);

    void AddInterval(int length, QVariant value);
    void Add(QVariant value);

    void Clear();

protected:
    SubArray &Search(int index);

protected:
    class Box box;
    vector<SubArray> data;
    QVariant nullValue;
};

}}}

#endif // BOXARRAY_H
