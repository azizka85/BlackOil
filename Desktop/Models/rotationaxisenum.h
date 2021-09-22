#ifndef ROTATIONAXISENUM_H
#define ROTATIONAXISENUM_H

#include <qmetaobject.h>

#include <qabstractitemmodel.h>

#include <desktop_global.h>

namespace BlackOil {
namespace Desktop {
namespace Models {

class DESKTOP_EXPORT RotationAxisEnum : public QAbstractListModel
{
    Q_OBJECT
    Q_ENUMS(RotationAxis)
public:
    explicit RotationAxisEnum(QObject *parent = nullptr);

    enum RotationAxis {OXY, OX, OY, OZ};

    // QAbstractItemModel interface
public:
    int rowCount(const QModelIndex &) const override;
    QVariant data(const QModelIndex &index, int role) const override;
};

}}}

#endif // ROTATIONAXISENUM_H
