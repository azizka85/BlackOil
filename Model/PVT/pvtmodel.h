#ifndef PVTMODEL_H
#define PVTMODEL_H

#include <qobject.h>

#include <projectdata.h>

#include <pvtregionmodel.h>
#include <pvtomodel.h>
#include <pvtgmodel.h>

#include <model_global.h>

using namespace BlackOil::Data::Project;

namespace BlackOil {
namespace Model {
namespace PVT {

class MODEL_EXPORT PVTModel : public QObject
{
    Q_OBJECT
public:
    explicit PVTModel(ProjectData *projectData, QObject *parent = nullptr);

    void InitVariables();
    void ProcessData();
    void ProcessBeforeSave();

    PVTRegionModel *PVTRegion();
    PVTOModel *PVTO();
    PVTGModel *PVTG();

protected:
    ProjectData *projectData;

    PVTRegionModel *pvtRegion;
    PVTOModel *pvto;
    PVTGModel *pvtg;
};

}}}

#endif // PVTMODEL_H
