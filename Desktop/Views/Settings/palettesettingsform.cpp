#include "palettesettingsform.h"
#include "ui_palettesettingsform.h"

namespace BlackOil {
namespace Desktop {
namespace Views {
namespace Settings {

PaletteSettingsForm::PaletteSettingsForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PaletteSettingsForm)
{
    ui->setupUi(this);

    connect(ui->SelectableCheckBox, SIGNAL(toggled(bool)), this, SLOT(HandleSelectableToggled(bool)));
    connect(ui->LightEnabledCheckBox, SIGNAL(toggled(bool)), this, SLOT(HandleLightEnabledToggled(bool)));
    connect(ui->TransparencySlider, SIGNAL(valueChanged(int)), this, SLOT(HandleTransparencyValueChanged()));
}

PaletteSettingsForm::~PaletteSettingsForm()
{
    delete ui;
}

bool PaletteSettingsForm::Selectable()
{
    return ui->SelectableCheckBox->isChecked();
}

bool PaletteSettingsForm::LightEnabled()
{
    return ui->LightEnabledCheckBox->isChecked();
}

float PaletteSettingsForm::Transparency()
{
    return 1 - ui->TransparencySlider->value()/10.0;
}

void PaletteSettingsForm::SetSelectable(bool selectable)
{
    ui->SelectableCheckBox->setChecked(selectable);
}

void PaletteSettingsForm::SetLightEnabled(bool lightEnabled)
{
    ui->LightEnabledCheckBox->setChecked(lightEnabled);
}

void PaletteSettingsForm::SetTransparency(float transparency)
{
    int value = 9;

    if(transparency > 0.1)
    {
        if(transparency <= 1)
            value = 10 - qFloor(10*transparency);
        else
            value = 0;
    }

    ui->TransparencySlider->setValue(value);
}

void PaletteSettingsForm::HandleSelectableToggled(bool selectable)
{
    emit SelectableChanged(selectable);
}

void PaletteSettingsForm::HandleLightEnabledToggled(bool lightEnabled)
{
    emit LightEnabledChanged(lightEnabled);
}

void PaletteSettingsForm::HandleTransparencyValueChanged()
{
    emit TransparencyChanged(Transparency());
}

}}}}
