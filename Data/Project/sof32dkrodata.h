#ifndef SOF32DKRODATA_H
#define SOF32DKRODATA_H

#include <vector>

#include <data_global.h>

using namespace std;

namespace BlackOil {
namespace Data {
namespace Project {

class DATA_EXPORT SOF32DKrOData
{
public:
    SOF32DKrOData();

    double SG();
    vector<double> &KrO();

    void SetSG(const double& sg);

    void InitVariables();

protected:
    double sg;
    vector<double> kro;
};

}}}

#endif // SOF32DKRODATA_H
