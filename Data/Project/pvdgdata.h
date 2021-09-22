#ifndef PVDGDATA_H
#define PVDGDATA_H

#include <data_global.h>

namespace BlackOil {
namespace Data {
namespace Project {

class DATA_EXPORT PVDGData
{
public:
    PVDGData();

    double PG();
    double BG();
    double MG();

    void SetPG(const double& pg);
    void SetBG(const double& bg);
    void SetMG(const double& mg);

    void InitVariables();

protected:
    double pg, bg, mg;
};

}}}

#endif // PVDGDATA_H
