#ifndef PBVDDATA_H
#define PBVDDATA_H

#include <data_global.h>

namespace BlackOil {
namespace Data {
namespace Project {

class DATA_EXPORT PBVDData
{
public:
    PBVDData();

    double Depth();
    double PBub();

    void SetDepth(const double& depth);
    void SetPBub(const double& pBub);

    void InitVariables();

protected:
    double depth, pBub;};

}}}

#endif // PBVDDATA_H
