#include "eclipsefilereadertest.h"

namespace BlackOil {
namespace Test {
namespace Data {
namespace Readers {

EclipseFileReaderTest::EclipseFileReaderTest(QObject *parent) : QObject(parent) { }

void EclipseFileReaderTest::CheckFile1()
{
    EclipseFileReader reader;

    ProjectData data;

    reader.Load(data, "D:\\Workspace\\C#\\Projects\\WinForms\\BlackOil\\Data\\SPE9\\SPE9 - no pc.DATA");

    VERIFY(data.Title() == "SPE 9TH COMPARATIVE STUDY", "");
    VERIFY(data.StartDate() == QDateTime(QDate(1990, 1, 1)), "");

    VERIFY(data.Unit() == UnitsEnum::FIELD, "");
    VERIFY(data.Model() == ModelsEnum::ThreePhase, "");
    VERIFY(data.TemperatureOption().isNull(), "");

    VERIFY(data.NumRES().isNull(), "");
    VERIFY(data.Nx() == 24, "");
    VERIFY(data.Ny() == 25, "");
    VERIFY(data.Nz() == 15, "");

    VERIFY(data.TABDIMS().NTSFUN() == 1, "");
    VERIFY(data.TABDIMS().NTPVT() == 1, "");
    VERIFY(data.TABDIMS().NSSFUN() == 40, "");

    VERIFY(data.EQLDIMS().NTEQUL().isNull(), "");

    VERIFY(data.ENDSCALE().Directional().isNull(), "");
    VERIFY(data.ENDSCALE().Irreversible().isNull(), "");
    VERIFY(data.ENDSCALE().NTENDP().isNull(), "");
    VERIFY(data.ENDSCALE().MaxNodesEPD().isNull(), "");

    VERIFY(data.Arrays()[ArrayNamesEnum::TOPS].Box().N() == 0, "");

    VERIFY(data.Arrays()[ArrayNamesEnum::DX].Box().N() == 0, "");
    VERIFY(data.Arrays()[ArrayNamesEnum::DY].Box().N() == 0, "");
    VERIFY(data.Arrays()[ArrayNamesEnum::DZ].Box().N() == 0, "");

    VERIFY(data.Arrays()[ArrayNamesEnum::DXV].Box().N() == 0, "");
    VERIFY(data.Arrays()[ArrayNamesEnum::DYV].Box().N() == 0, "");
    VERIFY(data.Arrays()[ArrayNamesEnum::DZV].Box().N() == 0, "");

    VERIFY(data.Arrays()[ArrayNamesEnum::COORD].Box().N() == 0, "");
    VERIFY(data.Arrays()[ArrayNamesEnum::ZCORN].Box().N() == 0, "");

    VERIFY(data.Arrays()[ArrayNamesEnum::ACTNUM].Box().N() == 0, "");

    VERIFY(data.Arrays()[ArrayNamesEnum::MULTPV].Box().N() == 0, "");

    VERIFY(data.Arrays()[ArrayNamesEnum::PERMX].Box().N() == data.Nx() * data.Ny() * data.Nz(), "");
    VERIFY(data.Arrays()[ArrayNamesEnum::PERMY].Box().N() == 0, "");
    VERIFY(data.Arrays()[ArrayNamesEnum::PERMZ].Box().N() == 0, "");

    VERIFY(data.Arrays()[ArrayNamesEnum::PORO].Box().N() == 0, "");
    VERIFY(data.Arrays()[ArrayNamesEnum::NTG].Box().N() == 0, "");
    VERIFY(data.Arrays()[ArrayNamesEnum::DZNET].Box().N() == 0, "");

    VERIFY(data.Arrays()[ArrayNamesEnum::MULTX].Box().N() == 0, "");
    VERIFY(data.Arrays()[ArrayNamesEnum::MULTY].Box().N() == 0, "");
    VERIFY(data.Arrays()[ArrayNamesEnum::MULTZ].Box().N() == 0, "");

    VERIFY(data.Arrays()[ArrayNamesEnum::MULTXm].Box().N() == 0, "");
    VERIFY(data.Arrays()[ArrayNamesEnum::MULTYm].Box().N() == 0, "");
    VERIFY(data.Arrays()[ArrayNamesEnum::MULTZm].Box().N() == 0, "");

    VERIFY(data.MINPV().isNull(), "");

    VERIFY(data.Arrays()[ArrayNamesEnum::MINPVV].Box().N() == 0, "");

    VERIFY(data.RSCONST().RS() == 0, "");
    VERIFY(data.RSCONST().PBub() == 0, "");

    VERIFY(data.RSCONSTT().size() == 0, "");

    VERIFY(data.PVTO().size() == data.TABDIMS().NTPVT(), "");
    VERIFY(data.PVCO().size() == 0, "");

    VERIFY(data.PMAX().PMax().isNull(), "");
    VERIFY(data.PMAX().PMaxComp().isNull(), "");
    VERIFY(data.PMAX().PMinComp().isNull(), "");
    VERIFY(data.PMAX().NumNodes().isNull(), "");

    VERIFY(data.PVCDO().size() == 0, "");
    VERIFY(data.PVDO().size() == 0, "");
    VERIFY(data.PVTW().size() == data.TABDIMS().NTPVT(), "");
    VERIFY(data.PVDG().size() == data.TABDIMS().NTPVT(), "");
    VERIFY(data.PVTG().size() == 0, "");

    VERIFY(data.ROCKOPTS().MAOTP().isNull(), "");
    VERIFY(data.ROCKOPTS().RPO().isNull(), "");
    VERIFY(data.ROCKOPTS().RegionOption().isNull(), "");
    VERIFY(data.ROCKOPTS().IHBOption().isNull(), "");

    VERIFY(data.ROCK().size() == data.TABDIMS().NTPVT(), "");
    VERIFY(data.DENSITY().size() == data.TABDIMS().NTPVT(), "");
    VERIFY(data.GRAVITY().size() == 0, "");

    VERIFY(data.SWOF().size() == data.TABDIMS().NTSFUN(), "");
    VERIFY(data.SGOF().size() == data.TABDIMS().NTSFUN(), "");
    VERIFY(data.SGWFN().size() == 0, "");
    VERIFY(data.SLGOF().size() == 0, "");
    VERIFY(data.SOF2().size() == 0, "");
    VERIFY(data.SOF3().size() == 0, "");
    VERIFY(data.SOF32D().size() == 0, "");
    VERIFY(data.SWFN().size() == 0, "");
    VERIFY(data.SGFN().size() == 0, "");
    VERIFY(data.SOMGAS().size() == 0, "");
    VERIFY(data.SOMWAT().size() == 0, "");

    VERIFY(data.Arrays()[ArrayNamesEnum::SWATINIT].Box().N() == 0, "");
    VERIFY(data.Arrays()[ArrayNamesEnum::SWCR].Box().N() == 0, "");
    VERIFY(data.Arrays()[ArrayNamesEnum::ISWCR].Box().N() == 0, "");
    VERIFY(data.Arrays()[ArrayNamesEnum::SWL].Box().N() == 0, "");
    VERIFY(data.Arrays()[ArrayNamesEnum::ISWL].Box().N() == 0, "");
    VERIFY(data.Arrays()[ArrayNamesEnum::SWLPC].Box().N() == 0, "");
    VERIFY(data.Arrays()[ArrayNamesEnum::ISWLPC].Box().N() == 0, "");
    VERIFY(data.Arrays()[ArrayNamesEnum::SWU].Box().N() == 0, "");
    VERIFY(data.Arrays()[ArrayNamesEnum::ISWU].Box().N() == 0, "");
    VERIFY(data.Arrays()[ArrayNamesEnum::SGCR].Box().N() == 0, "");
    VERIFY(data.Arrays()[ArrayNamesEnum::ISGCR].Box().N() == 0, "");
    VERIFY(data.Arrays()[ArrayNamesEnum::SGL].Box().N() == 0, "");
    VERIFY(data.Arrays()[ArrayNamesEnum::ISGL].Box().N() == 0, "");
    VERIFY(data.Arrays()[ArrayNamesEnum::SGLPC].Box().N() == 0, "");
    VERIFY(data.Arrays()[ArrayNamesEnum::ISGLPC].Box().N() == 0, "");
    VERIFY(data.Arrays()[ArrayNamesEnum::PCG].Box().N() == 0, "");
    VERIFY(data.Arrays()[ArrayNamesEnum::IPCG].Box().N() == 0, "");
    VERIFY(data.Arrays()[ArrayNamesEnum::PCW].Box().N() == 0, "");
    VERIFY(data.Arrays()[ArrayNamesEnum::IPCW].Box().N() == 0, "");

    VERIFY(data.PPCWMAX().size() == 0, "");

    VERIFY(data.Arrays()[ArrayNamesEnum::KRO].Box().N() == 0, "");
    VERIFY(data.Arrays()[ArrayNamesEnum::IKRO].Box().N() == 0, "");
    VERIFY(data.Arrays()[ArrayNamesEnum::KRORW].Box().N() == 0, "");
    VERIFY(data.Arrays()[ArrayNamesEnum::IKRORW].Box().N() == 0, "");
    VERIFY(data.Arrays()[ArrayNamesEnum::KRORG].Box().N() == 0, "");
    VERIFY(data.Arrays()[ArrayNamesEnum::IKRORG].Box().N() == 0, "");
    VERIFY(data.Arrays()[ArrayNamesEnum::KRW].Box().N() == 0, "");
    VERIFY(data.Arrays()[ArrayNamesEnum::IKRW].Box().N() == 0, "");
    VERIFY(data.Arrays()[ArrayNamesEnum::KRWR].Box().N() == 0, "");
    VERIFY(data.Arrays()[ArrayNamesEnum::IKRWR].Box().N() == 0, "");
    VERIFY(data.Arrays()[ArrayNamesEnum::KRG].Box().N() == 0, "");
    VERIFY(data.Arrays()[ArrayNamesEnum::IKRG].Box().N() == 0, "");
    VERIFY(data.Arrays()[ArrayNamesEnum::KRGR].Box().N() == 0, "");
    VERIFY(data.Arrays()[ArrayNamesEnum::IKRGR].Box().N() == 0, "");

    VERIFY(data.ENKRVD().size() == 0, "");
    VERIFY(data.ENPCVD().size() == 0, "");
    VERIFY(data.ENSPCVD().size() == 0, "");
    VERIFY(data.SCALELIM().size() == 0, "");

    VERIFY(data.SCALECRS().isNull(), "");

    VERIFY(data.SPECHEAT().size() == 0, "");
    VERIFY(data.SPECROCK().size() == 0, "");
    VERIFY(data.VISCREF().size() == 0, "");
    VERIFY(data.OILVISCT().size() == 0, "");
    VERIFY(data.WATVISCT().size() == 0, "");

    VERIFY(data.Arrays()[ArrayNamesEnum::PVTNUM].Box().N() == 0, "");
    VERIFY(data.Arrays()[ArrayNamesEnum::SATNUM].Box().N() == 0, "");
    VERIFY(data.Arrays()[ArrayNamesEnum::EQLNUM].Box().N() == 0, "");
    VERIFY(data.Arrays()[ArrayNamesEnum::ENDNUM].Box().N() == 0, "");

    VERIFY(data.EQUIL().size() == DefaultValues::EQLDIMS_NTEQUL, "");
    VERIFY(data.RSVD().size() == 0, "");
    VERIFY(data.PBVD().size() == DefaultValues::EQLDIMS_NTEQUL, "");
    VERIFY(data.PRVD().size() == 0, "");

    VERIFY(data.Arrays()[ArrayNamesEnum::PRESSURE].Box().N() == 0, "");
    VERIFY(data.Arrays()[ArrayNamesEnum::SWAT].Box().N() == 0, "");
    VERIFY(data.Arrays()[ArrayNamesEnum::SGAS].Box().N() == 0, "");
    VERIFY(data.Arrays()[ArrayNamesEnum::PBUB].Box().N() == 0, "");
    VERIFY(data.Arrays()[ArrayNamesEnum::RS].Box().N() == 0, "");

    VERIFY(data.AQUANCON().size() == 0, "");
    VERIFY(data.AQUFETP().size() == 0, "");

    VERIFY(data.DIMPES().DSTARG().isNull(), "");
    VERIFY(data.DIMPES().DSMAX().isNull(), "");
    VERIFY(data.DIMPES().DPMAX().isNull(), "");

    VERIFY(data.WELSPECS().size() > 0, "");
    VERIFY(data.COMPDAT().size() > 0, "");
    VERIFY(data.WCONPROD().size() > 0, "");
    VERIFY(data.WCONINJE().size() > 0, "");

    VERIFY(data.DATES().size() > 0, "");

    VERIFY(data.WCONHIST().size() == 0, "");
    VERIFY(data.WCONINJH().size() == 0, "");

    VERIFY(data.WELTARG().size() > 0, "");

    VERIFY(data.Arrays()[ArrayNamesEnum::DEPTH].Box().N() == 0, "");
    VERIFY(data.Arrays()[ArrayNamesEnum::PORV].Box().N() == 0, "");
    VERIFY(data.Arrays()[ArrayNamesEnum::TRANX].Box().N() == 0, "");
    VERIFY(data.Arrays()[ArrayNamesEnum::TRANY].Box().N() == 0, "");
    VERIFY(data.Arrays()[ArrayNamesEnum::TRANZ].Box().N() == 0, "");

    VERIFY(data.Operators().size() == 74, "");
}

void EclipseFileReaderTest::CheckFile2()
{
    EclipseFileReader reader;

    ProjectData data;

    reader.Load(data, "D:\\Workspace\\C#\\Projects\\WinForms\\BlackOil\\Data\\OPMKBTU_TEST01 - Weltarg — No MULTPV\\OPMKBTU_TEST01.DATA");

    VERIFY(data.Title() == "'OPTIMUM TEST FOR KBTU'", "");
    VERIFY(data.StartDate() == QDateTime(QDate(2007, 7, 1)), "");

    VERIFY(data.Unit() == UnitsEnum::METRIC, "");
    VERIFY(data.Model().isNull(), "");
    VERIFY(data.TemperatureOption().isNull(), "");

    VERIFY(data.NumRES().isNull(), "");
    VERIFY(data.Nx() == 83, "");
    VERIFY(data.Ny() == 91, "");
    VERIFY(data.Nz() == 33, "");

    VERIFY(data.TABDIMS().NTSFUN().isNull(), "");
    VERIFY(data.TABDIMS().NTPVT().isNull(), "");
    VERIFY(data.TABDIMS().NSSFUN().isNull(), "");

    VERIFY(data.EQLDIMS().NTEQUL() == 1, "");

    VERIFY(data.ENDSCALE().Directional().isNull(), "");
    VERIFY(data.ENDSCALE().Irreversible().isNull(), "");
    VERIFY(data.ENDSCALE().NTENDP().isNull(), "");
    VERIFY(data.ENDSCALE().MaxNodesEPD().isNull(), "");

    VERIFY(data.Arrays()[ArrayNamesEnum::TOPS].Box().N() == 0, "");

    VERIFY(data.Arrays()[ArrayNamesEnum::DX].Box().N() == 0, "");
    VERIFY(data.Arrays()[ArrayNamesEnum::DY].Box().N() == 0, "");
    VERIFY(data.Arrays()[ArrayNamesEnum::DZ].Box().N() == 0, "");

    VERIFY(data.Arrays()[ArrayNamesEnum::DXV].Box().N() == 0, "");
    VERIFY(data.Arrays()[ArrayNamesEnum::DYV].Box().N() == 0, "");
    VERIFY(data.Arrays()[ArrayNamesEnum::DZV].Box().N() == 0, "");

    VERIFY(data.Arrays()[ArrayNamesEnum::COORD].Box().N() == 6*(data.Nx()+1)*(data.Ny()+1), "");
    VERIFY(data.Arrays()[ArrayNamesEnum::ZCORN].Box().N() == 8*data.Nx()*data.Ny()*data.Nz(), "");

    VERIFY(data.Arrays()[ArrayNamesEnum::ACTNUM].Box().N() == data.Nx() * data.Ny() * data.Nz(), "");

    VERIFY(data.Arrays()[ArrayNamesEnum::MULTPV].Box().N() == data.Nx() * data.Ny() * data.Nz(), "");

    VERIFY(data.Arrays()[ArrayNamesEnum::PERMX].Box().N() == data.Nx() * data.Ny() * data.Nz(), "");
    VERIFY(data.Arrays()[ArrayNamesEnum::PERMY].Box().N() == data.Nx() * data.Ny() * data.Nz(), "");
    VERIFY(data.Arrays()[ArrayNamesEnum::PERMZ].Box().N() == data.Nx() * data.Ny() * data.Nz(), "");

    VERIFY(data.Arrays()[ArrayNamesEnum::PORO].Box().N() == data.Nx() * data.Ny() * data.Nz(), "");
    VERIFY(data.Arrays()[ArrayNamesEnum::NTG].Box().N() == data.Nx() * data.Ny() * data.Nz(), "");
    VERIFY(data.Arrays()[ArrayNamesEnum::DZNET].Box().N() == 0, "");

    VERIFY(data.Arrays()[ArrayNamesEnum::MULTX].Box().N() == 0, "");
    VERIFY(data.Arrays()[ArrayNamesEnum::MULTY].Box().N() == 0, "");
    VERIFY(data.Arrays()[ArrayNamesEnum::MULTZ].Box().N() == 0, "");

    VERIFY(data.Arrays()[ArrayNamesEnum::MULTXm].Box().N() == 0, "");
    VERIFY(data.Arrays()[ArrayNamesEnum::MULTYm].Box().N() == 0, "");
    VERIFY(data.Arrays()[ArrayNamesEnum::MULTZm].Box().N() == 0, "");

    VERIFY(data.MINPV().isNull(), "");

    VERIFY(data.Arrays()[ArrayNamesEnum::MINPVV].Box().N() == 0, "");

    VERIFY(data.RSCONST().RS() == 0, "");
    VERIFY(data.RSCONST().PBub() == 0, "");

    VERIFY(data.RSCONSTT().size() == 1, "");

    VERIFY(data.PVTO().size() == 0, "");
    VERIFY(data.PVCO().size() == 0, "");

    VERIFY(data.PMAX().PMax().isNull(), "");
    VERIFY(data.PMAX().PMaxComp().isNull(), "");
    VERIFY(data.PMAX().PMinComp().isNull(), "");
    VERIFY(data.PMAX().NumNodes().isNull(), "");

    VERIFY(data.PVCDO().size() == 0, "");
    VERIFY(data.PVDO().size() == DefaultValues::TABDIMS_NTPVT, "");
    VERIFY(data.PVTW().size() == DefaultValues::TABDIMS_NTPVT, "");
    VERIFY(data.PVDG().size() == 0, "");
    VERIFY(data.PVTG().size() == 0, "");

    VERIFY(data.ROCKOPTS().MAOTP().isNull(), "");
    VERIFY(data.ROCKOPTS().RPO().isNull(), "");
    VERIFY(data.ROCKOPTS().RegionOption() == RegionOptionsEnum::PVTNUM, "");
    VERIFY(data.ROCKOPTS().IHBOption().isNull(), "");

    VERIFY(data.ROCK().size() == DefaultValues::TABDIMS_NTPVT, "");
    VERIFY(data.DENSITY().size() == DefaultValues::TABDIMS_NTPVT, "");
    VERIFY(data.GRAVITY().size() == 0, "");

    VERIFY(data.SWOF().size() == DefaultValues::TABDIMS_NTSFUN, "");
    VERIFY(data.SGOF().size() == 0, "");
    VERIFY(data.SGWFN().size() == 0, "");
    VERIFY(data.SLGOF().size() == 0, "");
    VERIFY(data.SOF2().size() == 0, "");
    VERIFY(data.SOF3().size() == 0, "");
    VERIFY(data.SOF32D().size() == 0, "");
    VERIFY(data.SWFN().size() == 0, "");
    VERIFY(data.SGFN().size() == 0, "");
    VERIFY(data.SOMGAS().size() == 0, "");
    VERIFY(data.SOMWAT().size() == 0, "");

    VERIFY(data.Arrays()[ArrayNamesEnum::SWATINIT].Box().N() == 0, "");
    VERIFY(data.Arrays()[ArrayNamesEnum::SWCR].Box().N() == 0, "");
    VERIFY(data.Arrays()[ArrayNamesEnum::ISWCR].Box().N() == 0, "");
    VERIFY(data.Arrays()[ArrayNamesEnum::SWL].Box().N() == 0, "");
    VERIFY(data.Arrays()[ArrayNamesEnum::ISWL].Box().N() == 0, "");
    VERIFY(data.Arrays()[ArrayNamesEnum::SWLPC].Box().N() == 0, "");
    VERIFY(data.Arrays()[ArrayNamesEnum::ISWLPC].Box().N() == 0, "");
    VERIFY(data.Arrays()[ArrayNamesEnum::SWU].Box().N() == 0, "");
    VERIFY(data.Arrays()[ArrayNamesEnum::ISWU].Box().N() == 0, "");
    VERIFY(data.Arrays()[ArrayNamesEnum::SGCR].Box().N() == 0, "");
    VERIFY(data.Arrays()[ArrayNamesEnum::ISGCR].Box().N() == 0, "");
    VERIFY(data.Arrays()[ArrayNamesEnum::SGL].Box().N() == 0, "");
    VERIFY(data.Arrays()[ArrayNamesEnum::ISGL].Box().N() == 0, "");
    VERIFY(data.Arrays()[ArrayNamesEnum::SGLPC].Box().N() == 0, "");
    VERIFY(data.Arrays()[ArrayNamesEnum::ISGLPC].Box().N() == 0, "");
    VERIFY(data.Arrays()[ArrayNamesEnum::PCG].Box().N() == 0, "");
    VERIFY(data.Arrays()[ArrayNamesEnum::IPCG].Box().N() == 0, "");
    VERIFY(data.Arrays()[ArrayNamesEnum::PCW].Box().N() == 0, "");
    VERIFY(data.Arrays()[ArrayNamesEnum::IPCW].Box().N() == 0, "");

    VERIFY(data.PPCWMAX().size() == 0, "");

    VERIFY(data.Arrays()[ArrayNamesEnum::KRO].Box().N() == 0, "");
    VERIFY(data.Arrays()[ArrayNamesEnum::IKRO].Box().N() == 0, "");
    VERIFY(data.Arrays()[ArrayNamesEnum::KRORW].Box().N() == 0, "");
    VERIFY(data.Arrays()[ArrayNamesEnum::IKRORW].Box().N() == 0, "");
    VERIFY(data.Arrays()[ArrayNamesEnum::KRORG].Box().N() == 0, "");
    VERIFY(data.Arrays()[ArrayNamesEnum::IKRORG].Box().N() == 0, "");
    VERIFY(data.Arrays()[ArrayNamesEnum::KRW].Box().N() == 0, "");
    VERIFY(data.Arrays()[ArrayNamesEnum::IKRW].Box().N() == 0, "");
    VERIFY(data.Arrays()[ArrayNamesEnum::KRWR].Box().N() == 0, "");
    VERIFY(data.Arrays()[ArrayNamesEnum::IKRWR].Box().N() == 0, "");
    VERIFY(data.Arrays()[ArrayNamesEnum::KRG].Box().N() == 0, "");
    VERIFY(data.Arrays()[ArrayNamesEnum::IKRG].Box().N() == 0, "");
    VERIFY(data.Arrays()[ArrayNamesEnum::KRGR].Box().N() == 0, "");
    VERIFY(data.Arrays()[ArrayNamesEnum::IKRGR].Box().N() == 0, "");

    VERIFY(data.ENKRVD().size() == 0, "");
    VERIFY(data.ENPCVD().size() == 0, "");
    VERIFY(data.ENSPCVD().size() == 0, "");
    VERIFY(data.SCALELIM().size() == 0, "");

    VERIFY(data.SCALECRS() == true, "");

    VERIFY(data.SPECHEAT().size() == 0, "");
    VERIFY(data.SPECROCK().size() == 0, "");
    VERIFY(data.VISCREF().size() == 0, "");
    VERIFY(data.OILVISCT().size() == 0, "");
    VERIFY(data.WATVISCT().size() == 0, "");

    VERIFY(data.Arrays()[ArrayNamesEnum::PVTNUM].Box().N() == data.Nx() * data.Ny() * data.Nz(), "");
    VERIFY(data.Arrays()[ArrayNamesEnum::SATNUM].Box().N() == data.Nx() * data.Ny() * data.Nz(), "");
    VERIFY(data.Arrays()[ArrayNamesEnum::EQLNUM].Box().N() == data.Nx() * data.Ny() * data.Nz(), "");
    VERIFY(data.Arrays()[ArrayNamesEnum::ENDNUM].Box().N() == 0, "");

    VERIFY(data.EQUIL().size() == DefaultValues::EQLDIMS_NTEQUL, "");
    VERIFY(data.RSVD().size() == 0, "");
    VERIFY(data.PBVD().size() == 0, "");
    VERIFY(data.PRVD().size() == 0, "");

    VERIFY(data.Arrays()[ArrayNamesEnum::PRESSURE].Box().N() == 0, "");
    VERIFY(data.Arrays()[ArrayNamesEnum::SWAT].Box().N() == 0, "");
    VERIFY(data.Arrays()[ArrayNamesEnum::SGAS].Box().N() == 0, "");
    VERIFY(data.Arrays()[ArrayNamesEnum::PBUB].Box().N() == 0, "");
    VERIFY(data.Arrays()[ArrayNamesEnum::RS].Box().N() == 0, "");

    VERIFY(data.AQUANCON().size() == 0, "");
    VERIFY(data.AQUFETP().size() == 0, "");

    VERIFY(data.DIMPES().DSTARG().isNull(), "");
    VERIFY(data.DIMPES().DSMAX().isNull(), "");
    VERIFY(data.DIMPES().DPMAX().isNull(), "");

    VERIFY(data.WELSPECS().size() > 0, "");
    VERIFY(data.COMPDAT().size() > 0, "");
    VERIFY(data.WCONPROD().size() == 0, "");
    VERIFY(data.WCONINJE().size() == 0, "");

    VERIFY(data.DATES().size() > 0, "");

    VERIFY(data.WCONHIST().size() > 0, "");
    VERIFY(data.WCONINJH().size() == 0, "");

    VERIFY(data.WELTARG().size() > 0, "");

    VERIFY(data.Arrays()[ArrayNamesEnum::DEPTH].Box().N() == 0, "");
    VERIFY(data.Arrays()[ArrayNamesEnum::PORV].Box().N() == 0, "");
    VERIFY(data.Arrays()[ArrayNamesEnum::TRANX].Box().N() == 0, "");
    VERIFY(data.Arrays()[ArrayNamesEnum::TRANY].Box().N() == 0, "");
    VERIFY(data.Arrays()[ArrayNamesEnum::TRANZ].Box().N() == 0, "");

    VERIFY(data.Operators().size() == 0, "");
}

}}}}
