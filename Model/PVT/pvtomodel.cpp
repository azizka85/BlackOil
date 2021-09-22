#include "pvtomodel.h"

namespace BlackOil {
namespace Model {
namespace PVT {

PVTOModel::PVTOModel(ProjectData *projectData, QObject *parent) : QAbstractTableModel(parent)
{
    region = 0;
    this->projectData = projectData;
    minMax.resize(2);
    minMax[0].resize(columnCount(QModelIndex()));
    minMax[1].resize(columnCount(QModelIndex()));

    connect(this, SIGNAL(RegionChanged(int)), this, SLOT(HandleRegionChanged(int)));
}

int PVTOModel::Region()
{
    return region;
}

void PVTOModel::InitVariables()
{
    beginResetModel();

    SetRegion(0);

    int cnt = columnCount(QModelIndex());

    for(int i = 0; i < cnt; i++)
    {
        minMax[0][i].clear();
        minMax[1][i].clear();

        emit MinMaxChanged(i, minMax[0][i], minMax[1][i]);
    }

    projectData->PVTO().resize(DefaultValues::TABDIMS_NTPVT);

    endResetModel();
}

void PVTOModel::ProcessData()
{
    beginResetModel();

    ResetMinMax();

    endResetModel();
}

void PVTOModel::ProcessBeforeSave()
{

}

void PVTOModel::SetRegion(int region)
{
    if(this->region != region)
    {
        this->region = region;

        emit RegionChanged(region);
    }
}

void PVTOModel::HandleRegionChanged(int)
{
    beginResetModel();

    ResetMinMax();

    endResetModel();
}

void PVTOModel::ResetMinMax()
{
    if(region >= 0 && region < projectData->PVTO().size())
    {
        int cnt = columnCount(QModelIndex());

        for(int i = 0; i < projectData->PVTO()[region].size(); i++)
        {
            for(int j = 0; j < cnt; j++)
            {
                if(j == PVTORS)
                {
                    if(minMax[0][j].isNull() || projectData->PVTO()[region][i].RS() < minMax[0][j].toDouble())
                        minMax[0][j] = projectData->PVTO()[region][i].RS();

                    if(minMax[1][j].isNull() || projectData->PVTO()[region][i].RS() > minMax[1][j].toDouble())
                        minMax[1][j] = projectData->PVTO()[region][i].RS();
                }
                else if(j == PVTOPO)
                {
                    if(minMax[0][j].isNull() || projectData->PVTO()[region][i].PO() < minMax[0][j].toDouble())
                        minMax[0][j] = projectData->PVTO()[region][i].PO();

                    if(minMax[1][j].isNull() || projectData->PVTO()[region][i].PO() > minMax[1][j].toDouble())
                        minMax[1][j] = projectData->PVTO()[region][i].PO();
                }
                else if(j == PVTOBO)
                {
                    if(minMax[0][j].isNull() || projectData->PVTO()[region][i].BO() < minMax[0][j].toDouble())
                        minMax[0][j] = projectData->PVTO()[region][i].BO();

                    if(minMax[1][j].isNull() || projectData->PVTO()[region][i].BO() > minMax[1][j].toDouble())
                        minMax[1][j] = projectData->PVTO()[region][i].BO();
                }
                else if(j == PVTOMO)
                {
                    if(minMax[0][j].isNull() || projectData->PVTO()[region][i].MO() < minMax[0][j].toDouble())
                        minMax[0][j] = projectData->PVTO()[region][i].MO();

                    if(minMax[1][j].isNull() || projectData->PVTO()[region][i].MO() > minMax[1][j].toDouble())
                        minMax[1][j] = projectData->PVTO()[region][i].MO();
                }
            }
        }

        for(int i = 0; i < cnt; i++) emit MinMaxChanged(i, minMax[0][i], minMax[1][i]);
    }
}

int PVTOModel::rowCount(const QModelIndex &) const
{
    if(region >= 0 && region < projectData->PVTO().size())
        return projectData->PVTO()[region].size();
    else
        return 0;
}


int PVTOModel::columnCount(const QModelIndex &) const
{
    return staticMetaObject.enumerator(staticMetaObject.indexOfEnumerator("Columns")).keyCount();
}

QVariant PVTOModel::data(const QModelIndex &index, int role) const
{
    if(index.isValid() && (role == Qt::DisplayRole || role == Qt::EditRole) && region >= 0 && region < projectData->PVTO().size())
    {
        switch (index.column())
        {
            case PVTORS: return projectData->PVTO()[region][index.row()].RS();
            case PVTOPO: return role == Qt::DisplayRole ? projectData->PVTO()[region][index.row()].PO() : projectData->PVTO()[region][index.row()].PO();
            case PVTOBO: return role == Qt::DisplayRole ? projectData->PVTO()[region][index.row()].BO() : projectData->PVTO()[region][index.row()].BO();
            case PVTOMO: return role == Qt::DisplayRole ? projectData->PVTO()[region][index.row()].MO() : projectData->PVTO()[region][index.row()].MO();
        }
    }

    if(role == Qt::TextAlignmentRole) return QVariant(Qt::AlignHCenter | Qt::AlignVCenter);

    return QVariant();
}

QVariant PVTOModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(role == Qt::DisplayRole)
    {
        if(orientation == Qt::Horizontal)
        {
            switch (section)
            {
                case PVTORS: return tr("RS");
                case PVTOPO: return tr("PO");
                case PVTOBO: return tr("BO");
                case PVTOMO: return tr("MO");
            }
        }
        else
        {
            return QString::number(section);
        }
    }

    if(role == Qt::TextAlignmentRole) return QVariant(Qt::AlignHCenter | Qt::AlignVCenter);

    return QVariant();
}

bool PVTOModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(index.isValid() && role == Qt::EditRole && region >= 0 && region < projectData->PVTO().size())
    {
        if(index.column() == PVTORS)
        {
            projectData->PVTO()[region][index.row()].SetRS(value.toDouble());

            if(minMax[0][index.column()].isNull() || value.toDouble() < minMax[0][index.column()].toDouble())
            {
                minMax[0][index.column()] = value.toDouble();

                emit MinMaxChanged(index.column(), minMax[0][index.column()], minMax[1][index.column()]);
            }

            if(minMax[1][index.column()].isNull() || value.toDouble() > minMax[1][index.column()].toDouble())
            {
                minMax[1][index.column()] = value.toDouble();

                emit MinMaxChanged(index.column(), minMax[0][index.column()], minMax[1][index.column()]);
            }
        }
        else if(index.column() == PVTOPO)
        {
            projectData->PVTO()[region][index.row()].SetPO(value.toDouble());

            if(minMax[0][index.column()].isNull() || value.toDouble() < minMax[0][index.column()].toDouble())
            {
                minMax[0][index.column()] = value.toDouble();

                emit MinMaxChanged(index.column(), minMax[0][index.column()], minMax[1][index.column()]);
            }

            if(minMax[1][index.column()].isNull() || value.toDouble() > minMax[1][index.column()].toDouble())
            {
                minMax[1][index.column()] = value.toDouble();

                emit MinMaxChanged(index.column(), minMax[0][index.column()], minMax[1][index.column()]);
            }
        }
        else if(index.column() == PVTOBO)
        {
            projectData->PVTO()[region][index.row()].SetBO(value.toDouble());

            if(minMax[0][index.column()].isNull() || value.toDouble() < minMax[0][index.column()].toDouble())
            {
                minMax[0][index.column()] = value.toDouble();

                emit MinMaxChanged(index.column(), minMax[0][index.column()], minMax[1][index.column()]);
            }

            if(minMax[1][index.column()].isNull() || value.toDouble() > minMax[1][index.column()].toDouble())
            {
                minMax[1][index.column()] = value.toDouble();

                emit MinMaxChanged(index.column(), minMax[0][index.column()], minMax[1][index.column()]);
            }
        }
        else if(index.column() == PVTOMO)
        {
            projectData->PVTO()[region][index.row()].SetMO(value.toDouble());

            if(minMax[0][index.column()].isNull() || value.toDouble() < minMax[0][index.column()].toDouble())
            {
                minMax[0][index.column()] = value.toDouble();

                emit MinMaxChanged(index.column(), minMax[0][index.column()], minMax[1][index.column()]);
            }

            if(minMax[1][index.column()].isNull() || value.toDouble() > minMax[1][index.column()].toDouble())
            {
                minMax[1][index.column()] = value.toDouble();

                emit MinMaxChanged(index.column(), minMax[0][index.column()], minMax[1][index.column()]);
            }
        }

        emit dataChanged(index, index);

        return true;
    }

    return false;
}

Qt::ItemFlags PVTOModel::flags(const QModelIndex &index) const
{
    auto opt = QAbstractItemModel::flags(index);;

    if(index.isValid())
        opt |= Qt::ItemIsEditable;

    return opt;
}

bool PVTOModel::insertRows(int row, int count, const QModelIndex &parent)
{
    if(region >= 0 && region < projectData->PVTO().size())
    {
        beginInsertRows(parent, row, row + count - 1);

        projectData->PVTO()[region].insert(row, count, PVTOData());

        ResetMinMax();

        endInsertRows();

        return true;
    }

    return false;
}

bool PVTOModel::removeRows(int row, int count, const QModelIndex &parent)
{
    if(region >= 0 && region < projectData->PVTO().size())
    {
        beginRemoveRows(parent, row, row + count - 1);

        projectData->PVTO()[region].remove(row, count);

        ResetMinMax();

        endRemoveRows();

        return true;
    }

    return false;
}

}}}
