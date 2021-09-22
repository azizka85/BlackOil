#include "zlayermodel.h"

namespace BlackOil {
namespace Model {
namespace Grid {

ZLayerModel::ZLayerModel(QObject *parent) : QAbstractListModel(parent) { }

QVector<bool> &ZLayerModel::DisplayBlocks()
{
    return displayBlocks;
}

void ZLayerModel::InitVariables()
{
    beginResetModel();

    displayBlocks.clear();

    endResetModel();
}

void ZLayerModel::ProcessData(int n)
{
    beginResetModel();

    displayBlocks.fill(true, n);

    endResetModel();
}

void ZLayerModel::ProcessBeforeSave()
{

}

void ZLayerModel::Clear()
{
    int n = displayBlocks.size();

    if(n > 0)
    {
        for(int i = 0; i < n; i++) displayBlocks[i] = false;

        emit dataChanged(index(0), index(n-1));
    }
}

void ZLayerModel::CheckAll()
{
    int n = displayBlocks.size();

    if(n > 0)
    {
        for(int i = 0; i < n; i++) displayBlocks[i] = true;

        emit dataChanged(index(0), index(n-1));
    }
}

int ZLayerModel::rowCount(const QModelIndex &) const
{
    return displayBlocks.size();
}

QVariant ZLayerModel::data(const QModelIndex &index, int role) const
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

Qt::ItemFlags ZLayerModel::flags(const QModelIndex &index) const
{
    auto opt = QAbstractItemModel::flags(index);;

    if(index.isValid())
        opt |= Qt::ItemIsUserCheckable;

    return opt;
}

bool ZLayerModel::setData(const QModelIndex &index, const QVariant &value, int role)
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
