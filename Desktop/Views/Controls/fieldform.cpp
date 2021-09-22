#include "fieldform.h"
#include "ui_fieldform.h"

namespace BlackOil {
namespace Desktop {
namespace Views {
namespace Controls {

FieldForm::FieldForm(ProjectModel *project, QWidget *parent) :
    QOpenGLWidget(parent),
    fieldIndexBuffer(QOpenGLBuffer::IndexBuffer), meshIndexBuffer(QOpenGLBuffer::IndexBuffer), boxIndexBuffer(QOpenGLBuffer::IndexBuffer),
    ui(new Ui::FieldForm)
{
    this->project = project;

    InitVariables();

    ui->setupUi(this);   

    auto label1 = new QLabel(tr("toto1"), this);
    label1->setTextInteractionFlags(Qt::LinksAccessibleByMouse|Qt::TextSelectableByMouse);
    label1->setStyleSheet("color: rgb(255, 255, 255);");

    auto label2 = new QLabel(tr("toto2"), this);
    label2->setTextInteractionFlags(Qt::LinksAccessibleByMouse|Qt::TextSelectableByMouse);
    label2->setStyleSheet("color: rgb(255, 255, 255);");

    auto label3 = new QLabel(tr("toto3"), this);
    label3->setTextInteractionFlags(Qt::LinksAccessibleByMouse|Qt::TextSelectableByMouse);
    label3->setStyleSheet("color: rgb(255, 255, 255);");

    ui->LegendLayout->addWidget(label1, 1, 0, Qt::AlignLeft | Qt::AlignVCenter);
    ui->LegendLayout->addWidget(label2, 1, 1, Qt::AlignLeft | Qt::AlignVCenter);
    ui->LegendLayout->addWidget(label3, 1, 1, Qt::AlignRight | Qt::AlignVCenter);

    WidgetHelper::SetWidgetSpan(ui->LegendColor, ui->LegendLayout, 1, 2);            
}

FieldForm::~FieldForm()
{
    delete ui;
}

int FieldForm::MeshWidth()
{
    return meshWidth;
}

float FieldForm::PaletteTransparency()
{
    return paletteTransparency;
}

float FieldForm::AxesLength()
{
    return axesLength;
}

bool FieldForm::DisplayMesh()
{
    return displayMesh;
}

bool FieldForm::DisplayPalette()
{
    return displayPalette;
}

bool FieldForm::DisplayLegend()
{
    return ui->Legend->isVisible();
}

bool FieldForm::DisplayBox()
{
    return displayBox;
}

bool FieldForm::DisplayAxes()
{
    return displayAxes;
}

bool FieldForm::LightEnabled()
{
    return lightEnabled;
}

bool FieldForm::FieldSelectable()
{
    return fieldSelectable;
}

int FieldForm::AxisOfRotation()
{
    return axisOfRotation;
}

float FieldForm::ScaleX()
{
    return scaleX;
}

float FieldForm::ScaleY()
{
    return scaleY;
}

float FieldForm::ScaleZ()
{
    return scaleZ;
}

void FieldForm::SetMeshWidth(int meshWidth)
{
    if(this->meshWidth != meshWidth)
    {
        this->meshWidth = meshWidth;

        emit MeshWidthChanged(meshWidth);

        update();
    }
}

void FieldForm::SetPaletteTransparency(float paletteTransparency)
{
    if(this->paletteTransparency != paletteTransparency)
    {
        this->paletteTransparency = paletteTransparency;

        emit PaletteTransparencyChanged(paletteTransparency);

        update();
    }
}

void FieldForm::SetAxesLength(double axesLength)
{
    if(this->axesLength != axesLength)
    {
        this->axesLength = axesLength;

        emit AxesLengthChanged(axesLength);

        update();
    }
}

void FieldForm::SetDisplayMesh(bool displayMesh)
{
    if(this->displayMesh != displayMesh)
    {
        this->displayMesh = displayMesh;

        emit DisplayMeshChanged(displayMesh);

        update();
    }
}

void FieldForm::SetDisplayPalette(bool displayPalette)
{
    if(this->displayPalette != displayPalette)
    {
        this->displayPalette = displayPalette;

        emit DisplayPaletteChanged(displayPalette);

        update();
    }
}

void FieldForm::SetDisplayLegend(bool displayLegend)
{
    if(ui->Legend->isVisible() != displayLegend)
    {
        ui->Legend->setVisible(displayLegend);

        emit DisplayLegendChanged(displayLegend);
    }
}

void FieldForm::SetDisplayBox(bool displayBox)
{
    if(this->displayBox != displayBox)
    {
        this->displayBox = displayBox;

        emit DisplayBoxChanged(displayBox);

        update();
    }
}

void FieldForm::SetDisplayAxes(bool displayAxes)
{
    if(this->displayAxes != displayAxes)
    {
        this->displayAxes = displayAxes;

        emit DisplayAxesChanged(displayAxes);

        update();
    }
}

void FieldForm::SetLightEnabled(bool lightEnabled)
{
    if(this->lightEnabled != lightEnabled)
    {
        this->lightEnabled = lightEnabled;

        emit LightEnabledChanged(lightEnabled);

        update();
    }
}

void FieldForm::SetFieldSelectable(bool fieldSelectable)
{
    if(this->fieldSelectable != fieldSelectable)
    {
        this->fieldSelectable = fieldSelectable;

        emit FieldSelectableChanged(fieldSelectable);

        update();
    }
}

void FieldForm::SetAxisOfRotation(int axisOfRotation)
{
    if(this->axisOfRotation != axisOfRotation)
    {
        this->axisOfRotation = axisOfRotation;

        emit AxisOfRotationChanged(axisOfRotation);
    }
}

void FieldForm::SetScaleX(double scaleX)
{
    if(this->scaleX != scaleX)
    {
        this->scaleX = scaleX;

        emit ScaleXChanged(scaleX);

        update();
    }
}

void FieldForm::SetScaleY(double scaleY)
{
    if(this->scaleY != scaleY)
    {
        this->scaleY = scaleY;

        emit ScaleYChanged(scaleY);

        update();
    }
}

void FieldForm::SetScaleZ(double scaleZ)
{
    if(this->scaleZ != scaleZ)
    {
        this->scaleZ = scaleZ;

        emit ScaleZChanged(scaleZ);

        update();
    }
}

void FieldForm::SetXYViewAxis()
{
    SetDefaultPosition();

    rot = QQuaternion::fromAxisAndAngle(0, 0, 0, 0);

    update();
}

void FieldForm::SetXZViewAxis()
{
    SetDefaultPosition();

    rot = QQuaternion::fromAxisAndAngle(1, 0, 0, 90);

    update();
}

void FieldForm::SetYZViewAxis()
{
    SetDefaultPosition();

    rot = QQuaternion::fromAxisAndAngle(0, 1, 0, 90);

    update();
}

void FieldForm::HandleContextDestroyed()
{
    makeCurrent();

    delete fieldShader;
    delete meshShader;
    delete selectFieldShader;
    delete axesShader;

    fieldVertexBuffer.destroy();
    fieldIndexBuffer.destroy();
    meshIndexBuffer.destroy();

    boxVertexBuffer.destroy();
    boxIndexBuffer.destroy();

    axes3d.HandleContextDestroyed();

    doneCurrent();
}

void FieldForm::InitVariables()
{
    geometryChanged = dataChanged = false;

    selectedFieldIndex = QVector3D(0, 0, 0);

    axesLength = 0.2;

    meshWidth = 2;
    paletteTransparency = 1;

    fieldSelectable = true;

    lightEnabled = true;

    displayMesh = displayPalette = displayBox = false;

    axisOfRotation = RotationAxisEnum::OXY;

    scaleX = scaleY = scaleZ = 1;

    SetDefaultPosition();

    axes3d.InitAxes();

    ClearData();    
}

void FieldForm::SetDefaultPosition()
{
    x = y = 0;
    z = -1.5;

    rot = QQuaternion::fromAxisAndAngle(1, 0, 0, 90);
}

void FieldForm::ClearData()
{
    blocks.clear();

    fieldVertexes.clear();
    fieldIndexes.clear();
    meshIndexes.clear();

    boxVertexes.clear();
    boxIndexes.clear();

    axes3d.ClearData();
}

void FieldForm::InitShaders()
{
    fieldShader = new QOpenGLShaderProgram(this);
    fieldShader->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/Shaders/field-vertex.vsh");
    fieldShader->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/Shaders/field-fragment.fsh");
    fieldShader->link();

    meshShader = new QOpenGLShaderProgram(this);
    meshShader->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/Shaders/grid-vertex.vsh");
    meshShader->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/Shaders/grid-fragment.fsh");
    meshShader->link();

    selectFieldShader = new QOpenGLShaderProgram(this);
    selectFieldShader->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/Shaders/select-vertex.vsh");
    selectFieldShader->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/Shaders/select-fragment.fsh");
    selectFieldShader->link();

    axesShader = new QOpenGLShaderProgram(this);
    axesShader->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/Shaders/axes-vertex.vsh");
    axesShader->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/Shaders/axes-fragment.fsh");
    axesShader->link();
}

void FieldForm::InitGeometry()
{
    for(int i = 0; i < blocks.size(); i++)
    {
        QVector3D index = CalcRGBIndex(i+1);

        auto &block = blocks[i];

        QVector3D p8 = QVector3D(block.P8().X(), block.P8().Y(), block.P8().Z());
        QVector3D p7 = QVector3D(block.P7().X(), block.P7().Y(), block.P7().Z());
        QVector3D p6 = QVector3D(block.P6().X(), block.P6().Y(), block.P6().Z());
        QVector3D p5 = QVector3D(block.P5().X(), block.P5().Y(), block.P5().Z());
        QVector3D p4 = QVector3D(block.P4().X(), block.P4().Y(), block.P4().Z());
        QVector3D p3 = QVector3D(block.P3().X(), block.P3().Y(), block.P3().Z());
        QVector3D p2 = QVector3D(block.P2().X(), block.P2().Y(), block.P2().Z());
        QVector3D p1 = QVector3D(block.P1().X(), block.P1().Y(), block.P1().Z());

        QVector3D a = p5 - p7;
        QVector3D b = p8 - p7;

        QVector3D n = QVector3D::crossProduct(a, b);

        fieldVertexes.append(VertexData(p7, n, index));
        fieldVertexes.append(VertexData(p5, n, index));
        fieldVertexes.append(VertexData(p8, n, index));
        fieldVertexes.append(VertexData(p6, n, index));

        a = p6 - p8;
        b = p4 - p8;

        n = QVector3D::crossProduct(a, b);

        fieldVertexes.append(VertexData(p8, n, index));
        fieldVertexes.append(VertexData(p6, n, index));
        fieldVertexes.append(VertexData(p4, n, index));
        fieldVertexes.append(VertexData(p2, n, index));

        a = p4 - p8;
        b = p7 - p8;

        n = QVector3D::crossProduct(a, b);

        fieldVertexes.append(VertexData(p8, n, index));
        fieldVertexes.append(VertexData(p4, n, index));
        fieldVertexes.append(VertexData(p7, n, index));
        fieldVertexes.append(VertexData(p3, n, index));

        a = p2 - p4;
        b = p3 - p4;

        n = QVector3D::crossProduct(a, b);

        fieldVertexes.append(VertexData(p4, n, index));
        fieldVertexes.append(VertexData(p2, n, index));
        fieldVertexes.append(VertexData(p3, n, index));
        fieldVertexes.append(VertexData(p1, n, index));

        a = p3 - p7;
        b = p5 - p7;

        n = QVector3D::crossProduct(a, b);

        fieldVertexes.append(VertexData(p7, n, index));
        fieldVertexes.append(VertexData(p3, n, index));
        fieldVertexes.append(VertexData(p5, n, index));
        fieldVertexes.append(VertexData(p1, n, index));

        a = p1 - p5;
        b = p6 - p5;

        n = QVector3D::crossProduct(a, b);

        fieldVertexes.append(VertexData(p5, n, index));
        fieldVertexes.append(VertexData(p1, n, index));
        fieldVertexes.append(VertexData(p6, n, index));
        fieldVertexes.append(VertexData(p2, n, index));

        for(int j = 0; j < 24; j += 4)
        {
            fieldIndexes.append(24*i + j + 0);
            fieldIndexes.append(24*i + j + 1);
            fieldIndexes.append(24*i + j + 2);

            fieldIndexes.append(24*i + j + 2);
            fieldIndexes.append(24*i + j + 1);
            fieldIndexes.append(24*i + j + 3);

            meshIndexes.append(24*i + j + 0);
            meshIndexes.append(24*i + j + 1);

            meshIndexes.append(24*i + j + 0);
            meshIndexes.append(24*i + j + 2);

            meshIndexes.append(24*i + j + 1);
            meshIndexes.append(24*i + j + 3);

            meshIndexes.append(24*i + j + 2);
            meshIndexes.append(24*i + j + 3);
        }
    }
}

void FieldForm::InitBox(double scaleX, double scaleY, double scaleZ)
{
    float sizeDiv2 = 1 / 2.0f;

    boxVertexes.append(QVector3D(-sizeDiv2*scaleX, sizeDiv2*scaleY, sizeDiv2*scaleZ));
    boxVertexes.append(QVector3D(-sizeDiv2*scaleX, -sizeDiv2*scaleY, sizeDiv2*scaleZ));
    boxVertexes.append(QVector3D(sizeDiv2*scaleX, sizeDiv2*scaleY, sizeDiv2*scaleZ));
    boxVertexes.append(QVector3D(sizeDiv2*scaleX, -sizeDiv2*scaleY, sizeDiv2*scaleZ));

    boxVertexes.append(QVector3D(sizeDiv2*scaleX, sizeDiv2*scaleY, sizeDiv2*scaleZ));
    boxVertexes.append(QVector3D(sizeDiv2*scaleX, -sizeDiv2*scaleY, sizeDiv2*scaleZ));
    boxVertexes.append(QVector3D(sizeDiv2*scaleX, sizeDiv2*scaleY, -sizeDiv2*scaleZ));
    boxVertexes.append(QVector3D(sizeDiv2*scaleX, -sizeDiv2*scaleY, -sizeDiv2*scaleZ));

    boxVertexes.append(QVector3D(sizeDiv2*scaleX, sizeDiv2*scaleY, sizeDiv2*scaleZ));
    boxVertexes.append(QVector3D(sizeDiv2*scaleX, sizeDiv2*scaleY, -sizeDiv2*scaleZ));
    boxVertexes.append(QVector3D(-sizeDiv2*scaleX, sizeDiv2*scaleY, sizeDiv2*scaleZ));
    boxVertexes.append(QVector3D(-sizeDiv2*scaleX, sizeDiv2*scaleY, -sizeDiv2*scaleZ));

    boxVertexes.append(QVector3D(sizeDiv2*scaleX, sizeDiv2*scaleY, -sizeDiv2*scaleZ));
    boxVertexes.append(QVector3D(sizeDiv2*scaleX, -sizeDiv2*scaleY, -sizeDiv2*scaleZ));
    boxVertexes.append(QVector3D(-sizeDiv2*scaleX, sizeDiv2*scaleY, -sizeDiv2*scaleZ));
    boxVertexes.append(QVector3D(-sizeDiv2*scaleX, -sizeDiv2*scaleY, -sizeDiv2*scaleZ));

    boxVertexes.append(QVector3D(-sizeDiv2*scaleX, sizeDiv2*scaleY, sizeDiv2*scaleZ));
    boxVertexes.append(QVector3D(-sizeDiv2*scaleX, sizeDiv2*scaleY, -sizeDiv2*scaleZ));
    boxVertexes.append(QVector3D(-sizeDiv2*scaleX, -sizeDiv2*scaleY, sizeDiv2*scaleZ));
    boxVertexes.append(QVector3D(-sizeDiv2*scaleX, -sizeDiv2*scaleY, -sizeDiv2*scaleZ));

    boxVertexes.append(QVector3D(-sizeDiv2*scaleX, -sizeDiv2*scaleY, sizeDiv2*scaleZ));
    boxVertexes.append(QVector3D(-sizeDiv2*scaleX, -sizeDiv2*scaleY, -sizeDiv2*scaleZ));
    boxVertexes.append(QVector3D(sizeDiv2*scaleX, -sizeDiv2*scaleY, sizeDiv2*scaleZ));
    boxVertexes.append(QVector3D(sizeDiv2*scaleX, -sizeDiv2*scaleY, -sizeDiv2*scaleZ));

    for(int i = 0; i < 24; i += 4)
    {
        boxIndexes.append(i + 0);
        boxIndexes.append(i + 1);

        boxIndexes.append(i + 0);
        boxIndexes.append(i + 2);

        boxIndexes.append(i + 1);
        boxIndexes.append(i + 3);

        boxIndexes.append(i + 2);
        boxIndexes.append(i + 3);
    }
}

void FieldForm::InitScene()
{
    project->SetLoadingState(ProjectLoadingStateEnum::Drawing);

    ClearData();

    double xMin = 0;
    double xMax = 0;

    double yMin = 0;
    double yMax = 0;

    double zMin = 0;
    double zMax = 0;

    double scaleX = 1;
    double scaleY = 1;
    double scaleZ = 1;

    QVector<bool> existBlock;
    QVector<bool> drawBlock;

    project->Grid()->CalculateExistBlockArray(existBlock);
    project->Grid()->CalculateDrawBlockArray(existBlock, drawBlock);
    project->Grid()->CalculateDisplayBlocks(drawBlock, blocks, xMin, xMax, yMin, yMax, zMin, zMax);
    project->Grid()->NormalizeDisplayBlocks(xMin, xMax, yMin, yMax, zMin, zMax, scaleX, scaleY, scaleZ, blocks);

    double adjustX = ISEQUAL(scaleX, 0) ? 0 : scaleX < 0.5 ? 0.5 / scaleX : 1;
    double adjustY = ISEQUAL(scaleY, 0) ? 0 : scaleY < 0.5 ? 0.5 / scaleY : 1;
    double adjustZ = ISEQUAL(scaleZ, 0) ? 0 : scaleZ < 0.5 ? 0.5 / scaleZ : 1;

    InitGeometry();
    InitBox(scaleX, scaleY, scaleZ);
    axes3d.TranslateAxes(scaleX, scaleY, scaleZ);

    geometryChanged = dataChanged = true;

    SetScaleX(adjustX);
    SetScaleY(adjustY);
    SetScaleZ(adjustZ);    
}

void FieldForm::ClearScene()
{
    ClearData();

    geometryChanged = dataChanged = true;

    update();
}

QVector3D FieldForm::CalcRGBIndex(int i)
{
    int r = i / (256 * 256);

    i = i - r * 256 * 256;

    int g = i / 256;
    int b = i % 256;

    return QVector3D(r / 255.0, g / 255.0, b / 255.0);
}

int FieldForm::CalcBlockIndex(unsigned char r, unsigned char g, unsigned char b)
{
    return 256*256*r + 256*g + b;
}

void FieldForm::SelectFieldIndex(int x, int y)
{
    glEnable(GL_DEPTH_TEST);

    glViewport(0, 0, width(), height());
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    selectFieldShader->bind();
    fieldVertexBuffer.bind();
    fieldIndexBuffer.bind();

    QMatrix4x4 modelViewMatrix;
    modelViewMatrix.setToIdentity();
    modelViewMatrix.translate(this->x, this->y, z);
    modelViewMatrix.rotate(rot);

    selectFieldShader->setUniformValue("u_projectionMatrix", projectionMatrix);
    selectFieldShader->setUniformValue("u_modelViewMatrix", modelViewMatrix);
    selectFieldShader->setUniformValue("u_scaleX", scaleX);
    selectFieldShader->setUniformValue("u_scaleY", scaleY);
    selectFieldShader->setUniformValue("u_scaleZ", scaleZ);

    int offset = 0;

    int vertexLoc = selectFieldShader->attributeLocation("a_position");
    selectFieldShader->enableAttributeArray(vertexLoc);
    selectFieldShader->setAttributeBuffer(vertexLoc, GL_FLOAT, offset, 3, sizeof (VertexData));

    offset += 2*sizeof (QVector3D);

    int indexLoc = selectFieldShader->attributeLocation("a_index");
    selectFieldShader->enableAttributeArray(indexLoc);
    selectFieldShader->setAttributeBuffer(indexLoc, GL_FLOAT, offset, 3, sizeof (VertexData));

    glDrawElements(GL_TRIANGLES, fieldIndexBuffer.size(), GL_UNSIGNED_INT, nullptr);

    fieldIndexBuffer.release();
    fieldVertexBuffer.release();
    selectFieldShader->release();

    GLint viewport[4];
    unsigned char result[4];

    glGetIntegerv(GL_VIEWPORT, viewport);
    glReadPixels(x, viewport[3] - y, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, &result);

    glDisable(GL_DEPTH_TEST);

    selectedFieldIndex = QVector3D(result[0]/255.0, result[1]/255.0, result[2]/255.0);

    int blockIndex = CalcBlockIndex(result[0], result[1], result[2]) - 1;

    Block block;

    if(blockIndex >= 0 && blockIndex < blocks.size()) block = blocks[blockIndex];

    emit SelectedBlockChanged(block.I(), block.J(), block.K());
}

void FieldForm::RefreshGeometryBuffers()
{
    fieldVertexBuffer.destroy();
    fieldVertexBuffer.create();
    fieldVertexBuffer.bind();
    fieldVertexBuffer.allocate(fieldVertexes.constData(), fieldVertexes.size() * sizeof (VertexData));
    fieldVertexBuffer.release();

    fieldIndexBuffer.destroy();
    fieldIndexBuffer.create();
    fieldIndexBuffer.bind();
    fieldIndexBuffer.allocate(fieldIndexes.constData(), fieldIndexes.size() * sizeof (GLuint));
    fieldIndexBuffer.release();

    meshIndexBuffer.destroy();
    meshIndexBuffer.create();
    meshIndexBuffer.bind();
    meshIndexBuffer.allocate(meshIndexes.constData(), meshIndexes.size() * sizeof (GLuint));
    meshIndexBuffer.release();
}

void FieldForm::RefreshBoxBuffers()
{
    boxVertexBuffer.destroy();
    boxVertexBuffer.create();
    boxVertexBuffer.bind();
    boxVertexBuffer.allocate(boxVertexes.constData(), boxVertexes.size() * sizeof (QVector3D));
    boxVertexBuffer.release();

    boxIndexBuffer.destroy();
    boxIndexBuffer.create();
    boxIndexBuffer.bind();
    boxIndexBuffer.allocate(boxIndexes.constData(), boxIndexes.size() * sizeof (GLuint));
    boxIndexBuffer.release();
}

void FieldForm::RefreshDataBuffers()
{

}

void FieldForm::initializeGL()
{
    glClearColor(0, 0, 0, 1);

    glEnable(GL_DEPTH_TEST);
    // glEnable(GL_CULL_FACE);

    // glEnable(GL_ALPHA_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    InitShaders();

    geometryChanged = dataChanged = true;

    connect(context(), SIGNAL(aboutToBeDestroyed()), this, SLOT(HandleContextDestroyed()));
}

void FieldForm::resizeGL(int w, int h)
{
    float aspect = (float)w/h;

    projectionMatrix.setToIdentity();
    projectionMatrix.perspective(45, aspect, 0.1, 100);
}

void FieldForm::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    QMatrix4x4 modelViewMatrix;
    modelViewMatrix.setToIdentity();
    modelViewMatrix.translate(x, y, z);
    modelViewMatrix.rotate(rot);

    if(geometryChanged)
    {
        RefreshGeometryBuffers();
        RefreshBoxBuffers();
        axes3d.RefreshAxesBuffers();

        geometryChanged = false;
    }

    if(dataChanged)
    {
        RefreshDataBuffers();

        dataChanged = false;
    }

    // Draw box
    if(displayBox)
    {
        meshShader->bind();
        boxVertexBuffer.bind();
        boxIndexBuffer.bind();

        meshShader->setUniformValue("u_projectionMatrix", projectionMatrix);
        meshShader->setUniformValue("u_modelViewMatrix", modelViewMatrix);
        meshShader->setUniformValue("u_scaleX", scaleX);
        meshShader->setUniformValue("u_scaleY", scaleY);
        meshShader->setUniformValue("u_scaleZ", scaleZ);

        int vertexLoc = meshShader->attributeLocation("a_position");
        meshShader->enableAttributeArray(vertexLoc);
        meshShader->setAttributeBuffer(vertexLoc, GL_FLOAT, 0, 3, sizeof (QVector3D));

        glLineWidth(meshWidth);

        glDrawElements(GL_LINES, boxIndexBuffer.size(), GL_UNSIGNED_INT, nullptr);

        boxIndexBuffer.release();
        boxVertexBuffer.release();
        meshShader->release();
    }

    // Draw axes
    if(displayAxes)
        axes3d.Draw(axesShader, projectionMatrix * modelViewMatrix, axesLength, scaleX, scaleY, scaleZ);

    // Draw mesh
    if(displayMesh)
    {
        meshShader->bind();
        fieldVertexBuffer.bind();
        meshIndexBuffer.bind();

        meshShader->setUniformValue("u_projectionMatrix", projectionMatrix);
        meshShader->setUniformValue("u_modelViewMatrix", modelViewMatrix);
        meshShader->setUniformValue("u_scaleX", scaleX);
        meshShader->setUniformValue("u_scaleY", scaleY);
        meshShader->setUniformValue("u_scaleZ", scaleZ);

        int vertexLoc = meshShader->attributeLocation("a_position");
        meshShader->enableAttributeArray(vertexLoc);
        meshShader->setAttributeBuffer(vertexLoc, GL_FLOAT, 0, 3, sizeof (VertexData));

        glLineWidth(meshWidth);

        glDrawElements(GL_LINES, meshIndexBuffer.size(), GL_UNSIGNED_INT, nullptr);

        meshIndexBuffer.release();
        fieldVertexBuffer.release();
        meshShader->release();
    }

    // Draw field
    if(displayPalette)
    {
        fieldShader->bind();
        fieldVertexBuffer.bind();
        fieldIndexBuffer.bind();

        fieldShader->setUniformValue("u_projectionMatrix", projectionMatrix);
        fieldShader->setUniformValue("u_modelViewMatrix", modelViewMatrix);
        fieldShader->setUniformValue("u_lightEnabled", lightEnabled);
        fieldShader->setUniformValue("u_selectedIndex", selectedFieldIndex);
        fieldShader->setUniformValue("u_paletteTransparency", paletteTransparency);
        fieldShader->setUniformValue("u_scaleX", scaleX);
        fieldShader->setUniformValue("u_scaleY", scaleY);
        fieldShader->setUniformValue("u_scaleZ", scaleZ);
        fieldShader->setUniformValue("u_color", QVector3D(0.25, 0.75, 0.25));

        int offset = 0;

        int vertexLoc = fieldShader->attributeLocation("a_position");
        fieldShader->enableAttributeArray(vertexLoc);
        fieldShader->setAttributeBuffer(vertexLoc, GL_FLOAT, offset, 3, sizeof (VertexData));

        offset += sizeof (QVector3D);

        int normLoc = fieldShader->attributeLocation("a_normal");
        fieldShader->enableAttributeArray(normLoc);
        fieldShader->setAttributeBuffer(normLoc, GL_FLOAT, offset, 3, sizeof (VertexData));

        offset += sizeof (QVector3D);

        int indexLoc = fieldShader->attributeLocation("a_index");
        fieldShader->enableAttributeArray(indexLoc);
        fieldShader->setAttributeBuffer(indexLoc, GL_FLOAT, offset, 3, sizeof (VertexData));

        glDrawElements(GL_TRIANGLES, fieldIndexBuffer.size(), GL_UNSIGNED_INT, nullptr);

        fieldIndexBuffer.release();
        fieldVertexBuffer.release();
        fieldShader->release();
    }
}

void FieldForm::mousePressEvent(QMouseEvent *event)
{
    if(event->buttons() == Qt::LeftButton)
    {
        mousePosition = QVector2D(event->localPos());

        selectedFieldIndex = QVector3D();

        if(fieldSelectable) SelectFieldIndex(event->x(), event->y());
    }

    event->accept();

    update();
}

void FieldForm::mouseMoveEvent(QMouseEvent *event)
{
    QVector2D diff = QVector2D(event->localPos()) - mousePosition;

    mousePosition = QVector2D(event->localPos());

    if(event->buttons() == (Qt::LeftButton | Qt::RightButton))
    {
        x += diff.x() / 1000;
        y -= diff.y() / 1000;
    }
    else if(event->buttons() == Qt::LeftButton)
    {
        float angle = diff.length() / 2;
        QVector3D axis;

        switch (axisOfRotation)
        {
            case RotationAxisEnum::OXY:
                axis = QVector3D(diff.y(), diff.x(), 0);
                break;
            case RotationAxisEnum::OX:
                axis = QVector3D(diff.y(), 0, 0);
                break;
            case RotationAxisEnum::OY:
                axis = QVector3D(0, diff.x(), 0);
                break;
            case RotationAxisEnum::OZ:
                axis = QVector3D(0, 0, -diff.x());
                break;
        }

        rot = QQuaternion::fromAxisAndAngle(axis, angle) * rot;
    }
    else if(event->buttons() == Qt::MiddleButton)
    {
        float angle = diff.length() / 2;
        QVector3D axis = QVector3D(0, 0, -diff.x());

        rot = QQuaternion::fromAxisAndAngle(axis, angle) * rot;
    }

    update();
}

void FieldForm::wheelEvent(QWheelEvent *event)
{
    if(event->delta() > 0)
        z += 0.25;
    else if(event->delta() < 0)
        z -= 0.25;

    update();
}

}}}}
