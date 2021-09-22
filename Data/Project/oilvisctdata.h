#ifndef OILVISCTDATA_H
#define OILVISCTDATA_H

#include <data_global.h>

namespace BlackOil {
namespace Data {
namespace Project {

class DATA_EXPORT OILVISCTData
{
public:
    OILVISCTData();

    double T();
    double MO();

    void SetT(const double& t);
    void SetMO(const double& mo);

    void InitVariables();

protected:
    double t, mo;
};

}}}

#endif // OILVISCTDATA_H
