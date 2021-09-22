#include "projectmodel.h"

namespace BlackOil {
namespace Model {

ProjectModel::ProjectModel(QObject *parent) : QObject(parent)
{
    operatorModel = new OperatorModel(&data, this);

    gridModel = new GridModel(&data, operatorModel, this);

    wells = new WellsModel(&data, this);
    sf = new SFModel(&data, this);
    pvt = new PVTModel(&data, this);

    InitVariables();
}

int ProjectModel::LoadingState()
{
    return loadingState;
}

QString &ProjectModel::ProjectPath()
{
    return projectPath;
}

QString &ProjectModel::Title()
{
    return data.Title();
}

int ProjectModel::Nx()
{
    return data.Nx();
}

int ProjectModel::Ny()
{
    return data.Ny();
}

int ProjectModel::Nz()
{
    return data.Nz();
}

OperatorModel *ProjectModel::Operator()
{
    return operatorModel;
}

GridModel *ProjectModel::Grid()
{
    return gridModel;
}

WellsModel *ProjectModel::Wells()
{
    return wells;
}

SFModel *ProjectModel::SF()
{
    return sf;
}

PVTModel *ProjectModel::PVT()
{
    return pvt;
}

void ProjectModel::SetProjectPath(const QString &projectPath)
{
    this->projectPath = projectPath;
}

void ProjectModel::InitVariables()
{    
    projectPath = "";

    InitProjectReaderVariables();    

    SetLoadingState(ProjectLoadingStateEnum::FinishInitializing);
}

void ProjectModel::ProcessData()
{
    SetLoadingState(ProjectLoadingStateEnum::Processing);

    operatorModel->ProcessData();

    gridModel->ProcessData();

    wells->ProcessData();
    sf->ProcessData();
    pvt->ProcessData();
}

void ProjectModel::ProcessBeforeSave()
{
    operatorModel->ProcessBeforeSave();

    gridModel->ProcessBeforeSave();

    wells->ProcessBeforeSave();
    sf->ProcessBeforeSave();
    pvt->ProcessBeforeSave();
}

void ProjectModel::Load()
{
    SetLoadingState(ProjectLoadingStateEnum::StartLoading);

    InitProjectReaderVariables();

    reader.Load(data, projectPath);
}

void ProjectModel::InitProjectReaderVariables()
{
    data.InitVariables();
    reader.InitVariables();

    operatorModel->InitVariables();

    gridModel->InitVariables();

    wells->InitVariables();
    sf->InitVariables();       
    pvt->InitVariables();
}

void ProjectModel::SetLoadingState(int loadingState)
{
    if(this->loadingState != loadingState)
    {
        this->loadingState = loadingState;

        emit LoadingStateChanged(loadingState);
    }
}

}}
