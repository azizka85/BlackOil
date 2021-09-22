#include "pvtregionmodel.h"

namespace BlackOil {
namespace Model {
namespace PVT {

PVTRegionModel::PVTRegionModel(ProjectData *projectData, QObject *parent) : QAbstractListModel(parent)
{
    this->projectData = projectData;
}

void PVTRegionModel::InitVariables()
{
    beginResetModel();
    endResetModel();
}

void PVTRegionModel::ProcessData()
{
    beginResetModel();
    endResetModel();
}

void PVTRegionModel::ProcessBeforeSave()
{

}

int PVTRegionModel::rowCount(const QModelIndex &) const
{
    return projectData->TABDIMS().NTPVT().isNull()
            ? DefaultValues::TABDIMS_NTPVT
            : projectData->TABDIMS().NTPVT().toInt();
}

QVariant PVTRegionModel::data(const QModelIndex &index, int role) const
{
    if(index.isValid() && role == Qt::DisplayRole) return index.row() + 1;

    return QVariant();
}

}}}
