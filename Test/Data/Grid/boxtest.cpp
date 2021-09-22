#include "boxtest.h"

namespace BlackOil {
namespace Test {
namespace Data {
namespace Grid {

BoxTest::BoxTest(QObject* parent): QObject(parent) { }

void BoxTest::CheckVariables()
{
    Box box;

    VERIFY(box.I1() == -1, "");
    VERIFY(box.I2() == -1, "");
    VERIFY(box.J1() == -1, "");
    VERIFY(box.J2() == -1, "");
    VERIFY(box.K1() == -1, "");
    VERIFY(box.K2() == -1, "");

    VERIFY(box.Nx() == 0, "");
    VERIFY(box.Ny() == 0, "");
    VERIFY(box.Nz() == 0, "");
    VERIFY(box.N() == 0, "");

    box = Box(23, 78, 56, 29, 67, 41);

    VERIFY(box.I1() == 23, "");
    VERIFY(box.I2() == 78, "");
    VERIFY(box.J1() == 56, "");
    VERIFY(box.J2() == 29, "");
    VERIFY(box.K1() == 67, "");
    VERIFY(box.K2() == 41, "");

    VERIFY(box.Nx() == 56, "");
    VERIFY(box.Ny() == 0, "");
    VERIFY(box.Nz() == 0, "");
    VERIFY(box.N() == 0, "");

    box = Box(13, 97, 34, 78, 25, 53);

    VERIFY(box.I1() == 13, "");
    VERIFY(box.I2() == 97, "");
    VERIFY(box.J1() == 34, "");
    VERIFY(box.J2() == 78, "");
    VERIFY(box.K1() == 25, "");
    VERIFY(box.K2() == 53, "");

    VERIFY(box.Nx() == 85, "");
    VERIFY(box.Ny() == 45, "");
    VERIFY(box.Nz() == 29, "");
    VERIFY(box.N() == 110925, "");

    VERIFY(box.Contains(14, 35, 29), "");
    VERIFY(!box.Contains(12, 76, 45), "");

    VERIFY(box.BelongsX(33, 44), "");
    VERIFY(!box.BelongsX(11, 44), "");
    VERIFY(!box.BelongsX(77, 99), "");

    VERIFY(box.BelongsY(44, 77), "");
    VERIFY(!box.BelongsY(22, 44), "");
    VERIFY(!box.BelongsY(77, 88), "");

    VERIFY(box.BelongsZ(33, 44), "");
    VERIFY(!box.BelongsZ(11, 44), "");
    VERIFY(!box.BelongsZ(44, 99), "");

    Box checkBox(33, 44, 44, 77, 33, 44);

    VERIFY(box.Belongs(checkBox), "");

    checkBox = Box(11, 44, 22, 44, 11, 44);

    VERIFY(!box.Belongs(checkBox), "");

    checkBox = Box(77, 99, 77, 88, 44, 99);

    VERIFY(!box.Belongs(checkBox), "");
}

void BoxTest::CheckClone()
{
    Box box(1, 2, 3, 4, 5, 6);
    Box checkBox = box;

    VERIFY(box.I1() == 1, "");
    VERIFY(box.I2() == 2, "");
    VERIFY(box.J1() == 3, "");
    VERIFY(box.J2() == 4, "");
    VERIFY(box.K1() == 5, "");
    VERIFY(box.K2() == 6, "");

    VERIFY(checkBox.I1() == 1, "");
    VERIFY(checkBox.I2() == 2, "");
    VERIFY(checkBox.J1() == 3, "");
    VERIFY(checkBox.J2() == 4, "");
    VERIFY(checkBox.K1() == 5, "");
    VERIFY(checkBox.K2() == 6, "");

    checkBox.InitVariables();

    VERIFY(box.I1() == 1, "");
    VERIFY(box.I2() == 2, "");
    VERIFY(box.J1() == 3, "");
    VERIFY(box.J2() == 4, "");
    VERIFY(box.K1() == 5, "");
    VERIFY(box.K2() == 6, "");

    VERIFY(checkBox.I1() == -1, "");
    VERIFY(checkBox.I2() == -1, "");
    VERIFY(checkBox.J1() == -1, "");
    VERIFY(checkBox.J2() == -1, "");
    VERIFY(checkBox.K1() == -1, "");
    VERIFY(checkBox.K2() == -1, "");
}

void BoxTest::CheckLocalToGlobalIndex()
{
    Box box(1, 2, 1, 2, 1, 2);

    int index = box.LocalToGlobalIndex(0, 4, 4);

    VERIFY(index == 21, "");

    index = box.LocalToGlobalIndex(2, 4, 4);

    VERIFY(index == 25, "");

    index = box.LocalToGlobalIndex(4, 4, 4);

    VERIFY(index == 37, "");

    index = box.LocalToGlobalIndex(7, 4, 4);

    VERIFY(index == 42, "");
}

}}}}
