#ifndef SGOFDATA_H
#define SGOFDATA_H

#include <qvariant.h>

#include <data_global.h>

namespace BlackOil {
namespace Data {
namespace Project {

class DATA_EXPORT SGOFData
{
public:
    SGOFData();

    double SG();

    QVariant KrG();
    QVariant KrO();
    QVariant Pc();

    void SetSG(const double& sg);

    void SetKrG(const QVariant& krg);
    void SetKrO(const QVariant& kro);
    void SetPc(const QVariant& pc);

    void InitVariables();

protected:
    double sg;
    QVariant krg, kro, pc;
};

}}}

#endif // SGOFDATA_H
