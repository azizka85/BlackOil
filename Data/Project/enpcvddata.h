#ifndef ENPCVDDATA_H
#define ENPCVDDATA_H

#include <qvariant.h>

#include <data_global.h>

namespace BlackOil {
namespace Data {
namespace Project {

class DATA_EXPORT ENPCVDData
{
public:
    ENPCVDData();

    double Depth();
    QVariant MaxPcGO();
    QVariant MaxPcWO();

    void SetDepth(const double& depth);
    void SetMaxPcGO(const QVariant& maxPcGO);
    void SetMaxPcWO(const QVariant& maxPcWO);

    void InitVariables();

protected:
    double depth;
    QVariant maxPcGO, maxPcWO;};

}}}

#endif // ENPCVDDATA_H
