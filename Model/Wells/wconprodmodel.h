#ifndef WCONPRODMODEL_H
#define WCONPRODMODEL_H

#include <qmetaobject.h>
#include <qstring.h>
#include <qvector.h>

#include <qabstractitemmodel.h>

#include <wellstatusenum.h>
#include <wellcontrolenum.h>
#include <projectdata.h>

#include <welspecsmodel.h>

#include <model_global.h>

namespace BlackOil {
namespace Model {
namespace Wells {

class MODEL_EXPORT WCONPRODModel : public QAbstractItemModel
{
    Q_OBJECT
    Q_ENUMS(Columns)
public:
    explicit WCONPRODModel(ProjectData *projectData, WELSPECSModel *welspecs, QObject *parent = nullptr);

    enum Columns { WellName, WellDate, WellStatus, WellControl, WellORAT, WellWRAT, WellGRAT, WellLRAT, WellRESV, WellBHP };

    void InitVariables();
    void ProcessData();
    void ProcessBeforeSave();

protected slots:
    void HandleWELSPECSInserted(int welspecsIndex);
    void HandleWELSPECSRemoved(int welspecsIndex);
    void HandleWELSPECSChanged(int welspecsIndex);

protected:
    bool CheckWELSPECSMatch(int index, int welspecsIndex);
    void HandleWellNameChanged(QModelIndex index);

protected:
    ProjectData *projectData;
    WELSPECSModel *welspecs;
    QVector<int> groups;
    QVector<QVector<int>> indexes;
    QVector<int> removed;

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

#endif // WCONPRODMODEL_H
