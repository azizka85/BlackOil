#ifndef ECLIPSEFILEREADERTEST_H
#define ECLIPSEFILEREADERTEST_Hs

#include <eclipsefilereader.h>

#include <test.h>

using namespace BlackOil::Data::Project;
using namespace BlackOil::Data::Readers;

namespace BlackOil {
namespace Test {
namespace Data {
namespace Readers {

class EclipseFileReaderTest : public QObject
{
    Q_OBJECT
public:
    explicit EclipseFileReaderTest(QObject *parent = nullptr);

private slots:
    void CheckFile1();
    void CheckFile2();
};

}}}}

#endif // ECLIPSEFILEREADERTEST_H
