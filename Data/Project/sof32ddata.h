#ifndef SOF32DDATA_H
#define SOF32DDATA_H

#include <vector>

#include <sof32dkrodata.h>

#include <data_global.h>

namespace BlackOil {
namespace Data {
namespace Project {

class DATA_EXPORT SOF32DData
{
public:
    SOF32DData();

    vector<double> &SW();
    vector<SOF32DKrOData> &SOF32DKrO();

    void InitVariables();

protected:
    vector<double> sw;
    vector<SOF32DKrOData> sof32dKrO;
};

}}}

#endif // SOF32DDATA_H
