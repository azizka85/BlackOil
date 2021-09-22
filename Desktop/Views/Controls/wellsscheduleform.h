#ifndef WELLSSCHEDULEFORM_H
#define WELLSSCHEDULEFORM_H

#include <qwidget.h>
#include <qshortcut.h>
#include <qsortfilterproxymodel.h>

#include <qmessagebox.h>

#include <projectmodel.h>

#include <desktop_global.h>

using namespace BlackOil::Model;

namespace Ui {
class WellsScheduleForm;
}

namespace BlackOil {
namespace Desktop {
namespace Views {
namespace Controls {

class DESKTOP_EXPORT WellsScheduleForm : public QWidget
{
    Q_OBJECT

public:
    explicit WellsScheduleForm(ProjectModel *project, QWidget *parent = nullptr);
    ~WellsScheduleForm();

protected slots:
    void HandleDeleteWELSPECSRow();
    void HandleInsertWELSPECSGroup();
    void HandleInsertWELSPECSRow();

    void HandleDeleteCOMPDATRow();
    void HandleInsertCOMPDATRow();

    void HandleDeleteWCONPRODRow();
    void HandleInsertWCONPRODRow();

    void HandleDeleteWCONINJERow();
    void HandleInsertWCONINJERow();

protected:
    Ui::WellsScheduleForm *ui;
    ProjectModel *project;
};

}}}}

#endif // WELLSSCHEDULEFORM_H
