#ifndef MODELSENUM_H
#define MODELSENUM_H

#include <qobject.h>

#include <data_global.h>

namespace BlackOil {
namespace Data {
namespace Project {

class DATA_EXPORT ModelsEnum : public QObject
{
    Q_OBJECT
    Q_ENUMS(Models)
public:
    explicit ModelsEnum(QObject *parent = nullptr);

    enum Models { TwoPhase = 0, ThreePhase = 1 };
};

}}}

#endif // MODELSENUM_H
