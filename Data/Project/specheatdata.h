#ifndef SPECHEATDATA_H
#define SPECHEATDATA_H

#include <data_global.h>

namespace BlackOil {
namespace Data {
namespace Project {

class DATA_EXPORT SPECHEATData
{
public:
    SPECHEATData();

    double T();
    double CO();
    double CW();
    double CG();

    void SetT(const double& t);
    void SetCO(const double& co);
    void SetCW(const double& cw);
    void SetCG(const double& cg);

    void InitVariables();

protected:
    double t, co, cw, cg;
};

}}}

#endif // SPECHEATDATA_H
