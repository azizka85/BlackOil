#ifndef IRREVERSIBLEENUM_H
#define IRREVERSIBLEENUM_H

#include <qobject.h>

#include <data_global.h>

namespace BlackOil {
namespace Data {
namespace Project {

class DATA_EXPORT IrreversibleEnum : public QObject
{
    Q_OBJECT
    Q_ENUMS(Irreversible)
public:
    explicit IrreversibleEnum(QObject *parent = nullptr);

    enum Irreversible { REVERS = 0, IRREVERS = 1 };
};

}}}

#endif // IRREVERSIBLEENUM_H
