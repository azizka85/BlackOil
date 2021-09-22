#ifndef ECLIPSEFILEREADER_H
#define ECLIPSEFILEREADER_H

#include <qmetaobject.h>
#include <qstring.h>
#include <qdatetime.h>
#include <qvector.h>
#include <qdir.h>
#include <qfile.h>
#include <qfileinfo.h>
#include <qtextstream.h>
#include <qdebug.h>

#include <box.h>

#include <casesenum.h>
#include <unitsenum.h>
#include <modelsenum.h>
#include <directionalenum.h>
#include <irreversibleenum.h>
#include <monthsenum.h>
#include <datatypeenum.h>
#include <maotpoptionsenum.h>
#include <referencepressureoptionsenum.h>
#include <regionoptionsenum.h>
#include <ihboptionsenum.h>
#include <facetypeenum.h>
#include <wellstatusenum.h>
#include <wellcontrolenum.h>
#include <fluidtypeenum.h>
#include <operatortypeenum.h>
#include <defaultvalues.h>
#include <projectdata.h>
#include <operatordata.h>

#include <readfilehelper.h>

#include <data_global.h>

using namespace BlackOil::Data::Grid;
using namespace BlackOil::Data::Project;
using namespace BlackOil::Data::Helpers::Eclipse;

namespace BlackOil {
namespace Data {
namespace Readers {

class DATA_EXPORT EclipseFileReader
{
public:
    EclipseFileReader();

    void Load(ProjectData &data, const QString &filePath);

    void InitVariables();

protected:
    void ReadFile(ProjectData& data, const QString& filePath, QMetaEnum &casesEnum);

    // RUNSPEC
    void ReadTITLE(ProjectData &data, QTextStream &sr);
    void ReadSTART(ProjectData &data, QTextStream &sr);
    void ReadNUMRES(ProjectData &data, QTextStream &sr);
    void ReadDIMENS(ProjectData &data, QTextStream &sr);
    void ReadTABDIMS(ProjectData &data, QTextStream &sr);
    void ReadEQLDIMS(ProjectData &data, QTextStream &sr);
    void ReadENDSCALE(ProjectData &data, QTextStream &sr);

    // GRID
    void ReadMINPV(ProjectData &data, QTextStream &sr);

    // PROPS
    void ReadRSCONST(ProjectData &data, QTextStream &sr);
    void ReadRSCONSTT(ProjectData &data, QTextStream &sr);
    void ReadPVTO(ProjectData &data, QTextStream &sr);
    void ReadPVCO(ProjectData &data, QTextStream &sr);
    void ReadPMAX(ProjectData &data, QTextStream &sr);
    void ReadPVCDO(ProjectData &data, QTextStream &sr);
    void ReadPVDO(ProjectData &data, QTextStream &sr);
    void ReadPVTW(ProjectData &data, QTextStream &sr);
    void ReadPVDG(ProjectData &data, QTextStream &sr);
    void ReadPVTG(ProjectData &data, QTextStream &sr);
    void ReadROCKOPTS(ProjectData &data, QTextStream &sr);
    void ReadROCK(ProjectData &data, QTextStream &sr);
    void ReadDENSITY(ProjectData &data, QTextStream &sr);
    void ReadGRAVITY(ProjectData &data, QTextStream &sr);
    void ReadSWOF(ProjectData &data, QTextStream &sr);
    void ReadSGOF(ProjectData &data, QTextStream &sr);
    void ReadSGWFN(ProjectData &data, QTextStream &sr);
    void ReadSLGOF(ProjectData &data, QTextStream &sr);
    void ReadSOF2(ProjectData &data, QTextStream &sr);
    void ReadSOF3(ProjectData &data, QTextStream &sr);
    void ReadSOF32D(ProjectData &data, QTextStream &sr);
    void ReadSWFN(ProjectData &data, QTextStream &sr);
    void ReadSGFN(ProjectData &data, QTextStream &sr);
    void ReadSOMGAS(ProjectData &data, QTextStream &sr);
    void ReadSOMWAT(ProjectData &data, QTextStream &sr);
    void ReadPPCWMAX(ProjectData &data, QTextStream &sr);
    void ReadENKRVD(ProjectData &data, QTextStream &sr);
    void ReadENPCVD(ProjectData &data, QTextStream &sr);
    void ReadENSPCVD(ProjectData &data, QTextStream &sr);
    void ReadSCALELIM(ProjectData &data, QTextStream &sr);
    void ReadSCALECRS(ProjectData &data, QTextStream &sr);
    void ReadSPECHEAT(ProjectData &data, QTextStream &sr);
    void ReadSPECROCK(ProjectData &data, QTextStream &sr);
    void ReadVISCREF(ProjectData &data, QTextStream &sr);
    void ReadOILVISCT(ProjectData &data, QTextStream &sr);
    void ReadWATVISCT(ProjectData &data, QTextStream &sr);

    // SOLUTION
    void ReadEQUIL(ProjectData &data, QTextStream &sr);
    void ReadRSVD(ProjectData &data, QTextStream &sr);
    void ReadPBVD(ProjectData &data, QTextStream &sr);
    void ReadPRVD(ProjectData &data, QTextStream &sr);
    void ReadAQUANCON(ProjectData &data, QTextStream &sr);
    void ReadAQUFETP(ProjectData &data, QTextStream &sr);

    // SCHEDULE
    void ReadDIMPES(ProjectData &data, QTextStream &sr);
    void ReadWELSPECS(ProjectData &data, QTextStream &sr);
    void ReadCOMPDAT(ProjectData &data, QTextStream &sr);
    void ReadWCONPROD(ProjectData &data, QTextStream &sr);
    void ReadWCONINJE(ProjectData &data, QTextStream &sr);
    void ReadDATES(ProjectData &data, QTextStream &sr);
    void ReadTSTEP(ProjectData &data, QTextStream &sr);
    void ReadWCONHIST(ProjectData &data, QTextStream &sr);
    void ReadWCONINJH(ProjectData &data, QTextStream &sr);
    void ReadWELTARG(ProjectData &data, QTextStream &sr);

    // ANY SECTION
    void ReadINCLUDE(ProjectData &data, QTextStream &sr, const QString &currentDir, QMetaEnum &casesEnum);
    void ReadEQUALS(ProjectData &data, QTextStream &sr);
    void ReadBOX(QTextStream &sr);
    void ReadENDBOX(ProjectData &data);
    void ReadCOPY(ProjectData &data, QTextStream &sr);
    void ReadADD(ProjectData &data, QTextStream &sr);
    void ReadMULTIPLY(ProjectData &data, QTextStream &sr);

protected:
    Box box;
    QDateTime currentDate;
};

}}}

#endif // ECLIPSEFILEREADER_H
