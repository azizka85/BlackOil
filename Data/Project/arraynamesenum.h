#ifndef ARRAYNAMESENUM_H
#define ARRAYNAMESENUM_H

#include <qobject.h>

#include <data_global.h>

namespace BlackOil {
namespace Data {
namespace Project {

class DATA_EXPORT ArrayNamesEnum : public QObject
{
    Q_OBJECT
    Q_ENUMS(ArrayNames)
public:
    explicit ArrayNamesEnum(QObject *parent = nullptr);

    enum ArrayNames { TOPS, DX, DY, DZ, DXV, DYV, DZV, COORD, ZCORN, ACTNUM, MULTPV, PERMX, PERMY, PERMZ, PORO, NTG, DZNET, MULTX, MULTY, MULTZ, MULTXm, MULTYm, MULTZm, MINPVV,
                        SWATINIT, SWCR, ISWCR, SWL, ISWL, SWLPC, ISWLPC, SWU, ISWU, SGCR, ISGCR, SGL, ISGL, SGLPC, ISGLPC, PCG, IPCG, PCW, IPCW,
                        KRO, IKRO, KRORW, IKRORW, KRORG, IKRORG, KRW, IKRW, KRWR, IKRWR, KRG, IKRG, KRGR, IKRGR,
                        PVTNUM, SATNUM, EQLNUM, ENDNUM,
                        PRESSURE, SWAT, SOIL, SGAS, PBUB, RS,
                        DEPTH, PORV, TRANX, TRANY, TRANZ };
};

}}}

#endif // ARRAYNAMESENUM_H
