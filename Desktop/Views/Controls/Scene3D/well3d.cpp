#include "well3d.h"

namespace BlackOil {
namespace Desktop {
namespace Views {
namespace Controls {
namespace Scene3D {

Well3D::Well3D(): indexBuffer(QOpenGLBuffer::IndexBuffer)
{
    InitVariables();
}

void Well3D::InitWell(QVector<float> &levels)
{
    ClearData();
}

void Well3D::RefreshWellBuffers()
{
    vertexBuffer.destroy();
    vertexBuffer.create();
    vertexBuffer.bind();
    vertexBuffer.allocate(vertexes.constData(), vertexes.size() * sizeof (VertexData));
    vertexBuffer.release();

    indexBuffer.destroy();
    indexBuffer.create();
    indexBuffer.bind();
    indexBuffer.allocate(indexes.constData(), indexes.size() * sizeof (GLuint));
    indexBuffer.release();
}

void Well3D::Draw(QOpenGLShaderProgram *shader, QMatrix4x4 transformMatrix, float scaleX, float scaleY, float scaleZ)
{

}

void Well3D::HandleContextDestroyed()
{
    vertexBuffer.destroy();
    indexBuffer.destroy();
}

void Well3D::ClearData()
{
    vertexes.clear();
    indexes.clear();
}

void Well3D::InitVariables()
{
    ClearData();
}

}}}}}
