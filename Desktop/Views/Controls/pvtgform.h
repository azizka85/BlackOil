#ifndef PVTGFORM_H
#define PVTGFORM_H

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
class PVTGForm;
}

namespace BlackOil {
namespace Desktop {
namespace Views {
namespace Controls {

class DESKTOP_EXPORT PVTGForm : public QWidget
{
    Q_OBJECT
    Q_ENUMS(Series)
public:
    explicit PVTGForm(ProjectModel *project, QWidget *parent = nullptr);
    ~PVTGForm();

    enum Series { SeriesBG, SeriesMG };

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
    Ui::PVTGForm *ui;
    ProjectModel *project;
    QValueAxis *axisPG, *axisBG, *axisMG;
    QChartView *chartView;
    QVector<QLineSeries *> lines;
    QVector<QScatterSeries *> scatters;
};

}}}}

#endif // PVTGFORM_H
