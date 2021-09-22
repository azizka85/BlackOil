#include "operatormodel.h"

namespace BlackOil {
namespace Model {

OperatorModel::OperatorModel(ProjectData *projectData, QObject *parent) : QObject(parent)
{
    this->projectData = projectData;

    int arrayNamesCount = ArrayNamesEnum::staticMetaObject.enumerator(ArrayNamesEnum::staticMetaObject.indexOfEnumerator("ArrayNames")).keyCount();
    int operatorTypesCount = OperatorTypeEnum::staticMetaObject.enumerator(OperatorTypeEnum::staticMetaObject.indexOfEnumerator("OperatorType")).keyCount();

    indexes.resize(operatorTypesCount);

    for(int i = 0; i < operatorTypesCount; i++) indexes[i].resize(arrayNamesCount);
}

void OperatorModel::InitVariables()
{
    int arrayNamesCount = ArrayNamesEnum::staticMetaObject.enumerator(ArrayNamesEnum::staticMetaObject.indexOfEnumerator("ArrayNames")).keyCount();
    int operatorTypesCount = OperatorTypeEnum::staticMetaObject.enumerator(OperatorTypeEnum::staticMetaObject.indexOfEnumerator("OperatorType")).keyCount();

    for(int i = 0; i < operatorTypesCount; i++)
        for(int j = 0; j < arrayNamesCount; j++)
            indexes[i][j].clear();
}

void OperatorModel::ProcessData()
{
    for(int i = 0; i < projectData->Operators().size(); i++)
        indexes[projectData->Operators()[i].OperatorType()][projectData->Operators()[i].ArrayName().toInt()].push_back(i);
}

void OperatorModel::ProcessBeforeSave()
{

}

QVariant OperatorModel::GetEQUALSData(int arrayName, int i, int j, int k, int dataType)
{
    for(int index = 0; index < indexes[OperatorTypeEnum::EQUALS][arrayName].size(); index++)
    {
        if(projectData->Operators()[indexes[OperatorTypeEnum::EQUALS][arrayName][index]].Box().Contains(i, j, k))
        {
            switch(dataType)
            {
                case DataTypeEnum::DOUBLE: return projectData->Operators()[indexes[OperatorTypeEnum::EQUALS][arrayName][index]].Value().toDouble();
                case DataTypeEnum::INTEGER: return projectData->Operators()[indexes[OperatorTypeEnum::EQUALS][arrayName][index]].Value().toInt();
            }
        }
    }

    return QVariant();
}

bool OperatorModel::EQUALSExist(int arrayName)
{
    return indexes[OperatorTypeEnum::EQUALS][arrayName].size() > 0;
}

QVariant OperatorModel::GetCOPYData(int arrayName, int i, int j, int k, int dataType)
{
    for(int index = 0; index < indexes[OperatorTypeEnum::COPY][arrayName].size(); index++)
    {
        if(projectData->Operators()[indexes[OperatorTypeEnum::COPY][arrayName][index]].Box().Contains(i, j, k))
        {
            switch(dataType)
            {
                case DataTypeEnum::DOUBLE: return projectData->Operators()[indexes[OperatorTypeEnum::COPY][arrayName][index]].Value().toDouble();
                case DataTypeEnum::INTEGER: return projectData->Operators()[indexes[OperatorTypeEnum::COPY][arrayName][index]].Value().toInt();
            }
        }
    }

    return QVariant();
}

bool OperatorModel::COPYExist(int arrayName)
{
    return indexes[OperatorTypeEnum::COPY][arrayName].size() > 0;
}

void OperatorModel::MULTIPLYValue(int arrayName, QVariant &val, int i, int j, int k, int dataType)
{
    for(int index = 0; index < indexes[OperatorTypeEnum::MULTIPLY][arrayName].size(); index++)
    {
        if(projectData->Operators()[indexes[OperatorTypeEnum::MULTIPLY][arrayName][index]].Box().Contains(i, j, k))
        {
            switch(dataType)
            {
                case DataTypeEnum::DOUBLE:
                    val = val.toDouble() * projectData->Operators()[indexes[OperatorTypeEnum::MULTIPLY][arrayName][index]].Value().toDouble();
                    break;
                case DataTypeEnum::INTEGER:
                    val = val.toInt() * projectData->Operators()[indexes[OperatorTypeEnum::MULTIPLY][arrayName][index]].Value().toInt();
                    break;
            }

            break;
        }
    }
}

void OperatorModel::ADDValue(int arrayName, QVariant &val, int i, int j, int k, int dataType)
{
    for(int index = 0; index < indexes[OperatorTypeEnum::ADD][arrayName].size(); index++)
    {
        if(projectData->Operators()[indexes[OperatorTypeEnum::ADD][arrayName][index]].Box().Contains(i, j, k))
        {
            switch(dataType)
            {
                case DataTypeEnum::DOUBLE:
                    val = val.toDouble() + projectData->Operators()[indexes[OperatorTypeEnum::ADD][arrayName][index]].Value().toDouble();
                    break;
                case DataTypeEnum::INTEGER:
                    val = val.toInt() + projectData->Operators()[indexes[OperatorTypeEnum::ADD][arrayName][index]].Value().toInt();
                    break;
            }

            break;
        }
    }
}

}}
