#include "welspecsmodel.h"

namespace BlackOil {
namespace Model {
namespace Wells {

WELSPECSModel::WELSPECSModel(ProjectData *projectData, QObject *parent) : QAbstractItemModel(parent)
{
    this->projectData = projectData;
}

QVector<int> WELSPECSModel::WELSPECSIndexes()
{
    QVector<int> result;

    for(int i = 0; i < indexes.size(); i++)
        result.append(indexes[i]);

    return result;
}

void WELSPECSModel::InitVariables()
{
    beginResetModel();

    removed.clear();
    groups.clear();
    indexes.clear();

    endResetModel();
}

void WELSPECSModel::ProcessData()
{
    beginResetModel();

    QHash<QString, int> groupMaps;

    for(auto i = 0; i < projectData->WELSPECS().size(); i++)
    {
        auto welspecs = projectData->WELSPECS()[i];
        auto group = welspecs.WellGroup().isEmpty() ? DefaultValues::WELSPECS_WellGroup : welspecs.WellGroup();

        if(!groupMaps.contains(group))
        {
            groupMaps[group] = groups.size();
            groups.push_back(group);
            indexes.push_back(QVector<int>());
        }

        int index = groupMaps[group];

        indexes[index].push_back(i);
    }

    endResetModel();
}

void WELSPECSModel::ProcessBeforeSave()
{

}

QModelIndex WELSPECSModel::index(int row, int column, const QModelIndex &parent) const
{    
    if(!hasIndex(row, column, parent))
        return QModelIndex();

    if(parent.isValid() && !parent.parent().isValid() && parent.row() >= 0 && parent.row() < groups.size())
        return createIndex(row, column, (void *)&groups[parent.row()]);
    else
        return createIndex(row, column);
}

QModelIndex WELSPECSModel::parent(const QModelIndex &child) const
{
    if(!child.isValid())
        return QModelIndex();

    auto group = (QString *)child.internalPointer();    

    if(!group)
        return QModelIndex();

    int index = group - groups.begin();

    return createIndex(index, 0);
}

int WELSPECSModel::rowCount(const QModelIndex &parent) const
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

int WELSPECSModel::columnCount(const QModelIndex &) const
{
    return staticMetaObject.enumerator(staticMetaObject.indexOfEnumerator("Columns")).keyCount();
}

QVariant WELSPECSModel::data(const QModelIndex &index, int role) const
{
    if(index.isValid() && (role == Qt::DisplayRole || role == Qt::EditRole))
    {
        auto group = (QString *)index.internalPointer();

        int i = group - groups.begin();

        if(i < 0 || i >= groups.size())
        {
            if(index.column() == 0)
                return groups[index.row()] + (role == Qt::DisplayRole ? tr(" (Количество: %1)").arg(indexes[index.row()].size()) : "");
            else
                return QVariant();
        }
        else
        {
            if(index.column() == 0)
            {
                return QVariant();
            }
            else
            {
                int j = indexes[i][index.row()];

                switch (index.column())
                {
                    case WellName: return projectData->WELSPECS()[j].WellName();
                    case WellDate: return projectData->WELSPECS()[j].Date().date();
                    case WellI: return projectData->WELSPECS()[j].I();
                    case WellJ: return projectData->WELSPECS()[j].J();
                    case WellDepth: return projectData->WELSPECS()[j].Depth();
                }

                return QVariant();
            }
        }
    }

    if(role == Qt::TextAlignmentRole) return QVariant(Qt::AlignHCenter | Qt::AlignVCenter);

    return QVariant();
}

QVariant WELSPECSModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(role == Qt::DisplayRole)
    {
        if(orientation == Qt::Horizontal)
        {
            switch (section)
            {
                case WellGroup: return tr("Группа скважины");
                case WellName: return tr("Имя скважины");
                case WellDate: return tr("Дата");
                case WellI: return tr("I - координата");
                case WellJ: return tr("J - координата");
                case WellDepth: return tr("Глубина");
            }
        }
    }

    if(role == Qt::TextAlignmentRole) return QVariant(Qt::AlignHCenter | Qt::AlignVCenter);

    return QVariant();
}

bool WELSPECSModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(index.isValid() && role == Qt::EditRole)
    {
        auto group = (QString *)index.internalPointer();

        int i = group - groups.begin();

        if(((i < 0 || i >= groups.size()) && index.column() == 0) || (i >= 0 && i < groups.size() && index.column() > 0))
        {
            if((i < 0 || i >= groups.size()) && index.column() == 0)
            {
                groups[index.row()] = value.toString();

                for(int j: indexes[index.row()]) projectData->WELSPECS()[j].SetWellGroup(groups[index.row()]);
            }
            else if(i >= 0 && i < groups.size() && index.column() > 0)
            {
                int j = indexes[i][index.row()];

                switch (index.column())
                {
                    case WellName:
                        projectData->WELSPECS()[j].SetWellName(value.toString());
                        emit WELSPECSChanged(j);
                        break;
                    case WellDate:
                        projectData->WELSPECS()[j].SetDate(value.toDateTime());
                        break;
                    case WellI:
                        projectData->WELSPECS()[j].SetI(value.toInt());
                        break;
                    case WellJ:
                        projectData->WELSPECS()[j].SetJ(value.toInt());
                        break;
                    case WellDepth:
                        projectData->WELSPECS()[j].SetDepth(value);
                        break;
                }
            }

            emit dataChanged(index, index);

            return true;
        }
    }

    return false;
}

Qt::ItemFlags WELSPECSModel::flags(const QModelIndex &index) const
{
    auto opt = QAbstractItemModel::flags(index);;

    if(index.isValid() && ((index.parent().isValid() && index.column() > 0) || (!index.parent().isValid() && index.column() == 0)))
        opt |= Qt::ItemIsEditable;

    return opt;
}

bool WELSPECSModel::insertRows(int row, int count, const QModelIndex &parent)
{
    if(parent.isValid())
    {
        beginInsertRows(parent, row, row + count - 1);

        for(int i = 0; i < count; i++)
        {
            if(removed.size() > 0)
            {
                int j = removed[0];

                WELSPECSData &welspecs = projectData->WELSPECS()[j];
                welspecs.InitVariables();
                welspecs.SetWellGroup(groups[parent.row()]);
                indexes[parent.row()].insert(indexes[parent.row()].begin() + row, j);

                removed.pop_front();

                emit WELSPECSInserted(j);
            }
            else
            {
                int j = projectData->WELSPECS().size();

                WELSPECSData welspecs;
                welspecs.SetWellGroup(groups[parent.row()]);
                indexes[parent.row()].insert(indexes[parent.row()].begin() + row, j);
                projectData->WELSPECS().push_back(welspecs);

                emit WELSPECSInserted(j);
            }

            row++;
        }

        endInsertRows();
    }
    else
    {        
        beginInsertRows(parent, row, row);

        groups.insert(row, 1, DefaultValues::WELSPECS_WellGroup);
        indexes.insert(row, 1, QVector<int>());

        endInsertRows();
    }

    // qDebug() << "Indexes: " << indexes;
    // qDebug() << "Groups: " << groups;
    // qDebug() << inserted;

    return true;
}

bool WELSPECSModel::removeRows(int row, int count, const QModelIndex &parent)
{
    beginRemoveRows(parent, row, row + count - 1);

    if(parent.isValid())
    {
        for(int i = 0; i < count; i++)
        {
            int j = indexes[parent.row()][row];

            removed.push_back(j);
            indexes[parent.row()].remove(row);

            emit WELSPECSRemoved(j);
        }
    }
    else
    {
        for(int i = 0; i < count; i++)
        {
            while(indexes[row].size() > 0)
            {
                int j = indexes[row][0];

                removed.push_back(j);
                indexes[row].pop_front();

                emit WELSPECSRemoved(j);
            }

            groups.remove(row);
            indexes.remove(row);
        }
    }

    endRemoveRows();

    // qDebug() << "Indexes: " << indexes;
    // qDebug() << "Groups: " << groups;

    return true;
}

}}}
