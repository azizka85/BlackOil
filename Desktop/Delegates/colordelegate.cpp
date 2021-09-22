#include "colordelegate.h"

namespace BlackOil {
namespace Desktop {
namespace Delegates {

ColorDelegate::ColorDelegate(QObject *parent) : QStyledItemDelegate(parent)
{

}

void ColorDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    painter->setBrush(QBrush(index.data(Qt::DisplayRole).value<QColor>()));
    painter->drawRect(option.rect);
}

bool ColorDelegate::editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index)
{
    if(event->type() == QEvent::MouseButtonRelease)
    {
        model->setData(index,
                       QColorDialog::getColor(model->data(index, Qt::EditRole).value<QColor>(), nullptr, tr("Выберите цвет")),
                       Qt::EditRole);

        return true;
    }

    return QStyledItemDelegate::editorEvent(event, model, option, index);
}

}}}
