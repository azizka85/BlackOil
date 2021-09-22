#include "wconprodmodel.h"

namespace BlackOil {
namespace Model {
namespace Wells {

WCONPRODModel::WCONPRODModel(ProjectData *projectData, WELSPECSModel *welspecs, QObject *parent) : QAbstractItemModel(parent)
{
    this->projectData = projectData;
    this->welspecs = welspecs;

    connect(welspecs, SIGNAL(WELSPECSInserted(int)), this, SLOT(HandleWELSPECSInserted(int)));
    connect(welspecs, SIGNAL(WELSPECSRemoved(int)), this, SLOT(HandleWELSPECSRemoved(int)));
    connect(welspecs, SIGNAL(WELSPECSChanged(int)), this, SLOT(HandleWELSPECSChanged(int)));
}

void WCONPRODModel::InitVariables()
{
    beginResetModel();

    removed.clear();
    groups.clear();
    indexes.clear();

    endResetModel();
}

void WCONPRODModel::ProcessData()
{
    beginResetModel();

    groups.resize(projectData->WCONPROD().size());
    indexes.resize(projectData->WCONPROD().size());

    for(int i = 0; i < projectData->WCONPROD().size(); i++)
        groups[i] = i;

    for(int i = 0; i < projectData->WELSPECS().size(); i++)
        for(int j = 0; j < groups.size(); j++)
            if(CheckWELSPECSMatch(j, i)) indexes[j].push_back(i);

    endResetModel();
}

void WCONPRODModel::ProcessBeforeSave()
{

}

void WCONPRODModel::HandleWELSPECSInserted(int welspecsIndex)
{
    for(int i = 0; i < groups.size(); i++)
    {
        bool doInsert = CheckWELSPECSMatch(i, welspecsIndex) && indexes[i].indexOf(welspecsIndex) < 0;

        if(doInsert)
        {
            QModelIndex parent = index(i, 0, QModelIndex());

            beginInsertRows(parent, indexes[i].size(), indexes[i].size());
            indexes[i].push_back(welspecsIndex);
            endInsertRows();
        }
    }
}

void WCONPRODModel::HandleWELSPECSRemoved(int welspecsIndex)
{
    for(int i = 0; i < groups.size(); i++)
    {
        int j = indexes[i].indexOf(welspecsIndex);

        if(j >= 0)
        {
            QModelIndex parent = index(i, 0, QModelIndex());

            beginRemoveRows(parent, j, j);
            indexes[i].removeAt(j);
            endRemoveRows();
        }
    }
}

void WCONPRODModel::HandleWELSPECSChanged(int welspecsIndex)
{
    for(int i = 0; i < groups.size(); i++)
    {
        bool matched = CheckWELSPECSMatch(i, welspecsIndex);
        int j = indexes[i].indexOf(welspecsIndex);

        QModelIndex parent = index(i, 0, QModelIndex());

        if(matched && j < 0)
        {
            beginInsertRows(parent, indexes[i].size(), indexes[i].size());
            indexes[i].push_back(welspecsIndex);
            endInsertRows();
        }
        else if(!matched && j >= 0)
        {
            beginRemoveRows(parent, j, j);
            indexes[i].removeAt(j);
            endRemoveRows();
        }
    }
}

bool WCONPRODModel::CheckWELSPECSMatch(int index, int welspecsIndex)
{
    int result = 0;

    int group = groups[index];

    QString search = projectData->WCONPROD()[group].WellName().replace("*", "");

    if(projectData->WCONPROD()[group].WellName().startsWith("*") && projectData->WELSPECS()[welspecsIndex].WellName().endsWith(search))
        result |= 1;

    if(projectData->WCONPROD()[group].WellName().endsWith("*") && projectData->WELSPECS()[welspecsIndex].WellName().startsWith(search))
        result |= 2;

    if(projectData->WELSPECS()[welspecsIndex].WellName() == search)
        result |= 4;

    return result > 0;
}

void WCONPRODModel::HandleWellNameChanged(QModelIndex index)
{
    beginRemoveRows(index, 0, indexes[index.row()].size() - 1);
    indexes[index.row()].clear();
    endRemoveRows();

    auto list = welspecs->WELSPECSIndexes();

    for(int i: list)
    {
        if(CheckWELSPECSMatch(index.row(), i))
        {
            beginInsertRows(index, indexes[index.row()].size(), indexes[index.row()].size());
            indexes[index.row()].push_back(i);
            endInsertRows();
        }
    }
}

QModelIndex WCONPRODModel::index(int row, int column, const QModelIndex &parent) const
{
    if(!hasIndex(row, column, parent))
        return QModelIndex();

    if(parent.isValid() && !parent.parent().isValid() && parent.row() >= 0 && parent.row() < indexes.size())
        return createIndex(row, column, (void *)&groups[parent.row()]);
    else
        return createIndex(row, column);
}

QModelIndex WCONPRODModel::parent(const QModelIndex &child) const
{
    if(!child.isValid())
        return QModelIndex();

    auto group = (int *)child.internalPointer();

    if(!group)
        return QModelIndex();

    int index = group - groups.begin();

    return createIndex(index, 0);
}

int WCONPRODModel::rowCount(const QModelIndex &parent) const
{
    if(parent.column() > 0)
        return 0;

    if(!parent.isValid())
    {
        return groups.size();
    }
    else
    {
        if(!parent.parent().isValid())
            return indexes[parent.row()].size();
        else
            return 0;
    }
}

int WCONPRODModel::columnCount(const QModelIndex &) const
{
    return staticMetaObject.enumerator(staticMetaObject.indexOfEnumerator("Columns")).keyCount();
}

QVariant WCONPRODModel::data(const QModelIndex &index, int role) const
{
    if(index.isValid() && (role == Qt::DisplayRole || role == Qt::EditRole))
    {
        auto group = (int *)index.internalPointer();

        int i = group - groups.begin();
        int k = i < 0 || i >= groups.size() ? groups[index.row()] : groups[i];

        auto wellStatusEnum = WellStatusEnum::staticMetaObject;
        auto wellControlEnum = WellControlEnum::staticMetaObject;

        int wellStatus = projectData->WCONPROD()[k].WellStatus().isNull()
                ? DefaultValues::WCONPROD_WellStatus
                : projectData->WCONPROD()[k].WellStatus().toInt();

        switch (index.column())
        {
            case WellName: return i < 0 || i >= groups.size()
                    ? projectData->WCONPROD()[k].WellName() + (role == Qt::DisplayRole ? tr(" (Количество: %1)").arg(indexes[index.row()].size()) : "")
                    : projectData->WELSPECS()[indexes[i][index.row()]].WellName();
            case WellDate: return projectData->WCONPROD()[k].Date().date();
            case WellStatus: return role == Qt::DisplayRole
                    ? wellStatusEnum.enumerator(wellStatusEnum.indexOfEnumerator("WellStatus")).key(wellStatus)
                    : projectData->WCONPROD()[k].WellStatus();
            case WellControl: return  role == Qt::DisplayRole
                    ? projectData->WCONPROD()[k].WellControl().isNull()
                        ? ""
                        : wellControlEnum.enumerator(wellControlEnum.indexOfEnumerator("WellControl")).key(projectData->WCONPROD()[k].WellControl().toInt())
                    : projectData->WCONPROD()[k].WellControl();
            case WellORAT: return projectData->WCONPROD()[k].ORAT();
            case WellWRAT: return projectData->WCONPROD()[k].WRAT();
            case WellGRAT: return projectData->WCONPROD()[k].GRAT();
            case WellLRAT: return projectData->WCONPROD()[k].LRAT();
            case WellRESV: return projectData->WCONPROD()[k].RESV();
            case WellBHP: return projectData->WCONPROD()[k].BHP();
        }

        return QVariant();
    }

    if(role == Qt::TextAlignmentRole) return QVariant(Qt::AlignHCenter | Qt::AlignVCenter);

    return QVariant();
}

QVariant WCONPRODModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(role == Qt::DisplayRole)
    {
        if(orientation == Qt::Horizontal)
        {
            switch (section)
            {
                case WellName: return tr("Имя скважины");
                case WellDate: return tr("Дата");
                case WellStatus: return tr("Статус");
                case WellControl: return tr("Режим управления");
                case WellORAT: return tr("Значение ORAT");
                case WellWRAT: return tr("Значение WRAT");
                case WellGRAT: return tr("Значение GRAT");
                case WellLRAT: return tr("Значение LRAT");
                case WellRESV: return tr("Значение RESV");
                case WellBHP: return tr("Значение BHP");
            }
        }
    }

    if(role == Qt::TextAlignmentRole) return QVariant(Qt::AlignHCenter | Qt::AlignVCenter);

    return QVariant();
}

bool WCONPRODModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(index.isValid() && role == Qt::EditRole)
    {
        if(!index.parent().isValid())
        {
            int group = groups[index.row()];

            switch (index.column())
            {
                case WellName:
                    projectData->WCONPROD()[group].SetWellName(value.toString());
                    HandleWellNameChanged(index);
                    break;
                case WellDate:
                    projectData->WCONPROD()[group].SetDate(value.toDateTime());
                    break;
                case WellStatus:
                    projectData->WCONPROD()[group].SetWellStatus(value);
                    break;
                case WellControl:
                    projectData->WCONPROD()[group].SetWellControl(value);
                    break;
                case WellORAT:
                    projectData->WCONPROD()[group].SetORAT(value);
                    break;
                case WellWRAT:
                    projectData->WCONPROD()[group].SetWRAT(value);
                    break;
                case WellGRAT:
                    projectData->WCONPROD()[group].SetGRAT(value);
                    break;
                case WellLRAT:
                    projectData->WCONPROD()[group].SetLRAT(value);
                    break;
                case WellRESV:
                    projectData->WCONPROD()[group].SetRESV(value);
                    break;
                case WellBHP:
                    projectData->WCONPROD()[group].SetBHP(value);
                    break;
            }

            emit dataChanged(index, index);

            return true;
        }
    }

    return false;
}

Qt::ItemFlags WCONPRODModel::flags(const QModelIndex &index) const
{
    auto opt = QAbstractItemModel::flags(index);;

    if(index.isValid() && !index.parent().isValid())
        opt |= Qt::ItemIsEditable;

    return opt;
}

bool WCONPRODModel::insertRows(int row, int count, const QModelIndex &parent)
{
    if(!parent.isValid())
    {
        beginInsertRows(parent, row, row + count - 1);

        for(int i = row; i < row + count; i++)
        {
            if(removed.size() > 0)
            {
                int j = removed[0];

                WCONPRODData &wconprod = projectData->WCONPROD()[j];
                wconprod.InitVariables();
                groups.insert(i, j);
                indexes.insert(i, QVector<int>());

                removed.pop_front();
            }
            else
            {
                int j = projectData->WCONPROD().size();

                WCONPRODData wconprod;
                groups.insert(i, j);
                indexes.insert(i, QVector<int>());
                projectData->WCONPROD().push_back(wconprod);
            }
        }

        endInsertRows();

        for(int i = row; i < row + count; i++) HandleWellNameChanged(index(i, 0, QModelIndex()));

        // qDebug() << "Groups: " << groups;
        // qDebug() << "Indexes: " << indexes;

        return true;
    }

    return false;
}

bool WCONPRODModel::removeRows(int row, int count, const QModelIndex &parent)
{
    if(!parent.isValid())
    {
        beginRemoveRows(parent, row, row + count - 1);

        int n = count;

        while(n > 0)
        {
            int j = groups[row];

            removed.push_back(j);
            groups.remove(row);
            indexes.remove(row);

            n--;
        }

        endRemoveRows();

        // qDebug() << "Groups: " << groups;
        // qDebug() << "Indexes: " << indexes;

        return true;
    }

    return false;
}

}}}
