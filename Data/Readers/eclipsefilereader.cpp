#include "eclipsefilereader.h"

namespace BlackOil {
namespace Data {
namespace Readers {

EclipseFileReader::EclipseFileReader()
{
    InitVariables();
}

void EclipseFileReader::Load(ProjectData &data, const QString &filePath)
{
    QMetaObject casesMetaObject = CasesEnum::staticMetaObject;

    QMetaEnum casesEnum = casesMetaObject.enumerator(casesMetaObject.indexOfEnumerator("Cases"));

    ReadFile(data, filePath, casesEnum);
}

void EclipseFileReader::InitVariables()
{
    box = Box();
    currentDate = QDateTime::currentDateTime();
}

void EclipseFileReader::ReadFile(ProjectData &data, const QString &filePath, QMetaEnum &casesEnum)
{
    QString currentDir = QFileInfo(filePath).dir().path();

    QFile file(filePath);

    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)) return;

    QTextStream sr(&file);

    while (true)
    {
        QString line = ReadFileHelper::GetNextLine(sr);
        if (line == nullptr) break;

        QString keyword = ReadFileHelper::ParseKeyword(line);

        keyword = keyword.replace('-', 'm')
                            .replace('+', 'p');

        int index = casesEnum.keyToValue(keyword.toLatin1());

        switch (index)
        {
            // RUNSPEC
            case CasesEnum::RUNSPEC: break;
            case CasesEnum::TITLE: ReadTITLE(data, sr); break;
            case CasesEnum::START: ReadSTART(data, sr); break;
            case CasesEnum::METRIC: data.SetUnit(UnitsEnum::METRIC); break;
            case CasesEnum::FIELD: data.SetUnit(UnitsEnum::FIELD); break;
            case CasesEnum::LAB: data.SetUnit(UnitsEnum::LAB); break;
            case CasesEnum::PVTmM: data.SetUnit(UnitsEnum::LAB); break;
            case CasesEnum::UNIFOUT: break;
            case CasesEnum::OIL: break;
            case CasesEnum::WATER: break;
            case CasesEnum::GAS: data.SetModel(ModelsEnum::ThreePhase); break;
            case CasesEnum::DISGAS: break;
            case CasesEnum::TEMP: data.SetTemperatureOption(true); break;
            case CasesEnum::NOECHO: break;
            case CasesEnum::IMPLICIT: break;
            case CasesEnum::FULLIMP: break;
            case CasesEnum::IMPES: break;
            case CasesEnum::NUMRES: ReadNUMRES(data, sr); break;
            case CasesEnum::DIMENS: ReadDIMENS(data, sr); break;
            case CasesEnum::REGDIMS: ReadFileHelper::IgnoreParams(sr); break;
            case CasesEnum::TABDIMS: ReadTABDIMS(data, sr); break;
            case CasesEnum::EQLDIMS: ReadEQLDIMS(data, sr); break;
            case CasesEnum::WELLDIMS: ReadFileHelper::IgnoreParams(sr); break;
            case CasesEnum::ENDSCALE: ReadENDSCALE(data, sr); break;
            case CasesEnum::BLACKOIL: break;
            case CasesEnum::DEADOIL: break;

            // GRID
            case CasesEnum::GRID: break;
            case CasesEnum::INIT: break;
            case CasesEnum::GRIDFILE: ReadFileHelper::IgnoreParams(sr); break;
            case CasesEnum::TOPS: ReadFileHelper::ReadArray(sr, box, data.Arrays()[ArrayNamesEnum::TOPS], DataTypeEnum::DOUBLE); break;
            case CasesEnum::DX: ReadFileHelper::ReadArray(sr, box, data.Arrays()[ArrayNamesEnum::DX], DataTypeEnum::DOUBLE); break;
            case CasesEnum::DY: ReadFileHelper::ReadArray(sr, box, data.Arrays()[ArrayNamesEnum::DY], DataTypeEnum::DOUBLE); break;
            case CasesEnum::DZ: ReadFileHelper::ReadArray(sr, box, data.Arrays()[ArrayNamesEnum::DZ], DataTypeEnum::DOUBLE); break;
            case CasesEnum::DXV: ReadFileHelper::ReadArray(sr, Box(0, data.Nx() - 1, 0, 0, 0, 0), data.Arrays()[ArrayNamesEnum::DXV], DataTypeEnum::DOUBLE); break;
            case CasesEnum::DYV: ReadFileHelper::ReadArray(sr, Box(0, data.Ny() - 1, 0, 0, 0, 0), data.Arrays()[ArrayNamesEnum::DYV], DataTypeEnum::DOUBLE); break;
            case CasesEnum::DZV: ReadFileHelper::ReadArray(sr, Box(0, data.Nz() - 1, 0, 0, 0, 0), data.Arrays()[ArrayNamesEnum::DZV], DataTypeEnum::DOUBLE); break;
            case CasesEnum::COORD: ReadFileHelper::ReadArray(sr, Box(0, 6*(data.Nx()+1)*(data.Ny()+1) - 1, 0, 0, 0, 0), data.Arrays()[ArrayNamesEnum::COORD], DataTypeEnum::DOUBLE); break;
            case CasesEnum::ZCORN: ReadFileHelper::ReadArray(sr, Box(0, 8*data.Nx()*data.Ny()*data.Nz() - 1, 0, 0, 0, 0), data.Arrays()[ArrayNamesEnum::ZCORN], DataTypeEnum::DOUBLE); break;
            case CasesEnum::ACTNUM: ReadFileHelper::ReadArray(sr, box, data.Arrays()[ArrayNamesEnum::ACTNUM], DataTypeEnum::INTEGER); break;
            case CasesEnum::MULTPV: ReadFileHelper::ReadArray(sr, box, data.Arrays()[ArrayNamesEnum::MULTPV], DataTypeEnum::DOUBLE); break;
            case CasesEnum::PERMX: ReadFileHelper::ReadArray(sr, box, data.Arrays()[ArrayNamesEnum::PERMX], DataTypeEnum::DOUBLE); break;
            case CasesEnum::PERMY: ReadFileHelper::ReadArray(sr, box, data.Arrays()[ArrayNamesEnum::PERMY], DataTypeEnum::DOUBLE); break;
            case CasesEnum::PERMZ: ReadFileHelper::ReadArray(sr, box, data.Arrays()[ArrayNamesEnum::PERMZ], DataTypeEnum::DOUBLE); break;
            case CasesEnum::PORO: ReadFileHelper::ReadArray(sr, box, data.Arrays()[ArrayNamesEnum::PORO], DataTypeEnum::DOUBLE); break;
            case CasesEnum::NTG: ReadFileHelper::ReadArray(sr, box, data.Arrays()[ArrayNamesEnum::NTG], DataTypeEnum::DOUBLE); break;
            case CasesEnum::DZNET: ReadFileHelper::ReadArray(sr, box, data.Arrays()[ArrayNamesEnum::DZNET], DataTypeEnum::DOUBLE); break;
            case CasesEnum::MULTX: ReadFileHelper::ReadArray(sr, box, data.Arrays()[ArrayNamesEnum::MULTX], DataTypeEnum::DOUBLE); break;
            case CasesEnum::MULTY: ReadFileHelper::ReadArray(sr, box, data.Arrays()[ArrayNamesEnum::MULTY], DataTypeEnum::DOUBLE); break;
            case CasesEnum::MULTZ: ReadFileHelper::ReadArray(sr, box, data.Arrays()[ArrayNamesEnum::MULTZ], DataTypeEnum::DOUBLE); break;
            case CasesEnum::MULTXm: ReadFileHelper::ReadArray(sr, box, data.Arrays()[ArrayNamesEnum::MULTXm], DataTypeEnum::DOUBLE); break;
            case CasesEnum::MULTYm: ReadFileHelper::ReadArray(sr, box, data.Arrays()[ArrayNamesEnum::MULTYm], DataTypeEnum::DOUBLE); break;
            case CasesEnum::MULTZm: ReadFileHelper::ReadArray(sr, box, data.Arrays()[ArrayNamesEnum::MULTZm], DataTypeEnum::DOUBLE); break;
            case CasesEnum::MINPVV: ReadFileHelper::ReadArray(sr, box, data.Arrays()[ArrayNamesEnum::MINPVV], DataTypeEnum::DOUBLE); break;
            case CasesEnum::MINPV: ReadMINPV(data, sr); break;

            // PROPS
            case CasesEnum::PROPS: break;
            case CasesEnum::STONE: break; // STONE2
            case CasesEnum::STONE1: break; // STONE1
            case CasesEnum::STONE2: break; // STONE2
            case CasesEnum::RSCONST: ReadRSCONST(data, sr); break;
            case CasesEnum::RSCONSTT: ReadRSCONSTT(data, sr); break;
            case CasesEnum::PVTO: ReadPVTO(data, sr); break;
            case CasesEnum::PVCO: ReadPVCO(data, sr); break;
            case CasesEnum::PMAX: ReadPMAX(data, sr); break;
            case CasesEnum::PVCDO: ReadPVCDO(data, sr); break;
            case CasesEnum::PVDO: ReadPVDO(data, sr); break;
            case CasesEnum::PVTW: ReadPVTW(data, sr); break;
            case CasesEnum::PVDG: ReadPVDG(data, sr); break;
            case CasesEnum::PVTG: ReadPVTG(data, sr); break;
            case CasesEnum::ROCKOPTS: ReadROCKOPTS(data, sr); break;
            case CasesEnum::ROCK: ReadROCK(data, sr); break;
            case CasesEnum::DENSITY: ReadDENSITY(data, sr); break;
            case CasesEnum::GRAVITY: ReadGRAVITY(data, sr); break;
            case CasesEnum::SWOF: ReadSWOF(data, sr); break;
            case CasesEnum::SGOF: ReadSGOF(data, sr); break;
            case CasesEnum::SGWFN: ReadSGWFN(data, sr); break;
            case CasesEnum::SLGOF: ReadSLGOF(data, sr); break;
            case CasesEnum::SOF2: ReadSOF2(data, sr); break;
            case CasesEnum::SOF3: ReadSOF3(data, sr); break;
            case CasesEnum::SOF32D: ReadSOF32D(data, sr); break;
            case CasesEnum::SWFN: ReadSWFN(data, sr); break;
            case CasesEnum::SGFN: ReadSGFN(data, sr); break;
            case CasesEnum::SOMGAS: ReadSOMGAS(data, sr); break;
            case CasesEnum::SOMWAT: ReadSOMWAT(data, sr); break;
            case CasesEnum::SWATINIT: ReadFileHelper::ReadArray(sr, box, data.Arrays()[ArrayNamesEnum::SWATINIT], DataTypeEnum::DOUBLE); break;
            case CasesEnum::SWCR: ReadFileHelper::ReadArray(sr, box, data.Arrays()[ArrayNamesEnum::SWCR], DataTypeEnum::DOUBLE); break;
            case CasesEnum::ISWCR: ReadFileHelper::ReadArray(sr, box, data.Arrays()[ArrayNamesEnum::ISWCR], DataTypeEnum::DOUBLE); break;
            case CasesEnum::SWL: ReadFileHelper::ReadArray(sr, box, data.Arrays()[ArrayNamesEnum::SWL], DataTypeEnum::DOUBLE); break;
            case CasesEnum::ISWL: ReadFileHelper::ReadArray(sr, box, data.Arrays()[ArrayNamesEnum::ISWL], DataTypeEnum::DOUBLE); break;
            case CasesEnum::SWLPC: ReadFileHelper::ReadArray(sr, box, data.Arrays()[ArrayNamesEnum::SWLPC], DataTypeEnum::DOUBLE); break;
            case CasesEnum::ISWLPC: ReadFileHelper::ReadArray(sr, box, data.Arrays()[ArrayNamesEnum::ISWLPC], DataTypeEnum::DOUBLE); break;
            case CasesEnum::SWU: ReadFileHelper::ReadArray(sr, box, data.Arrays()[ArrayNamesEnum::SWU], DataTypeEnum::DOUBLE); break;
            case CasesEnum::ISWU: ReadFileHelper::ReadArray(sr, box, data.Arrays()[ArrayNamesEnum::ISWU], DataTypeEnum::DOUBLE); break;
            case CasesEnum::SGCR: ReadFileHelper::ReadArray(sr, box, data.Arrays()[ArrayNamesEnum::SGCR], DataTypeEnum::DOUBLE); break;
            case CasesEnum::ISGCR: ReadFileHelper::ReadArray(sr, box, data.Arrays()[ArrayNamesEnum::ISGCR], DataTypeEnum::DOUBLE); break;
            case CasesEnum::SGL: ReadFileHelper::ReadArray(sr, box, data.Arrays()[ArrayNamesEnum::SGL], DataTypeEnum::DOUBLE); break;
            case CasesEnum::ISGL: ReadFileHelper::ReadArray(sr, box, data.Arrays()[ArrayNamesEnum::ISGL], DataTypeEnum::DOUBLE); break;
            case CasesEnum::SGLPC: ReadFileHelper::ReadArray(sr, box, data.Arrays()[ArrayNamesEnum::SGLPC], DataTypeEnum::DOUBLE); break;
            case CasesEnum::ISGLPC: ReadFileHelper::ReadArray(sr, box, data.Arrays()[ArrayNamesEnum::ISGLPC], DataTypeEnum::DOUBLE); break;
            case CasesEnum::PCG: ReadFileHelper::ReadArray(sr, box, data.Arrays()[ArrayNamesEnum::PCG], DataTypeEnum::DOUBLE); break;
            case CasesEnum::IPCG: ReadFileHelper::ReadArray(sr, box, data.Arrays()[ArrayNamesEnum::IPCG], DataTypeEnum::DOUBLE); break;
            case CasesEnum::PCW: ReadFileHelper::ReadArray(sr, box, data.Arrays()[ArrayNamesEnum::PCW], DataTypeEnum::DOUBLE); break;
            case CasesEnum::IPCW: ReadFileHelper::ReadArray(sr, box, data.Arrays()[ArrayNamesEnum::IPCW], DataTypeEnum::DOUBLE); break;
            case CasesEnum::PPCWMAX: ReadPPCWMAX(data, sr); break;
            case CasesEnum::KRO: ReadFileHelper::ReadArray(sr, box, data.Arrays()[ArrayNamesEnum::KRO], DataTypeEnum::DOUBLE); break;
            case CasesEnum::IKRO: ReadFileHelper::ReadArray(sr, box, data.Arrays()[ArrayNamesEnum::IKRO], DataTypeEnum::DOUBLE); break;
            case CasesEnum::KRORW: ReadFileHelper::ReadArray(sr, box, data.Arrays()[ArrayNamesEnum::KRORW], DataTypeEnum::DOUBLE); break;
            case CasesEnum::IKRORW: ReadFileHelper::ReadArray(sr, box, data.Arrays()[ArrayNamesEnum::IKRORW], DataTypeEnum::DOUBLE); break;
            case CasesEnum::KRORG: ReadFileHelper::ReadArray(sr, box, data.Arrays()[ArrayNamesEnum::KRORG], DataTypeEnum::DOUBLE); break;
            case CasesEnum::IKRORG: ReadFileHelper::ReadArray(sr, box, data.Arrays()[ArrayNamesEnum::IKRORG], DataTypeEnum::DOUBLE); break;
            case CasesEnum::KRW: ReadFileHelper::ReadArray(sr, box, data.Arrays()[ArrayNamesEnum::KRW], DataTypeEnum::DOUBLE); break;
            case CasesEnum::IKRW: ReadFileHelper::ReadArray(sr, box, data.Arrays()[ArrayNamesEnum::IKRW], DataTypeEnum::DOUBLE); break;
            case CasesEnum::KRWR: ReadFileHelper::ReadArray(sr, box, data.Arrays()[ArrayNamesEnum::KRWR], DataTypeEnum::DOUBLE); break;
            case CasesEnum::IKRWR: ReadFileHelper::ReadArray(sr, box, data.Arrays()[ArrayNamesEnum::IKRWR], DataTypeEnum::DOUBLE); break;
            case CasesEnum::KRG: ReadFileHelper::ReadArray(sr, box, data.Arrays()[ArrayNamesEnum::KRG], DataTypeEnum::DOUBLE); break;
            case CasesEnum::IKRG: ReadFileHelper::ReadArray(sr, box, data.Arrays()[ArrayNamesEnum::IKRG], DataTypeEnum::DOUBLE); break;
            case CasesEnum::KRGR: ReadFileHelper::ReadArray(sr, box, data.Arrays()[ArrayNamesEnum::KRGR], DataTypeEnum::DOUBLE); break;
            case CasesEnum::IKRGR: ReadFileHelper::ReadArray(sr, box, data.Arrays()[ArrayNamesEnum::IKRGR], DataTypeEnum::DOUBLE); break;
            case CasesEnum::ENKRVD: ReadENKRVD(data, sr); break;
            case CasesEnum::ENPCVD: ReadENPCVD(data, sr); break;
            case CasesEnum::ENSPCVD: ReadENSPCVD(data, sr); break;
            case CasesEnum::SCALELIM: ReadSCALELIM(data, sr); break;
            case CasesEnum::SCALECRS: ReadSCALECRS(data, sr); break;
            case CasesEnum::SPECHEAT: ReadSPECHEAT(data, sr); break;
            case CasesEnum::SPECROCK: ReadSPECROCK(data, sr); break;
            case CasesEnum::VISCREF: ReadVISCREF(data, sr); break;
            case CasesEnum::OILVISCT: ReadOILVISCT(data, sr); break;
            case CasesEnum::WATVISCT: ReadWATVISCT(data, sr); break;

            // REGIONS
            case CasesEnum::REGIONS: break;
            case CasesEnum::PVTNUM: ReadFileHelper::ReadArray(sr, box, data.Arrays()[ArrayNamesEnum::PVTNUM], DataTypeEnum::INTEGER); break;
            case CasesEnum::SATNUM: ReadFileHelper::ReadArray(sr, box, data.Arrays()[ArrayNamesEnum::SATNUM], DataTypeEnum::INTEGER); break;
            case CasesEnum::EQLNUM: ReadFileHelper::ReadArray(sr, box, data.Arrays()[ArrayNamesEnum::EQLNUM], DataTypeEnum::INTEGER); break;
            case CasesEnum::ENDNUM: ReadFileHelper::ReadArray(sr, box, data.Arrays()[ArrayNamesEnum::ENDNUM], DataTypeEnum::INTEGER); break;
            case CasesEnum::FIPNUM: ReadFileHelper::IgnoreParams(sr); break;

            // SOLUTION
            case CasesEnum::SOLUTION: break;
            case CasesEnum::EQUIL: ReadEQUIL(data, sr); break;
            case CasesEnum::RSVD: ReadRSVD(data, sr); break;
            case CasesEnum::PBVD: ReadPBVD(data, sr); break;
            case CasesEnum::PRVD: ReadPRVD(data, sr); break;
            case CasesEnum::PRESSURE: ReadFileHelper::ReadArray(sr, box, data.Arrays()[ArrayNamesEnum::PRESSURE], DataTypeEnum::DOUBLE); break;
            case CasesEnum::SWAT: ReadFileHelper::ReadArray(sr, box, data.Arrays()[ArrayNamesEnum::SWAT], DataTypeEnum::DOUBLE); break;
            case CasesEnum::SOIL: ReadFileHelper::ReadArray(sr, box, data.Arrays()[ArrayNamesEnum::SOIL], DataTypeEnum::DOUBLE); break;
            case CasesEnum::SGAS: ReadFileHelper::ReadArray(sr, box, data.Arrays()[ArrayNamesEnum::SGAS], DataTypeEnum::DOUBLE); break;
            case CasesEnum::PBUB: ReadFileHelper::ReadArray(sr, box, data.Arrays()[ArrayNamesEnum::PBUB], DataTypeEnum::DOUBLE); break;
            case CasesEnum::RS: ReadFileHelper::ReadArray(sr, box, data.Arrays()[ArrayNamesEnum::RS], DataTypeEnum::DOUBLE); break;
            case CasesEnum::AQUANCON: ReadAQUANCON(data, sr); break;
            case CasesEnum::AQUFETP: ReadAQUFETP(data, sr); break;

            // SUMMARY
            case CasesEnum::SUMMARY: break;
            case CasesEnum::ALL: break;
            case CasesEnum::RUNSUM: break;
            case CasesEnum::RPTONLY: break;

            // SCHEDULE
            case CasesEnum::SCHEDULE: break;
            case CasesEnum::DIMPLICT: break;
            case CasesEnum::DIMPES: ReadDIMPES(data, sr); break;
            case CasesEnum::RPTRST: ReadFileHelper::IgnoreParams(sr); break;
            case CasesEnum::RPTSCHED: ReadFileHelper::IgnoreParams(sr); break;
            case CasesEnum::WELSPECS: ReadWELSPECS(data, sr); break;
            case CasesEnum::COMPDAT: ReadCOMPDAT(data, sr); break;
            case CasesEnum::WCONPROD: ReadWCONPROD(data, sr); break;
            case CasesEnum::WCONINJE: ReadWCONINJE(data, sr); break;
            case CasesEnum::DATES: ReadDATES(data, sr); break;
            case CasesEnum::TSTEP: ReadTSTEP(data, sr); break;
            case CasesEnum::WCONHIST: ReadWCONHIST(data, sr); break;
            case CasesEnum::WCONINJH: ReadWCONINJH(data, sr); break;
            case CasesEnum::WELTARG: ReadWELTARG(data, sr); break;

            // ANY SECTION
            case CasesEnum::INCLUDE: ReadINCLUDE(data, sr, currentDir, casesEnum); break;
            case CasesEnum::EQUALS: ReadEQUALS(data, sr); break;
            case CasesEnum::BOX: ReadBOX(sr); break;
            case CasesEnum::ENDBOX: ReadENDBOX(data); break;
            case CasesEnum::COPY: ReadCOPY(data, sr); break;
            case CasesEnum::ADD: ReadADD(data, sr); break;
            case CasesEnum::MULTIPLY: ReadMULTIPLY(data, sr); break;
            case CasesEnum::EDIT: break;
            case CasesEnum::DEPTH: ReadFileHelper::ReadArray(sr, box, data.Arrays()[ArrayNamesEnum::DEPTH], DataTypeEnum::DOUBLE); break;
            case CasesEnum::PORV: ReadFileHelper::ReadArray(sr, box, data.Arrays()[ArrayNamesEnum::PORV], DataTypeEnum::DOUBLE); break;
            case CasesEnum::TRANX: ReadFileHelper::ReadArray(sr, box, data.Arrays()[ArrayNamesEnum::TRANX], DataTypeEnum::DOUBLE); break;
            case CasesEnum::TRANY: ReadFileHelper::ReadArray(sr, box, data.Arrays()[ArrayNamesEnum::TRANY], DataTypeEnum::DOUBLE); break;
            case CasesEnum::TRANZ: ReadFileHelper::ReadArray(sr, box, data.Arrays()[ArrayNamesEnum::TRANZ], DataTypeEnum::DOUBLE); break;
            case CasesEnum::END: break;

            /// TODO: Need to write logs instead console
            default: qDebug() << QString("%1: !!!unknown line: %2").arg(index).arg(keyword); break;
        }
    }

    file.close();
}

// RUNSPEC
void EclipseFileReader::ReadTITLE(ProjectData &data, QTextStream &sr)
{
    data.SetTitle(ReadFileHelper::GetNextLine(sr));
}

void EclipseFileReader::ReadSTART(ProjectData &data, QTextStream &sr)
{
    QMetaObject metaObject = MonthsEnum::staticMetaObject;

    QMetaEnum monthsEnum = metaObject.enumerator(metaObject.indexOfEnumerator("Months"));

    QStringList str = ReadFileHelper::ParseParams(sr);

    QString dateStr = ReadFileHelper::EclipseDateToStr(str, monthsEnum);

    QDateTime date = ReadFileHelper::StrToDate(dateStr);

    data.SetStartDate(date);

    data.DATES().push_back(date);

    currentDate = date;
}

void EclipseFileReader::ReadNUMRES(ProjectData &data, QTextStream &sr)
{
    QStringList str = ReadFileHelper::ParseParams(sr);

    if(str.length() > 0 && str[0] == "1*") data.SetNumRES(str[0].toInt());
}

void EclipseFileReader::ReadDIMENS(ProjectData &data, QTextStream &sr)
{
    QStringList str = ReadFileHelper::ParseParams(sr);

    int nx = str[0].toInt();
    int ny = str[1].toInt();
    int nz = str[2].toInt();

    data.SetNx(nx);
    data.SetNy(ny);
    data.SetNz(nz);

    box = Box(0, nx-1, 0, ny-1, 0, nz-1);
}

void EclipseFileReader::ReadTABDIMS(ProjectData &data, QTextStream &sr)
{
    QStringList str = ReadFileHelper::ParseParams(sr);

    if (str.length() > 0 && str[0] != "1*") data.TABDIMS().SetNTSFUN(str[0].toInt());
    if (str.length() > 1 && str[1] != "1*") data.TABDIMS().SetNTPVT(str[1].toInt());
    if (str.length() > 2 && str[2] != "1*") data.TABDIMS().SetNSSFUN(str[2].toInt());
}

void EclipseFileReader::ReadEQLDIMS(ProjectData &data, QTextStream &sr)
{
    QStringList str = ReadFileHelper::ParseParams(sr);

    if (str.length() > 0 && str[0] != "1*") data.EQLDIMS().SetNTEQUL(str[0].toInt());
}

void EclipseFileReader::ReadENDSCALE(ProjectData &data, QTextStream &sr)
{
    QMetaObject directionalMetaObject = DirectionalEnum::staticMetaObject;
    QMetaObject irreversibleMetaObject = IrreversibleEnum::staticMetaObject;

    QMetaEnum directionalTypes = directionalMetaObject.enumerator(directionalMetaObject.indexOfEnumerator("Directional"));
    QMetaEnum irreversibleTypes = irreversibleMetaObject.enumerator(irreversibleMetaObject.indexOfEnumerator("Irreversible"));

    QStringList str = ReadFileHelper::GetNextLineWords(sr);

    if (str.length() > 1 && str[0] != "1*")
    {
        int directionalType = directionalTypes.keyToValue(str[0].toLatin1());

        data.ENDSCALE().SetDirectional(directionalType);
    }

    if (str.length() > 2 && str[1] != "1*")
    {
        int irreversibleType = irreversibleTypes.keyToValue(str[1].toLatin1());

        data.ENDSCALE().SetIrreversible(irreversibleType);
    }

    if (str.length() > 3 && str[2] != "1*") data.ENDSCALE().SetNTENDP(str[2].toInt());

    if (str.length() > 4 && str[3] != "1*") data.ENDSCALE().SetMaxNodesEPD(str[3].toInt());
}

// GRID
void EclipseFileReader::ReadMINPV(ProjectData &data, QTextStream &sr)
{
    QStringList str = ReadFileHelper::ParseParams(sr);

    data.SetMINPV(str[0].toDouble());
}

// PROPS
void EclipseFileReader::ReadRSCONST(ProjectData &data, QTextStream &sr)
{
    QStringList str = ReadFileHelper::ParseParams(sr);

    data.RSCONST().SetRS(str[0].toDouble());
    data.RSCONST().SetPBub(str[1].toDouble());
}

void EclipseFileReader::ReadRSCONSTT(ProjectData &data, QTextStream &sr)
{
    int ntPVT = data.TABDIMS().NTPVT().isNull() ? DefaultValues::TABDIMS_NTPVT : data.TABDIMS().NTPVT().toInt();

    data.RSCONSTT().resize(ntPVT);

    for (int reg = 0; reg < ntPVT; reg++)
    {
        QStringList str = ReadFileHelper::ParseParams(sr);

        RSCONSTData rsCONST;

        rsCONST.SetRS(str[0].toDouble());
        rsCONST.SetPBub(str[1].toDouble());

        data.RSCONSTT()[reg] = rsCONST;
    }
}

void EclipseFileReader::ReadPVTO(ProjectData &data, QTextStream &sr)
{
    int ntPVT = data.TABDIMS().NTPVT().isNull() ? DefaultValues::TABDIMS_NTPVT : data.TABDIMS().NTPVT().toInt();

    data.PVTO().resize(ntPVT);

    for (int reg = 0; reg < ntPVT; reg++)
    {
        while (true)
        {
            QStringList str = ReadFileHelper::ParseParams(sr);

            if (str.length() == 0) break;

            double rs = str[0].toDouble();

            for (int i = 0; i < (str.length() - 1) / 3; i++)
            {
                PVTOData pvto;

                pvto.SetRS(rs);

                pvto.SetPO(str[1 + 3 * i].toDouble());
                pvto.SetBO(str[2 + 3 * i].toDouble());
                pvto.SetMO(str[3 + 3 * i].toDouble());

                data.PVTO()[reg].push_back(pvto);
            }
        }
    }
}

void EclipseFileReader::ReadPVCO(ProjectData &data, QTextStream &sr)
{
    int ntPVT = data.TABDIMS().NTPVT().isNull() ? DefaultValues::TABDIMS_NTPVT : data.TABDIMS().NTPVT().toInt();

    data.PVCO().resize(ntPVT);

    for (int reg = 0; reg < ntPVT; reg++)
    {
        QStringList str = ReadFileHelper::ParseParams(sr);

        for (int i = 0; i < str.length() / 6; i++)
        {
            PVCOData pvco;

            pvco.SetPO(str[0 + 6 * i].toDouble());

            if (str[1 + 6 * i] != "1*") pvco.SetRS(str[1 + 6 * i].toDouble());
            if (str[2 + 6 * i] != "1*") pvco.SetBO(str[2 + 6 * i].toDouble());
            if (str[3 + 6 * i] != "1*") pvco.SetMO(str[3 + 6 * i].toDouble());
            if (str[4 + 6 * i] != "1*") pvco.SetCO(str[4 + 6 * i].toDouble());
            if (str[5 + 6 * i] != "1*") pvco.SetCVO(str[5 + 6 * i].toDouble());

            data.PVCO()[reg].push_back(pvco);
        }
    }
}

void EclipseFileReader::ReadPMAX(ProjectData &data, QTextStream &sr)
{
    QStringList str = ReadFileHelper::ParseParams(sr);

    if (str.length() > 0 && str[0] != "1*") data.PMAX().SetPMax(str[0].toDouble());

    if (str.length() > 1 && str[1] != "1*") data.PMAX().SetPMaxComp(str[1].toDouble());
    if (str.length() > 2 && str[2] != "1*") data.PMAX().SetPMinComp(str[2].toDouble());

    if (str.length() > 3 && str[3] != "1*") data.PMAX().SetNumNodes(str[3].toInt());
}

void EclipseFileReader::ReadPVCDO(ProjectData &data, QTextStream &sr)
{
    int ntPVT = data.TABDIMS().NTPVT().isNull() ? DefaultValues::TABDIMS_NTPVT : data.TABDIMS().NTPVT().toInt();

    data.PVCDO().resize(ntPVT);

    for (int reg = 0; reg < ntPVT; reg++)
    {
        QStringList str = ReadFileHelper::ParseParams(sr);

        PVCDOData pvcdo;

        pvcdo.SetPORef(str[0].toDouble());
        pvcdo.SetBORef(str[1].toDouble());
        pvcdo.SetCO(str[2].toDouble());
        pvcdo.SetMORef(str[3].toDouble());
        pvcdo.SetCVO(str[4].toDouble());

        data.PVCDO()[reg] = pvcdo;
    }
}

void EclipseFileReader::ReadPVDO(ProjectData &data, QTextStream &sr)
{
    int ntPVT = data.TABDIMS().NTPVT().isNull() ? DefaultValues::TABDIMS_NTPVT : data.TABDIMS().NTPVT().toInt();

    data.PVDO().resize(ntPVT);

    for (int reg = 0; reg < ntPVT; reg++)
    {
        QStringList str = ReadFileHelper::ParseParams(sr);

        for (int i = 0; i < str.length() / 3; i++)
        {
            PVDOData pvdo;

            pvdo.SetPO(str[0 + 3*i].toDouble());
            pvdo.SetBO(str[1 + 3*i].toDouble());
            pvdo.SetMO(str[2 + 3*i].toDouble());

            data.PVDO()[reg].push_back(pvdo);
        }
    }
}

void EclipseFileReader::ReadPVTW(ProjectData &data, QTextStream &sr)
{
    int ntPVT = data.TABDIMS().NTPVT().isNull() ? DefaultValues::TABDIMS_NTPVT : data.TABDIMS().NTPVT().toInt();

    data.PVTW().resize(ntPVT);

    for (int reg = 0; reg < ntPVT; reg++)
    {
        QStringList str = ReadFileHelper::ParseParams(sr);

        PVTWData pvtw;

        if (str.length() > 0 && str[0] != "1*") pvtw.SetPWRef(str[0].toDouble());
        if (str.length() > 1 && str[1] != "1*") pvtw.SetBWRef(str[1].toDouble());
        if (str.length() > 2 && str[2] != "1*") pvtw.SetCW(str[2].toDouble());
        if (str.length() > 3 && str[3] != "1*") pvtw.SetMWRef(str[3].toDouble());
        if (str.length() > 4 && str[4] != "1*") pvtw.SetCVW(str[4].toDouble());

        data.PVTW()[reg] = pvtw;
    }
}

void EclipseFileReader::ReadPVDG(ProjectData &data, QTextStream &sr)
{
    int ntPVT = data.TABDIMS().NTPVT().isNull() ? DefaultValues::TABDIMS_NTPVT : data.TABDIMS().NTPVT().toInt();

    data.PVDG().resize(ntPVT);

    for (int reg = 0; reg < ntPVT; reg++)
    {
        QStringList str = ReadFileHelper::ParseParams(sr);

        for (int i = 0; i < str.length() / 3; i++)
        {
            PVDGData pvdg;

            pvdg.SetPG(str[0 + i * 3].toDouble());
            pvdg.SetBG(str[1 + i * 3].toDouble());
            pvdg.SetMG(str[2 + i * 3].toDouble());

            data.PVDG()[reg].push_back(pvdg);
        }
    }
}

void EclipseFileReader::ReadPVTG(ProjectData &data, QTextStream &sr)
{
    int ntPVT = data.TABDIMS().NTPVT().isNull() ? DefaultValues::TABDIMS_NTPVT : data.TABDIMS().NTPVT().toInt();

    data.PVTG().resize(ntPVT);

    for (int reg = 0; reg < ntPVT; reg++)
    {
        while (true)
        {
            QStringList str = ReadFileHelper::ParseParams(sr);

            if (str.length() == 0) break;

            double pg = str[0].toDouble();

            for (int i = 0; i < (str.length() - 1) / 3; i++)
            {
                PVTGData pvtg;

                pvtg.SetPG(pg);

                pvtg.SetRV(str[1 + 3 * i].toDouble());
                pvtg.SetBG(str[2 + 3 * i].toDouble());
                pvtg.SetMG(str[3 + 3 * i].toDouble());

                data.PVTG()[reg].push_back(pvtg);
            }
        }
    }
}

void EclipseFileReader::ReadROCKOPTS(ProjectData &data, QTextStream &sr)
{
    QStringList str = ReadFileHelper::GetNextLineWords(sr);

    if (str.length() > 1 && str[0] != "1*")
    {
        QMetaObject metaObject = MAOTPOptionsEnum::staticMetaObject;
        QMetaEnum maotpOptions = metaObject.enumerator(metaObject.indexOfEnumerator("MAOTPOptions"));

        data.ROCKOPTS().SetMAOTP(maotpOptions.keyToValue(str[0].toLatin1()));
    }

    if (str.length() > 2 && str[1] != "1*")
    {
        QMetaObject metaObject = ReferencePressureOptionsEnum::staticMetaObject;
        QMetaEnum referencePressureOptions = metaObject.enumerator(metaObject.indexOfEnumerator("ReferencePressureOptions"));

        data.ROCKOPTS().SetRPO(referencePressureOptions.keyToValue(str[1].toLatin1()));
    }

    if (str.length() > 3 && str[2] != "1*")
    {
        QMetaObject metaObject = RegionOptionsEnum::staticMetaObject;
        QMetaEnum regionOptions = metaObject.enumerator(metaObject.indexOfEnumerator("RegionOptions"));

        int val = regionOptions.keyToValue(str[2].toLatin1());

        data.ROCKOPTS().SetRegionOption(val >= 0 ? val : RegionOptionsEnum::PVTNUM);
    }

    if (str.length() > 4 && str[3] != "1*")
    {
        QMetaObject metaObject = IHBOptionsEnum::staticMetaObject;
        QMetaEnum ihbOptions = metaObject.enumerator(metaObject.indexOfEnumerator("IHBOptions"));

        data.ROCKOPTS().SetIHBOption(ihbOptions.keyToValue(str[3].toLatin1()));
    }
}

void EclipseFileReader::ReadROCK(ProjectData &data, QTextStream &sr)
{
    int regionOption = !data.ROCKOPTS().RegionOption().isNull() ?
                                    data.ROCKOPTS().RegionOption().toInt() :
                                    DefaultValues::ROCKOPTS_RegionOption;

    int nt = regionOption == RegionOptionsEnum::SATNUM ?
                                data.TABDIMS().NTSFUN().isNull() ? DefaultValues::TABDIMS_NTSFUN : data.TABDIMS().NTSFUN().toInt() :
                                data.TABDIMS().NTPVT().isNull() ? DefaultValues::TABDIMS_NTPVT : data.TABDIMS().NTPVT().toInt();

    data.ROCK().resize(nt);

    for (int reg = 0; reg < nt; reg++)
    {
        ROCKData rock;

        QStringList str = ReadFileHelper::ParseParams(sr);

        if (str.length() > 0 && str[0] != "1*") rock.SetPRef(str[0].toDouble());
        if (str.length() > 1 && str[1] != "1*") rock.SetCPP(str[1].toDouble());

        data.ROCK()[reg] = rock;
    }
}

void EclipseFileReader::ReadDENSITY(ProjectData &data, QTextStream &sr)
{
    int ntPVT = data.TABDIMS().NTPVT().isNull() ? DefaultValues::TABDIMS_NTPVT : data.TABDIMS().NTPVT().toInt();

    data.DENSITY().resize(ntPVT);

    for (int reg = 0; reg < ntPVT; reg++)
    {
        QStringList str = ReadFileHelper::ParseParams(sr);

        DENSITYData density;

        if (str.length() > 0 && str[0] != "1*") density.SetRO(str[0].toDouble());
        if (str.length() > 1 && str[1] != "1*") density.SetRW(str[1].toDouble());
        if (str.length() > 2 && str[2] != "1*") density.SetRG(str[2].toDouble());

        data.DENSITY()[reg] = density;
    }
}

void EclipseFileReader::ReadGRAVITY(ProjectData &data, QTextStream &sr)
{
    int ntPVT = data.TABDIMS().NTPVT().isNull() ? DefaultValues::TABDIMS_NTPVT : data.TABDIMS().NTPVT().toInt();

    data.GRAVITY().resize(ntPVT);

    for (int reg = 0; reg < ntPVT; reg++)
    {
        QStringList str = ReadFileHelper::ParseParams(sr);

        GRAVITYData gravity;

        if (str.length() > 0 && str[0] != "1*") gravity.SetGO(str[0].toDouble());
        if (str.length() > 1 && str[1] != "1*") gravity.SetGW(str[1].toDouble());
        if (str.length() > 2 && str[2] != "1*") gravity.SetGG(str[2].toDouble());

        data.GRAVITY()[reg] = gravity;
    }
}

void EclipseFileReader::ReadSWOF(ProjectData &data, QTextStream &sr)
{
    int ntSFUN = data.TABDIMS().NTSFUN().isNull() ? DefaultValues::TABDIMS_NTSFUN : data.TABDIMS().NTSFUN().toInt();

    data.SWOF().resize(ntSFUN);

    for (int reg = 0; reg < ntSFUN; reg++)
    {
        QStringList str = ReadFileHelper::ParseParams(sr);

        for (int i = 0; i < str.length() / 4; i++)
        {
            SWOFData swof;

            swof.SetSW(str[0 + 4 * i].toDouble());
            if (str[1 + 4 * i] != "1*") swof.SetKrW(str[1 + 4 * i].toDouble());
            if (str[2 + 4 * i] != "1*") swof.SetKrO(str[2 + 4 * i].toDouble());
            if (str[3 + 4 * i] != "1*") swof.SetPc(str[3 + 4 * i].toDouble());

            data.SWOF()[reg].push_back(swof);
        }
    }
}

void EclipseFileReader::ReadSGOF(ProjectData &data, QTextStream &sr)
{
    int ntSFUN = data.TABDIMS().NTSFUN().isNull() ? DefaultValues::TABDIMS_NTSFUN : data.TABDIMS().NTSFUN().toInt();

    data.SGOF().resize(ntSFUN);

    for (int reg = 0; reg < ntSFUN; reg++)
    {
        QStringList str = ReadFileHelper::ParseParams(sr);

        for (int i = 0; i < str.length() / 4; i++)
        {
            SGOFData sgof;

            sgof.SetSG(str[0 + 4 * i].toDouble());
            if (str[1 + 4 * i] != "1*") sgof.SetKrG(str[1 + 4 * i].toDouble());
            if (str[2 + 4 * i] != "1*") sgof.SetKrO(str[2 + 4 * i].toDouble());
            if (str[3 + 4 * i] != "1*") sgof.SetPc(str[3 + 4 * i].toDouble());

            data.SGOF()[reg].push_back(sgof);
        }
    }
}

void EclipseFileReader::ReadSGWFN(ProjectData &data, QTextStream &sr)
{
    int ntSFUN = data.TABDIMS().NTSFUN().isNull() ? DefaultValues::TABDIMS_NTSFUN : data.TABDIMS().NTSFUN().toInt();

    data.SGWFN().resize(ntSFUN);

    for (int reg = 0; reg < ntSFUN; reg++)
    {
        QStringList str = ReadFileHelper::ParseParams(sr);

        for (int i = 0; i < str.length() / 4; i++)
        {
            SGWFNData sgwfn;

            sgwfn.SetSG(str[0 + 4 * i].toDouble());
            if (str[1 + 4 * i] != "1*") sgwfn.SetKrG(str[1 + 4 * i].toDouble());
            if (str[2 + 4 * i] != "1*") sgwfn.SetKrW(str[2 + 4 * i].toDouble());
            if (str[3 + 4 * i] != "1*") sgwfn.SetPc(str[3 + 4 * i].toDouble());

            data.SGWFN()[reg].push_back(sgwfn);
        }
    }
}

void EclipseFileReader::ReadSLGOF(ProjectData &data, QTextStream &sr)
{
    int ntSFUN = data.TABDIMS().NTSFUN().isNull() ? DefaultValues::TABDIMS_NTSFUN : data.TABDIMS().NTSFUN().toInt();

    data.SLGOF().resize(ntSFUN);

    for (int reg = 0; reg < ntSFUN; reg++)
    {
        QStringList str = ReadFileHelper::ParseParams(sr);

        for (int i = 0; i < str.length() / 4; i++)
        {
            SLGOFData slgof;

            slgof.SetSL(str[0 + 4 * i].toDouble());
            if (str[1 + 4 * i] != "1*") slgof.SetKrG(str[1 + 4 * i].toDouble());
            if (str[2 + 4 * i] != "1*") slgof.SetKrO(str[2 + 4 * i].toDouble());
            if (str[3 + 4 * i] != "1*") slgof.SetPc(str[3 + 4 * i].toDouble());

            data.SLGOF()[reg].push_back(slgof);
        }
    }
}

void EclipseFileReader::ReadSOF2(ProjectData &data, QTextStream &sr)
{
    int ntSFUN = data.TABDIMS().NTSFUN().isNull() ? DefaultValues::TABDIMS_NTSFUN : data.TABDIMS().NTSFUN().toInt();

    data.SOF2().resize(ntSFUN);

    for (int reg = 0; reg < ntSFUN; reg++)
    {
        QStringList str = ReadFileHelper::ParseParams(sr);

        for (int i = 0; i < str.length() / 2; i++)
        {
            SOF2Data sof2;

            sof2.SetSO(str[0 + 2 * i].toDouble());
            sof2.SetKrO(str[1 + 2 * i].toDouble());

            data.SOF2()[reg].push_back(sof2);
        }
    }
}

void EclipseFileReader::ReadSOF3(ProjectData &data, QTextStream &sr)
{
    int ntSFUN = data.TABDIMS().NTSFUN().isNull() ? DefaultValues::TABDIMS_NTSFUN : data.TABDIMS().NTSFUN().toInt();

    data.SOF3().resize(ntSFUN);

    for (int reg = 0; reg < ntSFUN; reg++)
    {
        QStringList str = ReadFileHelper::ParseParams(sr);

        for (int i = 0; i < str.length() / 3; i++)
        {
            SOF3Data sof3;

            sof3.SetSO(str[0 + 3 * i].toDouble());
            if (str[1 + 3 * i] != "1*") sof3.SetKrOW(str[1 + 3 * i].toDouble());
            if (str[2 + 3 * i] != "1*") sof3.SetKrOGWC(str[2 + 3 * i].toDouble());

            data.SOF3()[reg].push_back(sof3);
        }
    }
}

void EclipseFileReader::ReadSOF32D(ProjectData &data, QTextStream &sr)
{
    int ntSFUN = data.TABDIMS().NTSFUN().isNull() ? DefaultValues::TABDIMS_NTSFUN : data.TABDIMS().NTSFUN().toInt();

    data.SOF32D().resize(ntSFUN);

    for (int reg = 0; reg < ntSFUN; reg++)
    {
        SOF32DData sof32d;

        // SWAT
        QStringList str = ReadFileHelper::ParseParams(sr);

        for (int i = 0; i < str.length(); i++) sof32d.SW().push_back(str[i].toDouble());

        while (true)
        {
            str = ReadFileHelper::ParseParams(sr);

            if (str.length() == 0) break;

            SOF32DKrOData sof32dKrO;

            sof32dKrO.SetSG(str[0].toDouble());

            for (int i = 1; i < str.length(); i++) sof32dKrO.KrO().push_back(str[i].toDouble());

            sof32d.SOF32DKrO().push_back(sof32dKrO);
        }

        data.SOF32D()[reg] = sof32d;
    }
}

void EclipseFileReader::ReadSWFN(ProjectData &data, QTextStream &sr)
{
    int ntSFUN = data.TABDIMS().NTSFUN().isNull() ? DefaultValues::TABDIMS_NTSFUN : data.TABDIMS().NTSFUN().toInt();

    data.SWFN().resize(ntSFUN);

    for (int reg = 0; reg < ntSFUN; reg++)
    {
        QStringList str = ReadFileHelper::ParseParams(sr);

        for (int i = 0; i < str.length() / 3; i++)
        {
            SWFNData swfn;

            swfn.SetSW(str[0 + 3 * i].toDouble());
            if (str[1 + 3 * i] != "1*") swfn.SetKrW(str[1 + 3 * i].toDouble());
            if (str[2 + 3 * i] != "1*") swfn.SetPc(str[2 + 3 * i].toDouble());

            data.SWFN()[reg].push_back(swfn);
        }
    }
}

void EclipseFileReader::ReadSGFN(ProjectData &data, QTextStream &sr)
{
    int ntSFUN = data.TABDIMS().NTSFUN().isNull() ? DefaultValues::TABDIMS_NTSFUN : data.TABDIMS().NTSFUN().toInt();

    data.SGFN().resize(ntSFUN);

    for (int reg = 0; reg < ntSFUN; reg++)
    {
        QStringList str = ReadFileHelper::ParseParams(sr);

        for (int i = 0; i < str.length() / 3; i++)
        {
            SGFNData sgfn;

            sgfn.SetSG(str[0 + 3 * i].toDouble());
            if (str[1 + 3 * i] != "1*") sgfn.SetKrG(str[1 + 3 * i].toDouble());
            if (str[2 + 3 * i] != "1*") sgfn.SetPc(str[2 + 3 * i].toDouble());

            data.SGFN()[reg].push_back(sgfn);
        }
    }
}

void EclipseFileReader::ReadSOMGAS(ProjectData &data, QTextStream &sr)
{
    int ntSFUN = data.TABDIMS().NTSFUN().isNull() ? DefaultValues::TABDIMS_NTSFUN : data.TABDIMS().NTSFUN().toInt();

    data.SOMGAS().resize(ntSFUN);

    for (int reg = 0; reg < ntSFUN; reg++)
    {
        QStringList str = ReadFileHelper::ParseParams(sr);

        for (int i = 0; i < str.length() / 2; i++)
        {
            SOMGASData somgas;

            somgas.SetSG(str[0 + 2 * i].toDouble());
            somgas.SetSOMin(str[1 + 2 * i].toDouble());

            data.SOMGAS()[reg].push_back(somgas);
        }
    }
}

void EclipseFileReader::ReadSOMWAT(ProjectData &data, QTextStream &sr)
{
    int ntSFUN = data.TABDIMS().NTSFUN().isNull() ? DefaultValues::TABDIMS_NTSFUN : data.TABDIMS().NTSFUN().toInt();

    data.SOMWAT().resize(ntSFUN);

    for (int reg = 0; reg < ntSFUN; reg++)
    {
        QStringList str = ReadFileHelper::ParseParams(sr);

        for (int i = 0; i < str.length() / 2; i++)
        {
            SOMWATData somwat;

            somwat.SetSW(str[0 + 2 * i].toDouble());
            somwat.SetSOMin(str[1 + 2 * i].toDouble());

            data.SOMWAT()[reg].push_back(somwat);
        }
    }
}

void EclipseFileReader::ReadPPCWMAX(ProjectData &data, QTextStream &sr)
{
    int ntSFUN = data.TABDIMS().NTSFUN().isNull() ? DefaultValues::TABDIMS_NTSFUN : data.TABDIMS().NTSFUN().toInt();

    data.PPCWMAX().resize(ntSFUN);

    for (int reg = 0; reg < ntSFUN; reg++)
    {
        QStringList str = ReadFileHelper::ParseParams(sr);

        PPCWMAXData ppcwMAX;

        if (str.length() > 0 && str[0] != "1*") ppcwMAX.SetPcMax(str[0].toDouble());

        if (str.length() > 1 && str[1] != "1*") ppcwMAX.SetSModify(ReadFileHelper::IsYes(str[1]));

        data.PPCWMAX()[reg] = ppcwMAX;
    }
}

void EclipseFileReader::ReadENKRVD(ProjectData &data, QTextStream &sr)
{
    int ntENDP = data.ENDSCALE().NTENDP().isNull() ? DefaultValues::ENDSCALE_NTENDP : data.ENDSCALE().NTENDP().toInt();

    data.ENKRVD().resize(ntENDP);

    for (int nt = 0; nt < ntENDP; nt++)
    {
        QStringList str = ReadFileHelper::ParseParams(sr);

        for (int i = 0; i < str.length() / 8; i++)
        {
            ENKRVDData enkrvd;

            enkrvd.SetDepth(str[0 + 8 * i].toDouble());
            if (str[1 + 8 * i] != "1*") enkrvd.SetMaxKrW(str[1 + 8 * i].toDouble());
            if (str[2 + 8 * i] != "1*") enkrvd.SetMaxKrG(str[2 + 8 * i].toDouble());
            if (str[3 + 8 * i] != "1*") enkrvd.SetMaxKrO(str[3 + 8 * i].toDouble());
            if (str[4 + 8 * i] != "1*") enkrvd.SetKrWCO(str[4 + 8 * i].toDouble());
            if (str[5 + 8 * i] != "1*") enkrvd.SetKrGCO(str[5 + 8 * i].toDouble());
            if (str[6 + 8 * i] != "1*") enkrvd.SetKrOCG(str[6 + 8 * i].toDouble());
            if (str[7 + 8 * i] != "1*") enkrvd.SetKrOCW(str[7 + 8 * i].toDouble());

            data.ENKRVD()[nt].push_back(enkrvd);
        }
    }
}

void EclipseFileReader::ReadENPCVD(ProjectData &data, QTextStream &sr)
{
    int ntENDP = data.ENDSCALE().NTENDP().isNull() ? DefaultValues::ENDSCALE_NTENDP : data.ENDSCALE().NTENDP().toInt();

    data.ENPCVD().resize(ntENDP);

    for (int nt = 0; nt < ntENDP; nt++)
    {
        QStringList str = ReadFileHelper::ParseParams(sr);

        for (int i = 0; i < str.length() / 3; i++)
        {
            ENPCVDData enpcvd;

            enpcvd.SetDepth(str[0 + 3 * i].toDouble());
            if (str[1 + 3 * i] != "1*") enpcvd.SetMaxPcGO(str[1 + 3 * i].toDouble());
            if (str[2 + 3 * i] != "1*") enpcvd.SetMaxPcWO(str[2 + 3 * i].toDouble());

            data.ENPCVD()[nt].push_back(enpcvd);
        }
    }
}

void EclipseFileReader::ReadENSPCVD(ProjectData &data, QTextStream &sr)
{
    int ntENDP = data.ENDSCALE().NTENDP().isNull() ? DefaultValues::ENDSCALE_NTENDP : data.ENDSCALE().NTENDP().toInt();

    data.ENSPCVD().resize(ntENDP);

    for (int nt = 0; nt < ntENDP; nt++)
    {
        QStringList str = ReadFileHelper::ParseParams(sr);

        for (int i = 0; i < str.length() / 3; i++)
        {
            ENSPCVDData enspcvd;

            enspcvd.SetDepth(str[0 + 3 * i].toDouble());
            if (str[1 + 3 * i] != "1*") enspcvd.SetSGL(str[1 + 3 * i].toDouble());
            if (str[2 + 3 * i] != "1*") enspcvd.SetSWL(str[2 + 3 * i].toDouble());

            data.ENSPCVD()[nt].push_back(enspcvd);
        }
    }
}

void EclipseFileReader::ReadSCALELIM(ProjectData &data, QTextStream &sr)
{
    int ntENDP = data.ENDSCALE().NTENDP().isNull() ? DefaultValues::ENDSCALE_NTENDP : data.ENDSCALE().NTENDP().toInt();

    data.SCALELIM().resize(ntENDP);

    for (int nt = 0; nt < ntENDP; nt++)
    {
        QStringList str = ReadFileHelper::ParseParams(sr);

        QVariant val;

        if (str.length() > 0 && str[0] != "1*") val = str[0].toDouble();

        data.SCALELIM()[nt] = val;
    }
}

void EclipseFileReader::ReadSCALECRS(ProjectData &data, QTextStream &sr)
{
    QString str = ReadFileHelper::GetNextLine(sr);

    data.SetSCALECRS(ReadFileHelper::IsYes(ReadFileHelper::ParseKeyword(str)));
}

void EclipseFileReader::ReadSPECHEAT(ProjectData &data, QTextStream &sr)
{
    int ntPVT = data.TABDIMS().NTPVT().isNull() ? DefaultValues::TABDIMS_NTPVT : data.TABDIMS().NTPVT().toInt();

    data.SPECHEAT().resize(ntPVT);

    for (int reg = 0; reg < ntPVT; reg++)
    {
        QStringList str = ReadFileHelper::ParseParams(sr);

        for (int i = 0; i < str.length() / 4; i++)
        {
            SPECHEATData specHEAT;

            specHEAT.SetT(str[0 + 4 * i].toDouble());
            specHEAT.SetCO(str[1 + 4 * i].toDouble());
            specHEAT.SetCW(str[2 + 4 * i].toDouble());
            specHEAT.SetCG(str[3 + 4 * i].toDouble());

            data.SPECHEAT()[reg].push_back(specHEAT);
        }
    }
}

void EclipseFileReader::ReadSPECROCK(ProjectData &data, QTextStream &sr)
{
    int ntSFUN = data.TABDIMS().NTSFUN().isNull() ? DefaultValues::TABDIMS_NTSFUN : data.TABDIMS().NTSFUN().toInt();

    data.SPECROCK().resize(ntSFUN);

    for (int reg = 0; reg < ntSFUN; reg++)
    {
        QStringList str = ReadFileHelper::ParseParams(sr);

        for (int i = 0; i < str.length() / 2; i++)
        {
            SPECROCKData specROCK;

            specROCK.SetT(str[0 + 2 * i].toDouble());
            specROCK.SetCV(str[1 + 2 * i].toDouble());

            data.SPECROCK()[reg].push_back(specROCK);
        }
    }
}

void EclipseFileReader::ReadVISCREF(ProjectData &data, QTextStream &sr)
{
    int ntPVT = data.TABDIMS().NTPVT().isNull() ? DefaultValues::TABDIMS_NTPVT : data.TABDIMS().NTPVT().toInt();

    data.VISCREF().resize(ntPVT);

    for (int reg = 0; reg < ntPVT; reg++)
    {
        QStringList str = ReadFileHelper::ParseParams(sr);

        VISCREFData viscREF;

        viscREF.SetPRef(str[0].toDouble());
        if (str.length() > 1 && str[1] != "1*") viscREF.SetRSRef(str[1].toDouble());
        if (str.length() > 2 && str[2] != "1*") viscREF.SetGRef(str[2].toDouble());

        data.VISCREF()[reg] = viscREF;
    }
}

void EclipseFileReader::ReadOILVISCT(ProjectData &data, QTextStream &sr)
{
    int ntPVT = data.TABDIMS().NTPVT().isNull() ? DefaultValues::TABDIMS_NTPVT : data.TABDIMS().NTPVT().toInt();

    data.OILVISCT().resize(ntPVT);

    for (int reg = 0; reg < ntPVT; reg++)
    {
        QStringList str = ReadFileHelper::ParseParams(sr);

        for (int i = 0; i < str.length() / 2; i++)
        {
            OILVISCTData oilVISCT;

            oilVISCT.SetT(str[0 + 2 * i].toDouble());
            oilVISCT.SetMO(str[1 + 2 * i].toDouble());

            data.OILVISCT()[reg].push_back(oilVISCT);
        }
    }
}

void EclipseFileReader::ReadWATVISCT(ProjectData &data, QTextStream &sr)
{
    int ntPVT = data.TABDIMS().NTPVT().isNull() ? DefaultValues::TABDIMS_NTPVT : data.TABDIMS().NTPVT().toInt();

    data.WATVISCT().resize(ntPVT);

    for (int reg = 0; reg < ntPVT; reg++)
    {
        QStringList str = ReadFileHelper::ParseParams(sr);

        for (int i = 0; i < str.length() / 2; i++)
        {
            WATVISCTData watVISCT;

            watVISCT.SetT(str[0 + 2 * i].toDouble());
            watVISCT.SetMW(str[1 + 2 * i].toDouble());

            data.WATVISCT()[reg].push_back(watVISCT);
        }
    }
}

// SOLUTION
void EclipseFileReader::ReadEQUIL(ProjectData &data, QTextStream &sr)
{
    int ntEQUL = data.EQLDIMS().NTEQUL().isNull() ? DefaultValues::EQLDIMS_NTEQUL : data.EQLDIMS().NTEQUL().toInt();

    data.EQUIL().resize(ntEQUL);

    for (int reg = 0; reg < ntEQUL; reg++)
    {
        QStringList str = ReadFileHelper::ParseParams(sr);

        EQUILData equil;

        equil.SetDatumDepth(str[0].toDouble());
        equil.SetDatumP(str[1].toDouble());
        if (str.length() > 2 && str[2] != "1*") equil.SetWOCDepth(str[2].toDouble());
        if (str.length() > 3 && str[3] != "1*") equil.SetWOCPc(str[3].toDouble());
        if (str.length() > 4 && str[4] != "1*") equil.SetGOCDepth(str[4].toDouble());
        if (str.length() > 5 && str[5] != "1*") equil.SetGOCPc(str[5].toDouble());

        data.EQUIL()[reg] = equil;
    }
}

void EclipseFileReader::ReadRSVD(ProjectData &data, QTextStream &sr)
{
    int ntEQUL = data.EQLDIMS().NTEQUL().isNull() ? DefaultValues::EQLDIMS_NTEQUL : data.EQLDIMS().NTEQUL().toInt();

    data.RSVD().resize(ntEQUL);

    for (int reg = 0; reg < ntEQUL; reg++)
    {
        QStringList str = ReadFileHelper::ParseParams(sr);

        for (int i = 0; i < str.length() / 2; i++)
        {
            RSVDData rsvd;

            rsvd.SetDepth(str[0 + i * 2].toDouble());
            rsvd.SetRS(str[1 + i * 2].toDouble());

            data.RSVD()[reg].push_back(rsvd);
        }
    }
}

void EclipseFileReader::ReadPBVD(ProjectData &data, QTextStream &sr)
{
    int ntEQUL = data.EQLDIMS().NTEQUL().isNull() ? DefaultValues::EQLDIMS_NTEQUL : data.EQLDIMS().NTEQUL().toInt();

    data.PBVD().resize(ntEQUL);

    for (int reg = 0; reg < ntEQUL; reg++)
    {
        QStringList str = ReadFileHelper::ParseParams(sr);

        for (int i = 0; i < str.length() / 2; i++)
        {
            PBVDData pbvd;

            pbvd.SetDepth(str[0 + i * 2].toDouble());
            pbvd.SetPBub(str[1 + i * 2].toDouble());

            data.PBVD()[reg].push_back(pbvd);
        }
    }
}

void EclipseFileReader::ReadPRVD(ProjectData &data, QTextStream &sr)
{
    int ntEQUL = data.EQLDIMS().NTEQUL().isNull() ? DefaultValues::EQLDIMS_NTEQUL : data.EQLDIMS().NTEQUL().toInt();

    data.PRVD().resize(ntEQUL);

    for (int reg = 0; reg < ntEQUL; reg++)
    {
        QStringList str = ReadFileHelper::ParseParams(sr);

        for (int i = 0; i < str.length() / 2; i++)
        {
            PRVDData prvd;

            prvd.SetDepth(str[0 + i * 2].toDouble());
            prvd.SetPO(str[1 + i * 2].toDouble());

            data.PRVD()[reg].push_back(prvd);
        }
    }
}

void EclipseFileReader::ReadAQUANCON(ProjectData &data, QTextStream &sr)
{
    QMetaObject metaObject = FaceTypeEnum::staticMetaObject;

    QMetaEnum faceTypeEnum = metaObject.enumerator(metaObject.indexOfEnumerator("FaceType"));

    while (true)
    {
        QStringList str = ReadFileHelper::ParseParams(sr);
        if (str.length() == 0) break;

        AQUANCONData aquanCON;

        str[7] = str[7].replace('-', 'm');
        str[7] = str[7].replace('+', 'p');

        aquanCON.SetNum(str[0].toInt());
        aquanCON.SetI1(str[1].toInt() - 1);
        aquanCON.SetI2(str[2].toInt() - 1);
        aquanCON.SetJ1(str[3].toInt() - 1);
        aquanCON.SetJ2(str[4].toInt() - 1);
        aquanCON.SetK1(str[5].toInt() - 1);
        aquanCON.SetK2(str[6].toInt() - 1);
        aquanCON.SetSide(faceTypeEnum.keyToValue(str[7].toLatin1()));
        if (str.length() > 8 && str[8] != "1*") aquanCON.SetInfluxCoef(str[8].toDouble());
        if (str.length() > 9 && str[9] != "1*") aquanCON.SetInfluxMult(str[9].toDouble());

        data.AQUANCON().push_back(aquanCON);
    }
}

void EclipseFileReader::ReadAQUFETP(ProjectData &data, QTextStream &sr)
{
    while (true)
    {
        QStringList str = ReadFileHelper::ParseParams(sr);
        if (str.length() == 0) break;

        AQUFETPData aquFETP;

        aquFETP.SetNum(str[0].toInt());
        aquFETP.SetDatumDepth(str[1].toDouble());
        if (str[2] != "1*") aquFETP.SetDatumP(str[2].toDouble());
        aquFETP.SetVW(str[3].toDouble());
        aquFETP.SetC(str[4].toDouble());
        aquFETP.SetProdIndex(str[5].toDouble());
        aquFETP.SetPVTWNum(str[6].toInt());
        if (str.length() > 7 && str[7] != "1*") aquFETP.SetSALT(str[7].toDouble());

        data.AQUFETP().push_back(aquFETP);
    }
}

// SCHEDULE
void EclipseFileReader::ReadDIMPES(ProjectData &data, QTextStream &sr)
{
    QStringList str = ReadFileHelper::ParseParams(sr);

    if (str.length() > 0 && str[0] != "1*") data.DIMPES().SetDSTARG(str[0].toDouble());
    if (str.length() > 1 && str[1] != "1*") data.DIMPES().SetDSMAX(str[1].toDouble());
    if (str.length() > 2 && str[2] != "1*") data.DIMPES().SetDPMAX(str[2].toDouble());
}

void EclipseFileReader::ReadWELSPECS(ProjectData &data, QTextStream &sr)
{
    while (true)
    {
        QStringList str = ReadFileHelper::ParseParams(sr, 0, false);
        if (str.length() == 0) break;

        WELSPECSData wData;

        wData.SetWellName(str[0]);
        if(str[1] != "1*") wData.SetWellGroup(str[1]);
        wData.SetI(str[2].toInt());
        wData.SetJ(str[3].toInt());
        if (str.length() > 4 && str[4] != "1*") wData.SetDepth(str[4].toDouble());

        wData.SetDate(currentDate);

        data.WELSPECS().push_back(wData);
    }
}

void EclipseFileReader::ReadCOMPDAT(ProjectData &data, QTextStream &sr)
{
    QMetaObject metaObject = WellStatusEnum::staticMetaObject;

    QMetaEnum wellStatusEnum = metaObject.enumerator(metaObject.indexOfEnumerator("WellStatus"));

    while (true)
    {
        QStringList str = ReadFileHelper::ParseParams(sr, 0, false);
        if (str.length() == 0) break;

        COMPDATData compdat;

        compdat.SetWellName(str[0]);
        if (str.length() > 1 && str[1] != "1*") compdat.SetI(str[1].toInt());
        if (str.length() > 2 && str[2] != "1*") compdat.SetJ(str[2].toInt());
        if (str.length() > 3 && str[3] != "1*") compdat.SetK1(str[3].toInt());
        if (str.length() > 4 && str[4] != "1*") compdat.SetK2(str[4].toInt());
        if (str.length() > 5 && str[5] != "1*") compdat.SetWellStatus(wellStatusEnum.keyToValue(str[5].toLatin1()));
        if (str.length() > 6 && str[6] != "1*") compdat.SetSATNUM(str[6].toInt());
        if (str.length() > 7 && str[7] != "1*") compdat.SetTranFactor(str[7].toDouble());
        if (str.length() > 8 && str[8] != "1*") compdat.SetDiameter(str[8].toDouble());
        if (str.length() > 9 && str[9] != "1*") compdat.SetKh(str[9].toDouble());
        if (str.length() > 10 && str[10] != "1*") compdat.SetSkinFactor(str[10].toDouble());

        compdat.SetDate(currentDate);

        data.COMPDAT().push_back(compdat);
    }
}

void EclipseFileReader::ReadWCONPROD(ProjectData &data, QTextStream &sr)
{
    QMetaObject wellStatusObject = WellStatusEnum::staticMetaObject;
    QMetaObject wellControlObject = WellControlEnum::staticMetaObject;

    QMetaEnum wellStatusEnum = wellStatusObject.enumerator(wellStatusObject.indexOfEnumerator("WellStatus"));
    QMetaEnum wellControlEnum = wellControlObject.enumerator(wellControlObject.indexOfEnumerator("WellControl"));

    while (true)
    {
        QStringList str = ReadFileHelper::ParseParams(sr, 0, false);
        if (str.length() == 0) break;

        WCONPRODData wconprod;

        wconprod.SetWellName(str[0]);
        if (str.length() > 1 && str[1] != "1*") wconprod.SetWellStatus(wellStatusEnum.keyToValue(str[1].toLatin1()));
        if (str.length() > 2 && str[2] != "1*") wconprod.SetWellControl(wellControlEnum.keyToValue(str[2].toLatin1()));
        if (str.length() > 3 && str[3] != "1*") wconprod.SetORAT(str[3].toDouble());
        if (str.length() > 4 && str[4] != "1*") wconprod.SetWRAT(str[4].toDouble());
        if (str.length() > 5 && str[5] != "1*") wconprod.SetGRAT(str[5].toDouble());
        if (str.length() > 6 && str[6] != "1*") wconprod.SetLRAT(str[6].toDouble());
        if (str.length() > 7 && str[7] != "1*") wconprod.SetRESV(str[7].toDouble());
        if (str.length() > 8 && str[8] != "1*") wconprod.SetBHP(str[8].toDouble());

        wconprod.SetDate(currentDate);

        data.WCONPROD().push_back(wconprod);
    }
}

void EclipseFileReader::ReadWCONINJE(ProjectData &data, QTextStream &sr)
{
    QMetaObject wellStatusObject = WellStatusEnum::staticMetaObject;
    QMetaObject wellControlObject = WellControlEnum::staticMetaObject;
    QMetaObject fluidTypeObject = FluidTypeEnum::staticMetaObject;

    QMetaEnum wellStatusEnum = wellStatusObject.enumerator(wellStatusObject.indexOfEnumerator("WellStatus"));
    QMetaEnum wellControlEnum = wellControlObject.enumerator(wellControlObject.indexOfEnumerator("WellControl"));
    QMetaEnum fluidTypeEnum = fluidTypeObject.enumerator(fluidTypeObject.indexOfEnumerator("FluidType"));

    while (true)
    {
        QStringList str = ReadFileHelper::ParseParams(sr, 0, false);
        if (str.length() == 0) break;

        WCONINJEData wconinje;

        wconinje.SetWellName(str[0]);
        if (str.length() > 1 && str[1] != "1*") wconinje.SetInjFluid(fluidTypeEnum.keyToValue(str[1].toLatin1()));
        if (str.length() > 2 && str[2] != "1*") wconinje.SetWellStatus(wellStatusEnum.keyToValue(str[2].toLatin1()));
        if (str.length() > 3 && str[3] != "1*") wconinje.SetWellControl(wellControlEnum.keyToValue(str[3].toLatin1()));
        if (str.length() > 4 && str[4] != "1*") wconinje.SetRATE(str[4].toDouble());
        if (str.length() > 5 && str[5] != "1*") wconinje.SetRESV(str[5].toDouble());
        if (str.length() > 6 && str[6] != "1*") wconinje.SetBHP(str[6].toDouble());

        wconinje.SetDate(currentDate);

        data.WCONINJE().push_back(wconinje);
    }
}

void EclipseFileReader::ReadDATES(ProjectData &data, QTextStream &sr)
{
    QMetaObject metaObject = MonthsEnum::staticMetaObject;

    QMetaEnum monthsEnum = metaObject.enumerator(metaObject.indexOfEnumerator("Months"));

    while (true)
    {
        QStringList str = ReadFileHelper::ParseParams(sr, 0, false);
        if (str.length() == 0) break;

        QString strDate = ReadFileHelper::EclipseDateToStr(str, monthsEnum);

        QDateTime date = ReadFileHelper::StrToDate(strDate);

        data.DATES().push_back(date);

        currentDate = date;
    }
}

void EclipseFileReader::ReadTSTEP(ProjectData &data, QTextStream &sr)
{
    QStringList str = ReadFileHelper::ParseParams(sr);
    if (str.length() == 0) return;

    for (int i = 0; i < str.length(); i++)
    {
        double day = str[i].toDouble();

        qint64 seconds = static_cast<qint64>(24*3600*day);

        currentDate = currentDate.addSecs(seconds);

        data.DATES().push_back(currentDate);
    }
}

void EclipseFileReader::ReadWCONHIST(ProjectData &data, QTextStream &sr)
{
    QMetaObject wellStatusObject = WellStatusEnum::staticMetaObject;
    QMetaObject wellControlObject = WellControlEnum::staticMetaObject;

    QMetaEnum wellStatusEnum = wellStatusObject.enumerator(wellStatusObject.indexOfEnumerator("WellStatus"));
    QMetaEnum wellControlEnum = wellControlObject.enumerator(wellControlObject.indexOfEnumerator("WellControl"));

    while (true)
    {
        QStringList str = ReadFileHelper::ParseParams(sr, 0, false);
        if (str.length() == 0) break;

        WCONHISTData wconhist;

        wconhist.SetWellName(str[0]);
        if (str.length() > 1 && str[1] != "1*") wconhist.SetWellStatus(wellStatusEnum.keyToValue(str[1].toLatin1()));
        if (str.length() > 2 && str[2] != "1*") wconhist.SetWellControl(wellControlEnum.keyToValue(str[2].toLatin1()));
        if (str.length() > 3 && str[3] != "1*") wconhist.SetORAT(str[3].toDouble());
        if (str.length() > 4 && str[4] != "1*") wconhist.SetWRAT(str[4].toDouble());
        if (str.length() > 5 && str[5] != "1*") wconhist.SetGRAT(str[5].toDouble());

        wconhist.SetDate(currentDate);

        data.WCONHIST().push_back(wconhist);
    }
}

void EclipseFileReader::ReadWCONINJH(ProjectData &data, QTextStream &sr)
{
    QMetaObject wellStatusObject = WellStatusEnum::staticMetaObject;
    QMetaObject fluidTypeObject = FluidTypeEnum::staticMetaObject;

    QMetaEnum wellStatusEnum = wellStatusObject.enumerator(wellStatusObject.indexOfEnumerator("WellStatus"));
    QMetaEnum fluidTypeEnum = fluidTypeObject.enumerator(fluidTypeObject.indexOfEnumerator("FluidType"));

    while (true)
    {
        QStringList str = ReadFileHelper::ParseParams(sr, 0, false);
        if (str.length() == 0) break;

        WCONINJHData wconinjh;

        wconinjh.SetWellName(str[0]);
        if (str.length() > 1 && str[1] != "1*") wconinjh.SetInjFluid(fluidTypeEnum.keyToValue(str[1].toLatin1()));
        if (str.length() > 2 && str[2] != "1*") wconinjh.SetWellStatus(wellStatusEnum.keyToValue(str[2].toLatin1()));
        if (str.length() > 3 && str[3] != "1*") wconinjh.SetRATE(str[3].toDouble());
        if (str.length() > 4 && str[4] != "1*") wconinjh.SetBHP(str[4].toDouble());

        wconinjh.SetDate(currentDate);

        data.WCONINJH().push_back(wconinjh);
    }
}

void EclipseFileReader::ReadWELTARG(ProjectData &data, QTextStream &sr)
{
    QMetaObject metaObject = WellControlEnum::staticMetaObject;

    QMetaEnum wellControlEnum = metaObject.enumerator(metaObject.indexOfEnumerator("WellControl"));

    while (true)
    {
        QStringList str = ReadFileHelper::ParseParams(sr, 0, false);
        if (str.length() == 0) break;

        WELTARGData weltarg;

        weltarg.SetWellName(str[0]);
        if (str.length() > 1 && str[1] != "1*") weltarg.SetWellControl(wellControlEnum.keyToValue(str[1].toLatin1()));
        if (str.length() > 2 && str[2] != "1*") weltarg.SetValue(str[2].toDouble());

        weltarg.SetDate(currentDate);

        data.WELTARG().push_back(weltarg);
    }
}

// ANY SECTION
void EclipseFileReader::ReadINCLUDE(ProjectData &data, QTextStream &sr, const QString &currentDir, QMetaEnum &casesEnum)
{
    QStringList str = ReadFileHelper::ParseParams(sr);
    if (str.length() == 0) return;

    QString filename = currentDir + QDir::separator() + str[0].replace("'", "");

    ReadFile(data, filename, casesEnum);
}

void EclipseFileReader::ReadEQUALS(ProjectData &data, QTextStream &sr)
{
    while (true)
    {
        QStringList str = ReadFileHelper::ParseParams(sr, 0, true);
        if (str.length() == 0) break;

        OperatorData equals;

        equals.SetOperatorType(OperatorTypeEnum::EQUALS);        

        QString arrayName = str[0].replace("'", "");

        arrayName = arrayName.replace('-', 'm')
                            .replace('+', 'p');

        int index = ArrayNamesEnum::staticMetaObject.enumerator(ArrayNamesEnum::staticMetaObject.indexOfEnumerator("ArrayNames")).keyToValue(arrayName.toLatin1());

        equals.SetArrayName(index);

        equals.SetValue(str[1]);

        int i1 = str.length() > 2 && str[2] != "1*" ? str[2].toInt() - 1 : box.I1();
        int i2 = str.length() > 3 && str[3] != "1*" ? str[3].toInt() - 1 : box.I2();

        int j1 = str.length() > 4 && str[4] != "1*" ? str[4].toInt() - 1 : box.J1();
        int j2 = str.length() > 5 && str[5] != "1*" ? str[5].toInt() - 1 : box.J2();

        int k1 = str.length() > 6 && str[6] != "1*" ? str[6].toInt() - 1 : box.K1();
        int k2 = str.length() > 7 && str[7] != "1*" ? str[7].toInt() - 1 : box.K2();

        equals.SetBox(Box(i1, i2, j1, j2, k1, k2));

        data.Operators().push_back(equals);
    }
}

void EclipseFileReader::ReadBOX(QTextStream &sr)
{
    QStringList str = ReadFileHelper::ParseParams(sr);
    if (str.length() == 0) return;

    int i1 = str[0].toInt() - 1;
    int i2 = str[1].toInt() - 1;

    int j1 = str[2].toInt() - 1;
    int j2 = str[3].toInt() - 1;

    int k1 = str[4].toInt() - 1;
    int k2 = str[5].toInt() - 1;

    box = Box(i1, i2, j1, j2, k1, k2);
}

void EclipseFileReader::ReadENDBOX(ProjectData &data)
{
    int nx = data.Nx();
    int ny = data.Ny();
    int nz = data.Nz();

    box = Box(0, nx-1, 0, ny-1, 0, nz-1);
}

void EclipseFileReader::ReadCOPY(ProjectData &data, QTextStream &sr)
{
    while (true)
    {
        QStringList str = ReadFileHelper::ParseParams(sr);
        if (str.length() == 0) break;

        OperatorData copy;

        copy.SetOperatorType(OperatorTypeEnum::COPY);

        QString arrayName = str[0].replace("'", "");

        arrayName = arrayName.replace('-', 'm')
                            .replace('+', 'p');

        int index = ArrayNamesEnum::staticMetaObject.enumerator(ArrayNamesEnum::staticMetaObject.indexOfEnumerator("ArrayNames")).keyToValue(arrayName.toLatin1());

        copy.SetSource(index);

        arrayName = str[1].replace("'", "");

        arrayName = arrayName.replace('-', 'm')
                            .replace('+', 'p');

        index = ArrayNamesEnum::staticMetaObject.enumerator(ArrayNamesEnum::staticMetaObject.indexOfEnumerator("ArrayNames")).keyToValue(arrayName.toLatin1());

        copy.SetArrayName(index);

        int i1 = str.length() > 2 && str[2] != "1*" ? str[2].toInt() - 1 : box.I1();
        int i2 = str.length() > 3 && str[3] != "1*" ? str[3].toInt() - 1 : box.I2();

        int j1 = str.length() > 4 && str[4] != "1*" ? str[4].toInt() - 1 : box.J1();
        int j2 = str.length() > 5 && str[5] != "1*" ? str[5].toInt() - 1 : box.J2();

        int k1 = str.length() > 6 && str[6] != "1*" ? str[6].toInt() - 1 : box.K1();
        int k2 = str.length() > 7 && str[7] != "1*" ? str[7].toInt() - 1 : box.K2();

        copy.SetBox(Box(i1, i2, j1, j2, k1, k2));

        data.Operators().push_back(copy);
    }
}

void EclipseFileReader::ReadADD(ProjectData &data, QTextStream &sr)
{
    while (true)
    {
        QStringList str = ReadFileHelper::ParseParams(sr);
        if (str.length() == 0) break;

        OperatorData add;

        add.SetOperatorType(OperatorTypeEnum::ADD);

        QString arrayName = str[0].replace("'", "");

        arrayName = arrayName.replace('-', 'm')
                            .replace('+', 'p');

        int index = ArrayNamesEnum::staticMetaObject.enumerator(ArrayNamesEnum::staticMetaObject.indexOfEnumerator("ArrayNames")).keyToValue(arrayName.toLatin1());

        add.SetArrayName(index);

        add.SetValue(str[1]);

        int i1 = str.length() > 2 && str[2] != "1*" ? str[2].toInt() - 1 : box.I1();
        int i2 = str.length() > 3 && str[3] != "1*" ? str[3].toInt() - 1 : box.I2();

        int j1 = str.length() > 4 && str[4] != "1*" ? str[4].toInt() - 1 : box.J1();
        int j2 = str.length() > 5 && str[5] != "1*" ? str[5].toInt() - 1 : box.J2();

        int k1 = str.length() > 6 && str[6] != "1*" ? str[6].toInt() - 1 : box.K1();
        int k2 = str.length() > 7 && str[7] != "1*" ? str[7].toInt() - 1 : box.K2();

        add.SetBox(Box(i1, i2, j1, j2, k1, k2));

        data.Operators().push_back(add);
    }
}

void EclipseFileReader::ReadMULTIPLY(ProjectData &data, QTextStream &sr)
{
    while (true)
    {
        QStringList str = ReadFileHelper::ParseParams(sr);
        if (str.length() == 0) break;

        OperatorData multiply;

        multiply.SetOperatorType(OperatorTypeEnum::MULTIPLY);

        QString arrayName = str[0].replace("'", "");

        arrayName = arrayName.replace('-', 'm')
                            .replace('+', 'p');

        int index = ArrayNamesEnum::staticMetaObject.enumerator(ArrayNamesEnum::staticMetaObject.indexOfEnumerator("ArrayNames")).keyToValue(arrayName.toLatin1());

        multiply.SetArrayName(index);

        multiply.SetValue(str[1]);

        int i1 = str.length() > 2 && str[2] != "1*" ? str[2].toInt() - 1 : box.I1();
        int i2 = str.length() > 3 && str[3] != "1*" ? str[3].toInt() - 1 : box.I2();

        int j1 = str.length() > 4 && str[4] != "1*" ? str[4].toInt() - 1 : box.J1();
        int j2 = str.length() > 5 && str[5] != "1*" ? str[5].toInt() - 1 : box.J2();

        int k1 = str.length() > 6 && str[6] != "1*" ? str[6].toInt() - 1 : box.K1();
        int k2 = str.length() > 7 && str[7] != "1*" ? str[7].toInt() - 1 : box.K2();

        multiply.SetBox(Box(i1, i2, j1, j2, k1, k2));

        data.Operators().push_back(multiply);
    }
}

}}}
