#include "sfmodel.h"

namespace BlackOil {
namespace Model {
namespace SF {

SFModel::SFModel(ProjectData *projectData, QObject *parent) : QObject(parent)
{
    this->projectData = projectData;

    sfRegion = new SFRegionModel(projectData, this);

    swof = new SWOFModel(projectData, this);
    sgof = new SGOFModel(projectData, this);

    rpm = new RPMEnum(this);
}

SWOFModel *SFModel::SWOF()
{
    return swof;
}

SGOFModel *SFModel::SGOF()
{
    return sgof;
}

SFRegionModel *SFModel::SFRegion()
{
    return sfRegion;
}

RPMEnum *SFModel::RPM()
{
    return rpm;
}

void SFModel::InitVariables()
{
    swof->InitVariables();
    sgof->InitVariables();

    sfRegion->InitVariables();
}

void SFModel::ProcessData()
{
    swof->ProcessData();
    sgof->ProcessData();

    sfRegion->ProcessData();
}

void SFModel::ProcessBeforeSave()
{
    swof->ProcessBeforeSave();
    sgof->ProcessBeforeSave();

    sfRegion->ProcessBeforeSave();
}

}}}
