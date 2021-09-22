#include "widgethelper.h"

namespace BlackOil {
namespace Desktop {
namespace Helpers {

void WidgetHelper::SetWidgetSpan(QWidget *widget, QGridLayout *layout, int rowSpan, int colSpan)
{
    int row = -1;
    int col = -1;
    int rSpan = 1;
    int cSpan = 1;

    int index = layout->indexOf(widget);
    layout->getItemPosition(index, &row, &col, &rSpan, &cSpan);

    if(row >= 0 && col >= 0) layout->addWidget(widget, row, col, rowSpan, colSpan);
}

}}}
