#ifndef WELSPECSDATA_H
#define WELSPECSDATA_H

#include <qvariant.h>
#include <qstring.h>
#include <qdatetime.h>

#include <data_global.h>

namespace BlackOil {
namespace Data {
namespace Project {

class DATA_EXPORT WELSPECSData
{
public:
    WELSPECSData();

    QDateTime Date();
    QString WellName();
    QString WellGroup();
    int I();
    int J();
    QVariant Depth();

    void SetDate(const QDateTime &date);
    void SetWellName(const QString &wellName);
    void SetWellGroup(const QString &wellGroup);
    void SetI(const int &i);
    void SetJ(const int &j);
    void SetDepth(const QVariant &depth);

    void InitVariables();

protected:
    int i, j;
    QVariant depth;
    QString wellName, wellGroup;
    QDateTime date;
};

}}}

#endif // WELSPECSDATA_H
