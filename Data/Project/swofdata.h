#ifndef SWOFDATA_H
#define SWOFDATA_H

#include <qvariant.h>

#include <data_global.h>

namespace BlackOil {
namespace Data {
namespace Project {

class DATA_EXPORT SWOFData
{
public:
    SWOFData();

    double SW();

    QVariant KrW();
    QVariant KrO();
    QVariant Pc();

    void SetSW(const double& sw);

    void SetKrW(const QVariant& krw);
    void SetKrO(const QVariant& kro);
    void SetPc(const QVariant& pc);

    void InitVariables();

protected:
    double sw;
    QVariant krw, kro, pc;
};

}}}

#endif // SWOFDATA_H
