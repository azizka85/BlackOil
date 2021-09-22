#ifndef IHBOPTIONSENUM_H
#define IHBOPTIONSENUM_H

#include <qobject.h>

#include <data_global.h>

namespace BlackOil {
namespace Data {
namespace Project {

class DATA_EXPORT IHBOptionsEnum : public QObject
{
    Q_OBJECT
    Q_ENUMS(IHBOptions)
public:
    explicit IHBOptionsEnum(QObject *parent = nullptr);

    enum IHBOptions {DEFLATION = 0, ELASTIC = 1};
};

}}}

#endif // IHBOPTIONSENUM_H
