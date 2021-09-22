#include "box.h"

namespace BlackOil {
namespace Data {
namespace Grid {

Box::Box()
{
    InitVariables();
}

Box::Box(int i1, int i2, int j1, int j2, int k1, int k2)
{
    this->i1 = i1;
    this->i2 = i2;

    this->j1 = j1;
    this->j2 = j2;

    this->k1 = k1;
    this->k2 = k2;
}

int Box::I1()
{
    return i1;
}

int Box::I2()
{
    return i2;
}

int Box::J1()
{
    return j1;
}

int Box::J2()
{
    return j2;
}

int Box::K1()
{
    return k1;
}

int Box::K2()
{
    return k2;
}

int Box::Nx()
{
    return i1 >= 0 && i2 >= i1 ? i2 - i1 + 1 : 0;
}

int Box::Ny()
{
    return j1 >= 0 && j2 >= j1 ? j2 - j1 + 1 : 0;
}

int Box::Nz()
{
    return k1 >= 0 && k2 >= k1 ? k2 - k1 + 1 : 0;
}

int Box::N()
{
    return Nx() * Ny() * Nz();
}

int Box::LocalToGlobalIndex(int index, int nx, int ny)
{
    int k = index / (Nx() * Ny());

    index -= k * Nx() * Ny();

    int j = index / Nx();
    int i = index % Nx();

    i += i1;
    j += j1;
    k += k1;

    return k * nx * ny + j * nx + i;
}

bool Box::Contains(int i, int j, int k)
{
    if(i >= this->i1 && i <= this->i2 && j >= this->j1 && j <= this->j2 && k >= this->k1 && k <= this->k2)
        return true;

    return false;
}

bool Box::BelongsX(int i1, int i2)
{
    return i2 >= i1 && i1 >= this->i1 && i2 <= this->i2;
}

bool Box::BelongsY(int j1, int j2)
{
    return j2 >= j1 && j1 >= this->j1 && j2 <= this->j2;
}

bool Box::BelongsZ(int k1, int k2)
{
    return k2 >= k1 && k1 >= this->k1 && k2 <= this->k2;
}

bool Box::Belongs(const Box &box)
{
    return BelongsX(box.i1, box.i2) && BelongsY(box.j1, box.j2) && BelongsZ(box.k1, box.k2);
}

void Box::InitVariables()
{
    i1 = -1;
    i2 = -1;

    j1 = -1;
    j2 = -1;

    k1 = -1;
    k2 = -1;
}

}}}
