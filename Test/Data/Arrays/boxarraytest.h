#ifndef BOXARRAYTEST_H
#define BOXARRAYTEST_H

#include <qobject.h>

#include <box.h>
#include <boxarray.h>

#include <test.h>

using namespace BlackOil::Data::Grid;
using namespace BlackOil::Data::Arrays;

namespace BlackOil {
namespace Test {
namespace Data {
namespace Arrays {

class BoxArrayTest : public QObject
{
    Q_OBJECT
public:
    explicit BoxArrayTest(QObject *parent = nullptr);

private slots:
    void Check();
};

}}}}

#endif // BOXARRAYTEST_H
