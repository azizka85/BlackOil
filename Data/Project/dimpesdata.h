#ifndef DIMPESDATA_H
#define DIMPESDATA_H

#include <qvariant.h>

#include <data_global.h>

namespace BlackOil {
namespace Data {
namespace Project {

class DATA_EXPORT DIMPESData
{
public:
    DIMPESData();

    QVariant DSTARG();
    QVariant DSMAX();
    QVariant DPMAX();

    void SetDSTARG(const QVariant& dsTARG);
    void SetDSMAX(const QVariant& dsMAX);
    void SetDPMAX(const QVariant& dpMAX);

    void InitVariables();

protected:
    QVariant dsTARG, dsMAX, dpMAX;};

}}}

#endif // DIMPESDATA_H
