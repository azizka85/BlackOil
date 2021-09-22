#ifndef SGOFFORM_H
#define SGOFFORM_H

#include <qmetaobject.h>
#include <qvector.h>

#include <qwidget.h>
#include <qlabel.h>
#include <qcombobox.h>
#include <qtoolbar.h>
#include <qshortcut.h>
#include <qvalueaxis.h>
#include <qlegendmarker.h>
#include <QtCharts/qlineseries.h>
#include <QtCharts/qscatterseries.h>
#include <QtCharts/qchart.h>
#include <QtCharts/qchartview.h>

#include <qsortfilterproxymodel.h>

#include <qvxymodelmapper.h>

#include <projectmodel.h>

#include <desktop_global.h>

using namespace QtCharts;

using namespace BlackOil::Model;

namespace Ui {
class SGOFForm;
}

namespace BlackOil {
namespace Desktop {
namespace Views {
namespace Controls {

class DESKTOP_EXPORT SGOFForm : public QWidget
{
    Q_OBJECT
    Q_ENUMS(Series)
public:
    explicit SGOFForm(ProjectModel *project, QWidget *parent = nullptr);
    ~SGOFForm();

    enum Series { SeriesKrG, SeriesKrO, SeriesPcOG };

    QVector<QLineSeries *> *Lines();
    QVector<QScatterSeries *> *Scatters();

    QAction *DisplayFigureSettingsAction();

public slots:
    void HandleDisplayAction();
    void HandleSplitAction();
    void HandleDeleteRow();
    void HandleInsertRow();
    void HandleMinMax(int column, QVariant min, QVariant max);
    void HandleLineLegendVisibleChanged();
    void HandleScatterLegendVisibleChanged();

protected:
    void HandleLegendVisible(QLegendMarker *lineLegend, QScatterSeries *scatterSeries, QLegendMarker *scatterLegend);

protected:
    Ui::SGOFForm *ui;
    ProjectModel *project;
    QValueAxis *axisPc;
    QChartView *chartView;
    QVector<QLineSeries *> lines;
    QVector<QScatterSeries *> scatters;
};

}}}}

#endif // SGOFFORM_H
