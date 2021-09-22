#include "scenedrawingdialog.h"
#include "ui_scenedrawingdialog.h"

namespace BlackOil {
namespace Desktop {
namespace Views {
namespace Dialogs {

SceneDrawingDialog::SceneDrawingDialog(ProjectModel *project, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SceneDrawingDialog)
{
    this->project = project;

    setWindowFlags(Qt::Dialog | Qt::WindowTitleHint);

    ui->setupUi(this);

    auto movie = new QMovie(":/Images/icon-waiting.gif");

    ui->MovieLabel->setMovie(movie);

    movie->start();

    connect(project, SIGNAL(LoadingStateChanged(int)), this, SLOT(ProjectLoadingStateChanged(int)));
}

SceneDrawingDialog::~SceneDrawingDialog()
{
    delete ui;
}

void SceneDrawingDialog::ProjectLoadingStateChanged(int state)
{
    switch (state)
    {
        case ProjectLoadingStateEnum::StartLoading:
            ui->TitleLabel->setText(tr("Идет загрузка ..."));
            break;
        case ProjectLoadingStateEnum::Processing:
            ui->TitleLabel->setText(tr("Обработка данных ..."));
            break;
        case ProjectLoadingStateEnum::Drawing:
            ui->TitleLabel->setText(tr("Отрисовка сцены ..."));
            break;
        case ProjectLoadingStateEnum::FinishLoading:
            ui->TitleLabel->setText(tr("Завершение загрузки ..."));
            hide();
            break;
    }
}

}}}}
