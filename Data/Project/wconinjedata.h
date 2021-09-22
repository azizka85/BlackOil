#ifndef WCONINJEDATA_H
#define WCONINJEDATA_H

#include <qvariant.h>
#include <qstring.h>
#include <qdatetime.h>

#include <data_global.h>

namespace BlackOil {
namespace Data {
namespace Project {

class DATA_EXPORT WCONINJEData
{
public:
    WCONINJEData();

    QString WellName();
    QVariant InjFluid();
    QVariant WellStatus();
    QVariant WellControl();
    QVariant RATE();
    QVariant RESV();
    QVariant BHP();
    QDateTime Date();

    void SetWellName(const QString& wellName);
    void SetInjFluid(const QVariant& injFluid);
    void SetWellStatus(const QVariant& wellStatus);
    void SetWellControl(const QVariant& wellControl);
    void SetRATE(const QVariant& rate);
    void SetRESV(const QVariant& resv);
    void SetBHP(const QVariant& bhp);
    void SetDate(const QDateTime& date);

    void InitVariables();

protected:
    QString wellName;
    QVariant wellStatus, wellControl, injFluid, rate, resv, bhp;
    QDateTime date;};

}}}

#endif // WCONINJEDATA_H
