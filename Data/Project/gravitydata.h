#ifndef GRAVITYDATA_H
#define GRAVITYDATA_H

#include <qvariant.h>

#include <data_global.h>

namespace BlackOil {
namespace Data {
namespace Project {

class DATA_EXPORT GRAVITYData
{
public:
    GRAVITYData();

    QVariant GO();
    QVariant GW();
    QVariant GG();

    void SetGO(const QVariant& go);
    void SetGW(const QVariant& gw);
    void SetGG(const QVariant& gg);

    void InitVariables();

protected:
    QVariant go, gw, gg;
};

}}}

#endif // GRAVITYDATA_H
