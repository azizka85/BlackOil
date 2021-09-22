#ifndef RPMENUM_H
#define RPMENUM_H

#include <qmetaobject.h>

#include <qabstractitemmodel.h>

#include <data_global.h>

namespace BlackOil {
namespace Data {
namespace Project {

class DATA_EXPORT RPMEnum : public QAbstractListModel
{
    Q_OBJECT
    Q_ENUMS(RPM)
public:
    explicit RPMEnum(QObject *parent = nullptr);

    enum RPM { Simple, Stone1, Stone2, Eclipse };

    // QAbstractItemModel interface
public:
    int rowCount(const QModelIndex &) const override;
    QVariant data(const QModelIndex &index, int role) const override;
};

}}}

#endif // RPMENUM_H
