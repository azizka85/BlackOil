#ifndef COMPDATDATA_H
#define COMPDATDATA_H

#include <qvariant.h>
#include <qstring.h>
#include <qdatetime.h>

#include <data_global.h>

namespace BlackOil {
namespace Data {
namespace Project {

class DATA_EXPORT COMPDATData
{
public:
    COMPDATData();

    QString WellName();
    QVariant I();
    QVariant J();
    QVariant K1();
    QVariant K2();
    QVariant WellStatus();
    QVariant SATNUM();
    QVariant TranFactor();
    QVariant Diameter();
    QVariant Kh();
    QVariant SkinFactor();
    QDateTime Date();

    void SetWellName(const QString& wellName);
    void SetI(const QVariant& i);
    void SetJ(const QVariant& j);
    void SetK1(const QVariant& k1);
    void SetK2(const QVariant& k2);
    void SetWellStatus(const QVariant& wellStatus);
    void SetSATNUM(const QVariant& satnum);
    void SetTranFactor(const QVariant& tranFactor);
    void SetDiameter(const QVariant& diameter);
    void SetKh(const QVariant& kh);
    void SetSkinFactor(const QVariant& skinFactor);
    void SetDate(const QDateTime& date);

    void InitVariables();

protected:
    QString wellName;
    QVariant wellStatus, i, j, k1, k2, satnum, tranFactor, diameter, kh, skinFactor;
    QDateTime date;};

}}}

#endif // COMPDATDATA_H
