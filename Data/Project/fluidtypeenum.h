#ifndef FLUIDTYPEENUM_H
#define FLUIDTYPEENUM_H

#include <qobject.h>

#include <data_global.h>

namespace BlackOil {
namespace Data {
namespace Project {

class DATA_EXPORT FluidTypeEnum : public QObject
{
    Q_OBJECT
    Q_ENUMS(FluidType)
public:
    explicit FluidTypeEnum(QObject *parent = nullptr);

    enum FluidType { WATER = 0, GAS = 1, OIL = 2 };
};

}}}

#endif // FLUIDTYPEENUM_H
