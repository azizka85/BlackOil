#include "ylayermodel.h"

namespace BlackOil {
namespace Model {
namespace Grid {

YLayerModel::YLayerModel(QObject *parent) : QAbstractListModel(parent) { }

QVector<bool> &YLayerModel::DisplayBlocks()
{
    return displayBlocks;
}

void YLayerModel::InitVariables()
{
    beginResetModel();

    displayBlocks.clear();

    endResetModel();
}

void YLayerModel::ProcessData(int n)
{
    beginResetModel();

    displayBlocks.fill(true, n);

    endResetModel();
}

void YLayerModel::ProcessBeforeSave()
{

}

void YLayerModel::Clear()
{
    int n = displayBlocks.size();

    if(n > 0)
    {
        for(int i = 0; i < n; i++) displayBlocks[i] = false;

        emit dataChanged(index(0), index(n-1));
    }
}

void YLayerModel::CheckAll()
{
    int n = displayBlocks.size();

    if(n > 0)
    {
        for(int i = 0; i < n; i++) displayBlocks[i] = true;

        emit dataChanged(index(0), index(n-1));
    }
}

int YLayerModel::rowCount(const QModelIndex &) const
{
    return displayBlocks.size();
}

QVariant YLayerModel::data(const QModelIndex &index, int role) const
{
    if(index.isValid())
    {
        if(role == Qt::DisplayRole)
            return index.row() + 1;
        else if(role == Qt::CheckStateRole)
            return displayBlocks[index.row()] ? Qt::Checked : Qt::Unchecked;
        else if(role == Qt::UserRole)
            return displayBlocks[index.row()];
    }

    return QVariant();
}

Qt::ItemFlags YLayerModel::flags(const QModelIndex &index) const
{
    auto opt = QAbstractItemModel::flags(index);;

    if(index.isValid())
        opt |= Qt::ItemIsUserCheckable;

    return opt;
}

bool YLayerModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(index.isValid() && role == Qt::CheckStateRole)
    {
        displayBlocks[index.row()] = value.toInt() != Qt::Unchecked;

        emit dataChanged(index, index);

        return true;
    }

    return false;
}

}}}
