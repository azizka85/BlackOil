#ifndef FIGURESETTINGSMODEL_H
#define FIGURESETTINGSMODEL_H

#include <qmetaobject.h>
#include <qvector.h>

#include <QtCharts/qlineseries.h>
#include <QtCharts/qscatterseries.h>

#include <qabstractitemmodel.h>

#include <desktop_global.h>

using namespace QtCharts;

namespace BlackOil {
namespace Desktop {
namespace Models {

class DESKTOP_EXPORT FigureSettingsModel : public QAbstractTableModel
{
    Q_OBJECT
    Q_ENUMS(Columns)
public:
    explicit FigureSettingsModel(QVector<QLineSeries *> *lines, QVector<QScatterSeries *> *scatters, QObject *parent = nullptr);

    enum Columns { Name, Display, LineColor, LineWidth, MarkerDisplay, MarkerColor, MarkerBorderColor, MarkerSize };

protected:
    QVector<QLineSeries *> *lines;
    QVector<QScatterSeries *> *scatters;

    // QAbstractItemModel interface
public:
    int rowCount(const QModelIndex &) const override;
    int columnCount(const QModelIndex &) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role) override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
};

}}}

#endif // FIGURESETTINGSMODEL_H
