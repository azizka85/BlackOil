#ifndef WELSPECSMODEL_H
#define WELSPECSMODEL_H

#include <qmetaobject.h>
#include <qstring.h>
#include <qvector.h>
#include <qhash.h>

#include <qabstractitemmodel.h>

#include <defaultvalues.h>
#include <projectdata.h>

#include <model_global.h>

using namespace BlackOil::Data::Project;

namespace BlackOil {
namespace Model {
namespace Wells {

class MODEL_EXPORT WELSPECSModel : public QAbstractItemModel
{
    Q_OBJECT
    Q_ENUMS(Columns)
public:
    explicit WELSPECSModel(ProjectData *projectData, QObject *parent = nullptr);

    enum Columns {WellGroup, WellName, WellDate, WellI, WellJ, WellDepth};

    QVector<int> WELSPECSIndexes();

    void InitVariables();
    void ProcessData();
    void ProcessBeforeSave();

signals:
    void WELSPECSRemoved(int welspecsIndex);
    void WELSPECSInserted(int welspecsIndex);
    void WELSPECSChanged(int welspecsIndex);

protected:
    ProjectData *projectData;
    QVector<int> removed;
    QVector<QString> groups;
    QVector<QVector<int>> indexes;

    // QAbstractItemModel interface
public:
    QModelIndex index(int row, int column, const QModelIndex &parent) const override;
    QModelIndex parent(const QModelIndex &child) const override;
    int rowCount(const QModelIndex &parent) const override;
    int columnCount(const QModelIndex &) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role) override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    bool insertRows(int row, int count, const QModelIndex &parent) override;
    bool removeRows(int row, int count, const QModelIndex &parent) override;
};

}}}

#endif // WELSPECSMODEL_H
