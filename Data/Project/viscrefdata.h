#ifndef VISCREFDATA_H
#define VISCREFDATA_H

#include <qvariant.h>

#include <data_global.h>

namespace BlackOil {
namespace Data {
namespace Project {

class DATA_EXPORT VISCREFData
{
public:
    VISCREFData();

    double PRef();
    QVariant RSRef();
    QVariant GRef();

    void SetPRef(const double& pRef);
    void SetRSRef(const QVariant& rsRef);
    void SetGRef(const QVariant& gRef);

    void InitVariables();

protected:
    double pRef;
    QVariant rsRef, gRef;};

}}}

#endif // VISCREFDATA_H
