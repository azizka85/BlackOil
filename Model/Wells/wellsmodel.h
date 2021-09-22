#ifndef WELLSMODEL_H
#define WELLSMODEL_H

#include <qobject.h>

#include <projectdata.h>

#include <welspecsmodel.h>
#include <compdatmodel.h>
#include <wconprodmodel.h>
#include <wconinjemodel.h>

#include <model_global.h>

using namespace BlackOil::Data::Project;

namespace BlackOil {
namespace Model {
namespace Wells {

class MODEL_EXPORT WellsModel : public QObject
{
    Q_OBJECT
public:
    explicit WellsModel(ProjectData *projectData, QObject *parent = nullptr);

    WELSPECSModel *WELSPECS();
    COMPDATModel *COMPDAT();
    WCONPRODModel *WCONPROD();
    WCONINJEModel *WCONINJE();

    void InitVariables();
    void ProcessData();
    void ProcessBeforeSave();

protected:
    ProjectData *projectData;
    WELSPECSModel *welspecs;
    COMPDATModel *compdat;
    WCONPRODModel *wconprod;
    WCONINJEModel *wconinje;
};

}}}

#endif // WELLSMODEL_H
