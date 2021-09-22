#ifndef AXES3D_H
#define AXES3D_H

#include <math.h>

#include <qmatrix4x4.h>

#include <qvector.h>

#include <qopenglbuffer.h>
#include <qopenglshaderprogram.h>

#include <axesdata.h>

#include <desktop_global.h>

using namespace BlackOil::Desktop::Data;

namespace BlackOil {
namespace Desktop {
namespace Views {
namespace Controls {
namespace Scene3D {

class DESKTOP_EXPORT Axes3D
{
public:
    Axes3D();

    void InitAxes();
    void TranslateAxes(double scaleX, double scaleY, double scaleZ);
    void RefreshAxesBuffers();

    void Draw(QOpenGLShaderProgram* shader, QMatrix4x4 transformMatrix, float axesLength, float scaleX, float scaleY, float scaleZ);

    void HandleContextDestroyed();
    void ClearData();

protected:
    float translateAxesX, translateAxesY, translateAxesZ;

    QVector<AxesData> axesVertexes;
    QVector<GLuint> axesIndexes;

    QOpenGLBuffer axesVertexBuffer;
    QOpenGLBuffer axesIndexBuffer;
};

}}}}}

#endif // AXES3D_H
