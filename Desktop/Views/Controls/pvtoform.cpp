#include "pvtoform.h"
#include "ui_pvtoform.h"

namespace BlackOil {
namespace Desktop {
namespace Views {
namespace Controls {

PVTOForm::PVTOForm(ProjectModel *project, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PVTOForm)
{
    this->project = project;

    ui->setupUi(this);

    auto model = new QSortFilterProxyModel(this);
    model->setSourceModel(project->PVT()->PVTO());
    ui->Table->setModel(model);

    auto toolBar = new QToolBar(this);
    auto regionLabel = new QLabel(tr("Регион: "), this);
    auto regionCombobox = new QComboBox(this);

    regionCombobox->setModel(project->PVT()->PVTRegion());

    toolBar->setStyleSheet("margin: 3px");
    toolBar->addWidget(regionLabel);
    toolBar->addWidget(regionCombobox);

    layout()->setMenuBar(toolBar);

    lines.resize(staticMetaObject.enumerator(staticMetaObject.indexOfEnumerator("Series")).keyCount());
    scatters.resize(staticMetaObject.enumerator(staticMetaObject.indexOfEnumerator("Series")).keyCount());

    lines[SeriesRS] = new QLineSeries(this);
    lines[SeriesBO] = new QLineSeries(this);
    lines[SeriesMO] = new QLineSeries(this);

    scatters[SeriesRS] = new QScatterSeries(this);
    scatters[SeriesBO] = new QScatterSeries(this);
    scatters[SeriesMO] = new QScatterSeries(this);

    chartView = new QChartView(new QChart(), this);

    chartView->chart()->addSeries(lines[SeriesRS]);
    chartView->chart()->addSeries(lines[SeriesBO]);
    chartView->chart()->addSeries(lines[SeriesMO]);

    chartView->chart()->addSeries(scatters[SeriesRS]);
    chartView->chart()->legend()->markers(scatters[SeriesRS])[0]->setVisible(false);
    chartView->chart()->addSeries(scatters[SeriesBO]);
    chartView->chart()->legend()->markers(scatters[SeriesBO])[0]->setVisible(false);
    chartView->chart()->addSeries(scatters[SeriesMO]);
    chartView->chart()->legend()->markers(scatters[SeriesMO])[0]->setVisible(false);

    axisPO = new QValueAxis(this);
    axisRS = new QValueAxis(this);
    axisBO = new QValueAxis(this);
    axisMO = new QValueAxis(this);

    axisPO->setTitleText(tr("Давление нефти, Psia"));
    axisPO->setMin(0);
    axisPO->setMax(1);
    axisPO->setTickCount(6);
    axisPO->setLinePenColor(QColor(50, 50, 50));
    axisPO->setGridLineColor(QColor(150, 150, 150));
    axisPO->setMinorTickCount(6);
    axisPO->setMinorGridLineColor(QColor(200, 200, 200));

    axisRS->setTitleText(tr("Растворимость газа, Mscf/stb"));
    axisRS->setMin(0);
    axisRS->setMax(1);
    axisRS->setTickCount(6);
    axisRS->setLinePenColor(QColor(50, 50, 50));
    axisRS->setGridLineColor(QColor(150, 150, 150));
    axisRS->setMinorTickCount(6);
    axisRS->setMinorGridLineColor(QColor(200, 200, 200));

    axisBO->setTitleText(tr("Объемный коэффициент нефти, RB/stb"));
    axisBO->setMin(0);
    axisBO->setMax(1);
    axisBO->setTickCount(6);
    axisBO->setLinePenColor(QColor(50, 50, 50));
    axisBO->setGridLineColor(QColor(150, 150, 150));
    axisBO->setMinorTickCount(6);
    axisBO->setMinorGridLineColor(QColor(200, 200, 200));

    axisMO->setTitleText(tr("Вязкость нефти, cpoise"));
    axisMO->setMin(0);
    axisMO->setMax(1);
    axisMO->setTickCount(6);
    axisMO->setLinePenColor(QColor(50, 50, 50));
    axisMO->setGridLineColor(QColor(150, 150, 150));
    axisMO->setMinorTickCount(6);
    axisMO->setMinorGridLineColor(QColor(200, 200, 200));

    chartView->chart()->addAxis(axisPO, Qt::AlignBottom);
    chartView->chart()->addAxis(axisBO, Qt::AlignLeft);
    chartView->chart()->addAxis(axisMO, Qt::AlignLeft);
    chartView->chart()->addAxis(axisRS, Qt::AlignRight);

    lines[SeriesRS]->setName(tr("RS"));
    lines[SeriesRS]->attachAxis(axisPO);
    lines[SeriesRS]->attachAxis(axisRS);

    scatters[SeriesRS]->setName(tr("RS"));
    scatters[SeriesRS]->setMarkerSize(5);
    scatters[SeriesRS]->setMarkerShape(QScatterSeries::MarkerShapeRectangle);
    scatters[SeriesRS]->setColor(lines[SeriesRS]->color());
    scatters[SeriesRS]->setBorderColor(lines[SeriesRS]->color());
    scatters[SeriesRS]->attachAxis(axisPO);
    scatters[SeriesRS]->attachAxis(axisRS);

    lines[SeriesBO]->setName(tr("BO"));
    lines[SeriesBO]->attachAxis(axisPO);
    lines[SeriesBO]->attachAxis(axisBO);

    scatters[SeriesBO]->setName(tr("BO"));
    scatters[SeriesBO]->setMarkerSize(5);
    scatters[SeriesBO]->setMarkerShape(QScatterSeries::MarkerShapeRectangle);
    scatters[SeriesBO]->setColor(lines[SeriesBO]->color());
    scatters[SeriesBO]->setBorderColor(lines[SeriesBO]->color());
    scatters[SeriesBO]->attachAxis(axisPO);
    scatters[SeriesBO]->attachAxis(axisBO);

    lines[SeriesMO]->setName(tr("MO"));
    lines[SeriesMO]->attachAxis(axisPO);
    lines[SeriesMO]->attachAxis(axisMO);

    scatters[SeriesMO]->setName("MO");
    scatters[SeriesMO]->setMarkerSize(5);
    scatters[SeriesMO]->setMarkerShape(QScatterSeries::MarkerShapeRectangle);
    scatters[SeriesMO]->setColor(lines[SeriesMO]->color());
    scatters[SeriesMO]->setBorderColor(lines[SeriesMO]->color());
    scatters[SeriesMO]->attachAxis(axisPO);
    scatters[SeriesMO]->attachAxis(axisMO);

    auto rsMapper = new QVXYModelMapper(this);
    auto rsScatterMapper = new QVXYModelMapper(this);
    auto boMapper = new QVXYModelMapper(this);
    auto boScatterMapper = new QVXYModelMapper(this);
    auto moMapper = new QVXYModelMapper(this);
    auto moScatterMapper = new QVXYModelMapper(this);

    rsMapper->setXColumn(PVTOModel::PVTOPO);
    rsMapper->setYColumn(PVTOModel::PVTORS);
    rsMapper->setSeries(lines[SeriesRS]);
    rsMapper->setModel(project->PVT()->PVTO());

    rsScatterMapper->setXColumn(PVTOModel::PVTOPO);
    rsScatterMapper->setYColumn(PVTOModel::PVTORS);
    rsScatterMapper->setSeries(scatters[SeriesRS]);
    rsScatterMapper->setModel(project->PVT()->PVTO());

    boMapper->setXColumn(PVTOModel::PVTOPO);
    boMapper->setYColumn(PVTOModel::PVTOBO);
    boMapper->setSeries(lines[SeriesBO]);
    boMapper->setModel(project->PVT()->PVTO());

    boScatterMapper->setXColumn(PVTOModel::PVTOPO);
    boScatterMapper->setYColumn(PVTOModel::PVTOBO);
    boScatterMapper->setSeries(scatters[SeriesBO]);
    boScatterMapper->setModel(project->PVT()->PVTO());

    moMapper->setXColumn(PVTOModel::PVTOPO);
    moMapper->setYColumn(PVTOModel::PVTOMO);
    moMapper->setSeries(lines[SeriesMO]);
    moMapper->setModel(project->PVT()->PVTO());

    moScatterMapper->setXColumn(PVTOModel::PVTOPO);
    moScatterMapper->setYColumn(PVTOModel::PVTOMO);
    moScatterMapper->setSeries(scatters[SeriesMO]);
    moScatterMapper->setModel(project->PVT()->PVTO());

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

    connect(regionCombobox, SIGNAL(currentIndexChanged(int)), project->PVT()->PVTO(), SLOT(SetRegion(int)));
    connect(project->PVT()->PVTO(), SIGNAL(RegionChanged(int)), regionCombobox, SLOT(setCurrentIndex(int)));

    connect(project->PVT()->PVTO(), SIGNAL(MinMaxChanged(int, QVariant, QVariant)), this, SLOT(HandleMinMax(int, QVariant, QVariant)));

    connect(lines[SeriesRS], SIGNAL(visibleChanged()), this, SLOT(HandleLineLegendVisibleChanged()));
    connect(lines[SeriesBO], SIGNAL(visibleChanged()), this, SLOT(HandleLineLegendVisibleChanged()));
    connect(lines[SeriesMO], SIGNAL(visibleChanged()), this, SLOT(HandleLineLegendVisibleChanged()));

    connect(scatters[SeriesRS], SIGNAL(visibleChanged()), this, SLOT(HandleScatterLegendVisibleChanged()));
    connect(scatters[SeriesBO], SIGNAL(visibleChanged()), this, SLOT(HandleScatterLegendVisibleChanged()));
    connect(scatters[SeriesMO], SIGNAL(visibleChanged()), this, SLOT(HandleScatterLegendVisibleChanged()));

    ui->Table->setVisible(ui->DisplayTableAction->isChecked());
    HandleDisplayAction();
    HandleSplitAction();

    ui->Splitter->insertWidget(0, chartView);
}

PVTOForm::~PVTOForm()
{
    delete ui;
}

QVector<QLineSeries *> *PVTOForm::Lines()
{
    return &lines;
}

QVector<QScatterSeries *> *PVTOForm::Scatters()
{
    return &scatters;
}

QAction *PVTOForm::DisplayFigureSettingsAction()
{
    return ui->DisplayFigureSettingsAction;
}

void PVTOForm::HandleDisplayAction()
{
    if(ui->DisplayTableAction->isChecked() || ui->DisplayFigureAction->isChecked())
        ui->SplitAction->setVisible(true);
    else
        ui->SplitAction->setVisible(false);
}

void PVTOForm::HandleSplitAction()
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

void PVTOForm::HandleDeleteRow()
{
    for(auto index: ui->Table->selectionModel()->selectedIndexes()) ui->Table->model()->removeRow(index.row(), index.parent());
}

void PVTOForm::HandleInsertRow()
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

void PVTOForm::HandleMinMax(int column, QVariant min, QVariant max)
{
    if(column == PVTOModel::PVTOPO)
    {
        if(abs(max.toDouble() - min.toDouble()) < 1e-6)
        {
            axisPO->setMin(-1e-6);
            axisPO->setMax(1e-6);
        }
        else if(max.toDouble() - min.toDouble() < 1e-6 * min.toDouble())
        {
            axisPO->setMin((1 - 1e-6)*min.toDouble());
            axisPO->setMax((1 + 1e-6)*max.toDouble());
        }
        else
        {
            axisPO->setMin(min.toDouble());
            axisPO->setMax(max.toDouble());
        }
    }
    else if(column == PVTOModel::PVTORS)
    {
        if(abs(max.toDouble() - min.toDouble()) < 1e-6)
        {
            axisRS->setMin(-1e-6);
            axisRS->setMax(1e-6);
        }
        else if(max.toDouble() - min.toDouble() < 1e-6 * min.toDouble())
        {
            axisRS->setMin((1 - 1e-6)*min.toDouble());
            axisRS->setMax((1 + 1e-6)*max.toDouble());
        }
        else
        {
            axisRS->setMin(min.toDouble());
            axisRS->setMax(max.toDouble());
        }
    }
    else if(column == PVTOModel::PVTOBO)
    {
        if(abs(max.toDouble() - min.toDouble()) < 1e-6)
        {
            axisBO->setMin(-1e-6);
            axisBO->setMax(1e-6);
        }
        else if(max.toDouble() - min.toDouble() < 1e-6 * min.toDouble())
        {
            axisBO->setMin((1 - 1e-6)*min.toDouble());
            axisBO->setMax((1 + 1e-6)*max.toDouble());
        }
        else
        {
            axisBO->setMin(min.toDouble());
            axisBO->setMax(max.toDouble());
        }
    }
    else if(column == PVTOModel::PVTOMO)
    {
        if(abs(max.toDouble() - min.toDouble()) < 1e-6)
        {
            axisMO->setMin(-1e-6);
            axisMO->setMax(1e-6);
        }
        else if(max.toDouble() - min.toDouble() < 1e-6 * min.toDouble())
        {
            axisMO->setMin((1 - 1e-6)*min.toDouble());
            axisMO->setMax((1 + 1e-6)*max.toDouble());
        }
        else
        {
            axisMO->setMin(min.toDouble());
            axisMO->setMax(max.toDouble());
        }
    }
}

void PVTOForm::HandleLineLegendVisibleChanged()
{
    auto lineSeries = static_cast<QLineSeries *>(sender());
    auto lineLegend = chartView->chart()->legend()->markers(lineSeries)[0];
    auto scatterSeries = scatters[lines.indexOf(lineSeries)];
    auto scatterLegend = chartView->chart()->legend()->markers(scatterSeries)[0];

    HandleLegendVisible(lineLegend, scatterSeries, scatterLegend);
}

void PVTOForm::HandleScatterLegendVisibleChanged()
{
    auto scatterSeries = static_cast<QScatterSeries *>(sender());
    auto scatterLegend = chartView->chart()->legend()->markers(scatterSeries)[0];
    auto lineLegend = chartView->chart()->legend()->markers(lines[scatters.indexOf(scatterSeries)])[0];

    HandleLegendVisible(lineLegend, scatterSeries, scatterLegend);
}

void PVTOForm::HandleLegendVisible(QLegendMarker *lineLegend, QScatterSeries *scatterSeries, QLegendMarker *scatterLegend)
{
    scatterLegend->setVisible(!lineLegend->isVisible() && scatterSeries->isVisible());
}

}}}}
