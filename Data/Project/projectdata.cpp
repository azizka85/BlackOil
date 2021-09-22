#include "projectdata.h"

namespace BlackOil {
namespace Data {
namespace Project {

ProjectData::ProjectData()
{
    int cnt = ArrayNamesEnum::staticMetaObject.enumerator(ArrayNamesEnum::staticMetaObject.indexOfEnumerator("ArrayNames")).keyCount();

    arrays.resize(cnt);

    InitVariables();
}

QString &ProjectData::Title()
{
    return title;
}

QDateTime &ProjectData::StartDate()
{
    return startDate;
}

QVector<QDateTime> &ProjectData::DATES()
{
    return dates;
}

QVariant ProjectData::Unit()
{
    return unit;
}

QVariant ProjectData::Model()
{
    return model;
}

QVariant ProjectData::TemperatureOption()
{
    return temperatureOption;
}

QVariant ProjectData::NumRES()
{
    return numRES;
}

int ProjectData::Nx()
{
    return nx;
}

int ProjectData::Ny()
{
    return ny;
}

int ProjectData::Nz()
{
    return nz;
}

TABDIMSData &ProjectData::TABDIMS()
{
    return tabDIMS;
}

EQLDIMSData &ProjectData::EQLDIMS()
{
    return eqlDIMS;
}

ENDSCALEData &ProjectData::ENDSCALE()
{
    return endSCALE;
}

QVariant ProjectData::MINPV()
{
    return minpv;
}

RSCONSTData &ProjectData::RSCONST()
{
    return rsCONST;
}

QVector<RSCONSTData> &ProjectData::RSCONSTT()
{
    return rsCONSTT;
}

QVector<QVector<PVTOData> > &ProjectData::PVTO()
{
    return pvto;
}

QVector<QVector<PVCOData> > &ProjectData::PVCO()
{
    return pvco;
}

PMAXData &ProjectData::PMAX()
{
    return pmax;
}

QVector<PVCDOData> &ProjectData::PVCDO()
{
    return pvcdo;
}

QVector<QVector<PVDOData> > &ProjectData::PVDO()
{
    return pvdo;
}

QVector<PVTWData> &ProjectData::PVTW()
{
    return pvtw;
}

QVector<QVector<PVDGData> > &ProjectData::PVDG()
{
    return pvdg;
}

QVector<QVector<PVTGData> > &ProjectData::PVTG()
{
    return pvtg;
}

ROCKOPTSData &ProjectData::ROCKOPTS()
{
    return rockOPTS;
}

QVector<ROCKData> &ProjectData::ROCK()
{
    return rock;
}

QVector<DENSITYData> &ProjectData::DENSITY()
{
    return density;
}

QVector<GRAVITYData> &ProjectData::GRAVITY()
{
    return gravity;
}

QVector<QVector<SWOFData> > &ProjectData::SWOF()
{
    return swof;
}

QVector<QVector<SGOFData> > &ProjectData::SGOF()
{
    return sgof;
}

QVector<QVector<SGWFNData> > &ProjectData::SGWFN()
{
    return sgwfn;
}

QVector<QVector<SLGOFData> > &ProjectData::SLGOF()
{
    return slgof;
}

QVector<QVector<SOF2Data> > &ProjectData::SOF2()
{
    return sof2;
}

QVector<QVector<SOF3Data> > &ProjectData::SOF3()
{
    return sof3;
}

QVector<SOF32DData> &ProjectData::SOF32D()
{
    return sof32d;
}

QVector<QVector<SWFNData> > &ProjectData::SWFN()
{
    return swfn;
}

QVector<QVector<SGFNData> > &ProjectData::SGFN()
{
    return sgfn;
}

QVector<QVector<SOMGASData> > &ProjectData::SOMGAS()
{
    return somgas;
}

QVector<QVector<SOMWATData> > &ProjectData::SOMWAT()
{
    return somwat;
}

QVector<PPCWMAXData> &ProjectData::PPCWMAX()
{
    return ppcwMAX;
}

QVector<QVector<ENKRVDData> > &ProjectData::ENKRVD()
{
    return enkrvd;
}

QVector<QVector<ENPCVDData> > &ProjectData::ENPCVD()
{
    return enpcvd;
}

QVector<QVector<ENSPCVDData> > &ProjectData::ENSPCVD()
{
    return enspcvd;
}

QVector<QVariant> &ProjectData::SCALELIM()
{
    return scalelim;
}

QVariant ProjectData::SCALECRS()
{
    return scleCRS;
}

QVector<QVector<SPECHEATData> > &ProjectData::SPECHEAT()
{
    return specheat;
}

QVector<QVector<SPECROCKData> > &ProjectData::SPECROCK()
{
    return specrock;
}

QVector<VISCREFData> &ProjectData::VISCREF()
{
    return viscREF;
}

QVector<QVector<OILVISCTData> > &ProjectData::OILVISCT()
{
    return oilVISCT;
}

QVector<QVector<WATVISCTData> > &ProjectData::WATVISCT()
{
    return watVISCT;
}

QVector<EQUILData> &ProjectData::EQUIL()
{
    return equil;
}

QVector<QVector<RSVDData> > &ProjectData::RSVD()
{
    return rsvd;
}

QVector<QVector<PBVDData> > &ProjectData::PBVD()
{
    return pbvd;
}

QVector<QVector<PRVDData> > &ProjectData::PRVD()
{
    return prvd;
}

QVector<AQUANCONData> &ProjectData::AQUANCON()
{
    return aquanCON;
}

QVector<AQUFETPData> &ProjectData::AQUFETP()
{
    return aquFETP;
}

DIMPESData &ProjectData::DIMPES()
{
    return dimpes;
}

QVector<WELSPECSData> &ProjectData::WELSPECS()
{
    return welspecs;
}

QVector<COMPDATData> &ProjectData::COMPDAT()
{
    return compdat;
}

QVector<WCONPRODData> &ProjectData::WCONPROD()
{
    return wconprod;
}

QVector<WCONINJEData> &ProjectData::WCONINJE()
{
    return wconinje;
}

QVector<WCONHISTData> &ProjectData::WCONHIST()
{
    return wconHIST;
}

QVector<WCONINJHData> &ProjectData::WCONINJH()
{
    return wconINJH;
}

QVector<WELTARGData> &ProjectData::WELTARG()
{
    return welTARG;
}

QVector<OperatorData> &ProjectData::Operators()
{
    return operators;
}

QVector<BoxArray> &ProjectData::Arrays()
{
    return arrays;
}

void ProjectData::SetTitle(const QString &title)
{
    this->title = title;
}

void ProjectData::SetStartDate(const QDateTime &startDate)
{
    this->startDate = startDate;
}

void ProjectData::SetUnit(const QVariant &unit)
{
    this->unit = unit;
}

void ProjectData::SetModel(const QVariant &model)
{
    this->model = model;
}

void ProjectData::SetTemperatureOption(const QVariant &temperatureOption)
{
    this->temperatureOption = temperatureOption;
}

void ProjectData::SetNumRES(const QVariant &numRES)
{
    this->numRES = numRES;
}

void ProjectData::SetNx(int nx)
{
    this->nx = nx;
}

void ProjectData::SetNy(int ny)
{
    this->ny = ny;
}

void ProjectData::SetNz(int nz)
{
    this->nz = nz;
}

void ProjectData::SetMINPV(const double &minpv)
{
    this->minpv = minpv;
}

void ProjectData::SetSCALECRS(const QVariant &scleCRS)
{
    this->scleCRS = scleCRS;
}

void ProjectData::InitVariables()
{
    SetTitle("");
    SetStartDate(QDateTime::currentDateTime());

    dates.clear();

    SetUnit(QVariant());
    SetModel(QVariant());
    SetTemperatureOption(QVariant());

    SetNumRES(QVariant());
    SetNx(0);
    SetNy(0);
    SetNz(0);

    tabDIMS.InitVariables();
    eqlDIMS.InitVariables();
    endSCALE.InitVariables();

    minpv.clear();

    rsCONST.InitVariables();

    rsCONSTT.clear();

    pvto.clear();
    pvco.clear();

    pmax.InitVariables();

    pvcdo.clear();

    pvdo.clear();

    pvtw.clear();

    pvdg.clear();
    pvtg.clear();

    rockOPTS.InitVariables();

    rock.clear();
    density.clear();
    gravity.clear();

    swof.clear();
    sgof.clear();
    sgwfn.clear();
    slgof.clear();
    sof2.clear();
    sof3.clear();

    sof32d.clear();

    swfn.clear();
    sgfn.clear();
    somgas.clear();
    somwat.clear();

    ppcwMAX.clear();

    enkrvd.clear();
    enpcvd.clear();
    enspcvd.clear();

    scalelim.clear();

    scleCRS.clear();

    specheat.clear();
    specrock.clear();

    viscREF.clear();

    oilVISCT.clear();
    watVISCT.clear();

    equil.clear();

    rsvd.clear();
    pbvd.clear();
    prvd.clear();

    aquanCON.clear();
    aquFETP.clear();

    dimpes.InitVariables();

    welspecs.clear();
    compdat.clear();
    wconprod.clear();
    wconinje.clear();
    wconHIST.clear();
    wconINJH.clear();
    welTARG.clear();

    operators.clear();

    int cnt = ArrayNamesEnum::staticMetaObject.enumerator(ArrayNamesEnum::staticMetaObject.indexOfEnumerator("ArrayNames")).keyCount();

    for(int i = 0; i < cnt; i++) arrays[i].Clear();
}

}}}
