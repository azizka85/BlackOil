#ifndef COLORDELEGATE_H
#define COLORDELEGATE_H

#include <qcolor.h>

#include <qevent.h>

#include <qpainter.h>

#include <qcolordialog.h>

#include <qstyleditemdelegate.h>

#include <desktop_global.h>

namespace BlackOil {
namespace Desktop {
namespace Delegates {

class DESKTOP_EXPORT ColorDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit ColorDelegate(QObject *parent = nullptr);

    // QAbstractItemDelegate interface
public:
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    bool editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index) override;
};

}}}

#endif // COLORDELEGATE_H
