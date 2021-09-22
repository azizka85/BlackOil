#include "figuresettingsmodel.h"

namespace BlackOil {
namespace Desktop {
namespace Models {

FigureSettingsModel::FigureSettingsModel(QVector<QLineSeries *> *lines, QVector<QScatterSeries *> *scatters, QObject *parent) : QAbstractTableModel(parent)
{
    this->lines = lines;
    this->scatters = scatters;
}

int FigureSettingsModel::rowCount(const QModelIndex &) const
{
    return lines->size();
}

int FigureSettingsModel::columnCount(const QModelIndex &) const
{
    return staticMetaObject.enumerator(staticMetaObject.indexOfEnumerator("Columns")).keyCount();
}

QVariant FigureSettingsModel::data(const QModelIndex &index, int role) const
{
    if(index.isValid() && (role == Qt::DisplayRole || role == Qt::EditRole))
    {
        switch (index.column())
        {
            case Name: return lines->at(index.row())->name();
            case Display: return role == Qt::DisplayRole
                ? QVariant(lines->at(index.row())->isVisible() ? tr("Да") : tr("Нет"))
                : lines->at(index.row())->isVisible();
            case LineColor: return lines->at(index.row())->pen().color();
            case LineWidth: return lines->at(index.row())->pen().width();
            case MarkerDisplay: return role == Qt::DisplayRole
                ? QVariant(scatters->at(index.row())->isVisible() ? tr("Да") : tr("Нет"))
                : scatters->at(index.row())->isVisible();
            case MarkerColor: return scatters->at(index.row())->color();
            case MarkerBorderColor: return scatters->at(index.row())->borderColor();
            case MarkerSize: return scatters->at(index.row())->markerSize();
        }
    }

    if(role == Qt::TextAlignmentRole) return QVariant(Qt::AlignHCenter | Qt::AlignVCenter);

    return QVariant();
}

bool FigureSettingsModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(index.isValid() && role == Qt::EditRole)
    {
        switch (index.column())
        {
            case Name: lines->at(index.row())->setName(value.toString()); break;
            case Display: lines->at(index.row())->setVisible(value.toBool()); break;
            case LineColor: lines->at(index.row())->setColor(value.value<QColor>()); break;
            case LineWidth: lines->at(index.row())->setPen(QPen(QBrush(lines->at(index.row())->color()), value.toInt())); break;
            case MarkerDisplay: scatters->at(index.row())->setVisible(value.toBool()); break;
            case MarkerColor: scatters->at(index.row())->setColor(value.value<QColor>()); break;
            case MarkerBorderColor: scatters->at(index.row())->setBorderColor(value.value<QColor>()); break;
            case MarkerSize: scatters->at(index.row())->setMarkerSize(value.toDouble()); break;
        }

        return true;
    }

    return false;
}

QVariant FigureSettingsModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(role == Qt::DisplayRole || role == Qt::EditRole)
    {
        if(orientation == Qt::Horizontal)
        {
            switch (section)
            {
                case Name: return tr("Название");
                case Display: return tr("Показать линию");
                case LineColor: return tr("Цвет линии");
                case LineWidth: return tr("Толщина линии");
                case MarkerDisplay: return tr("Показать маркеры");
                case MarkerColor: return tr("Цвет маркеров");
                case MarkerBorderColor: return tr("Цвет линии маркеров");
                case MarkerSize: return tr("Размер маркеров");
            }
        }
    }

    return QVariant();
}

Qt::ItemFlags FigureSettingsModel::flags(const QModelIndex &index) const
{
    auto opt = QAbstractItemModel::flags(index);;

    if(index.isValid())
        opt |= Qt::ItemIsEditable;

    return opt;
}

}}}
