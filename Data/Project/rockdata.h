#ifndef ROCKDATA_H
#define ROCKDATA_H

#include <qvariant.h>

#include <data_global.h>

namespace BlackOil {
namespace Data {
namespace Project {

class DATA_EXPORT ROCKData
{
public:
    explicit ROCKData();

    QVariant PRef();
    QVariant CPP();

    void SetPRef(const QVariant& pRef);
    void SetCPP(const QVariant& cpp);

    void InitVariables();

protected:
    QVariant pRef, cpp;
};

}}}

#endif // ROCKDATA_H
