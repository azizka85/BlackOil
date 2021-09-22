#include "wellsscheduleform.h"
#include "ui_wellsscheduleform.h"

namespace BlackOil {
namespace Desktop {
namespace Views {
namespace Controls {

WellsScheduleForm::WellsScheduleForm(ProjectModel *project, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WellsScheduleForm)
{
    this->project = project;

    ui->setupUi(this);

    auto model = new QSortFilterProxyModel(this);
    model->setSourceModel(project->Wells()->WELSPECS());
    ui->WELSPECSTable->setModel(model);

    auto delWELSPECSShortcut = new QShortcut(QKeySequence(Qt::Key_Delete), ui->WELSPECSTable);
    auto insWELSPECSShortcut = new QShortcut(QKeySequence(Qt::Key_Insert), ui->WELSPECSTable);
    auto subWELSPECSShortcut = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_Insert), ui->WELSPECSTable);    

    connect(delWELSPECSShortcut, SIGNAL(activated()), this, SLOT(HandleDeleteWELSPECSRow()));
    connect(insWELSPECSShortcut, SIGNAL(activated()), this, SLOT(HandleInsertWELSPECSGroup()));
    connect(subWELSPECSShortcut, SIGNAL(activated()), this, SLOT(HandleInsertWELSPECSRow()));

    model = new QSortFilterProxyModel(this);
    model->setSourceModel(project->Wells()->COMPDAT());
    ui->COMPDATTable->setModel(model);

    auto delCOMPDATShortcut = new QShortcut(QKeySequence(Qt::Key_Delete), ui->COMPDATTable);
    auto insCOMPDATShortcut = new QShortcut(QKeySequence(Qt::Key_Insert), ui->COMPDATTable);

    connect(delCOMPDATShortcut, SIGNAL(activated()), this, SLOT(HandleDeleteCOMPDATRow()));
    connect(insCOMPDATShortcut, SIGNAL(activated()), this, SLOT(HandleInsertCOMPDATRow()));

    model = new QSortFilterProxyModel(this);
    model->setSourceModel(project->Wells()->WCONPROD());
    ui->WCONPRODTable->setModel(model);

    auto delWCONPRODShortcut = new QShortcut(QKeySequence(Qt::Key_Delete), ui->WCONPRODTable);
    auto insWCONPRODShortcut = new QShortcut(QKeySequence(Qt::Key_Insert), ui->WCONPRODTable);

    connect(delWCONPRODShortcut, SIGNAL(activated()), this, SLOT(HandleDeleteWCONPRODRow()));
    connect(insWCONPRODShortcut, SIGNAL(activated()), this, SLOT(HandleInsertWCONPRODRow()));

    model = new QSortFilterProxyModel(this);
    model->setSourceModel(project->Wells()->WCONINJE());
    ui->WCONINJETable->setModel(model);

    auto delWCONINJEShortcut = new QShortcut(QKeySequence(Qt::Key_Delete), ui->WCONINJETable);
    auto insWCONINJEShortcut = new QShortcut(QKeySequence(Qt::Key_Insert), ui->WCONINJETable);

    connect(delWCONINJEShortcut, SIGNAL(activated()), this, SLOT(HandleDeleteWCONINJERow()));
    connect(insWCONINJEShortcut, SIGNAL(activated()), this, SLOT(HandleInsertWCONINJERow()));
}

WellsScheduleForm::~WellsScheduleForm()
{
    delete ui;
}

void WellsScheduleForm::HandleDeleteWELSPECSRow()
{
    for(auto index: ui->WELSPECSTable->selectionModel()->selectedRows()) ui->WELSPECSTable->model()->removeRow(index.row(), index.parent());
}

void WellsScheduleForm::HandleInsertWELSPECSGroup()
{
    if(ui->WELSPECSTable->selectionModel()->hasSelection())
    {
        for(auto index: ui->WELSPECSTable->selectionModel()->selectedRows())
            ui->WELSPECSTable->model()->insertRow(index.row(), index.parent());
    }
    else
    {
        ui->WELSPECSTable->model()->insertRow(0, QModelIndex());
    }
}

void WellsScheduleForm::HandleInsertWELSPECSRow()
{
    if(ui->WELSPECSTable->selectionModel()->hasSelection())
    {
        for(auto index: ui->WELSPECSTable->selectionModel()->selectedRows())
        {
            if(!index.parent().isValid())
                ui->WELSPECSTable->model()->insertRow(0, index);
        }
    }
    else
    {
        ui->WELSPECSTable->model()->insertRow(0, QModelIndex());
    }
}

void WellsScheduleForm::HandleDeleteCOMPDATRow()
{
    for(auto index: ui->COMPDATTable->selectionModel()->selectedRows()) ui->COMPDATTable->model()->removeRow(index.row(), index.parent());
}

void WellsScheduleForm::HandleInsertCOMPDATRow()
{
    if(ui->COMPDATTable->selectionModel()->hasSelection())
    {
        for(auto index: ui->COMPDATTable->selectionModel()->selectedRows())
            ui->COMPDATTable->model()->insertRow(index.row(), index.parent());
    }
    else
    {
        ui->COMPDATTable->model()->insertRow(0, QModelIndex());
    }
}

void WellsScheduleForm::HandleDeleteWCONPRODRow()
{
    for(auto index: ui->WCONPRODTable->selectionModel()->selectedRows()) ui->WCONPRODTable->model()->removeRow(index.row(), index.parent());
}

void WellsScheduleForm::HandleInsertWCONPRODRow()
{
    if(ui->WCONPRODTable->selectionModel()->hasSelection())
    {
        for(auto index: ui->WCONPRODTable->selectionModel()->selectedRows())
            ui->WCONPRODTable->model()->insertRow(index.row(), index.parent());
    }
    else
    {
        ui->WCONPRODTable->model()->insertRow(0, QModelIndex());
    }
}

void WellsScheduleForm::HandleDeleteWCONINJERow()
{
    for(auto index: ui->WCONINJETable->selectionModel()->selectedRows()) ui->WCONINJETable->model()->removeRow(index.row(), index.parent());
}

void WellsScheduleForm::HandleInsertWCONINJERow()
{
    if(ui->WCONINJETable->selectionModel()->hasSelection())
    {
        for(auto index: ui->WCONINJETable->selectionModel()->selectedRows())
            ui->WCONINJETable->model()->insertRow(index.row(), index.parent());
    }
    else
    {
        ui->WCONINJETable->model()->insertRow(0, QModelIndex());
    }
}

}}}}
