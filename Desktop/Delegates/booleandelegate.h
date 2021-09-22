#ifndef BOOLEANDELEGATE_H
#define BOOLEANDELEGATE_H

#include <qcombobox.h>

#include <qabstractitemmodel.h>

#include <qstyleditemdelegate.h>

#include <desktop_global.h>

namespace BlackOil {
namespace Desktop {
namespace Delegates {

class DESKTOP_EXPORT BooleanDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit BooleanDelegate(QAbstractItemModel *model, QObject *parent = nullptr);

protected slots:
    void HandleIndexChanged(int index);

protected:
    QAbstractItemModel *model;

    // QAbstractItemDelegate interface
public:
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &, const QModelIndex &index) const override;
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &) const override;
    void setEditorData(QWidget *editor, const QModelIndex &index) const override;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override;
};

}}}

#endif // BOOLEANDELEGATE_H
