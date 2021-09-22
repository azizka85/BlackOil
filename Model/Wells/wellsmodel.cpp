#include "wellsmodel.h"

namespace BlackOil {
namespace Model {
namespace Wells {

WellsModel::WellsModel(ProjectData *projectData, QObject *parent) : QObject(parent)
{
    this->projectData = projectData;

    welspecs = new WELSPECSModel(projectData, this);
    compdat = new COMPDATModel(projectData, welspecs, this);
    wconprod = new WCONPRODModel(projectData, welspecs, this);
    wconinje = new WCONINJEModel(projectData, welspecs, this);
}

WELSPECSModel *WellsModel::WELSPECS()
{
    return welspecs;
}

COMPDATModel *WellsModel::COMPDAT()
{
    return compdat;
}

WCONPRODModel *WellsModel::WCONPROD()
{
    return wconprod;
}

WCONINJEModel *WellsModel::WCONINJE()
{
    return wconinje;
}

void WellsModel::InitVariables()
{
    welspecs->InitVariables();
    compdat->InitVariables();
    wconprod->InitVariables();
    wconinje->InitVariables();
}

void WellsModel::ProcessData()
{
    welspecs->ProcessData();
    compdat->ProcessData();
    wconprod->ProcessData();
    wconinje->ProcessData();
}

void WellsModel::ProcessBeforeSave()
{
    welspecs->ProcessBeforeSave();
    compdat->ProcessBeforeSave();
    wconprod->ProcessBeforeSave();
    wconinje->ProcessBeforeSave();
}

}}}
