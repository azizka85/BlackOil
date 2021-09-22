#ifndef WELL3D_H
#define WELL3D_H

#include <math.h>

#include <qmatrix4x4.h>

#include <qvector.h>

#include <qopenglbuffer.h>
#include <qopenglshaderprogram.h>

#include <vertexdata.h>

#include <desktop_global.h>

using namespace BlackOil::Desktop::Data;

namespace BlackOil {
namespace Desktop {
namespace Views {
namespace Controls {
namespace Scene3D {

class DESKTOP_EXPORT Well3D
{
public:
    Well3D();

    void InitWell(QVector<float> &levels);
    void RefreshWellBuffers();

    void Draw(QOpenGLShaderProgram* shader, QMatrix4x4 transformMatrix, float scaleX, float scaleY, float scaleZ);

    void HandleContextDestroyed();

    void ClearData();
    void InitVariables();

protected:
    QVector<VertexData> vertexes;
    QVector<GLuint> indexes;

    QOpenGLBuffer vertexBuffer;
    QOpenGLBuffer indexBuffer;
};

}}}}}

#endif // WELL3D_H
