#ifndef REGIONOPTIONSENUM_H
#define REGIONOPTIONSENUM_H

#include <qobject.h>

#include <data_global.h>

namespace BlackOil {
namespace Data {
namespace Project {

class DATA_EXPORT RegionOptionsEnum : public QObject
{
    Q_OBJECT
    Q_ENUMS(RegionOptions)
public:
    explicit RegionOptionsEnum(QObject *parent = nullptr);

    enum RegionOptions {PVTNUM = 0, SATNUM = 1};
};

}}}

#endif // REGIONOPTIONSENUM_H
