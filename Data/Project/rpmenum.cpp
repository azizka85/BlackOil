#include "rpmenum.h"

namespace BlackOil {
namespace Data {
namespace Project {

RPMEnum::RPMEnum(QObject *parent) : QAbstractListModel(parent)
{

}

int RPMEnum::rowCount(const QModelIndex &) const
{
    return staticMetaObject.enumerator(staticMetaObject.indexOfEnumerator("RPM")).keyCount();
}

QVariant RPMEnum::data(const QModelIndex &index, int role) const
{
    if(index.isValid() && role == Qt::DisplayRole)
    {
        switch (index.row())
        {
            case Simple: return tr("Простая модель");
            case Stone1: return tr("Модель Стоуна 1");
            case Stone2: return tr("Модель Стоуна 2");
            case Eclipse: return tr("Модель Eclipse");
        }
    }

    return QVariant();
}

}}}
