#ifndef PALETTESETTINGSFORM_H
#define PALETTESETTINGSFORM_H

#include <qmath.h>

#include <qwidget.h>
#include <qcheckbox.h>
#include <qslider.h>

#include <desktop_global.h>

namespace Ui {
class PaletteSettingsForm;
}

namespace BlackOil {
namespace Desktop {
namespace Views {
namespace Settings {

class DESKTOP_EXPORT PaletteSettingsForm : public QWidget
{
    Q_OBJECT

public:
    explicit PaletteSettingsForm(QWidget *parent = nullptr);
    ~PaletteSettingsForm();

    bool Selectable();
    bool LightEnabled();
    float Transparency();

public slots:
    void SetSelectable(bool selectable);
    void SetLightEnabled(bool lightEnabled);
    void SetTransparency(float transparency);

protected slots:
    void HandleSelectableToggled(bool selectable);
    void HandleLightEnabledToggled(bool lightEnabled);
    void HandleTransparencyValueChanged();

signals:
    void SelectableChanged(bool selectable);
    void LightEnabledChanged(bool lightEnabled);
    void TransparencyChanged(float transparency);

protected:
    Ui::PaletteSettingsForm *ui;
};

}}}}

#endif // PALETTESETTINGSFORM_H
