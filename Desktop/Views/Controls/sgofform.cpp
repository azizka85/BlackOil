#include "sgofform.h"
#include "ui_sgofform.h"

namespace BlackOil {
namespace Desktop {
namespace Views {
namespace Controls {

SGOFForm::SGOFForm(ProjectModel *project, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SGOFForm)
{
    this->project = project;

    ui->setupUi(this);

    auto model = new QSortFilterProxyModel(this);
    model->setSourceModel(project->SF()->SGOF());
    ui->Table->setModel(model);

    auto toolBar = new QToolBar(this);
    auto regionLabel = new QLabel(tr("Регион: "), this);
    auto regionCombobox = new QComboBox(this);
    auto rpmLabel = new QLabel(tr("МОП: "), this);
    auto rpmCombobox = new QComboBox(this);

    lines.resize(staticMetaObject.enumerator(staticMetaObject.indexOfEnumerator("Series")).keyCount());
    scatters.resize(staticMetaObject.enumerator(staticMetaObject.indexOfEnumerator("Series")).keyCount());

    lines[SeriesKrG] = new QLineSeries(this);
    lines[SeriesKrO] = new QLineSeries(this);
    lines[SeriesPcOG] = new QLineSeries(this);

    scatters[SeriesKrG] = new QScatterSeries(this);
    scatters[SeriesKrO] = new QScatterSeries(this);
    scatters[SeriesPcOG] = new QScatterSeries(this);

    chartView = new QChartView(new QChart(), this);

    chartView->chart()->addSeries(lines[SeriesKrG]);
    chartView->chart()->addSeries(lines[SeriesKrO]);
    chartView->chart()->addSeries(lines[SeriesPcOG]);

    chartView->chart()->addSeries(scatters[SeriesKrG]);
    chartView->chart()->legend()->markers(scatters[SeriesKrG])[0]->setVisible(false);
    chartView->chart()->addSeries(scatters[SeriesKrO]);
    chartView->chart()->legend()->markers(scatters[SeriesKrO])[0]->setVisible(false);
    chartView->chart()->addSeries(scatters[SeriesPcOG]);
    chartView->chart()->legend()->markers(scatters[SeriesPcOG])[0]->setVisible(false);

    auto axisS = new QValueAxis(this);
    auto axisKr = new QValueAxis(this);
    axisPc = new QValueAxis(this);

    axisS->setTitleText(tr("Насыщенность газа, д. ед."));
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

    lines[SeriesKrG]->setName(tr("KrG"));
    lines[SeriesKrG]->attachAxis(axisS);
    lines[SeriesKrG]->attachAxis(axisKr);

    scatters[SeriesKrG]->setName(tr("KrG"));
    scatters[SeriesKrG]->setMarkerSize(5);
    scatters[SeriesKrG]->setMarkerShape(QScatterSeries::MarkerShapeRectangle);
    scatters[SeriesKrG]->setColor(lines[SeriesKrG]->color());
    scatters[SeriesKrG]->setBorderColor(lines[SeriesKrG]->color());
    scatters[SeriesKrG]->attachAxis(axisS);
    scatters[SeriesKrG]->attachAxis(axisKr);

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

    lines[SeriesPcOG]->setName(tr("Pc"));
    lines[SeriesPcOG]->attachAxis(axisS);
    lines[SeriesPcOG]->attachAxis(axisPc);

    scatters[SeriesPcOG]->setName("Pc");
    scatters[SeriesPcOG]->setMarkerSize(5);
    scatters[SeriesPcOG]->setMarkerShape(QScatterSeries::MarkerShapeRectangle);
    scatters[SeriesPcOG]->setColor(lines[SeriesPcOG]->color());
    scatters[SeriesPcOG]->setBorderColor(lines[SeriesPcOG]->color());
    scatters[SeriesPcOG]->attachAxis(axisS);
    scatters[SeriesPcOG]->attachAxis(axisPc);

    auto krgMapper = new QVXYModelMapper(this);
    auto krgScatterMapper = new QVXYModelMapper(this);
    auto kroMapper = new QVXYModelMapper(this);
    auto kroScatterMapper = new QVXYModelMapper(this);
    auto pcMapper = new QVXYModelMapper(this);
    auto pcScatterMapper = new QVXYModelMapper(this);

    krgMapper->setXColumn(SGOFModel::SGOFSg);
    krgMapper->setYColumn(SGOFModel::SGOFKrG);
    krgMapper->setSeries(lines[SeriesKrG]);
    krgMapper->setModel(project->SF()->SGOF());

    krgScatterMapper->setXColumn(SGOFModel::SGOFSg);
    krgScatterMapper->setYColumn(SGOFModel::SGOFKrG);
    krgScatterMapper->setSeries(scatters[SeriesKrG]);
    krgScatterMapper->setModel(project->SF()->SGOF());

    kroMapper->setXColumn(SGOFModel::SGOFSg);
    kroMapper->setYColumn(SGOFModel::SGOFKrO);
    kroMapper->setSeries(lines[SeriesKrO]);
    kroMapper->setModel(project->SF()->SGOF());

    kroScatterMapper->setXColumn(SGOFModel::SGOFSg);
    kroScatterMapper->setYColumn(SGOFModel::SGOFKrO);
    kroScatterMapper->setSeries(scatters[SeriesKrO]);
    kroScatterMapper->setModel(project->SF()->SGOF());

    pcMapper->setXColumn(SGOFModel::SGOFSg);
    pcMapper->setYColumn(SGOFModel::SGOFPcOG);
    pcMapper->setSeries(lines[SeriesPcOG]);
    pcMapper->setModel(project->SF()->SGOF());

    pcScatterMapper->setXColumn(SGOFModel::SGOFSg);
    pcScatterMapper->setYColumn(SGOFModel::SGOFPcOG);
    pcScatterMapper->setSeries(scatters[SeriesPcOG]);
    pcScatterMapper->setModel(project->SF()->SGOF());

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

    connect(regionCombobox, SIGNAL(currentIndexChanged(int)), project->SF()->SGOF(), SLOT(SetRegion(int)));
    connect(project->SF()->SGOF(), SIGNAL(RegionChanged(int)), regionCombobox, SLOT(setCurrentIndex(int)));

    connect(project->SF()->SGOF(), SIGNAL(MinMaxChanged(int, QVariant, QVariant)), this, SLOT(HandleMinMax(int, QVariant, QVariant)));

    connect(lines[SeriesKrG], SIGNAL(visibleChanged()), this, SLOT(HandleLineLegendVisibleChanged()));
    connect(lines[SeriesKrO], SIGNAL(visibleChanged()), this, SLOT(HandleLineLegendVisibleChanged()));
    connect(lines[SeriesPcOG], SIGNAL(visibleChanged()), this, SLOT(HandleLineLegendVisibleChanged()));

    connect(scatters[SeriesKrG], SIGNAL(visibleChanged()), this, SLOT(HandleScatterLegendVisibleChanged()));
    connect(scatters[SeriesKrO], SIGNAL(visibleChanged()), this, SLOT(HandleScatterLegendVisibleChanged()));
    connect(scatters[SeriesPcOG], SIGNAL(visibleChanged()), this, SLOT(HandleScatterLegendVisibleChanged()));

    ui->Table->setVisible(ui->DisplayTableAction->isChecked());
    HandleDisplayAction();
    HandleSplitAction();

    ui->Splitter->insertWidget(0, chartView);
}

SGOFForm::~SGOFForm()
{
    delete ui;
}

QVector<QLineSeries *> *SGOFForm::Lines()
{
    return &lines;
}

QVector<QScatterSeries *> *SGOFForm::Scatters()
{
    return &scatters;
}

QAction *SGOFForm::DisplayFigureSettingsAction()
{
    return ui->DisplayFigureSettingsAction;
}

void SGOFForm::HandleDisplayAction()
{
    if(ui->DisplayTableAction->isChecked() || ui->DisplayFigureAction->isChecked())
        ui->SplitAction->setVisible(true);
    else
        ui->SplitAction->setVisible(false);
}

void SGOFForm::HandleSplitAction()
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

void SGOFForm::HandleDeleteRow()
{
    for(auto index: ui->Table->selectionModel()->selectedIndexes()) ui->Table->model()->removeRow(index.row(), index.parent());
}

void SGOFForm::HandleInsertRow()
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

void SGOFForm::HandleMinMax(int column, QVariant min, QVariant max)
{
    if(column == SGOFModel::SGOFPcOG)
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

void SGOFForm::HandleLineLegendVisibleChanged()
{
    auto lineSeries = static_cast<QLineSeries *>(sender());
    auto lineLegend = chartView->chart()->legend()->markers(lineSeries)[0];
    auto scatterSeries = scatters[lines.indexOf(lineSeries)];
    auto scatterLegend = chartView->chart()->legend()->markers(scatterSeries)[0];

    HandleLegendVisible(lineLegend, scatterSeries, scatterLegend);
}

void SGOFForm::HandleScatterLegendVisibleChanged()
{
    auto scatterSeries = static_cast<QScatterSeries *>(sender());
    auto scatterLegend = chartView->chart()->legend()->markers(scatterSeries)[0];
    auto lineLegend = chartView->chart()->legend()->markers(lines[scatters.indexOf(scatterSeries)])[0];

    HandleLegendVisible(lineLegend, scatterSeries, scatterLegend);
}

void SGOFForm::HandleLegendVisible(QLegendMarker *lineLegend, QScatterSeries *scatterSeries, QLegendMarker *scatterLegend)
{
    scatterLegend->setVisible(!lineLegend->isVisible() && scatterSeries->isVisible());
}

}}}}
