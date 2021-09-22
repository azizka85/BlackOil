#include "booleandelegate.h"

namespace BlackOil {
namespace Desktop {
namespace Delegates {

BooleanDelegate::BooleanDelegate(QAbstractItemModel *model, QObject *parent) : QStyledItemDelegate(parent)
{
    this->model = model;
}

void BooleanDelegate::HandleIndexChanged(int index)
{
    auto editor = static_cast<QComboBox *>(sender());

    auto modelIndex = editor->property("index").toModelIndex();

    model->setData(modelIndex, index == 0, Qt::EditRole);
}

QWidget *BooleanDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &, const QModelIndex &index) const
{
    auto comboBox = new QComboBox(parent);

    comboBox->addItem(tr("Да"));
    comboBox->addItem(tr("Нет"));

    comboBox->setProperty("index", index);

    connect(comboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(HandleIndexChanged(int)));

    return comboBox;
}

void BooleanDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &) const
{
    editor->setGeometry(option.rect);
}

void BooleanDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    static_cast<QComboBox *>(editor)->setCurrentIndex(index.model()->data(index, Qt::EditRole).toBool() ? 0 : 1);
}

void BooleanDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    model->setData(index, static_cast<QComboBox *>(editor)->currentIndex() == 0, Qt::EditRole);
}

}}}
