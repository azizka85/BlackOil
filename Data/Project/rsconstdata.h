#ifndef RSCONSTDATA_H
#define RSCONSTDATA_H

#include <data_global.h>

namespace BlackOil {
namespace Data {
namespace Project {

class DATA_EXPORT RSCONSTData
{
public:
    RSCONSTData();

    double RS();
    double PBub();

    void SetRS(const double& rs);
    void SetPBub(const double& pBub);

    void InitVariables();

protected:
    double rs, pBub;
};

}}}

#endif // RSCONSTDATA_H
