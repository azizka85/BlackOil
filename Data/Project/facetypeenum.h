#ifndef FACETYPEENUM_H
#define FACETYPEENUM_H

#include <qobject.h>

#include <data_global.h>

namespace BlackOil {
namespace Data {
namespace Project {

class DATA_EXPORT FaceTypeEnum : public QObject
{
    Q_OBJECT
    Q_ENUMS(FaceType)
public:
    explicit FaceTypeEnum(QObject *parent = nullptr);

    enum FaceType { Im = 0, Ip = 1, Jm = 2, Jp = 3, Km = 4, Kp = 5 };
};

}}}

#endif // FACETYPEENUM_H
