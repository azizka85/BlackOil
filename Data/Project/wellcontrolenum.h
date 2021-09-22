#ifndef WELLCONTROLENUM_H
#define WELLCONTROLENUM_H

#include <qobject.h>

#include <data_global.h>

namespace BlackOil {
namespace Data {
namespace Project {

class DATA_EXPORT WellControlEnum : public QObject
{
    Q_OBJECT
    Q_ENUMS(WellControl)
public:
    explicit WellControlEnum(QObject *parent = nullptr);

    enum WellControl { ORAT = 0, WRAT = 1, GRAT = 2, LRAT = 3, RESV = 4, BHP = 5, RATE = 6 };
};

}}}

#endif // WELLCONTROLENUM_H
