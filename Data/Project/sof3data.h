#ifndef SOF3DATA_H
#define SOF3DATA_H

#include <qvariant.h>

#include <data_global.h>

namespace BlackOil {
namespace Data {
namespace Project {

class DATA_EXPORT SOF3Data
{
public:
    SOF3Data();

    double SO();

    QVariant KrOW();
    QVariant KrOGWC();

    void SetSO(const double& so);
    void SetKrOW(const QVariant& krow);
    void SetKrOGWC(const QVariant& krogwc);

    void InitVariables();

protected:
    double so;
    QVariant krow, krogwc;
};

}}}

#endif // SOF3DATA_H
