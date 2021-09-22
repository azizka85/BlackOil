#ifndef FIELDSETTINGSFORM_H
#define FIELDSETTINGSFORM_H

#include <qwidget.h>
#include <QDoubleSpinBox>
#include <qcheckbox.h>
#include <qcombobox.h>
#include <qpushbutton.h>
#include <qslider.h>

#include <rotationaxisenum.h>

#include <desktop_global.h>

using namespace BlackOil::Desktop::Models;

namespace Ui {
class FieldSettingsForm;
}

namespace BlackOil {
namespace Desktop {
namespace Views {
namespace Settings {

class DESKTOP_EXPORT FieldSettingsForm : public QWidget
{
    Q_OBJECT

public:
    explicit FieldSettingsForm(QWidget *parent = nullptr);
    ~FieldSettingsForm();

    QCheckBox *DisplayPaletteCheckBox();
    QCheckBox *DisplayMeshCheckBox();
    QSlider *MeshWidthSlider();
    QCheckBox *DisplayBoxCheckBox();
    QCheckBox *DisplayWellsCheckBox();
    QCheckBox *DisplayAxesCheckBox();
    QDoubleSpinBox *AxesLengthSpinBox();
    QCheckBox *DisplayLegendCheckBox();
    QPushButton *LegendSettingsButton();
    QPushButton *PaletteSettingsButton();
    QPushButton *PaletteValuesButton();
    QPushButton *GridSettingsButton();
    QPushButton *WellSettingsButton();
    QComboBox *RotationComboBox();
    QDoubleSpinBox *ScaleXSpinBox();
    QDoubleSpinBox *ScaleYSpinBox();
    QDoubleSpinBox *ScaleZSpinBox();
    QPushButton *XYViewAxisButton();
    QPushButton *XZViewAxisButton();
    QPushButton *YZViewAxisButton();

protected slots:
    void ToggleWellInfoCheckBox(bool wellsDisplayed);

private:
    Ui::FieldSettingsForm *ui;
};

}}}}

#endif // FIELDSETTINGSFORM_H
