#include "projectdatatest.h"

namespace BlackOil {
namespace Test {
namespace Data {
namespace Project {

ProjectDataTest::ProjectDataTest(QObject *parent) : QObject(parent) { }

void ProjectDataTest::CheckVariables()
{
    // Construct object
    ProjectData data;

    VERIFY(data.Title().compare("") == 0, "");
    VERIFY(data.StartDate().date() == QDate::currentDate(), "");

    VERIFY(data.DATES().size() == 0, "");

    VERIFY(data.Unit().isNull(), "");
    VERIFY(data.Model().isNull(), "");
    VERIFY(data.TemperatureOption().isNull(), "");

    VERIFY(data.NumRES().isNull(), "");
    VERIFY(data.Nx() == 0, "");
    VERIFY(data.Ny() == 0, "");
    VERIFY(data.Nz() == 0, "");

    VERIFY(data.TABDIMS().NTSFUN().isNull(), "");
    VERIFY(data.TABDIMS().NTPVT().isNull(), "");
    VERIFY(data.TABDIMS().NSSFUN().isNull(), "");

    VERIFY(data.EQLDIMS().NTEQUL().isNull(), "");

    VERIFY(data.ENDSCALE().Directional().isNull(), "");
    VERIFY(data.ENDSCALE().Irreversible().isNull(), "");
    VERIFY(data.ENDSCALE().NTENDP().isNull(), "");
    VERIFY(data.ENDSCALE().MaxNodesEPD().isNull(), "");

    VERIFY(data.Arrays()[ArrayNamesEnum::TOPS].Box().Belongs(Box()), "");

    VERIFY(data.Arrays()[ArrayNamesEnum::DX].Box().Belongs(Box()), "");
    VERIFY(data.Arrays()[ArrayNamesEnum::DY].Box().Belongs(Box()), "");
    VERIFY(data.Arrays()[ArrayNamesEnum::DZ].Box().Belongs(Box()), "");

    VERIFY(data.Arrays()[ArrayNamesEnum::DXV].Box().Belongs(Box()), "");
    VERIFY(data.Arrays()[ArrayNamesEnum::DYV].Box().Belongs(Box()), "");
    VERIFY(data.Arrays()[ArrayNamesEnum::DZV].Box().Belongs(Box()), "");

    VERIFY(data.Arrays()[ArrayNamesEnum::COORD].Box().Belongs(Box()), "");
    VERIFY(data.Arrays()[ArrayNamesEnum::ZCORN].Box().Belongs(Box()), "");

    VERIFY(data.Arrays()[ArrayNamesEnum::ACTNUM].Box().Belongs(Box()), "");
    VERIFY(data.Arrays()[ArrayNamesEnum::MULTPV].Box().Belongs(Box()), "");

    VERIFY(data.Arrays()[ArrayNamesEnum::PERMX].Box().Belongs(Box()), "");
    VERIFY(data.Arrays()[ArrayNamesEnum::PERMY].Box().Belongs(Box()), "");
    VERIFY(data.Arrays()[ArrayNamesEnum::PERMZ].Box().Belongs(Box()), "");

    VERIFY(data.Arrays()[ArrayNamesEnum::PORO].Box().Belongs(Box()), "");
    VERIFY(data.Arrays()[ArrayNamesEnum::NTG].Box().Belongs(Box()), "");
    VERIFY(data.Arrays()[ArrayNamesEnum::DZNET].Box().Belongs(Box()), "");

    VERIFY(data.Arrays()[ArrayNamesEnum::MULTX].Box().Belongs(Box()), "");
    VERIFY(data.Arrays()[ArrayNamesEnum::MULTY].Box().Belongs(Box()), "");
    VERIFY(data.Arrays()[ArrayNamesEnum::MULTZ].Box().Belongs(Box()), "");

    VERIFY(data.Arrays()[ArrayNamesEnum::MULTXm].Box().Belongs(Box()), "");
    VERIFY(data.Arrays()[ArrayNamesEnum::MULTYm].Box().Belongs(Box()), "");
    VERIFY(data.Arrays()[ArrayNamesEnum::MULTZm].Box().Belongs(Box()), "");

    VERIFY(data.Arrays()[ArrayNamesEnum::MINPVV].Box().Belongs(Box()), "");

    VERIFY(data.MINPV().isNull(), "");

    VERIFY(data.RSCONST().RS() == 0, "");
    VERIFY(data.RSCONST().PBub() ==  0, "");

    VERIFY(data.RSCONSTT().size() == 0, "");

    VERIFY(data.PVTO().size() == 0, "");
    VERIFY(data.PVCO().size() == 0, "");

    VERIFY(data.PMAX().PMax().isNull(), "");
    VERIFY(data.PMAX().NumNodes().isNull(), "");
    VERIFY(data.PMAX().PMaxComp().isNull(), "");
    VERIFY(data.PMAX().PMinComp().isNull(), "");

    VERIFY(data.PVCDO().size() == 0, "");

    VERIFY(data.PVDO().size() == 0, "");

    VERIFY(data.PVTW().size() == 0, "");

    VERIFY(data.PVDG().size() == 0, "");
    VERIFY(data.PVTG().size() == 0, "");

    VERIFY(data.ROCKOPTS().RPO().isNull(), "");
    VERIFY(data.ROCKOPTS().MAOTP().isNull(), "");
    VERIFY(data.ROCKOPTS().IHBOption().isNull(), "");
    VERIFY(data.ROCKOPTS().RegionOption().isNull(), "");

    VERIFY(data.ROCK().size() == 0, "");
    VERIFY(data.DENSITY().size() == 0, "");
    VERIFY(data.GRAVITY().size() == 0, "");

    VERIFY(data.SWOF().size() == 0, "");
    VERIFY(data.SGOF().size() == 0, "");
    VERIFY(data.SGWFN().size() == 0, "");
    VERIFY(data.SLGOF().size() == 0, "");
    VERIFY(data.SOF2().size() == 0, "");
    VERIFY(data.SOF3().size() == 0, "");

    VERIFY(data.SOF32D().size() == 0, "");

    VERIFY(data.SWFN().size() == 0, "");
    VERIFY(data.SGFN().size() == 0, "");
    VERIFY(data.SOMWAT().size() == 0, "");
    VERIFY(data.SOMGAS().size() == 0, "");

    VERIFY(data.Arrays()[ArrayNamesEnum::SWATINIT].Box().Belongs(Box()), "");
    VERIFY(data.Arrays()[ArrayNamesEnum::SWCR].Box().Belongs(Box()), "");
    VERIFY(data.Arrays()[ArrayNamesEnum::ISWCR].Box().Belongs(Box()), "");
    VERIFY(data.Arrays()[ArrayNamesEnum::SWL].Box().Belongs(Box()), "");
    VERIFY(data.Arrays()[ArrayNamesEnum::ISWL].Box().Belongs(Box()), "");
    VERIFY(data.Arrays()[ArrayNamesEnum::SWLPC].Box().Belongs(Box()), "");
    VERIFY(data.Arrays()[ArrayNamesEnum::ISWLPC].Box().Belongs(Box()), "");
    VERIFY(data.Arrays()[ArrayNamesEnum::SWU].Box().Belongs(Box()), "");
    VERIFY(data.Arrays()[ArrayNamesEnum::ISWU].Box().Belongs(Box()), "");
    VERIFY(data.Arrays()[ArrayNamesEnum::SGCR].Box().Belongs(Box()), "");
    VERIFY(data.Arrays()[ArrayNamesEnum::ISGCR].Box().Belongs(Box()), "");
    VERIFY(data.Arrays()[ArrayNamesEnum::SGL].Box().Belongs(Box()), "");
    VERIFY(data.Arrays()[ArrayNamesEnum::ISGL].Box().Belongs(Box()), "");
    VERIFY(data.Arrays()[ArrayNamesEnum::SGLPC].Box().Belongs(Box()), "");
    VERIFY(data.Arrays()[ArrayNamesEnum::ISGLPC].Box().Belongs(Box()), "");
    VERIFY(data.Arrays()[ArrayNamesEnum::PCG].Box().Belongs(Box()), "");
    VERIFY(data.Arrays()[ArrayNamesEnum::IPCG].Box().Belongs(Box()), "");
    VERIFY(data.Arrays()[ArrayNamesEnum::PCW].Box().Belongs(Box()), "");
    VERIFY(data.Arrays()[ArrayNamesEnum::IPCW].Box().Belongs(Box()), "");

    VERIFY(data.PPCWMAX().size() == 0, "");

    VERIFY(data.Arrays()[ArrayNamesEnum::KRO].Box().Belongs(Box()), "");
    VERIFY(data.Arrays()[ArrayNamesEnum::IKRO].Box().Belongs(Box()), "");
    VERIFY(data.Arrays()[ArrayNamesEnum::KRORW].Box().Belongs(Box()), "");
    VERIFY(data.Arrays()[ArrayNamesEnum::IKRORW].Box().Belongs(Box()), "");
    VERIFY(data.Arrays()[ArrayNamesEnum::KRORG].Box().Belongs(Box()), "");
    VERIFY(data.Arrays()[ArrayNamesEnum::IKRORG].Box().Belongs(Box()), "");
    VERIFY(data.Arrays()[ArrayNamesEnum::KRW].Box().Belongs(Box()), "");
    VERIFY(data.Arrays()[ArrayNamesEnum::IKRW].Box().Belongs(Box()), "");
    VERIFY(data.Arrays()[ArrayNamesEnum::KRWR].Box().Belongs(Box()), "");
    VERIFY(data.Arrays()[ArrayNamesEnum::IKRWR].Box().Belongs(Box()), "");
    VERIFY(data.Arrays()[ArrayNamesEnum::KRG].Box().Belongs(Box()), "");
    VERIFY(data.Arrays()[ArrayNamesEnum::IKRG].Box().Belongs(Box()), "");
    VERIFY(data.Arrays()[ArrayNamesEnum::KRGR].Box().Belongs(Box()), "");
    VERIFY(data.Arrays()[ArrayNamesEnum::IKRGR].Box().Belongs(Box()), "");

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

    VERIFY(data.Arrays()[ArrayNamesEnum::PVTNUM].Box().Belongs(Box()), "");
    VERIFY(data.Arrays()[ArrayNamesEnum::SATNUM].Box().Belongs(Box()), "");
    VERIFY(data.Arrays()[ArrayNamesEnum::EQLNUM].Box().Belongs(Box()), "");
    VERIFY(data.Arrays()[ArrayNamesEnum::ENDNUM].Box().Belongs(Box()), "");

    VERIFY(data.EQUIL().size() == 0, "");

    VERIFY(data.RSVD().size() == 0, "");
    VERIFY(data.PBVD().size() == 0, "");
    VERIFY(data.PRVD().size() == 0, "");

    VERIFY(data.Arrays()[ArrayNamesEnum::PRESSURE].Box().Belongs(Box()), "");
    VERIFY(data.Arrays()[ArrayNamesEnum::SWAT].Box().Belongs(Box()), "");
    VERIFY(data.Arrays()[ArrayNamesEnum::SOIL].Box().Belongs(Box()), "");
    VERIFY(data.Arrays()[ArrayNamesEnum::SGAS].Box().Belongs(Box()), "");
    VERIFY(data.Arrays()[ArrayNamesEnum::PBUB].Box().Belongs(Box()), "");
    VERIFY(data.Arrays()[ArrayNamesEnum::RS].Box().Belongs(Box()), "");

    VERIFY(data.AQUANCON().size() == 0, "");
    VERIFY(data.AQUFETP().size() == 0, "");

    VERIFY(data.DIMPES().DSTARG().isNull(), "");
    VERIFY(data.DIMPES().DSMAX().isNull(), "");
    VERIFY(data.DIMPES().DPMAX().isNull(), "");

    VERIFY(data.WELSPECS().size() == 0, "");
    VERIFY(data.COMPDAT().size() == 0, "");
    VERIFY(data.WCONPROD().size() == 0, "");
    VERIFY(data.WCONINJE().size() == 0, "");
    VERIFY(data.WCONHIST().size() == 0, "");
    VERIFY(data.WCONINJH().size() == 0, "");
    VERIFY(data.WELTARG().size() == 0, "");

    VERIFY(data.Operators().size() == 0, "");

    VERIFY(data.Arrays()[ArrayNamesEnum::DEPTH].Box().Belongs(Box()), "");
    VERIFY(data.Arrays()[ArrayNamesEnum::PORV].Box().Belongs(Box()), "");
    VERIFY(data.Arrays()[ArrayNamesEnum::TRANX].Box().Belongs(Box()), "");
    VERIFY(data.Arrays()[ArrayNamesEnum::TRANY].Box().Belongs(Box()), "");
    VERIFY(data.Arrays()[ArrayNamesEnum::TRANZ].Box().Belongs(Box()), "");

    // Setting values to object
    data.SetTitle("Test");
    data.SetStartDate(QDateTime::fromString("03.06.2020", "dd.MM.yyyy"));

    data.DATES().push_back(QDateTime::fromString("03.06.2020"));

    data.SetUnit(UnitsEnum::LAB);
    data.SetModel(ModelsEnum::ThreePhase);
    data.SetTemperatureOption(false);

    data.SetNumRES(23);
    data.SetNx(1);
    data.SetNy(1);
    data.SetNz(1);

    data.TABDIMS().SetNTSFUN(1);
    data.TABDIMS().SetNTPVT(1);
    data.TABDIMS().SetNSSFUN(1);

    data.EQLDIMS().SetNTEQUL(1);

    data.ENDSCALE().SetDirectional(DirectionalEnum::DIRECT);
    data.ENDSCALE().SetIrreversible(IrreversibleEnum::REVERS);
    data.ENDSCALE().SetNTENDP(1);
    data.ENDSCALE().SetMaxNodesEPD(5);

    data.Arrays()[ArrayNamesEnum::TOPS].SetBox(Box(0, 0, 0, 0, 0, 0));

    data.Arrays()[ArrayNamesEnum::DX].SetBox(Box(0, 0, 0, 0, 0, 0));
    data.Arrays()[ArrayNamesEnum::DY].SetBox(Box(0, 0, 0, 0, 0, 0));
    data.Arrays()[ArrayNamesEnum::DZ].SetBox(Box(0, 0, 0, 0, 0, 0));

    data.Arrays()[ArrayNamesEnum::DXV].SetBox(Box(0, 0, 0, 0, 0, 0));
    data.Arrays()[ArrayNamesEnum::DYV].SetBox(Box(0, 0, 0, 0, 0, 0));
    data.Arrays()[ArrayNamesEnum::DZV].SetBox(Box(0, 0, 0, 0, 0, 0));

    data.Arrays()[ArrayNamesEnum::COORD].SetBox(Box(0, 0, 0, 0, 0, 0));
    data.Arrays()[ArrayNamesEnum::ZCORN].SetBox(Box(0, 0, 0, 0, 0, 0));

    data.Arrays()[ArrayNamesEnum::ACTNUM].SetBox(Box(0, 0, 0, 0, 0, 0));
    data.Arrays()[ArrayNamesEnum::MULTPV].SetBox(Box(0, 0, 0, 0, 0, 0));

    data.Arrays()[ArrayNamesEnum::PERMX].SetBox(Box(0, 0, 0, 0, 0, 0));
    data.Arrays()[ArrayNamesEnum::PERMY].SetBox(Box(0, 0, 0, 0, 0, 0));
    data.Arrays()[ArrayNamesEnum::PERMZ].SetBox(Box(0, 0, 0, 0, 0, 0));

    data.Arrays()[ArrayNamesEnum::PORO].SetBox(Box(0, 0, 0, 0, 0, 0));
    data.Arrays()[ArrayNamesEnum::NTG].SetBox(Box(0, 0, 0, 0, 0, 0));
    data.Arrays()[ArrayNamesEnum::DZNET].SetBox(Box(0, 0, 0, 0, 0, 0));

    data.Arrays()[ArrayNamesEnum::MULTX].SetBox(Box(0, 0, 0, 0, 0, 0));
    data.Arrays()[ArrayNamesEnum::MULTY].SetBox(Box(0, 0, 0, 0, 0, 0));
    data.Arrays()[ArrayNamesEnum::MULTZ].SetBox(Box(0, 0, 0, 0, 0, 0));

    data.Arrays()[ArrayNamesEnum::MULTXm].SetBox(Box(0, 0, 0, 0, 0, 0));
    data.Arrays()[ArrayNamesEnum::MULTYm].SetBox(Box(0, 0, 0, 0, 0, 0));
    data.Arrays()[ArrayNamesEnum::MULTZm].SetBox(Box(0, 0, 0, 0, 0, 0));

    data.Arrays()[ArrayNamesEnum::MINPVV].SetBox(Box(0, 0, 0, 0, 0, 0));

    data.SetMINPV(1);

    data.RSCONST().SetRS(1);
    data.RSCONST().SetPBub(1);

    data.RSCONSTT().push_back(RSCONSTData());

    data.PVTO().resize(5);
    data.PVCO().resize(5);

    data.PMAX().SetPMax(1);
    data.PMAX().SetNumNodes(1);
    data.PMAX().SetPMaxComp(1);
    data.PMAX().SetPMinComp(1);

    data.PVCDO().resize(5);

    data.PVDO().resize(5);

    data.PVTW().resize(5);

    data.PVDG().resize(5);
    data.PVTG().resize(5);

    data.ROCKOPTS().SetRPO(ReferencePressureOptionsEnum::STORE);
    data.ROCKOPTS().SetMAOTP(MAOTPOptionsEnum::STRESS);
    data.ROCKOPTS().SetIHBOption(IHBOptionsEnum::ELASTIC);
    data.ROCKOPTS().SetRegionOption(RegionOptionsEnum::PVTNUM);

    data.ROCK().resize(5);
    data.DENSITY().resize(5);
    data.GRAVITY().resize(5);

    data.SWOF().resize(5);
    data.SGOF().resize(5);
    data.SGWFN().resize(5);
    data.SLGOF().resize(5);
    data.SOF2().resize(5);
    data.SOF3().resize(5);

    data.SOF32D().resize(5);

    data.SWFN().resize(5);
    data.SGFN().resize(5);
    data.SOMWAT().resize(5);
    data.SOMGAS().resize(5);

    data.Arrays()[ArrayNamesEnum::SWATINIT].SetBox(Box(0, 0, 0, 0, 0, 0));
    data.Arrays()[ArrayNamesEnum::SWCR].SetBox(Box(0, 0, 0, 0, 0, 0));
    data.Arrays()[ArrayNamesEnum::ISWCR].SetBox(Box(0, 0, 0, 0, 0, 0));
    data.Arrays()[ArrayNamesEnum::SWL].SetBox(Box(0, 0, 0, 0, 0, 0));
    data.Arrays()[ArrayNamesEnum::ISWL].SetBox(Box(0, 0, 0, 0, 0, 0));
    data.Arrays()[ArrayNamesEnum::SWLPC].SetBox(Box(0, 0, 0, 0, 0, 0));
    data.Arrays()[ArrayNamesEnum::ISWLPC].SetBox(Box(0, 0, 0, 0, 0, 0));
    data.Arrays()[ArrayNamesEnum::SWU].SetBox(Box(0, 0, 0, 0, 0, 0));
    data.Arrays()[ArrayNamesEnum::ISWU].SetBox(Box(0, 0, 0, 0, 0, 0));
    data.Arrays()[ArrayNamesEnum::SGCR].SetBox(Box(0, 0, 0, 0, 0, 0));
    data.Arrays()[ArrayNamesEnum::ISGCR].SetBox(Box(0, 0, 0, 0, 0, 0));
    data.Arrays()[ArrayNamesEnum::SGL].SetBox(Box(0, 0, 0, 0, 0, 0));
    data.Arrays()[ArrayNamesEnum::ISGL].SetBox(Box(0, 0, 0, 0, 0, 0));
    data.Arrays()[ArrayNamesEnum::SGLPC].SetBox(Box(0, 0, 0, 0, 0, 0));
    data.Arrays()[ArrayNamesEnum::ISGLPC].SetBox(Box(0, 0, 0, 0, 0, 0));
    data.Arrays()[ArrayNamesEnum::PCG].SetBox(Box(0, 0, 0, 0, 0, 0));
    data.Arrays()[ArrayNamesEnum::IPCG].SetBox(Box(0, 0, 0, 0, 0, 0));
    data.Arrays()[ArrayNamesEnum::PCW].SetBox(Box(0, 0, 0, 0, 0, 0));
    data.Arrays()[ArrayNamesEnum::IPCW].SetBox(Box(0, 0, 0, 0, 0, 0));

    data.PPCWMAX().resize(5);

    data.Arrays()[ArrayNamesEnum::KRO].SetBox(Box(0, 0, 0, 0, 0, 0));
    data.Arrays()[ArrayNamesEnum::IKRO].SetBox(Box(0, 0, 0, 0, 0, 0));
    data.Arrays()[ArrayNamesEnum::KRORW].SetBox(Box(0, 0, 0, 0, 0, 0));
    data.Arrays()[ArrayNamesEnum::IKRORW].SetBox(Box(0, 0, 0, 0, 0, 0));
    data.Arrays()[ArrayNamesEnum::KRORG].SetBox(Box(0, 0, 0, 0, 0, 0));
    data.Arrays()[ArrayNamesEnum::IKRORG].SetBox(Box(0, 0, 0, 0, 0, 0));
    data.Arrays()[ArrayNamesEnum::KRW].SetBox(Box(0, 0, 0, 0, 0, 0));
    data.Arrays()[ArrayNamesEnum::IKRW].SetBox(Box(0, 0, 0, 0, 0, 0));
    data.Arrays()[ArrayNamesEnum::KRWR].SetBox(Box(0, 0, 0, 0, 0, 0));
    data.Arrays()[ArrayNamesEnum::IKRWR].SetBox(Box(0, 0, 0, 0, 0, 0));
    data.Arrays()[ArrayNamesEnum::KRG].SetBox(Box(0, 0, 0, 0, 0, 0));
    data.Arrays()[ArrayNamesEnum::IKRG].SetBox(Box(0, 0, 0, 0, 0, 0));
    data.Arrays()[ArrayNamesEnum::KRGR].SetBox(Box(0, 0, 0, 0, 0, 0));
    data.Arrays()[ArrayNamesEnum::IKRGR].SetBox(Box(0, 0, 0, 0, 0, 0));

    data.ENKRVD().resize(5);
    data.ENPCVD().resize(5);
    data.ENSPCVD().resize(5);

    data.SCALELIM().resize(5);

    data.SetSCALECRS(1);

    data.SPECHEAT().resize(5);
    data.SPECROCK().resize(5);

    data.VISCREF().resize(5);

    data.OILVISCT().resize(5);
    data.WATVISCT().resize(5);

    data.Arrays()[ArrayNamesEnum::PVTNUM].SetBox(Box(0, 0, 0, 0, 0, 0));
    data.Arrays()[ArrayNamesEnum::SATNUM].SetBox(Box(0, 0, 0, 0, 0, 0));
    data.Arrays()[ArrayNamesEnum::EQLNUM].SetBox(Box(0, 0, 0, 0, 0, 0));
    data.Arrays()[ArrayNamesEnum::ENDNUM].SetBox(Box(0, 0, 0, 0, 0, 0));

    data.EQUIL().resize(5);

    data.RSVD().resize(5);
    data.PBVD().resize(5);
    data.PRVD().resize(5);

    data.Arrays()[ArrayNamesEnum::PRESSURE].SetBox(Box(0, 0, 0, 0, 0, 0));
    data.Arrays()[ArrayNamesEnum::SWAT].SetBox(Box(0, 0, 0, 0, 0, 0));
    data.Arrays()[ArrayNamesEnum::SGAS].SetBox(Box(0, 0, 0, 0, 0, 0));
    data.Arrays()[ArrayNamesEnum::SOIL].SetBox(Box(0, 0, 0, 0, 0, 0));
    data.Arrays()[ArrayNamesEnum::PBUB].SetBox(Box(0, 0, 0, 0, 0, 0));
    data.Arrays()[ArrayNamesEnum::RS].SetBox(Box(0, 0, 0, 0, 0, 0));

    data.AQUANCON().resize(5);
    data.AQUFETP().resize(5);

    data.DIMPES().SetDSTARG(1);
    data.DIMPES().SetDSMAX(1);
    data.DIMPES().SetDPMAX(1);

    data.WELSPECS().resize(5);
    data.COMPDAT().resize(5);
    data.WCONPROD().resize(5);
    data.WCONINJE().resize(5);
    data.WCONHIST().resize(5);
    data.WCONINJH().resize(5);
    data.WELTARG().resize(5);

    data.Operators().push_back(OperatorData());

    data.Arrays()[ArrayNamesEnum::DEPTH].SetBox(Box(0, 0, 0, 0, 0, 0));
    data.Arrays()[ArrayNamesEnum::PORV].SetBox(Box(0, 0, 0, 0, 0, 0));
    data.Arrays()[ArrayNamesEnum::TRANX].SetBox(Box(0, 0, 0, 0, 0, 0));
    data.Arrays()[ArrayNamesEnum::TRANY].SetBox(Box(0, 0, 0, 0, 0, 0));
    data.Arrays()[ArrayNamesEnum::TRANZ].SetBox(Box(0, 0, 0, 0, 0, 0));

    VERIFY(data.Title().compare("Test") == 0, "");
    VERIFY(data.StartDate().date() == QDate(2020, 6, 3), "");

    VERIFY(data.DATES().size() == 1, "");

    VERIFY(data.Unit() == UnitsEnum::LAB, "");
    VERIFY(data.Model() == ModelsEnum::ThreePhase, "");
    VERIFY(data.TemperatureOption() == false, "");

    VERIFY(data.NumRES() == 23, "");
    VERIFY(data.Nx() == 1, "");
    VERIFY(data.Ny() == 1, "");
    VERIFY(data.Nz() == 1, "");

    VERIFY(data.TABDIMS().NTSFUN() == 1, "");
    VERIFY(data.TABDIMS().NTPVT() == 1, "");
    VERIFY(data.TABDIMS().NSSFUN() == 1, "");

    VERIFY(data.EQLDIMS().NTEQUL() == 1, "");

    VERIFY(data.ENDSCALE().Directional() == DirectionalEnum::DIRECT, "");
    VERIFY(data.ENDSCALE().Irreversible() == IrreversibleEnum::REVERS, "");
    VERIFY(data.ENDSCALE().NTENDP() == 1, "");
    VERIFY(data.ENDSCALE().MaxNodesEPD() == 5, "");

    VERIFY(data.Arrays()[ArrayNamesEnum::TOPS].Box().Belongs(Box(0, 0, 0, 0, 0, 0)), "");

    VERIFY(data.Arrays()[ArrayNamesEnum::DX].Box().Belongs(Box(0, 0, 0, 0, 0, 0)), "");
    VERIFY(data.Arrays()[ArrayNamesEnum::DY].Box().Belongs(Box(0, 0, 0, 0, 0, 0)), "");
    VERIFY(data.Arrays()[ArrayNamesEnum::DZ].Box().Belongs(Box(0, 0, 0, 0, 0, 0)), "");

    VERIFY(data.Arrays()[ArrayNamesEnum::DXV].Box().Belongs(Box(0, 0, 0, 0, 0, 0)), "");
    VERIFY(data.Arrays()[ArrayNamesEnum::DYV].Box().Belongs(Box(0, 0, 0, 0, 0, 0)), "");
    VERIFY(data.Arrays()[ArrayNamesEnum::DZV].Box().Belongs(Box(0, 0, 0, 0, 0, 0)), "");

    VERIFY(data.Arrays()[ArrayNamesEnum::COORD].Box().Belongs(Box(0, 0, 0, 0, 0, 0)), "");
    VERIFY(data.Arrays()[ArrayNamesEnum::ZCORN].Box().Belongs(Box(0, 0, 0, 0, 0, 0)), "");

    VERIFY(data.Arrays()[ArrayNamesEnum::ACTNUM].Box().Belongs(Box(0, 0, 0, 0, 0, 0)), "");
    VERIFY(data.Arrays()[ArrayNamesEnum::MULTPV].Box().Belongs(Box(0, 0, 0, 0, 0, 0)), "");

    VERIFY(data.Arrays()[ArrayNamesEnum::PERMX].Box().Belongs(Box(0, 0, 0, 0, 0, 0)), "");
    VERIFY(data.Arrays()[ArrayNamesEnum::PERMY].Box().Belongs(Box(0, 0, 0, 0, 0, 0)), "");
    VERIFY(data.Arrays()[ArrayNamesEnum::PERMZ].Box().Belongs(Box(0, 0, 0, 0, 0, 0)), "");

    VERIFY(data.Arrays()[ArrayNamesEnum::PORO].Box().Belongs(Box(0, 0, 0, 0, 0, 0)), "");
    VERIFY(data.Arrays()[ArrayNamesEnum::NTG].Box().Belongs(Box(0, 0, 0, 0, 0, 0)), "");
    VERIFY(data.Arrays()[ArrayNamesEnum::DZNET].Box().Belongs(Box(0, 0, 0, 0, 0, 0)), "");

    VERIFY(data.Arrays()[ArrayNamesEnum::MULTX].Box().Belongs(Box(0, 0, 0, 0, 0, 0)), "");
    VERIFY(data.Arrays()[ArrayNamesEnum::MULTY].Box().Belongs(Box(0, 0, 0, 0, 0, 0)), "");
    VERIFY(data.Arrays()[ArrayNamesEnum::MULTZ].Box().Belongs(Box(0, 0, 0, 0, 0, 0)), "");

    VERIFY(data.Arrays()[ArrayNamesEnum::MULTXm].Box().Belongs(Box(0, 0, 0, 0, 0, 0)), "");
    VERIFY(data.Arrays()[ArrayNamesEnum::MULTYm].Box().Belongs(Box(0, 0, 0, 0, 0, 0)), "");
    VERIFY(data.Arrays()[ArrayNamesEnum::MULTZm].Box().Belongs(Box(0, 0, 0, 0, 0, 0)), "");

    VERIFY(data.Arrays()[ArrayNamesEnum::MINPVV].Box().Belongs(Box(0, 0, 0, 0, 0, 0)), "");

    VERIFY(data.MINPV() == 1, "");

    VERIFY(data.RSCONST().RS() == 1, "");
    VERIFY(data.RSCONST().PBub() ==  1, "");

    VERIFY(data.RSCONSTT().size() == 1, "");

    VERIFY(data.PVTO().size() == 5, "");
    VERIFY(data.PVCO().size() == 5, "");

    VERIFY(data.PMAX().PMax() == 1, "");
    VERIFY(data.PMAX().NumNodes() == 1, "");
    VERIFY(data.PMAX().PMaxComp() == 1, "");
    VERIFY(data.PMAX().PMinComp() == 1, "");

    VERIFY(data.PVCDO().size() == 5, "");

    VERIFY(data.PVDO().size() == 5, "");

    VERIFY(data.PVTW().size() == 5, "");

    VERIFY(data.PVDG().size() == 5, "");
    VERIFY(data.PVTG().size() == 5, "");

    VERIFY(data.ROCKOPTS().RPO() == ReferencePressureOptionsEnum::STORE, "");
    VERIFY(data.ROCKOPTS().MAOTP() == MAOTPOptionsEnum::STRESS, "");
    VERIFY(data.ROCKOPTS().IHBOption() == IHBOptionsEnum::ELASTIC, "");
    VERIFY(data.ROCKOPTS().RegionOption() == RegionOptionsEnum::PVTNUM, "");

    VERIFY(data.ROCK().size() == 5, "");
    VERIFY(data.DENSITY().size() == 5, "");
    VERIFY(data.GRAVITY().size() == 5, "");

    VERIFY(data.SWOF().size() == 5, "");
    VERIFY(data.SGOF().size() == 5, "");
    VERIFY(data.SGWFN().size() == 5, "");
    VERIFY(data.SLGOF().size() == 5, "");
    VERIFY(data.SOF2().size() == 5, "");
    VERIFY(data.SOF3().size() == 5, "");

    VERIFY(data.SOF32D().size() == 5, "");

    VERIFY(data.SWFN().size() == 5, "");
    VERIFY(data.SGFN().size() == 5, "");
    VERIFY(data.SOMWAT().size() == 5, "");
    VERIFY(data.SOMGAS().size() == 5, "");

    VERIFY(data.Arrays()[ArrayNamesEnum::SWATINIT].Box().Belongs(Box(0, 0, 0, 0, 0, 0)), "");
    VERIFY(data.Arrays()[ArrayNamesEnum::SWCR].Box().Belongs(Box(0, 0, 0, 0, 0, 0)), "");
    VERIFY(data.Arrays()[ArrayNamesEnum::ISWCR].Box().Belongs(Box(0, 0, 0, 0, 0, 0)), "");
    VERIFY(data.Arrays()[ArrayNamesEnum::SWL].Box().Belongs(Box(0, 0, 0, 0, 0, 0)), "");
    VERIFY(data.Arrays()[ArrayNamesEnum::ISWL].Box().Belongs(Box(0, 0, 0, 0, 0, 0)), "");
    VERIFY(data.Arrays()[ArrayNamesEnum::SWLPC].Box().Belongs(Box(0, 0, 0, 0, 0, 0)), "");
    VERIFY(data.Arrays()[ArrayNamesEnum::ISWLPC].Box().Belongs(Box(0, 0, 0, 0, 0, 0)), "");
    VERIFY(data.Arrays()[ArrayNamesEnum::SWU].Box().Belongs(Box(0, 0, 0, 0, 0, 0)), "");
    VERIFY(data.Arrays()[ArrayNamesEnum::ISWU].Box().Belongs(Box(0, 0, 0, 0, 0, 0)), "");
    VERIFY(data.Arrays()[ArrayNamesEnum::SGCR].Box().Belongs(Box(0, 0, 0, 0, 0, 0)), "");
    VERIFY(data.Arrays()[ArrayNamesEnum::ISGCR].Box().Belongs(Box(0, 0, 0, 0, 0, 0)), "");
    VERIFY(data.Arrays()[ArrayNamesEnum::SGL].Box().Belongs(Box(0, 0, 0, 0, 0, 0)), "");
    VERIFY(data.Arrays()[ArrayNamesEnum::ISGL].Box().Belongs(Box(0, 0, 0, 0, 0, 0)), "");
    VERIFY(data.Arrays()[ArrayNamesEnum::SGLPC].Box().Belongs(Box(0, 0, 0, 0, 0, 0)), "");
    VERIFY(data.Arrays()[ArrayNamesEnum::ISGLPC].Box().Belongs(Box(0, 0, 0, 0, 0, 0)), "");
    VERIFY(data.Arrays()[ArrayNamesEnum::PCG].Box().Belongs(Box(0, 0, 0, 0, 0, 0)), "");
    VERIFY(data.Arrays()[ArrayNamesEnum::IPCG].Box().Belongs(Box(0, 0, 0, 0, 0, 0)), "");
    VERIFY(data.Arrays()[ArrayNamesEnum::PCW].Box().Belongs(Box(0, 0, 0, 0, 0, 0)), "");
    VERIFY(data.Arrays()[ArrayNamesEnum::IPCW].Box().Belongs(Box(0, 0, 0, 0, 0, 0)), "");

    VERIFY(data.PPCWMAX().size() == 5, "");

    VERIFY(data.Arrays()[ArrayNamesEnum::KRO].Box().Belongs(Box(0, 0, 0, 0, 0, 0)), "");
    VERIFY(data.Arrays()[ArrayNamesEnum::IKRO].Box().Belongs(Box(0, 0, 0, 0, 0, 0)), "");
    VERIFY(data.Arrays()[ArrayNamesEnum::KRORW].Box().Belongs(Box(0, 0, 0, 0, 0, 0)), "");
    VERIFY(data.Arrays()[ArrayNamesEnum::IKRORW].Box().Belongs(Box(0, 0, 0, 0, 0, 0)), "");
    VERIFY(data.Arrays()[ArrayNamesEnum::KRORG].Box().Belongs(Box(0, 0, 0, 0, 0, 0)), "");
    VERIFY(data.Arrays()[ArrayNamesEnum::IKRORG].Box().Belongs(Box(0, 0, 0, 0, 0, 0)), "");
    VERIFY(data.Arrays()[ArrayNamesEnum::KRW].Box().Belongs(Box(0, 0, 0, 0, 0, 0)), "");
    VERIFY(data.Arrays()[ArrayNamesEnum::IKRW].Box().Belongs(Box(0, 0, 0, 0, 0, 0)), "");
    VERIFY(data.Arrays()[ArrayNamesEnum::KRWR].Box().Belongs(Box(0, 0, 0, 0, 0, 0)), "");
    VERIFY(data.Arrays()[ArrayNamesEnum::IKRWR].Box().Belongs(Box(0, 0, 0, 0, 0, 0)), "");
    VERIFY(data.Arrays()[ArrayNamesEnum::KRG].Box().Belongs(Box(0, 0, 0, 0, 0, 0)), "");
    VERIFY(data.Arrays()[ArrayNamesEnum::IKRG].Box().Belongs(Box(0, 0, 0, 0, 0, 0)), "");
    VERIFY(data.Arrays()[ArrayNamesEnum::KRGR].Box().Belongs(Box(0, 0, 0, 0, 0, 0)), "");
    VERIFY(data.Arrays()[ArrayNamesEnum::IKRGR].Box().Belongs(Box(0, 0, 0, 0, 0, 0)), "");

    VERIFY(data.ENKRVD().size() == 5, "");
    VERIFY(data.ENPCVD().size() == 5, "");
    VERIFY(data.ENSPCVD().size() == 5, "");

    VERIFY(data.SCALELIM().size() == 5, "");

    VERIFY(data.SCALECRS() == 1, "");

    VERIFY(data.SPECHEAT().size() == 5, "");
    VERIFY(data.SPECROCK().size() == 5, "");

    VERIFY(data.VISCREF().size() == 5, "");

    VERIFY(data.OILVISCT().size() == 5, "");
    VERIFY(data.WATVISCT().size() == 5, "");

    VERIFY(data.Arrays()[ArrayNamesEnum::PVTNUM].Box().Belongs(Box(0, 0, 0, 0, 0, 0)), "");
    VERIFY(data.Arrays()[ArrayNamesEnum::SATNUM].Box().Belongs(Box(0, 0, 0, 0, 0, 0)), "");
    VERIFY(data.Arrays()[ArrayNamesEnum::EQLNUM].Box().Belongs(Box(0, 0, 0, 0, 0, 0)), "");
    VERIFY(data.Arrays()[ArrayNamesEnum::ENDNUM].Box().Belongs(Box(0, 0, 0, 0, 0, 0)), "");

    VERIFY(data.EQUIL().size() == 5, "");

    VERIFY(data.RSVD().size() == 5, "");
    VERIFY(data.PBVD().size() == 5, "");
    VERIFY(data.PRVD().size() == 5, "");

    VERIFY(data.Arrays()[ArrayNamesEnum::PRESSURE].Box().Belongs(Box(0, 0, 0, 0, 0, 0)), "");
    VERIFY(data.Arrays()[ArrayNamesEnum::SWAT].Box().Belongs(Box(0, 0, 0, 0, 0, 0)), "");
    VERIFY(data.Arrays()[ArrayNamesEnum::SGAS].Box().Belongs(Box(0, 0, 0, 0, 0, 0)), "");
    VERIFY(data.Arrays()[ArrayNamesEnum::SOIL].Box().Belongs(Box(0, 0, 0, 0, 0, 0)), "");
    VERIFY(data.Arrays()[ArrayNamesEnum::PBUB].Box().Belongs(Box(0, 0, 0, 0, 0, 0)), "");
    VERIFY(data.Arrays()[ArrayNamesEnum::RS].Box().Belongs(Box(0, 0, 0, 0, 0, 0)), "");

    VERIFY(data.AQUANCON().size() == 5, "");
    VERIFY(data.AQUFETP().size() == 5, "");

    VERIFY(data.DIMPES().DSTARG() == 1, "");
    VERIFY(data.DIMPES().DSMAX() == 1, "");
    VERIFY(data.DIMPES().DPMAX() == 1, "");

    VERIFY(data.WELSPECS().size() == 5, "");
    VERIFY(data.COMPDAT().size() == 5, "");
    VERIFY(data.WCONPROD().size() == 5, "");
    VERIFY(data.WCONINJE().size() == 5, "");
    VERIFY(data.WCONHIST().size() == 5, "");
    VERIFY(data.WCONINJH().size() == 5, "");
    VERIFY(data.WELTARG().size() == 5, "");

    VERIFY(data.Operators().size() == 1, "");

    VERIFY(data.Arrays()[ArrayNamesEnum::DEPTH].Box().Belongs(Box(0, 0, 0, 0, 0, 0)), "");
    VERIFY(data.Arrays()[ArrayNamesEnum::PORV].Box().Belongs(Box(0, 0, 0, 0, 0, 0)), "");
    VERIFY(data.Arrays()[ArrayNamesEnum::TRANX].Box().Belongs(Box(0, 0, 0, 0, 0, 0)), "");
    VERIFY(data.Arrays()[ArrayNamesEnum::TRANY].Box().Belongs(Box(0, 0, 0, 0, 0, 0)), "");
    VERIFY(data.Arrays()[ArrayNamesEnum::TRANZ].Box().Belongs(Box(0, 0, 0, 0, 0, 0)), "");

    // Reinit object
    data.InitVariables();

    VERIFY(data.Title().compare("") == 0, "");
    VERIFY(data.StartDate().date() == QDate::currentDate(), "");

    VERIFY(data.DATES().size() == 0, "");

    VERIFY(data.Unit().isNull(), "");
    VERIFY(data.Model().isNull(), "");
    VERIFY(data.TemperatureOption().isNull(), "");

    VERIFY(data.NumRES().isNull(), "");
    VERIFY(data.Nx() == 0, "");
    VERIFY(data.Ny() == 0, "");
    VERIFY(data.Nz() == 0, "");

    VERIFY(data.TABDIMS().NTSFUN().isNull(), "");
    VERIFY(data.TABDIMS().NTPVT().isNull(), "");
    VERIFY(data.TABDIMS().NSSFUN().isNull(), "");

    VERIFY(data.EQLDIMS().NTEQUL().isNull(), "");

    VERIFY(data.ENDSCALE().Directional().isNull(), "");
    VERIFY(data.ENDSCALE().Irreversible().isNull(), "");
    VERIFY(data.ENDSCALE().NTENDP().isNull(), "");
    VERIFY(data.ENDSCALE().MaxNodesEPD().isNull(), "");

    VERIFY(data.Arrays()[ArrayNamesEnum::TOPS].Box().Belongs(Box()), "");

    VERIFY(data.Arrays()[ArrayNamesEnum::DX].Box().Belongs(Box()), "");
    VERIFY(data.Arrays()[ArrayNamesEnum::DY].Box().Belongs(Box()), "");
    VERIFY(data.Arrays()[ArrayNamesEnum::DZ].Box().Belongs(Box()), "");

    VERIFY(data.Arrays()[ArrayNamesEnum::DXV].Box().Belongs(Box()), "");
    VERIFY(data.Arrays()[ArrayNamesEnum::DYV].Box().Belongs(Box()), "");
    VERIFY(data.Arrays()[ArrayNamesEnum::DZV].Box().Belongs(Box()), "");

    VERIFY(data.Arrays()[ArrayNamesEnum::COORD].Box().Belongs(Box()), "");
    VERIFY(data.Arrays()[ArrayNamesEnum::ZCORN].Box().Belongs(Box()), "");

    VERIFY(data.Arrays()[ArrayNamesEnum::ACTNUM].Box().Belongs(Box()), "");
    VERIFY(data.Arrays()[ArrayNamesEnum::MULTPV].Box().Belongs(Box()), "");

    VERIFY(data.Arrays()[ArrayNamesEnum::PERMX].Box().Belongs(Box()), "");
    VERIFY(data.Arrays()[ArrayNamesEnum::PERMY].Box().Belongs(Box()), "");
    VERIFY(data.Arrays()[ArrayNamesEnum::PERMZ].Box().Belongs(Box()), "");

    VERIFY(data.Arrays()[ArrayNamesEnum::PORO].Box().Belongs(Box()), "");
    VERIFY(data.Arrays()[ArrayNamesEnum::NTG].Box().Belongs(Box()), "");
    VERIFY(data.Arrays()[ArrayNamesEnum::DZNET].Box().Belongs(Box()), "");

    VERIFY(data.Arrays()[ArrayNamesEnum::MULTX].Box().Belongs(Box()), "");
    VERIFY(data.Arrays()[ArrayNamesEnum::MULTY].Box().Belongs(Box()), "");
    VERIFY(data.Arrays()[ArrayNamesEnum::MULTZ].Box().Belongs(Box()), "");

    VERIFY(data.Arrays()[ArrayNamesEnum::MULTXm].Box().Belongs(Box()), "");
    VERIFY(data.Arrays()[ArrayNamesEnum::MULTYm].Box().Belongs(Box()), "");
    VERIFY(data.Arrays()[ArrayNamesEnum::MULTZm].Box().Belongs(Box()), "");

    VERIFY(data.Arrays()[ArrayNamesEnum::MINPVV].Box().Belongs(Box()), "");

    VERIFY(data.MINPV().isNull(), "");

    VERIFY(data.RSCONST().RS() == 0, "");
    VERIFY(data.RSCONST().PBub() ==  0, "");

    VERIFY(data.RSCONSTT().size() == 0, "");

    VERIFY(data.PVTO().size() == 0, "");
    VERIFY(data.PVCO().size() == 0, "");

    VERIFY(data.PMAX().PMax().isNull(), "");
    VERIFY(data.PMAX().NumNodes().isNull(), "");
    VERIFY(data.PMAX().PMaxComp().isNull(), "");
    VERIFY(data.PMAX().PMinComp().isNull(), "");

    VERIFY(data.PVCDO().size() == 0, "");

    VERIFY(data.PVDO().size() == 0, "");

    VERIFY(data.PVTW().size() == 0, "");

    VERIFY(data.PVDG().size() == 0, "");
    VERIFY(data.PVTG().size() == 0, "");

    VERIFY(data.ROCKOPTS().RPO().isNull(), "");
    VERIFY(data.ROCKOPTS().MAOTP().isNull(), "");
    VERIFY(data.ROCKOPTS().IHBOption().isNull(), "");
    VERIFY(data.ROCKOPTS().RegionOption().isNull(), "");

    VERIFY(data.ROCK().size() == 0, "");
    VERIFY(data.DENSITY().size() == 0, "");
    VERIFY(data.GRAVITY().size() == 0, "");

    VERIFY(data.SWOF().size() == 0, "");
    VERIFY(data.SGOF().size() == 0, "");
    VERIFY(data.SGWFN().size() == 0, "");
    VERIFY(data.SLGOF().size() == 0, "");
    VERIFY(data.SOF2().size() == 0, "");
    VERIFY(data.SOF3().size() == 0, "");

    VERIFY(data.SOF32D().size() == 0, "");

    VERIFY(data.SWFN().size() == 0, "");
    VERIFY(data.SGFN().size() == 0, "");
    VERIFY(data.SOMWAT().size() == 0, "");
    VERIFY(data.SOMGAS().size() == 0, "");

    VERIFY(data.Arrays()[ArrayNamesEnum::SWATINIT].Box().Belongs(Box()), "");
    VERIFY(data.Arrays()[ArrayNamesEnum::SWCR].Box().Belongs(Box()), "");
    VERIFY(data.Arrays()[ArrayNamesEnum::ISWCR].Box().Belongs(Box()), "");
    VERIFY(data.Arrays()[ArrayNamesEnum::SWL].Box().Belongs(Box()), "");
    VERIFY(data.Arrays()[ArrayNamesEnum::ISWL].Box().Belongs(Box()), "");
    VERIFY(data.Arrays()[ArrayNamesEnum::SWLPC].Box().Belongs(Box()), "");
    VERIFY(data.Arrays()[ArrayNamesEnum::ISWLPC].Box().Belongs(Box()), "");
    VERIFY(data.Arrays()[ArrayNamesEnum::SWU].Box().Belongs(Box()), "");
    VERIFY(data.Arrays()[ArrayNamesEnum::ISWU].Box().Belongs(Box()), "");
    VERIFY(data.Arrays()[ArrayNamesEnum::SGCR].Box().Belongs(Box()), "");
    VERIFY(data.Arrays()[ArrayNamesEnum::ISGCR].Box().Belongs(Box()), "");
    VERIFY(data.Arrays()[ArrayNamesEnum::SGL].Box().Belongs(Box()), "");
    VERIFY(data.Arrays()[ArrayNamesEnum::ISGL].Box().Belongs(Box()), "");
    VERIFY(data.Arrays()[ArrayNamesEnum::SGLPC].Box().Belongs(Box()), "");
    VERIFY(data.Arrays()[ArrayNamesEnum::ISGLPC].Box().Belongs(Box()), "");
    VERIFY(data.Arrays()[ArrayNamesEnum::PCG].Box().Belongs(Box()), "");
    VERIFY(data.Arrays()[ArrayNamesEnum::IPCG].Box().Belongs(Box()), "");
    VERIFY(data.Arrays()[ArrayNamesEnum::PCW].Box().Belongs(Box()), "");
    VERIFY(data.Arrays()[ArrayNamesEnum::IPCW].Box().Belongs(Box()), "");

    VERIFY(data.PPCWMAX().size() == 0, "");

    VERIFY(data.Arrays()[ArrayNamesEnum::KRO].Box().Belongs(Box()), "");
    VERIFY(data.Arrays()[ArrayNamesEnum::IKRO].Box().Belongs(Box()), "");
    VERIFY(data.Arrays()[ArrayNamesEnum::KRORW].Box().Belongs(Box()), "");
    VERIFY(data.Arrays()[ArrayNamesEnum::IKRORW].Box().Belongs(Box()), "");
    VERIFY(data.Arrays()[ArrayNamesEnum::KRORG].Box().Belongs(Box()), "");
    VERIFY(data.Arrays()[ArrayNamesEnum::IKRORG].Box().Belongs(Box()), "");
    VERIFY(data.Arrays()[ArrayNamesEnum::KRW].Box().Belongs(Box()), "");
    VERIFY(data.Arrays()[ArrayNamesEnum::IKRW].Box().Belongs(Box()), "");
    VERIFY(data.Arrays()[ArrayNamesEnum::KRWR].Box().Belongs(Box()), "");
    VERIFY(data.Arrays()[ArrayNamesEnum::IKRWR].Box().Belongs(Box()), "");
    VERIFY(data.Arrays()[ArrayNamesEnum::KRG].Box().Belongs(Box()), "");
    VERIFY(data.Arrays()[ArrayNamesEnum::IKRG].Box().Belongs(Box()), "");
    VERIFY(data.Arrays()[ArrayNamesEnum::KRGR].Box().Belongs(Box()), "");
    VERIFY(data.Arrays()[ArrayNamesEnum::IKRGR].Box().Belongs(Box()), "");

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

    VERIFY(data.Arrays()[ArrayNamesEnum::PVTNUM].Box().Belongs(Box()), "");
    VERIFY(data.Arrays()[ArrayNamesEnum::SATNUM].Box().Belongs(Box()), "");
    VERIFY(data.Arrays()[ArrayNamesEnum::EQLNUM].Box().Belongs(Box()), "");
    VERIFY(data.Arrays()[ArrayNamesEnum::ENDNUM].Box().Belongs(Box()), "");

    VERIFY(data.EQUIL().size() == 0, "");

    VERIFY(data.RSVD().size() == 0, "");
    VERIFY(data.PBVD().size() == 0, "");
    VERIFY(data.PRVD().size() == 0, "");

    VERIFY(data.Arrays()[ArrayNamesEnum::PRESSURE].Box().Belongs(Box()), "");
    VERIFY(data.Arrays()[ArrayNamesEnum::SWAT].Box().Belongs(Box()), "");
    VERIFY(data.Arrays()[ArrayNamesEnum::SGAS].Box().Belongs(Box()), "");
    VERIFY(data.Arrays()[ArrayNamesEnum::SOIL].Box().Belongs(Box()), "");
    VERIFY(data.Arrays()[ArrayNamesEnum::PBUB].Box().Belongs(Box()), "");
    VERIFY(data.Arrays()[ArrayNamesEnum::RS].Box().Belongs(Box()), "");

    VERIFY(data.AQUANCON().size() == 0, "");
    VERIFY(data.AQUFETP().size() == 0, "");

    VERIFY(data.DIMPES().DSTARG().isNull(), "");
    VERIFY(data.DIMPES().DSMAX().isNull(), "");
    VERIFY(data.DIMPES().DPMAX().isNull(), "");

    VERIFY(data.WELSPECS().size() == 0, "");
    VERIFY(data.COMPDAT().size() == 0, "");
    VERIFY(data.WCONPROD().size() == 0, "");
    VERIFY(data.WCONINJE().size() == 0, "");
    VERIFY(data.WCONHIST().size() == 0, "");
    VERIFY(data.WCONINJH().size() == 0, "");
    VERIFY(data.WELTARG().size() == 0, "");

    VERIFY(data.Operators().size() == 0, "");

    VERIFY(data.Arrays()[ArrayNamesEnum::DEPTH].Box().Belongs(Box()), "");
    VERIFY(data.Arrays()[ArrayNamesEnum::PORV].Box().Belongs(Box()), "");
    VERIFY(data.Arrays()[ArrayNamesEnum::TRANX].Box().Belongs(Box()), "");
    VERIFY(data.Arrays()[ArrayNamesEnum::TRANY].Box().Belongs(Box()), "");
    VERIFY(data.Arrays()[ArrayNamesEnum::TRANZ].Box().Belongs(Box()), "");

}

}}}}
