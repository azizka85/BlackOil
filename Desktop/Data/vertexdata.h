#ifndef VERTEXDATA_H
#define VERTEXDATA_H

#include <qvector3d.h>

#include <desktop_global.h>

namespace BlackOil {
namespace Desktop {
namespace Data {

class DESKTOP_EXPORT VertexData
{
public:
    VertexData(const QVector3D &position, const QVector3D &normal, const QVector3D &index);

    QVector3D position;
    QVector3D normal;
    QVector3D index;
};

}}}

#endif // VERTEXDATA_H
