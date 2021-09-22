#include "vertexdata.h"

namespace BlackOil {
namespace Desktop {
namespace Data {

VertexData::VertexData(const QVector3D &position, const QVector3D &normal, const QVector3D &index)
{
    this->position = position;
    this->normal = normal;
    this->index = index;
}

}}}
