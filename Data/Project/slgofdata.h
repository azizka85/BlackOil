#ifndef SLGOFDATA_H
#define SLGOFDATA_H

#include <qvariant.h>

#include <data_global.h>

namespace BlackOil {
namespace Data {
namespace Project {

class DATA_EXPORT SLGOFData
{
public:
    SLGOFData();

    double SL();

    QVariant KrG();
    QVariant KrO();
    QVariant Pc();

    void SetSL(const double& sl);

    void SetKrG(const QVariant& krg);
    void SetKrO(const QVariant& kro);
    void SetPc(const QVariant& pc);

    void InitVariables();

protected:
    double sl;
    QVariant krg, kro, pc;
};

}}}

#endif // SLGOFDATA_H
