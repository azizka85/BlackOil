#ifndef WIDGETHELPER_H
#define WIDGETHELPER_H

#include <qwidget.h>
#include <qgridlayout.h>

#include <desktop_global.h>

namespace BlackOil {
namespace Desktop {
namespace Helpers {

class DESKTOP_EXPORT WidgetHelper
{
public:
    static void SetWidgetSpan(QWidget *widget, QGridLayout *layout, int rowSpan = 1, int colSpan = 1);
};

}}}

#endif // WIDGETHELPER_H
