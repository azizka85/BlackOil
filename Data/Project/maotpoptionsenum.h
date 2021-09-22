#ifndef MAOTPOPTIONSENUM_H
#define MAOTPOPTIONSENUM_H

#include <qobject.h>

#include <data_global.h>

namespace BlackOil {
namespace Data {
namespace Project {

class DATA_EXPORT MAOTPOptionsEnum : public QObject
{
    Q_OBJECT
    Q_ENUMS(MAOTPOptions)
public:
    explicit MAOTPOptionsEnum(QObject *parent = nullptr);

    enum MAOTPOptions {PRESSURE = 0, STRESS = 1};
};

}}}

#endif // MAOTPOPTIONSENUM_H
