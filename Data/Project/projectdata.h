#ifndef PROJECTDATA_H
#define PROJECTDATA_H

#include <qmetaobject.h>
#include <qvariant.h>
#include <qstring.h>
#include <qdatetime.h>
#include <qvector.h>

#include <arraynamesenum.h>

#include <boxarray.h>

#include <tabdimsdata.h>
#include <eqldimsdata.h>
#include <endscaledata.h>

#include <rsconstdata.h>

#include <pvtodata.h>
#include <pvcodata.h>

#include <pmaxdata.h>

#include <pvcdodata.h>

#include <pvdodata.h>

#include <pvtwdata.h>

#include <pvdgdata.h>
#include <pvtgdata.h>

#include <rockoptsdata.h>

#include <rockdata.h>
#include <densitydata.h>
#include <gravitydata.h>

#include <swofdata.h>
#include <sgofdata.h>
#include <sgwfndata.h>
#include <slgofdata.h>
#include <sof2data.h>
#include <sof3data.h>

#include <sof32ddata.h>

#include <swfndata.h>
#include <sgfndata.h>
#include <somgasdata.h>
#include <somwatdata.h>

#include <ppcwmaxdata.h>

#include <enkrvddata.h>
#include <enpcvddata.h>
#include <enspcvddata.h>

#include <specheatdata.h>
#include <specrockdata.h>

#include <viscrefdata.h>

#include <oilvisctdata.h>
#include <watvisctdata.h>

#include <equildata.h>

#include <rsvddata.h>
#include <pbvddata.h>
#include <prvddata.h>

#include <aquancondata.h>
#include <aqufetpdata.h>

#include <dimpesdata.h>

#include <welspecsdata.h>
#include <compdatdata.h>
#include <wconproddata.h>
#include <wconinjedata.h>
#include <wconhistdata.h>
#include <wconinjhdata.h>
#include <weltargdata.h>

#include <operatordata.h>

#include <data_global.h>

using namespace BlackOil::Data::Arrays;

namespace BlackOil {
namespace Data {
namespace Project {

class DATA_EXPORT ProjectData
{
public:
    ProjectData();

    QString &Title();
    QDateTime &StartDate();

    QVector<QDateTime> &DATES();

    QVariant Unit();
    QVariant Model();
    QVariant TemperatureOption();

    QVariant NumRES();
    int Nx();
    int Ny();
    int Nz();

    TABDIMSData &TABDIMS();
    EQLDIMSData &EQLDIMS();
    ENDSCALEData &ENDSCALE();

    QVariant MINPV();

    RSCONSTData &RSCONST();

    QVector<RSCONSTData> &RSCONSTT();

    QVector<QVector<PVTOData>> &PVTO();
    QVector<QVector<PVCOData>> &PVCO();

    PMAXData &PMAX();

    QVector<PVCDOData> &PVCDO();

    QVector<QVector<PVDOData>> &PVDO();

    QVector<PVTWData> &PVTW();

    QVector<QVector<PVDGData>> &PVDG();
    QVector<QVector<PVTGData>> &PVTG();

    ROCKOPTSData &ROCKOPTS();

    QVector<ROCKData> &ROCK();
    QVector<DENSITYData> &DENSITY();
    QVector<GRAVITYData> &GRAVITY();

    QVector<QVector<SWOFData>> &SWOF();
    QVector<QVector<SGOFData>> &SGOF();
    QVector<QVector<SGWFNData>> &SGWFN();
    QVector<QVector<SLGOFData>> &SLGOF();
    QVector<QVector<SOF2Data>> &SOF2();
    QVector<QVector<SOF3Data>> &SOF3();

    QVector<SOF32DData> &SOF32D();

    QVector<QVector<SWFNData>> &SWFN();
    QVector<QVector<SGFNData>> &SGFN();
    QVector<QVector<SOMGASData>> &SOMGAS();
    QVector<QVector<SOMWATData>> &SOMWAT();

    QVector<PPCWMAXData> &PPCWMAX();

    QVector<QVector<ENKRVDData>> &ENKRVD();
    QVector<QVector<ENPCVDData>> &ENPCVD();
    QVector<QVector<ENSPCVDData>> &ENSPCVD();

    QVector<QVariant> &SCALELIM();

    QVariant SCALECRS();

    QVector<QVector<SPECHEATData>> &SPECHEAT();
    QVector<QVector<SPECROCKData>> &SPECROCK();

    QVector<VISCREFData> &VISCREF();

    QVector<QVector<OILVISCTData>> &OILVISCT();
    QVector<QVector<WATVISCTData>> &WATVISCT();

    QVector<EQUILData> &EQUIL();

    QVector<QVector<RSVDData>> &RSVD();
    QVector<QVector<PBVDData>> &PBVD();
    QVector<QVector<PRVDData>> &PRVD();

    QVector<AQUANCONData> &AQUANCON();
    QVector<AQUFETPData> &AQUFETP();

    DIMPESData &DIMPES();

    QVector<WELSPECSData> &WELSPECS();
    QVector<COMPDATData> &COMPDAT();
    QVector<WCONPRODData> &WCONPROD();
    QVector<WCONINJEData> &WCONINJE();
    QVector<WCONHISTData> &WCONHIST();
    QVector<WCONINJHData> &WCONINJH();
    QVector<WELTARGData> &WELTARG();

    QVector<OperatorData> &Operators();

    QVector<BoxArray> &Arrays();

    void SetTitle(const QString &title);
    void SetStartDate(const QDateTime &startDate);

    void SetUnit(const QVariant &unit);
    void SetModel(const QVariant &model);
    void SetTemperatureOption(const QVariant &temperatureOption);

    void SetNumRES(const QVariant& numRES);
    void SetNx(int nx);
    void SetNy(int ny);
    void SetNz(int nz);

    void SetMINPV(const double &minpv);

    void SetSCALECRS(const QVariant &scleCRS);

    void InitVariables();

protected:
    QString title;
    QDateTime startDate;
    QVector<QDateTime> dates;
    QVariant unit;
    QVariant model;
    QVariant temperatureOption;
    QVariant numRES;
    int nx, ny, nz;

    TABDIMSData tabDIMS;
    EQLDIMSData eqlDIMS;
    ENDSCALEData endSCALE;

    QVector<BoxArray> arrays;

    QVariant minpv;

    RSCONSTData rsCONST;

    QVector<RSCONSTData> rsCONSTT;

    QVector<QVector<PVTOData>> pvto;
    QVector<QVector<PVCOData>> pvco;

    PMAXData pmax;

    QVector<PVCDOData> pvcdo;

    QVector<QVector<PVDOData>> pvdo;

    QVector<PVTWData> pvtw;

    QVector<QVector<PVDGData>> pvdg;
    QVector<QVector<PVTGData>> pvtg;

    ROCKOPTSData rockOPTS;

    QVector<ROCKData> rock;
    QVector<DENSITYData> density;
    QVector<GRAVITYData> gravity;

    QVector<QVector<SWOFData>> swof;
    QVector<QVector<SGOFData>> sgof;
    QVector<QVector<SGWFNData>> sgwfn;
    QVector<QVector<SLGOFData>> slgof;
    QVector<QVector<SOF2Data>> sof2;
    QVector<QVector<SOF3Data>> sof3;

    QVector<SOF32DData> sof32d;

    QVector<QVector<SWFNData>> swfn;
    QVector<QVector<SGFNData>> sgfn;
    QVector<QVector<SOMGASData>> somgas;
    QVector<QVector<SOMWATData>> somwat;

    QVector<PPCWMAXData> ppcwMAX;

    QVector<QVector<ENKRVDData>> enkrvd;
    QVector<QVector<ENPCVDData>> enpcvd;
    QVector<QVector<ENSPCVDData>> enspcvd;

    QVector<QVariant> scalelim;

    QVariant scleCRS;

    QVector<QVector<SPECHEATData>> specheat;
    QVector<QVector<SPECROCKData>> specrock;

    QVector<VISCREFData> viscREF;

    QVector<QVector<OILVISCTData>> oilVISCT;
    QVector<QVector<WATVISCTData>> watVISCT;

    QVector<EQUILData> equil;

    QVector<QVector<RSVDData>> rsvd;
    QVector<QVector<PBVDData>> pbvd;
    QVector<QVector<PRVDData>> prvd;

    QVector<AQUANCONData> aquanCON;
    QVector<AQUFETPData> aquFETP;

    DIMPESData dimpes;

    QVector<WELSPECSData> welspecs;
    QVector<COMPDATData> compdat;
    QVector<WCONPRODData> wconprod;
    QVector<WCONINJEData> wconinje;
    QVector<WCONHISTData> wconHIST;
    QVector<WCONINJHData> wconINJH;
    QVector<WELTARGData> welTARG;

    QVector<OperatorData> operators;
};

}}}

#endif // PROJECTDATA_H
