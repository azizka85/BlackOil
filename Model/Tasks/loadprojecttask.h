#ifndef LOADPROJECTTASK_H
#define LOADPROJECTTASK_H

#include <qstring.h>
#include <qthread.h>

#include <projectmodel.h>

#include <model_global.h>

using namespace BlackOil::Model;

namespace BlackOil {
namespace Model {
namespace Tasks {

class MODEL_EXPORT LoadProjectTask : public QThread
{
    Q_OBJECT
public:
    explicit LoadProjectTask(ProjectModel *project, QObject *parent = nullptr);

    void Load(const QString &projectPath);

signals:
    void Finished();

protected:
    void run() override;

protected:
    ProjectModel *project;
};

}}}

#endif // LOADPROJECTTASK_H
