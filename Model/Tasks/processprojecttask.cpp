#include "processprojecttask.h"

namespace BlackOil {
namespace Model {
namespace Tasks {

ProcessProjectTask::ProcessProjectTask(ProjectModel *project, QObject *parent) : QThread(parent)
{
    this->project = project;
}

void ProcessProjectTask::Process()
{
    start();
}

void ProcessProjectTask::run()
{
    project->ProcessData();

    emit Finished();
}

}}}
