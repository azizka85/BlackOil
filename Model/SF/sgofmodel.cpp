#include "sgofmodel.h"

namespace BlackOil {
namespace Model {
namespace SF {

SGOFModel::SGOFModel(ProjectData *projectData, QObject *parent): QAbstractTableModel(parent)
{
    region = 0;
    this->projectData = projectData;
    minMax.resize(2);
    minMax[0].resize(columnCount(QModelIndex()));
    minMax[1].resize(columnCount(QModelIndex()));

    connect(this, SIGNAL(RegionChanged(int)), this, SLOT(HandleRegionChanged(int)));
}

int SGOFModel::Region()
{
    return region;
}

void SGOFModel::InitVariables()
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

    projectData->SGOF().resize(DefaultValues::TABDIMS_NTSFUN);

    endResetModel();
}

void SGOFModel::ProcessData()
{
    beginResetModel();

    ResetMinMax();

    endResetModel();
}

void SGOFModel::ProcessBeforeSave()
{

}

void SGOFModel::SetRegion(int region)
{
    if(this->region != region)
    {
        this->region = region;

        emit RegionChanged(region);
    }
}

void SGOFModel::HandleRegionChanged(int)
{
    beginResetModel();

    ResetMinMax();

    endResetModel();
}

void SGOFModel::ResetMinMax()
{
    if(region >= 0 && region < projectData->SGOF().size())
    {
        int cnt = columnCount(QModelIndex());

        for(int i = 0; i < projectData->SGOF()[region].size(); i++)
        {
            for(int j = 0; j < cnt; j++)
            {
                if(j == SGOFSg)
                {
                    if(minMax[0][j].isNull() || projectData->SGOF()[region][i].SG() < minMax[0][j].toDouble())
                        minMax[0][j] = projectData->SGOF()[region][i].SG();

                    if(minMax[1][j].isNull() || projectData->SGOF()[region][i].SG() > minMax[1][j].toDouble())
                        minMax[1][j] = projectData->SGOF()[region][i].SG();
                }
                else if(j == SGOFKrG)
                {
                    if(minMax[0][j].isNull() || (!projectData->SGOF()[region][i].KrG().isNull() && projectData->SGOF()[region][i].KrG().toDouble() < minMax[0][j].toDouble()))
                        minMax[0][j] = projectData->SGOF()[region][i].KrG();

                    if(minMax[1][j].isNull() || (!projectData->SGOF()[region][i].KrG().isNull() && projectData->SGOF()[region][i].KrG().toDouble() > minMax[1][j].toDouble()))
                        minMax[1][j] = projectData->SGOF()[region][i].KrG();
                }
                else if(j == SGOFKrO)
                {
                    if(minMax[0][j].isNull() || (!projectData->SGOF()[region][i].KrO().isNull() && projectData->SGOF()[region][i].KrO().toDouble() < minMax[0][j].toDouble()))
                        minMax[0][j] = projectData->SGOF()[region][i].KrO();

                    if(minMax[1][j].isNull() || (!projectData->SGOF()[region][i].KrO().isNull() && projectData->SGOF()[region][i].KrO().toDouble() > minMax[1][j].toDouble()))
                        minMax[1][j] = projectData->SGOF()[region][i].KrO();
                }
                else if(j == SGOFPcOG)
                {
                    if(minMax[0][j].isNull() || (!projectData->SGOF()[region][i].Pc().isNull() && projectData->SGOF()[region][i].Pc().toDouble() < minMax[0][j].toDouble()))
                        minMax[0][j] = projectData->SGOF()[region][i].Pc();

                    if(minMax[1][j].isNull() || (!projectData->SGOF()[region][i].Pc().isNull() && projectData->SGOF()[region][i].Pc().toDouble() > minMax[1][j].toDouble()))
                        minMax[1][j] = projectData->SGOF()[region][i].Pc();
                }
            }
        }

        for(int i = 0; i < cnt; i++) emit MinMaxChanged(i, minMax[0][i], minMax[1][i]);
    }
}

int SGOFModel::rowCount(const QModelIndex &) const
{
    if(region >= 0 && region < projectData->SGOF().size())
        return projectData->SGOF()[region].size();
    else
        return 0;
}

int SGOFModel::columnCount(const QModelIndex &) const
{
    return staticMetaObject.enumerator(staticMetaObject.indexOfEnumerator("Columns")).keyCount();
}

QVariant SGOFModel::data(const QModelIndex &index, int role) const
{
    if(index.isValid() && (role == Qt::DisplayRole || role == Qt::EditRole) && region >= 0 && region < projectData->SGOF().size())
    {
        switch (index.column())
        {
            case SGOFSg: return projectData->SGOF()[region][index.row()].SG();
            case SGOFKrG: return role == Qt::DisplayRole ? projectData->SGOF()[region][index.row()].KrG().toDouble() : projectData->SGOF()[region][index.row()].KrG();
            case SGOFKrO: return role == Qt::DisplayRole ? projectData->SGOF()[region][index.row()].KrO().toDouble() : projectData->SGOF()[region][index.row()].KrO();
            case SGOFPcOG: return role == Qt::DisplayRole ? projectData->SGOF()[region][index.row()].Pc().toDouble() : projectData->SGOF()[region][index.row()].Pc();
        }
    }

    if(role == Qt::TextAlignmentRole) return QVariant(Qt::AlignHCenter | Qt::AlignVCenter);

    return QVariant();
}

QVariant SGOFModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(role == Qt::DisplayRole)
    {
        if(orientation == Qt::Horizontal)
        {
            switch (section)
            {
                case SGOFSg: return tr("Sg");
                case SGOFKrG: return tr("KrG");
                case SGOFKrO: return tr("KrO");
                case SGOFPcOG: return tr("PcOG");
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

bool SGOFModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(index.isValid() && role == Qt::EditRole && region >= 0 && region < projectData->SGOF().size())
    {
        if(index.column() == SGOFSg)
        {
            projectData->SGOF()[region][index.row()].SetSG(value.toDouble());

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
        else if(index.column() == SGOFKrG)
        {
            projectData->SGOF()[region][index.row()].SetKrG(value);

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
        else if(index.column() == SGOFKrO)
        {
            projectData->SGOF()[region][index.row()].SetKrO(value);

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
        else if(index.column() == SGOFPcOG)
        {
            projectData->SGOF()[region][index.row()].SetPc(value);

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

Qt::ItemFlags SGOFModel::flags(const QModelIndex &index) const
{
    auto opt = QAbstractItemModel::flags(index);;

    if(index.isValid())
        opt |= Qt::ItemIsEditable;

    return opt;
}

bool SGOFModel::insertRows(int row, int count, const QModelIndex &parent)
{
    if(region >= 0 && region < projectData->SGOF().size())
    {
        beginInsertRows(parent, row, row + count - 1);

        projectData->SGOF()[region].insert(row, count, SGOFData());

        ResetMinMax();

        endInsertRows();

        return true;
    }

    return false;
}

bool SGOFModel::removeRows(int row, int count, const QModelIndex &parent)
{
    if(region >= 0 && region < projectData->SGOF().size())
    {
        beginRemoveRows(parent, row, row + count - 1);

        projectData->SGOF()[region].remove(row, count);

        ResetMinMax();

        endRemoveRows();

        return true;
    }

    return false;
}

}}}
