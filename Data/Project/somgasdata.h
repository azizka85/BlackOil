#ifndef SOMGASDATA_H
#define SOMGASDATA_H

#include <data_global.h>

namespace BlackOil {
namespace Data {
namespace Project {

class DATA_EXPORT SOMGASData
{
public:
    SOMGASData();

    double SG();
    double SOMin();

    void SetSG(const double& sg);
    void SetSOMin(const double& soMin);

    void InitVariables();

protected:
    double sg, soMin;
};

}}}

#endif // SOMGASDATA_H
