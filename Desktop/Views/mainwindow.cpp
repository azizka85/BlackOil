#include "mainwindow.h"
#include "ui_mainwindow.h"

namespace BlackOil {
namespace Desktop {
namespace Views {

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    project = new ProjectModel(this);

    ui->setupUi(this);

    dockManager = new CDockManager(this);

    InitDockWidgets();

    loadTask = new LoadProjectTask(project, this);
    processTask = new ProcessProjectTask(project, this);
    drawTask = new DrawSceneTask(fieldForm, this);

    projectFileDialog = new QFileDialog(this, tr("Открыть в формате Eclipse"), QString(), tr("DATA files(*.DATA)"));

    projectLoadingDialog = new ProjectLoadingDialog(project, this);
    sceneDrawingDialog = new SceneDrawingDialog(project, this);

    InitDataBinding();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::ProjectLoadFinished()
{
    processTask->Process();
}

void MainWindow::ProjectProcessFinished()
{
    drawTask->Draw();
}

void MainWindow::HandleDrawingDataChanged()
{
    drawTask->Draw();

    sceneDrawingDialog->show();
}

void MainWindow::DrawSceneFinished()
{
    project->SetLoadingState(ProjectLoadingStateEnum::FinishLoading);
}

void MainWindow::ToggleWindowState(bool checked)
{
    if(checked)
        setWindowState(Qt::WindowFullScreen);
    else
        setWindowState(Qt::WindowMaximized);
}

void MainWindow::InitDockWidgets()
{
    fieldDock = new CDockWidget(tr("Поле"), this);
    fieldForm = new FieldForm(project, this);
    fieldDock->setWidget(fieldForm);
    fieldDock->setIcon(QIcon(":/Images/icon-slicers-32x32.png"));

    fieldSettingsDock = new CDockWidget(tr("Свойства поля"), this);    
    fieldSettingsForm = new FieldSettingsForm(this);
    fieldSettingsDock->setWidget(fieldSettingsForm);
    fieldSettingsDock->setIcon(QIcon(":/Images/icon-slicers-32x32.png"));

    legendSettingsDock = new CDockWidget(tr("Свойства легенды"), this);
    legendSettingsDock->setIcon(QIcon(":/Images/icon-legend-32x32.png"));

    paletteSettingsDock = new CDockWidget(tr("Настройки контура"), this);
    paletteSettingsForm = new PaletteSettingsForm(this);
    paletteSettingsDock->setWidget(paletteSettingsForm);
    paletteSettingsDock->setIcon(QIcon(":/Images/icon-mesh-32x32.png"));

    paletteValuesDock = new CDockWidget(tr("Палитра значений"), this);
    paletteValuesDock->setIcon(QIcon(":/Images/icon-mesh-32x32.png"));

    gridSettingsDock = new CDockWidget(tr("Видимость блоков"), this);
    gridSettingsForm = new GridSettingsForm(project, this);
    gridSettingsDock->setWidget(gridSettingsForm);
    gridSettingsDock->setIcon(QIcon(":/Images/icon-mesh-32x32.png"));

    wellSettingsDock = new CDockWidget(tr("Внешний вид скважин"), this);
    wellSettingsDock->setIcon(QIcon(":/Images/icon-well-32x32.png"));

    wellsScheduleDock = new CDockWidget(tr("Расписание скважин"), this);
    wellsScheduleForm = new WellsScheduleForm(project, this);
    wellsScheduleDock->setWidget(wellsScheduleForm);
    wellsScheduleDock->setIcon(QIcon(":/Images/icon-schedule-32x32.png"));

    swofDock = new CDockWidget(tr("ОФП и КД (нефть-вода)"), this);
    swofForm = new SWOFForm(project, this);
    swofDock->setWidget(swofForm);
    swofDock->setIcon(QIcon(":/Images/icon-linechart-32x32.png"));

    sgofDock = new CDockWidget(tr("ОФП и КД (газ-нефть)"), this);
    sgofForm = new SGOFForm(project, this);
    sgofDock->setWidget(sgofForm);
    sgofDock->setIcon(QIcon(":/Images/icon-linechart-32x32.png"));

    swofSettingsDock = new CDockWidget(tr("Настройки графики ОФП и КД (нефть-вода)"), this);
    swofFigureSettingsForm = new FigureSettingsForm(swofForm->Lines(), swofForm->Scatters(), this);
    swofSettingsDock->setWidget(swofFigureSettingsForm);
    swofSettingsDock->setIcon(QIcon(":/Images/icon-settings-32x32.png"));

    sgofSettingsDock = new CDockWidget(tr("Настройки графики ОФП и КД (газ-нефть)"), this);
    sgofFigureSettingsForm = new FigureSettingsForm(sgofForm->Lines(), sgofForm->Scatters(), this);
    sgofSettingsDock->setWidget(sgofFigureSettingsForm);
    sgofSettingsDock->setIcon(QIcon(":/Images/icon-settings-32x32.png"));

    pvtoDock = new CDockWidget(tr("PVT нефти"), this);
    pvtoForm = new PVTOForm(project, this);
    pvtoDock->setWidget(pvtoForm);
    pvtoDock->setIcon(QIcon(":/Images/icon-linechart-32x32.png"));

    pvtgDock = new CDockWidget(tr("PVT газа"), this);
    pvtgForm = new PVTGForm(project, this);
    pvtgDock->setWidget(pvtgForm);
    pvtgDock->setIcon(QIcon(":/Images/icon-linechart-32x32.png"));

    pvtoSettingsDock = new CDockWidget(tr("Настройки графики PVT нефти"), this);
    pvtoFigureSettingsForm = new FigureSettingsForm(pvtoForm->Lines(), pvtoForm->Scatters(), this);
    pvtoSettingsDock->setWidget(pvtoFigureSettingsForm);
    pvtoSettingsDock->setIcon(QIcon(":/Images/icon-settings-32x32.png"));

    pvtgSettingsDock = new CDockWidget(tr("Настройки графики PVT газа"), this);
    pvtgFigureSettingsForm = new FigureSettingsForm(pvtgForm->Lines(), pvtgForm->Scatters(), this);
    pvtgSettingsDock->setWidget(pvtgFigureSettingsForm);
    pvtgSettingsDock->setIcon(QIcon(":/Images/icon-settings-32x32.png"));

    consoleDock = new CDockWidget(tr("Консоль"), this);
    consoleDock->setIcon(QIcon(":/Images/icon-console-32x32.png"));

    auto fieldArea = dockManager->addDockWidget(CenterDockWidgetArea, fieldDock);
    auto fieldSettingsArea = dockManager->addDockWidget(RightDockWidgetArea, fieldSettingsDock);
    auto legendSettingsArea = dockManager->addDockWidget(BottomDockWidgetArea, legendSettingsDock, fieldSettingsArea);
    auto paletteSettingsArea = dockManager->addDockWidget(CenterDockWidgetArea, paletteSettingsDock, legendSettingsArea);
    auto paletteValuesArea = dockManager->addDockWidget(CenterDockWidgetArea, paletteValuesDock, legendSettingsArea);
    auto meshSettingsArea = dockManager->addDockWidget(CenterDockWidgetArea, gridSettingsDock, legendSettingsArea);
    auto wellSettingsArea = dockManager->addDockWidget(CenterDockWidgetArea, wellSettingsDock, legendSettingsArea);
    auto wellsScheduleArea = dockManager->addDockWidget(CenterDockWidgetArea, wellsScheduleDock, fieldArea);
    auto swofArea = dockManager->addDockWidget(CenterDockWidgetArea, swofDock, fieldArea);
    auto sgofArea = dockManager->addDockWidget(CenterDockWidgetArea, sgofDock, fieldArea);
    auto swofSettingsArea = dockManager->addDockWidget(BottomDockWidgetArea, swofSettingsDock, fieldArea);
    auto sgofSettingsArea = dockManager->addDockWidget(CenterDockWidgetArea, sgofSettingsDock, swofSettingsArea);
    auto pvtoArea = dockManager->addDockWidget(CenterDockWidgetArea, pvtoDock, fieldArea);
    auto pvtgArea = dockManager->addDockWidget(CenterDockWidgetArea, pvtgDock, fieldArea);
    auto pvtoSettingsArea = dockManager->addDockWidget(CenterDockWidgetArea, pvtoSettingsDock, swofSettingsArea);
    auto pvtgSettingsArea = dockManager->addDockWidget(CenterDockWidgetArea, pvtgSettingsDock, swofSettingsArea);
    auto consoleArea = dockManager->addDockWidget(CenterDockWidgetArea, consoleDock, fieldArea);

    fieldArea->setMinimumWidth(350);
    fieldArea->setMinimumHeight(350);

    fieldSettingsArea->setMinimumWidth(350);
    fieldSettingsArea->setMinimumHeight(350);

    legendSettingsArea->setMinimumWidth(350);
    legendSettingsArea->setMinimumHeight(350);

    paletteSettingsArea->setMinimumWidth(350);
    paletteSettingsArea->setMinimumHeight(350);

    paletteValuesArea->setMinimumWidth(350);
    paletteValuesArea->setMinimumHeight(350);

    meshSettingsArea->setMinimumWidth(350);
    meshSettingsArea->setMinimumHeight(350);

    wellSettingsArea->setMinimumWidth(350);
    wellSettingsArea->setMinimumHeight(350);

    wellsScheduleArea->setMinimumWidth(350);
    wellsScheduleArea->setMinimumHeight(350);

    swofArea->setMinimumWidth(350);
    swofArea->setMinimumHeight(350);

    sgofArea->setMinimumWidth(350);
    sgofArea->setMinimumHeight(350);

    swofSettingsArea->setMinimumWidth(200);
    swofSettingsArea->setMinimumHeight(200);

    sgofSettingsArea->setMinimumWidth(200);
    sgofSettingsArea->setMinimumHeight(200);

    pvtoArea->setMinimumWidth(350);
    pvtoArea->setMinimumHeight(350);

    pvtgArea->setMinimumWidth(350);
    pvtgArea->setMinimumHeight(350);

    pvtoSettingsArea->setMinimumWidth(200);
    pvtoSettingsArea->setMinimumHeight(200);

    pvtgSettingsArea->setMinimumWidth(200);
    pvtgSettingsArea->setMinimumHeight(200);

    consoleArea->setMinimumWidth(350);
    consoleArea->setMinimumHeight(350);
}

void MainWindow::InitDataBinding()
{
    connect(loadTask, SIGNAL(Finished()), this, SLOT(ProjectLoadFinished()));
    connect(processTask, SIGNAL(Finished()), this, SLOT(ProjectProcessFinished()));
    connect(drawTask, SIGNAL(Finished()), this, SLOT(DrawSceneFinished()));

    connect(ui->LoadDataAction, SIGNAL(toggled(bool)), ui->DataToolBar, SLOT(setVisible(bool)));
    connect(ui->FieldActionsListAction, SIGNAL(toggled(bool)), ui->FieldToolBar, SLOT(setVisible(bool)));
    connect(ui->WellsActionsListAction, SIGNAL(toggled(bool)), ui->WellsToolBar, SLOT(setVisible(bool)));
    connect(ui->FPAction, SIGNAL(toggled(bool)), ui->FPToolBar, SLOT(setVisible(bool)));

    connect(ui->FieldAction, SIGNAL(toggled(bool)), fieldDock, SLOT(toggleView(bool)));
    connect(fieldDock, SIGNAL(viewToggled(bool)), ui->FieldAction, SLOT(setChecked(bool)));
    connect(ui->FieldSettingsAction, SIGNAL(toggled(bool)), fieldSettingsDock, SLOT(toggleView(bool)));
    connect(fieldSettingsDock, SIGNAL(viewToggled(bool)), ui->FieldSettingsAction, SLOT(setChecked(bool)));
    connect(ui->LegendSettingsAction, SIGNAL(toggled(bool)), legendSettingsDock, SLOT(toggleView(bool)));
    connect(legendSettingsDock, SIGNAL(viewToggled(bool)), ui->LegendSettingsAction, SLOT(setChecked(bool)));
    connect(ui->WellsScheduleAction, SIGNAL(toggled(bool)), wellsScheduleDock, SLOT(toggleView(bool)));
    connect(wellsScheduleDock, SIGNAL(viewToggled(bool)), ui->WellsScheduleAction, SLOT(setChecked(bool)));
    connect(ui->SWOFAction, SIGNAL(toggled(bool)), swofDock, SLOT(toggleView(bool)));
    connect(swofDock, SIGNAL(viewToggled(bool)), ui->SWOFAction, SLOT(setChecked(bool)));
    connect(ui->SGOFAction, SIGNAL(toggled(bool)), sgofDock, SLOT(toggleView(bool)));
    connect(sgofDock, SIGNAL(viewToggled(bool)), ui->SGOFAction, SLOT(setChecked(bool)));
    connect(ui->PVTOAction, SIGNAL(toggled(bool)), pvtoDock, SLOT(toggleView(bool)));
    connect(pvtoDock, SIGNAL(viewToggled(bool)), ui->PVTOAction, SLOT(setChecked(bool)));
    connect(ui->PVTGAction, SIGNAL(toggled(bool)), pvtgDock, SLOT(toggleView(bool)));
    connect(pvtgDock, SIGNAL(viewToggled(bool)), ui->PVTGAction, SLOT(setChecked(bool)));
    connect(ui->ConsoleAction, SIGNAL(toggled(bool)), consoleDock, SLOT(toggleView(bool)));
    connect(consoleDock, SIGNAL(viewToggled(bool)), ui->ConsoleAction, SLOT(setChecked(bool)));

    connect(ui->DisplayPaletteAction, SIGNAL(toggled(bool)), fieldSettingsForm->DisplayPaletteCheckBox(), SLOT(setChecked(bool)));
    connect(fieldSettingsForm->DisplayPaletteCheckBox(), SIGNAL(toggled(bool)), ui->DisplayPaletteAction, SLOT(setChecked(bool)));
    connect(fieldForm, SIGNAL(DisplayPaletteChanged(bool)), fieldSettingsForm->DisplayPaletteCheckBox(), SLOT(setChecked(bool)));
    connect(fieldSettingsForm->DisplayPaletteCheckBox(), SIGNAL(toggled(bool)), fieldForm, SLOT(SetDisplayPalette(bool)));
    connect(ui->DisplayMeshAction, SIGNAL(toggled(bool)), fieldSettingsForm->DisplayMeshCheckBox(), SLOT(setChecked(bool)));
    connect(fieldSettingsForm->DisplayMeshCheckBox(), SIGNAL(toggled(bool)), ui->DisplayMeshAction, SLOT(setChecked(bool)));
    connect(fieldForm, SIGNAL(DisplayMeshChanged(bool)), fieldSettingsForm->DisplayMeshCheckBox(), SLOT(setChecked(bool)));
    connect(fieldSettingsForm->DisplayMeshCheckBox(), SIGNAL(toggled(bool)), fieldForm, SLOT(SetDisplayMesh(bool)));
    connect(fieldForm, SIGNAL(MeshWidthChanged(int)), fieldSettingsForm->MeshWidthSlider(), SLOT(setValue(int)));
    connect(fieldSettingsForm->MeshWidthSlider(), SIGNAL(valueChanged(int)), fieldForm, SLOT(SetMeshWidth(int)));
    connect(ui->DisplayBlockAction, SIGNAL(toggled(bool)), fieldSettingsForm->DisplayBoxCheckBox(), SLOT(setChecked(bool)));
    connect(fieldSettingsForm->DisplayBoxCheckBox(), SIGNAL(toggled(bool)), ui->DisplayBlockAction, SLOT(setChecked(bool)));
    connect(ui->DisplayWellsAction, SIGNAL(toggled(bool)), fieldSettingsForm->DisplayWellsCheckBox(), SLOT(setChecked(bool)));
    connect(fieldSettingsForm->DisplayWellsCheckBox(), SIGNAL(toggled(bool)), ui->DisplayWellsAction, SLOT(setChecked(bool)));
    connect(ui->DisplayAxesAction, SIGNAL(toggled(bool)), fieldSettingsForm->DisplayAxesCheckBox(), SLOT(setChecked(bool)));
    connect(fieldSettingsForm->DisplayAxesCheckBox(), SIGNAL(toggled(bool)), ui->DisplayAxesAction, SLOT(setChecked(bool)));
    connect(ui->DisplayLegendAction, SIGNAL(toggled(bool)), fieldSettingsForm->DisplayLegendCheckBox(), SLOT(setChecked(bool)));
    connect(fieldSettingsForm->DisplayLegendCheckBox(), SIGNAL(toggled(bool)), ui->DisplayLegendAction, SLOT(setChecked(bool)));
    connect(fieldForm, SIGNAL(DisplayLegendChanged(bool)), fieldSettingsForm->DisplayLegendCheckBox(), SLOT(setChecked(bool)));
    connect(fieldSettingsForm->DisplayLegendCheckBox(), SIGNAL(toggled(bool)), fieldForm, SLOT(SetDisplayLegend(bool)));
    connect(ui->LegendSettingsAction, SIGNAL(toggled(bool)), fieldSettingsForm->LegendSettingsButton(), SLOT(setChecked(bool)));
    connect(fieldSettingsForm->LegendSettingsButton(), SIGNAL(toggled(bool)), ui->LegendSettingsAction, SLOT(setChecked(bool)));    

    connect(paletteSettingsDock, SIGNAL(viewToggled(bool)), fieldSettingsForm->PaletteSettingsButton(), SLOT(setChecked(bool)));
    connect(fieldSettingsForm->PaletteSettingsButton(), SIGNAL(toggled(bool)), paletteSettingsDock, SLOT(toggleView(bool)));
    connect(paletteValuesDock, SIGNAL(viewToggled(bool)), fieldSettingsForm->PaletteValuesButton(), SLOT(setChecked(bool)));
    connect(fieldSettingsForm->PaletteValuesButton(), SIGNAL(toggled(bool)), paletteValuesDock, SLOT(toggleView(bool)));
    connect(gridSettingsDock, SIGNAL(viewToggled(bool)), fieldSettingsForm->GridSettingsButton(), SLOT(setChecked(bool)));
    connect(fieldSettingsForm->GridSettingsButton(), SIGNAL(toggled(bool)), gridSettingsDock, SLOT(toggleView(bool)));
    connect(wellSettingsDock, SIGNAL(viewToggled(bool)), fieldSettingsForm->WellSettingsButton(), SLOT(setChecked(bool)));
    connect(fieldSettingsForm->WellSettingsButton(), SIGNAL(toggled(bool)), wellSettingsDock, SLOT(toggleView(bool)));
    connect(fieldForm, SIGNAL(DisplayBoxChanged(bool)), fieldSettingsForm->DisplayBoxCheckBox(), SLOT(setChecked(bool)));
    connect(fieldSettingsForm->DisplayBoxCheckBox(), SIGNAL(toggled(bool)), fieldForm, SLOT(SetDisplayBox(bool)));
    connect(fieldForm, SIGNAL(DisplayAxesChanged(bool)), fieldSettingsForm->DisplayAxesCheckBox(), SLOT(setChecked(bool)));
    connect(fieldSettingsForm->DisplayAxesCheckBox(), SIGNAL(toggled(bool)), fieldForm, SLOT(SetDisplayAxes(bool)));
    connect(fieldForm, SIGNAL(AxesLengthChanged(double)), fieldSettingsForm->AxesLengthSpinBox(), SLOT(setValue(double)));
    connect(fieldSettingsForm->AxesLengthSpinBox(), SIGNAL(valueChanged(double)), fieldForm, SLOT(SetAxesLength(double)));
    connect(fieldForm, SIGNAL(AxisOfRotationChanged(int)), fieldSettingsForm->RotationComboBox(), SLOT(setCurrentIndex(int)));
    connect(fieldSettingsForm->RotationComboBox(), SIGNAL(currentIndexChanged(int)), fieldForm, SLOT(SetAxisOfRotation(int)));
    connect(fieldForm, SIGNAL(ScaleXChanged(double)), fieldSettingsForm->ScaleXSpinBox(), SLOT(setValue(double)));
    connect(fieldSettingsForm->ScaleXSpinBox(), SIGNAL(valueChanged(double)), fieldForm, SLOT(SetScaleX(double)));
    connect(fieldForm, SIGNAL(ScaleYChanged(double)), fieldSettingsForm->ScaleYSpinBox(), SLOT(setValue(double)));
    connect(fieldSettingsForm->ScaleYSpinBox(), SIGNAL(valueChanged(double)), fieldForm, SLOT(SetScaleY(double)));
    connect(fieldForm, SIGNAL(ScaleZChanged(double)), fieldSettingsForm->ScaleZSpinBox(), SLOT(setValue(double)));
    connect(fieldSettingsForm->ScaleZSpinBox(), SIGNAL(valueChanged(double)), fieldForm, SLOT(SetScaleZ(double)));
    connect(fieldSettingsForm->XYViewAxisButton(), SIGNAL(clicked(bool)), fieldForm, SLOT(SetXYViewAxis()));
    connect(fieldSettingsForm->XZViewAxisButton(), SIGNAL(clicked(bool)), fieldForm, SLOT(SetXZViewAxis()));
    connect(fieldSettingsForm->YZViewAxisButton(), SIGNAL(clicked(bool)), fieldForm, SLOT(SetYZViewAxis()));

    connect(paletteSettingsForm, SIGNAL(SelectableChanged(bool)), fieldForm, SLOT(SetFieldSelectable(bool)));
    connect(fieldForm, SIGNAL(FieldSelectableChanged(bool)), paletteSettingsForm, SLOT(SetSelectable(bool)));
    connect(paletteSettingsForm, SIGNAL(LightEnabledChanged(bool)), fieldForm, SLOT(SetLightEnabled(bool)));
    connect(fieldForm, SIGNAL(LightEnabledChanged(bool)), paletteSettingsForm, SLOT(SetLightEnabled(bool)));
    connect(paletteSettingsForm, SIGNAL(TransparencyChanged(float)), fieldForm, SLOT(SetPaletteTransparency(float)));
    connect(fieldForm, SIGNAL(PaletteTransparencyChanged(float)), paletteSettingsForm, SLOT(SetTransparency(float)));

    connect(gridSettingsForm, SIGNAL(DataChanged()), this, SLOT(HandleDrawingDataChanged()));

    connect(swofSettingsDock, SIGNAL(viewToggled(bool)), swofForm->DisplayFigureSettingsAction(), SLOT(setChecked(bool)));
    connect(swofForm->DisplayFigureSettingsAction(), SIGNAL(toggled(bool)), swofSettingsDock, SLOT(toggleView(bool)));
    connect(sgofSettingsDock, SIGNAL(viewToggled(bool)), sgofForm->DisplayFigureSettingsAction(), SLOT(setChecked(bool)));
    connect(sgofForm->DisplayFigureSettingsAction(), SIGNAL(toggled(bool)), sgofSettingsDock, SLOT(toggleView(bool)));

    connect(pvtoSettingsDock, SIGNAL(viewToggled(bool)), pvtoForm->DisplayFigureSettingsAction(), SLOT(setChecked(bool)));
    connect(pvtoForm->DisplayFigureSettingsAction(), SIGNAL(toggled(bool)), pvtoSettingsDock, SLOT(toggleView(bool)));
    connect(pvtgSettingsDock, SIGNAL(viewToggled(bool)), pvtgForm->DisplayFigureSettingsAction(), SLOT(setChecked(bool)));
    connect(pvtgForm->DisplayFigureSettingsAction(), SIGNAL(toggled(bool)), pvtgSettingsDock, SLOT(toggleView(bool)));

    connect(ui->LoadEclipseDataAction, SIGNAL(triggered(bool)), this, SLOT(OpenProjectFileDialog()));
    connect(projectFileDialog, SIGNAL(fileSelected(QString)), this, SLOT(LoadEclipseData(QString)));
    connect(ui->WindowFullSizeAction, SIGNAL(toggled(bool)), this, SLOT(ToggleWindowState(bool)));
    connect(project, SIGNAL(LoadingStateChanged(int)), this, SLOT(ProjectLoadingStateChanged(int)));
    connect(ui->UnsetAction, SIGNAL(triggered(bool)), this, SLOT(UnsetData()));

    ui->DataToolBar->setVisible(ui->LoadDataAction->isChecked());
    ui->FieldToolBar->setVisible(ui->FieldActionsListAction->isChecked());
    ui->WellsToolBar->setVisible(ui->WellsActionsListAction->isChecked());
    ui->FPToolBar->setVisible(ui->FPAction->isChecked());

    fieldDock->toggleView(ui->FieldAction->isChecked());
    fieldSettingsDock->toggleView(ui->FieldSettingsAction->isChecked());
    wellsScheduleDock->toggleView(ui->WellsScheduleAction->isChecked());
    consoleDock->toggleView(ui->ConsoleAction->isChecked());
    legendSettingsDock->toggleView(ui->LegendSettingsAction->isChecked());
    paletteSettingsDock->toggleView(fieldSettingsForm->PaletteSettingsButton()->isChecked());
    paletteValuesDock->toggleView(fieldSettingsForm->PaletteValuesButton()->isChecked());
    gridSettingsDock->toggleView(fieldSettingsForm->GridSettingsButton()->isChecked());
    wellSettingsDock->toggleView(fieldSettingsForm->WellSettingsButton()->isChecked());
    swofDock->toggleView(ui->SWOFAction->isChecked());
    sgofDock->toggleView(ui->SGOFAction->isChecked());
    pvtoDock->toggleView(ui->PVTOAction->isChecked());
    pvtgDock->toggleView(ui->PVTGAction->isChecked());

    fieldSettingsForm->DisplayPaletteCheckBox()->setChecked(ui->DisplayPaletteAction->isChecked());
    fieldSettingsForm->DisplayMeshCheckBox()->setChecked(ui->DisplayMeshAction->isChecked());
    fieldSettingsForm->MeshWidthSlider()->setValue(fieldForm->MeshWidth());
    fieldSettingsForm->DisplayBoxCheckBox()->setChecked(ui->DisplayBlockAction->isChecked());
    fieldSettingsForm->DisplayWellsCheckBox()->setChecked(ui->DisplayWellsAction->isChecked());
    fieldSettingsForm->DisplayAxesCheckBox()->setChecked(ui->DisplayAxesAction->isChecked());
    fieldSettingsForm->AxesLengthSpinBox()->setValue(fieldForm->AxesLength());
    fieldSettingsForm->DisplayLegendCheckBox()->setChecked(ui->DisplayLegendAction->isChecked());
    fieldSettingsForm->LegendSettingsButton()->setChecked(ui->LegendSettingsAction->isChecked());
    fieldSettingsForm->RotationComboBox()->setCurrentIndex(fieldForm->AxisOfRotation());
    fieldSettingsForm->ScaleXSpinBox()->setValue(fieldForm->ScaleX());
    fieldSettingsForm->ScaleYSpinBox()->setValue(fieldForm->ScaleY());
    fieldSettingsForm->ScaleZSpinBox()->setValue(fieldForm->ScaleZ());

    paletteSettingsForm->SetSelectable(fieldForm->FieldSelectable());
    paletteSettingsForm->SetLightEnabled(fieldForm->LightEnabled());
    paletteSettingsForm->SetTransparency(fieldForm->PaletteTransparency());

    fieldForm->SetDisplayPalette(fieldSettingsForm->DisplayPaletteCheckBox()->isChecked());
    fieldForm->SetDisplayMesh(fieldSettingsForm->DisplayMeshCheckBox()->isChecked());
    fieldForm->SetDisplayLegend(fieldSettingsForm->DisplayLegendCheckBox()->isChecked());
    fieldForm->SetDisplayBox(fieldSettingsForm->DisplayBoxCheckBox()->isChecked());
    fieldForm->SetDisplayAxes(fieldSettingsForm->DisplayAxesCheckBox()->isChecked());

    swofSettingsDock->toggleView(swofForm->DisplayFigureSettingsAction()->isChecked());
    sgofSettingsDock->toggleView(sgofForm->DisplayFigureSettingsAction()->isChecked());

    pvtoSettingsDock->toggleView(pvtoForm->DisplayFigureSettingsAction()->isChecked());
    pvtgSettingsDock->toggleView(pvtgForm->DisplayFigureSettingsAction()->isChecked());

    ToggleWindowState(ui->WindowFullSizeAction->isChecked());   
}

void MainWindow::OpenProjectFileDialog()
{
    projectFileDialog->open();
}

void MainWindow::LoadEclipseData(const QString &filePath)
{
    projectFileDialog->setDirectory(filePath);

    loadTask->Load(filePath);

    projectLoadingDialog->show();
}

void MainWindow::ProjectLoadingStateChanged(int state)
{
    if(state == ProjectLoadingStateEnum::FinishLoading || state == ProjectLoadingStateEnum::FinishInitializing)
    {
        setEnabled(true);
        setWindowTitle(!project->Title().isEmpty() ? project->Title() : tr("BlackOil"));
    }
    else
    {
        setEnabled(false);
    }
}

void MainWindow::UnsetData()
{
    project->InitVariables();

    fieldForm->ClearScene();
}

}}}
