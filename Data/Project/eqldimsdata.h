#ifndef EQLDIMSDATA_H
#define EQLDIMSDATA_H

#include <qvariant.h>

#include <data_global.h>

namespace BlackOil {
namespace Data {
namespace Project {

class DATA_EXPORT EQLDIMSData
{
public:
    EQLDIMSData();

    QVariant NTEQUL() const;

    void SetNTEQUL(const QVariant &ntEQUL);

    void InitVariables();

protected:
    QVariant ntEQUL;
};

}}}

#endif // EQLDIMSDATA_H
