#ifndef PROCESSPROJECTTASK_H
#define PROCESSPROJECTTASK_H

#include <qthread.h>

#include <projectmodel.h>

#include <model_global.h>

using namespace BlackOil::Model;

namespace BlackOil {
namespace Model {
namespace Tasks {

class MODEL_EXPORT ProcessProjectTask : public QThread
{
    Q_OBJECT
public:
    explicit ProcessProjectTask(ProjectModel *project, QObject *parent = nullptr);

    void Process();

signals:
    void Finished();

protected:
    void run() override;

protected:
    ProjectModel *project;
};

}}}

#endif // PROCESSPROJECTTASK_H
