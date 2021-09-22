#ifndef DIRECTIONALENUM_H
#define DIRECTIONALENUM_H

#include <qobject.h>

#include <data_global.h>

namespace BlackOil {
namespace Data {
namespace Project {

class DATA_EXPORT DirectionalEnum : public QObject
{
    Q_OBJECT
    Q_ENUMS(Directional)
public:
    explicit DirectionalEnum(QObject *parent = nullptr);

    enum Directional { NODIR = 0, DIRECT = 1 };
};

}}}

#endif // DIRECTIONALENUM_H
