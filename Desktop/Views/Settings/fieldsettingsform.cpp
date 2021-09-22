#include "fieldsettingsform.h"
#include "ui_fieldsettingsform.h"

namespace BlackOil {
namespace Desktop {
namespace Views {
namespace Settings {

FieldSettingsForm::FieldSettingsForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FieldSettingsForm)
{
    ui->setupUi(this);

    ui->RotationComboBox->setModel(new RotationAxisEnum(this));

    connect(ui->DisplayWellsCheckBox, SIGNAL(toggled(bool)), this, SLOT(ToggleWellInfoCheckBox(bool)));
}

FieldSettingsForm::~FieldSettingsForm()
{
    delete ui;
}

QCheckBox *FieldSettingsForm::DisplayPaletteCheckBox()
{
    return ui->DisplayPaletteCheckBox;
}

QCheckBox *FieldSettingsForm::DisplayMeshCheckBox()
{
    return ui->DisplayMeshCheckBox;
}

QSlider *FieldSettingsForm::MeshWidthSlider()
{
    return ui->MeshWidthSlider;
}

QCheckBox *FieldSettingsForm::DisplayBoxCheckBox()
{
    return ui->DisplayBoxCheckBox;
}

QCheckBox *FieldSettingsForm::DisplayWellsCheckBox()
{
    return ui->DisplayWellsCheckBox;
}

QCheckBox *FieldSettingsForm::DisplayAxesCheckBox()
{
    return ui->DisplayAxesCheckBox;
}

QDoubleSpinBox *FieldSettingsForm::AxesLengthSpinBox()
{
    return ui->AxesLengthSpinBox;
}

QCheckBox *FieldSettingsForm::DisplayLegendCheckBox()
{
    return ui->DisplayLegendCheckBox;
}

QPushButton *FieldSettingsForm::LegendSettingsButton()
{
    return ui->LegendSettingsButton;
}

QPushButton *FieldSettingsForm::PaletteSettingsButton()
{
    return ui->PaletteSettingsButton;
}

QPushButton *FieldSettingsForm::PaletteValuesButton()
{
    return ui->PaletteValuesButton;
}

QPushButton *FieldSettingsForm::GridSettingsButton()
{
    return ui->GridSettingsButton;
}

QPushButton *FieldSettingsForm::WellSettingsButton()
{
    return ui->WellSettingsButton;
}

QComboBox *FieldSettingsForm::RotationComboBox()
{
    return ui->RotationComboBox;
}

QDoubleSpinBox *FieldSettingsForm::ScaleXSpinBox()
{
    return ui->ScaleXSpinBox;
}

QDoubleSpinBox *FieldSettingsForm::ScaleYSpinBox()
{
    return ui->ScaleYSpinBox;
}

QDoubleSpinBox *FieldSettingsForm::ScaleZSpinBox()
{
    return ui->ScaleZSpinBox;
}

QPushButton *FieldSettingsForm::XYViewAxisButton()
{
    return ui->XYViewAxisButton;
}

QPushButton *FieldSettingsForm::XZViewAxisButton()
{
    return ui->XZViewAxisButton;
}

QPushButton *FieldSettingsForm::YZViewAxisButton()
{
    return ui->YZViewAxisButton;
}

void FieldSettingsForm::ToggleWellInfoCheckBox(bool wellsDisplayed)
{
    if(!wellsDisplayed) ui->DisplayWellInfoCheckBox->setChecked(false);
}

}}}}
