#ifndef AXESDATA_H
#define AXESDATA_H

#include <qvector3d.h>

#include <desktop_global.h>

namespace BlackOil {
namespace Desktop {
namespace Data {

class DESKTOP_EXPORT AxesData
{
public:
    AxesData(const QVector3D &position, const QVector3D &color);

    QVector3D position;
    QVector3D color;
};

}}}

#endif // AXESDATA_H
