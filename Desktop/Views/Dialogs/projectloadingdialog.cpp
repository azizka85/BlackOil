#include "projectloadingdialog.h"
#include "ui_projectloadingdialog.h"

namespace BlackOil {
namespace Desktop {
namespace Views {
namespace Dialogs {

ProjectLoadingDialog::ProjectLoadingDialog(ProjectModel *project, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ProjectLoadingDialog)
{
    this->project = project;

    setWindowFlags(Qt::Dialog | Qt::WindowTitleHint);
    setFixedSize(QSize(350, 160));

    ui->setupUi(this);

    auto movie = new QMovie(":/Images/icon-waiting.gif");

    ui->MovieLabel->setMovie(movie);

    movie->start();

    connect(project, SIGNAL(LoadingStateChanged(int)), this, SLOT(ProjectLoadingStateChanged(int)));
}

ProjectLoadingDialog::~ProjectLoadingDialog()
{
    delete ui;
}

void ProjectLoadingDialog::ProjectLoadingStateChanged(int state)
{
    switch (state)
    {
        case ProjectLoadingStateEnum::StartLoading:
            ui->TitleLabel->setText(tr("Идет загрузка ..."));
            ui->ProgressBar->setValue(0);
            break;
        case ProjectLoadingStateEnum::Processing:
            ui->TitleLabel->setText(tr("Обработка данных ..."));
            ui->ProgressBar->setValue(33);
            break;
        case ProjectLoadingStateEnum::Drawing:
            ui->TitleLabel->setText(tr("Отрисовка сцены ..."));
            ui->ProgressBar->setValue(66);
            break;
        case ProjectLoadingStateEnum::FinishLoading:
            ui->TitleLabel->setText(tr("Завершение загрузки ..."));
            ui->ProgressBar->setValue(99);
            hide();
            break;
    }
}

}}}}
