#include "pvtgmodel.h"

namespace BlackOil {
namespace Model {
namespace PVT {

PVTGModel::PVTGModel(ProjectData *projectData, QObject *parent) : QAbstractTableModel(parent)
{
    region = 0;
    this->projectData = projectData;
    minMax.resize(2);
    minMax[0].resize(columnCount(QModelIndex()));
    minMax[1].resize(columnCount(QModelIndex()));

    connect(this, SIGNAL(RegionChanged(int)), this, SLOT(HandleRegionChanged(int)));
}

int PVTGModel::Region()
{
    return region;
}

void PVTGModel::InitVariables()
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

    projectData->PVTG().resize(DefaultValues::TABDIMS_NTPVT);

    endResetModel();
}

void PVTGModel::ProcessData()
{
    beginResetModel();

    ResetMinMax();

    endResetModel();
}

void PVTGModel::ProcessBeforeSave()
{

}

void PVTGModel::SetRegion(int region)
{
    if(this->region != region)
    {
        this->region = region;

        emit RegionChanged(region);
    }
}

void PVTGModel::HandleRegionChanged(int)
{
    beginResetModel();

    ResetMinMax();

    endResetModel();
}

void PVTGModel::ResetMinMax()
{
    if(region >= 0 && region < projectData->PVTG().size())
    {
        int cnt = columnCount(QModelIndex());

        for(int i = 0; i < projectData->PVTG()[region].size(); i++)
        {
            for(int j = 0; j < cnt; j++)
            {
                if(j == PVTGPG)
                {
                    if(minMax[0][j].isNull() || projectData->PVTG()[region][i].PG() < minMax[0][j].toDouble())
                        minMax[0][j] = projectData->PVTG()[region][i].PG();

                    if(minMax[1][j].isNull() || projectData->PVTG()[region][i].PG() > minMax[1][j].toDouble())
                        minMax[1][j] = projectData->PVTG()[region][i].PG();
                }
                else if(j == PVTGBG)
                {
                    if(minMax[0][j].isNull() || projectData->PVTG()[region][i].BG() < minMax[0][j].toDouble())
                        minMax[0][j] = projectData->PVTG()[region][i].BG();

                    if(minMax[1][j].isNull() || projectData->PVTG()[region][i].BG() > minMax[1][j].toDouble())
                        minMax[1][j] = projectData->PVTG()[region][i].BG();
                }
                else if(j == PVTGMG)
                {
                    if(minMax[0][j].isNull() || projectData->PVTG()[region][i].MG() < minMax[0][j].toDouble())
                        minMax[0][j] = projectData->PVTG()[region][i].MG();

                    if(minMax[1][j].isNull() || projectData->PVTG()[region][i].MG() > minMax[1][j].toDouble())
                        minMax[1][j] = projectData->PVTG()[region][i].MG();
                }
            }
        }

        for(int i = 0; i < cnt; i++) emit MinMaxChanged(i, minMax[0][i], minMax[1][i]);
    }
}

int PVTGModel::rowCount(const QModelIndex &) const
{
    if(region >= 0 && region < projectData->PVTG().size())
        return projectData->PVTG()[region].size();
    else
        return 0;
}

int PVTGModel::columnCount(const QModelIndex &) const
{
    return staticMetaObject.enumerator(staticMetaObject.indexOfEnumerator("Columns")).keyCount();
}

QVariant PVTGModel::data(const QModelIndex &index, int role) const
{
    if(index.isValid() && (role == Qt::DisplayRole || role == Qt::EditRole) && region >= 0 && region < projectData->PVTG().size())
    {
        switch (index.column())
        {
            case PVTGPG: return role == Qt::DisplayRole ? projectData->PVTG()[region][index.row()].PG() : projectData->PVTG()[region][index.row()].PG();
            case PVTGBG: return role == Qt::DisplayRole ? projectData->PVTG()[region][index.row()].BG() : projectData->PVTG()[region][index.row()].BG();
            case PVTGMG: return role == Qt::DisplayRole ? projectData->PVTG()[region][index.row()].MG() : projectData->PVTG()[region][index.row()].MG();
        }
    }

    if(role == Qt::TextAlignmentRole) return QVariant(Qt::AlignHCenter | Qt::AlignVCenter);

    return QVariant();
}

QVariant PVTGModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(role == Qt::DisplayRole)
    {
        if(orientation == Qt::Horizontal)
        {
            switch (section)
            {
                case PVTGPG: return tr("PG");
                case PVTGBG: return tr("BG");
                case PVTGMG: return tr("MG");
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

bool PVTGModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(index.isValid() && role == Qt::EditRole && region >= 0 && region < projectData->PVTG().size())
    {
        if(index.column() == PVTGPG)
        {
            projectData->PVTG()[region][index.row()].SetPG(value.toDouble());

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
        else if(index.column() == PVTGBG)
        {
            projectData->PVTG()[region][index.row()].SetBG(value.toDouble());

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
        else if(index.column() == PVTGMG)
        {
            projectData->PVTG()[region][index.row()].SetMG(value.toDouble());

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

Qt::ItemFlags PVTGModel::flags(const QModelIndex &index) const
{
    auto opt = QAbstractItemModel::flags(index);;

    if(index.isValid())
        opt |= Qt::ItemIsEditable;

    return opt;
}

bool PVTGModel::insertRows(int row, int count, const QModelIndex &parent)
{
    if(region >= 0 && region < projectData->PVTG().size())
    {
        beginInsertRows(parent, row, row + count - 1);

        projectData->PVTG()[region].insert(row, count, PVTGData());

        ResetMinMax();

        endInsertRows();

        return true;
    }

    return false;
}

bool PVTGModel::removeRows(int row, int count, const QModelIndex &parent)
{
    if(region >= 0 && region < projectData->PVTG().size())
    {
        beginRemoveRows(parent, row, row + count - 1);

        projectData->PVTG()[region].remove(row, count);

        ResetMinMax();

        endRemoveRows();

        return true;
    }

    return false;
}

}}}
