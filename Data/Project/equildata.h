#ifndef EQUILDATA_H
#define EQUILDATA_H

#include <qvariant.h>

#include <data_global.h>

namespace BlackOil {
namespace Data {
namespace Project {

class DATA_EXPORT EQUILData
{
public:
    EQUILData();

    double DatumDepth();
    double DatumP();
    QVariant WOCDepth();
    QVariant WOCPc();
    QVariant GOCDepth();
    QVariant GOCPc();

    void SetDatumDepth(const double& datumDepth);
    void SetDatumP(const double& datumP);
    void SetWOCDepth(const QVariant& wocDepth);
    void SetWOCPc(const QVariant& wocPc);
    void SetGOCDepth(const QVariant& gocDepth);
    void SetGOCPc(const QVariant& gocPc);

    void InitVariables();

protected:
    double datumDepth, datumP;
    QVariant wocDepth, wocPc, gocDepth, gocPc;};

}}}

#endif // EQUILDATA_H
