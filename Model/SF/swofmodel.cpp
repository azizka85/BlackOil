#include "swofmodel.h"

namespace BlackOil {
namespace Model {
namespace SF {

SWOFModel::SWOFModel(ProjectData *projectData, QObject *parent) : QAbstractTableModel(parent)
{
    region = 0;
    this->projectData = projectData;
    minMax.resize(2);
    minMax[0].resize(columnCount(QModelIndex()));
    minMax[1].resize(columnCount(QModelIndex()));

    connect(this, SIGNAL(RegionChanged(int)), this, SLOT(HandleRegionChanged(int)));
}

int SWOFModel::Region()
{
    return region;
}

void SWOFModel::SetRegion(int region)
{
    if(this->region != region)
    {
        this->region = region;

        emit RegionChanged(region);
    }
}

void SWOFModel::InitVariables()
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

    projectData->SWOF().resize(DefaultValues::TABDIMS_NTSFUN);

    endResetModel();
}

void SWOFModel::ProcessData()
{
    beginResetModel();       

    ResetMinMax();

    endResetModel();
}

void SWOFModel::ProcessBeforeSave()
{

}

void SWOFModel::HandleRegionChanged(int)
{
    beginResetModel();

    ResetMinMax();

    endResetModel();
}

void SWOFModel::ResetMinMax()
{
    if(region >= 0 && region < projectData->SWOF().size())
    {
        int cnt = columnCount(QModelIndex());

        for(int i = 0; i < projectData->SWOF()[region].size(); i++)
        {
            for(int j = 0; j < cnt; j++)
            {
                if(j == SWOFSw)
                {
                    if(minMax[0][j].isNull() || projectData->SWOF()[region][i].SW() < minMax[0][j].toDouble())
                        minMax[0][j] = projectData->SWOF()[region][i].SW();

                    if(minMax[1][j].isNull() || projectData->SWOF()[region][i].SW() > minMax[1][j].toDouble())
                        minMax[1][j] = projectData->SWOF()[region][i].SW();
                }
                else if(j == SWOFKrW)
                {
                    if(minMax[0][j].isNull() || (!projectData->SWOF()[region][i].KrW().isNull() && projectData->SWOF()[region][i].KrW().toDouble() < minMax[0][j].toDouble()))
                        minMax[0][j] = projectData->SWOF()[region][i].KrW();

                    if(minMax[1][j].isNull() || (!projectData->SWOF()[region][i].KrW().isNull() && projectData->SWOF()[region][i].KrW().toDouble() > minMax[1][j].toDouble()))
                        minMax[1][j] = projectData->SWOF()[region][i].KrW();
                }
                else if(j == SWOFKrO)
                {
                    if(minMax[0][j].isNull() || (!projectData->SWOF()[region][i].KrO().isNull() && projectData->SWOF()[region][i].KrO().toDouble() < minMax[0][j].toDouble()))
                        minMax[0][j] = projectData->SWOF()[region][i].KrO();

                    if(minMax[1][j].isNull() || (!projectData->SWOF()[region][i].KrO().isNull() && projectData->SWOF()[region][i].KrO().toDouble() > minMax[1][j].toDouble()))
                        minMax[1][j] = projectData->SWOF()[region][i].KrO();
                }
                else if(j == SWOFPcOW)
                {
                    if(minMax[0][j].isNull() || (!projectData->SWOF()[region][i].Pc().isNull() && projectData->SWOF()[region][i].Pc().toDouble() < minMax[0][j].toDouble()))
                        minMax[0][j] = projectData->SWOF()[region][i].Pc();

                    if(minMax[1][j].isNull() || (!projectData->SWOF()[region][i].Pc().isNull() && projectData->SWOF()[region][i].Pc().toDouble() > minMax[1][j].toDouble()))
                        minMax[1][j] = projectData->SWOF()[region][i].Pc();
                }
            }
        }

        for(int i = 0; i < cnt; i++) emit MinMaxChanged(i, minMax[0][i], minMax[1][i]);
    }
}

int SWOFModel::rowCount(const QModelIndex &) const
{
    if(region >= 0 && region < projectData->SWOF().size())
        return projectData->SWOF()[region].size();
    else
        return 0;
}

int SWOFModel::columnCount(const QModelIndex &) const
{
    return staticMetaObject.enumerator(staticMetaObject.indexOfEnumerator("Columns")).keyCount();
}

QVariant SWOFModel::data(const QModelIndex &index, int role) const
{
    if(index.isValid() && (role == Qt::DisplayRole || role == Qt::EditRole) && region >= 0 && region < projectData->SWOF().size())
    {
        switch (index.column())
        {
            case SWOFSw: return projectData->SWOF()[region][index.row()].SW();
            case SWOFKrW: return role == Qt::DisplayRole ? projectData->SWOF()[region][index.row()].KrW().toDouble() : projectData->SWOF()[region][index.row()].KrW();
            case SWOFKrO: return role == Qt::DisplayRole ? projectData->SWOF()[region][index.row()].KrO().toDouble() : projectData->SWOF()[region][index.row()].KrO();
            case SWOFPcOW: return role == Qt::DisplayRole ? projectData->SWOF()[region][index.row()].Pc().toDouble() : projectData->SWOF()[region][index.row()].Pc();
        }
    }

    if(role == Qt::TextAlignmentRole) return QVariant(Qt::AlignHCenter | Qt::AlignVCenter);

    return QVariant();
}

QVariant SWOFModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(role == Qt::DisplayRole)
    {
        if(orientation == Qt::Horizontal)
        {
            switch (section)
            {
                case SWOFSw: return tr("Sw");
                case SWOFKrW: return tr("KrW");
                case SWOFKrO: return tr("KrO");
                case SWOFPcOW: return tr("PcOW");
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

bool SWOFModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(index.isValid() && role == Qt::EditRole && region >= 0 && region < projectData->SWOF().size())
    {
        if(index.column() == SWOFSw)
        {
            projectData->SWOF()[region][index.row()].SetSW(value.toDouble());

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
        else if(index.column() == SWOFKrW)
        {
            projectData->SWOF()[region][index.row()].SetKrW(value);

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
        else if(index.column() == SWOFKrO)
        {
            projectData->SWOF()[region][index.row()].SetKrO(value);

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
        else if(index.column() == SWOFPcOW)
        {
            projectData->SWOF()[region][index.row()].SetPc(value);

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

Qt::ItemFlags SWOFModel::flags(const QModelIndex &index) const
{
    auto opt = QAbstractItemModel::flags(index);

    if(index.isValid())
        opt |= Qt::ItemIsEditable;

    return opt;
}

bool SWOFModel::insertRows(int row, int count, const QModelIndex &parent)
{
    if(region >= 0 && region < projectData->SWOF().size())
    {
        beginInsertRows(parent, row, row + count - 1);

        projectData->SWOF()[region].insert(row, count, SWOFData());

        ResetMinMax();

        endInsertRows();

        return true;
    }

    return false;
}

bool SWOFModel::removeRows(int row, int count, const QModelIndex &parent)
{
    if(region >= 0 && region < projectData->SWOF().size())
    {
        beginRemoveRows(parent, row, row + count - 1);

        projectData->SWOF()[region].remove(row, count);

        ResetMinMax();

        endRemoveRows();

        return true;
    }

    return false;
}

}}}
