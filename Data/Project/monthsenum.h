#ifndef MONTHSENUM_H
#define MONTHSENUM_H

#include <qobject.h>

#include <data_global.h>

namespace BlackOil {
namespace Data {
namespace Project {

class DATA_EXPORT MonthsEnum : public QObject
{
    Q_OBJECT
    Q_ENUMS(Months)
public:
    explicit MonthsEnum(QObject *parent = nullptr);

    enum Months { JAN = 1, FEB = 2, MAR = 3, APR = 4, MAY = 5, JUN = 6, JUL = 7, AUG = 8, SEP = 9, OCT = 10, NOV = 11, DEC = 12 };
};

}}}

#endif // MONTHSENUM_H
