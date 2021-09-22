#ifndef SWFNDATA_H
#define SWFNDATA_H

#include <qvariant.h>

#include <data_global.h>

namespace BlackOil {
namespace Data {
namespace Project {

class DATA_EXPORT SWFNData
{
public:
    SWFNData();

    double SW();

    QVariant KrW();
    QVariant Pc();

    void SetSW(const double &sw);

    void SetKrW(const QVariant &krw);
    void SetPc(const QVariant &pc);

    void InitVariables();

protected:
    double sw;
    QVariant krw, pc;};

}}}

#endif // SWFNDATA_H
