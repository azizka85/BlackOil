#ifndef WCONHISTDATA_H
#define WCONHISTDATA_H

#include <qvariant.h>
#include <qstring.h>
#include <qdatetime.h>

#include <data_global.h>

namespace BlackOil {
namespace Data {
namespace Project {

class DATA_EXPORT WCONHISTData
{
public:
    WCONHISTData();

    QString WellName();
    QVariant WellStatus();
    QVariant WellControl();
    QVariant ORAT();
    QVariant WRAT();
    QVariant GRAT();
    QDateTime Date();

    void SetWellName(const QString& wellName);
    void SetWellStatus(const QVariant& wellStatus);
    void SetWellControl(const QVariant& wellControl);
    void SetORAT(const QVariant& orat);
    void SetWRAT(const QVariant& wrat);
    void SetGRAT(const QVariant& grat);
    void SetDate(const QDateTime& date);

    void InitVariables();

protected:
    QString wellName;
    QVariant wellStatus, wellControl, orat, wrat, grat;
    QDateTime date;
};

}}}

#endif // WCONHISTDATA_H
