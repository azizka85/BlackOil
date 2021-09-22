#ifndef GRIDSETTINGSFORM_H
#define GRIDSETTINGSFORM_H

#include <qwidget.h>

#include <projectmodel.h>

#include <desktop_global.h>

using namespace BlackOil::Model;

namespace Ui {
class GridSettingsForm;
}

namespace BlackOil {
namespace Desktop {
namespace Views {
namespace Settings {

class DESKTOP_EXPORT GridSettingsForm : public QWidget
{
    Q_OBJECT

public:
    explicit GridSettingsForm(ProjectModel *project, QWidget *parent = nullptr);
    ~GridSettingsForm();

public slots:
    void HandleDataChanged();

signals:
    void DataChanged();

protected:
    Ui::GridSettingsForm *ui;

    ProjectModel *project;
};

}}}}

#endif // GRIDSETTINGSFORM_H
