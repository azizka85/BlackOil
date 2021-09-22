#include "gridsettingsform.h"
#include "ui_gridsettingsform.h"

namespace BlackOil {
namespace Desktop {
namespace Views {
namespace Settings {

GridSettingsForm::GridSettingsForm(ProjectModel *project, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GridSettingsForm)
{
    this->project = project;

    ui->setupUi(this);        

    ui->XListView->setModel(project->Grid()->XLayer());
    ui->YListView->setModel(project->Grid()->YLayer());
    ui->ZListView->setModel(project->Grid()->ZLayer());

    connect(ui->XClearButton, SIGNAL(clicked(bool)), project->Grid()->XLayer(), SLOT(Clear()));
    connect(ui->XCheckAllButton, SIGNAL(clicked(bool)), project->Grid()->XLayer(), SLOT(CheckAll()));
    connect(ui->YClearButton, SIGNAL(clicked(bool)), project->Grid()->YLayer(), SLOT(Clear()));
    connect(ui->YCheckAllButton, SIGNAL(clicked(bool)), project->Grid()->YLayer(), SLOT(CheckAll()));
    connect(ui->ZClearButton, SIGNAL(clicked(bool)), project->Grid()->ZLayer(), SLOT(Clear()));
    connect(ui->ZCheckAllButton, SIGNAL(clicked(bool)), project->Grid()->ZLayer(), SLOT(CheckAll()));

    connect(project->Grid()->XLayer(), SIGNAL(dataChanged(QModelIndex, QModelIndex)), this, SLOT(HandleDataChanged()));
    connect(project->Grid()->YLayer(), SIGNAL(dataChanged(QModelIndex, QModelIndex)), this, SLOT(HandleDataChanged()));
    connect(project->Grid()->ZLayer(), SIGNAL(dataChanged(QModelIndex, QModelIndex)), this, SLOT(HandleDataChanged()));
}

GridSettingsForm::~GridSettingsForm()
{
    delete ui;
}

void GridSettingsForm::HandleDataChanged()
{
    emit DataChanged();
}

}}}}
