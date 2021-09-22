#ifndef SWOFFORM_H
#define SWOFFORM_H

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
class SWOFForm;
}

namespace BlackOil {
namespace Desktop {
namespace Views {
namespace Controls {

class DESKTOP_EXPORT SWOFForm : public QWidget
{
    Q_OBJECT
    Q_ENUMS(Series)
public:
    explicit SWOFForm(ProjectModel *project, QWidget *parent = nullptr);
    ~SWOFForm();

    enum Series { SeriesKrW, SeriesKrO, SeriesPcOW };

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
    Ui::SWOFForm *ui;
    ProjectModel *project;
    QValueAxis *axisPc;
    QChartView *chartView;
    QVector<QLineSeries *> lines;
    QVector<QScatterSeries *> scatters;
};

}}}}

#endif // SWOFFORM_H
