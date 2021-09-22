#ifndef SPECROCKDATA_H
#define SPECROCKDATA_H

#include <data_global.h>

namespace BlackOil {
namespace Data {
namespace Project {

class DATA_EXPORT SPECROCKData
{
public:
    SPECROCKData();

    double T();
    double CV();

    void SetT(const double& t);
    void SetCV(const double& cv);

    void InitVariables();

protected:
    double t, cv;};

}}}

#endif // SPECROCKDATA_H
