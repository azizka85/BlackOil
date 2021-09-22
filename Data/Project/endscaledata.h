#ifndef ENDSCALEDATA_H
#define ENDSCALEDATA_H

#include <qvariant.h>

#include <data_global.h>

namespace BlackOil {
namespace Data {
namespace Project {

class DATA_EXPORT ENDSCALEData
{
public:
    ENDSCALEData();

    QVariant Directional();
    QVariant Irreversible();
    QVariant NTENDP();
    QVariant MaxNodesEPD();

    void SetDirectional(const QVariant &directional);
    void SetIrreversible(const QVariant &irreversible);
    void SetNTENDP(const QVariant &ntENDP);
    void SetMaxNodesEPD(const QVariant &maxNodesEPD);

    void InitVariables();

protected:
    QVariant directional;
    QVariant irreversible;
    QVariant ntENDP;
    QVariant maxNodesEPD;
};

}}}

#endif // ENDSCALEDATA_H
