#ifndef OPERATORDATA_H
#define OPERATORDATA_H

#include <qvariant.h>
#include <qstring.h>

#include <box.h>
#include <operatortypeenum.h>

#include <data_global.h>

using namespace BlackOil::Data::Grid;

namespace BlackOil {
namespace Data {
namespace Project {

class DATA_EXPORT OperatorData
{
public:
    OperatorData();

    QVariant ArrayName();
    QString Value();
    QVariant Source();
    Box& Box();
    int OperatorType();

    void SetArrayName(const QVariant &arrayName);
    void SetValue(const QString &value);
    void SetSource(const QVariant &source);
    void SetBox(const class Box& box);
    void SetOperatorType(int operatorType);

    void InitVariables();

private:
    QVariant arrayName;
    QString value;
    QVariant source;
    class Box box;
    int operatorType;
};

}}}

#endif // OPERATORDATA_H
