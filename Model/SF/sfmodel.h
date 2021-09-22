#ifndef SFMODEL_H
#define SFMODEL_H

#include <qobject.h>

#include <rpmenum.h>
#include <projectdata.h>

#include <sfregionmodel.h>
#include <swofmodel.h>
#include <sgofmodel.h>

#include <model_global.h>

using namespace BlackOil::Data::Project;

namespace BlackOil {
namespace Model {
namespace SF {

class MODEL_EXPORT SFModel : public QObject
{
    Q_OBJECT
public:
    explicit SFModel(ProjectData *projectData, QObject *parent = nullptr);

    SWOFModel *SWOF();
    SGOFModel *SGOF();
    SFRegionModel *SFRegion();
    RPMEnum *RPM();

    void InitVariables();
    void ProcessData();
    void ProcessBeforeSave();

protected:
    ProjectData *projectData;

    SFRegionModel *sfRegion;
    SWOFModel *swof;
    SGOFModel *sgof;

    RPMEnum *rpm;
};

}}}

#endif // SFMODEL_H
