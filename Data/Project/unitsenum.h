#ifndef UNITSENUM_H
#define UNITSENUM_H

#include <qobject.h>

#include <data_global.h>

namespace BlackOil {
namespace Data {
namespace Project {

class DATA_EXPORT UnitsEnum : public QObject
{
    Q_OBJECT
    Q_ENUMS(Units)
public:
    explicit UnitsEnum(QObject *parent = nullptr);

    enum Units { METRIC = 0, FIELD = 1, LAB = 2 };
};

}}}

#endif // UNITSENUM_H
