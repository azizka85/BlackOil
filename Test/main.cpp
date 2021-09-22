#include <qtest.h>

#include <boxtest.h>
#include <boxarraytest.h>
#include <readfilehelpertest.h>
#include <projectdatatest.h>
#include <eclipsefilereadertest.h>

using namespace BlackOil::Test::Data::Grid;
using namespace BlackOil::Test::Data::Arrays;
using namespace BlackOil::Test::Data::Helpers::Eclipse;
using namespace BlackOil::Test::Data::Project;
using namespace BlackOil::Test::Data::Readers;

int main(int argc, char** argv)
{
    int status = 0;

    QTEST_SET_MAIN_SOURCE_PATH

    {
        BoxTest bt;

        status |= QTest::qExec(&bt, argc, argv);
    }

    {
        BoxArrayTest bat;

        status |= QTest::qExec(&bat, argc, argv);
    }

    {
        ReadFileHelperTest rfht;

        status |= QTest::qExec(&rfht, argc, argv);
    }

    {
        ProjectDataTest pdt;

        status |= QTest::qExec(&pdt, argc, argv);
    }

    {
        EclipseFileReaderTest efrt;

        status |= QTest::qExec(&efrt, argc, argv);
    }

    return status;
}
