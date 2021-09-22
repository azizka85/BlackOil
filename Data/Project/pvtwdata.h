#ifndef PVTWDATA_H
#define PVTWDATA_H

#include <qvariant.h>

#include <data_global.h>

namespace BlackOil {
namespace Data {
namespace Project {

class DATA_EXPORT PVTWData
{
public:
    PVTWData();

    QVariant PWRef();
    QVariant BWRef();
    QVariant CW();
    QVariant MWRef();
    QVariant CVW();

    void SetPWRef(const QVariant& pwRef);
    void SetBWRef(const QVariant& bwRef);
    void SetCW(const QVariant& cw);
    void SetMWRef(const QVariant& mwRef);
    void SetCVW(const QVariant& cvw);

    void InitVariables();

protected:
    QVariant pwRef, bwRef, cw, mwRef, cvw;
};

}}}

#endif // PVTWDATA_H
