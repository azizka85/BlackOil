#ifndef PROJECTLOADINGDIALOG_H
#define PROJECTLOADINGDIALOG_H

#include <qbytearray.h>

#include <qdialog.h>
#include <qmovie.h>

#include <projectloadingstateenum.h>

#include <projectmodel.h>

#include <desktop_global.h>

using namespace BlackOil::Model;

namespace Ui {
class ProjectLoadingDialog;
}

namespace BlackOil {
namespace Desktop {
namespace Views {
namespace Dialogs {

class DESKTOP_EXPORT ProjectLoadingDialog : public QDialog
{
    Q_OBJECT
public:
    explicit ProjectLoadingDialog(ProjectModel *project, QWidget *parent = nullptr);
    ~ProjectLoadingDialog();

public slots:
    void ProjectLoadingStateChanged(int state);

protected:
    Ui::ProjectLoadingDialog *ui;
    ProjectModel *project;
};

}}}}

#endif // PROJECTLOADINGDIALOG_H
