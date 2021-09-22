#ifndef PRVDDATA_H
#define PRVDDATA_H

#include <data_global.h>

namespace BlackOil {
namespace Data {
namespace Project {

class DATA_EXPORT PRVDData
{
public:
    PRVDData();

    double Depth();
    double PO();

    void SetDepth(const double& depth);
    void SetPO(const double& po);

    void InitVariables();

protected:
    double depth, po;};

}}}

#endif // PRVDDATA_H
