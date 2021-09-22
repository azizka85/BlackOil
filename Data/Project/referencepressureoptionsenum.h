#ifndef REFERENCEPRESSUREOPTIONSENUM_H
#define REFERENCEPRESSUREOPTIONSENUM_H

#include <qobject.h>

#include <data_global.h>

namespace BlackOil {
namespace Data {
namespace Project {

class DATA_EXPORT ReferencePressureOptionsEnum : public QObject
{
    Q_OBJECT
    Q_ENUMS(ReferencePressureOptions)
public:
    explicit ReferencePressureOptionsEnum(QObject *parent = nullptr);

    enum ReferencePressureOptions {NOSTORE = 0, STORE = 1};
};

}}}

#endif // REFERENCEPRESSUREOPTIONSENUM_H
