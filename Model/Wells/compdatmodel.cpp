#include "compdatmodel.h"

namespace BlackOil {
namespace Model {
namespace Wells {

COMPDATModel::COMPDATModel(ProjectData *projectData, WELSPECSModel *welspecs, QObject *parent) : QAbstractItemModel(parent)
{
    this->projectData = projectData;
    this->welspecs = welspecs;

    connect(welspecs, SIGNAL(WELSPECSInserted(int)), this, SLOT(HandleWELSPECSInserted(int)));
    connect(welspecs, SIGNAL(WELSPECSRemoved(int)), this, SLOT(HandleWELSPECSRemoved(int)));
    connect(welspecs, SIGNAL(WELSPECSChanged(int)), this, SLOT(HandleWELSPECSChanged(int)));
}

void COMPDATModel::InitVariables()
{
    beginResetModel();

    removed.clear();
    groups.clear();
    indexes.clear();

    endResetModel();
}

void COMPDATModel::ProcessData()
{
    beginResetModel();

    groups.resize(projectData->COMPDAT().size());
    indexes.resize(projectData->COMPDAT().size());

    for(int i = 0; i < projectData->COMPDAT().size(); i++)
        groups[i] = i;

    for(int i = 0; i < projectData->WELSPECS().size(); i++)
        for(int j = 0; j < groups.size(); j++)
            if(CheckWELSPECSMatch(j, i)) indexes[j].push_back(i);

    endResetModel();
}

void COMPDATModel::ProcessBeforeSave()
{

}

void COMPDATModel::HandleWELSPECSInserted(int welspecsIndex)
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

void COMPDATModel::HandleWELSPECSRemoved(int welspecsIndex)
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

void COMPDATModel::HandleWELSPECSChanged(int welspecsIndex)
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

bool COMPDATModel::CheckWELSPECSMatch(int index, int welspecsIndex)
{
    int result = 0;

    int group = groups[index];

    QString search = projectData->COMPDAT()[group].WellName().replace("*", "");

    if(projectData->COMPDAT()[group].WellName().startsWith("*") && projectData->WELSPECS()[welspecsIndex].WellName().endsWith(search))
        result |= 1;

    if(projectData->COMPDAT()[group].WellName().endsWith("*") && projectData->WELSPECS()[welspecsIndex].WellName().startsWith(search))
        result |= 2;

    if(projectData->WELSPECS()[welspecsIndex].WellName() == search)
        result |= 4;

    return result > 0;
}

void COMPDATModel::HandleWellNameChanged(QModelIndex index)
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

QModelIndex COMPDATModel::index(int row, int column, const QModelIndex &parent) const
{
    if(!hasIndex(row, column, parent))
        return QModelIndex();

    if(parent.isValid() && !parent.parent().isValid() && parent.row() >= 0 && parent.row() < indexes.size())
        return createIndex(row, column, (void *)&groups[parent.row()]);
    else
        return createIndex(row, column);
}

QModelIndex COMPDATModel::parent(const QModelIndex &child) const
{
    if(!child.isValid())
        return QModelIndex();

    auto group = (int *)child.internalPointer();

    if(!group)
        return QModelIndex();

    int index = group - groups.begin();

    return createIndex(index, 0);
}

int COMPDATModel::rowCount(const QModelIndex &parent) const
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

int COMPDATModel::columnCount(const QModelIndex &) const
{
    return staticMetaObject.enumerator(staticMetaObject.indexOfEnumerator("Columns")).keyCount();
}

QVariant COMPDATModel::data(const QModelIndex &index, int role) const
{
    if(index.isValid() && (role == Qt::DisplayRole || role == Qt::EditRole))
    {
        auto group = (int *)index.internalPointer();

        int i = group - groups.begin();
        int k = i < 0 || i >= groups.size() ? groups[index.row()] : groups[i];

        auto wellEnum = WellStatusEnum::staticMetaObject;

        int wellStatus = projectData->COMPDAT()[k].WellStatus().isNull()
                ? DefaultValues::COMPDAT_WellStatus
                : projectData->COMPDAT()[k].WellStatus().toInt();

        switch (index.column())
        {
            case WellName: return i < 0 || i >= groups.size()
                    ? projectData->COMPDAT()[k].WellName() + (role == Qt::DisplayRole ? tr(" (Количество: %1)").arg(indexes[index.row()].size()) : "")
                    : projectData->WELSPECS()[indexes[i][index.row()]].WellName();
            case WellDate: return projectData->COMPDAT()[k].Date().date();
            case WellI: return projectData->COMPDAT()[k].I();
            case WellJ: return projectData->COMPDAT()[k].J();
            case WellK1: return projectData->COMPDAT()[k].K1();
            case WellK2: return projectData->COMPDAT()[k].K2();
            case WellStatus: return role == Qt::DisplayRole
                    ? wellEnum.enumerator(wellEnum.indexOfEnumerator("WellStatus")).key(wellStatus)
                    : projectData->COMPDAT()[k].WellStatus();
            case WellTranFactor: return projectData->COMPDAT()[k].TranFactor();
            case WellDiameter: return projectData->COMPDAT()[k].Diameter();
            case WellKh: return projectData->COMPDAT()[k].Kh();
            case WellSkinFactor: return projectData->COMPDAT()[k].SkinFactor().isNull()
                    ? DefaultValues::COMPDAT_SkinFactor
                    : projectData->COMPDAT()[k].SkinFactor().toDouble();
        }

        return QVariant();
    }

    if(role == Qt::TextAlignmentRole) return QVariant(Qt::AlignHCenter | Qt::AlignVCenter);

    return QVariant();
}

QVariant COMPDATModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(role == Qt::DisplayRole)
    {
        if(orientation == Qt::Horizontal)
        {
            switch (section)
            {
                case WellName: return tr("Имя скважины");
                case WellDate: return tr("Дата");
                case WellI: return tr("I - координата");
                case WellJ: return tr("J - координата");
                case WellK1: return tr("K1 - координата");
                case WellK2: return tr("K2 - координата");
                case WellStatus: return tr("Статус");
                case WellTranFactor: return tr("Коэффициент проводимости");
                case WellDiameter: return tr("Диаметр скважины");
                case WellKh: return tr("Kh");
                case WellSkinFactor: return tr("Скин фактор");
            }
        }
    }

    if(role == Qt::TextAlignmentRole) return QVariant(Qt::AlignHCenter | Qt::AlignVCenter);

    return QVariant();
}

bool COMPDATModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(index.isValid() && role == Qt::EditRole)
    {
        if(!index.parent().isValid())
        {
            int group = groups[index.row()];

            switch (index.column())
            {
                case WellName:
                    projectData->COMPDAT()[group].SetWellName(value.toString());
                    HandleWellNameChanged(index);
                    break;
                case WellDate:
                    projectData->COMPDAT()[group].SetDate(value.toDateTime());
                    break;
                case WellI:
                    projectData->COMPDAT()[group].SetI(value);
                    break;
                case WellJ:
                    projectData->COMPDAT()[group].SetJ(value);
                    break;
                case WellK1:
                    projectData->COMPDAT()[group].SetK1(value);
                    break;
                case WellK2:
                    projectData->COMPDAT()[group].SetK2(value);
                    break;
                case WellStatus:
                    projectData->COMPDAT()[group].SetWellStatus(value);
                    break;
                case WellTranFactor:
                    projectData->COMPDAT()[group].SetTranFactor(value);
                    break;
                case WellDiameter:
                    projectData->COMPDAT()[group].SetDiameter(value);
                    break;
                case WellKh:
                    projectData->COMPDAT()[group].SetKh(value);
                    break;
                case WellSkinFactor:
                    projectData->COMPDAT()[group].SetSkinFactor(value);
                    break;
            }

            emit dataChanged(index, index);

            return true;
        }
    }

    return false;
}

Qt::ItemFlags COMPDATModel::flags(const QModelIndex &index) const
{
    auto opt = QAbstractItemModel::flags(index);;

    if(index.isValid() && !index.parent().isValid())
        opt |= Qt::ItemIsEditable;

    return opt;
}

bool COMPDATModel::insertRows(int row, int count, const QModelIndex &parent)
{
    if(!parent.isValid())
    {        
        beginInsertRows(parent, row, row + count - 1);

        for(int i = row; i < row + count; i++)
        {
            if(removed.size() > 0)
            {
                int j = removed[0];

                COMPDATData &compdat = projectData->COMPDAT()[j];
                compdat.InitVariables();
                groups.insert(i, j);
                indexes.insert(i, QVector<int>());

                removed.pop_front();
            }
            else
            {
                int j = projectData->COMPDAT().size();

                COMPDATData compdat;
                groups.insert(i, j);
                indexes.insert(i, QVector<int>());
                projectData->COMPDAT().push_back(compdat);
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

bool COMPDATModel::removeRows(int row, int count, const QModelIndex &parent)
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
