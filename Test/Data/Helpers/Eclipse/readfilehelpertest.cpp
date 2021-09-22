#include "readfilehelpertest.h"

namespace BlackOil {
namespace Test {
namespace Data {
namespace Helpers {
namespace Eclipse {

ReadFileHelperTest::ReadFileHelperTest(QObject *parent) : QObject(parent) { }

void ReadFileHelperTest::CheckEclipseDateToStr()
{
    QStringList dates({"3", "jun", "2020"});

    QMetaObject metaObject = MonthsEnum::staticMetaObject;

    QMetaEnum monthsEnum = metaObject.enumerator(metaObject.indexOfEnumerator("Months"));

    VERIFY(ReadFileHelper::EclipseDateToStr(dates, monthsEnum) == "03.06.2020", "");
}

void ReadFileHelperTest::CheckDateToStr()
{
    VERIFY(ReadFileHelper::DateToStr(QDateTime(QDate(2020, 6, 3))) == "03.06.2020", "");
}

void ReadFileHelperTest::CheckStrToDate()
{
    VERIFY(ReadFileHelper::StrToDate(QString("03.06.2020")) == QDateTime(QDate(2020, 6, 3)), "");
}

void ReadFileHelperTest::CheckIsYes()
{
    VERIFY(ReadFileHelper::IsYes("YES"), "");
    VERIFY(ReadFileHelper::IsYes("Y"), "");
    VERIFY(!ReadFileHelper::IsYes("NO"), "");
    VERIFY(!ReadFileHelper::IsYes("N"), "");
}

}}}}}
