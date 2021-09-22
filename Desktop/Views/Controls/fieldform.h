#ifndef FIELDFORM_H
#define FIELDFORM_H

#include <qmatrix4x4.h>

#include <qevent.h>

#include <qopenglwidget.h>
#include <qopenglcontext.h>
#include <qopenglbuffer.h>
#include <qopenglshaderprogram.h>

#include <axes3d.h>

#include <block.h>

#include <projectloadingstateenum.h>
#include <projectmodel.h>

#include <vertexdata.h>

#include <rotationaxisenum.h>

#include <widgethelper.h>

#include <desktop_global.h>

using namespace BlackOil::Data::Grid;

using namespace BlackOil::Model;

using namespace BlackOil::Desktop::Data;
using namespace BlackOil::Desktop::Models;
using namespace BlackOil::Desktop::Helpers;
using namespace BlackOil::Desktop::Views::Controls::Scene3D;

namespace Ui {
class FieldForm;
}

namespace BlackOil {
namespace Desktop {
namespace Views {
namespace Controls {

class DESKTOP_EXPORT FieldForm : public QOpenGLWidget
{
    Q_OBJECT

public:
    explicit FieldForm(ProjectModel *project, QWidget *parent = nullptr);
    ~FieldForm();    

    int MeshWidth();
    float PaletteTransparency();

    float AxesLength();

    bool DisplayMesh();
    bool DisplayPalette();
    bool DisplayLegend();
    bool DisplayBox();
    bool DisplayAxes();

    bool LightEnabled();

    bool FieldSelectable();

    int AxisOfRotation();

    float ScaleX();
    float ScaleY();
    float ScaleZ();

public slots:
    void SetMeshWidth(int meshWidth);
    void SetPaletteTransparency(float paletteTransparency);

    void SetAxesLength(double axesLength);

    void SetDisplayMesh(bool displayMesh);
    void SetDisplayPalette(bool displayPalette);
    void SetDisplayLegend(bool displayLegend);
    void SetDisplayBox(bool displayBox);
    void SetDisplayAxes(bool displayAxes);

    void SetLightEnabled(bool lightEnabled);

    void SetFieldSelectable(bool fieldSelectable);

    void SetAxisOfRotation(int axisOfRotation);

    void SetScaleX(double scaleX);
    void SetScaleY(double scaleY);
    void SetScaleZ(double scaleZ);

    void SetXYViewAxis();
    void SetXZViewAxis();
    void SetYZViewAxis();

    void HandleContextDestroyed();

    void InitVariables();
    void SetDefaultPosition();
    void ClearData();

    void InitScene();
    void ClearScene();

signals:
    void SelectedBlockChanged(int i, int j, int k);

    void MeshWidthChanged(int meshWidth);
    void PaletteTransparencyChanged(float paletteTransparency);

    void AxesLengthChanged(double axesLength);

    void DisplayMeshChanged(bool displayMesh);
    void DisplayPaletteChanged(bool displayPalette);
    void DisplayLegendChanged(bool displayLegend);
    void DisplayBoxChanged(bool displayBox);
    void DisplayAxesChanged(bool displayAxes);

    void LightEnabledChanged(bool lightEnabled);

    void FieldSelectableChanged(bool fieldSelectable);

    void AxisOfRotationChanged(int axisOfRotation);

    void ScaleXChanged(double scaleX);
    void ScaleYChanged(double scaleY);
    void ScaleZChanged(double scaleZ);

protected:
    QVector3D CalcRGBIndex(int i);
    int CalcBlockIndex(unsigned char r, unsigned char g, unsigned char b);

    void InitShaders();

    void InitGeometry();
    void InitBox(double scaleX, double scaleY, double scaleZ);

    void SelectFieldIndex(int x, int y);

    void RefreshGeometryBuffers();
    void RefreshBoxBuffers();    
    void RefreshDataBuffers();

protected:
    ProjectModel *project;

    bool geometryChanged, dataChanged;

    QVector3D selectedFieldIndex;

    bool contextDestroyed;

    float x, y, z;
    float axesLength;    
    int meshWidth;
    float paletteTransparency;
    bool fieldSelectable;
    bool lightEnabled;
    bool displayMesh, displayPalette, displayBox, displayAxes;
    int axisOfRotation;
    float scaleX, scaleY, scaleZ;

    QVector<Block> blocks;

    QVector<VertexData> fieldVertexes;
    QVector<GLuint> fieldIndexes;
    QVector<GLuint> meshIndexes;

    QVector<QVector3D> boxVertexes;
    QVector<GLuint> boxIndexes;

    QMatrix4x4 projectionMatrix;

    QOpenGLShaderProgram *fieldShader;
    QOpenGLShaderProgram *meshShader;
    QOpenGLShaderProgram *selectFieldShader;
    QOpenGLShaderProgram *axesShader;

    QOpenGLBuffer fieldVertexBuffer;
    QOpenGLBuffer fieldIndexBuffer;
    QOpenGLBuffer meshIndexBuffer;

    QOpenGLBuffer boxVertexBuffer;
    QOpenGLBuffer boxIndexBuffer;

    QQuaternion rot;

    QVector2D mousePosition;

    Axes3D axes3d;

    Ui::FieldForm *ui;

    // QOpenGLWidget interface
protected:
    void initializeGL() override;
    void resizeGL(int w, int h) override;
    void paintGL() override;

    // QWidget interface
protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;    
};

}}}}

#endif // FIELDFORM_H
