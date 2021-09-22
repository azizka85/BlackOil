#include "pvtmodel.h"

namespace BlackOil {
namespace Model {
namespace PVT {

PVTModel::PVTModel(ProjectData *projectData, QObject *parent) : QObject(parent)
{
    this->projectData = projectData;

    pvtRegion = new PVTRegionModel(projectData, this);
    pvto = new PVTOModel(projectData, this);
    pvtg = new PVTGModel(projectData, this);
}

void PVTModel::InitVariables()
{
    pvtRegion->InitVariables();
    pvto->InitVariables();
    pvtg->InitVariables();
}

void PVTModel::ProcessData()
{
    pvtRegion->ProcessData();
    pvto->ProcessData();
    pvtg->ProcessData();
}

void PVTModel::ProcessBeforeSave()
{
    pvtRegion->ProcessBeforeSave();
    pvto->ProcessBeforeSave();
    pvtg->ProcessBeforeSave();
}

PVTRegionModel *PVTModel::PVTRegion()
{
    return pvtRegion;
}

PVTOModel *PVTModel::PVTO()
{
    return pvto;
}

PVTGModel *PVTModel::PVTG()
{
    return pvtg;
}

}}}
