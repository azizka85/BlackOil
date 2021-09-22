#ifndef READFILEHELPER_H
#define READFILEHELPER_H

#include <qmetaobject.h>
#include <qvariant.h>
#include <qstring.h>
#include <qstringlist.h>
#include <qdatetime.h>
#include <qtextstream.h>

#include <boxarray.h>
#include <datatypeenum.h>

#include <data_global.h>

using namespace BlackOil::Data::Arrays;
using namespace BlackOil::Data::Project;

namespace BlackOil {
namespace Data {
namespace Helpers {
namespace Eclipse {

class DATA_EXPORT ReadFileHelper
{
public:
    static QString GetNextLine(QTextStream &stream);
    static QString ParseKeyword(const QString &line);
    static QStringList ParseParams(QTextStream &sr, int nameIndex = -1, bool canEmpty = false);
    static QString EclipseDateToStr(QStringList &str, QMetaEnum &monthsEnum);
    static QString DateToStr(const QDateTime &dt);
    static QDateTime StrToDate(const QString &strDate);
    static void IgnoreParams(QTextStream &sr);
    static QStringList GetNextLineWords(QTextStream &stream);
    static bool IsYes(const QString &str);

    static QVariant GetValue(QString &data, int dataType);
    static void FillVector(QTextStream &sr, BoxArray &array, int dataType);
    static void ReadArray(QTextStream &sr, const Box &box, BoxArray &array, int dataType);
};

}}}}

#endif // READFILEHELPER_H
