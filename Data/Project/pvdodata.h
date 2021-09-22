#ifndef PVDODATA_H
#define PVDODATA_H

#include <data_global.h>

namespace BlackOil {
namespace Data {
namespace Project {

class DATA_EXPORT PVDOData
{
public:
    PVDOData();

    double PO();
    double BO();
    double MO();

    void SetPO(const double& po);
    void SetBO(const double& bo);
    void SetMO(const double& mo);

    void InitVariables();

protected:
    double po, bo, mo;
};

}}}

#endif // PVDODATA_H
