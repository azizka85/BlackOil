#ifndef AQUFETPDATA_H
#define AQUFETPDATA_H

#include <qvariant.h>

#include <data_global.h>

namespace BlackOil {
namespace Data {
namespace Project {

class DATA_EXPORT AQUFETPData
{
public:
    AQUFETPData();

    int Num();
    double DatumDepth();
    QVariant DatumP();
    double VW();
    double C();
    double ProdIndex();
    int PVTWNum();
    QVariant SALT();

    void SetNum(const int& num);
    void SetDatumDepth(const double& datumDepth);
    void SetDatumP(const QVariant& datumP);
    void SetVW(const double& vw);
    void SetC(const double& c);
    void SetProdIndex(const double& prodIndex);
    void SetPVTWNum(const int& pvtwNum);
    void SetSALT(const QVariant& salt);

    void InitVariables();

protected:
    int num, pvtwNum;
    double datumDepth, vw, c, prodIndex;
    QVariant datumP, salt;
};

}}}

#endif // AQUFETPDATA_H
