#ifndef SUBARRAY_H
#define SUBARRAY_H

#include <vector>

#include <qvariant.h>

#include <data_global.h>

using namespace std;

namespace BlackOil {
namespace Data {
namespace Arrays {

class DATA_EXPORT SubArray
{
public:
    SubArray(int index);
    SubArray(int index, int length,const QVariant &value);

    bool IsInterval() const;
    int Index() const;
    int Length() const;
    QVariant &Value();
    vector<QVariant>& List();

    void SetIndex(int index);
    void SetLength(int length);
    void SetValue(const QVariant &value);

protected:
    int index;
    bool isInterval;
    int length;
    QVariant value;
    vector<QVariant> list;
};

}}}

#endif // SUBARRAY_H
