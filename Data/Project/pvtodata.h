#ifndef PVTODATA_H
#define PVTODATA_H

#include <data_global.h>

namespace BlackOil {
namespace Data {
namespace Project {

class DATA_EXPORT PVTOData
{
public:
    PVTOData();

    double RS();
    double PO();
    double BO();
    double MO();

    void SetRS(const double& rs);
    void SetPO(const double& po);
    void SetBO(const double& bo);
    void SetMO(const double& mo);

    void InitVariables();

protected:
    double rs, po, bo, mo;
};

}}}

#endif // PVTODATA_H
