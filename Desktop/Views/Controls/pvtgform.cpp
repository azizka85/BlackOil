#include "pvtgform.h"
#include "ui_pvtgform.h"

namespace BlackOil {
namespace Desktop {
namespace Views {
namespace Controls {

PVTGForm::PVTGForm(ProjectModel *project, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PVTGForm)
{
    this->project = project;

    ui->setupUi(this);

    auto model = new QSortFilterProxyModel(this);
    model->setSourceModel(project->PVT()->PVTG());
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

    lines[SeriesBG] = new QLineSeries(this);
    lines[SeriesMG] = new QLineSeries(this);

    scatters[SeriesBG] = new QScatterSeries(this);
    scatters[SeriesMG] = new QScatterSeries(this);

    chartView = new QChartView(new QChart(), this);

    chartView->chart()->addSeries(lines[SeriesBG]);
    chartView->chart()->addSeries(lines[SeriesMG]);

    chartView->chart()->addSeries(scatters[SeriesBG]);
    chartView->chart()->legend()->markers(scatters[SeriesBG])[0]->setVisible(false);
    chartView->chart()->addSeries(scatters[SeriesMG]);
    chartView->chart()->legend()->markers(scatters[SeriesMG])[0]->setVisible(false);

    axisPG = new QValueAxis(this);
    axisBG = new QValueAxis(this);
    axisMG = new QValueAxis(this);

    axisPG->setTitleText(tr("Давление газа, Psia"));
    axisPG->setMin(0);
    axisPG->setMax(1);
    axisPG->setTickCount(6);
    axisPG->setLinePenColor(QColor(50, 50, 50));
    axisPG->setGridLineColor(QColor(150, 150, 150));
    axisPG->setMinorTickCount(6);
    axisPG->setMinorGridLineColor(QColor(200, 200, 200));

    axisBG->setTitleText(tr("Объемный коэффициент газа, RB/Mscf"));
    axisBG->setMin(0);
    axisBG->setMax(1);
    axisBG->setTickCount(6);
    axisBG->setLinePenColor(QColor(50, 50, 50));
    axisBG->setGridLineColor(QColor(150, 150, 150));
    axisBG->setMinorTickCount(6);
    axisBG->setMinorGridLineColor(QColor(200, 200, 200));

    axisMG->setTitleText(tr("Вязкость газа, cpoise"));
    axisMG->setMin(0);
    axisMG->setMax(1);
    axisMG->setTickCount(6);
    axisMG->setLinePenColor(QColor(50, 50, 50));
    axisMG->setGridLineColor(QColor(150, 150, 150));
    axisMG->setMinorTickCount(6);
    axisMG->setMinorGridLineColor(QColor(200, 200, 200));

    chartView->chart()->addAxis(axisPG, Qt::AlignBottom);
    chartView->chart()->addAxis(axisBG, Qt::AlignLeft);
    chartView->chart()->addAxis(axisMG, Qt::AlignRight);

    lines[SeriesBG]->setName(tr("BG"));
    lines[SeriesBG]->attachAxis(axisPG);
    lines[SeriesBG]->attachAxis(axisBG);

    scatters[SeriesBG]->setName(tr("BG"));
    scatters[SeriesBG]->setMarkerSize(5);
    scatters[SeriesBG]->setMarkerShape(QScatterSeries::MarkerShapeRectangle);
    scatters[SeriesBG]->setColor(lines[SeriesBG]->color());
    scatters[SeriesBG]->setBorderColor(lines[SeriesBG]->color());
    scatters[SeriesBG]->attachAxis(axisPG);
    scatters[SeriesBG]->attachAxis(axisBG);

    lines[SeriesMG]->setName(tr("MG"));
    lines[SeriesMG]->attachAxis(axisPG);
    lines[SeriesMG]->attachAxis(axisMG);

    scatters[SeriesMG]->setName("MG");
    scatters[SeriesMG]->setMarkerSize(5);
    scatters[SeriesMG]->setMarkerShape(QScatterSeries::MarkerShapeRectangle);
    scatters[SeriesMG]->setColor(lines[SeriesMG]->color());
    scatters[SeriesMG]->setBorderColor(lines[SeriesMG]->color());
    scatters[SeriesMG]->attachAxis(axisPG);
    scatters[SeriesMG]->attachAxis(axisMG);

    auto bgMapper = new QVXYModelMapper(this);
    auto bgScatterMapper = new QVXYModelMapper(this);
    auto mgMapper = new QVXYModelMapper(this);
    auto mgScatterMapper = new QVXYModelMapper(this);

    bgMapper->setXColumn(PVTGModel::PVTGPG);
    bgMapper->setYColumn(PVTGModel::PVTGBG);
    bgMapper->setSeries(lines[SeriesBG]);
    bgMapper->setModel(project->PVT()->PVTG());

    bgScatterMapper->setXColumn(PVTGModel::PVTGPG);
    bgScatterMapper->setYColumn(PVTGModel::PVTGBG);
    bgScatterMapper->setSeries(scatters[SeriesBG]);
    bgScatterMapper->setModel(project->PVT()->PVTG());

    mgMapper->setXColumn(PVTGModel::PVTGPG);
    mgMapper->setYColumn(PVTGModel::PVTGMG);
    mgMapper->setSeries(lines[SeriesMG]);
    mgMapper->setModel(project->PVT()->PVTG());

    mgScatterMapper->setXColumn(PVTGModel::PVTGPG);
    mgScatterMapper->setYColumn(PVTGModel::PVTGMG);
    mgScatterMapper->setSeries(scatters[SeriesMG]);
    mgScatterMapper->setModel(project->PVT()->PVTG());

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

    connect(regionCombobox, SIGNAL(currentIndexChanged(int)), project->PVT()->PVTG(), SLOT(SetRegion(int)));
    connect(project->PVT()->PVTG(), SIGNAL(RegionChanged(int)), regionCombobox, SLOT(setCurrentIndex(int)));

    connect(project->PVT()->PVTG(), SIGNAL(MinMaxChanged(int, QVariant, QVariant)), this, SLOT(HandleMinMax(int, QVariant, QVariant)));

    connect(lines[SeriesBG], SIGNAL(visibleChanged()), this, SLOT(HandleLineLegendVisibleChanged()));
    connect(lines[SeriesMG], SIGNAL(visibleChanged()), this, SLOT(HandleLineLegendVisibleChanged()));

    connect(scatters[SeriesBG], SIGNAL(visibleChanged()), this, SLOT(HandleScatterLegendVisibleChanged()));
    connect(scatters[SeriesMG], SIGNAL(visibleChanged()), this, SLOT(HandleScatterLegendVisibleChanged()));

    ui->Table->setVisible(ui->DisplayTableAction->isChecked());
    HandleDisplayAction();
    HandleSplitAction();

    ui->Splitter->insertWidget(0, chartView);
}

PVTGForm::~PVTGForm()
{
    delete ui;
}

QVector<QLineSeries *> *PVTGForm::Lines()
{
    return &lines;
}

QVector<QScatterSeries *> *PVTGForm::Scatters()
{
    return &scatters;
}

QAction *PVTGForm::DisplayFigureSettingsAction()
{
    return ui->DisplayFigureSettingsAction;
}

void PVTGForm::HandleDisplayAction()
{
    if(ui->DisplayTableAction->isChecked() || ui->DisplayFigureAction->isChecked())
        ui->SplitAction->setVisible(true);
    else
        ui->SplitAction->setVisible(false);
}

void PVTGForm::HandleSplitAction()
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

void PVTGForm::HandleDeleteRow()
{
    for(auto index: ui->Table->selectionModel()->selectedIndexes()) ui->Table->model()->removeRow(index.row(), index.parent());
}

void PVTGForm::HandleInsertRow()
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

void PVTGForm::HandleMinMax(int column, QVariant min, QVariant max)
{
    if(column == PVTGModel::PVTGPG)
    {
        if(abs(max.toDouble() - min.toDouble()) < 1e-6)
        {
            axisPG->setMin(-1e-6);
            axisPG->setMax(1e-6);
        }
        else if(max.toDouble() - min.toDouble() < 1e-6 * min.toDouble())
        {
            axisPG->setMin((1 - 1e-6)*min.toDouble());
            axisPG->setMax((1 + 1e-6)*max.toDouble());
        }
        else
        {
            axisPG->setMin(min.toDouble());
            axisPG->setMax(max.toDouble());
        }
    }
    else if(column == PVTGModel::PVTGBG)
    {
        if(abs(max.toDouble() - min.toDouble()) < 1e-6)
        {
            axisBG->setMin(-1e-6);
            axisBG->setMax(1e-6);
        }
        else if(max.toDouble() - min.toDouble() < 1e-6 * min.toDouble())
        {
            axisBG->setMin((1 - 1e-6)*min.toDouble());
            axisBG->setMax((1 + 1e-6)*max.toDouble());
        }
        else
        {
            axisBG->setMin(min.toDouble());
            axisBG->setMax(max.toDouble());
        }
    }
    else if(column == PVTGModel::PVTGMG)
    {
        if(abs(max.toDouble() - min.toDouble()) < 1e-6)
        {
            axisMG->setMin(-1e-6);
            axisMG->setMax(1e-6);
        }
        else if(max.toDouble() - min.toDouble() < 1e-6 * min.toDouble())
        {
            axisMG->setMin((1 - 1e-6)*min.toDouble());
            axisMG->setMax((1 + 1e-6)*max.toDouble());
        }
        else
        {
            axisMG->setMin(min.toDouble());
            axisMG->setMax(max.toDouble());
        }
    }
}

void PVTGForm::HandleLineLegendVisibleChanged()
{
    auto lineSeries = static_cast<QLineSeries *>(sender());
    auto lineLegend = chartView->chart()->legend()->markers(lineSeries)[0];
    auto scatterSeries = scatters[lines.indexOf(lineSeries)];
    auto scatterLegend = chartView->chart()->legend()->markers(scatterSeries)[0];

    HandleLegendVisible(lineLegend, scatterSeries, scatterLegend);
}

void PVTGForm::HandleScatterLegendVisibleChanged()
{
    auto scatterSeries = static_cast<QScatterSeries *>(sender());
    auto scatterLegend = chartView->chart()->legend()->markers(scatterSeries)[0];
    auto lineLegend = chartView->chart()->legend()->markers(lines[scatters.indexOf(scatterSeries)])[0];

    HandleLegendVisible(lineLegend, scatterSeries, scatterLegend);
}

void PVTGForm::HandleLegendVisible(QLegendMarker *lineLegend, QScatterSeries *scatterSeries, QLegendMarker *scatterLegend)
{
    scatterLegend->setVisible(!lineLegend->isVisible() && scatterSeries->isVisible());
}

}}}}
