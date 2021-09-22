#ifndef OPERATORTYPEENUM_H
#define OPERATORTYPEENUM_H

#include <qobject.h>

#include <data_global.h>

namespace BlackOil {
namespace Data {
namespace Project {

class DATA_EXPORT OperatorTypeEnum : public QObject
{
    Q_OBJECT
    Q_ENUMS(OperatorType)
public:
    explicit OperatorTypeEnum(QObject *parent = nullptr);

    enum OperatorType { EQUALS, COPY, ADD, MULTIPLY };
};

}}}

#endif // OPERATORTYPEENUM_H
