#ifndef PMAXDATA_H
#define PMAXDATA_H

#include <qvariant.h>

#include <data_global.h>

namespace BlackOil {
namespace Data {
namespace Project {

class DATA_EXPORT PMAXData
{
public:
    PMAXData();

    QVariant PMax();
    QVariant PMaxComp();
    QVariant PMinComp();
    QVariant NumNodes();

    void SetPMax(const QVariant& pMax);
    void SetPMaxComp(const QVariant& pMaxComp);
    void SetPMinComp(const QVariant& pMinComp);
    void SetNumNodes(const QVariant& numNodes);

    void InitVariables();

protected:
    QVariant numNodes, pMaxComp, pMinComp, pMax;
};

}}}

#endif // PMAXDATA_H
