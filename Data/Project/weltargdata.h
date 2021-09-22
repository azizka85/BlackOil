#ifndef WELTARGDATA_H
#define WELTARGDATA_H

#include <qstring.h>
#include <qvariant.h>
#include <qdatetime.h>

#include <data_global.h>

namespace BlackOil {
namespace Data {
namespace Project {

class DATA_EXPORT WELTARGData
{
public:
    WELTARGData();

    QString WellName();
    QVariant WellControl();
    QVariant Value();
    QDateTime Date();

    void SetWellName(const QString& wellName);
    void SetWellControl(const QVariant& wellControl);
    void SetValue(const QVariant& value);
    void SetDate(const QDateTime& date);

    void InitVariables();

protected:
    QString wellName;
    QVariant wellControl, value;
    QDateTime date;};

}}}

#endif // WELTARGDATA_H
