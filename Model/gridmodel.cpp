#include "gridmodel.h"

namespace BlackOil {
namespace Model {

GridModel::GridModel(ProjectData *projectData, OperatorModel *operatorModel, QObject *parent): QObject(parent)
{
    this->projectData = projectData;
    this->operatorModel = operatorModel;

    xLayer = new XLayerModel(this);
    yLayer = new YLayerModel(this);
    zLayer = new ZLayerModel(this);
}

XLayerModel *GridModel::XLayer()
{
    return xLayer;
}

YLayerModel *GridModel::YLayer()
{
    return yLayer;
}

ZLayerModel *GridModel::ZLayer()
{
    return zLayer;
}

QVariant GridModel::Data(int arrayName, int i, int j, int k, int dataType, QVariant defaultValue)
{
    QVariant val;

    int cnt = ArrayNamesEnum::staticMetaObject.enumerator(ArrayNamesEnum::staticMetaObject.indexOfEnumerator("ArrayNames")).keyCount();

    if(arrayName >= 0 && arrayName < cnt)
    {
        if(projectData->Arrays()[arrayName].Box().Contains(i, j, k))
            val = projectData->Arrays()[arrayName](i, j, k);

        QVariant value = operatorModel->GetEQUALSData(arrayName, i, j, k, dataType);

        val = !value.isNull() ? value : val;

        value = operatorModel->GetCOPYData(arrayName, i, j, k, dataType);

        val = !value.isNull() ? value : val;

        operatorModel->MULTIPLYValue(arrayName, val, i, j, k, dataType);

        operatorModel->ADDValue(arrayName, val, i, j, k, dataType);
    }

    return val.isNull() ? defaultValue : val;
}

bool GridModel::DataExist(int arrayName)
{
    return projectData->Arrays()[arrayName].Box().N() > 0 || operatorModel->EQUALSExist(arrayName) || operatorModel->COPYExist(arrayName);
}

Block GridModel::GetBlock(int index)
{
    return blocks[index];
}

Block GridModel::GetBlock(int i, int j, int k)
{
    int nx = projectData->Nx();
    int ny = projectData->Ny();

    int ind = k*nx*ny + j*nx + i;

    return GetBlock(ind);
}

Block GridModel::CalcBlockByBCG(double x0, double y0, double z0, int i, int j, int k)
{
    Block current;

    double x1 = x0;
    double y1 = y0;
    double z1 = z0;

    double deltaX = Data(ArrayNamesEnum::DX, i, j, k).toDouble();
    double deltaY = Data(ArrayNamesEnum::DY, i, j, k).toDouble();
    double deltaZ = Data(ArrayNamesEnum::DZ, i, j, k).toDouble();

    double x2 = x0 + deltaX;
    double y2 = y0 + deltaY;
    double z2 = z0 + deltaZ;

    current.SetI(i);
    current.SetJ(j);
    current.SetK(k);

    current.P1().SetX(x1); current.P1().SetY(y1); current.P1().SetZ(z1);
    current.P2().SetX(x2); current.P2().SetY(y1); current.P2().SetZ(z1);
    current.P3().SetX(x1); current.P3().SetY(y2); current.P3().SetZ(z1);
    current.P4().SetX(x2); current.P4().SetY(y2); current.P4().SetZ(z1);
    current.P5().SetX(x1); current.P5().SetY(y1); current.P5().SetZ(z2);
    current.P6().SetX(x2); current.P6().SetY(y1); current.P6().SetZ(z2);
    current.P7().SetX(x1); current.P7().SetY(y2); current.P7().SetZ(z2);
    current.P8().SetX(x2); current.P8().SetY(y2); current.P8().SetZ(z2);

    return current;
}

Block GridModel::CalcBlockByCPG(int i, int j, int k)
{
    Line coordLine;

    double d1, d2, d3, d4, d5, d6, d7, d8;

    CalcBlockDepthsCPG(i, j, k, d1, d2, d3, d4, d5, d6, d7, d8);   

    Block block;

    block.SetI(i);
    block.SetJ(j);
    block.SetK(k);

    if(CheckPointOrderStandardCPG())
    {
        CalcCoordLineCPG(i, j, coordLine);

        MathHelper::IntersectZPlane(coordLine, d1, block.P1());
        MathHelper::IntersectZPlane(coordLine, d5, block.P5());

        CalcCoordLineCPG(i+1, j, coordLine);

        MathHelper::IntersectZPlane(coordLine, d2, block.P2());
        MathHelper::IntersectZPlane(coordLine, d6, block.P6());

        CalcCoordLineCPG(i, j+1, coordLine);

        MathHelper::IntersectZPlane(coordLine, d3, block.P3());
        MathHelper::IntersectZPlane(coordLine, d7, block.P7());

        CalcCoordLineCPG(i+1, j+1, coordLine);

        MathHelper::IntersectZPlane(coordLine, d4, block.P4());
        MathHelper::IntersectZPlane(coordLine, d8, block.P8());
    }
    else
    {
        CalcCoordLineCPG(i, j, coordLine);

        MathHelper::IntersectZPlane(coordLine, d1, block.P8());
        MathHelper::IntersectZPlane(coordLine, d5, block.P4());

        CalcCoordLineCPG(i+1, j, coordLine);

        MathHelper::IntersectZPlane(coordLine, d2, block.P7());
        MathHelper::IntersectZPlane(coordLine, d6, block.P3());

        CalcCoordLineCPG(i, j+1, coordLine);

        MathHelper::IntersectZPlane(coordLine, d3, block.P6());
        MathHelper::IntersectZPlane(coordLine, d7, block.P2());

        CalcCoordLineCPG(i+1, j+1, coordLine);

        MathHelper::IntersectZPlane(coordLine, d4, block.P5());
        MathHelper::IntersectZPlane(coordLine, d8, block.P1());
    }

    return block;
}

void GridModel::InitVariables()
{
    blocks.clear();

    xLayer->InitVariables();
    yLayer->InitVariables();
    zLayer->InitVariables();
}

void GridModel::ProcessData()
{
    int nx = projectData->Nx();
    int ny = projectData->Ny();
    int nz = projectData->Nz();

    blocks.resize(nx*ny*nz);

    double x0 = 0;
    double y0 = 0;
    double z0 = 0;

    bool isBlockCentered = DataExist(ArrayNamesEnum::TOPS);

    for(int i = 0; i < nx; i++)
    {
        y0 = 0;

        for(int j = 0; j < ny; j++)
        {
            z0 = Data(ArrayNamesEnum::TOPS, i, j, 0).toDouble();

            for(int k = 0; k < nz; k++)
            {
                Block block = isBlockCentered ? CalcBlockByBCG(x0, y0, z0, i, j, k) : CalcBlockByCPG(i, j, k);

                int ind = k*nx*ny + j*nx + i;

                blocks[ind] = block;

                if(k == nz-1 && j == ny-1) x0 = block.P8().X();
                if(k == nz-1) y0 = block.P8().Y();
                z0 = block.P8().Z();
            }
        }
    }

    xLayer->ProcessData(nx);
    yLayer->ProcessData(ny);
    zLayer->ProcessData(nz);
}

void GridModel::ProcessBeforeSave()
{
    xLayer->ProcessBeforeSave();
    yLayer->ProcessBeforeSave();
    zLayer->ProcessBeforeSave();
}

void GridModel::CalcCoordLineCPG(int i, int j, Line &coordLine)
{
    int nx = projectData->Nx();
    // int ny = projectData->Ny();

    // if(j*(nx+1) + i >= (nx+1)*(ny+1)) return false; //TODO: must be >= (nx+1)*(ny+1)*numRes

    int cur = (j*(nx + 1) + i)*6;

    double x1 = Data(ArrayNamesEnum::COORD, cur + 0, 0, 0).toDouble();
    double y1 = Data(ArrayNamesEnum::COORD, cur + 1, 0, 0).toDouble();
    double z1 = Data(ArrayNamesEnum::COORD, cur + 2, 0, 0).toDouble();

    double x2 = Data(ArrayNamesEnum::COORD, cur + 3, 0, 0).toDouble();
    double y2 = Data(ArrayNamesEnum::COORD, cur + 4, 0, 0).toDouble();
    double z2 = Data(ArrayNamesEnum::COORD, cur + 5, 0, 0).toDouble();

    // if(ISEQUAL(x1-x2, 0) && ISEQUAL(y1-y2, 0)) z2 = z1+10;

    coordLine.P1().SetX(x1);
    coordLine.P1().SetY(y1);
    coordLine.P1().SetZ(z1);

    coordLine.P2().SetX(x2);
    coordLine.P2().SetY(y2);
    coordLine.P2().SetZ(z2);
}

void GridModel::CalcBlockDepthsCPG(int i, int j, int k, double &d1, double &d2, double &d3, double &d4, double &d5, double &d6, double &d7, double &d8)
{
    int nx = projectData->Nx();
    int ny = projectData->Ny();

    // cur = pi + 2*i + 2*nx*pj + 4*nx*j + 4*nx*ny*pk + 8*nx*ny*k
    // p = pi + 2*pj + 4*pk

    int cur = 8*nx*ny*k + 4*nx*j + 2*i; // pi={0,1}, pj=0, pk=0

    d1 = Data(ArrayNamesEnum::ZCORN, cur + 0, 0, 0).toDouble(); // pi=0
    d2 = Data(ArrayNamesEnum::ZCORN, cur + 1, 0, 0).toDouble(); // pi=1

    cur = 8*nx*ny*k + 2*nx*(2*j+1) + 2*i; // pi={0,1}, pj=1, pk=0

    d3 = Data(ArrayNamesEnum::ZCORN, cur + 0, 0, 0).toDouble(); // pi=0
    d4 = Data(ArrayNamesEnum::ZCORN, cur + 1, 0, 0).toDouble(); // pi=1

    cur = 4*nx*ny*(2*k+1) + 4*nx*j + 2*i; // pi={0,1}, pj=0, pk=1

    d5 = Data(ArrayNamesEnum::ZCORN, cur + 0, 0, 0).toDouble(); // pi=0
    d6 = Data(ArrayNamesEnum::ZCORN, cur + 1, 0, 0).toDouble(); // pi=1

    cur = 4*nx*ny*(2*k+1) + 2*nx*(2*j+1) + 2*i; // pi={0,1}, pj=1, pk=1

    d7 = Data(ArrayNamesEnum::ZCORN, cur + 0, 0, 0).toDouble(); // pi=0
    d8 = Data(ArrayNamesEnum::ZCORN, cur + 1, 0, 0).toDouble(); // pi=1
}

bool GridModel::CheckPointOrderStandardCPG()
{
    Line coordLine;

    Point p1, p2, p3, p4;

    double d1, d2, d3, d4, d5, d6, d7, d8;

    CalcBlockDepthsCPG(0, 0, 0, d1, d2, d3, d4, d5, d6, d7, d8);

    CalcCoordLineCPG(0, 0, coordLine);

    MathHelper::IntersectZPlane(coordLine, d1, p1);

    CalcCoordLineCPG(1, 0, coordLine);

    MathHelper::IntersectZPlane(coordLine, d2, p2);

    CalcCoordLineCPG(0, 1, coordLine);

    MathHelper::IntersectZPlane(coordLine, d3, p3);

    CalcCoordLineCPG(1, 1, coordLine);

    MathHelper::IntersectZPlane(coordLine, d4, p4);

    return p1.X() <= p2.X() &&
            p3.X() <= p4.X() &&
            p1.Y() <= p3.Y() &&
            p2.Y() <= p4.Y();
}

void GridModel::CalculateExistBlockArray(QVector<bool> &existBlock)
{
    int nx = projectData->Nx();
    int ny = projectData->Ny();
    int nz = projectData->Nz();

    existBlock.resize(nx*ny*nz);

    for(int i = 0; i < nx; i++)
    {
        for(int j = 0; j < ny; j++)
        {
            for(int k = 0; k < nz; k++)
            {
                int ind = k*nx*ny + j*nx + i; // i, j, k                                

                existBlock[ind] = Data(ArrayNamesEnum::ACTNUM, i, j, k, DataTypeEnum::INTEGER, 1).toInt() > 0
                                    && xLayer->DisplayBlocks()[i] && yLayer->DisplayBlocks()[j] && zLayer->DisplayBlocks()[k];
            }
        }
    }
}

void GridModel::CalculateDrawBlockArray(QVector<bool> &existBlock, QVector<bool> &drawBlock)
{
    int nx = projectData->Nx();
    int ny = projectData->Ny();
    int nz = projectData->Nz();

    drawBlock.resize(nx*ny*nz);

    for(int i = 0; i < nx; i++)
    {
        for(int j = 0; j < ny; j++)
        {
            for(int k = 0; k < nz; k++)
            {
                int ind = k*nx*ny + j*nx + i; // i, j, k

                Block block = blocks[ind];

                drawBlock[ind] = false;

                if(!existBlock[ind]) continue;

                if (i == 0 || i == nx - 1 || j == 0 || j == ny - 1 || k == 0 || k == nz - 1)
                {
                    drawBlock[ind] = existBlock[ind];
                }
                else
                {
                    int ind1 = (k-1)*nx*ny + j*nx + i; // i, j, k-1
                    int ind2 = (k+1)*nx*ny + j*nx + i; // i, j, k+1

                    if(!existBlock[ind1] || !existBlock[ind2]) drawBlock[ind] = true;
                    else
                    {
                        // i+1,j
                        ind1 = j*nx + (i+1); // i+1, j, 0
                        ind2 = (nz-1)*nx*ny + j*nx + (i+1); // i+1, j, nz-1

                        Block block1 = blocks[ind1];
                        Block block2 = blocks[ind2];

                        bool found = false;

                        if(block.P6().Z() < block1.P1().Z() && block.P8().Z() < block1.P3().Z())
                        {
                            drawBlock[ind] = true;

                            continue;
                        }

                        if(block.P2().Z() > block2.P5().Z() && block.P4().Z() > block2.P7().Z())
                        {
                            drawBlock[ind] = true;

                            continue;
                        }

                        Segment lside1(block.P2().Z(), block.P6().Z());
                        Segment rside1(block.P4().Z(), block.P8().Z());

                        for(int kk = 0; kk < nz; kk++)
                        {
                            int subInd = kk*nx*ny + j*nx + i+1; // i+1, j, kk

                            Block subBlock = blocks[subInd];

                            if(!existBlock[subInd])
                            {
                                Segment lside2(subBlock.P1().Z(), subBlock.P5().Z());
                                Segment rside2(subBlock.P3().Z(), subBlock.P7().Z());

                                if(MathHelper::IsIntersectedSurfaces(lside1, rside1, lside2, rside2))
                                {
                                    found = true;

                                    break;
                                }
                            }
                        }

                        if(found)
                        {
                            drawBlock[ind] = true;

                            continue;
                        }

                        // i-1, j
                        ind1 = j*nx + (i-1); // i-1, j, 0
                        ind2 = (nz-1)*nx*ny + j*nx + (i-1); // i-1, j, nz-1

                        block1 = blocks[ind1];
                        block2 = blocks[ind2];

                        found = false;

                        if(block.P5().Z() < block1.P2().Z() && block.P7().Z() < block1.P4().Z())
                        {
                            drawBlock[ind] = true;

                            continue;
                        }

                        if(block.P1().Z() > block2.P6().Z() && block.P3().Z() > block2.P8().Z())
                        {
                            drawBlock[ind] = true;

                            continue;
                        }

                        lside1 = Segment(block.P1().Z(), block.P5().Z());
                        rside1 = Segment(block.P3().Z(), block.P7().Z());

                        for(int kk = 0; kk < nz; kk++)
                        {
                            int subInd = kk*nx*ny + j*nx + i-1; // i-1, j, kk

                            Block subBlock = blocks[subInd];

                            if(!existBlock[subInd])
                            {
                                Segment lside2(subBlock.P2().Z(), subBlock.P6().Z());
                                Segment rside2(subBlock.P4().Z(), subBlock.P8().Z());

                                if(MathHelper::IsIntersectedSurfaces(lside1, rside1, lside2, rside2))
                                {
                                    found = true;

                                    break;
                                }
                            }
                        }

                        if(found)
                        {
                            drawBlock[ind] = true;

                            continue;
                        }

                        // i, j+1
                        ind1 = (j+1)*nx + i; // i, j+1, 0
                        ind2 = (nz-1)*nx*ny + (j+1)*nx + i; // i, j+1, nz-1

                        block1 = blocks[ind1];
                        block2 = blocks[ind2];

                        found = false;

                        if(block.P7().Z() < block1.P1().Z() && block.P8().Z() < block1.P2().Z())
                        {
                            drawBlock[ind] = true;

                            continue;
                        }

                        if(block.P3().Z() > block2.P5().Z() && block.P4().Z() > block2.P6().Z())
                        {
                            drawBlock[ind] = true;

                            continue;
                        }

                        lside1 = Segment(block.P3().Z(), block.P7().Z());
                        rside1 = Segment(block.P4().Z(), block.P8().Z());

                        for(int kk = 0; kk < nz; kk++)
                        {
                            int subInd = kk*nx*ny + (j+1)*nx + i; // i, j+1, kk

                            Block subBlock = blocks[subInd];

                            if(!existBlock[subInd])
                            {
                                Segment lside2(subBlock.P1().Z(), subBlock.P5().Z());
                                Segment rside2(subBlock.P2().Z(), subBlock.P6().Z());

                                if(MathHelper::IsIntersectedSurfaces(lside1, rside1, lside2, rside2))
                                {
                                    found = true;

                                    break;
                                }
                            }
                        }

                        if(found)
                        {
                            drawBlock[ind] = true;

                            continue;
                        }

                        // i, j-1
                        ind1 = (j-1)*nx + i; // i, j-1, 0
                        ind2 = (nz-1)*nx*ny + (j-1)*nx + i; // i, j-1, nz-1

                        block1 = blocks[ind1];
                        block2 = blocks[ind2];

                        found = false;

                        if(block.P5().Z() < block1.P3().Z() && block.P6().Z() < block1.P4().Z())
                        {
                            drawBlock[ind] = true;

                            continue;
                        }

                        if(block.P1().Z() > block2.P7().Z() && block.P2().Z() > block2.P8().Z())
                        {
                            drawBlock[ind] = true;

                            continue;
                        }

                        lside1 = Segment(block.P1().Z(), block.P5().Z());
                        rside1 = Segment(block.P2().Z(), block.P6().Z());

                        for(int kk = 0; kk < nz; kk++)
                        {
                            int subInd = kk*nx*ny + (j-1)*nx + i; // i, j-1, kk

                            Block subBlock = blocks[subInd];

                            if(!existBlock[subInd])
                            {
                                Segment lside2(subBlock.P3().Z(), subBlock.P7().Z());
                                Segment rside2(subBlock.P4().Z(), subBlock.P8().Z());

                                if(MathHelper::IsIntersectedSurfaces(lside1, rside1, lside2, rside2))
                                {
                                    found = true;

                                    break;
                                }
                            }
                        }

                        if(found)
                        {
                            drawBlock[ind] = true;

                            continue;
                        }
                    }
                }
            }
        }
    }
}

void GridModel::CalculateDisplayBlocks(QVector<bool> &drawBlock, QVector<Block> &displayBlocks, double &xMin, double &xMax, double &yMin, double &yMax, double &zMin, double &zMax)
{
    int nx = projectData->Nx();
    int ny = projectData->Ny();
    int nz = projectData->Nz();

    xMin = xMax = 0;
    yMin = yMax = 0;
    zMin = zMax = 0;

    for(int i = 0; i < nx; i++)
    {
        for(int j = 0; j < ny; j++)
        {
            for(int k = 0; k < nz; k++)
            {
                int ind = k*nx*ny + j*nx + i;

                Block block = blocks[ind];

                if(drawBlock[ind])
                {
                    if(displayBlocks.size() == 0)
                    {
                        xMin = xMax = block.P1().X();
                        yMin = yMax = block.P1().Y();
                        zMin = zMax = block.P1().Z();
                    }

                    xMin = qMin(xMin, qMin(block.P1().X(), qMin(block.P2().X(), qMin(block.P3().X(), qMin(block.P4().X(), qMin(block.P5().X(), qMin(block.P6().X(), qMin(block.P7().X(), block.P8().X()))))))));
                    yMin = qMin(yMin, qMin(block.P1().Y(), qMin(block.P2().Y(), qMin(block.P3().Y(), qMin(block.P4().Y(), qMin(block.P5().Y(), qMin(block.P6().Y(), qMin(block.P7().Y(), block.P8().Y()))))))));
                    zMin = qMin(zMin, qMin(block.P1().Z(), qMin(block.P2().Z(), qMin(block.P3().Z(), qMin(block.P4().Z(), qMin(block.P5().Z(), qMin(block.P6().Z(), qMin(block.P7().Z(), block.P8().Z()))))))));

                    xMax = qMax(xMax, qMax(block.P1().X(), qMax(block.P2().X(), qMax(block.P3().X(), qMax(block.P4().X(), qMax(block.P5().X(), qMax(block.P6().X(), qMax(block.P7().X(), block.P8().X()))))))));
                    yMax = qMax(yMax, qMax(block.P1().Y(), qMax(block.P2().Y(), qMax(block.P3().Y(), qMax(block.P4().Y(), qMax(block.P5().Y(), qMax(block.P6().Y(), qMax(block.P7().Y(), block.P8().Y()))))))));
                    zMax = qMax(zMax, qMax(block.P1().Z(), qMax(block.P2().Z(), qMax(block.P3().Z(), qMax(block.P4().Z(), qMax(block.P5().Z(), qMax(block.P6().Z(), qMax(block.P7().Z(), block.P8().Z()))))))));

                    displayBlocks.append(block);
                }
            }
        }
    }
}

void GridModel::NormalizeDisplayBlocks(double xMin, double xMax, double yMin, double yMax, double zMin, double zMax,
                                       double &scaleX, double &scaleY, double &scaleZ, QVector<Block> &displayBlocks)
{
    double maxD = qMax(qMax(xMax - xMin, yMax - yMin), zMax - zMin);

    maxD = ISEQUAL(maxD, 0) ? 1 : maxD;

    scaleX = (xMax - xMin)/maxD;
    scaleY = (yMax - yMin)/maxD;
    scaleZ = (zMax - zMin)/maxD;

    for(int i = 0; i < displayBlocks.size(); i++)
    {
        double x = displayBlocks[i].P1().X();
        double y = displayBlocks[i].P1().Y();
        double z = displayBlocks[i].P1().Z();

        displayBlocks[i].P1().SetX(-0.5*scaleX + (x-xMin)/maxD);
        displayBlocks[i].P1().SetY(-0.5*scaleY + (y-yMin)/maxD);
        displayBlocks[i].P1().SetZ(-0.5*scaleZ + (z-zMin)/maxD);

        x = displayBlocks[i].P2().X();
        y = displayBlocks[i].P2().Y();
        z = displayBlocks[i].P2().Z();

        displayBlocks[i].P2().SetX(-0.5*scaleX + (x-xMin)/maxD);
        displayBlocks[i].P2().SetY(-0.5*scaleY + (y-yMin)/maxD);
        displayBlocks[i].P2().SetZ(-0.5*scaleZ + (z-zMin)/maxD);

        x = displayBlocks[i].P3().X();
        y = displayBlocks[i].P3().Y();
        z = displayBlocks[i].P3().Z();

        displayBlocks[i].P3().SetX(-0.5*scaleX + (x-xMin)/maxD);
        displayBlocks[i].P3().SetY(-0.5*scaleY + (y-yMin)/maxD);
        displayBlocks[i].P3().SetZ(-0.5*scaleZ + (z-zMin)/maxD);

        x = displayBlocks[i].P4().X();
        y = displayBlocks[i].P4().Y();
        z = displayBlocks[i].P4().Z();

        displayBlocks[i].P4().SetX(-0.5*scaleX + (x-xMin)/maxD);
        displayBlocks[i].P4().SetY(-0.5*scaleY + (y-yMin)/maxD);
        displayBlocks[i].P4().SetZ(-0.5*scaleZ + (z-zMin)/maxD);

        x = displayBlocks[i].P5().X();
        y = displayBlocks[i].P5().Y();
        z = displayBlocks[i].P5().Z();

        displayBlocks[i].P5().SetX(-0.5*scaleX + (x-xMin)/maxD);
        displayBlocks[i].P5().SetY(-0.5*scaleY + (y-yMin)/maxD);
        displayBlocks[i].P5().SetZ(-0.5*scaleZ + (z-zMin)/maxD);

        x = displayBlocks[i].P6().X();
        y = displayBlocks[i].P6().Y();
        z = displayBlocks[i].P6().Z();

        displayBlocks[i].P6().SetX(-0.5*scaleX + (x-xMin)/maxD);
        displayBlocks[i].P6().SetY(-0.5*scaleY + (y-yMin)/maxD);
        displayBlocks[i].P6().SetZ(-0.5*scaleZ + (z-zMin)/maxD);

        x = displayBlocks[i].P7().X();
        y = displayBlocks[i].P7().Y();
        z = displayBlocks[i].P7().Z();

        displayBlocks[i].P7().SetX(-0.5*scaleX + (x-xMin)/maxD);
        displayBlocks[i].P7().SetY(-0.5*scaleY + (y-yMin)/maxD);
        displayBlocks[i].P7().SetZ(-0.5*scaleZ + (z-zMin)/maxD);

        x = displayBlocks[i].P8().X();
        y = displayBlocks[i].P8().Y();
        z = displayBlocks[i].P8().Z();

        displayBlocks[i].P8().SetX(-0.5*scaleX + (x-xMin)/maxD);
        displayBlocks[i].P8().SetY(-0.5*scaleY + (y-yMin)/maxD);
        displayBlocks[i].P8().SetZ(-0.5*scaleZ + (z-zMin)/maxD);
    }   
}

}}
