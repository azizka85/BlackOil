#include "boxarraytest.h"

namespace BlackOil {
namespace Test {
namespace Data {
namespace Arrays {

BoxArrayTest::BoxArrayTest(QObject *parent) : QObject(parent) { }

void BoxArrayTest::Check()
{
    BoxArray array;

    array.SetBox(Box(3, 6, 0, 0, 0, 0));

    VERIFY(array.CalculateIndex(5) == 2, "");

    for(int i = 0; i < array.Box().N(); i++) array.Add(i);

    VERIFY(array(2).isNull(), "");
    VERIFY(array(3) == 0, "");
    VERIFY(array(4) == 1, "");
    VERIFY(array(5) == 2, "");
    VERIFY(array(6) == 3, "");
    VERIFY(array(7).isNull(), "");

    array.Clear();

    array.SetBox(Box(3, 6, 7, 9, 0, 0));

    VERIFY(array.CalculateIndex(5, 8) == 6, "");

    for(int i = 0; i < array.Box().Nx(); i++) array.Add(i);

    array.AddInterval(4, 4);

    for(int i = 0; i < array.Box().Nx(); i++) array.Add(i);

    VERIFY(array(3, 6).isNull(), "");
    VERIFY(array(4, 6).isNull(), "");
    VERIFY(array(5, 6).isNull(), "");
    VERIFY(array(6, 6).isNull(), "");

    VERIFY(array(2, 7).isNull(), "");
    VERIFY(array(3, 7) == 0, "");
    VERIFY(array(4, 7) == 1, "");
    VERIFY(array(5, 7) == 2, "");
    VERIFY(array(6, 7) == 3, "");
    VERIFY(array(7, 7).isNull(), "");

    VERIFY(array(2, 8).isNull(), "");
    VERIFY(array(3, 8) == 4, "");
    VERIFY(array(4, 8) == 4, "");
    VERIFY(array(5, 8) == 4, "");
    VERIFY(array(6, 8) == 4, "");
    VERIFY(array(7, 8).isNull(), "");

    VERIFY(array(2, 9).isNull(), "");
    VERIFY(array(3, 9) == 0, "");
    VERIFY(array(4, 9) == 1, "");
    VERIFY(array(5, 9) == 2, "");
    VERIFY(array(6, 9) == 3, "");
    VERIFY(array(7, 9).isNull(), "");

    VERIFY(array(3, 10).isNull(), "");
    VERIFY(array(4, 10).isNull(), "");
    VERIFY(array(5, 10).isNull(), "");
    VERIFY(array(6, 10).isNull(), "");

    array(4, 7) = 5;
    array(5, 7) = 6;

    VERIFY(array(4, 7) == 5, "");
    VERIFY(array(5, 7) == 6, "");

    array.Clear();

    array.SetBox(Box(3, 6, 7, 9, 15, 16));

    VERIFY(array.CalculateIndex(5, 8, 16) == 18, "");

    for(int i = 0; i < array.Box().Nx() * array.Box().Ny(); i++) array.Add(i);

    array.AddInterval(array.Box().Nx() * array.Box().Ny(), 12);

    VERIFY(array(3, 7, 14).isNull(), "");
    VERIFY(array(3, 7, 17).isNull(), "");
    VERIFY(array(6, 9, 14).isNull(), "");
    VERIFY(array(6, 9, 17).isNull(), "");

    VERIFY(array(3, 7, 15) == 0, "");
    VERIFY(array(6, 9, 15) == 11, "");

    VERIFY(array(3, 7, 16) == 12, "");
    VERIFY(array(6, 9, 16) == 12, "");
}

}}}}
