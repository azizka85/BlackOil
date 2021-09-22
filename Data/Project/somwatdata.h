#ifndef SOMWATDATA_H
#define SOMWATDATA_H

#include <data_global.h>

namespace BlackOil {
namespace Data {
namespace Project {

class DATA_EXPORT SOMWATData
{
public:
    SOMWATData();

    double SW();
    double SOMin();

    void SetSW(const double &sw);
    void SetSOMin(const double &soMin);

    void InitVariables();

protected:
    double sw, soMin;
};

}}}

#endif // SOMWATDATA_H
