#ifndef PVTGDATA_H
#define PVTGDATA_H

#include <data_global.h>

namespace BlackOil {
namespace Data {
namespace Project {

class DATA_EXPORT PVTGData
{
public:
    PVTGData();

    double PG();
    double RV();
    double BG();
    double MG();

    void SetPG(const double& pg);
    void SetRV(const double& rv);
    void SetBG(const double& bg);
    void SetMG(const double& mg);

    void InitVariables();

protected:
    double pg, rv, bg, mg;
};

}}}

#endif // PVTGDATA_H
