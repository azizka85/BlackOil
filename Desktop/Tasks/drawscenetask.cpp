#include "drawscenetask.h"

namespace BlackOil {
namespace Desktop {
namespace Tasks {

DrawSceneTask::DrawSceneTask(FieldForm *fieldForm, QObject *parent) : QThread(parent)
{
    this->fieldForm = fieldForm;
}

void DrawSceneTask::Draw()
{
    start();
}

void DrawSceneTask::run()
{
    fieldForm->InitScene();

    emit Finished();
}

}}}
