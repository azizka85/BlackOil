#ifndef SCENEDRAWINGDIALOG_H
#define SCENEDRAWINGDIALOG_H

#include <qdialog.h>
#include <qmovie.h>

#include <projectmodel.h>

#include <desktop_global.h>

using namespace BlackOil::Model;

namespace Ui {
class SceneDrawingDialog;
}

namespace BlackOil {
namespace Desktop {
namespace Views {
namespace Dialogs {

class DESKTOP_EXPORT SceneDrawingDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SceneDrawingDialog(ProjectModel *project, QWidget *parent = nullptr);
    ~SceneDrawingDialog();

public slots:
    void ProjectLoadingStateChanged(int state);

protected:
    Ui::SceneDrawingDialog *ui;

    ProjectModel *project;
};

}}}}

#endif // SCENEDRAWINGDIALOG_H
