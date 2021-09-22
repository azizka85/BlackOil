#include "axesdata.h"

namespace BlackOil {
namespace Desktop {
namespace Data {

AxesData::AxesData(const QVector3D &position, const QVector3D &color)
{
    this->position = position;
    this->color = color;
}

}}}
