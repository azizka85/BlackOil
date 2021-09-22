#ifndef FIGURESETTINGSFORM_H
#define FIGURESETTINGSFORM_H

#include <qvector.h>

#include <qwidget.h>

#include <qsortfilterproxymodel.h>

#include <QtCharts/qlineseries.h>
#include <QtCharts/qscatterseries.h>

#include <figuresettingsmodel.h>

#include <booleandelegate.h>
#include <colordelegate.h>

#include <desktop_global.h>

using namespace QtCharts;

using namespace BlackOil::Desktop::Models;
using namespace BlackOil::Desktop::Delegates;

namespace Ui {
class FigureSettingsForm;
}

namespace BlackOil {
namespace Desktop {
namespace Views {
namespace Settings {

class DESKTOP_EXPORT FigureSettingsForm : public QWidget
{
    Q_OBJECT
public:
    explicit FigureSettingsForm(QVector<QLineSeries *> *lines, QVector<QScatterSeries *> *scatters, QWidget *parent = nullptr);
    ~FigureSettingsForm();

protected:
    Ui::FigureSettingsForm *ui;
};

}}}}

#endif // FIGURESETTINGSFORM_H
