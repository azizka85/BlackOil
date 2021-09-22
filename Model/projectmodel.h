#ifndef PROJECTMODEL_H
#define PROJECTMODEL_H

#include <qobject.h>
#include <qstring.h>

#include <arraynamesenum.h>
#include <datatypeenum.h>
#include <projectdata.h>
#include <eclipsefilereader.h>

#include <operatormodel.h>

#include <gridmodel.h>

#include <wellsmodel.h>
#include <sfmodel.h>
#include <pvtmodel.h>

#include <projectloadingstateenum.h>

#include <model_global.h>

using namespace BlackOil::Data::Project;
using namespace BlackOil::Data::Readers;
using namespace BlackOil::Model::Wells;
using namespace BlackOil::Model::SF;
using namespace BlackOil::Model::PVT;

namespace BlackOil {
namespace Model {

class MODEL_EXPORT ProjectModel : public QObject
{
    Q_OBJECT
public:
    explicit ProjectModel(QObject *parent = nullptr);

    int LoadingState();
    QString &ProjectPath();

    QString &Title();

    int Nx();
    int Ny();
    int Nz();

    OperatorModel *Operator();

    GridModel *Grid();

    WellsModel *Wells();
    SFModel *SF();
    PVTModel *PVT();    

    void SetProjectPath(const QString &projectPath);

    void InitVariables();    
    void ProcessData();
    void ProcessBeforeSave();

    void Load();

protected:
    void InitProjectReaderVariables();

public slots:
    void SetLoadingState(int loadingState);

signals:
    void LoadingStateChanged(int loadingState);

protected:
    int loadingState;
    QString projectPath;

    ProjectData data;
    EclipseFileReader reader;

    OperatorModel *operatorModel;

    GridModel *gridModel;

    WellsModel *wells;
    SFModel *sf;
    PVTModel *pvt;    
};

}}

#endif // PROJECTMODEL_H
