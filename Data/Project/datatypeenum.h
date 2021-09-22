#ifndef DATATYPEENUM_H
#define DATATYPEENUM_H

#include <qobject.h>

#include <data_global.h>

namespace BlackOil {
namespace Data {
namespace Project {

class DATA_EXPORT DataTypeEnum : public QObject
{
    Q_OBJECT
    Q_ENUMS(DataType)
public:
    explicit DataTypeEnum(QObject *parent = nullptr);

    enum DataType { INTEGER, DOUBLE };
};

}}}

#endif // DATATYPEENUM_H
