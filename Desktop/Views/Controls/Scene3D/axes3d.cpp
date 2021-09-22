#include "axes3d.h"

namespace BlackOil {
namespace Desktop {
namespace Views {
namespace Controls {
namespace Scene3D {

Axes3D::Axes3D(): axesIndexBuffer(QOpenGLBuffer::IndexBuffer)
{

}

void Axes3D::InitAxes()
{
    float l = 1 / 2.0f;
    float rp = l / 20;
    float rs = rp;
    float r = rp / 5;

    // Init axes
    QVector3D xColor(1, 0, 0);
    QVector3D yColor(0, 1, 0);
    QVector3D zColor(0, 0, 1);
    QVector3D oColor(0.5, 0.5, 0.5);

    QVector3D pxh(l, 0, 0);
    QVector3D pxo(l - 2*rp, 0, 0);

    QVector3D pyh(0, l, 0);
    QVector3D pyo(0, l - 2*rp, 0);

    QVector3D pzh(0, 0, l);
    QVector3D pzo(0, 0, l - 2*rp);

    for(int i = 0; i < 24; i++)
    {
        QVector3D p1(rp*cos(M_PI*i/12), rp*sin(M_PI*i/12), l - 2*rp);
        QVector3D p2(rp*cos(M_PI*(i+1)/12), rp*sin(M_PI*(i+1)/12), l - 2*rp);

        QVector3D p3(r*cos(M_PI*i/12), r*sin(M_PI*i/12), 0);
        QVector3D p4(r*cos(M_PI*i/12), r*sin(M_PI*i/12), l - 2*rp);
        QVector3D p5(r*cos(M_PI*(i+1)/12), r*sin(M_PI*(i+1)/12), l - 2*rp);
        QVector3D p6(r*cos(M_PI*(i+1)/12), r*sin(M_PI*(i+1)/12), 0);

        QVector3D p7(rp*cos(M_PI*i/12), l - 2*rp, rp*sin(M_PI*i/12));
        QVector3D p8(rp*cos(M_PI*(i+1)/12), l - 2*rp, rp*sin(M_PI*(i+1)/12));

        QVector3D p9(r*cos(M_PI*i/12), 0, r*sin(M_PI*i/12));
        QVector3D p10(r*cos(M_PI*i/12), l - 2*rp, r*sin(M_PI*i/12));
        QVector3D p11(r*cos(M_PI*(i+1)/12), l - 2*rp, r*sin(M_PI*(i+1)/12));
        QVector3D p12(r*cos(M_PI*(i+1)/12), 0, r*sin(M_PI*(i+1)/12));

        QVector3D p13(l - 2*rp, rp*cos(M_PI*i/12), rp*sin(M_PI*i/12));
        QVector3D p14(l - 2*rp, rp*cos(M_PI*(i+1)/12), rp*sin(M_PI*(i+1)/12));

        QVector3D p15(0, r*cos(M_PI*i/12), r*sin(M_PI*i/12));
        QVector3D p16(l - 2*rp, r*cos(M_PI*i/12), r*sin(M_PI*i/12));
        QVector3D p17(l - 2*rp, r*cos(M_PI*(i+1)/12), r*sin(M_PI*(i+1)/12));
        QVector3D p18(0, r*cos(M_PI*(i+1)/12), r*sin(M_PI*(i+1)/12));

        axesVertexes.append(AxesData(pzh, zColor));
        axesVertexes.append(AxesData(p1, zColor));
        axesVertexes.append(AxesData(p2, zColor));

        axesVertexes.append(AxesData(pzo, zColor));
        axesVertexes.append(AxesData(p2, zColor));
        axesVertexes.append(AxesData(p1, zColor));

        axesVertexes.append(AxesData(p3, zColor));
        axesVertexes.append(AxesData(p6, zColor));
        axesVertexes.append(AxesData(p4, zColor));

        axesVertexes.append(AxesData(p4, zColor));
        axesVertexes.append(AxesData(p6, zColor));
        axesVertexes.append(AxesData(p5, zColor));

        axesVertexes.append(AxesData(pyh, yColor));
        axesVertexes.append(AxesData(p7, yColor));
        axesVertexes.append(AxesData(p8, yColor));

        axesVertexes.append(AxesData(pyo, yColor));
        axesVertexes.append(AxesData(p8, yColor));
        axesVertexes.append(AxesData(p7, yColor));

        axesVertexes.append(AxesData(p9, yColor));
        axesVertexes.append(AxesData(p12, yColor));
        axesVertexes.append(AxesData(p10, yColor));

        axesVertexes.append(AxesData(p10, yColor));
        axesVertexes.append(AxesData(p12, yColor));
        axesVertexes.append(AxesData(p11, yColor));

        axesVertexes.append(AxesData(pxh, xColor));
        axesVertexes.append(AxesData(p13, xColor));
        axesVertexes.append(AxesData(p14, xColor));

        axesVertexes.append(AxesData(pxo, xColor));
        axesVertexes.append(AxesData(p14, xColor));
        axesVertexes.append(AxesData(p13, xColor));

        axesVertexes.append(AxesData(p15, xColor));
        axesVertexes.append(AxesData(p18, xColor));
        axesVertexes.append(AxesData(p16, xColor));

        axesVertexes.append(AxesData(p16, xColor));
        axesVertexes.append(AxesData(p18, xColor));
        axesVertexes.append(AxesData(p17, xColor));

        for(int j = 0; j < 36; j++) axesIndexes.append(36*i + j);
    }

    for(int i = 0; i < 24; i++)
    {
        for(int j = 0; j < 24; j++)
        {
            QVector3D p1(rs*cos(-M_PI/2 + M_PI*i/24)*cos(M_PI*j/12), rs*cos(-M_PI/2 + M_PI*i/24)*sin(M_PI*j/12), rs*sin(-M_PI/2 + M_PI*i/24));
            QVector3D p2(rs*cos(-M_PI/2 + M_PI*i/24)*cos(M_PI*(j+1)/12), rs*cos(-M_PI/2 + M_PI*i/24)*sin(M_PI*(j+1)/12), rs*sin(-M_PI/2 + M_PI*i/24));
            QVector3D p3(rs*cos(-M_PI/2 + M_PI*(i+1)/24)*cos(M_PI*j/12), rs*cos(-M_PI/2 + M_PI*(i+1)/24)*sin(M_PI*j/12), rs*sin(-M_PI/2 + M_PI*(i+1)/24));
            QVector3D p4(rs*cos(-M_PI/2 + M_PI*(i+1)/24)*cos(M_PI*(j+1)/12), rs*cos(-M_PI/2 + M_PI*(i+1)/24)*sin(M_PI*(j+1)/12), rs*sin(-M_PI/2 + M_PI*(i+1)/24));

            int n = axesVertexes.size();

            axesVertexes.append(AxesData(p1, oColor));
            axesVertexes.append(AxesData(p2, oColor));
            axesVertexes.append(AxesData(p3, oColor));

            axesVertexes.append(AxesData(p2, oColor));
            axesVertexes.append(AxesData(p4, oColor));
            axesVertexes.append(AxesData(p3, oColor));

            for(int k = 0; k < 6; k++) axesIndexes.append(n + k);
        }
    }
}

void Axes3D::TranslateAxes(double scaleX, double scaleY, double scaleZ)
{
    float l = 1 / 2.0f;

    translateAxesX = -l * scaleX;
    translateAxesY = -l * scaleY;
    translateAxesZ = -l * scaleZ;
}

void Axes3D::RefreshAxesBuffers()
{
    axesVertexBuffer.destroy();
    axesVertexBuffer.create();
    axesVertexBuffer.bind();
    axesVertexBuffer.allocate(axesVertexes.constData(), axesVertexes.size() * sizeof (AxesData));
    axesVertexBuffer.release();

    axesIndexBuffer.destroy();
    axesIndexBuffer.create();
    axesIndexBuffer.bind();
    axesIndexBuffer.allocate(axesIndexes.constData(), axesIndexes.size() * sizeof (GLuint));
    axesIndexBuffer.release();
}

void Axes3D::Draw(QOpenGLShaderProgram *shader, QMatrix4x4 transformMatrix, float axesLength, float scaleX, float scaleY, float scaleZ)
{
    shader->bind();
    axesVertexBuffer.bind();
    axesIndexBuffer.bind();

    QMatrix4x4 translateMatrix;
    translateMatrix.setToIdentity();
    translateMatrix.translate(scaleX * translateAxesX, scaleY * translateAxesY, scaleZ * translateAxesZ);

    shader->setUniformValue("u_transformMatrix", transformMatrix * translateMatrix);
    shader->setUniformValue("u_axesLength", axesLength);

    int offset = 0;

    int vertexLoc = shader->attributeLocation("a_position");
    shader->enableAttributeArray(vertexLoc);
    shader->setAttributeBuffer(vertexLoc, GL_FLOAT, offset, 3, sizeof (AxesData));

    offset += sizeof (QVector3D);

    int colorLoc = shader->attributeLocation("a_color");
    shader->enableAttributeArray(colorLoc);
    shader->setAttributeBuffer(colorLoc, GL_FLOAT, offset, 3, sizeof (AxesData));

    glDrawElements(GL_TRIANGLES, axesIndexBuffer.size(), GL_UNSIGNED_INT, nullptr);

    axesIndexBuffer.release();
    axesVertexBuffer.release();
    shader->release();
}

void Axes3D::HandleContextDestroyed()
{
    axesVertexBuffer.destroy();
    axesIndexBuffer.destroy();
}

void Axes3D::ClearData()
{
    translateAxesX = 0;
    translateAxesY = 0;
    translateAxesZ = 0;
}

}}}}}
