#ifndef TABDIMSDATA_H
#define TABDIMSDATA_H

#include <qvariant.h>

#include <data_global.h>

namespace BlackOil {
namespace Data {
namespace Project {

class DATA_EXPORT TABDIMSData
{
public:
    TABDIMSData();

    QVariant NTSFUN();
    QVariant NTPVT();
    QVariant NSSFUN();

    void SetNTSFUN(const QVariant &ntSFUN);
    void SetNTPVT(const QVariant &ntPVT);
    void SetNSSFUN(const QVariant &nsSFUN);

    void InitVariables();

protected:
    QVariant ntSFUN, ntPVT, nsSFUN;
};

}}}

#endif // TABDIMSDATA_H
