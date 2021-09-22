#include "readfilehelper.h"

namespace BlackOil {
namespace Data {
namespace Helpers {
namespace Eclipse {

QString ReadFileHelper::GetNextLine(QTextStream &stream)
{
    QString res = "===";
    do
    {
        if (stream.atEnd()) return nullptr;

        res = stream.readLine().replace('\t', ' ').trimmed();

        if (res.contains("--"))
        {
            int pos = res.indexOf("--");
            res = res.mid(0, pos).trimmed();
        }

        while (res.toUpper().startsWith("#IF"))
        {
            while (!res.toUpper().startsWith("#ENDIF")) res = stream.readLine().trimmed();
            res = stream.readLine().trimmed();
        }
    }
    while (res.length() == 0 || res.startsWith("--"));

    return res;
}

QString ReadFileHelper::ParseKeyword(const QString &line)
{
    if (line.length() == 0) return line;

    return line.split(' ', QString::SkipEmptyParts)[0].toUpper();
}

QStringList ReadFileHelper::ParseParams(QTextStream &sr, int nameIndex, bool canEmpty)
{
    QString temp = "";

    while (true)
    {
        QString line = GetNextLine(sr);

        if (line == nullptr) return QStringList();

        if (line == "/" && temp == "") return QStringList();

        if (line.contains("/"))
        {
            int pos = line.indexOf("/");

            temp += " " + line.mid(0, pos);
            break;
        }
        else temp += " " + line;
    }

    QStringList str = temp.split('\'');
    temp = "";
    for (int i = 0; i < str.length(); i++)
    {
        if (i % 2 == 0) temp += str[i];
        else
        {
            if (str.length() == 0) temp += "-";
            else if (nameIndex < 0) temp += str[i].replace(" ", "_");
            else temp += str[i];
        }
    }

    if (canEmpty)
    {
        str = temp.split(',');
        temp = "";
        for (int i = 0; i < str.length(); i++)
        {
            temp += (str[i].trimmed().isEmpty() ? "*" : str[i]) + ",";
        }
    }

    temp = temp.replace(',', ' ');

    QStringList res;
    str = temp.split(' ', QString::SkipEmptyParts);
    for (int i = 0; i < str.length(); i++)
    {
        if (str[i].contains("*") && i != nameIndex)
        {
            if (str[i].endsWith("*"))
            {
                int n = str[i] == "*" ? 1 : str[i].replace("*", "").toInt();
                for (int j = 0; j < n; j++) res.append("1*");
            }
            else
            {
                QStringList num_str = str[i].split('*');
                int n = num_str[0].toInt();
                for (int j = 0; j < n; j++) res.append(num_str[1]);
            }
        }
        else res.append(str[i].toUpper());
    }

    return res;
}

QString ReadFileHelper::EclipseDateToStr(QStringList &str, QMetaEnum &monthsEnum)
{
    QString days = QString("%1").arg(str[0].toInt(), 2, 10, QLatin1Char('0'));

    QString keyword = str[1].replace("'", "").toUpper();

    int month = monthsEnum.keyToValue(keyword.toLatin1());

    QString months = QString("%1").arg(month, 2, 10, QLatin1Char('0'));

    QString years = QString("%1").arg(str[2].toInt(), 4, 10, QLatin1Char('0'));

    return days + "." + months + "." + years;
}

QString ReadFileHelper::DateToStr(const QDateTime &dt)
{
    return dt.toString("dd.MM.yyyy");
}

QDateTime ReadFileHelper::StrToDate(const QString &strDate)
{
    return QDateTime::fromString(strDate, "dd.MM.yyyy");
}

void ReadFileHelper::IgnoreParams(QTextStream &sr)
{
    ParseParams(sr);
}

QStringList ReadFileHelper::GetNextLineWords(QTextStream &stream)
{
    return GetNextLine(stream).split(' ', QString::SkipEmptyParts);
}

bool ReadFileHelper::IsYes(const QString &str)
{
    return str == "YES" || str == "Y" ? true : false;
}

QVariant ReadFileHelper::GetValue(QString &data, int dataType)
{
    switch (dataType)
    {
        case DataTypeEnum::DOUBLE: return QVariant(data.toDouble());
        case DataTypeEnum::INTEGER: return QVariant(data.toInt());
    }

    return QVariant(data);
}

void ReadFileHelper::FillVector(QTextStream &sr, BoxArray &array, int dataType)
{
    bool finish = false;

    QStringList str;
    QStringList numberStr;

    while (!finish)
    {
        str = GetNextLineWords(sr);

        if (str[str.length() - 1] == "/") finish = true;

        for (int i = 0; i < (finish ? str.length() - 1 : str.length()); i++)
        {
            numberStr = str[i].split('*');

            if (numberStr.length() == 1) array.Add(GetValue(numberStr[0], dataType));
            else
            {
                int numCount = numberStr[0].toInt();
                QVariant val = GetValue(numberStr[1], dataType);

                array.AddInterval(numCount, val);
            }
        }
    }
}

void ReadFileHelper::ReadArray(QTextStream &sr, const Box &box, BoxArray &array, int dataType)
{
    array.SetBox(box);

    FillVector(sr, array, dataType);
}


}}}}
