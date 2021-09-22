#ifndef SFREGIONMODEL_H
#define SFREGIONMODEL_H

#include <qabstractitemmodel.h>

#include <defaultvalues.h>
#include <projectdata.h>

#include <model_global.h>

using namespace BlackOil::Data::Project;

namespace BlackOil {
namespace Model {
namespace SF {

class MODEL_EXPORT SFRegionModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit SFRegionModel(ProjectData *projectData, QObject *parent = nullptr);

    void InitVariables();
    void ProcessData();
    void ProcessBeforeSave();

protected:
    ProjectData *projectData;

    // QAbstractItemModel interface
public:
    int rowCount(const QModelIndex &) const override;
    QVariant data(const QModelIndex &index, int role) const override;
};

}}}

#endif // SFREGIONMODEL_H
