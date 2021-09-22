#ifndef WELLSTATUSENUM_H
#define WELLSTATUSENUM_H

#include <qobject.h>

#include <data_global.h>

namespace BlackOil {
namespace Data {
namespace Project {

class DATA_EXPORT WellStatusEnum : public QObject
{
    Q_OBJECT
    Q_ENUMS(WellStatus)
public:
    explicit WellStatusEnum(QObject *parent = nullptr);

    enum WellStatus { AUTO = 0, OPEN = 1, STOP = 2, SHUT = 3 };
};

}}}

#endif // WELLSTATUSENUM_H
