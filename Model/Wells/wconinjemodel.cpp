#include "wconinjemodel.h"

namespace BlackOil {
namespace Model {
namespace Wells {

WCONINJEModel::WCONINJEModel(ProjectData *projectData, WELSPECSModel *welspecs, QObject *parent) : QAbstractItemModel(parent)
{
    this->projectData = projectData;
    this->welspecs = welspecs;

    connect(welspecs, SIGNAL(WELSPECSInserted(int)), this, SLOT(HandleWELSPECSInserted(int)));
    connect(welspecs, SIGNAL(WELSPECSRemoved(int)), this, SLOT(HandleWELSPECSRemoved(int)));
    connect(welspecs, SIGNAL(WELSPECSChanged(int)), this, SLOT(HandleWELSPECSChanged(int)));
}

void WCONINJEModel::InitVariables()
{
    beginResetModel();

    removed.clear();
    groups.clear();
    indexes.clear();

    endResetModel();
}

void WCONINJEModel::ProcessData()
{
    beginResetModel();

    groups.resize(projectData->WCONINJE().size());
    indexes.resize(projectData->WCONINJE().size());

    for(int i = 0; i < projectData->WCONINJE().size(); i++)
        groups[i] = i;

    for(int i = 0; i < projectData->WELSPECS().size(); i++)
        for(int j = 0; j < groups.size(); j++)
            if(CheckWELSPECSMatch(j, i)) indexes[j].push_back(i);

    endResetModel();
}

void WCONINJEModel::ProcessBeforeSave()
{

}

void WCONINJEModel::HandleWELSPECSInserted(int welspecsIndex)
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

void WCONINJEModel::HandleWELSPECSRemoved(int welspecsIndex)
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

void WCONINJEModel::HandleWELSPECSChanged(int welspecsIndex)
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

bool WCONINJEModel::CheckWELSPECSMatch(int index, int welspecsIndex)
{
    int result = 0;

    int group = groups[index];

    QString search = projectData->WCONINJE()[group].WellName().replace("*", "");

    if(projectData->WCONINJE()[group].WellName().startsWith("*") && projectData->WELSPECS()[welspecsIndex].WellName().endsWith(search))
        result |= 1;

    if(projectData->WCONINJE()[group].WellName().endsWith("*") && projectData->WELSPECS()[welspecsIndex].WellName().startsWith(search))
        result |= 2;

    if(projectData->WELSPECS()[welspecsIndex].WellName() == search)
        result |= 4;

    return result > 0;
}

void WCONINJEModel::HandleWellNameChanged(QModelIndex index)
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

QModelIndex WCONINJEModel::index(int row, int column, const QModelIndex &parent) const
{
    if(!hasIndex(row, column, parent))
        return QModelIndex();

    if(parent.isValid() && !parent.parent().isValid() && parent.row() >= 0 && parent.row() < indexes.size())
        return createIndex(row, column, (void *)&groups[parent.row()]);
    else
        return createIndex(row, column);
}

QModelIndex WCONINJEModel::parent(const QModelIndex &child) const
{
    if(!child.isValid())
        return QModelIndex();

    auto group = (int *)child.internalPointer();

    if(!group)
        return QModelIndex();

    int index = group - groups.begin();

    return createIndex(index, 0);
}

int WCONINJEModel::rowCount(const QModelIndex &parent) const
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

int WCONINJEModel::columnCount(const QModelIndex &) const
{
    return staticMetaObject.enumerator(staticMetaObject.indexOfEnumerator("Columns")).keyCount();
}

QVariant WCONINJEModel::data(const QModelIndex &index, int role) const
{
    if(index.isValid() && (role == Qt::DisplayRole || role == Qt::EditRole))
    {
        auto group = (int *)index.internalPointer();

        int i = group - groups.begin();
        int k = i < 0 || i >= groups.size() ? groups[index.row()] : groups[i];

        auto wellStatusEnum = WellStatusEnum::staticMetaObject;
        auto wellControlEnum = WellControlEnum::staticMetaObject;
        auto fluidTypeEnum = FluidTypeEnum::staticMetaObject;

        int wellStatus = projectData->WCONINJE()[k].WellStatus().isNull()
                ? DefaultValues::WCONINJE_WellStatus
                : projectData->WCONINJE()[k].WellStatus().toInt();

        switch (index.column())
        {
            case WellName: return i < 0 || i >= groups.size()
                    ? projectData->WCONINJE()[k].WellName() + (role == Qt::DisplayRole ? tr(" (Количество: %1)").arg(indexes[index.row()].size()) : "")
                    : projectData->WELSPECS()[indexes[i][index.row()]].WellName();
            case WellDate: return projectData->WCONINJE()[k].Date().date();
            case WellInjFluid: return role == Qt::DisplayRole
                    ? projectData->WCONINJE()[k].InjFluid().isNull()
                        ? ""
                        : fluidTypeEnum.enumerator(fluidTypeEnum.indexOfEnumerator("FluidType")).key(projectData->WCONINJE()[k].InjFluid().toInt())
                    : projectData->WCONINJE()[k].InjFluid();
            case WellStatus: return role == Qt::DisplayRole
                    ? wellStatusEnum.enumerator(wellStatusEnum.indexOfEnumerator("WellStatus")).key(wellStatus)
                    : projectData->WCONINJE()[k].WellStatus();
            case WellControl: return  role == Qt::DisplayRole
                    ? projectData->WCONINJE()[k].WellControl().isNull()
                        ? ""
                        : wellControlEnum.enumerator(wellControlEnum.indexOfEnumerator("WellControl")).key(projectData->WCONINJE()[k].WellControl().toInt())
                    : projectData->WCONINJE()[k].WellControl();
            case WellRATE: return projectData->WCONINJE()[k].RATE();
            case WellRESV: return projectData->WCONINJE()[k].RESV();
            case WellBHP: return projectData->WCONINJE()[k].BHP();
        }

        return QVariant();
    }

    if(role == Qt::TextAlignmentRole) return QVariant(Qt::AlignHCenter | Qt::AlignVCenter);

    return QVariant();
}

QVariant WCONINJEModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(role == Qt::DisplayRole)
    {
        if(orientation == Qt::Horizontal)
        {
            switch (section)
            {
                case WellName: return tr("Имя скважины");
                case WellDate: return tr("Дата");
                case WellInjFluid: return tr("Фаза");
                case WellStatus: return tr("Статус");
                case WellControl: return tr("Режим управления");
                case WellRATE: return tr("Значение RATE");
                case WellRESV: return tr("Значение RESV");
                case WellBHP: return tr("Значение BHP");
            }
        }
    }

    if(role == Qt::TextAlignmentRole) return QVariant(Qt::AlignHCenter | Qt::AlignVCenter);

    return QVariant();
}

bool WCONINJEModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(index.isValid() && role == Qt::EditRole)
    {
        if(!index.parent().isValid())
        {
            int group = groups[index.row()];

            switch (index.column())
            {
                case WellName:
                    projectData->WCONINJE()[group].SetWellName(value.toString());
                    HandleWellNameChanged(index);
                    break;
                case WellDate:
                    projectData->WCONINJE()[group].SetDate(value.toDateTime());
                    break;
                case WellInjFluid:
                    projectData->WCONINJE()[group].SetInjFluid(value);
                    break;
                case WellStatus:
                    projectData->WCONINJE()[group].SetWellStatus(value);
                    break;
                case WellControl:
                    projectData->WCONINJE()[group].SetWellControl(value);
                    break;
                case WellRATE:
                    projectData->WCONINJE()[group].SetRATE(value);
                    break;
                case WellRESV:
                    projectData->WCONINJE()[group].SetRESV(value);
                    break;
                case WellBHP:
                    projectData->WCONINJE()[group].SetBHP(value);
                    break;
            }

            emit dataChanged(index, index);

            return true;
        }
    }

    return false;
}

Qt::ItemFlags WCONINJEModel::flags(const QModelIndex &index) const
{
    auto opt = QAbstractItemModel::flags(index);;

    if(index.isValid() && !index.parent().isValid())
        opt |= Qt::ItemIsEditable;

    return opt;
}

bool WCONINJEModel::insertRows(int row, int count, const QModelIndex &parent)
{
    if(!parent.isValid())
    {
        beginInsertRows(parent, row, row + count - 1);

        for(int i = row; i < row + count; i++)
        {
            if(removed.size() > 0)
            {
                int j = removed[0];

                WCONINJEData &wconinje = projectData->WCONINJE()[j];
                wconinje.InitVariables();
                groups.insert(i, j);
                indexes.insert(i, QVector<int>());

                removed.pop_front();
            }
            else
            {
                int j = projectData->WCONINJE().size();

                WCONINJEData wconinje;
                groups.insert(i, j);
                indexes.insert(i, QVector<int>());
                projectData->WCONINJE().push_back(wconinje);
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

bool WCONINJEModel::removeRows(int row, int count, const QModelIndex &parent)
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
