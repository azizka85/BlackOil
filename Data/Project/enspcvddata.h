#ifndef ENSPCVDDATA_H
#define ENSPCVDDATA_H

#include <qvariant.h>

#include <data_global.h>

namespace BlackOil {
namespace Data {
namespace Project {

class DATA_EXPORT ENSPCVDData
{
public:
    ENSPCVDData();

    double Depth();
    QVariant SGL();
    QVariant SWL();

    void SetDepth(const double& depth);
    void SetSGL(const QVariant& sgl);
    void SetSWL(const QVariant& swl);

    void InitVariables();

protected:
    double depth;
    QVariant sgl, swl;};

}}}

#endif // ENSPCVDDATA_H
