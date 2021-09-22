#include "loadprojecttask.h"

namespace BlackOil {
namespace Model {
namespace Tasks {

LoadProjectTask::LoadProjectTask(ProjectModel *project, QObject *parent) : QThread(parent)
{
    this->project = project;
}

void LoadProjectTask::Load(const QString &projectPath)
{
    project->SetProjectPath(projectPath);

    start();
}

void LoadProjectTask::run()
{
    project->Load();

    emit Finished();
}

}}}
