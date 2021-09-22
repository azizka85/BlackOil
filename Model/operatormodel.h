#ifndef OPERATORMODEL_H
#define OPERATORMODEL_H

#include <qobject.h>
#include <qvector.h>

#include <arraynamesenum.h>
#include <datatypeenum.h>
#include <operatortypeenum.h>
#include <projectdata.h>

#include <model_global.h>

using namespace BlackOil::Data::Project;

namespace BlackOil {
namespace Model {

class MODEL_EXPORT OperatorModel : public QObject
{
    Q_OBJECT
public:
    explicit OperatorModel(ProjectData *projectData, QObject *parent = nullptr);

    void InitVariables();
    void ProcessData();
    void ProcessBeforeSave();

    QVariant GetEQUALSData(int arrayName, int i, int j, int k, int dataType = DataTypeEnum::DOUBLE);
    bool EQUALSExist(int arrayName);
    QVariant GetCOPYData(int arrayName, int i, int j, int k, int dataType = DataTypeEnum::DOUBLE);
    bool COPYExist(int arrayName);
    void MULTIPLYValue(int arrayName, QVariant &val, int i, int j, int k, int dataType = DataTypeEnum::DOUBLE);
    void ADDValue(int arrayName, QVariant &val, int i, int j, int k, int dataType = DataTypeEnum::DOUBLE);

protected:
    ProjectData *projectData;
    QVector<QVector<QVector<int>>> indexes;
};

}}

#endif // OPERATORMODEL_H
