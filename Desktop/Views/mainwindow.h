#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <qmainwindow.h>
#include <qfiledialog.h>

#include <DockManager.h>
#include <DockAreaWidget.h>

#include <projectloadingstateenum.h>

#include <projectmodel.h>

#include <loadprojecttask.h>
#include <processprojecttask.h>
#include <drawscenetask.h>

#include <projectloadingdialog.h>
#include <scenedrawingdialog.h>

#include <fieldform.h>

#include <fieldsettingsform.h>
#include <figuresettingsform.h>
#include <palettesettingsform.h>
#include <gridsettingsform.h>

#include <wellsscheduleform.h>

#include <swofform.h>
#include <sgofform.h>

#include <pvtoform.h>
#include <pvtgform.h>

#include <desktop_global.h>

using namespace ads;

using namespace BlackOil::Model;
using namespace BlackOil::Model::Tasks;

using namespace BlackOil::Desktop::Tasks;
using namespace BlackOil::Desktop::Views::Dialogs;
using namespace BlackOil::Desktop::Views::Settings;
using namespace BlackOil::Desktop::Views::Controls;

namespace Ui {
class MainWindow;
}

namespace BlackOil {
namespace Desktop {
namespace Views {

class DESKTOP_EXPORT MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void ProjectLoadFinished();
    void ProjectProcessFinished();
    void HandleDrawingDataChanged();
    void DrawSceneFinished();
    void ToggleWindowState(bool checked);
    void OpenProjectFileDialog();
    void LoadEclipseData(const QString &filePath);    
    void UnsetData();

protected slots:
    void InitDockWidgets();
    void InitDataBinding();
    void ProjectLoadingStateChanged(int state);    

protected:
    Ui::MainWindow *ui;

    CDockManager *dockManager;

    CDockWidget *fieldDock, *fieldSettingsDock;
    CDockWidget *legendSettingsDock, *paletteSettingsDock, *paletteValuesDock, *gridSettingsDock, *wellSettingsDock;
    CDockWidget *wellsScheduleDock;
    CDockWidget *swofDock, *sgofDock;
    CDockWidget *swofSettingsDock, *sgofSettingsDock;
    CDockWidget *pvtoDock, *pvtgDock;
    CDockWidget *pvtoSettingsDock, *pvtgSettingsDock;
    CDockWidget *consoleDock;

    FieldForm *fieldForm;

    FieldSettingsForm *fieldSettingsForm;
    PaletteSettingsForm *paletteSettingsForm;
    GridSettingsForm *gridSettingsForm;

    FigureSettingsForm *swofFigureSettingsForm, *sgofFigureSettingsForm;
    FigureSettingsForm *pvtoFigureSettingsForm, *pvtgFigureSettingsForm;

    WellsScheduleForm *wellsScheduleForm;

    SWOFForm *swofForm;
    SGOFForm *sgofForm;

    PVTOForm *pvtoForm;
    PVTGForm *pvtgForm;

    ProjectLoadingDialog *projectLoadingDialog;
    SceneDrawingDialog *sceneDrawingDialog;
    QFileDialog *projectFileDialog;

    ProjectModel *project;

    LoadProjectTask *loadTask;
    ProcessProjectTask *processTask;
    DrawSceneTask *drawTask;
};

}}}

#endif // MAINWINDOW_H
