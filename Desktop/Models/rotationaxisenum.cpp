#include "rotationaxisenum.h"

namespace BlackOil {
namespace Desktop {
namespace Models {

RotationAxisEnum::RotationAxisEnum(QObject *parent) : QAbstractListModel(parent) { }

int RotationAxisEnum::rowCount(const QModelIndex &) const
{
    return staticMetaObject.enumerator(staticMetaObject.indexOfEnumerator("RotationAxis")).keyCount();
}

QVariant RotationAxisEnum::data(const QModelIndex &index, int role) const
{
    if(index.isValid() && role == Qt::DisplayRole)
        return staticMetaObject.enumerator(staticMetaObject.indexOfEnumerator("RotationAxis")).key(index.row());

    return QVariant();
}

}}}
