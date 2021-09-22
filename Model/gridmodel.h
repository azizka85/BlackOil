#ifndef GRIDMODEL_H
#define GRIDMODEL_H

#include <qobject.h>
#include <qvector.h>

#include <line.h>
#include <block.h>

#include <arraynamesenum.h>
#include <datatypeenum.h>
#include <projectdata.h>
#include <operatormodel.h>

#include <xlayermodel.h>
#include <ylayermodel.h>
#include <zlayermodel.h>

#include <mathhelper.h>

#include <model_global.h>

using namespace BlackOil::Data::Project;
using namespace BlackOil::Data::Helpers;

using namespace BlackOil::Model::Grid;

namespace BlackOil {
namespace Model {

class MODEL_EXPORT GridModel : public QObject
{
    Q_OBJECT
public:
    explicit GridModel(ProjectData *projectData, OperatorModel *operatorModel, QObject *parent = nullptr);

    XLayerModel *XLayer();
    YLayerModel *YLayer();
    ZLayerModel *ZLayer();

    QVariant Data(int arrayName, int i, int j, int k, int dataType = DataTypeEnum::DOUBLE, QVariant defaultValue = QVariant());
    bool DataExist(int arrayName);

    Block GetBlock(int index);
    Block GetBlock(int i, int j, int k);
    Block CalcBlockByBCG(double x0, double y0, double z0, int i, int j, int k);
    Block CalcBlockByCPG(int i, int j, int k);

    void InitVariables();
    void ProcessData();
    void ProcessBeforeSave();

    void CalcCoordLineCPG(int i, int j, Line& coordLine);
    void CalcBlockDepthsCPG(int i, int j, int k, double &d1, double &d2, double &d3, double &d4, double &d5, double &d6, double &d7, double &d8);
    bool CheckPointOrderStandardCPG();

    void CalculateExistBlockArray(QVector<bool> &existBlock);
    void CalculateDrawBlockArray(QVector<bool> &existBlock, QVector<bool> &drawBlock);
    void CalculateDisplayBlocks(QVector<bool> &drawBlock, QVector<Block> &displayBlocks, double &xMin, double &xMax, double &yMin, double &yMax, double &zMin, double &zMax);
    void NormalizeDisplayBlocks(double xMin, double xMax, double yMin, double yMax, double zMin, double zMax,
                                double &scaleX, double &scaleY, double &scaleZ, QVector<Block> &displayBlocks);

protected:
    ProjectData *projectData;
    OperatorModel *operatorModel;
    QVector<Block> blocks;

    XLayerModel *xLayer;
    YLayerModel *yLayer;
    ZLayerModel *zLayer;
};

}}

#endif // GRIDMODEL_H
