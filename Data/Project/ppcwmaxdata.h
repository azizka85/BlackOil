#ifndef PPCWMAXDATA_H
#define PPCWMAXDATA_H

#include <qvariant.h>

#include <data_global.h>

namespace BlackOil {
namespace Data {
namespace Project {

class DATA_EXPORT PPCWMAXData
{
public:
    PPCWMAXData();

    QVariant PcMax();
    QVariant SModify();

    void SetPcMax(const QVariant &pcMax);
    void SetSModify(const QVariant& sModify);

    void InitVariables();
protected:
    QVariant pcMax, sModify;};

}}}

#endif // PPCWMAXDATA_H
