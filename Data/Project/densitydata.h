#ifndef DENSITYDATA_H
#define DENSITYDATA_H

#include <qvariant.h>

#include <data_global.h>

namespace BlackOil {
namespace Data {
namespace Project {

class DATA_EXPORT DENSITYData
{
public:
    DENSITYData();

    QVariant RO();
    QVariant RW();
    QVariant RG();

    void SetRO(const QVariant& ro);
    void SetRW(const QVariant& rw);
    void SetRG(const QVariant& rg);

    void InitVariables();

protected:
    QVariant ro, rw, rg;
};

}}}

#endif // DENSITYDATA_H
