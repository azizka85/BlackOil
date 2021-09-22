#ifndef ENKRVDDATA_H
#define ENKRVDDATA_H

#include <qvariant.h>

#include <data_global.h>

namespace BlackOil {
namespace Data {
namespace Project {

class DATA_EXPORT ENKRVDData
{
public:
    ENKRVDData();

    double Depth();
    QVariant MaxKrW();
    QVariant MaxKrG();
    QVariant MaxKrO();
    QVariant KrWCO();
    QVariant KrGCO();
    QVariant KrOCG();
    QVariant KrOCW();

    void SetDepth(const double& depth);
    void SetMaxKrW(const QVariant& maxkrw);
    void SetMaxKrG(const QVariant& maxkrg);
    void SetMaxKrO(const QVariant& maxkro);
    void SetKrWCO(const QVariant& krwCO);
    void SetKrGCO(const QVariant& krgCO);
    void SetKrOCG(const QVariant& kroCG);
    void SetKrOCW(const QVariant& kroCW);

    void InitVariables();

protected:
    double depth;
    QVariant maxkrw, maxkrg, maxkro, krwCO, krgCO, kroCG, kroCW;};

}}}

#endif // ENKRVDDATA_H
