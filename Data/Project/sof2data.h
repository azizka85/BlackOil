#ifndef SOF2DATA_H
#define SOF2DATA_H

#include <data_global.h>

namespace BlackOil {
namespace Data {
namespace Project {

class DATA_EXPORT SOF2Data
{
public:
    SOF2Data();

    double SO();
    double KrO();

    void SetSO(const double& so);
    void SetKrO(const double& kro);

    void InitVariables();

protected:
    double so, kro;
};

}}}

#endif // SOF2DATA_H
