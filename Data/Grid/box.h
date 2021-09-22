#ifndef BOX_H
#define BOX_H

#include <data_global.h>

namespace BlackOil {
namespace Data {
namespace Grid {

class DATA_EXPORT Box
{
public:
    Box();
    Box(int i1, int i2, int j1, int j2, int k1, int k2);

    int I1();
    int I2();

    int J1();
    int J2();

    int K1();
    int K2();

    int Nx();
    int Ny();
    int Nz();

    int N();

    int LocalToGlobalIndex(int index, int nx, int ny);

    bool Contains(int i, int j, int k);

    bool BelongsX(int i1, int i2);
    bool BelongsY(int j1, int j2);
    bool BelongsZ(int k1, int k2);

    bool Belongs(const Box& box);

    void InitVariables();

protected:
    int i1, i2;
    int j1, j2;
    int k1, k2;
};

}}}

#endif // BOX_H
