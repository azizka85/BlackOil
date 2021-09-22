#include "swofform.h"
#include "ui_swofform.h"

namespace BlackOil {
namespace Desktop {
namespace Views {
namespace Controls {

SWOFForm::SWOFForm(ProjectModel *project, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SWOFForm)
{    
    this->project = project;

    ui->setupUi(this);

    auto model = new QSortFilterProxyModel(this);
    model->setSourceModel(project->SF()->SWOF());
    ui->Table->setModel(model);

    auto toolBar = new QToolBar(this);
    auto regionLabel = new QLabel(tr("Регион: "), this);
    auto regionCombobox = new QComboBox(this);
    auto rpmLabel = new QLabel(tr("МОП: "), this);
    auto rpmCombobox = new QComboBox(this);

    lines.resize(staticMetaObject.enumerator(staticMetaObject.indexOfEnumerator("Series")).keyCount());
    scatters.resize(staticMetaObject.enumerator(staticMetaObject.indexOfEnumerator("Series")).keyCount());

    lines[SeriesKrW] = new QLineSeries(this);
    lines[SeriesKrO] = new QLineSeries(this);
    lines[SeriesPcOW] = new QLineSeries(this);

    scatters[SeriesKrW] = new QScatterSeries(this);
    scatters[SeriesKrO] = new QScatterSeries(this);
    scatters[SeriesPcOW] = new QScatterSeries(this);

    chartView = new QChartView(new QChart(), this);

    chartView->chart()->addSeries(lines[SeriesKrW]);
    chartView->chart()->addSeries(lines[SeriesKrO]);
    chartView->chart()->addSeries(lines[SeriesPcOW]);

    chartView->chart()->addSeries(scatters[SeriesKrW]);
    chartView->chart()->legend()->markers(scatters[SeriesKrW])[0]->setVisible(false);
    chartView->chart()->addSeries(scatters[SeriesKrO]);
    chartView->chart()->legend()->markers(scatters[SeriesKrO])[0]->setVisible(false);
    chartView->chart()->addSeries(scatters[SeriesPcOW]);
    chartView->chart()->legend()->markers(scatters[SeriesPcOW])[0]->setVisible(false);

    auto axisS = new QValueAxis(this);
    auto axisKr = new QValueAxis(this);
    axisPc = new QValueAxis(this);

    axisS->setTitleText(tr("Насыщенность воды, д. ед."));
    axisS->setMin(0);
    axisS->setMax(1);
    axisS->setTickCount(6);
    axisS->setLinePenColor(QColor(50, 50, 50));
    axisS->setGridLineColor(QColor(150, 150, 150));
    axisS->setMinorTickCount(6);
    axisS->setMinorGridLineColor(QColor(200, 200, 200));

    axisKr->setTitleText(tr("Относительная фазовая проницаемость, д. ед."));
    axisKr->setMin(0);
    axisKr->setMax(1);
    axisKr->setTickCount(6);
    axisKr->setLinePenColor(QColor(50, 50, 50));
    axisKr->setGridLineColor(QColor(150, 150, 150));
    axisKr->setMinorTickCount(6);
    axisKr->setMinorGridLineColor(QColor(200, 200, 200));

    axisPc->setTitleText(tr("Капиллярное давление, Psia"));
    axisPc->setMin(0);
    axisPc->setMax(1);
    axisPc->setTickCount(6);
    axisPc->setLinePenColor(QColor(50, 50, 50));
    axisPc->setGridLineColor(QColor(150, 150, 150));
    axisPc->setMinorTickCount(6);
    axisPc->setMinorGridLineColor(QColor(200, 200, 200));

    chartView->chart()->addAxis(axisS, Qt::AlignBottom);
    chartView->chart()->addAxis(axisKr, Qt::AlignLeft);
    chartView->chart()->addAxis(axisPc, Qt::AlignRight);

    lines[SeriesKrW]->setName(tr("KrW"));
    lines[SeriesKrW]->attachAxis(axisS);
    lines[SeriesKrW]->attachAxis(axisKr);

    scatters[SeriesKrW]->setName(tr("KrW"));
    scatters[SeriesKrW]->setMarkerSize(5);
    scatters[SeriesKrW]->setMarkerShape(QScatterSeries::MarkerShapeRectangle);
    scatters[SeriesKrW]->setColor(lines[SeriesKrW]->color());
    scatters[SeriesKrW]->setBorderColor(lines[SeriesKrW]->color());
    scatters[SeriesKrW]->attachAxis(axisS);
    scatters[SeriesKrW]->attachAxis(axisKr);

    lines[SeriesKrO]->setName(tr("KrO"));
    lines[SeriesKrO]->attachAxis(axisS);
    lines[SeriesKrO]->attachAxis(axisKr);

    scatters[SeriesKrO]->setName(tr("KrO"));
    scatters[SeriesKrO]->setMarkerSize(5);
    scatters[SeriesKrO]->setMarkerShape(QScatterSeries::MarkerShapeRectangle);
    scatters[SeriesKrO]->setColor(lines[SeriesKrO]->color());
    scatters[SeriesKrO]->setBorderColor(lines[SeriesKrO]->color());
    scatters[SeriesKrO]->attachAxis(axisS);
    scatters[SeriesKrO]->attachAxis(axisKr);

    lines[SeriesPcOW]->setName(tr("Pc"));
    lines[SeriesPcOW]->attachAxis(axisS);
    lines[SeriesPcOW]->attachAxis(axisPc);

    scatters[SeriesPcOW]->setName("Pc");
    scatters[SeriesPcOW]->setMarkerSize(5);
    scatters[SeriesPcOW]->setMarkerShape(QScatterSeries::MarkerShapeRectangle);
    scatters[SeriesPcOW]->setColor(lines[SeriesPcOW]->color());
    scatters[SeriesPcOW]->setBorderColor(lines[SeriesPcOW]->color());
    scatters[SeriesPcOW]->attachAxis(axisS);
    scatters[SeriesPcOW]->attachAxis(axisPc);

    auto krwMapper = new QVXYModelMapper(this);
    auto krwScatterMapper = new QVXYModelMapper(this);
    auto kroMapper = new QVXYModelMapper(this);
    auto kroScatterMapper = new QVXYModelMapper(this);
    auto pcMapper = new QVXYModelMapper(this);
    auto pcScatterMapper = new QVXYModelMapper(this);

    krwMapper->setXColumn(SWOFModel::SWOFSw);
    krwMapper->setYColumn(SWOFModel::SWOFKrW);
    krwMapper->setSeries(lines[SeriesKrW]);
    krwMapper->setModel(project->SF()->SWOF());

    krwScatterMapper->setXColumn(SWOFModel::SWOFSw);
    krwScatterMapper->setYColumn(SWOFModel::SWOFKrW);
    krwScatterMapper->setSeries(scatters[SeriesKrW]);
    krwScatterMapper->setModel(project->SF()->SWOF());

    kroMapper->setXColumn(SWOFModel::SWOFSw);
    kroMapper->setYColumn(SWOFModel::SWOFKrO);
    kroMapper->setSeries(lines[SeriesKrO]);
    kroMapper->setModel(project->SF()->SWOF());

    kroScatterMapper->setXColumn(SWOFModel::SWOFSw);
    kroScatterMapper->setYColumn(SWOFModel::SWOFKrO);
    kroScatterMapper->setSeries(scatters[SeriesKrO]);
    kroScatterMapper->setModel(project->SF()->SWOF());

    pcMapper->setXColumn(SWOFModel::SWOFSw);
    pcMapper->setYColumn(SWOFModel::SWOFPcOW);
    pcMapper->setSeries(lines[SeriesPcOW]);
    pcMapper->setModel(project->SF()->SWOF());

    pcScatterMapper->setXColumn(SWOFModel::SWOFSw);
    pcScatterMapper->setYColumn(SWOFModel::SWOFPcOW);
    pcScatterMapper->setSeries(scatters[SeriesPcOW]);
    pcScatterMapper->setModel(project->SF()->SWOF());

    regionCombobox->setModel(project->SF()->SFRegion());
    rpmLabel->setToolTip(tr("Модель относительной проницаемости"));
    rpmCombobox->setModel(project->SF()->RPM());

    toolBar->setStyleSheet("margin: 3px");
    toolBar->addWidget(regionLabel);
    toolBar->addWidget(regionCombobox);
    toolBar->addSeparator();
    toolBar->addWidget(rpmLabel);
    toolBar->addWidget(rpmCombobox);

    layout()->setMenuBar(toolBar);

    addAction(ui->DisplayFigureAction);
    addAction(ui->DisplayTableAction);
    addAction(ui->SplitAction);
    addAction(ui->DisplayFigureSettingsAction);

    auto delShortcut = new QShortcut(QKeySequence(Qt::Key_Delete), ui->Table);
    auto insShortcut = new QShortcut(QKeySequence(Qt::Key_Insert), ui->Table);

    connect(delShortcut, SIGNAL(activated()), this, SLOT(HandleDeleteRow()));
    connect(insShortcut, SIGNAL(activated()), this, SLOT(HandleInsertRow()));

    connect(ui->DisplayFigureAction, SIGNAL(toggled(bool)), this, SLOT(HandleDisplayAction()));
    connect(ui->DisplayTableAction, SIGNAL(toggled(bool)), this, SLOT(HandleDisplayAction()));
    connect(ui->DisplayTableAction, SIGNAL(toggled(bool)), ui->Table, SLOT(setVisible(bool)));
    connect(ui->DisplayFigureAction, SIGNAL(toggled(bool)), chartView, SLOT(setVisible(bool)));
    connect(ui->SplitAction, SIGNAL(toggled(bool)), this, SLOT(HandleSplitAction()));

    connect(regionCombobox, SIGNAL(currentIndexChanged(int)), project->SF()->SWOF(), SLOT(SetRegion(int)));
    connect(project->SF()->SWOF(), SIGNAL(RegionChanged(int)), regionCombobox, SLOT(setCurrentIndex(int)));

    connect(project->SF()->SWOF(), SIGNAL(MinMaxChanged(int, QVariant, QVariant)), this, SLOT(HandleMinMax(int, QVariant, QVariant)));        

    connect(lines[SeriesKrW], SIGNAL(visibleChanged()), this, SLOT(HandleLineLegendVisibleChanged()));
    connect(lines[SeriesKrO], SIGNAL(visibleChanged()), this, SLOT(HandleLineLegendVisibleChanged()));
    connect(lines[SeriesPcOW], SIGNAL(visibleChanged()), this, SLOT(HandleLineLegendVisibleChanged()));

    connect(scatters[SeriesKrW], SIGNAL(visibleChanged()), this, SLOT(HandleScatterLegendVisibleChanged()));
    connect(scatters[SeriesKrO], SIGNAL(visibleChanged()), this, SLOT(HandleScatterLegendVisibleChanged()));
    connect(scatters[SeriesPcOW], SIGNAL(visibleChanged()), this, SLOT(HandleScatterLegendVisibleChanged()));

    ui->Table->setVisible(ui->DisplayTableAction->isChecked());    
    HandleDisplayAction();
    HandleSplitAction();

    ui->Splitter->insertWidget(0, chartView);
}

SWOFForm::~SWOFForm()
{
    delete ui;
}

QVector<QLineSeries *> *SWOFForm::Lines()
{
    return &lines;
}

QVector<QScatterSeries *> *SWOFForm::Scatters()
{
    return &scatters;
}

QAction *SWOFForm::DisplayFigureSettingsAction()
{
    return ui->DisplayFigureSettingsAction;
}

void SWOFForm::HandleDisplayAction()
{
    if(ui->DisplayTableAction->isChecked() || ui->DisplayFigureAction->isChecked())
        ui->SplitAction->setVisible(true);
    else
        ui->SplitAction->setVisible(false);
}

void SWOFForm::HandleSplitAction()
{
    if(ui->SplitAction->isChecked())
    {
        ui->SplitAction->setText(tr("Разделить вертикально"));
        ui->Splitter->setOrientation(Qt::Horizontal);
    }
    else
    {
        ui->SplitAction->setText(tr("Разделить горизонтально"));
        ui->Splitter->setOrientation(Qt::Vertical);
    }
}

void SWOFForm::HandleDeleteRow()
{
    for(auto index: ui->Table->selectionModel()->selectedIndexes()) ui->Table->model()->removeRow(index.row(), index.parent());
}

void SWOFForm::HandleInsertRow()
{
    if(ui->Table->selectionModel()->hasSelection())
    {
        for(auto index: ui->Table->selectionModel()->selectedIndexes())
            ui->Table->model()->insertRow(index.row(), index.parent());
    }
    else
    {
        ui->Table->model()->insertRow(0, QModelIndex());
    }
}

void SWOFForm::HandleMinMax(int column, QVariant min, QVariant max)
{
    if(column == SWOFModel::SWOFPcOW)
    {
        if(abs(max.toDouble() - min.toDouble()) < 1e-6)
        {
            axisPc->setMin(-1e-6);
            axisPc->setMax(1e-6);
        }
        else if(max.toDouble() - min.toDouble() < 1e-6 * min.toDouble())
        {
            axisPc->setMin((1 - 1e-6)*min.toDouble());
            axisPc->setMax((1 + 1e-6)*max.toDouble());
        }
        else
        {
            axisPc->setMin(min.toDouble());
            axisPc->setMax(max.toDouble());
        }
    }
}

void SWOFForm::HandleLineLegendVisibleChanged()
{
    auto lineSeries = static_cast<QLineSeries *>(sender());
    auto lineLegend = chartView->chart()->legend()->markers(lineSeries)[0];
    auto scatterSeries = scatters[lines.indexOf(lineSeries)];
    auto scatterLegend = chartView->chart()->legend()->markers(scatterSeries)[0];

    HandleLegendVisible(lineLegend, scatterSeries, scatterLegend);
}

void SWOFForm::HandleScatterLegendVisibleChanged()
{
    auto scatterSeries = static_cast<QScatterSeries *>(sender());
    auto scatterLegend = chartView->chart()->legend()->markers(scatterSeries)[0];
    auto lineLegend = chartView->chart()->legend()->markers(lines[scatters.indexOf(scatterSeries)])[0];

    HandleLegendVisible(lineLegend, scatterSeries, scatterLegend);
}

void SWOFForm::HandleLegendVisible(QLegendMarker *lineLegend, QScatterSeries *scatterSeries, QLegendMarker *scatterLegend)
{
    scatterLegend->setVisible(!lineLegend->isVisible() && scatterSeries->isVisible());
}

}}}}
