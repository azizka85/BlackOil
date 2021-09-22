#ifndef SGOFMODEL_H
#define SGOFMODEL_H

#include <qmetaobject.h>
#include <qvector.h>

#include <qabstractitemmodel.h>

#include <defaultvalues.h>
#include <projectdata.h>

#include <model_global.h>

using namespace BlackOil::Data::Project;

namespace BlackOil {
namespace Model {
namespace SF {

class MODEL_EXPORT SGOFModel : public QAbstractTableModel
{
    Q_OBJECT
    Q_ENUMS(Columns)
public:
    explicit SGOFModel(ProjectData *projectData, QObject *parent = nullptr);

    enum Columns { SGOFSg, SGOFKrG, SGOFKrO, SGOFPcOG };

    int Region();

    void InitVariables();
    void ProcessData();
    void ProcessBeforeSave();

public slots:
    void SetRegion(int region);

protected slots:
    void HandleRegionChanged(int);

protected:
    void ResetMinMax();

signals:
    void RegionChanged(int region);
    void MinMaxChanged(int column, QVariant min, QVariant max);

protected:
    ProjectData *projectData;
    int region;
    QVector<QVector<QVariant>> minMax;

    // QAbstractItemModel interface
public:
    int rowCount(const QModelIndex &) const override;
    int columnCount(const QModelIndex &) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role) override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    bool insertRows(int row, int count, const QModelIndex &parent) override;
    bool removeRows(int row, int count, const QModelIndex &parent) override;
};

}}}

#endif // SGOFMODEL_H
