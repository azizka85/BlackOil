#ifndef DRAWSCENETASK_H
#define DRAWSCENETASK_H

#include <qthread.h>

#include <fieldform.h>

#include <desktop_global.h>

using namespace BlackOil::Desktop::Views::Controls;

namespace BlackOil {
namespace Desktop {
namespace Tasks {

class DESKTOP_EXPORT DrawSceneTask : public QThread
{
    Q_OBJECT
public:
    explicit DrawSceneTask(FieldForm *fieldForm, QObject *parent = nullptr);

    void Draw();

signals:
    void Finished();

protected:
    FieldForm *fieldForm;

    // QThread interface
protected:
    void run() override;
};

}}}

#endif // DRAWSCENETASK_H
