#ifndef WATVISCTDATA_H
#define WATVISCTDATA_H

#include <data_global.h>

namespace BlackOil {
namespace Data {
namespace Project {

class DATA_EXPORT WATVISCTData
{
public:
    WATVISCTData();

    double T();
    double MW();

    void SetT(const double& t);
    void SetMW(const double& mw);

    void InitVariables();

private:
    double t, mw;
};

}}}

#endif // WATVISCTDATA_H
