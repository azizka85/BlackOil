#ifndef ROCKOPTSDATA_H
#define ROCKOPTSDATA_H

#include <qvariant.h>

#include <data_global.h>

namespace BlackOil {
namespace Data {
namespace Project {

class DATA_EXPORT ROCKOPTSData
{
public:
    ROCKOPTSData();

    QVariant MAOTP();
    QVariant RPO();
    QVariant RegionOption();
    QVariant IHBOption();

    void SetMAOTP(const QVariant& maotp);
    void SetRPO(const QVariant& rpo);
    void SetRegionOption(const QVariant& regionOption);
    void SetIHBOption(const QVariant& ihbOption);

    void InitVariables();

protected:
    QVariant maotp, rpo, regionOption, ihbOption;
};

}}}

#endif // ROCKOPTSDATA_H
