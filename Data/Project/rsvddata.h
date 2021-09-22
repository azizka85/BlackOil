#ifndef RSVDDATA_H
#define RSVDDATA_H

#include <data_global.h>

namespace BlackOil {
namespace Data {
namespace Project {

class DATA_EXPORT RSVDData
{
public:
    RSVDData();

    double Depth();
    double RS();

    void SetDepth(const double& depth);
    void SetRS(const double& rs);

    void InitVariables();

protected:
    double depth, rs;
};

}}}

#endif // RSVDDATA_H
