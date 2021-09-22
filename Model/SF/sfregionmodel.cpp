#include "sfregionmodel.h"

namespace BlackOil {
namespace Model {
namespace SF {

SFRegionModel::SFRegionModel(ProjectData *projectData, QObject *parent) : QAbstractListModel(parent)
{
    this->projectData = projectData;
}

void SFRegionModel::InitVariables()
{
    beginResetModel();
    endResetModel();
}

void SFRegionModel::ProcessData()
{
    beginResetModel();
    endResetModel();
}

void SFRegionModel::ProcessBeforeSave()
{

}

int SFRegionModel::rowCount(const QModelIndex &) const
{
    return projectData->TABDIMS().NTSFUN().isNull()
            ? DefaultValues::TABDIMS_NTSFUN
            : projectData->TABDIMS().NTSFUN().toInt();
}

QVariant SFRegionModel::data(const QModelIndex &index, int role) const
{
    if(index.isValid() && role == Qt::DisplayRole) return index.row() + 1;

    return QVariant();
}

}}}
