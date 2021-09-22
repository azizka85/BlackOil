#ifndef SGFNDATA_H
#define SGFNDATA_H

#include <qvariant.h>

#include <data_global.h>

namespace BlackOil {
namespace Data {
namespace Project {

class DATA_EXPORT SGFNData
{
public:
    SGFNData();

    double SG();

    QVariant KrG();
    QVariant Pc();

    void SetSG(const double& sg);

    void SetKrG(const QVariant& krg);
    void SetPc(const QVariant& pc);

    void InitVariables();

protected:
    double sg;
    QVariant krg, pc;
};

}}}

#endif // SGFNDATA_H
