#ifndef BOXTEST_H
#define BOXTEST_H

#include <qobject.h>

#include <box.h>

#include <test.h>

using namespace BlackOil::Data::Grid;

namespace BlackOil {
namespace Test {
namespace Data {
namespace Grid {

class BoxTest: public QObject
{
    Q_OBJECT
public:
    explicit BoxTest(QObject* parent = nullptr);

private slots:
    void CheckVariables();
    void CheckClone();
    void CheckLocalToGlobalIndex();
};

}}}}

#endif // BOXTEST_H
