#ifndef READFILEHELPERTEST_H
#define READFILEHELPERTEST_H

#include <qmetaobject.h>
#include <qobject.h>
#include <qstringlist.h>
#include <qdatetime.h>

#include <monthsenum.h>
#include <readfilehelper.h>

#include <test.h>

using namespace BlackOil::Data::Helpers::Eclipse;
using namespace BlackOil::Data::Project;

namespace BlackOil {
namespace Test {
namespace Data {
namespace Helpers {
namespace Eclipse {

class ReadFileHelperTest : public QObject
{
    Q_OBJECT
public:
    explicit ReadFileHelperTest(QObject *parent = nullptr);

private slots:
    void CheckEclipseDateToStr();
    void CheckDateToStr();
    void CheckStrToDate();
    void CheckIsYes();
};

}}}}}

#endif // READFILEHELPERTEST_H
